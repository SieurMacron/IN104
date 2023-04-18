/* Solal Marzouk & Clément Nedonsel*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "source/Entite_du_jeu.h"



int main(int argc, char *argv[])
{
/*initialisation de SDL*/
    if(0 != SDL_Init(SDL_EVERYTHING)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;

/*boucle principale*/
    SDL_Event events;  
    bool isOpen{ true };
    /*Fenetre de jeu*/
        pwindow= SDL_CreateWindow('Fenetre_jeu', SDL_WINDOWPOS_CENTERED /*coordonnées centrées*/, SDL_WINDOWPOS_CENTERED, 640/*largeur*/, 680/*hauteur*/, SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN);
        if(NULL == window)
        {
            fprintf(stderr, "Erreur lors de la création de la fenetre : %s", SDL_GetError());
            return EXIT_FAILURE;
        }
        prenderer=SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);
        SDL_DestroyWindow(pWindow);  
        SDL_DestroyRenderer(prenderer);
    while (isOpen){ /*tant que isOpen reste à true le jeu reste ouvert*/
        while (SDL_PollEvent(&events)){/*on code ici les conditions sous lesquelles le jeu se ferme*/
            switch (events.type){
                case SDL_QUIT:isOpen = false;
                    break;
                }
        }
    }


    return 0;
}
