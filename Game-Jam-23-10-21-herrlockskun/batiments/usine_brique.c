#include "usine_brique.h"

void newUsine_brique(batiment_io_t * tab_bat[C_MAX][C_MAX] , int pos_x , int pos_y)
{
    batiment_io_t * batiment;

    newBatiment(&batiment , pos_x , pos_y , 1 , 1);
    batiment->type = 0;
    batiment->stock_entree[0] = 0;
    tab_bat[pos_y][pos_x] = batiment;
}

int processUsine_Brique(batiment_io_t * batiment)
{
    int erreur = 0;

    if (batiment->type == 0)
    {
        if (stockSortieVide(batiment) && stockEntreePlein(batiment , 0 , MAX_STOCK_UB_E0))
        {
            batiment->stock_entree[0] = 0;
            batiment->stock_sortie = 1;
        }
    }
    else
    {
        erreur = 1;
    }
    
    return erreur;
}

void fctUsine_Brique(batiment_io_t * batiment)
{
    int dest;

    processUsine_Brique(batiment);
    dest = destRessource(batiment);
    //envoi de la ressource RES_STOCK_UB_S dans le tuyau côte dest
    if (batiment->stock_sortie > 0 && dest >= 0)
    {
        batiment->stock_sortie--;
    }
}
