/* Solal Marzouk & Clément Nedonsel*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h> /*permet d'afficher des images au format png, pdf...*/
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


    SDL_Event events;  // evenement courant à traiter(clic souris, entrée clavier, evenement fenetre)
    bool isOpen{ true };

    /*Fenetre de jeu*/

        SDL_Window * window= SDL_CreateWindow('Fenetre_jeu', SDL_WINDOWPOS_CENTERED /*coordonnées centrées*/, SDL_WINDOWPOS_CENTERED, 640/*largeur*/, 680/*hauteur*/, SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN);
        if(NULL == window)
        {
            fprintf(stderr, "Erreur lors de la création de la fenetre : %s", SDL_GetError());
            return EXIT_FAILURE;
        }
        SDL_Renderer* renderer=SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

        SDL_Surface * ecran= NULL; //on crée notre image ecran
       
        SDL_WM SetIcon (IMG_Load(/*"nom de l'icone bomberman"*/)); //affiche l'icone du jeu
        SDL_WM_SetCaption(/*"nom de notre jeu"*/,NULL); // affiche le nom du jeu

        ecran = IMG_Load(/*"nom de notre ecran"*/); //on charge notre image d'ecran dans le pointeur vers l'ecran
        SDL_Texture * texture_ecran = SDL_CreateTextureFromSurface(renderer, ecran);

        SDL_RenderClear(renderer); //efface l'ecran
        SDL_RenderCopy(renderer, texture_ecran, NULL, NULL); //affiche la texture
        SDL_RenderPresent(renderer); // met à jour l'affichage

       

/*boucle principale*/

    while (isOpen){ /*tant que isOpen reste à true le jeu reste ouvert*/
        while (SDL_PollEvent(&events)){/*on code ici les conditions sous lesquelles le jeu évolue(=les règles)*/
        /*SDL_PollEvent prend l'evenenement le plus ancien de la file des evenements et le stocke dans la structure events pour qu'il soit traité*/
            switch (events.type){ /*switch compare son argument avec tous les "case" et exécute le case correspondant*/
                case SDL_QUIT: /*si l'utilisateur quitte le jeu*/
                    isOpen = false; /*la page se ferme*/
                    break;

                case SDL_KEYDOWN: /*si l'utilisateur presse une touche*/
                    switch(event.key.keysym.sym){ /*différentes touches possibles*/
                        case SDLK_SPACE: /*si espace est pressée*/
                            /*on pose une bombe*/
                            break;
                        case SDL_SCANCODE_UP : /*si fleche du haut est pressée*/
                            deplacer_joueur(carte, tuile_courante,mon_joueur, HAUT);
                            break;
                        case SDL_SCANCODE_DOWN: /*si flehce du bas est pressée*/
                            deplacer_joueur(carte, tuile_courante,mon_joueur, BAS);
                            break;
                        case SDL_SCANCODE_LEFT: /*si fleche de gauche est pressée*/
                            deplacer_joueur(carte, tuile_courante,mon_joueur, GAUCHE);
                            break;
                        case SDL_SCANCODE_RIGHT: /*si fleche de droite est pressée*/
                            deplacer_joueur(carte, tuile_courante,mon_joueur, DROITE);
                            break;
                         default: /*si toute autre touche est pressée*/
                            /*on ne fait rien*/
                            break;
                    }
                    default: /*si toute autre action est réalisée*/
                        /*on ne fait rien*/
                        break;
            }
        }
        /*on rafraichit l'image à chaque tour de boucle*/
        SDL_RenderClear(renderer); //efface l'ecran
        SDL_RenderCopy(renderer, texture_ecran, NULL, NULL); //affiche la texture
        SDL_RenderPresent(renderer); // met à jour l'affichage
    }


    SDL_DestroyTexture(texture_ecran);
    SDL_FreeSurface(ecran);
    SDL_DestroyWindow(Window);  
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
