#ifndef TUYAU_H
#define TUYAU_H


#include <math.h>
#include "map.h"



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
    struct tuyau* liste[NB_MAX_TUYAU];
    int taille;
} listeTuyau_t;



typedef struct tuyau
{
    batiment_io_t *entree;
    int cote_entree;
    batiment_io_t *sortie;
    int cote_sortie;
    int taille;

    int level;
    int nb_passage;

    enum Ressource contenu[NB_MAX_CASE];
    int lien_contenu_case[NB_MAX_CASE][2];
    enum TuyauOrientation orientation[NB_MAX_CASE];

} tuyau_t;


int mainTuyau();

int initListeTuyau(listeTuyau_t **l_tuyau);

int constructionTuyau(listeTuyau_t **p_l_tuyau, map_t **p_map, int x_souris, int y_souris);
int placeTuyau(tuyau_t **p_tuyau, map_t **p_map, int x_case, int y_case);
int checkCaseAdjacente(map_t *map, int x_case_souris, int y_case_souris, int x_case_prec, int y_case_prec);
int initTuyau(listeTuyau_t **l_tuyau);

int annulerConstructionTuyau(tuyau_t *tuyau, map_t *map);

int orientation_tuyau(tuyau_t *tuyau);
int check_entree_tuyau(tuyau_t *tuyau);
int decale_dans_tuyau(tuyau_t *tuyau);
int insertion_dans_tuyau(tuyau_t *tuyau, enum Ressource);

// A virer quand merge avec nathan
//int deleteDoor(batiment_io_t *batiment, tuyau_t *tube);

#endif
