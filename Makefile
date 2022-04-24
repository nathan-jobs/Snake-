CFLAGS = -ansi -pedantic -Wall -Wfatal-errors
LDFLAGS = -lMLV
CC = gcc

OBJ = main.o affichage.o monde.o snake.o 
	
serpent : $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 

## EN METTANT CETTE PARTIE EN COMMENTAIRE########	
#main.o : main.c affichage.h
#affichage.o : affichage.c affichage.h monde.h snake.h
#monde.o : monde.c monde.h snake.h
#snake.o : snake.c snake.h
#%.o : %.c
#	$(CC) -c $<  $(CFLAGS) 
###################################################
	
clean : 
	rm -f *.o
	
mrproper : clean
	rm -f $@

