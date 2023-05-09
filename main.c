/* Solal Marzouk & Clément Nedonsel*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "source/gui.h"
//#include <SDL_image.h> /*permet d'afficher des images au format png, pdf...*/
#include "source/Entites_du_jeu.h"
#include "source/fonctions_jeu.h"



int main(int argc, char *argv[])
{

/* Initialisation de la carte et du (des) joueurs.e.s */
Carte* carte;

tuile* tuile_courante;

joueur* mon_joueur;

/*initialisation de SDL*/
    if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;


    SDL_Event events;  // evenement courant à traiter(clic souris, entrée clavier, evenement fenetre)
    bool isOpen = true ;

/*boucle principale*/

    while (isOpen){ /*tant que isOpen reste à true le jeu reste ouvert*/
        while (SDL_PollEvent(&events)){/*on code ici les conditions sous lesquelles le jeu évolue(=les règles)*/
        /*SDL_PollEvent prend l'evenenement le plus ancien de la file des evenements et le stocke dans la structure events pour qu'il soit traité*/
            switch (events.type){ /*switch compare son argument avec tous les "case" et exécute le case correspondant*/
                case SDL_QUIT: /*si l'utilisateur quitte le jeu*/
                    isOpen = false; /*la page se ferme*/
                    break;

                case SDL_KEYDOWN: /*si l'utilisateur presse une touche*/
                    switch(events.key.keysym.sym){ /*différentes touches possibles*/
                        case SDLK_SPACE: /*si espace est pressée*/
                            /*on pose une bombe*/
                            clock_t instant_pose_bombe = clock(); // on stocke l'instant où a été posé la dernière bombe
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
       
    }
    // Mise à jour des entités
        mise_a_jour(carte->entities, carte->num_entities, carte);

        // Affichage du plateau de jeu et des entités
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawMap(renderer, carte);
        drawEntities(renderer, carte->entities, carte->num_entities);
        SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture_ecran);
    SDL_FreeSurface(ecran);
    SDL_DestroyWindow(window);  
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;



}
