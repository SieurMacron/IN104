#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Carte.h"
#include "gui.h"


int main (int argc, char * argv[])
{
	// Le code prend en entrée un fichier txt qui encode la position des murs et des tuiles
	if (argc > 1)
	{	//On initialise les variables verifiant si le jeu se termine 
		int jeu_termine;
		int joueur_gagnant;

		jeu_termine =0; 	// PErmettra de verifier si la partie est finie : si 1 vrai sinon faux
		joueur_gagnant = 0;	//Indiquera le numero du joueur gagnant


		//On crée le plateau de jeu sur lequel les joueurs vont évoluer
		
		Carte_t * Carte = (Carte_t *) malloc (sizeof (Carte_t));
	
		// On initialise la Carte
		chargement_Carte (argv[1], Carte);
		// On affiche la Carte via SDL
		affichage (Carte->w, Carte->h);
		// Chargement des images du jeu.
		chargement_im ();
	
		// Boucle while qui décrit le deroulement du jeu :
		while (!jeu_termine)
		{
			// Execution des differents evenements
			getEvent (Carte, &jeu_termine);
			// Mise à jour des explosions.
			majexplosion (Carte);
			// Mise à jour des bombes.
			majbombe (Carte);
			// Mise à jour de la position ds joueurs
			majjoueur (Carte, 1);
			// On ralentit un peu le jeu.
			//SDL_Delay (175);
			// Mise à jour des cases.
			affichage_carte (Carte);



			// Verification de si la partie est finie :
			updateOutput (&joueur_gagnant);
		}
	
		// On libère la mémoire en détruisant la Carte : 
		destruction_Carte (Carte);
	}
	else

		// Si le plateau de jeu n'est pas renseigné, on affiche un message d'erreur 
		printf ("ERREUR : PLATEAU DE JEU NON RENSEIGNE \n");

	return 0;
}