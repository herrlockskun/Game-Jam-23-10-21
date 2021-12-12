#ifndef TUYAU_H
#define TUYAU_H

#include "const.h"
#include "map.h"
#include "batiment_io.h"

int mainTuyau();

int initListeTuyau(listeTuyau_t **l_tuyau);

int constructionTuyau(listeTuyau_t **p_l_tuyau, map_t **p_map, int x_souris, int y_souris);
int placeTuyau(tuyau_t **p_tuyau, map_t **p_map, int x_case, int y_case);
int checkCaseAdjacente(map_t *map, int x_case_souris, int y_case_souris, int x_case_prec, int y_case_prec);
int initTuyau(listeTuyau_t **l_tuyau);

int annulerConstructionTuyauUnite(listeTuyau_t **p_l_tuyau, map_t *map);

int orientation_tuyau(tuyau_t **p_tuyau);
int check_entree_tuyau(tuyau_t *tuyau);
int decale_dans_tuyau(tuyau_t *tuyau);
int insertion_dans_tuyau(tuyau_t *tuyau, enum Ressource);

int suppressionTuyau(listeTuyau_t **l_tuyau);

int selectionTuyauMap(listeTuyau_t **p_l_tuyau, map_t *map, int x_souris, int y_souris);

int suppressionTotalTuyau(listeTuyau_t **p_l_tuyau, map_t *map);

// Fonction Nathan
void PlaceCoteBatEntree(map_t **p_map, int x_case_prec, int y_case_prec, int x_case_souris, int y_case_souris);
void PlaceCoteBatSortie(map_t **p_map, int x_case_prec, int y_case_prec, int x_case_souris, int y_case_souris);

#endif
