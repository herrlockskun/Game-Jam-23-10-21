#ifndef background_gard
#define background_gard
/*bacground.h*/
/*23 octobre 2021*/

#include "const.h"
#include "map.h"

SDL_Texture *load_texture_from_image(char *file_image_name,
                                     SDL_Renderer *renderer);
void dessin_texture(int x, int y, int numero_minerai,
                    SDL_Texture **tableau_minerai, SDL_Renderer *renderer, int, SDL_RendererFlip);
SDL_Texture *dessin_arriere_plan(SDL_Renderer *renderer,
                                 SDL_Texture **tableau_minerai);
int r_angle(int num_tuyau);
SDL_RendererFlip r_miroir(int num_tuyau);
int r_numero_texture(int num_tuyau);
void dessin_tuyau(struct listeTuyau *tuyau_l, map_t *map,
                  SDL_Texture **tableau_minerai, SDL_Renderer *rendeder);
void dessin_bat(batiment_io_t *carte_batiment[20][20],
                SDL_Renderer *renderer, SDL_Texture **tableau_texture);

void charger_texture_jeu(SDL_Texture **tableau_texture,
                         SDL_Renderer *renderer);
#endif
