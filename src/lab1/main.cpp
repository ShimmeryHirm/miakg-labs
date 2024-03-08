#include "draw.h"
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <ctime>
#include <iostream>

bool init();

void close();

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *loadedSurface = nullptr;


bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            if (renderer == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }


    float a = 100;
    float l = 50;

    int rotate = 0;
    float shift_x = SCREEN_WIDTH / 2;
    float shift_y = SCREEN_HEIGHT / 2;
    float scale = 1;
    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
            if (SDL_QUIT == e.type) {
                quit = true;
            }
            if (SDL_KEYDOWN == e.type) {
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                        break;

                    case SDL_SCANCODE_W:
                        shift_y -= 10;
                        break;
                    case SDL_SCANCODE_A:
                        shift_x -= 10;
                        break;
                    case SDL_SCANCODE_S:
                        shift_y += 10;
                        break;
                    case SDL_SCANCODE_D:
                        shift_x += 10;
                        break;

                    case SDL_SCANCODE_Z:
                        if (scale > 0.1) scale -= 0.1;
                        break;
                    case SDL_SCANCODE_X:
                        scale += 0.1;
                        break;
                    case SDL_SCANCODE_C:
                        scale *= -1;
                        break;

                    case SDL_SCANCODE_Q:
                        rotate += 10;
                        break;
                    case SDL_SCANCODE_E:
                        rotate -= 10;
                        break;

                    case SDL_SCANCODE_R:
                        rotate = 0;
                        shift_x = SCREEN_WIDTH / 2;
                        shift_y = SCREEN_HEIGHT / 2;
                        scale = 1;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        draw_limacon(renderer, a, l, rotate * M_PI / 180.0, shift_x, shift_y, scale);

        SDL_RenderPresent(renderer);
    }


    close();
    return 0;
}