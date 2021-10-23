#include "tuyau.h"

int mainTuyau()
{
    int erreur;
    listeTuyau_t *l = NULL;
    erreur = initListeTuyau(l);

    map_t *map = NULL;

    if (erreur == 0)
    {

        //Clic construction
        erreur = initTuyau(l);

        if (erreur == 0)
        {
            constructionTuyau(l, map, 0, 0);

            if (erreur == 5)
            {
                constructionTuyau(l, map, 45, 0);
                if (erreur == 0)
                {
                    constructionTuyau(l, map, 90, 0);
                    if (erreur == 6)
                    {
                        printf("yoyo\n");
                    }
                }
            }
        }
    }

    /*
    map[2][1] = tuyau;
    map[2][2] = tuyau;
    map[2][3] = tuyau;
    map[3][3] = tuyau;

    print_map_console(map);*/

    /*
    tuyau_t *tuyau = (tuyau_t *)malloc(sizeof(tuyau_t));

    if (tuyau)
    {
        tuyau->taille = 5;
        tuyau->lien_contenu_case[0][0] = 2;
        tuyau->lien_contenu_case[0][1] = 2;
        tuyau->lien_contenu_case[1][0] = 2;
        tuyau->lien_contenu_case[1][1] = 1;
        tuyau->lien_contenu_case[2][0] = 1;
        tuyau->lien_contenu_case[2][1] = 1;
        tuyau->lien_contenu_case[3][0] = 0;
        tuyau->lien_contenu_case[3][1] = 1;
        tuyau->lien_contenu_case[4][0] = 0;
        tuyau->lien_contenu_case[4][1] = 0;

        for (int i = 0; i < tuyau->taille; i++)
            tuyau->orientation[i] = 0;

        orientation_tuyau(tuyau);

        for (int i = 0; i < tuyau->taille; i++)
        {
            printf("Orientation du tuyau n°%d : %d\n", i, tuyau->orientation[i]);
        }
    }
*/
    return 0;
}

