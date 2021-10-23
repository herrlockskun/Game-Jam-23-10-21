#ifndef TUYAU_H
#define TUYAU_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "enum.h"

#define TAILLE_MAP 5
#define NB_MAX_CASE (TAILLE_MAP*TAILLE_MAP)


enum CaseMap
{
    sol,
    montagne,
    tuyau
};

enum Ressource
{
    aucuneRessource,
    titane,
    fer,
    eau
};

enum TuyauOrientation
{
    aucuneOrientation,
    vertical,
    horizontal
};


typedef struct tuyau
{
    //usine_t * entree;
    //usine_t * sortie;
    int taille;
    
    enum Ressource contenu[NB_MAX_CASE];
    int  lien_contenu_case[NB_MAX_CASE][2];
    enum TuyauOrientation orientation[NB_MAX_CASE];
    

}tuyau_t;



void print_map_console(enum CaseMap map[TAILLE_MAP][TAILLE_MAP]);
void print_case_console(enum CaseMap caseMap);




#endif
