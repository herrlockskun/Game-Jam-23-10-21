#include "tuyau.h"

int mainTuyau()
{
    int erreur;
    listeTuyau_t *l = NULL;
    erreur = initListeTuyau(&l);

    map_t *map = NULL;
    map = malloc(sizeof(map_t));
    for (int i = 0; i < TAILLE_MAP; ++i)
    {
        for (int j = 0; j < TAILLE_MAP; j++)
        {
            map->batiment[i][j] = NULL;
            map->tuyau[i][j] = NULL;
        }
    }
    batiment_io_t *bat1 = malloc(sizeof(batiment_io_t));
    batiment_io_t *bat2 = malloc(sizeof(batiment_io_t));
    bat1->pos_x = 0;
    bat1->pos_y = 0;
    bat2->pos_x = 2;
    bat2->pos_y = 0;

    map->batiment[0][0] = bat1;
    map->batiment[0][2] = bat2;

    if (erreur == 0)
    {

        //Clic construction
        erreur = initTuyau(&l);

        if (erreur == 0)
        {
            erreur = constructionTuyau(&l, &map, 5, 5);

            if (erreur == 5)
            {
                printf("1-bat bien select\n");
                erreur = constructionTuyau(&l, &map, 48, 5);
                if (erreur == 0)
                {
                    printf("2-tuyau bien place\n");
                    erreur = constructionTuyau(&l, &map, 95, 5);
                    if (erreur == 6)
                    {
                        printf("3-bat fin bien select");
                    }
                }
            }
        }
    }
    printf("batiment entree x %d\n", l->liste[0]->entree->pos_x);
    printf("batiment entree y %d\n", l->liste[0]->entree->pos_y);

    printf("\nadresse du tuyau %p\n", l->liste[0]);
    printf("tuyau unite x %d\n", l->liste[0]->lien_contenu_case[0][0]);
    printf("tuyau unite y %d\n", l->liste[0]->lien_contenu_case[0][1]);
    printf("tuyau orientation %d\n", l->liste[0]->orientation[0]);

    printf("\nbatiment sortie x %d\n", l->liste[0]->sortie->pos_x);
    printf("batiment sortie y %d\n", l->liste[0]->sortie->pos_y);
    return 0;
}

/***************************************************/
/* Init de liste de tuyau                          */
/*                                                 */
/* erreur : 0 - Allocation reussi                  */
/*          1 - Allocation echec                   */
/***************************************************/
int initListeTuyau(listeTuyau_t **l_tuyau)
{
    int erreur = 1; // Erreur
    *l_tuyau = (listeTuyau_t *)malloc(sizeof(listeTuyau_t));
    if (l_tuyau != NULL)
    {
        (*l_tuyau)->taille = 0;

        for (int i = 0; i < NB_MAX_TUYAU; i++)
        {
            (*l_tuyau)->liste[i] = NULL;
        }

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
int constructionTuyau(listeTuyau_t **p_l_tuyau, map_t **p_map, int x_souris, int y_souris)
{
    int erreur = 1; // Pas de voisinage

    int x_case_prec, y_case_prec;

    tuyau_t *tuyau = NULL;
    tuyau = (*p_l_tuyau)->liste[(*p_l_tuyau)->taille - 1];
    int x_case_souris,
        y_case_souris;

    x_case_souris = x_souris / 45; // 45 -> taille d'une case en pixel
    y_case_souris = y_souris / 45; // Ils onts pas fait un define ces sauvages

    //    printf("x : %d,  y : %d \n", x_case_souris, y_case_souris);

    if (tuyau->taille == 0)
    {
        if (tuyau->entree == NULL) // Clic sur usine car debut tuyau
        {

            if ((*p_map)->batiment[y_case_souris][x_case_souris] != NULL)
            { // Lien du tuyau d'entre avec la sortie
                tuyau->entree = (*p_map)->batiment[y_case_souris][x_case_souris];
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
            x_case_prec = tuyau->entree->pos_x;
            y_case_prec = tuyau->entree->pos_y;
            erreur = checkCaseAdjacente(*p_map, x_case_souris, y_case_souris, x_case_prec, y_case_prec);
            // Place le tuyau adjacent au batiment
            erreur = placeTuyau(&tuyau, p_map, x_case_souris, y_case_souris);
            PlaceCoteBatEntree(p_map, x_case_prec, y_case_prec, x_case_souris, y_case_souris);
            printf("bon cote\n");
        }
    }
    else // Taille != 0
    {
        // Check case adjacente
        x_case_prec = tuyau->lien_contenu_case[tuyau->taille - 1][0];
        y_case_prec = tuyau->lien_contenu_case[tuyau->taille - 1][1];
        erreur = checkCaseAdjacente(*p_map, x_case_souris, y_case_souris, x_case_prec, y_case_prec);
        if (erreur == 4) // Case souris -> batiment
        {                // Selectionne le dernier batiment
            tuyau->sortie = (*p_map)->batiment[y_case_souris][x_case_souris];
            erreur = 6; // 6 - Batiment sortie bien selectione
            // Chemin de tuyau connecte
            orientation_tuyau(tuyau);
            PlaceCoteBatSortie(p_map, x_case_prec, y_case_prec, x_case_souris, y_case_souris);
            tuyau->level = 1; // Tuyau ok -> level 1
        }
        else
        {
            // Place le tuyau adjacent au tuyau precedent
            erreur = placeTuyau(&tuyau, p_map, x_case_souris, y_case_souris);
        }
    }
    return erreur;
}

/****************************************************/
/* Place une unite de tuyau sur la case d'la souris */
/* Place le pointeur vers le tuyau                  */
/****************************************************/
int placeTuyau(tuyau_t **p_tuyau, map_t **p_map, int x_case, int y_case)
{
    (*p_tuyau)->lien_contenu_case[(*p_tuyau)->taille][0] = x_case;
    (*p_tuyau)->lien_contenu_case[(*p_tuyau)->taille][1] = y_case;
    (*p_map)->tuyau[y_case][x_case] = p_tuyau; // Normalement adr de struct tuyau
    (*p_tuyau)->taille++;

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
int initTuyau(listeTuyau_t **l_tuyau)
{
    int erreur = 1;

    tuyau_t *tuyau = (tuyau_t *)malloc(sizeof(tuyau_t));

    if (tuyau != NULL)
    {
        erreur = 0;
        tuyau->taille = 0;
        tuyau->level = 0; // level = 0 quand tuyau pas encore ok
        tuyau->cote_entree = -1;
        tuyau->cote_sortie = -1;

        tuyau->entree = NULL;
        tuyau->sortie = NULL;

        for (int i = 0; i < NB_MAX_CASE; i++)
        {
            tuyau->contenu[i] = aucuneRessource;

            tuyau->lien_contenu_case[i][0] = -1;
            tuyau->lien_contenu_case[i][1] = -1;

            tuyau->orientation[i] = aucuneOrientation;
        }
        // Ajout du tuyau vierge cree dans tab tuyau
        (*l_tuyau)->liste[(*l_tuyau)->taille] = tuyau; /**** ATTENTION ****/
        (*l_tuyau)->taille++;
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
    // for (int i = 0; i < tuyau->taille; i++)
    {
        if ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) != 0)
            tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) < 0) * 2 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) > 0) * 1;
        else
            tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) < 0) * 2 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) > 0) * 1;
    }

    int x_usine, y_usine, x_tuyau, y_tuyau;

    /*** Gestion orientation 1er tuyau-usine entree ***/

    // x_usine = tuyau.

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

