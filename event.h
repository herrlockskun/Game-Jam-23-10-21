#ifndef event_gard
#define event_gard

#include "const.h"
#include "usine_brique.h"

void eventsec(int posx, int posy, enum EtatJeu *status,
              listeTuyau_t **p_l_tuyau);

void mainevent(int posx, int posy, enum EtatJeu *status, int *money,
               listeTuyau_t **p_l_tuyau,
               map_t **p_map);

#endif