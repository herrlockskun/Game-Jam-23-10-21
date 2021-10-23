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
    map[0][1] = tuyau;
    map[0][2] = tuyau;
    map[0][3] = tuyau;
    map[1][3] = tuyau;*/

    tuyau_t *tuyau = (tuyau_t *)malloc(sizeof(tuyau_t));
    if (tuyau)
    {
        tuyau->taille = 5;
        for (int i = 0; i < tuyau->taille; i++)
        {
            tuyau->contenu[i] = aucuneRessource;
        }

        print_tuyau(tuyau);

        insertion(tuyau, titane);

        print_tuyau(tuyau);

        insertion(tuyau, fer);
        insertion(tuyau, eau);
        insertion(tuyau, titane);
        insertion(tuyau, fer);
        insertion(tuyau, fer);

        print_tuyau(tuyau);
    }

    //print_map_console(map);

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

void print_tuyau(tuyau_t *tuyau)
{
    printf("Voici la composition du tuyau :\n");
    for (int i = 0; i < tuyau->taille; i++)
    {
        printf("Voici l'élément n°%d : %d\n", i, tuyau->contenu[i]);
    }
}

int check_entree(tuyau_t *tuyau)
{
    return (tuyau->contenu[0] == aucuneRessource);
}

int decale(tuyau_t *tuyau)
{
    int erreur = 0;

    //Test d'insertion d'une matière dans l'usine alors on dit qu'il n'y a plus de ressources dans la case sinon on ne peut décaler la dernière case
    /*if (insertion_usine(tuyau->sortie))
    {
        ajout_stock(tuyau->contenu[tuyau->taille-1]);
        tuyau->contenu[tuyau->taille-1] = aucuneRessource;
    }*/

    for (int i = tuyau->taille - 2; i >= 0; i--)
    {
        if (tuyau->contenu[i + 1] == aucuneRessource)
        {
            tuyau->contenu[i + 1] = tuyau->contenu[i];
            tuyau->contenu[i] = aucuneRessource;
        }
    }

    erreur = 1;

    return erreur;
}

int insertion(tuyau_t *tuyau, enum Ressource materiau)
{
    int erreur = 0;

    erreur = decale(tuyau);

    if (check_entree(tuyau))
    {
        tuyau->contenu[0] = materiau;
        erreur = 1;
    }

    return erreur;
}