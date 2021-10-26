#ifndef MAP_H
#define MAP_H

#include "const.h"

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

struct tuyau;

typedef struct map
{
    int vierge[TAILLE_MAP][TAILLE_MAP];
    batiment_io_t *batiment[TAILLE_MAP][TAILLE_MAP];
    struct tuyau **tuyau[TAILLE_MAP][TAILLE_MAP];

} map_t;

#endif
