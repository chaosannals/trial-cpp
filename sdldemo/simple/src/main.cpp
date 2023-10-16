#include <SDL.h>

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    window = SDL_CreateWindow(
        "simple demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 64, 255, 128, 16);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(4000);
    SDL_Quit();

    return 0;
}
