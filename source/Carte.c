#include "Carte.h"




Carte* creation_carte(int largeu_r, int hauteu_r) {
    // Création de la carte
    Carte* carte = malloc(sizeof(Carte));

    // On définit les limites
    carte->largeur = largeu_r;
    carte->hauteur = hauteu_r;

    // Création de la zone de mémoire pour le tableau de tuiles
    carte->tuile** = malloc(sizeof(tuile*) * hauteu_r);
    for (int i = 0; i < hauteu_r; i++) {
        carte->grille[i] = malloc(sizeof(tuile) * largeu_r);
    }

    // On remplit le tableau avec du vide
    for (int i = 0; i < hauteu_r; i++) {
        for (int j = 0; j < largeu_r; j++) {
            EntityType sol = VIDE;
            carte->grille[i][j].type = sol;
        }
    }
    // On délimite le terrain en remplaçant les bords par des murs indestrcutibles

    for (int i = 0; i < hauteu_r; i++) {
        carte->grille[i][0].type = MURDUR;
        carte->grille[i][largeu_r - 1].type = MURDUR;
    }
    for (int j = 0; j < largeu_r; j++) {
        carte->grille[0][j].type = MURDUR;
        carte->grille[hauteu_r - 1][j].type = MURDUR;
    }

 // Creation de mur aléatoire
float Proba_de_mur = 0.3 ;
 //Pourcentage de mur sur la carte





    for (int i = 2; i < largeu_r - 2; i += 2) {
        for (int j = 2; j < hauteu_r - 2; j += 2) {
            if (rand() % 100 < Proba_de_mur) {
                carte->grille[i][j].type = MURDUR;
            }
        }
    }

    

}