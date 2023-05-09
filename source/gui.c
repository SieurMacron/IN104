/* Solal Marzouk & Clément Nedonsel*/

#include "gui.h"


void visu()
{
/*initialisation de SDL*/
    if(0 != SDL_Init(SDL_INIT_EVERYTHING)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Quit();
    return EXIT_SUCCESS;


    SDL_Event events;  // evenement courant à traiter(clic souris, entrée clavier, evenement fenetre)
    bool isOpen{true };

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
        // cette fonction crée une texture à partir d'une surface. Texture= image stockée dans la mémoire graphique, plus rapide à afficher qu'une surface.

        SDL_RenderClear(renderer); //efface l'ecran
        SDL_RenderCopy(renderer, texture_ecran, NULL, NULL); //affiche la texture
        SDL_RenderPresent(renderer); // met à jour l'affichage

/*initialisation des sprites*/
    struct Entite feur1={0,0,60, JOUEUR,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom mon_joueur de profil droit*/))};
    struct Entite feur2={600,600,60, JOUEUR,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom adversaire*/))};
    struct joueur mon_joueur= {feur1,20,/*vitesse*/,5.0,1,NULL }; 
    struct joueur adversaire= {feur2,20,/*vitesse*/,5.0,1,NULL };
    SDL_Rect dstrect_mon_joueur = { feur1->x,feur1->y ,/*largeur de l'image*/, /*hauteur de l'image*/ };
    SDL_Rect dstrect_adversaire = { /*x de départ*/,/*y de départ*/ ,/*largeur de l'image*/, /*hauteur de l'image*/ };
    //Remarque: comment stocker les bonus du joueur? Besoin d'une puissance alors que la bombe en a déjà une?

    struct Entite feur3={/*x*/,/*y*/,10000, MURDUR,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom murdur*/))};
    struct Entite feur4={/*x*/,/*y*/,20, MURMOU,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom murmou*/))};
    struct mur murdur= {feur3,/*butin*/}; 
    struct mur murmou= {feur4,/*butin*/};

    struct Entite feur5={/*x*/,/*y*/,10000, BOMBE,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom bombe*/))};
    struct bombe bombe= {feur5,3.0,20};

    struct Entite feur6={/*x*/,/*y*/,10000, EXPLOSION,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom explosion*/))};
    struct explosion explosion= {feur6, 1.0};
    //Remarque: il faut rajouter la portée de l'explosion.

    struct Entite feur7={/*x*/,/*y*/,10000, BONUS,SDL_CreateTextureFromSurface(renderer, IMG_Load(/*nom bonus*/))};
    struct bonus bonus= {feur7,/*type de bonus*/};
    //Remarque: type de bonus et sprite correspondant définis aléatoirement à l'apparition du bonus?

    

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
                            feur5->x=feur1->x;
                            feur5->y=feur1->y;
                            SDL_Rect dstrect_bombe = { feur5->x,feur5->y ,/*largeur de l'image*/, /*hauteur de l'image*/ };
                            SDL_RenderCopy(renderer,feur5->texture, NULL, &dstrect_bombe);
                            SDL_DestroyTexture(feur5->texture); //à sortir du switch peut-être
                            break;
                        case SDL_SCANCODE_UP : /*si fleche du haut est pressée*/
                            /*déplacer le sprite vers le haut*/
                            feur1->texture=SDL_CreateTextureFromSurface(renderer, IMG_Load(/*mon_joueur de dos*/));
                            for (int i=0, i</*largeur d'une tuile*/,i++)
                            {
                                feur1->y--;
                                SDL_RenderCopy(renderer, feur1->texture, NULL, &dstrect_mon_joueur);
                                /*prendre en compte la vitesse de déplacement en laissant un délai entre chaque itération*/
                                SDL_DestroyTexture(feur1->texture);
                            }
                            break;
                        case SDL_SCANCODE_DOWN: /*si flehce du bas est pressée*/
                            /*déplacer le sprite vers le bas*/
                            feur1->texture=SDL_CreateTextureFromSurface(renderer, IMG_Load(/*mon_joueur de face*/));
                            for (int i=0, i</*largeur d'une tuile*/,i++)
                            {
                                feur1->y++;
                                SDL_RenderCopy(renderer, feur1->texture, NULL, &dstrect_mon_joueur);
                                /*prendre en compte la vitesse de déplacement en laissant un délai entre chaque itération*/
                                SDL_DestroyTexture(feur1->texture);
                            }
                            break;
                        case SDL_SCANCODE_LEFT: /*si fleche de gauche est pressée*/
                            /*déplacer le sprite vers la gauche*/
                            feur1->texture=SDL_CreateTextureFromSurface(renderer, IMG_Load(/*mon_joueur de profil gauche*/));
                            for (int i=0, i</*largeur d'une tuile*/,i++)
                            {
                                feur1->x--;
                                SDL_RenderCopy(renderer, feur1->texture, NULL, &dstrect_mon_joueur);
                                /*prendre en compte la vitesse de déplacement en laissant un délai entre chaque itération*/
                                SDL_DestroyTexture(feur1->texture);
                            }
                            break;
                        case SDL_SCANCODE_RIGHT: /*si fleche de droite est pressée*/
                            /*déplacer le sprite vers la droite*/
                            feur1->texture=SDL_CreateTextureFromSurface(renderer, IMG_Load(/*mon_joueur de profil droit*/));
                            for (int i=0, i</*largeur d'une tuile*/,i++)
                            {
                                feur1->x++;
                                SDL_RenderCopy(renderer, feur1->texture, NULL, &dstrect_mon_joueur);
                                /*prendre en compte la vitesse de déplacement en laissant un délai entre chaque itération*/
                                SDL_DestroyTexture(feur1->texture);
                            }
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

        //mettre en pause
        sleep(0.33);
    }


    SDL_DestroyTexture(texture_ecran);
    SDL_FreeSurface(ecran);
    SDL_DestroyWindow(Window);  
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
