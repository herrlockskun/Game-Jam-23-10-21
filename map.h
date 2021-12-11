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
{                      // * Indique test en + pour passer par la bonne case
    aucuneOrientation, // 0  ( 0, 0)
    bas,               // 1  ( 0, 2)
    bas_gauche,        // 2  (-1, 1) *
    bas_droite,        // 3  ( 1, 1) *
    haut,              // 4  ( 0,-2)
    haut_gauche,       // 5  (-1,-1) *
    haut_droite,       // 6  ( 1,-1) *
    gauche,            // 7  (-2, 0)
    gauche_haut,       // 8  (-1,-1)
    gauche_bas,        // 9  (-1, 1)
    droite,            // 10 ( 2, 0)
    droite_haut,       // 11 ( 1,-1)
    droite_bas         // 12 ( 1, 1)
};

// Permet de retrouver plus facilement la texture dans le tableau sans se soucier de l'indice
enum TextureIndice
{
    tuyau_horizontale,
    tuyau_virage,
    stone

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
