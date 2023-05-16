// evenement courant à traiter(clic souris, entrée clavier, evenement fenetre)
void getEvent (Carte_t * Carte, int * finished);
// Ouvre une fenetre SDL.
void initWindow (int w, int h);
// Charge les differentes images du jeu
void chargement_im ();
// Affiche la carte du jeu.
void affichage_carte (Carte_t * Carte);