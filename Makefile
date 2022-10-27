CC = gcc #Déclaration de variables
DEBUG = yes
SRC = $(wildcard *.c)#Génération de la liste des fichiers sources
EXE = prog
OBJ = $(SRC:.c=.o)
TOBJ=$(OBJ:%.o=target/%.o)

ifeq ($(DEBUG), yes) #Condtions
$(info "Debug activé")

CFLAGS = -g -Wall -Wextra
else
CFLAGS = -Wall -Wextra
endif

LIB=-lm -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: $(OBJ)
	@echo "Compilation"
	@$(CC) -o $(EXE) $(TOBJ) $(LIB)

	
%.o:%.c
	@make target
	$(CC) -c $< -o target/$@ $(CFLAGS)

clean:
	rm target/*.o 

target:
	if [ ! -d target ];then mkdir target;echo "Dossier target cree";fi
