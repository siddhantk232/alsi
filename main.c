#include <stdbool.h>
#include <stdio.h>

#include "SDL2/SDL.h"

int const WIDTH = 1280;
int const HEIGHT = 720;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window =
        SDL_CreateWindow("ALSI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (window == NULL) {
        printf("[ERROR]: failed to initialize window : %s\n", SDL_GetError());
        return 1;
    }
    if (renderer == NULL) {
        printf("[ERROR]: failed to initialize window : %s\n", SDL_GetError());
        return 1;
    }

    bool is_running = true;

    int arr[] = {100, 200, 150, 250, 300, 280, 370, 280, 650, 480, 390};
    size_t size = sizeof(arr) / sizeof(int);

    const int bar_width = (WIDTH - (size * 2)) / size;

    size_t i = 0;
    size_t j = 0;

    while (is_running) {
        SDL_Event event;
        int x = 0;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    printf("[INFO]: exiting game...\n");
                    is_running = false;
                } break;
                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);
        bool swap = false;
        if (i < size) {
            if (j < size - i - 1) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;

                    swap = true;
                }
            }
        }

        for (size_t k = 0; k < size; ++k) {
            SDL_Rect rect = {
                .h = arr[k],
                .w = bar_width,
                .x = x,
                .y = HEIGHT - arr[k],
            };

            if (j == k) {
                SDL_SetRenderDrawColor(renderer, 200, 155, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 155, 0, 255);
            }

            if (swap && j + 1 == k) {
                SDL_SetRenderDrawColor(renderer, 50, 155, 0, 255);
            }

            SDL_RenderFillRect(renderer, &rect);
            x += bar_width;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect sep = {
                .h = HEIGHT,
                .w = 2,
                .x = x,
                .y = 0,
            };

            SDL_RenderFillRect(renderer, &sep);
            x += 2;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        j++;

        if (j == size - 1) {
            i++;
            j = 0;
        }

        // TODO: show a finish message (text rendering)
        if (i == size - 1) break;

        SDL_Delay(300);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
