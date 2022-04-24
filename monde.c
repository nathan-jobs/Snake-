/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <assert.h>

#include "monde.h"


int recherchePomme(Monde* mon, Case* carreau){
	int i;
	for (i = 0 ; i < mon->nbrPommes ; i++ ){
		if (carreau->pos_x == mon->tab[i].dedans.pos_x && carreau->pos_y == mon->tab[i].dedans.pos_y)
			return i;
	}
	return -1;
}

int ajouter_pomme_monde(Monde* mon){
	Case carreau;
	int res;
	Pomme pom = pomme_gen_alea(N, M);
	carreau.pos_x = -1;
	carreau.pos_y = -1;
	if (estOccupePar(mon, &(pom.dedans)) == 0){
		res = recherchePomme(mon, &carreau);
		if (res != -1){
			
			mon->tab[res] = pom;
			return 1;
		}
	}
	return 0;
}


int estOccupePar(Monde* mon, Case* carreau){
	int i;
	Serpent* tmp = &(mon->reptile);
	for (i = 0 ; i < mon->nbrPommes ; i++ ){
		if (carreau->pos_x == mon->tab[i].dedans.pos_x && carreau->pos_y == mon->tab[i].dedans.pos_y)
			return 1;
	}
	for (i = 1 ; i < tmp->taille ; i++){
		if (carreau->pos_x == tmp->tab[i].pos_x && carreau->pos_y == tmp->tab[i].pos_y)
			return 2;
	}
	if (!((0 <= carreau->pos_x && carreau->pos_x < M) && (0 <= carreau->pos_y && carreau->pos_y < N)))
		return -1;
	if (carreau->pos_x == tmp->tab[0].pos_x && carreau->pos_y == tmp->tab[0].pos_y)
		return 3;
	return 0;
}

Monde init_monde(int nb_pommes){
	Monde plateau;
	int canaliseur;
	int i;
	int j;
	int largeur = 0;
	int longueur = 0;
	int verif;
	assert(nb_pommes > 0);
	for ( i = 0 ; i < N ; i++ ){
		largeur = 0;
		for ( j = 0 ; j < M ; j++ ){
			plateau.quadrillage[i][j].pos_x = 300 + largeur;
			plateau.quadrillage[i][j].pos_y = 50 + longueur;
			largeur = largeur + 19;
		}
		longueur = longueur + 19;
	}
	plateau.tab = (Pomme*)malloc(sizeof(Pomme) * nb_pommes);
	if (plateau.tab == NULL)
		exit(EXIT_FAILURE);
	plateau.reptile = init_serpent();
	plateau.nbrPommes = nb_pommes;
	for ( j = 0 ; j < nb_pommes ; j++ ){
		plateau.tab[j].dedans.pos_x = -1;
		plateau.tab[j].dedans.pos_y = -1;
	}
	for ( i = 0 ; i < nb_pommes ; i++ ){
		canaliseur = 0;
		do{
			verif = ajouter_pomme_monde(&plateau);
			canaliseur += 1;
		}while(verif == 0 && canaliseur != 1000);
	}
	plateau.pomme_manges = 0;
	return plateau;
}



int deplacer_serpent(Monde *mon){
	Serpent* tmp = &(mon->reptile);
	int i;
	if (tmp->vers == EST){
		tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
		
		if (estOccupePar(mon, &(tmp->tab[0])) == 3){
			tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_x = tmp->tab[i].pos_x + 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
					
				}
			}
			return 1;
		}
		tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
	}
	else if (tmp->vers == OUEST){
		tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 3){
			tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_x = tmp->tab[i].pos_x - 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			return 1;
		}
		tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
	}
	else if (tmp->vers == SUD){
		tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 3){
			tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_y = tmp->tab[i].pos_y + 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			return 1;
		}
		tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
	}
	else if (tmp->vers == NORD){
		tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 3){
			tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_y = tmp->tab[i].pos_y - 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			return 1;
		}
		tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
	}
	return 0;
}




