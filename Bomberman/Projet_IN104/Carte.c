#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "time.h"

//On verifie que les 2 joueurs sont sur des cases differentes
int verification_autre_joueurs(int numjoueur)
{
	int numero_joueur; // Permet d'identifier les joueurs 
	int resultat;		// Indiquera la valeur de verité (si oui ou non sur la même case)
	resultat = 0 ;

	// La boucle for verifie pour chacun des joueurs s'ils sont sur la même case
	for (numero_joueur = 0; numero_joueur < nombre_joueur; numero_joueur++)
	{
		if (numero_joueur != numjoueur && joueurCourant[numero_joueur].vivant == 1)
		{
			switch (joueurCourant[numjoueur].direction)
			{
				case haut:
					resultat = (joueurCourant[numero_joueur].y == (joueurCourant[numjoueur].y - 1) && joueurCourant[numero_joueur].x == joueurCourant[numjoueur].x) ? resultat + 1 : resultat;
					break;
				case bas:
					resultat = (joueurCourant[numero_joueur].y == (joueurCourant[numjoueur].y + 1) && joueurCourant[numero_joueur].x == joueurCourant[numjoueur].x) ? resultat + 1 : resultat;
					break;
				case gauche:
					resultat = (joueurCourant[numero_joueur].y == joueurCourant[numjoueur].y && joueurCourant[numero_joueur].x == (joueurCourant[numjoueur].x - 1)) ? resultat + 1 : resultat;
					break;
				case droite:
					resultat = (joueurCourant[numero_joueur].y == joueurCourant[numjoueur].y && joueurCourant[numero_joueur].x == (joueurCourant[numjoueur].x + 1)) ? resultat + 1 : resultat;
					break;
				default: ;
			}
		}
	}

	return resultat;
}

// Verifie que le joueur peu marcher sur la case

int verification_case (enum tile_e case_suivante)
{
	if (case_suivante == CASE_VIDE || case_suivante == CASE_BONUS || case_suivante == CASE_EXPLOSION)
		return 0;
	else
		return 1;
}

// Gère l'explosion des bombes (arret en fonction du mur, puissance et portée)
void explosion (Case_t * Case, int numero_case)
{
	int limite_explosion[4] ; // On stockera la limite de l'explosion pour les quatres directions de l'espace
	int puissance_joueur;
	int direction_joueur;
	int numero_joueur; 
	explosion_s explosion[4];
	
	// Initialisation du tableau qui permettra de connaitre les limites de l'explosion.
	limite_explosion[0] = limite_explosion[1] = limite_explosion[2] = limite_explosion[3] = 0;

	// Explosion de la case contenant la bombe.
	Case->t[numero_case].type = CASE_EXPLOSION;
	Case->t[numero_case].chrono = 0;
	
	for (numero_joueur = 0; numero_joueur <= nombre_joueur; numero_joueur++)
	{
		if (conversion (Case, joueurCourant[numero_joueur].x, joueurCourant[numero_joueur].y) == numero_case)
		{
			joueurCourant[numero_joueur].vivant = 0;
		}
	}

	// On adapte la puissance de l'explosion à celle du joueur
	for (puissance_joueur = 1; puissance_joueur <= Case->t[numero_case].power; puissance_joueur++)
	{
	
		explosion[0].test = ((Case->w * puissance_joueur) <= numero_case);
		explosion[1].test = ((numero_case % Case->w) < (Case->w - puissance_joueur));
		explosion[2].test = (numero_case < (Case->w * (Case->h - puissance_joueur)));
		explosion[3].test = (puissance_joueur <= (numero_case % Case->w));
		explosion[0].tile = (numero_case - Case->w * puissance_joueur);
		explosion[1].tile = (numero_case + puissance_joueur);
		explosion[2].tile = (numero_case + Case->w * puissance_joueur);
		explosion[3].tile = (numero_case - puissance_joueur);

		// On regarde toutes les directions pour l'explosion de la bombe ( en fonction du type de cases rencontrée, on limite plus ou moins l'explosion de la bombe)
		for (direction_joueur = 0; direction_joueur < 4; direction_joueur++)
		{
			if (explosion[direction_joueur].test && limite_explosion[direction_joueur] == 0)
			{
				switch (Case->t[explosion[direction_joueur].tile].type)
				{
					case CASE_MURDUR:
						limite_explosion[direction_joueur] = 1;
						break;
					case CASE_BOMBE:
						explosion (Case, explosion[direction_joueur].tile);
						break;
					default:
						Case->t[explosion[direction_joueur].tile].type = CASE_EXPLOSION;
						Case->t[explosion[direction_joueur].tile].chrono = 0;
						
						for (numero_joueur = 0; numero_joueur <= nombre_joueur; numero_joueur++)
						{
							if (conversion (Case, joueurCourant[numero_joueur].x, joueurCourant[numero_joueur].y) == explosion[direction_joueur].tile)
							{
								joueurCourant[numero_joueur].vivant = 0;
							}
						}
						break;
				}
			}
		}
	}
}

