#ifndef USINE_BRIQUE_H
#define USINE_BRIQUE_H

#include "batiment_io.h"

//1 ressource d'entree : regolithe
#define RES_STOCK_UB_E0 0
#define MAX_STOCK_UB_E0 2
//une ressource de sortie : brique
#define RES_STOCK_UB_S 10
#define MAX_STOCK_UB_S 1

/****************************************************************************************/
/*newUsinne_brique : cree un nouveau batiment de type Usine_Brique selon les bonnes spec*/
/****************************************************************************************/
void newUsine_brique(batiment_io_t * tab_bat[20][20] , int pos_x , int pos_y);

/****************************************************************************************/
/*processUsinne_brique : produit la bonne ressource selon les spec de Usine_brique      */
/****************************************************************************************/
int processUsine_Brique(batiment_io_t * batiment);

/****************************************************************************************/
/*fctUsinne_brique : fonction qui fait tourner le batiment sur un tic                   */
/****************************************************************************************/
void fctUsine_Brique(batiment_io_t * batiment);

#endif
