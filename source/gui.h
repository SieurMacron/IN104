#ifndef Gui_H
#define Gui_H

#include "Entites_du_jeu.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <SDL_image.h> /*permet d'afficher des images au format png, pdf...*/
#include <time.h>
#include <unistd.h>

void visu();

#endif

// créer la surface de dessin
    drawSurface = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);
    if(drawSurface == NULL)
    {
        printf("Could not create drawing surface! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // obtenir la surface de la fenêtre
    screenSurface = SDL_GetWindowSurface(window);

    // remplir la surface de dessin avec une couleur de fond
    SDL_FillRect(drawSurface, NULL, SDL_MapRGB(drawSurface->format, 255, 255, 255));

    // copier la surface de dessin sur la surface de la fenêtre
    SDL_Rect rect = { 100, 100, 320, 240 };
    SDL_BlitSurface(drawSurface, NULL, screenSurface, &rect);

    // mettre à jour la fenêtre
    SDL_UpdateWindowSurface(window);



    SDL_Surface* screenSurface; // la surface de la fenêtre
    SDL_Surface* drawSurface; // la surface de dessin