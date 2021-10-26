#ifndef CONST_H
#define CONST_H

/*** PATH ***/
#define BOUTON_CONSTRUCTION_TUYAU
#define BOUTON_CONSTRUCTION_USINE

#define BACKGROUND_MENU

#define TUYAU_HORIZONTAL
#define TUYAU_VERTICAL
#define TUYAU_VIRAGE

/*** Librairies ***/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


/*** constante ***/
#define TAILLE_MAP 20   // Taille de la grille
#define NB_MAX_CASE (TAILLE_MAP * TAILLE_MAP)

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 900

#define LARGEUR_MAP (0.75*LARGEUR_FENETRE)
#define HAUTEUR_MAP HAUTEUR_FENETRE
#define TAILLE_CASE_MAP 45 // Taille en pixel d'une case

#define OFFSETX LARGEUR_MAP
#define OFFSETY 300
#define LARGEUR_MENU (LARGEUR_FENETRE - LARGEUR_MAP)

#define NB_MAX_TUYAU 10


#include "tuyau.h"
#include "background.h"
#include "menu.h"
#include "map.h"

#endif