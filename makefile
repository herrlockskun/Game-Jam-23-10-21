CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o tuyau.o liste_c_tuyau.o
	$(CC) main.o tuyau.o liste_c_tuyau.o $(SDL2) -o prog 

main.o : main.c main.h
	$(CC) $(OPT) main.c

tuyau.o : tuyau.c tuyau.h
	$(CC) $(OPT) tuyau.c

liste_c_tuyau.o : liste_c_tuyau.c liste_c_tuyau.h
	$(CC) $(OPT) liste_c_tuyau.c


clear :
	rm  *.o 
	
propre :
	rm prog
