#include "liste_c_tuyau.h"

/*------------------------------------------------------------*/
/* Cycle de vie d'une liste simplement chainee                */
/*                                                            */
/*------------------------------------------------------------*/

liste creeListe()
{
  liste l;
  l.tete = NULL;
  return l;
}

cell *creeCel()
{
  cell *nouv = NULL;

  nouv = (cell *)malloc(sizeof(cell));

  if (nouv == NULL)
  {
    printf("Erreur malloc : creeCel\n");
  }
  else
  {
    nouv->prec = NULL;
    nouv->suiv = NULL;
  }
  return nouv;
}

void insereTete(liste *l, tuyau_t *tuyau)
{
  cell *nouv = creeCel();
  if (nouv == NULL)
  {
    printf("Erreur malloc : creeCel\n");
  }
  else
  {
    nouv->val = tuyau;
    nouv->prec = NULL;
    nouv->suiv = l->tete;
    l->tete = nouv;
  }
}

void libereListe(liste *l)
{
  cell **prevCel = &(l->tete);
  cell *currCel = l->tete;
  while (currCel != NULL)
  {
    *prevCel = currCel;
    currCel = currCel->suiv;
    free(*prevCel);
  }
}

void afficheListe(liste l)
{
  cell *currCel = l.tete;
  printf("Liste \n");
  while (currCel != NULL)
  {
    //printf("val %lf\tusine %d\tperiode %d\n", currCel->val, currCel->usine, currCel->periode);
    //currCel = currCel->suiv;
  }
  printf("\n");
}

cell **rechPrec(cell **head, tuyau_t *v)
{
  cell **prevCel = head;
  cell *currCel = *prevCel;
  while (currCel != NULL && currCel->val > v)
  {
    prevCel = &currCel->suiv;
    currCel = currCel->suiv;
  }
  return prevCel;
}

void adjCel(cell **prevCel, cell *nouv)
{
  nouv->suiv = *prevCel;
  *prevCel = nouv;
}

void supprCel(cell **prevCel)
{
  if (*prevCel != NULL)
  {
    cell *suppr = *prevCel;
    *prevCel = suppr->suiv;
    free(suppr);
  }
}

void supprCelBis(cell *cel)
{
  if (cel != NULL)
  {

    cel->prec->suiv = cel->suiv;
    cel->suiv->prec = cel->prec;
    free(cel);
  }
}

