#include "tuyau.h"

int mainTuyau()
{
    // Init map
    /*enum CaseMap map[TAILLE_MAP][TAILLE_MAP];

    // Full sol
    for (int i = 0; i < TAILLE_MAP; i++)
    {
        for (int j = 0; j < TAILLE_MAP; j++)
        {
            map[i][j] = sol;
        }
    }
    map[2][1] = tuyau;
    map[2][2] = tuyau;
    map[2][3] = tuyau;
    map[3][3] = tuyau;

    print_map_console(map);*/

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

    erreur = 1;

    return erreur;
}

int check_entree_tuyau(tuyau_t *tuyau)
{
    return (tuyau->contenu[0] == aucuneRessource);
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

    return erreur;
}