int manger_pomme_serpent(Monde* mon){
	Serpent* tmp = &(mon->reptile);
	int i;
	int res;
	Case carreau = tmp->tab[tmp->taille-1];
	if (tmp->vers == EST){
		tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 1){
			tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
			/*le serpent avance dans la direction*/
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_x = tmp->tab[i].pos_x + 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			/*la pomme mangée est supprimée du Monde*/
			res = recherchePomme(mon, &(tmp->tab[0]));
			mon->tab[res].dedans.pos_x = -1;
			mon->tab[res].dedans.pos_y = -1;
			mon->pomme_manges = mon->pomme_manges + 1;
			/*la taille du serpent augmente*/
			tmp->taille = tmp->taille + 1;
			tmp->tab[tmp->taille-1].pos_x = carreau.pos_x;
			tmp->tab[tmp->taille-1].pos_y = carreau.pos_y;
			return 1;
		}
		tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
	}
	else if (tmp->vers == OUEST){
		tmp->tab[0].pos_x = tmp->tab[0].pos_x - 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 1){
			tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_x = tmp->tab[i].pos_x - 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			/*la pomme mangée est supprimée du Monde*/
			res = recherchePomme(mon, &(tmp->tab[0]));
			mon->tab[res].dedans.pos_x = -1;
			mon->tab[res].dedans.pos_y = -1;
			mon->pomme_manges = mon->pomme_manges + 1;
			/*la taille du serpent augmente*/
			tmp->taille = tmp->taille + 1;
			tmp->tab[tmp->taille-1].pos_x = carreau.pos_x;
			tmp->tab[tmp->taille-1].pos_y = carreau.pos_y;
			return 1;
		}
		tmp->tab[0].pos_x = tmp->tab[0].pos_x + 1;
	}
	else if (tmp->vers == SUD){
		tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 1){
			tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_y = tmp->tab[i].pos_y + 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			/*la pomme mangée est supprimée du Monde*/
			res = recherchePomme(mon, &(tmp->tab[0]));
			mon->tab[res].dedans.pos_x = -1;
			mon->tab[res].dedans.pos_y = -1;
			mon->pomme_manges = mon->pomme_manges + 1;
			/*la taille du serpent augmente*/
			tmp->taille = tmp->taille + 1;
			tmp->tab[tmp->taille-1].pos_x = carreau.pos_x;
			tmp->tab[tmp->taille-1].pos_y = carreau.pos_y;
			return 1;
		}
		tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
	}
	else if (tmp->vers == NORD){
		tmp->tab[0].pos_y = tmp->tab[0].pos_y - 1;
		if (estOccupePar(mon, &(tmp->tab[0])) == 1){
			tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
			for (i = tmp->taille-1 ; i >= 0 ; i--){
				if (i == 0)
					tmp->tab[i].pos_y = tmp->tab[i].pos_y - 1;
				else{
					tmp->tab[i].pos_x = tmp->tab[i-1].pos_x;
					tmp->tab[i].pos_y = tmp->tab[i-1].pos_y;
				}
			}
			/*la pomme mangée est supprimée du Monde*/
			res = recherchePomme(mon, &(tmp->tab[0]));
			mon->tab[res].dedans.pos_x = -1;
			mon->tab[res].dedans.pos_y = -1;
			mon->pomme_manges = mon->pomme_manges + 1;
			/*la taille du serpent augmente*/
			tmp->taille = tmp->taille + 1;
			tmp->tab[tmp->taille-1].pos_x = carreau.pos_x;
			tmp->tab[tmp->taille-1].pos_y = carreau.pos_y;
			return 1;
		}
		tmp->tab[0].pos_y = tmp->tab[0].pos_y + 1;
	}
	return 0;
}



int mort_serpent(Monde mon){
	Serpent tmp = mon.reptile;
	Case carreau;
	int verif;
	if (mon.reptile.vers == EST){
		carreau = tmp.tab[0];
		carreau.pos_x = tmp.tab[0].pos_x + 1;
		verif = estOccupePar(&mon, &carreau);
		if (verif == 2 || verif == -1)
			return 1;
	}
	else if (mon.reptile.vers == OUEST){
		carreau = tmp.tab[0];
		carreau.pos_x = tmp.tab[0].pos_x - 1;
		verif = estOccupePar(&mon, &carreau);
		if (verif == 2 || verif == -1)
			return 1;
	}
	else if (mon.reptile.vers == NORD){
		carreau = tmp.tab[0];
		carreau.pos_y = tmp.tab[0].pos_y - 1;
		verif = estOccupePar(&mon, &carreau);
		if (verif == 2 || verif == -1)
			return 1;
	}
	else if (mon.reptile.vers == SUD){
		carreau = tmp.tab[0];
		carreau.pos_y = tmp.tab[0].pos_y + 1;
		verif = estOccupePar(&mon, &carreau);
		if (verif == 2 || verif == -1)
			return 1;
	}
	return 0;
}
