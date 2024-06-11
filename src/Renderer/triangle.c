#include "triangle.h"
#include "display.h"
#include "utility.h"


//              (x0,y0)
//                / \
//               /   \
//              /     \
//             /       \
//            /         \
//    (x1, y1)-----------(Mx, My)
//           \            \
//             \           \
//               \          \
//                 \         \
//                   \        \
//                     \       \
//                       \      \
//                         \     \
//                           \    \
//                             \   \
//                               \  \
//                                 \ \
//                                   \\
//                                     \ 
//                                  (x2, y2)
//

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Sort vertices by y co-ordinate (y0 < y1 < y2)
    if (y0 > y1)
    {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }
    if (y1 > y2)
    {
        int_swap(&y1, &y2);
        int_swap(&x1, &x2);
    }
    if (y0 > y1)
    {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }

    // Calculate vertex (Mx, My) using triangle similarity
    int My = y1;
    int Mx = x0 + ((float)(x2 - x0) * (y1 - y0) / (float)(y2 - y0));

    // Draw flat bottom triangle (x0, y0), (x1, y1), (Mx, My)
    fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

    // Draw flat top triangle
    fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);

}

void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Calculate inverted slope for (x0,y0) , (x1,y1)
    float inv_slope1 = (float)(x1 - x0)/(y1 - y0);
    // Calculate inverted slope for (x0,y0) , (x2,y2)
    float inv_slope2 = (float)(x2 - x0) / (y2 - y0);

    // Top vertex start and end in x co-ordinate
    float x_start = x0;
    float x_end = x0;

    // Loop all scanlines from y0 to y2(top to bottom)
    for (int y = y0; y <= y2; y++)
    {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope1;
        x_end += inv_slope2;
    }
}

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Calculate inverted slope for (x2,y2) , (x0,y0)
    float inv_slope1 = (float)(x2 - x0) / (y2 - y0);
    // Calculate inverted slope for (x2,y2) , (x1,y1)
    float inv_slope2 = (float)(x2 - x1) / (y2 - y1);

    // Bottom vertex start and end in x co-ordinate
    float x_start = x2;
    float x_end = x2;

    // Loop all scanlines from y2 to y0 or y1(bottom to top)
    for (int y = y2; y >= y0; y--)
    {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope1;
        x_end -= inv_slope2;
    }
}
