#include "tuyau.h"

int mainTuyau()
{
    // Init map
    enum CaseMap map[TAILLE_MAP][TAILLE_MAP];

    // Full sol
    for (int i = 0; i < TAILLE_MAP; i++)
    {
        for (int j = 0; j < TAILLE_MAP; j++)
        {
            map[i][j] = sol;
        }
    }
    map[0][1] = tuyau;
    map[0][2] = tuyau;
    map[0][3] = tuyau;
    map[1][3] = tuyau;

    print_map_console(map);

    return 0;
}

/***************************************************/
/* print la map dans la console                    */
/***************************************************/
void print_map_console(enum CaseMap map[TAILLE_MAP][TAILLE_MAP])
{
    for (int i = 0; i < TAILLE_MAP; i++)
    {
        for (int j = 0; j < TAILLE_MAP; j++)
        {
            print_case_console(map[i][j]);
        }
        printf("\n");
    }
    printf("\033[0m\n");
}

/***************************************************/
/* print une case de la couleur correspondante     */
/***************************************************/
void print_case_console(enum CaseMap caseMap) // Faire un switch case
{
    // Reset \033[0m\n
    if (caseMap == sol)
        printf("\033[0;47m ");
    else if (caseMap == montagne)
        printf("\033[0;40m ");
    else if (caseMap == tuyau)
        printf("\033[0;41m ");
}

/***************************************************/
/*                                                 */
/*  Construction tuyau                             */
/* 1-selection batiment                            */
/* 2-placer case adjacente batiment                */
/* 3-placer case adjacente case prec               */
/* 4-selectionner batiment adjacent derniere case  */
/*                                                 */
/***************************************************/
int constructionTuyau(tuyau_t *tuyau, map_t *map, int x,int y)
{
    int erreur = 1;

    int x_case, y_case;
    x_case = x, y_case = y; // Appeler fct pour recup indice a partir de pixel

    if (tuyau->taille == 0) // Pas de tuyau unitaire cree
    {
        if(tuyau->entree == NULL) // Clic sur usine car debut tuyau
        if (map->batiment_io_t[y_case][x_case] != NULL)
        {   // Lien du tuyau d'entre avec la sortie
            //tuyau->entree = map->batiment_io_t[y_case][x_case] 
        }
        else
        {
            erreur = 2; // Pas un batiment selectione pour debut du tuyau
        }
    }
    else
    {
        
    }

}

/***************************************************/
/* malloc du tuyau et initialisation a 0           */
/***************************************************/
int initTuyau(tuyau_t *tuyau)
{
    int erreur = 1;

    tuyau = (tuyau_t *)malloc(sizeof(tuyau_t *));

    if (tuyau != NULL)
    {
        int erreur = 0; // malloc reussi
        tuyau->taille = 0;

        // Initialise le contenu vide et aucun tuyau unitaire
        for (int i = 0; i < NB_MAX_CASE; i++)
        {
            tuyau->contenu = aucuneRessource;

            tuyau->lien_contenu_case[i][0] = -1;
            tuyau->lien_contenu_case[i][1] = -1;

            tuyau->orientation[i] = aucuneOrientation;
        }
    }

    return erreur;
}