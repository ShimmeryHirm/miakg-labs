#include "draw.h"

void affine(float *x, float *y, float rotate, float shift_x, float shift_y, float scale) {

    *x *= scale;
    *y *= scale;

    float tmp_x = *x;
    *x = tmp_x * cos(rotate) + *y * sin(rotate);
    *y = -tmp_x * sin(rotate) + *y * cos(rotate);

    *x += shift_x;
    *y += shift_y;
}

void draw_limacon(SDL_Renderer *renderer, float a, float l, float rotate, float shift_x, float shift_y, float scale) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (float t = 0; t < 2 * M_PI; t += 0.001) {
        float x = a * cos(t) * cos(t) + l * cos(t);
        float y = a * cos(t) * sin(t) + l * sin(t);

        affine(&x, &y, rotate, shift_x, shift_y, scale);
        SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }

}