/*bacground.h*/
/*23 octobre 2021*/
#include <SDL2/SDL_image.h>        
#include <SDL2/SDL.h>

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Renderer *renderer );
void minerais(int x, int y, int numero_minerai, SDL_Texture** tableau_minerai, SDL_Renderer* renderer);
void dessin_arriere_plan(int carte[20][20], SDL_Renderer* renderer, SDL_Texture** tableau_minerai);

