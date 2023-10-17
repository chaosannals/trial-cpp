#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    window = SDL_CreateWindow(
        "simple demo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* image = IMG_Load("img-1.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Event event;
    bool able = true;
    while (able) {
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            able = false;
            break;
        }

        SDL_SetRenderDrawColor(renderer, 64, 255, 128, 16);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    //SDL_Delay(4000);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
