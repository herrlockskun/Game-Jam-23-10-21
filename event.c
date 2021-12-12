#include "event.h"

void eventsec(int posx, int posy, enum EtatJeu *status,
              listeTuyau_t **p_l_tuyau)
{
    if (posx < 900)
    {
        //a faire plus tard
        *status = etatClassique;
    }
    if (posx > 900)
    {
        if (posy > 750 && posy < 830)
        {
            if (posx > 910 && posx < 990)
            {
                initTuyau(p_l_tuyau);
                *status = etatConstructionTuyau;
            }
            if (posx > 1010 && posx < 1090)
            {
                *status = etatConstructionBat0;
            }
            if (posx > 1110 && posx < 1190)
            {
                *status = etatConstructionBat1;
            }
        }
    }
}

void mainevent(int posx, int posy, enum EtatJeu *status, int *money,
               listeTuyau_t **p_l_tuyau,
               map_t **p_map)
{
    int cout[10];
    int n;
    switch (*status)
    {
    case etatClassique:
        eventsec(posx, posy, status, p_l_tuyau);
        break;
    case etatConstructionTuyau:
        if (posx < 900)
        {
            //construction mathieu
            if (constructionTuyau(p_l_tuyau, p_map,
                                  posx, posy) == 6)
            {
                *status = etatClassique;
            }
        }
        else
        {
            if (posy > 480 && posy < 560)
            {
                //annulation du dernier posé
                annulerConstructionTuyauUnite(p_l_tuyau, *p_map);
            }
            if (posy > 600 && posy < 680)
            {
                //annulation de toute la construction
                suppressionTotalTuyau(p_l_tuyau, *p_map);
                *status = etatClassique;
            }
        }
        break;
    case etatConstructionBat0:
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
                    *status = 10 + n; // Etrange !!!
                }
            }
        }
        else
        {
            eventsec(posx, posy, status, p_l_tuyau);
        }
        break;
    case etatConstructionBat1:
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
                    *status = 20 + n; // Etrange !!!!
                }
            }
        }
        else
        {
            eventsec(posx, posy, status, p_l_tuyau);
        }
        break;
    case 10:
        if (posx < 900)
        {
            //appeler construire foreuse
            *status = etatClassique;
        }
        else
        {
            eventsec(posx, posy, status, p_l_tuyau);
        }
        break;
    case 20:
        if (posx < 900)
        {
            *status = etatClassique;
            newUsine_brique((*p_map)->batiment, posx / 45, posy / 45);
        }
        else
        {
            eventsec(posx, posy, status, p_l_tuyau);
        }
        break;
    }
}