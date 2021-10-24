CC = gcc #Déclaration de variables
DEBUG = yes
SRC = $(wildcard *.c)#Génération de la liste des fichiers sources
EXE = prog
OBJ = $(SRC:.c=.o) batiment_io.o tests_batiments.o usine_brique.o tests_batiments.o

ifeq ($(DEBUG), yes) #Condtions
$(info "Debug activé")
CFLAGS = -g -Wall -Wextra
else
CFLAGS = -Wall -Wextra
endif

LIB=-lm -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: $(OBJ)
	@echo "Compilation"
	@$(CC) -o $(EXE) $^ $(LIB)

%.o:%.c
	@$(CC) -c $< $(CFLAGS)

batiment_io.o : batiments/batiment_io.c
	@$(CC) -c $< $(CFLAGS)

usine_brique.o : batiments/usine_brique.c
	@$(CC) -c $< $(CFLAGS)

tests_batiments.o : local_test/tests_batiments.c
	@$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

