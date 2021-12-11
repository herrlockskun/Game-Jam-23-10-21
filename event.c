#include "event.h"

void eventsec(int posx, int posy, int *status)
{
    if (posx < 900)
    {
        //a faire plus tard
        *status = 0;
    }
    if (posx > 900)
    {
        if (posy > 750 && posy < 830)
        {
            if (posx > 910 && posx < 990)
            {
                *status = 1;
            }
            if (posx > 1010 && posx < 1090)
            {
                *status = 2;
            }
            if (posx > 1110 && posx < 1190)
            {
                *status = 3;
            }
        }
    }
}

void mainevent(int posx, int posy, int *status, int *money, batiment_io_t *carte_bat[20][20])
{
    int cout[10];
    int n;
    switch (*status)
    {
    case 0:
        eventsec(posx, posy, status);
        break;
    case 1:
        if (posx < 900)
        {
            //construction mathieu
        }
        else
        {
            if (posy > 480 && posy < 560)
            {
                //annulation du dernier posé
            }
            if (posy > 600 && posy < 680)
            {
                //annulation de toute la construction
                *status = 0;
            }
        }
        break;
    case 2:
        cout[0] = 10;
        cout[1] = 60;
        cout[2] = 200;
        cout[3] = 650;
        cout[4] = 1230;
        cout[5] = 2400;
        cout[6] = 6000;
        cout[7] = 11500;
        cout[8] = 20000;
        n = ((posx - 900) / 80) + (3 * (posy - 280) / 140);
        if (posx > 900)
        {
            if (n >= 0 && n < 9)
            {
                if (*money > cout[n])
                {
                    *money = *money - cout[n];
                    *status = 10 + n;
                }
            }
        }
        else
        {
            eventsec(posx, posy, status);
        }
        break;
    case 3:
        cout[0] = 50;
        cout[1] = 280;
        cout[2] = 600;
        cout[3] = 1800;
        cout[4] = 5000;
        cout[5] = 9800;
        cout[6] = 15000;
        cout[7] = 22000;
        cout[8] = 45000;
        n = ((posx - 900) / 80) + (3 * (posy - 280) / 140);
        if (posx > 900)
        {
            if (n >= 0 && n < 9)
            {
                if (*money > cout[n])
                {
                    *money = *money - cout[n];
                    *status = 20 + n;
                }
            }
        }
        else
        {
            eventsec(posx, posy, status);
        }
        break;
    case 10:
        if (posx < 900)
        {
            //appeler construire foreuse
            *status = 0;
        }
        else
        {
            eventsec(posx, posy, status);
        }
        break;
    case 20:
        if (posx < 900)
        {
            *status = 0;
            newUsine_brique(carte_bat, posx / 45, posy / 45);
        }
        else
        {
            eventsec(posx, posy, status);
        }
        break;
    }
}