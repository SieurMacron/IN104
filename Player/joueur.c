#include "joueur.h"



void updatePlayer(Entity* player, Carte* carte) {
    // Récupération de la position actuelle du joueur
    int x = player->x;
    int y = player->y;

    // Déplacement du joueur en fonction de sa direction
    switch (player->dep) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }

    // Vérification que le joueur ne sort pas de la carte
    if (x < 0 || x >= carte->largeur || y < 0 || y >= carte->hauteur) {
        return;
    }

    // Vérification que le joueur ne rencontre pas un mur
    if (carte->tuile[y][x].type == MURDUR || carte->tuile[y][x].type == MURMOU || carte->tuile[y][x].type == BOMBE ) {
        return;
    }

    // Vérification si le joueur rencontre une explosion
    if (carte->tuile[y][x].type == EXPLOSION) {
        // Le joueur est mort
        player->alive = false;
        return;
    }

    // Mise à jour de la position du joueur
    player->x = x;
    player->y = y;
}