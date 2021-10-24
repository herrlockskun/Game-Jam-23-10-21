
#ifndef TUYAU_H
#define TUYAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>

#define TAILLE_MAP 5
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

typedef struct listeTuyau
{
    struct tuyau *liste[TAILLE_MAP];
    int taille;
} listeTuyau_t;

// A virer apres merge avec nathan
typedef struct door
{
    int *tube;
    int type;
} door_t;

// A virer apres merge avec nathan
typedef struct batiment_io
{
    int pos_x;
    int pos_y;

    int *stock_entree;
    int *stock_sortie;

    door_t d_top;
    door_t d_bottom;
    door_t d_left;
    door_t d_right;
} batiment_io_t;

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
int initTuyau(listeTuyau_t *l_tuyau);

int annulerConstructionTuyau(tuyau_t *tuyau, map_t *map);

int orientation_tuyau(tuyau_t *tuyau);
int check_entree_tuyau(tuyau_t *tuyau);
int decale_dans_tuyau(tuyau_t *tuyau);
int insertion_dans_tuyau(tuyau_t *tuyau, enum Ressource);

// A virer quand merge avec nathan
int deleteDoor(batiment_io_t *batiment, tuyau_t *tube);

#endif