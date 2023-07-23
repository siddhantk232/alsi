#include <stdbool.h>
#include <stdio.h>

#include "SDL2/SDL.h"

int const WIDTH = 1280;
int const HEIGHT = 720;

void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {20, -1, 2, 1, 14, 12, 0, 1, 2, -5, 99};
    int size = sizeof(arr) / sizeof(int);

    bubble_sort(arr, size);

    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "ALSI");

    if (window == NULL) {
        printf("[ERROR]: failed to initialize window : %s\n", SDL_GetError());
        return 1;
    }
    if (renderer == NULL) {
        printf("[ERROR]: failed to initialize window : %s\n", SDL_GetError());
        return 1;
    }

    bool is_running = true;

    while (is_running) {
        SDL_Event event;

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
        SDL_Rect rect = {
            .h = 200,
            .w = 200,
            .x = WIDTH / 2 - 100,
            .y = HEIGHT / 2 - 100,
        };
        SDL_SetRenderDrawColor(renderer, 255, 155, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