/******** Fonction Nathan ***********/

void PlaceCoteBatEntree(map_t **p_map, int x_case_prec, int y_case_prec, int x_case_souris, int y_case_souris)
{
    if (y_case_souris - y_case_prec == 1)
    {
        (*(*p_map)->tuyau[y_case_souris][x_case_souris])->cote_entree = 0;
        newDoor((*p_map)->batiment[y_case_prec][x_case_prec], 0, 0);
    }
    else if (y_case_souris - y_case_prec == -1)
    {
        (*(*p_map)->tuyau[y_case_souris][x_case_souris])->cote_entree = 2;
        newDoor((*p_map)->batiment[y_case_prec][x_case_prec], 2, 0);
    }
    else if (x_case_souris - x_case_prec == 1)
    {
        (*(*p_map)->tuyau[y_case_souris][x_case_souris])->cote_entree = 1;
        newDoor((*p_map)->batiment[y_case_prec][x_case_prec], 1, 0);
    }
    else if (x_case_souris - x_case_prec == -1)
    {
        (*(*p_map)->tuyau[y_case_souris][x_case_souris])->cote_entree = 3;
        newDoor((*p_map)->batiment[y_case_prec][x_case_prec], 3, 0);
    }
}

void PlaceCoteBatSortie(map_t **p_map, int x_case_prec, int y_case_prec, int x_case_souris, int y_case_souris)
{
    if (y_case_souris - y_case_prec == -1)
    {
        (*(*p_map)->tuyau[y_case_prec][x_case_prec])->cote_entree = 0;
        newDoor((*p_map)->batiment[y_case_souris][x_case_souris], 0, 1);
    }
    else if (y_case_souris - y_case_prec == 1)
    {
        (*(*p_map)->tuyau[y_case_prec][x_case_prec])->cote_entree = 2;
        newDoor((*p_map)->batiment[y_case_souris][x_case_souris], 2, 1);
    }
    else if (x_case_souris - x_case_prec == -1)
    {
        (*(*p_map)->tuyau[y_case_prec][x_case_prec])->cote_entree = 1;
        newDoor((*p_map)->batiment[y_case_souris][x_case_souris], 1, 1);
    }
    else if (x_case_souris - x_case_prec == 1)
    {
        (*(*p_map)->tuyau[y_case_prec][x_case_prec])->cote_entree = 3;
        newDoor((*p_map)->batiment[y_case_souris][x_case_souris], 3, 1);
    }
}
