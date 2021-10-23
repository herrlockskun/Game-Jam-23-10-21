#ifndef TUYAU_H
#define TUYAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#define TAILLE_MAP 5
#define NB_MAX_CASE (TAILLE_MAP*TAILLE_MAP)


enum CaseMap
{
    sol,
    montagne,
    usine,
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
    bas,
    bas_gauche,
    bas_droite,
    haut,
    haut_gauche,
    haut_droite,
    gauche,
    gauche_haut,
    gauche_bas,
    droite,
    droite_haut,
    droite_bas
};


typedef struct tuyau
{
    //batiment_io_t * entree;
    //batiment_io_t * sortie;
    int taille;
    int level;
    int nb_passage;
    
    enum Ressource contenu[NB_MAX_CASE];
    int  lien_contenu_case[NB_MAX_CASE][2];
    enum TuyauOrientation orientation[NB_MAX_CASE];
    

}tuyau_t;

typedef struct map
{
    int vierge[TAILLE_MAP][TAILLE_MAP];
    //batiment_io_t * batiment[TAILLE_MAP][TAILLE_MAP];
    tuyau_t* tuyau[TAILLE_MAP][TAILLE_MAP];
    
}map_t;

int mainTuyau();
void print_tuyau(tuyau_t * tuyau);
void print_map_console(enum CaseMap map[TAILLE_MAP][TAILLE_MAP]);
void print_case_console(enum CaseMap caseMap);
int orientation_tuyau(tuyau_t *tuyau);
int check_entree_tuyau(tuyau_t * tuyau);
int decale_dans_tuyau(tuyau_t *tuyau);
int insertion_dans_tuyau(tuyau_t * tuyau, enum Ressource);

#endif