// Entités du jeu
#ifndef Entités_du_jeu_H
#define Entités_du_jeu_H

/*Definition d'une entité*/
typedef enum {
    JOUEUR,
    JOUEUR1,
    JOUEUR2,
    JOUEUR3,
    MUR,
    BOMBE,
    EXPLOSION,
    BONUS,
    SOL
} EntityType;


/*Définition de ce qu'est une entité*/
    //Toutes les entités auront le même type de données ( coordonnées, vie, texture etc). Je crée cette structure pour ne pas être redondant)
    typedef struct{
    int x, y;
    int health;
    EntityType type;
    SDL_Texture* texture;
}Entite;

/*bombe*/
typedef struct{
    Entite feur;
    float temps_de_vie;
    float puissance;    
}
bombe;

/*joueur*/
typedef struct{
    Entite feur;
    float puissance;    // Puissance d'explosion des bombes du joueur
    int vitesse;     // Vitesse de déplacement du joueur
    float temps_recharge // cooldown pour les bombes

}
joueur;


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
    Entite** entite;


} Carte;

/*Explosion*/
typedef struct{
    Entite feur;
    float timer; //Duréee de l'explosion
}explosion;


#endif