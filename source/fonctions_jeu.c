/*Fonctions du jeu*/
#include "fonctions_jeu.h"

void deplacer_joueur(Carte* carte, tuile* tuile_courante,joueur* mon_joueur,deplacement mon_joueur->dep){
    switch (mon_joueur->dep){
        case HAUT:
            tuile_courante->y--; // l'axe des y commence en haut à gauche de l'écran
            switch((carte->grille[tuile_courante->x][tuile_courante->y]).type){
                case VIDE:
                    break;
                case EXPLOSION:
                    mon_joueur->vivant = 0; //peut-etre à modifier si la puissance de l'explosion est variable
                    break;
                default:
                    tuile_courante->y++;
                    break;
            }
            break;
        case BAS:
            tuile_courante->y++;
            switch((carte->grille[tuile_courante->x][tuile_courante->y]).type){
                case VIDE:
                    break;
                case EXPLOSION:
                    mon_joueur->vivant = 0;
                    break;
                default:
                    tuile_courante->y--;
                    break;
            }
            break;
        case GAUCHE:
            tuile_courante->x--;
            switch((carte->grille[tuile_courante->x][tuile_courante->y]).type){
                case VIDE:
                    break;
                case EXPLOSION:
                    mon_joueur->vivant = 0;
                    break;
                default:
                    tuile_courante->x++;
                    break;
            }
            break;
        case DROITE:
            tuile_courante->x++; 
            switch((carte->grille[tuile_courante->x][tuile_courante->y]).type){
                case VIDE:
                    break;
                case EXPLOSION:
                    mon_joueur->vivant = 0;
                    break;
                default:
                    tuile_courante->x--;
                    break;
            }
            break;

    }
}

void poser_bombe (Carte* carte, tuile* tuile_courante,joueur* mon_joueur)
{
    if(instant_pose_bombe-clock()<temps_recharge){
        switch((carte->grille[tuile_courante->x][tuile_courante->y]).type){
            case VIDE:
                
        }

    }
}