//decomposition du jeu ///

-Partie graphique

--Partie Client (GUI)

--Partie serveur ( coeur du jeu)

--Coeur du jeu
Carte : matrice 
Joueur =structure (puissance des bombes, pv, etc)



// Structure du code ///
 • Initialisation de Sdl2
 • Création d une fenêtre de jeu ( initialisation avec SDL2)

 • Charger les sprites ( les trouver avant)

 • Créer les structures nécessaire au jeu (notamment une structure globale qui décrira toutes les entités via leurs coordonnées).
Les structure seront : La structure entité, joueur, ennemis, bombe, explosion, bonus, et carte.
 
 
 • Creer les fonctions pour l exécution du jeu :
-Initialiser sdl
-charger les textures
-charger la carte
-dessiner la carte
-Dessiner les entités (bomb, joueur, mur etc)
-Fonction pour actualiser les informations du joueur
-placer une bombe
-Actualiser la bombe
-fonction explosion
-(optionnel mais important je pense) Nettoyage des fichiers (destruction des images chargées par SDL2)