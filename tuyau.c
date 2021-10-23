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
/*      */
/***************************************************/
int creationTuyau(tuyau_t *tuyau)
{
    int erreur = 1;
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