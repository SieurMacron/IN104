// Solal Marzouk & Clément Nedonsel//
#include <SDL2/SDL.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(0 != SDL_Init(SDL_EVERYTHING)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;

    return 0;
}
