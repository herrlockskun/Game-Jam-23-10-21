#ifndef list_c_tuyau_h
#define list_c_tuyau_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "tuyau.h"

struct cellule
{
  tuyau_t * val;
  struct cellule * prec;
  struct cellule * suiv;
};
typedef struct cellule cell;

struct liste
{
  cell * tete;
};
typedef struct liste liste;

liste creeListe();

void insereTete(liste* l, tuyau_t *tuyau);

void libereListe(liste *l);

void afficheListe(liste l);

void adjCel(cell** prevCel,cell* nouv);

void supprCel(cell** prevCel);
void supprCelBis(cell *cel);

cell** rechPrec(cell ** head, tuyau_t* v);

cell* creeCel();


#endif
