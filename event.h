#ifndef event_gard
#define event_gard

#include "const.h"
#include "usine_brique.h"

void eventsec(int posx, int posy, int *status);

void mainevent(int posx, int posy, int *status, int *money, batiment_io_t *carte[20][20]);

#endif