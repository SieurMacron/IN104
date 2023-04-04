// Solal Marzouk & Clément Nedonsel//
#include <SDL2/SDL.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(0 != SDL_Init(SDL_EVERYTHING))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;

    return 0;
}
