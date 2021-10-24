#ifndef TUYAU_H
#define TUYAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "batiments/batiment_io.h"
#include <math.h>

#define TAILLE_MAP 20
#define NB_MAX_CASE (TAILLE_MAP * TAILLE_MAP)

enum CaseMap
{
    sol,
    montagne
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
    batiment_io_t *entree;
    batiment_io_t *sortie;
    int taille;

    int level;
    int nb_passage;

    enum Ressource contenu[NB_MAX_CASE];
    int lien_contenu_case[NB_MAX_CASE][2];
    enum TuyauOrientation orientation[NB_MAX_CASE];

} tuyau_t;

typedef struct listeTuyau
{
    struct tuyau* liste[10];
    int taille;
} listeTuyau_t;


typedef struct map
{
    int vierge[TAILLE_MAP][TAILLE_MAP];
    batiment_io_t *batiment[TAILLE_MAP][TAILLE_MAP];
    tuyau_t *tuyau[TAILLE_MAP][TAILLE_MAP];

} map_t;

int mainTuyau();

int initListeTuyau(listeTuyau_t **l_tuyau);

int constructionTuyau(listeTuyau_t *l_tuyau, map_t *map, int x_souris, int y_souris);
int placeTuyau(tuyau_t *tuyau, map_t *map, int x_case, int y_case);
int checkCaseAdjacente(map_t *map, int x_case_souris, int y_case_souris, int x_case_prec, int y_case_prec);
int initTuyau(listeTuyau_t **l_tuyau);

int annulerConstructionTuyau(tuyau_t *tuyau, map_t *map);

int orientation_tuyau(tuyau_t *tuyau);
int check_entree_tuyau(tuyau_t *tuyau);
int decale_dans_tuyau(tuyau_t *tuyau);
int insertion_dans_tuyau(tuyau_t *tuyau, enum Ressource);


#endif
