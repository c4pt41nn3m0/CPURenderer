#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include "light.h"

///////////////////////////////////////////////////////////////////////////////
// Array of triangles that should be rendered frame by frame
///////////////////////////////////////////////////////////////////////////////
triangle_t* triangles_to_render = NULL;

///////////////////////////////////////////////////////////////////////////////
// Global variables for execution status and game loop
///////////////////////////////////////////////////////////////////////////////
bool is_running = false;
int previous_frame_time = 0;

///////////////////////////////////////////////////////////////////////////////
// Global variables for rendering
///////////////////////////////////////////////////////////////////////////////
vec3_t camera_position = { .x = 0, .y = 0, .z = 0 };
mat4_t proj_matrix;
float fov = 0.0; 
float aspect_ratio = 0.0;
float znear = 0.0;
float zfar = 0.0;


///////////////////////////////////////////////////////////////////////////////
// Setup function to initialize variables and game objects
///////////////////////////////////////////////////////////////////////////////
void setup(void) {

    projection_type = PROJECTION_PERSPECTIVE;
    render_method = RENDER_WIRE;
    culling_type = CULL_BACKFACE;

    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    // Initialize the projection matrix and projection variables
    fov = M_PI/2.0; // 90 degrees in radians
    aspect_ratio = (float)window_height/ (float)window_width;
    znear = 0.05;
    zfar = 5000;
    proj_matrix = mat4_make_perspective(fov, aspect_ratio, znear, zfar);

    // Loads the cube values in the mesh data structure
    //load_cube_mesh_data();
    // Loads the obj file data to mesh data
    load_obj_file_data("./././assets/f22.obj");
}

///////////////////////////////////////////////////////////////////////////////
// Poll system events and handle keyboard input
///////////////////////////////////////////////////////////////////////////////
void process_events(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_running = false;
            }
            if (event.key.keysym.sym == SDLK_F11)
            {
                toggle_fullscreen();
            }
            if (event.key.keysym.sym == SDLK_F1)
            {
                toggle_projection();
            }
            if (event.key.keysym.sym == SDLK_F2)
            {
                toggle_backface_culling();
            }
            if (event.key.keysym.sym == SDLK_F3)
            {
                cycle_render_method();
            }
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function frame by frame with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Wait some time until the reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // Only delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    previous_frame_time = SDL_GetTicks();

    // Initialize the array of triangles to render
    triangles_to_render = NULL;

    //mesh.rotation.x += 0.001;
    //mesh.rotation.y += 0.01;
    //mesh.rotation.z += 0.01;

    //mesh.scale.x += 0.001;
    //mesh.scale.y += 0.001;
    //mesh.scale.z += 0.001;

    //mesh.translation.x += 0.005;
    mesh.translation.z = 5.0;

    // Scale matrix
    mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    // Translation matrix
    mat4_t translate_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    // Rotation matrices
    mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
    mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
    mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);

    // Loop all triangle faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++) {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vec4_t transformed_vertices[3];

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++) {
            vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

            // Create a World matrix combining scale, rotation and translation matrices
            // First scale then rotate then translate
            mat4_t world_matrix = mat4_identity();
            world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
            world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
            world_matrix = mat4_mul_mat4(translate_matrix, world_matrix);

            // Transform vertex by world matrix
            transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

            transformed_vertices[j] = transformed_vertex;
        }
        
        
        // Backface culling
        vec3_t vector_a = vec3_from_vec4(transformed_vertices[0]); /*   A   */
        vec3_t vector_b = vec3_from_vec4(transformed_vertices[1]); /*  / \  */
        vec3_t vector_c = vec3_from_vec4(transformed_vertices[2]); /* C---B */

        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);
        vec3_normalize(&vector_ab);
        vec3_normalize(&vector_ac);

        // Compute face normal for ABC
        vec3_t normal = vec3_cross(vector_ab, vector_ac); // Left-Handed Co-ordinate System
        vec3_normalize(&normal);
        // Compute camera ray
        vec3_t camera_ray = vec3_sub(camera_position, vector_a);
        // Compute dot product between normal and camera ray
        float dot = vec3_dot(normal, camera_ray);
        // If dot product is < 0 the face is pointing away from us
        // Bypass adding it to triangles to render
        if (culling_type == CULL_BACKFACE)
        {
            if (dot < 0)
            {
                continue;
            }
        }
        
        vec4_t projected_points[3];

        // Projection
        for(int j = 0; j < 3; j++){
            // Project the current vertex
            projected_points[j] = mat4_mul_vec4_project(proj_matrix, transformed_vertices[j]);

            // Scale projected points
            projected_points[j].x *= (float)window_width / 2.0;
            projected_points[j].y *= (float)window_height / 2.0;

            // Invert y values to account for flipped screen y co-ordinates
            projected_points[j].y *= -1;

            // Translate the projected points to the middle of the screen
            projected_points[j].x += (window_width / 2);
            projected_points[j].y += (window_height / 2);
        }

        // Calculate average depth for each face after projection
        float avg_depth = (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0;

        // Normalize light direction
        vec3_t light_direction = global_light.direction;
        vec3_normalize(&light_direction);

        // Calculate the light shading intensity depending on the angle between the the light vector and face normal vector and then invert it
        float light_intensity_factor = -vec3_dot(normal, light_direction);

        // Calculate the triangle face color depending on the light shading intensity
        uint32_t triangle_color = light_apply_intensity(mesh_face.color, light_intensity_factor);

        triangle_t projected_triangle = {
            .points = {
                { projected_points[0].x, projected_points[0].y},
                { projected_points[1].x, projected_points[1].y},
                { projected_points[2].x, projected_points[2].y},
            },
            .color = triangle_color,
            .avg_depth = avg_depth
        };

        // Save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }

    if (triangles_to_render != NULL)
    {
        // A naive approach using painter's algorithm to sort triangles by their avg_depth
        int num_triangles = array_length(triangles_to_render);
        for (int i = 0; i < num_triangles; i++) {
            for (int j = i; j < num_triangles; j++) {
                if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
                    // Swap triangles indexes
                    triangle_t temp = triangles_to_render[i];
                    triangles_to_render[i] = triangles_to_render[j];
                    triangles_to_render[j] = temp;
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw objects on the display
///////////////////////////////////////////////////////////////////////////////
void render(void) {
    //draw_grid();

    // Loop all projected triangles and render them
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];

        if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE) {
            //Draw filled triangle (fill faces)
            draw_filled_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                triangle.color
            );
        }

        if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE) {
            // Draw unfilled triangle (fill face edges)
            draw_triangle(
                triangle.points[0].x, triangle.points[0].y, // vertex A
                triangle.points[1].x, triangle.points[1].y, // vertex B
                triangle.points[2].x, triangle.points[2].y, // vertex C
                0xFF00FF00
            );
        }

        if (render_method == RENDER_WIRE_VERTEX) {
            // Draw vertex points (fill vertices)
            draw_rect(triangle.points[0].x, triangle.points[0].y, 4, 4, 0xFFFF0000); // vertex A
            draw_rect(triangle.points[1].x, triangle.points[1].y, 4, 4, 0xFFFF0000); // vertex B
            draw_rect(triangle.points[2].x, triangle.points[2].y, 4, 4, 0xFFFF0000); // vertex C
        }
    }

    // Clear the array of triangles to render every frame loop
    array_free(triangles_to_render);

    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Free the memory that was dynamically allocated by the program
///////////////////////////////////////////////////////////////////////////////
void free_resources(void) {
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(void) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_events();
        update();
        render();
    }

    destroy_window();
    free_resources();

    return 0;
}
