#include "tests_batiments.h"

void testCreation()
{
    batiment_io_t * batiment = NULL;
    int erreur = 0;

    newBatiment(&batiment , 18 , 24 , 1 , 1);
    
    printf("pos_x = %d\n" , batiment->pos_x);
    erreur = newDoor(batiment , 2 , 0);
    printf("type port0 = %d\n" , batiment->door_T[2]);
    deleteDoor(batiment , 0);

    deleteBatiment(batiment);
    printf("\n");
}

void testCreationUsine()
{
    batiment_io_t * tab_bat[20][20];


    newUsine_brique(tab_bat, 15 , 12);
    newDoor(tab_bat[15][12] , 1 , 0);
    fctUsine_Brique(tab_bat[15][12]);
    printf("pos_x = %d\n" , tab_bat[15][12]->pos_x);
    printf("type port0 = %d\n" , tab_bat[15][12]->door_T[1]);

    printf("\nstock entree = %d\n" , tab_bat[15][12]->stock_entree[0]);
    printf("stock sortie = %d\n" , tab_bat[15][12]->stock_sortie);
    printf("reception ressources entree\n");
    tab_bat[15][12]->stock_entree[0] = 2;
    printf("stock entree = %d\n" , tab_bat[15][12]->stock_entree[0]);
    printf("stock sortie = %d\n" , tab_bat[15][12]->stock_sortie);
    printf("processing\n");
    fctUsine_Brique(tab_bat[15][12]);
    printf("stock entree = %d\n" , tab_bat[15][12]->stock_entree[0]);
    printf("stock sortie = %d\n" , tab_bat[15][12]->stock_sortie);

    newDoor(tab_bat[15][12] , 2 , 1);
    printf("type port2 = %d\n" , tab_bat[15][12]->door_T[2]);
    printf("nb sortie = %d\n" , tab_bat[15][12]->nb_sortie);
    fctUsine_Brique(tab_bat[15][12]);
    printf("apres ajout d'une sortie\n");
    printf("stock entree = %d\n" , tab_bat[15][12]->stock_entree[0]);
    printf("stock sortie = %d\n" , tab_bat[15][12]->stock_sortie);

    deleteDoor(tab_bat[15][12] , 0);
    deleteBatiment(tab_bat[15][12]);
}