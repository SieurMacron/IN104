/*Fenetre de jeu*/
pwindow= SDL_CreateWindow('Fenetre_jeu', SDL_WINDOWPOS_CENTERED /*coordonnées centrées*/, SDL_WINDOWPOS_CENTERED, 640/*largeur*/, 680/*hauteur*/, SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN);
if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
prenderer=SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

SDL_DestroyWindow(pWindow);  
SDL_DestroyRenderer(prenderer);