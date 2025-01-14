#ifndef CONST_H
#define CONST_H

/*** PATH ***/
#define MAX_TEXTURE 20

#define PATH_BOUTON_CONSTRUCTION_TUYAU "./images/bouton.png"
#define PATH_BOUTON_CONSTRUCTION_USINE "./images/bouton.png"

#define PATH_BACKGROUND_MENU "./images/cosmos.jpeg"

#define PATH_BACKGROUND "./images/lune.jpg" // sol de base, plus untilise
#define PATH_TUYAU_HORIZONTAL
#define PATH_TUYAU_VERTICAL "./images/vertical.png"
#define PATH_TUYAU_VIRAGE "./images/virage_2.png"
#define PATH_TUYAU_AUCUNE_ORIENTATION "./images/tuyau_aucune_orientation.png"
#define PATH_CASE_SURLIGNEE "./images/case_surlignee.png"

// Sol
#define PATH_SOL_BASE "./images/voxel-pack/PNG/Tiles/stone.png"
#define PATH_FOUR "./images/voxel-pack/PNG/Tiles/oven.png"

#define PATH_FONT "./font/arial.ttf"

/*** Librairies ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/*** constante ***/
#define TAILLE_MAP 20 // Taille de la grille
#define NB_MAX_CASE (TAILLE_MAP * TAILLE_MAP)

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 900

#define LARGEUR_MAP (0.75 * LARGEUR_FENETRE)
#define HAUTEUR_MAP HAUTEUR_FENETRE
#define TAILLE_CASE_MAP 45 // Taille en pixel d'une case

#define OFFSETX LARGEUR_MAP
#define OFFSETY 300
#define LARGEUR_MENU (LARGEUR_FENETRE - LARGEUR_MAP)

#define NB_MAX_TUYAU 10

#include "tuyau.h"
#include "background.h"
#include "event.h"
#include "menu.h"
#include "event.h"
#include "map.h"

#endif
