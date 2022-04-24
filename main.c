/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/
 
#include <MLV/MLV_all.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "affichage.h"
 
/*fonction     :jouer_le_jeu
 * parametres  : un mot et un nom du fichier
 * retour      : void
 * description : cette fonction fait appelle à toutes les fonctions définies précedemment
 * de façon systématique elle génère le monde avec 3 pommes et par la suite on déplace le serpent en récuperant les événements
 * du clavier s'il y a une pomme sur la prochaine destination du serpent on mange et on génère une nouvelle
 * on reitère tant que le serpent n'est pas mort . On compte chaque modification du serpent qu'on mettra dans un fichier*/

void jouer_le_jeu(char *mot,FILE* fichier);


int main(void){
	int menu;
	int score;
	int i = 1;
	char *mot;
	char pseudo[50];
	FILE *fichier;
	
	srand(time(NULL));
	MLV_create_window("SNAKE 3", "SNAKE 3", LONGUEUR, LARGEUR);
	menu = afficher_menu();
	while(i){
		fichier = fopen("fichier.txt","a+");
		if (menu == 1){
			MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
			mot ="a";
			jouer_le_jeu(mot,fichier);
		}
		if(menu == 2){
			MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
			dessiner_boite(pseudo);
			MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
			jouer_le_jeu(pseudo,fichier);
		}
		if(menu == 3){
			MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
			score= afficher_score(fichier);
			if(score==1){
				MLV_clear_window(MLV_COLOR_BLACK);
				menu = afficher_menu();	
			}
		}
	
	}
	fclose(fichier);
	return 0;
	
}

void jouer_le_jeu(char *mot,FILE* fichier){
	Monde plateau;
	char texte[] = "a";
	char cmp[] = "Inconnu";
	int x, y;
	int menu;
	int i =1;
	int j =1;
	int score;
	char pseudo[50];
	MLV_Event event;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	MLV_Keyboard_button sym;
	plateau = init_monde(3);
	afficher_monde(&plateau);
	if(strcmp(texte,mot)==0)
		mot ="Inconnu";
	MLV_draw_adapted_text_box(300, 10," %s !",9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, mot);
	MLV_actualise_window();
	MLV_wait_keyboard( NULL, NULL, NULL );
	while(i){
		event = MLV_get_event( 
				&sym, NULL, NULL, 
				NULL, NULL,
				NULL, NULL, NULL,
				NULL
			);
		if (event == MLV_KEY){
			if (sym == MLV_KEYBOARD_UP){
				if (plateau.reptile.vers != SUD)
					plateau.reptile.vers = NORD;
				}
				else if (sym == MLV_KEYBOARD_DOWN){
					if (plateau.reptile.vers != NORD)
						plateau.reptile.vers = SUD;
				}
				else if (sym == MLV_KEYBOARD_RIGHT){
					if (plateau.reptile.vers != OUEST)
						plateau.reptile.vers = EST;
				}
				else if (sym == MLV_KEYBOARD_LEFT){
					if (plateau.reptile.vers != EST)
						plateau.reptile.vers = OUEST;
				}
				else if (sym == MLV_KEYBOARD_SPACE)
					MLV_wait_keyboard( NULL, NULL, NULL );
				
			}
		if (mort_serpent(plateau))
			i = 0;
		else if (deplacer_serpent(&plateau));
		else if (manger_pomme_serpent(&plateau)){
			
			ajouter_pomme_monde(&plateau);
		}
		MLV_wait_milliseconds( 50 );
		MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
		MLV_draw_adapted_text_box(300, 10," %s !",9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER,mot );
		afficher_monde(&plateau);
		
			MLV_wait_milliseconds( 50 );
		}
		
		if(strcmp(mot,cmp) != 0 && plateau.pomme_manges != 0){
			fprintf(fichier,"%s",mot);
			fprintf(fichier, " a mangé %d pommes \n",plateau.pomme_manges);
		}
		MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
		MLV_draw_adapted_text_box(500, 300,"PARTIE TERMINE !",9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER);
		MLV_draw_adapted_text_box(440, 400,"VOTRE SCORE : %d POMMES MANGEES !",9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, plateau.pomme_manges);
		MLV_draw_filled_rectangle(LONGUEUR - 340, LARGEUR -80, 450, 50, MLV_COLOR_WHITE );
		MLV_draw_text_with_font(LONGUEUR - 338, LARGEUR - 78,"RETOUR AU MENU", font, MLV_COLOR_BLUE);
		MLV_actualise_window();
		do{
			event = MLV_get_event(
				NULL,NULL,NULL,
				NULL, NULL,
				&x,&y,NULL,
				NULL
			);
			if(event == MLV_MOUSE_BUTTON ){
				if((x>LONGUEUR - 340 && y>LARGEUR - 80) && (x<LONGUEUR + 110 && y>LARGEUR - 80) &&  (x> LONGUEUR - 340 && y< LARGEUR-30) && (x<LONGUEUR + 110 && y< LARGEUR-30 )){
					MLV_clear_window(MLV_COLOR_BLACK);
					menu = afficher_menu();
				}
				while(j){
					fichier = fopen("fichier.txt","a+");
					if (menu == 1){
						MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
						mot ="a";
						jouer_le_jeu(mot,fichier);
					}
					if(menu == 2){
						MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
						dessiner_boite(pseudo);
						MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
						jouer_le_jeu(pseudo,fichier);
					}
					if(menu == 3){
						MLV_clear_window(MLV_COLOR_LIGHT_SEA_GREEN);
						score= afficher_score(fichier);
						if(score==1){
							MLV_clear_window(MLV_COLOR_BLACK);
							menu = afficher_menu();	
						}
					}
	
				}
			}
		}while(1);
		MLV_wait_seconds( 10 );
		MLV_free_window();
		exit(EXIT_FAILURE);

}
