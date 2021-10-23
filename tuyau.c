#include "tuyau.h"

typedef struct listeTuyau
{
    tuyau_t *liste[TAILLE_MAP];
    int taille;
} listeTuyau_t;

int mainTuyau()
{

    return 0;
}

/***************************************************/
/* Init de liste de tuyau                          */
/***************************************************/
int initListeTuyau()
{
    int erreur = 1;
}

/***************************************************/
/* print la map dans la console                    */
/***************************************************/
/*
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
*/

/***************************************************/
/* print une case de la couleur correspondante     */
/***************************************************/
/*
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
*/

/****************************************************/
/*                                                  */
/*  Construction tuyau                              */
/* 1-selection batiment                             */
/* 2-placer case adjacente batiment                 */
/* 3-placer case adjacente case prec                */
/* 4-selectionner batiment adjacent derniere case   */
/*                                                  */
/* erreur :                                         */
/*         -1 - Pas de bat select en debut chemin   */
/*          0 - Tuyau bien place                    */
/*          1 - Case pas voisinnage                 */
/*          2 - Case souris -> pas sol              */
/*          3 - Case souris -> tuyau                */
/*          4 - Case souris -> batiment             */
/*          5 - Batiment entree bien selectione     */
/*          6 - Batiment sortie bien selectione     */
/****************************************************/
int constructionTuyau(tuyau_t *tuyau, map_t *map, int x_souris, int y_souris)
{
    int erreur = 1; // Pas de voisinage

    int x_case_souris, y_case_souris;
    //x_case_souris = x_souris, y_case_souris = y_souris; // Appeler fct pour recup indice a partir de pixel

    x_case_souris = x_souris / 45; // 45 -> taille d'une case en pixel
    y_case_souris = y_souris / 45; // Ils onts pas fait un define ces sauvages

    if (tuyau->taille == 0) // Pas de tuyau unitaire cree
    {
        if (tuyau->entree == NULL) // Clic sur usine car debut tuyau
        {
            if (map->batiment[y_case_souris][x_case_souris] != NULL)
            { // Lien du tuyau d'entre avec la sortie
                tuyau->entree = *map->batiment[y_case_souris][x_case_souris];
                erreur = 5; // Batiment bien selectionne
            }
            else
            {
                erreur = -1; // Pas un batiment selectione pour debut du tuyau
            }
        }
        else // Batiment entree deja selectionne
        {    // Doit placer un tuyau
            // Check case adjacente
            erreur = checkCaseAdjacente(map, x_case_souris, y_case_souris, tuyau->entree->pos_x, tuyau->entree->pos_y);
            // Place le tuyau adjacent au batiment
            erreur = placeTuyau(tuyau, map, x_case_souris, y_case_souris);
        }
    }
    else
    {
        // Check case adjacente
        erreur = checkCaseAdjacente(map, x_case_souris, y_case_souris, tuyau->entree->pos_x, tuyau->entree->pos_y);
        if (erreur == 4) // Case souris -> batiment
        {                // Selectionne le dernier batiment
            tuyau->sortie = *map->batiment[y_case_souris][x_case_souris];
            erreur = 6; // 6 - Batiment sortie bien selectione
        }
        else
        {
            // Place le tuyau adjacent au tuyau precedent
            erreur = placeTuyau(tuyau, map, x_case_souris, y_case_souris);
        }
    }
    return erreur;
}

/****************************************************/
/* Place une unite de tuyau sur la case d'la souris */
/* Place le pointeur vers le tuyau                  */
/****************************************************/
int placeTuyau(tuyau_t *tuyau, map_t *map, int x_case, int y_case)
{
    tuyau->taille++;
    tuyau->lien_contenu_case[tuyau->taille][0] = x_case;
    tuyau->lien_contenu_case[tuyau->taille][1] = y_case;
    map->tuyau[y_case][x_case] = &tuyau; // Normalement adr case cell

    return 0;
}

/****************************************************/
/* Check si case de la souris                       */
/* est adjacente a la case precedente pose          */
/* erreur :                                         */
/*          0 - Case souris -> sol                  */
/*          1 - Case pas voisinnage                 */
/*          2 - Case souris -> pas sol              */
/*          3 - Case souris -> tuyau                */
/*          4 - Case souris -> batiment             */
/****************************************************/
int checkCaseAdjacente(map_t *map, int x_case_souris, int y_case_souris, int x_case_prec, int y_case_prec)
{
    int erreur = 1; // Case pas voisinnage

    int voisinage = abs(x_case_souris - x_case_prec) + abs(y_case_souris - y_case_prec);

    if (voisinage == 1) // Case souris adjacente a case precedente
    {
        if (map->batiment[y_case_souris][x_case_souris] == NULL) // Pas de batiment
        {
            if (map->tuyau[y_case_souris][x_case_souris] == NULL) // Pas de tuyau
            {
                if (map->vierge[y_case_souris][x_case_souris] == sol) // Pas de montagne -> sol
                {
                    erreur = 0; // Case souris -> sol
                }
                else
                {
                    erreur = 2; // Case souris -> pas sol
                }
            }
            else
            {
                erreur = 3; // Case souris -> tuyau
            }
        }
        else
        {
            erreur = 4; // Case souris -> batiment
        }
    }
    return erreur;
}

/***************************************************/
/* malloc du tuyau et initialisation a 0           */
/* erreur : 0 tuyau vierge ok / 1 erreur malloc    */
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
            tuyau->contenu[i] = aucuneRessource;

            tuyau->lien_contenu_case[i][0] = -1;
            tuyau->lien_contenu_case[i][1] = -1;

            tuyau->orientation[i] = aucuneOrientation;
        }
    }

    return erreur;
}

/***************************************************/
/*                                                 */
/*  erreur : 0 - porte supprime                    */
/*           1 - porte pas trouve sur le batiment  */
/*           2 - batiment pas lie                  */
/*                                                 */
/***************************************************/
int annulerConstructionTuyau(tuyau_t *tuyau, map_t *map)
{
    int erreur = 1;

    int x_unite, y_unite;

    for (int i = 0; i < tuyau->taille; ++i)
    {
        // Recuperation coordonnees du dernier tuyau
        x_unite = tuyau->lien_contenu_case[i][0];
        y_unite = tuyau->lien_contenu_case[i][1];

        map->tuyau[y_unite][x_unite] = NULL; // Reset de la case dans map
    }

    // Supprime la connexion avec batiment si elle existe
    //erreur = deleteDoor(tuyau->entree, tuyau);
    //erreur = deleteDoor(tuyau->sortie, tuyau);

    tuyau_t *tmp = tuyau;

    free(tuyau); // Libere le tuyau

    return erreur;
}