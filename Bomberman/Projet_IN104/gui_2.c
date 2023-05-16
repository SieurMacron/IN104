#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Carte.h"
#include "graphics.h"

// On définit la taille d'une image
#define TAILLE 32  // donc 64 pixels carres
// On défnit le chronomètre de la bombe
#define chrono_bombe 5

// Fenetre de jeu.
SDL_Surface * window = NULL; 

// On définit les type des differentes tuiles.
typedef enum  {
	VIDE = 0,
	MURDUR, // mur indestructible
	MURMOU, // mur destructible
	BOMBE, // bombe
	PUISSANCE, // puissance explosion
	EXPLOSION, // explosion
	JOUEUR1, 
	JOUEUR2,
	MAX_NB_TUILES // nombre de tuiles max
}EntityType;

 
SDL_Surface * EntityType[MAX_NB_TUILES]; // On initialise les differentes textures possibles des tuiles.

const char * noms_tuiles[]= {
	NULL, // Pas d'image quand la case est vide.
	"data/MURDUR.bmp", // il s'agit des différents noms des fichiers images utilisés
	"data/MURMOU.bmp",
	"data/BOMBE.bmp",
	"data/puissance.bmp",
	"data/EXPLOSION.bmp",
	"data/player1.bmp",
	"data/player2.bmp",
	"data/player3.bmp",
	"data/player4.bmp"
};


void getEvent (Carte_t * carte, int * finished) // evenement courant à traiter(clic souris, entrée clavier, evenement fenetre)
{
	SDL_Event event;
	int isOpen = 0; // Introduit pour le reseaux.

	
	while (SDL_PollEvent (&event)) /*tant que isOpen reste à 0 le jeu reste ouvert*/
	{/*on code ici les conditions sous lesquelles le jeu évolue(=les règles)*/
		
		if (event.type == SDL_QUIT) /*si l'utilisateur quitte le jeu*/
		{
			(* finished) = 1; /*la page se ferme*/
			break;
		}

		
		if (event.type == SDL_KEYDOWN) /*si l'utilisateur presse une touche*/
		{
 			switch (event.key.keysym.sym) /*différentes touches possibles*/
			{
				
 				case SDLK_ESCAPE: /*si echap est pressée*/
					(* finished) = 1; /*on quitte le jeu*/
					break;
				// Joueur 0.
				case SDLK_SPACE: /*si espace est pressée*/
					if (joueurCourant[isOpen].vivant == 1) /*si le joueur est en vie*/
					{
						Carte->t[joueurCourant[isOpen].y * Carte->w + joueurCourant[isOpen].x].type = CASE_BOMBE;
						Carte->t[joueurCourant[isOpen].y * Carte->w + joueurCourant[isOpen].x].puissance = joueurCourant[isOpen].puissanceBombe;
						Carte->t[joueurCourant[isOpen].y * Carte->w + joueurCourant[isOpen].x].chrono = (joueurCourant[isOpen].puissanceBombe >= chrono_bombe ? joueurCourant[isOpen].puissanceBombe +  2 : chrono_bombe);
						// Le joueur pose sa bombe et celle ci n'explose pas tout de suite
					}
					break;
				case SDLK_LEFT: /*si fleche de gauche est pressée*/
					joueurCourant[isOpen].direction = gauche;
					break;
				case SDLK_RIGHT: /*si fleche de droite est pressée*/
					joueurCourant[isOpen].direction = droite;
					break;
				case SDLK_UP: /*si fleche du haut est pressée*/
					joueurCourant[isOpen].direction = haut;
					break;
				case SDLK_DOWN: /*si fleche du bas est pressée*/
					joueurCourant[isOpen].direction = bas;
					break;
				// Joueur 1.
				/*Le deuxième joueur utilise les touches f,q,z,s,d du clavier */
				case SDLK_f: /*si touche f est pressée*/
					if (joueurCourant[1].vivant == 1) /*si le joueur est vivant*/
					{
						Carte->t[joueurCourant[1].y * Carte->w + joueurCourant[1].x].type = CASE_BOMBE;
						Carte->t[joueurCourant[1].y * Carte->w + joueurCourant[1].x].puissance = joueurCourant[1].puissanceBombe;
						Carte->t[joueurCourant[1].y * Carte->w + joueurCourant[1].x].chrono = (joueurCourant[1].puissanceBombe >= chrono_bombe ? joueurCourant[1].puissanceBombe +  2 : chrono_bombe);
						// Le joueur pose sa bombe et celle ci n'explose pas tout de suite
					}
					break;
				case SDLK_q: /*si touche q est pressée*/
					joueurCourant[1].direction = gauche;
					break;
				case SDLK_d: /*si touche d est pressée*/
					joueurCourant[1].direction = droite;
					break;
				case SDLK_z: /*si touche z est pressée*/
					joueurCourant[1].direction = haut;
					break;
				case SDLK_s: /*si touche s est pressée*/
					joueurCourant[1].direction = bas;
					break;
				default: ;
			}
		}
	}
}