// Création de bonus en dessous des mur mou
int bonus (int chanceux)
{
	static int k = 69; // Chiffre qui initialise la fonction random...
	srand ((time (NULL) * k++)); 

	return (rand() % chanceux);
}

// Conversion de la coordonnée en x y du tableau (mandelbrot)
int conversion (Case_t * Case, int x, int y)
{
	return (y * Case->w + x);
}

// Création du plateau de jeu à partir du fichier txt
void chargement_carte (char * nom_fichier, Case_t * Case)
{
	char buffer[1024], nom_fichier2[64];
	int line;
	int row;
	int nbjoueur
	int tempTile
	int chanceux;
	
	sprintf (nom_fichier2, "carte/%s.txt", nom_fichier);
	printf ("%s\n", nom_fichier2);
	// Ouvre le fichier en lecture.
	FILE * file = fopen (nom_fichier2, "r");
	
	if (file == NULL) 
	{
		Case = NULL;
	}

	// On compte le nombre de ligne et on le stocke dans h, et le nombre de colonnes dans w. On obtient ainsi les dimensions de notre plateau de jeu
	fscanf (file, "%d %d %d %d\n", &Case->w, &Case->h, &nombre_joueur, &chanceux);

	// On crée le tableau correspondant au joueur
	joueurCourant = malloc(sizeof(player_t) * nombre_joueur);


	// On crée chacune des cases qui feront à elles toutes le plateau de jeu
	Case->t = (tile_t *) malloc (sizeof (tile_t) * Case->w * Case->h);
	
	// Lit le fichier ligne par ligne et construit les tuiles du plateau.
	for (line = 0, nbPlayer = 0; line < Case->h; line++)
	{
		// Lit une ligne.
		fgets (buffer, 1024, file);

		// Buffer est un tableau de caractère. Pour chaque caractère, construit les tuiles.
		for (row = 0; row < Case->w; row++)
		{
			// Coordonnée linéaire de la case courante.
			tempTile = conversion (Case, row, line);
			// Par défaut.
			Case->t[tempTile].bonus = 0;
			Case->t[tempTile].puissance = 0;
			Case->t[tempTile].chrono = 0;

			switch (buffer[row])
			{
				default:
				case '.':
					Case->t[tempTile].type = CASE_VIDE;
					break;
				case '+':
					Case->t[tempTile].type = CASE_MURMOU;
					// Génération aléatoire des bonus.
					if (bonus ((chanceux > 0 ? chanceux : 3)) == 0) Case->t[tempTile].bonus = 1;
					break;
				case '#':
					Case->t[tempTile].type = CASE_MURDUR;
					break;
				case '$':
					Case->t[tempTile].type = CASE_VIDE;
					
					if (nombre_joueur == 0 || nbPlayer < nombre_joueur)
					{
						joueurCourant[nbPlayer].vivant = 1;				// Si le joueur est vivant.
						joueurCourant[nbPlayer].puissanceBombe = 1; 			// Puissance des bombe par défaut.
						joueurCourant[nbPlayer].direction = STOP; 		// Direction du joueur.
						joueurCourant[nbPlayer].x = row; 					// Affectation des coordonnées.
						joueurCourant[nbPlayer].y = line; 					// Affectation des coordonnées.

						nbjoueur++;
					}
					break;
			}
		}
	}
	
	fclose (file);
}

// Déplacement du joueur.
void deplacement_joueur (Case_t * Case, int numjoueur)
{
 	int case_suivante = case_suivanteType (Case, numjoueur);

	if (verification_case(case_suivante) == 0 && verification_autre_joueurs(numjoueur) == 0)
	{
		if (joueurCourant[numjoueur].direction == haut)
			joueurCourant[numjoueur].y -= 1;
		else if (joueurCourant[numjoueur].direction == droite)
			joueurCourant[numjoueur].x += 1;
		else if (joueurCourant[numjoueur].direction == bas)
			joueurCourant[numjoueur].y += 1;
		else if (joueurCourant[numjoueur].direction == gauche)
			joueurCourant[numjoueur].x -= 1;
		else
			joueurCourant[numjoueur].direction = STOP;
	}
	else
		joueurCourant[numjoueur].direction = STOP;
}

