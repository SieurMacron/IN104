// Entités du jeu
#ifndef Entités_du_jeu_H
#define Entités_du_jeu_H

/*Definition d'une entité*/
typedef enum {
    JOUEUR,     //Joueur 1 
    JOUEUR1,    //Joueur 2 
    JOUEUR2,    //Joueur 3
    JOUEUR3,    //Joueur 4
    MURDUR,     //Mur indestructible
    MURMOU,     //Mur destructible
    BOMBE,      //Bombe
    EXPLOSION,  //Explosion
    BONUS,      //Bonus 
    VIDE        //Case vide
} EntityType;


/*Définition de ce qu'est une entité*/
    //Toutes les entités auront le même type de données ( coordonnées, vie, texture etc). Je crée cette structure pour ne pas être redondant)
    typedef struct{
    int x, y;
    int health;
    EntityType type;
    SDL_Texture* texture;
}Entite;

    //Definition des tuiles qui composeront la carte
    typedef struct{
        int x,y ;
        EntityType type;
        SDL_Texture* texture;
    }tuile;

/*bombe*/
typedef struct{
    Entite feur;
    float temps_de_vie;
    float puissance;    
}
bombe;



/* Mur */
typedef struct{
    Entite feur;
    int butin; //Information du type de bonus laissé par le mur à sa mort
        
} mur;

/*Bonus*/

typedef struct{
    Entite feur;
    int type_de_bonus // Definir plus tard le type de bonus
}bonus;

/*Carte */
typedef struct {
    int largeur ;
    int hauteur;
    tuile** grille;

} Carte;


/*Explosion*/
typedef struct{
    Entite feur;
    float timer; //Duréee de l'explosion
}explosion;




//*******Partie sur le joueur**************//

//Definition de ses mouvements :
typedef enum{
    STOP , 	// Le joueur est à l'arret.
	HAUT,		// Le joueur va vers le haut.
	DROITE,		// Le joueur va vers la droite.
	BAS,		// Le joueur va vers le bas.
	GAUCHE,		// Le joueur va vers la gauche.

}deplacement;

//Definition du joueur

typedef struct{
    Entite feur;
    float puissance;    // Puissance d'explosion des bombes du joueur
    int vitesse;     // Vitesse de déplacement du joueur
    float temps_recharge; // cooldown pour les bombes
    int vivant; // 0 si mort 1 si vivant
    deplacement dep; //Direction de déplacement

}
joueur;







#endif