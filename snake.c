/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/
 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include <assert.h>
#include "snake.h"



Pomme pomme_gen_alea(int n, int m){
	Pomme pom;
	assert(n > 0);
	assert(m > 0); 
	pom.dedans.pos_x = rand() % m; 
	pom.dedans.pos_y = rand() % n;
	return pom;
}



Serpent init_serpent(void){
	Serpent reptile;
	Case carreau;
	int i;
	int j;
	for ( i = 0 ; i < N ; i++ ){
		for ( j = 0 ; j < M ; j++ ){
			if (i == (N/2) && j == (M/2)){
				carreau.pos_y = i;
				carreau.pos_x = j;
				reptile.tab[0] = carreau;
			}
			else if (i == (N/2) && j == (M/2)-1){
				carreau.pos_y = i;
				carreau.pos_x = j;
				reptile.tab[1] = carreau;
			}
		}
	}
	reptile.vers = EST;
	reptile.taille = 2;
	return reptile;
}
