#ifndef MAP_H
#define MAP_H

#include "const.h"

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

/*****************************************************/
/*La structure de batiment contient :                */
/*   - sa position                                   */
/*   - son type (ex : usine_Brique)                  */
/*   - son rang (lié au type)                        */
/*   - son niveau actuel                             */
/*   - un tableau stock_entree des stocks d'entree   */
/*   - un stock de sortie, avec le nombre de tuyaux  */
/*   en sortie et l'idication du tuyau suivant       */
/*   - un tableau door_T du type de connectique sur  */
/*   chaque port (N , E , S , O)                     */
/*****************************************************/
typedef struct batiment_io
{
    int pos_x;
    int pos_y;
    int type;
    int rang;
    int niveau;

    int *stock_entree;
    int stock_sortie;
    int nb_sortie;
    int next_s;

    int door_T[4]; //-1 = pas de tuyau ; 0 = entree ; 1 = sortie
} batiment_io_t;   //door_T[0] = top ; door_T[1] = right ; door_T[2] = bottom ; door_T[3] = left

typedef struct listeTuyau
{
    struct tuyau *liste[NB_MAX_TUYAU];
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

typedef struct map
{
    int vierge[TAILLE_MAP][TAILLE_MAP];
    batiment_io_t *batiment[TAILLE_MAP][TAILLE_MAP];
    struct tuyau **tuyau[TAILLE_MAP][TAILLE_MAP];

} map_t;

#endif
