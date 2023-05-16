// Définition du type case.
enum tile_e {
	CASE_VIDE = 0, 		// Case vide.
	CASE_MURDUR, 		// Mur indextructible.
	CASE_MURMOU, 		// Mur destructible.
	CASE_BOMB,				// Bombe.
	CASE_BONUS, 			// Bonus.
	CASE_EXPLOSION			// Explosion.
};

// Création du type d'une case du plateau
typedef struct {
	enum tile_e type; 	// Type de case.
	int power;			// Puissance des bombes.
	int timer;			// Compte à rebour des bombes.
	int bonus;			// Détermine si la case est un bonus.
} tile_t;

// Définit le plateau de jeu.
typedef struct {
  int w, h;		// largeur et hauteur du plateau de jeu
  tile_t * t;	// cases du plateau.
} Carte_t;

enum direction_e {
	STOP = 0, 	// Le joueur ne se déplace pas.
	bas,		// Le joueur va vers le bas.
	gauche,		// Le joueur va vers la gauche.
	haut,		// Le joueur va vers le haut.
	droite,		// Le joueur va vers la droite.
	MAX_STOP 	// Le joueur ne se déplace pas.
};

typedef struct {
	int vivant;					// Indique si le joueur est vivant !
	int puissanceBombe; 				// Puissance des bombes.
	enum direction_e direction; // Direction de déplacement.
	int x;						// Position horizontal sur le plateau.
	int y;						// Position vertical sur le plateau.
} player_t;

typedef struct {
	int test;	// Test.
	int tile;	// Case.
} explosion_s;

// Initialisation du tableau de joueur.
player_t * joueurCourant;

// Nombre de joueur;
int nombre_joueur;

// Aucun joueur ne se chevauchent ? 

int verification_autre_joueurs(int numjoueur);

// Case autorisée ? 
int verification_case (enum tile_e nextCase);

// Explosion d'une bombe.
void explosion (Carte_t * Carte, int numero_case);

// Création des bonus dans les MURMOU
int bonus (int chanceux);

// Convertit les coordonnées linéaire en x y (cf mandelbrot)
int conversion (Carte_t * Carte, int x, int y);

// Charge le plateau de jeu à partir d'un fichier texte.
void chargement_carte (char * filename, Carte_t * Carte);

// Déplacement du joueur.
void deplacement_joueur (Carte_t * Carte, int numjoueur);

// Retourne le type de la prochaine case du joueur.
int type_prochaine_tuile (Carte_t * Carte, int numjoueur);


// Mise à jour des bombes.
void majbombe (Carte_t * Carte);
// Mise à jour des explosions.
void majexplosion (Carte_t * Carte);

// Permet d'afficher un peu de texte dans la console.
void updateOutput (int * endGame);

// Mise à jour des parametres du joueur
void majjoueur (Carte_t * Carte, int stepByStep);

// Destruction du plateau de jeu
void destruction_carte (Carte_t * Carte);