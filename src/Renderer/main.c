#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t triangles_to_render[N_MESH_FACES];

vec3_t camera_position = { .x = 0, .y = 0, .z = -5 };
vec3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 100;

bool is_running = false;
int previous_frame_time = 0;

void setup(void) {
    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            if (event.key.keysym.sym == SDLK_F11)
            {
                toggle_fullscreen();
            }
            if (event.key.keysym.sym == SDLK_F1)
            {
                toggle_projection();
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Function that receives a 3D vector and returns a projected 2D point
////////////////////////////////////////////////////////////////////////////////
vec2_t project(vec3_t point, enum projection_type projection_mode) {

    vec2_t projected_point;

    switch (projection_mode)
    {
    case 0:
        projected_point.x = (fov_factor * point.x);
        projected_point.y = (fov_factor * point.y);
        break;
    case 1:
        projected_point.x = (fov_factor * point.x) / point.z;
        projected_point.y = (fov_factor * point.y) / point.z;
        break;
    default:
        projected_point.x = (fov_factor * point.x) / point.z;
        projected_point.y = (fov_factor * point.y) / point.z;
        break;
    }

    
    return projected_point;
}

void update(void) {
    // Wait some time until the reach the target frame time in milliseconds
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // Only delay execution if we are running too fast
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    // Loop triangle faces
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face_t current_mesh_face = mesh_faces[i];

        vec3_t face_vertices[3] = {
            mesh_vertices[current_mesh_face.a - 1],
            mesh_vertices[current_mesh_face.b - 1],
            mesh_vertices[current_mesh_face.c - 1]
        };

        triangle_t projected_triangle;

        // Loop face vertices
        for (int j = 0; j < 3; j++)
        {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

            // Translate away from camera
            transformed_vertex.z -= camera_position.z;

            // Project the current vertex to vec2_t for screen space
            vec2_t projected_point = project(transformed_vertex, projection_mode);

            //Scale and translate to middle of screen
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }
        triangles_to_render[i] = projected_triangle;
    }
}

void render(void) {
    draw_grid();

    // Loop all projected triangles and render them
    for (int i = 0; i < N_MESH_FACES; i++) {
        triangle_t current_triangle = triangles_to_render[i];
        
        // draw vertices
        draw_rect(current_triangle.points[0].x, current_triangle.points[0].y, 3, 3, 0xFFFFFF00);
        draw_rect(current_triangle.points[1].x, current_triangle.points[1].y, 3, 3, 0xFFFFFF00);
        draw_rect(current_triangle.points[2].x, current_triangle.points[2].y, 3, 3, 0xFFFFFF00);

        // draw edge lines
        draw_triangle(
            current_triangle.points[0].x, current_triangle.points[0].y,
            current_triangle.points[1].x, current_triangle.points[1].y,
            current_triangle.points[2].x, current_triangle.points[2].y, 
            0xFF00FF00);
    }



    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
