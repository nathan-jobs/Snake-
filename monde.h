/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/

#ifndef __monde__
#define __monde__
#include "snake.h"

typedef struct monde{
	Case quadrillage[N][M]; 
	Serpent reptile;
	Pomme* tab; /* le tableau des pommes présentes dans le jeu */
	int nbrPommes; /* le nombre des pommes présentes */
	int pomme_manges; /* le nombre des pommes mangées */ 
}Monde;	

/* fonction    : init_monde
 * parametre  : nombre de pommes
 * retour      : un monde (serpent ,pommes et quadrillage)
 * description :cette fonction initialise un monde ce dernier
 * 				est un ensemble constitué de :
 * 				serpent initialisé par init_serpent
 * 				les pommes qui sont allouées dynamiquement
 *				 et remplie les valeurs de chaque case du tableau */


Monde init_monde(int);

/*fonction     : ajouter_pomme_monde
 * parametres  : un pointeur sur un monde
 * retour      : un entier
 * description : cette fonction ajoute une pomme dans un monde 
 * 				elle renvoie 1 si l'ajout a été effectué 0 sinon */


int ajouter_pomme_monde(Monde*);

/* fonction    : deplacer_serpent
 * parametre   : un pointeur sur un monde
 * retour      : un entier 
 * description : cette fonction prend en parametre un pointeur
 * 				sur un monde et modifie le tableau de serpent en fonction de 
 * 				la direction . Pour eviter les variables temporaires on commence par modifier
 * 				la tête du serpent on regarde si la case correspont bien à la tête d'un serpent
 * 				dans le monde et pas autre chose  si c'est le cas on modifie le serpent en 
 * 				commençant par la queue et on renvoie 1 sinon en renvoie 0.*/

int deplacer_serpent(Monde*);


/* fonction    :  manger_pomme_serpent(Monde* mon)
 * parametre   :  un pointeur sur un monde
 * retour      :  un entier
 * description :  cette fonction prend en parametre un pointeur sur 
 * 				un monde comme pour le deplacement on commence par verifier si la case d'après contient 
 * 				une pomme si oui on supprime la pomme en mettant -1 -1 dans le tableau de pomme
 * 				ensuite on augmente la taille du serpent et enfin on renvoie 1 sinon on renvoie 0.*/

int manger_pomme_serpent(Monde*);

/*fonction     : estOccupePar
 * parametres  : un pointeur sur un monde et un pointeur sur une case
 * retour      : un entier
 * description : cette fonction verifie si une case du plateau est occupé 
 * 				elle renvoie: 
 * 				1 si elle est occupée par une pommme
 * 				2 si la case est occupée par un le corps du serpent
 * 				3 si la case est occupée par la tête du serpent 
 * -			1 si les coordonées de la case depasse la grille
 *  */


int estOccupePar(Monde*, Case*);

/* fonction    : recherchePomme
 * parametre   : un monde et une case
 * retour      : un entier positif ou negatif
 * description : cette fonction elle prend en parametre un
 * 				monde et une case et verifie si la valeur de la case est dans le monde et renvoie sa première 
 *				occurence . Cette fonction recherche la première apparition de -1 dans le tableau de pomme.*/
 
int recherchePomme(Monde*, Case*);

/* fonction    : mort_serpent(Monde mon)
 * parametre   : un monde
 * retour      : un entier
 * description : cette fonction verifie si la prochaine destination
 * 				du serpent peut entrainer la fin du jeu en d'autre terme si la fonction
 * 				estOccupePar renvoie 2 ou -1 */
int mort_serpent(Monde);
#endif
