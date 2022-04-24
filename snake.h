/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/
 
#ifndef __snake__
#define __snake__

#define N 30
#define M 30
#define LONGUEUR 1200
#define LARGEUR 700


typedef struct{
	int pos_x;
	int pos_y;
}Case;

typedef enum{
	NORD,
	EST,
	SUD,
	OUEST
}Direction;


typedef struct serpent{
	Case tab[N*M];
	Direction vers;
	int taille;
}Serpent;


typedef struct pomme{
	Case dedans;
}Pomme;

/* fonction    : pomme_gen_alea(int n , int m)
 * parametres  : deux entiers
 * retour      : un type pomme
 * description : cette fonction génère deux entiers aléatoires et le renvoie comme
 * 				une pomme */


Pomme pomme_gen_alea(int n, int m);
/* fonction    : init_serpent(void)
 * parametre   : rien 
 * retour      : un type serpent
 * description : cette fonction intialise un serpent au centre du quadrillage
 * 				direction vers l'EST*/


Serpent init_serpent(void);


#endif