/***************************************************/
/* Init de liste de tuyau                          */
/*                                                 */
/* erreur : 0 - Allocation reussi                  */
/*          1 - Allocation echec                   */
/***************************************************/
int initListeTuyau(listeTuyau_t *l_tuyau)
{
    int erreur = 1; // Erreur
    l_tuyau = (listeTuyau_t *)malloc(sizeof(listeTuyau_t *));
    if (l_tuyau != NULL)
    {
        l_tuyau->taille = 0;
        erreur = 0; // Allocation reussi
    }
    return erreur;
}

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
int constructionTuyau(listeTuyau_t *l_tuyau, map_t *map, int x_souris, int y_souris)
{
    int erreur = 1; // Pas de voisinage

    tuyau_t *tuyau = NULL;
    tuyau = l_tuyau->liste[l_tuyau->taille - 1];
    int x_case_souris,
        y_case_souris;

    x_case_souris = x_souris / 45; // 45 -> taille d'une case en pixel
    y_case_souris = y_souris / 45; // Ils onts pas fait un define ces sauvages

    if (tuyau->taille == 0)
    {
        if (tuyau->entree == NULL) // Clic sur usine car debut tuyau
        {
            if (map->batiment[y_case_souris][x_case_souris] != NULL)
            { // Lien du tuyau d'entre avec la sortie
                tuyau->entree = map->batiment[y_case_souris][x_case_souris];
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
            tuyau->sortie = map->batiment[y_case_souris][x_case_souris];
            erreur = 6; // 6 - Batiment sortie bien selectione
            // Chemin de tuyau connecte
            orientation_tuyau(tuyau);
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
    map->tuyau[y_case][x_case] = tuyau; // Normalement adr de struct tuyau

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
/* malloc d'un nouv tuyau et initialisation a 0    */
/* et ajout dans la liste                          */
/* erreur : 0 tuyau vierge ok / 1 erreur malloc    */
/***************************************************/
int initTuyau(listeTuyau_t *l_tuyau)
{
    int erreur = 1;

    tuyau_t *tuyau = (tuyau_t *)malloc(sizeof(tuyau_t *));

    if (tuyau != NULL)
    {
        erreur = 0;
        tuyau->taille = 0;

        for (int i = 0; i < NB_MAX_CASE; i++)
        {
            tuyau->contenu[i] = aucuneRessource;

            tuyau->lien_contenu_case[i][0] = -1;
            tuyau->lien_contenu_case[i][1] = -1;

            tuyau->orientation[i] = aucuneOrientation;
        }
        // Ajout du tuyau vierge cree dans tab tuyau
        l_tuyau->liste[l_tuyau->taille] = tuyau; /**** ATTENTION ****/
        l_tuyau++;
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
    //tuyau_t *tmp = tuyau;

    free(tuyau); //Libere le tuyau
    return erreur;
}

int check_entree_tuyau(tuyau_t *tuyau)
{
    return (tuyau->contenu[0] == aucuneRessource);
}

int orientation_tuyau(tuyau_t *tuyau)
{
    int erreur = 0;

    //tuyau->orientation[0] = ((tuyau->entree[1] - tuyau->lien_contenu_case[i][1]) < 0) * 1 + ((tuyau->entree[1] - tuyau->lien_contenu_case[i][1]) > 0) * 4 + ((tuyau->entree[0] - tuyau->lien_contenu_case[i][0]) < 0) * 10 + ((tuyau->entree[0] - tuyau->lien_contenu_case[i][0]) > 0) * 7 + ((tuyau->entree[1] - tuyau->lien_contenu_case[i + 1][1]) < 0) * 2 + ((tuyau->entree[1] - tuyau->lien_contenu_case[i + 1][1]) > 0) * 1 + ((tuyau->entree[0] - tuyau->lien_contenu_case[i + 1][0]) < 0) * 2 + ((tuyau->entree[0] - tuyau->lien_contenu_case[i + 1][0]) > 0) * 1;
    //tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][1] - tuyau->sortie[1]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->sortie[1]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->sortie[0]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->sortie[0]) > 0) * 7 + ((tuyau->lien_contenu_case[i][1] - tuyau->sortie[1]) < 0) * 2 + ((tuyau->lien_contenu_case[i][1] - tuyau->sortie[1]) > 0) * 1 + ((tuyau->lien_contenu_case[i][0] - tuyau->sortie[0]) < 0) * 2 + ((tuyau->lien_contenu_case[i][0] - tuyau->sortie[0]) > 0) * 1;

    for (int i = 1; i < tuyau->taille - 1; i++)
    {
        if ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) != 0)
            tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) < 0) * 2 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) > 0) * 1;
        else
            tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) < 0) * 2 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) > 0) * 1;
    }
    return erreur;
}

int decale_dans_tuyau(tuyau_t *tuyau)
{
    int erreur = 0;

    //Test d'insertion d'une matière dans l'usine alors on dit qu'il n'y a plus de ressources dans la case sinon on ne peut décaler la dernière case
    /*if (insertion_dans_usine(tuyau->sortie))
    {
        ajout_stock_usine(tuyau->contenu[tuyau->taille-1]);
        tuyau->contenu[tuyau->taille-1] = aucuneRessource;
    }*/

    if (tuyau->nb_passage % (5 - tuyau->level) == 0)
    {
        for (int i = tuyau->taille - 2; i >= 0; i--)
        {
            if (tuyau->contenu[i + 1] == aucuneRessource)
            {
                tuyau->contenu[i + 1] = tuyau->contenu[i];
                tuyau->contenu[i] = aucuneRessource;
            }
        }
    }
    tuyau->nb_passage++;
    printf("%d\n", tuyau->nb_passage);
    erreur = 1;

    return erreur;
}

int insertion_dans_tuyau(tuyau_t *tuyau, enum Ressource materiau)
{
    int erreur = 0;
    printf("Je veux insérer : %d\n", materiau);

    if (check_entree_tuyau(tuyau))
    {
        tuyau->contenu[0] = materiau;
        erreur = 1;
    }

    // Supprime la connexion avec batiment si elle existe
    //erreur = deleteDoor(tuyau->entree, tuyau);
    //erreur = deleteDoor(tuyau->sortie, tuyau);

    

    return erreur;
}