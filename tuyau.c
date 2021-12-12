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

        // Clic construction
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
        (*l_tuyau)->tuyau_select = NULL; // Aucun tuyau selectionne
        erreur = 0;                      // Allocation reussi
    }
    return erreur;
}

/****************************************************/
/*  Construction tuyau                              */
/* 1-selection batiment                             */
/* 2-placer case adjacente batiment                 */
/* 3-placer case adjacente case prec                */
/* 4-selectionner batiment adjacent derniere case   */
/*                                                  */
/* erreur :                                         */
/*         -2 - Bat select level != 0 -> pas const  */
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

    tuyau = *(*p_l_tuyau)->tuyau_select; // Acces au tuyau select
    // tuyau = (*p_l_tuyau)->liste[(*p_l_tuyau)->taille - 1];
    int x_case_souris,
        y_case_souris;

    x_case_souris = x_souris / 45; // 45 -> taille d'une case en pixel
    y_case_souris = y_souris / 45; // Ils onts pas fait un define ces sauvages

    //    printf("x : %d,  y : %d \n", x_case_souris, y_case_souris);
    if (tuyau->level == 0)
    {
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
            {    // Doit placer un tuyau premier
                // Check case adjacente
                x_case_prec = tuyau->entree->pos_x;
                y_case_prec = tuyau->entree->pos_y;
                erreur = checkCaseAdjacente(*p_map, x_case_souris, y_case_souris, x_case_prec, y_case_prec);
                if (erreur == 0) // case clique est du sol
                {                // Place le tuyau adjacent au batiment
                    erreur = placeTuyau(&tuyau, p_map, x_case_souris, y_case_souris);
                    PlaceCoteBatEntree(p_map, x_case_prec, y_case_prec, x_case_souris, y_case_souris);
                }
            }
        }
        else // Taille != 0
        {
            // Check case adjacente
            x_case_prec = tuyau->lien_contenu_case[tuyau->taille - 1][0];
            y_case_prec = tuyau->lien_contenu_case[tuyau->taille - 1][1];
            erreur = checkCaseAdjacente(*p_map, x_case_souris, y_case_souris, x_case_prec, y_case_prec);
            if (erreur == 4 &&                                                     // Case souris -> batiment
                tuyau->entree != (*p_map)->batiment[y_case_souris][x_case_souris]) // Bat != bat entree
            {                                                                      // Selectionne le dernier batiment
                tuyau->sortie = (*p_map)->batiment[y_case_souris][x_case_souris];
                erreur = 6; // 6 - Batiment sortie bien selectione
                // Chemin de tuyau connecte
                orientation_tuyau(&tuyau);
                PlaceCoteBatSortie(p_map, x_case_prec, y_case_prec, x_case_souris, y_case_souris);
                tuyau->level = 1; // Tuyau ok -> level 1

                (*p_l_tuyau)->tuyau_select = NULL; // Deselection du tuyau
            }
            else if (erreur == 0) // case clique est du sol
            {
                // Place le tuyau adjacent au tuyau precedent
                erreur = placeTuyau(&tuyau, p_map, x_case_souris, y_case_souris);
            }
        }
    }
    else
    {                // Level pas a 0 -> bat pas en construction
        erreur = -2; // Bat mal selectionne
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
                if (map->vierge[y_case_souris][x_case_souris] != montagne) // Pas de montagne -> sol
                {
                    erreur = 0; // Case souris -> sol
                }
                else
                {
                    erreur = 2; // Case souris -> pas sol ou case posable
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
    // printf("erreur : %d\n\n", erreur);
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

    (*l_tuyau)->liste[(*l_tuyau)->taille] = (tuyau_t *)malloc(sizeof(tuyau_t));
    tuyau_t *tuyau = (*l_tuyau)->liste[(*l_tuyau)->taille];

    if (tuyau != NULL)
    {
        erreur = 0;
        tuyau->taille = 0;
        tuyau->level = 0;        // level = 0 quand tuyau pas encore ok
        tuyau->cote_entree = -1; // Pas encore de bat co
        tuyau->cote_sortie = -1; // Pas encore de bat co

        tuyau->entree = NULL; // Pas encore de bat co
        tuyau->sortie = NULL; // Pas encore de bat co

        for (int i = 0; i < NB_MAX_CASE; i++)
        {
            tuyau->contenu[i] = aucuneRessource;

            tuyau->lien_contenu_case[i][0] = -1;
            tuyau->lien_contenu_case[i][1] = -1;

            tuyau->orientation[i] = aucuneOrientation;
        }
        // Ajout du tuyau vierge cree dans tab tuyau
        // (*l_tuyau)->liste[(*l_tuyau)->taille] = tuyau; /**** ATTENTION ****/
        (*l_tuyau)->tuyau_select = &(*l_tuyau)->liste[(*l_tuyau)->taille];
        (*l_tuyau)->taille++;
    }

    return erreur;
}

/***************************************************/
/* annulerConstructionTuyauUnite :                 */
/*      annule la dernière unite tuyau construite  */
/*  OU  annule le dernier batiment entree select   */
/*                                                 */
/* entree : liste de tuyau                         */
/*                                                 */
/* erreur : 0 - Bizarre ne devrait pas rester a 0  */
/*          1 - Batiment entree bien deco (succes) */
/*          2 - Batiment entree pas deco (...)     */
/*          3 - Pas de batiment entree a deco      */
/*          4 - Derniere unite tuyau bien supp     */
/*          5 - Batiment sortie bien deco (succes) */
/*          6 - Batiment entree pas deco (echec)   */
/*          7 - Pas de batiment sortie a deco (NON)*/
/*                                                 */
/* sortie : erreur = 1 -> unite+entree supprime    */
/***************************************************/
int annulerConstructionTuyauUnite(listeTuyau_t **p_l_tuyau, map_t **p_map)
{
    int erreur = 0;

    // Recuperation du dernier tuyau
    tuyau_t *tuyau_select = *((*p_l_tuyau)->tuyau_select);

    int x_unite, y_unite;

    if (tuyau_select->level == 0)
    { // Si le tuyau est toujours en construction

        int taille_tuyau = tuyau_select->taille;

        if (taille_tuyau == 0)
        { // Pas d'unite de tuyau
            if (tuyau_select->entree != NULL)
            { // Que bat entree selectionne
                // supprimer la porte
                erreur = deleteDoor(tuyau_select->entree, tuyau_select->cote_entree);
                if (erreur == 0)
                {
                    // tuyau_select->entree = NULL; // Supprime la connexion avec bat
                    erreur = 1; // Batiment entree correctement deconnecte
                }
                else
                { // Bat entree pas deco, mais peut etre pas besoin de le deco s il a pas ete co

                    erreur = 2;
                }
                /* a supp dans la liste des tuyau */
                suppressionTuyau(p_l_tuyau); // semble ok, mais suppression avec reoganisation de la liste tuyau pas vraiment testee
            }
            else
            { // Pas de batiment entree a deco
                erreur = 3;
                suppressionTuyau(p_l_tuyau); // semble ok, mais suppression avec reoganisation de la liste tuyau pas vraiment testee
            }
        }
        else
        { // Unite de tuyau a supp

            // Recuperation coordonnees du dernier unite tuyau
            x_unite = tuyau_select->lien_contenu_case[taille_tuyau - 1][0];
            y_unite = tuyau_select->lien_contenu_case[taille_tuyau - 1][1];

            // Effacement de la derniere unite de tuyau dans le tuyau lui meme
            taille_tuyau -= 1; // Decremente la taille
            tuyau_select->lien_contenu_case[taille_tuyau][0] = -1;
            tuyau_select->lien_contenu_case[taille_tuyau][1] = -1;
            tuyau_select->orientation[taille_tuyau] = aucuneOrientation; // Normalement deja avec aucune orientation

            tuyau_select->taille = taille_tuyau; // affecte la taille decremente du tuyau

            // Effacement de la derniere unite de tuyau dans la map
            (*p_map)->tuyau[y_unite][x_unite] = NULL;

            erreur = 4;
        }
    }
    else // level > 1
    {    // Tuyau deja construit entierement

        if (tuyau_select->sortie != NULL)
        { // Que bat sortie selectionne
            // supprimer la porte
            erreur = deleteDoor(tuyau_select->sortie, tuyau_select->cote_sortie);
            if (erreur == 0)
            {
                tuyau_select->sortie = NULL; // Supprime la connexion avec bat
                erreur = 5;                  // Batiment sortie correctement deconnecte
                tuyau_select->level = 0;     // Passe le tuyau en non fini
            }
            else
            {
                erreur = 6; // Bat sortie pas deco
            }
        }
        else
        {
            erreur = 7; // Pas de batiment sortie a deco
            // Pas normale car tuyau avec level = 1 -> tuyau correctement forme
        }
    }

    return erreur;
}

/***************************************************/
/* suppressionTuyau : free et reorganise la liste  */
/*                    de tuyau si besoin pour      */
/*                    garder la contiguite         */
/*                                                 */
/* entree : adr d'un pointeur liste tuyau          */
/*                                                 */
/* erreur : 0 - supp dans liste du dernier tuyau   */
/*          1 - supp d'un tuyau et decalge         */
/*                                                 */
/***************************************************/
int suppressionTuyau(listeTuyau_t **p_l_tuyau)
{
    int erreur = 0; // Si aucun mvt dans la liste

    /*** Test si le tuyau a supprimer n'est pas le dernier de la liste ***/
    /*** Adresse pointee par select est diff de adresse case de la liste contenant le dernier tuyau ***/
    if (&((*p_l_tuyau)->liste[(*p_l_tuyau)->taille - 1]) != (*p_l_tuyau)->tuyau_select)
    { // Pas le dernier de la liste
        // Il faut copier le dernier a sa place
        *(*p_l_tuyau)->tuyau_select = (*p_l_tuyau)->liste[(*p_l_tuyau)->taille - 1];
        erreur = 1; // Mvt dans la liste -> liste contigue
    }
    free((*(*p_l_tuyau)->tuyau_select)); // Normalement free du tuyau
    *(*p_l_tuyau)->tuyau_select = NULL;  // Pointeur dans liste
    (*p_l_tuyau)->tuyau_select = NULL;   // Selection de tuyau
    (*p_l_tuyau)->taille--;

    return erreur;
}

/***************************************************/
/* selectionTuyauMap : Check case de map pour      */
/*                     select  le tuyau associe    */
/*                                                 */
/* entree : adr d'un pointeur liste tuyau          */
/*          map                                    */
/*          2 entiers : postion souris en pixel    */
/*                                                 */
/* erreur : 0 - Pas de tuyau selectionne           */
/*          1 - existant tuyau et selection        */
/***************************************************/
int selectionTuyauMap(listeTuyau_t **p_l_tuyau, map_t *map, int x_souris, int y_souris)
{
    int erreur = 0; // Pas de tuyau selectionne
    int x_case_souris, y_case_souris;
    x_case_souris = x_souris / TAILLE_CASE_MAP;
    y_case_souris = y_souris / TAILLE_CASE_MAP;

    // Select le tuyau relie a la case cliquee
    (*p_l_tuyau)->tuyau_select = map->tuyau[y_case_souris][x_case_souris];

    if ((*p_l_tuyau)->tuyau_select != NULL)
    {
        erreur = 1; // existant tuyau et selection ok
    }

    return erreur;
}

/***************************************************/
/* suppressionTotalTuyau :       */
/*                         */
/*                                                 */
/* entree : adr d'un pointeur liste tuyau          */
/*          map                                    */
/*                                                 */
/* erreur : 0 -            */
/*          1 -         */
/***************************************************/
int suppressionTotalTuyau(listeTuyau_t **p_l_tuyau, map_t **p_map)
{
    int erreur = 1; // Tuyau pas encore construit -> level = 0

    while ((*p_l_tuyau)->tuyau_select != NULL)
    {
        annulerConstructionTuyauUnite(p_l_tuyau, p_map);
    }
    return erreur;
}

int check_entree_tuyau(tuyau_t *tuyau)
{
    return (tuyau->contenu[0] == aucuneRessource);
}

/***************************************************/
/* orientation_tuyau : calcul l'orientation des    */
/*                     des bouts de tuyau          */
/* fonction appelee quand le tuyau est ok          */
/* ie: bat entree - tuyau -...- tuyau - bat sortie */
/*                                                 */
/* entree : un pointeur de tuyau                   */
/*                                                 */
/* sortie : 0 pas de signification                 */
/***************************************************/
int orientation_tuyau(tuyau_t **p_tuyau)
{
    int erreur = 0;

    // for (int i = 1; i < tuyau->taille - 1; i++)
    // // for (int i = 0; i < tuyau->taille; i++)
    // {
    //     if ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) != 0)
    //         tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) < 0) * 2 + ((tuyau->lien_contenu_case[i][1] - tuyau->lien_contenu_case[i + 1][1]) > 0) * 1;
    //     else
    //         tuyau->orientation[i] = ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) < 0) * 1 + ((tuyau->lien_contenu_case[i - 1][0] - tuyau->lien_contenu_case[i][0]) > 0) * 4 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) < 0) * 10 + ((tuyau->lien_contenu_case[i - 1][1] - tuyau->lien_contenu_case[i][1]) > 0) * 7 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) < 0) * 2 + ((tuyau->lien_contenu_case[i][0] - tuyau->lien_contenu_case[i + 1][0]) > 0) * 1;
    // }

    int x_prec, y_prec, x_suiv, y_suiv;
    // int interieur; // Variable qui permet de savoir
    //                // comment parcourir vect x->y / y->x
    int x_cour, y_cour;
    int x_vect, y_vect;
    enum TuyauOrientation orientation = aucuneOrientation;

    for (int k = 0; k < (*p_tuyau)->taille; k++)
    {
        // Regarde la position de l'item precedent
        if (k == 0) // Premier tuyau
        {           // Connecter par rapport au batiment entree
            x_prec = (*p_tuyau)->entree->pos_x;
            y_prec = (*p_tuyau)->entree->pos_y;
        }
        else // Deja un bout de tuyau avant
        {    // Connecter par rapport au tuyau precedent
            x_prec = (*p_tuyau)->lien_contenu_case[k - 1][0];
            y_prec = (*p_tuyau)->lien_contenu_case[k - 1][1];
        }

        // Regarde la position de l'item suivant
        if (k + 1 == (*p_tuyau)->taille) // Fin du tuyau
        {                                // Connecter par rapport au batiment de sortie
            x_suiv = (*p_tuyau)->sortie->pos_x;
            y_suiv = (*p_tuyau)->sortie->pos_y;
        }
        else
        {
            x_suiv = (*p_tuyau)->lien_contenu_case[k + 1][0];
            y_suiv = (*p_tuyau)->lien_contenu_case[k + 1][1];
        }

        // // Regarde la position du tuyau a orienter
        x_cour = (*p_tuyau)->lien_contenu_case[k][0];
        y_cour = (*p_tuyau)->lien_contenu_case[k][1];

        /*** Calcul de l'orientation ***/
        x_vect = x_suiv - x_prec;
        y_vect = y_suiv - y_prec;

        if (x_vect == 0 && y_vect == 2)
            orientation = bas;
        else if (x_vect == -1 && y_vect == 1 && y_prec + y_vect == y_cour)
            orientation = bas_gauche;
        else if (x_vect == 1 && y_vect == 1 && y_prec + y_vect == y_cour)
            orientation = bas_droite;
        else if (x_vect == 0 && y_vect == -2)
            orientation = haut;
        else if (x_vect == -1 && y_vect == -1 && y_prec + y_vect == y_cour)
            orientation = haut_gauche;
        else if (x_vect == 1 && y_vect == -1 && y_prec + y_vect == y_cour)
            orientation = haut_droite;
        else if (x_vect == -2 && y_vect == 0)
            orientation = gauche;
        else if (x_vect == -1 && y_vect == -1)
            orientation = gauche_haut;
        else if (x_vect == -1 && y_vect == 1)
            orientation = gauche_bas;
        else if (x_vect == 2 && y_vect == 0)
            orientation = droite;
        else if (x_vect == 1 && y_vect == -1)
            orientation = droite_haut;
        else if (x_vect == 1 && y_vect == 1)
            orientation = droite_bas;

        (*p_tuyau)->orientation[k] = orientation;
    }

    return erreur;
}

/***************************************************/
/* decalage_l_tuyau : applique le decalage des     */
/*                    des ressources dans tous     */
/*                    les tuyaux                   */
/*                                                 */
/* entree : liste de tuyau                         */
/*                                                 */
/* sortie : rien                 */
/***************************************************/
void decalage_l_tuyau(listeTuyau_t *l_tuyau)
{
    for (int i = 0; i < l_tuyau->taille; i++)
    {
        decale_dans_tuyau(l_tuyau->liste[i]);
    }
}

int decale_dans_tuyau(tuyau_t *tuyau)
{
    int erreur = 0;

    // Test d'insertion d'une matière dans l'usine alors on dit qu'il n'y a plus de ressources dans la case sinon on ne peut décaler la dernière case
    // if (tuyau->contenu[tuyau->taille - 1] != aucuneRessource && stockEntreePlein(tuyau->sortie))
    if (tuyau->contenu[tuyau->taille - 1] != aucuneRessource && 1)
    {
        // Fonction n existe pas
        // ajout_stock_usine(tuyau->contenu[tuyau->taille - 1]);
        tuyau->contenu[tuyau->taille - 1] = aucuneRessource;
    }

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
    // erreur = deleteDoor(tuyau->entree, tuyau);
    // erreur = deleteDoor(tuyau->sortie, tuyau);

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
