#include <stdio.h>
#include <stdlib.h>
#include "batiment_io.h"

int initBatiment(batiment_io_t **batiment, int nb_s_entree)
{
    int erreur = 0;
    *batiment = NULL;

    *batiment = (batiment_io_t *)malloc(sizeof(batiment_io_t));
    if (*batiment != NULL)
    {
        (*batiment)->stock_entree = (int *)malloc(sizeof(int) * nb_s_entree);
        if ((*batiment)->stock_entree == NULL)
        {
            erreur = 1;
        }
    }
    else
    {
        erreur = 1;
    }

    return erreur;
}

void newBatiment(batiment_io_t **batiment, int pos_x, int pos_y, int nb_s_entree, int rang)
{
    int erreur = 0;
    int i;

    erreur = initBatiment(batiment, nb_s_entree);
    if (!erreur)
    {
        (*batiment)->pos_x = pos_x;
        (*batiment)->pos_y = pos_y;
        (*batiment)->rang = rang;
        (*batiment)->niveau = 1;
        (*batiment)->nb_sortie = 0;
        (*batiment)->next_s = 0;
        (*batiment)->stock_sortie = 0;
        for (i = 0; i < 4; i++)
        {
            (*batiment)->door_T[i] = -1;
        }
    }
    else
    {
        printf("Erreur a la creation du batiment\n");
    }
}

void deleteBatiment(batiment_io_t *batiment)
{
    free(batiment->stock_entree);
    free(batiment);
}

int newDoor(batiment_io_t *batiment, int side, int type)
{
    int erreur = 0;

    if (side < 4 && side >= 0)
    {
        batiment->door_T[side] = type;
    }
    else
    {
        erreur = 1;
    }

    // if (!erreur && type == 1)
    if (!erreur)
    {
        batiment->nb_sortie++;
        printf("erreur new door %d , porte cree\n", erreur);
    }

    return erreur;
}

int deleteDoor(batiment_io_t *batiment, int side)
{
    int erreur = 0;
    int type = -1;

    if (batiment != NULL)
    {
        if (side >= 0 && side < 4)
        {
            type = batiment->door_T[side];
            batiment->door_T[side] = -1;
        }
        else
        {
            erreur = 1;
        }
    }
    else
    {
        erreur = 2;
    }

    // if (!erreur && type == 1)
    if (!erreur)
    {
        batiment->nb_sortie--;
        printf("erreur delete door %d ,porte detruite \n", type);
    }

    return erreur;
}

int stockEntreePlein(batiment_io_t *batiment, int stock, int max)
{
    return (batiment->stock_entree[stock] == max);
}

int stockSortieVide(batiment_io_t *batiment)
{
    return (batiment->stock_sortie == 0);
}

int destRessource(batiment_io_t *batiment)
{
    int connection = -1;
    int i = 0;
    int j = 0;

    if (batiment->nb_sortie != 0 && !stockSortieVide(batiment))
    {
        batiment->next_s = (batiment->next_s + 1) % batiment->nb_sortie;

        while (i < 4 && j < batiment->next_s)
        {
            if (batiment->door_T[i] == 1)
            {
                j++;
            }
            i++;
        }
        if (i < 4)
        {
            connection = i;
        }
        else
        {
            connection = -2;
        }
    }

    return connection;
}