#ifndef TUYAU_H
#define TUYAU_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>


#define TAILLE_MAP 5
#define NB_MAX_CASE (TAILLE_MAP*TAILLE_MAP)


enum CaseMap
{
    sol,
    montagne
    //usine,
    //tuyau
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


typedef struct door
{
    int * tube;
    int type;
}door_t;

typedef struct batiment_io
{
    int pos_x;
    int pos_y;

    int * stock_entree;
    int * stock_sortie;

    door_t d_top;
    door_t d_bottom;
    door_t d_left;
    door_t d_right;
}batiment_io_t;

typedef struct tuyau
{
    batiment_io_t * entree;
    batiment_io_t * sortie;
    int taille;
    
    enum Ressource contenu[NB_MAX_CASE];
    int  lien_contenu_case[NB_MAX_CASE][2];
    enum TuyauOrientation orientation[NB_MAX_CASE];
    

}tuyau_t;

typedef struct map
{
    int vierge[TAILLE_MAP][TAILLE_MAP];
    batiment_io_t * batiment[TAILLE_MAP][TAILLE_MAP];
    tuyau_t* tuyau[TAILLE_MAP][TAILLE_MAP];
    
}map_t;

int mainTuyau();

void print_map_console(enum CaseMap map[TAILLE_MAP][TAILLE_MAP]);
void print_case_console(enum CaseMap caseMap);

int constructionTuyau(tuyau_t *tuyau, map_t *map, int x_souris, int y_souris);

int checkCaseAdjacente(map_t *map, int x_case_souris, int y_case_souris, int x_case_prec, int y_case_prec);

int initTuyau(tuyau_t *tuyau);




#endif
