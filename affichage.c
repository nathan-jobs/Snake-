/* Auteur : MBUMA MONA Nathan
 * création : 22/02/2019
 * modification : 11/03/2019*/
 
#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"


void afficher_quadrillage(Monde* mon){
	int i;
	int j;
	for ( i = 0 ; i < N ; i++ ){
		for ( j = 0 ; j < M ; j++ )
			if ((i+j) % 2 == 0)
				MLV_draw_filled_rectangle(mon->quadrillage[i][j].pos_x, mon->quadrillage[i][j].pos_y, 18, 18, MLV_COLOR_SPRINGGREEN);
			else
				MLV_draw_filled_rectangle(mon->quadrillage[i][j].pos_x, mon->quadrillage[i][j].pos_y, 18, 18, MLV_COLOR_DARKOLIVEGREEN1);
	}
}


void afficher_pomme(Monde* mon, Pomme pom){
	Case carreau;
	int i;
	int j;
	i = pom.dedans.pos_y;
	j = pom.dedans.pos_x;
	carreau = mon->quadrillage[i][j];
	MLV_draw_filled_circle(carreau.pos_x + 9, carreau.pos_y + 9, 7.5, MLV_COLOR_RED);
}


void afficher_serpent(Monde* mon, Serpent ser){
	Case carreau;
	int i;
	carreau = mon->quadrillage[ser.tab[0].pos_y][ser.tab[0].pos_x];
	MLV_draw_filled_circle(carreau.pos_x + 9, carreau.pos_y + 9, 8.5, MLV_COLOR_BLUE);
	for( i = 1 ; i < ser.taille ; i++){
		carreau = mon->quadrillage[ser.tab[i].pos_y][ser.tab[i].pos_x];
		MLV_draw_filled_rectangle(carreau.pos_x + 2, carreau.pos_y + 2, 14, 14, MLV_COLOR_STEEL_BLUE);
	}
}

void afficher_monde(Monde* mon){
	int i;
	afficher_quadrillage(mon);
	for (i = 0 ; i < mon->nbrPommes ; i++)
		afficher_pomme(mon, mon->tab[i]);
	afficher_serpent(mon, mon->reptile);
	MLV_draw_text(LONGUEUR - 200, LARGEUR - 50, "Score : %d Pommes mangées", MLV_COLOR_RED, mon->pomme_manges);
	MLV_draw_filled_rectangle(0, 0, 20, 20, MLV_COLOR_LIGHT_SEA_GREEN);
	MLV_actualise_window();
}

MLV_Color fabriqueCouleur(void){
	return MLV_rgba(255, 255, 255, 100);
}

int afficher_menu(void){
	MLV_Event event;
	int i = 1;
	int x, y;
	MLV_Image *image;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	image = MLV_load_image("src/serpent.jpg");
	MLV_resize_image_with_proportions(image, LONGUEUR, LARGEUR);
	MLV_draw_image(image, 0, 50);
	MLV_actualise_window();
	MLV_draw_filled_rectangle(400, 150, 450, 50,fabriqueCouleur());
	MLV_draw_text_with_font(560, 140,"JOUER", font, MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(400,215, 450, 50, fabriqueCouleur());
	MLV_draw_text_with_font(420, 210,"S'IDENTIFIER ET JOUER", font, MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(400, 275, 450, 50, fabriqueCouleur());
	MLV_draw_text_with_font(410, 270,"LES MEILLEURS SCORES", font, MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(400, 333, 450, 50, fabriqueCouleur());
	MLV_draw_text_with_font(530, 320,"QUITTER", font, MLV_COLOR_BLACK);
	MLV_actualise_window();
	do{
		event = MLV_get_event(
			NULL,NULL,NULL,
			NULL, NULL,
			&x,&y,NULL,
			NULL
		);
		if(event == MLV_MOUSE_BUTTON ){
			if((x>400 && y> 150) && (x<850 && y> 150) &&  (x> 400 && y< 200) && (x<850 && y< 200))
				return 1;
			else if((x>400 && y> 210) && (x<850 && y>210) &&  (x> 400 && y< 260) && (x<850 && y< 260))
				return 2;
			else if((x>400 && y> 260) && (x<850 && y> 260) &&  (x> 400 && y< 320) && (x<850 && y<320 ))
				return 3;
			else if((x>400 && y> 320) && (x<850 && y>320) &&  (x> 400 && y< 370) && (x<850 && y< 370)){
				MLV_clear_window(MLV_COLOR_BLACK);
				MLV_draw_filled_rectangle(LONGUEUR/2-250, LARGEUR/2-50, 250, 50, MLV_COLOR_WHITE);
				MLV_draw_text_with_font(LONGUEUR/2-235 , LARGEUR/2-50 ,"Au revoir  !!!", font, MLV_COLOR_BLUE);
				MLV_actualise_window();
				MLV_wait_seconds(5);
				MLV_free_window();
				exit(EXIT_FAILURE);
			}
		}
	}while(i);
	MLV_free_font( font );
	return 0;
}

int afficher_score(FILE *fichier){
	char chaine[100];
	MLV_Event event;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	int i = 50;
	int j= 1;
	int x,y;
	int cmp = 0;
	while (fgets(chaine,1000,fichier)!=NULL){	
		if(cmp > 0){
			MLV_draw_adapted_text_box(600, i," %s ",9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER,chaine);
			i = i + 50;
		}
		cmp++;
	}
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
			if((x>LONGUEUR - 340 && y>LARGEUR - 80) && (x<LONGUEUR + 110 && y>LARGEUR - 80) &&  (x> LONGUEUR - 340 && y< LARGEUR-30) && (x<LONGUEUR + 110 && y< LARGEUR-30 ))
				return 1;
		}
	}while(j);
	return 0;
}

void dessiner_boite(char texte[]){
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
    char *tableau;
    MLV_Input_box *box;
    MLV_Input_box *event_box;
    MLV_Event event;
	int i=1;
	
	
	MLV_clear_window(MLV_COLOR_BLACK);
	box = MLV_create_input_box(
    500,210,
    300, 35,
    MLV_COLOR_GREY, MLV_COLOR_BLUE,
    MLV_COLOR_WHITE,
    "Veuillez saisir votre pseudo: ",font
	);
	
	

	MLV_draw_input_box(box);
	MLV_activate_input_box(box);
	MLV_actualise_window();
	
	do{
		event = MLV_get_event(
			NULL,NULL,NULL,
			&tableau, &event_box,
			NULL,NULL,NULL,
			NULL
		);
	
		if(event == MLV_INPUT_BOX ){
			strcpy(texte,tableau);
			i=0;
		}

	MLV_draw_input_box(box);
	MLV_actualise_window();
	}while(i);
	MLV_free_input_box(box);
	MLV_free_font( font );
	
}
