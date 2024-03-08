#pragma once
#include <SDL.h>
#include <cassert>


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
void draw_limacon(SDL_Renderer *renderer, float a, float l, float rotate, float shift_x, float shift_y, float scale);