// Retourne le type de la prochaine case du joueur.
int case_suivanteType (Case_t * Case, int numjoueur)
{
 	int localisation = conversion (Case, joueurCourant[numjoueur].x, joueurCourant[numjoueur].y);

	switch (joueurCourant[numjoueur].direction)
	{
		case haut:
			return (joueurCourant[numjoueur].y > 0 ? Case->t[(localisation - Case->w)].type : CASE_MURDUR);
			break;
		case droite:
			return (joueurCourant[numjoueur].x < (Case->w - 1) ? Case->t[(localisation + 1)].type : CASE_MURDUR);
			break;
		case bas:
			return (joueurCourant[numjoueur].y < (Case->h - 1) ? Case->t[(localisation + Case->w)].type : CASE_MURDUR);
			break;
		case gauche:
			return (joueurCourant[numjoueur].x > 0 ? Case->t[(localisation - 1)].type : CASE_MURDUR);
			break;
		default: 
			return CASE_MURDUR;
			break;
	}
}

// Detruit le plateau de jeu.
void destruction_carte (Case_t * Case)
{
	free (Case->t);
	free (Case);
	free (joueurCourant);
}

// Met à jour les bombes.
void majbombe (Case_t * Case)
{
	int numero_tuile; // Variable de boucle (case courante).

	for (numero_tuile = 0; numero_tuile < (Case->w * Case->h); numero_tuile++) // Boucle pour les bombes.
	{
		if (Case->t[numero_tuile].type == CASE_BOMBE)
		{
			if (Case->t[numero_tuile].chrono == 0)
				explosion (Case, numero_tuile);
			else
				Case->t[numero_tuile].chrono -= 1;
		}
	}
}

// Met à jour les les explosions.
void majexplosion (Case_t * Case)
{
	int numero_tuile;

	// Boucle pour les explosions.
	for (numero_tuile = 0; numero_tuile < (Case->w * Case->h); numero_tuile++)
	{
		if (Case->t[numero_tuile].type == CASE_EXPLOSION)
		{
			if (Case->t[numero_tuile].chrono >= 1)
			{
				if (Case->t[numero_tuile].bonus == 1)
				{
					Case->t[numero_tuile].type = CASE_BONUS;
					Case->t[numero_tuile].bonus = 0;
				}
				else
					Case->t[numero_tuile].type = CASE_VIDE;
				
				Case->t[numero_tuile].power = 0;
				Case->t[numero_tuile].chrono = 0;
			}
			else
				Case->t[numero_tuile].chrono += 1;
		}
	}
}

// Permet d'afficher un peu de texte dans la console.
void updateOutput (int * endGame)
{
	if ((*endGame) == 0)
	{
		int numero_joueur, nbPlayervivant , playerWinner;

		for (numero_joueur = 0, nbPlayervivant = 0; numero_joueur < nombre_joueur; numero_joueur++)
		{
			nbPlayervivant += joueurCourant[numero_joueur].vivant;
			playerWinner = numero_joueur;
		}

		if (nbPlayervivant == 1)
		{
			printf ("\n^_^   ^_-   Le joueur %d a gagne la partie !   -_^   ^_^\n\n", playerWinner);
			(*endGame) = 1;
		}
	}
}

// Met à jour la position du joueur.
void majjoueur (Case_t * Case, int pas)
{
	int numero_joueur, tilePlayer; // Variable de boucle (joueur courant), case courante du joueur.

	// Gestion des déplacements des joueurs.
	for (numero_joueur = 0; numero_joueur < nombre_joueur; numero_joueur++)
	{
		if (joueurCourant[numero_joueur].vivant == 1 && joueurCourant[numero_joueur].direction != STOP)
		{	
			movePlayer (Case, numero_joueur);
			
			// Mise à jour de la position du joueur.
			tilePlayer = conversion (Case, joueurCourant[numero_joueur].x, joueurCourant[numero_joueur].y);
		
			if (Case->t[tilePlayer].type == CASE_EXPLOSION) // Permet de tuer un joueur.
			{
				joueurCourant[numero_joueur].vivant = 0;
			}
			else if (Case->t[tilePlayer].type == CASE_BONUS) // permet de ramasser des bonus.
			{
				joueurCourant[numero_joueur].puissanceBombe += 1;
				Case->t[tilePlayer].type = CASE_VIDE;
			}
	
	 		// Permet de faire du pas � pas.
			if (pas == 1) joueurCourant[numero_joueur].direction = STOP;
		}
	}
}