// On ouvre une fenetre SDL.
void initWindow (int w, int h)
{
	if (SDL_Init (SDL_INIT_VIDEO) == -1) /*initialisation de SDL*/
	{
		fprintf (stderr, "error %s\n", SDL_GetError ()); /*si l'initialisation se passe mal, erreur*/
		exit (1);
	}

	atexit (SDL_Quit);
	fprintf (stderr, "Taille du plateau de jeu : %dpx x %dpx.\n", w * TAILLE, h * TAILLE);
	window = SDL_SetVideoMode (w * TAILLE, h * TAILLE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	
	if (window == NULL)
	{
		fprintf (stderr, "error video mode: %s\n", SDL_GetError ());
		exit (1);
	}
	
	SDL_EnableKeyRepeat(25, 25);
}

// On charge les differentes images du jeu...
void chargement_im ()
{
	int i;
	
	for (i = 0; i < MAX_NB_TUILES; i++)
		EntityType[i] = SDL_LoadBMP (noms_tuiles[i]); // on assigne à chaque tuile une texture
}

// On affiche toute la carte de jeu.
void affichage_carte (Carte_t * Carte)
{
	int w, h, numero_joueur;
	SDL_Rect rect; // initialisation du rectangle
	rect.w = TAILLE;
	rect.h = TAILLE;

	// On efface l'ecran en le mettant tout noir.
	SDL_FillRect (window, NULL, SDL_MapRGB (window->format, 0, 0, 0)); /*cette ligne remplit le rectangle de noir*/
	
	for (h = 0; h < Carte->h; h++)
	{/*la double boucle permet de parcourir toute la carte*/
		for (w = 0; w < Carte->w; w++)		
		{
			rect.x = TAILLE * w;
			rect.y = TAILLE * h;

			switch (Carte->t[h * Carte->w + w].type) /*selon le type de la case courante*/
			{
				default:
				case CASE_VIDE:
					SDL_BlitSurface (EntityType[VIDE], NULL, window, &rect);
					break;
				case CASE_MURDUR:
					SDL_BlitSurface (EntityType[MURDUR], NULL, window, &rect);
					break;
				case CASE_MURMOU:
					SDL_BlitSurface (EntityType[MURMOU], NULL, window, &rect);
					break;
				case CASE_BOMBE:
					SDL_BlitSurface (EntityType[BOMBE], NULL, window, &rect);
					break;
				case CASE_EXPLOSION:
					SDL_BlitSurface (EntityType[EXPLOSION], NULL, window, &rect);
					break;
				case CASE_BONUS:
					SDL_BlitSurface (EntityType[PUISSANCE], NULL, window, &rect);
					break;
			}
		}
	}

	// Affichage des joueurs vivants.
	for (numero_joueur = 0; numero_joueur < 2; numero_joueur++)
	{
		rect.x = TAILLE * joueurCourant[numero_joueur].x; 
		rect.y = TAILLE * joueurCourant[numero_joueur].y;
		
		if (joueurCourant[numero_joueur].vivant == 1)
			SDL_BlitSurface(EntityType[JOUEUR1 + numero_joueur], NULL, window, &rect);
	}

	// Met a jour la fenetre.
	SDL_Flip(window);
}