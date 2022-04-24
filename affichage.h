/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/
 
#ifndef __affichage__
#define __affichage__
#include "snake.h"
#include "monde.h"
#include <MLV/MLV_all.h>

/* fonction    : afficher_quadrillage
 * parametre   : un monde 
 * retour      : rien
 * description : cette fonction le plateau du jeu
 */
void afficher_quadrillage(Monde* mon);

/* fonction    : afficher_pomme
 * parametre   : un monde et une pomme
 * retour      : rien
 * description : cette fonction affiche les différentes pommes 
 */

void afficher_pomme(Monde* mon, Pomme pom);

/* fonction    : afficher_serpent
 * parametre   : un monde et un serpent
 * retour      : rien
 * description : cette fonction affiche le serpent 
 */

void afficher_serpent(Monde*, Serpent ser);

/* fonction    : afficher_monde
 * parametre   : un monde et un serpent
 * retour      : rien
 * description : cette fonction affiche le monde du jeu
 * 				(pomme , serpent , quandrillage et le nom du joeur) 
 */


void afficher_monde(Monde* mon);

/* fonction    : afficher_menu 
 * parametre   : rien
 * retour      : un entier 
 * description : cette fonction affiche le menu principal du jeu
 * 				elle renvoie:  
 * 				1 pour jouer 
 * 				2 s'identifier et jouer
 * 				3 consulter les meilleurs scores 
 */
 
int afficher_menu(void);
  /* fonction    : fabriqueCouleur(void)
 * parametre   : rien
 * retour      : MLV_Color
 * description : cette fonction renvoie une couleur 
 */
 
MLV_Color fabriqueCouleur(void);
 
/* fonction    : dessiner_boite(char *texte)
 * parametre   : une chaine de caractère
 * retour      : rien
 * description : cette fonction crée une boite de dialogue
 * 				copie le nom renseigné par l'utilisateur dans texte */
void dessiner_boite(char* texte);

/* fonction    : afficher_score(FILE *fichier)
 * parametre   : un fichier
 * retour      : un entier
 * description : cette fonction affiche le score à la fin de la partie */

int afficher_score(FILE* fichier);


#endif
