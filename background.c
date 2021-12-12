/*bacground.c*/
/*23 octobre 2021*/
#include "background.h"

/*gcc fade.c -o fade -Wall -Wextra -g -lSDL2 -lSDL2_image */

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Renderer *renderer)
{
	SDL_Surface *my_image = NULL;	// Variable de passage
	SDL_Texture *my_texture = NULL; // La texture

	my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
										  // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
										  // uniquement possible si l'image est au format bmp */
	if (my_image == NULL)
		printf("my-image %s is NULL\n", file_image_name);

	my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
	SDL_FreeSurface(my_image);									   // la SDL_Surface ne sert que comme élément transitoire
	if (my_texture == NULL)
		printf("my-texture is NULL\n");

	return my_texture;
}

void dessin_texture(int x, int y, int numero_texture, SDL_Texture **tableau_minerai, SDL_Renderer *renderer, int angle, SDL_RendererFlip miroir)
{
	SDL_Rect destination = {0};
	destination.x = x * 45;
	destination.y = y * 45;
	destination.w = 45;
	destination.h = 45;
	SDL_Texture *my_texture = tableau_minerai[numero_texture];
	SDL_RenderCopyEx(renderer, my_texture, NULL, &destination, angle, NULL, miroir);
}

int r_angle(int num_tuyau)
{
	int angle = 0;
	// if (num_tuyau == 10 || num_tuyau == 5 || num_tuyau == 2)
	// 	angle = 270;
	// else if (num_tuyau == 4 || num_tuyau == 11 || num_tuyau == 8) //6
	// 	angle = 180;
	// else if (num_tuyau == 7 || num_tuyau == 4 || num_tuyau == 6 || num_tuyau == 3)
	// 	angle = 90;

	switch (num_tuyau)
	{
	case 3:	 // bas_droite
	case 10: // droite
	case 2:	 // bas_gauche
		angle = 270;
		break;
	case 12: // droite_bas
	case 11: // droite_haut
	case 4:	 // haut
		angle = 180;
		break;
	case 5: // haut_gauche
	case 7: // gauche
	case 6: // haut_droite
		angle = 90;
		break;

	default:
		break;
	}

	return angle;
}

SDL_RendererFlip r_miroir(int num_tuyau)
{
	SDL_RendererFlip miroir = SDL_FLIP_NONE;
	// if (num_tuyau == 5 || num_tuyau == 8 || num_tuyau == 6)
	// 	// if (num_tuyau == 12 || num_tuyau == 6 || num_tuyau == 2 || num_tuyau == 8)
	// 	miroir = SDL_FLIP_VERTICAL;
	switch (num_tuyau)
	{
	case 6:	 // haut_droite
	case 8:	 // gauche_haut
	case 12: // doite_bas
	case 2:	 // bas_gauche
		miroir = SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}
	return miroir;
}

int r_numero_texture(int num_tuyau)
{
	int numero_texture;
	if (num_tuyau == 0)
		numero_texture = caseNonOrientee;
	else if (num_tuyau == 1 || num_tuyau == 4 || num_tuyau == 7 || num_tuyau == 10)
		numero_texture = tuyauVertical;
	else
		numero_texture = tuyauVirage;
	return numero_texture;
}

SDL_Texture *dessin_arriere_plan(SDL_Renderer *renderer, SDL_Texture **tableau_minerai)
{
	//dessin de la carte au hasard sans cluster
	/*for (int j = 0; j < 20; ++j)
    {
        for (int i = 0; i < 20; ++i)
        {
            carte[i][j] = ((hasard < 910) && (hasard >= 850)) + ((hasard < 960) && (hasard >= 910)) * 2 + ((hasard < 980) && (hasard >= 960)) * 3 + ((hasard < 995) && (hasard >= 980)) * 4 + ((hasard < 1000) && (hasard >= 995)) * 5;
			printf("La case %d %d aura la texture : %d\n", i, j, carte[i][j]);
			printf("Le nombre au hasard est : %d\n", hasard);
			hasard = rand() % 1000;
        }
    }*/
	SDL_Texture *fond = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1200, 900);
	SDL_SetRenderTarget(renderer, fond);

	// Carte a remplacer par map->vierge !!!!
	int carte[20][20] = {{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 1, 1, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
						 {0, 0, 0, 7, 13, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
						 {0, 0, 0, 11, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 8, 12, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			dessin_texture(i, j, carte[i][j], tableau_minerai, renderer, 0, SDL_FLIP_NONE);
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
	return fond;
}

void dessin_tuyau(listeTuyau_t *tuyau_l,
				  map_t *map,
				  SDL_Texture **tableau_minerai,
				  SDL_Renderer *renderer)
{
	int nb_tuyau = tuyau_l->taille;
	int num_tuyau, x, y, angle, numero_texture, taille;
	SDL_RendererFlip miroir;
	for (int j = 0; j < nb_tuyau; j++)
	{
		taille = tuyau_l->liste[j]->taille;
		for (int i = 0; i < taille; i++)
		{
			x = tuyau_l->liste[j]->lien_contenu_case[i][0];
			y = tuyau_l->liste[j]->lien_contenu_case[i][1];
			num_tuyau = tuyau_l->liste[j]->orientation[i];
			angle = r_angle(num_tuyau);
			numero_texture = r_numero_texture(num_tuyau);
			miroir = r_miroir(num_tuyau);
			dessin_texture(x, y, numero_texture, tableau_minerai, renderer, angle, miroir);
		}

		// printf("\n\n\n\n\n\n");
		// for (int u = 0; u < TAILLE_MAP; ++u)
		// {
		// 	for (int v = 0; v < TAILLE_MAP; v++)
		// 	{
		// 		printf("%p ", map->tuyau[u][v]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n\n\n\n\n\n");

		/*** dessin case surlignee autour de la case selectionnee ***/
		if (tuyau_l->liste[j]->level == 0)
		{
			if (tuyau_l->liste[j]->taille == 0 && tuyau_l->liste[j]->entree != NULL)
			{ // Pas de bout de tuyau mais un batiment entree selectionne
				x = tuyau_l->liste[j]->entree->pos_x;
				y = tuyau_l->liste[j]->entree->pos_y;
			}

			if (x + 1 < TAILLE_MAP && map->tuyau[y][x + 1] == NULL)
			{
				dessin_texture(x + 1, y, caseSurgligne, tableau_minerai, renderer, 0, miroir);
			}
			if (x - 1 >= 0 && map->tuyau[y][x - 1] == NULL)
			{
				dessin_texture(x - 1, y, caseSurgligne, tableau_minerai, renderer, 0, miroir);
			}
			if (y + 1 < TAILLE_MAP && map->tuyau[y + 1][x] == NULL)
			{
				dessin_texture(x, y + 1, caseSurgligne, tableau_minerai, renderer, 0, miroir);
			}
			if (y - 1 >= 0 && map->tuyau[y - 1][x] == NULL)
			{
				dessin_texture(x, y - 1, caseSurgligne, tableau_minerai, renderer, 0, miroir);
			}
		}
	}
}

void dessin_bat(batiment_io_t *carte_bat[20][20], SDL_Renderer *renderer, SDL_Texture **tableau_texture)
{
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (carte_bat[i][j] != NULL)
				dessin_texture(j, i, carte_bat[i][j]->type + 18, tableau_texture, renderer, 0, SDL_FLIP_NONE);
		}
	}
}

/****************************************************/
/* charger_texture_jeu : charge les textures du jeu	*/
/* 					 	 dans un tableau      		*/
/*     												*/
/* entre : pointueur sur tableau de texture 		*/
/*		   renderer									*/
/*     												*/
/* retour : rien						            */
/****************************************************/
void charger_texture_jeu(SDL_Texture **tableau_texture,
						 SDL_Renderer *renderer)
{
	tableau_texture[1] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_browniron.png", renderer);
	tableau_texture[2] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_silver.png", renderer);
	tableau_texture[3] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_coal.png", renderer);
	tableau_texture[4] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_gold.png", renderer);
	tableau_texture[5] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_iron.png", renderer);
	tableau_texture[6] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone.png", renderer);
	tableau_texture[7] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left_top.png", renderer);
	tableau_texture[8] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right_top.png", renderer);
	tableau_texture[9] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left_bot.png", renderer);
	tableau_texture[10] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right_bot.png", renderer);
	tableau_texture[11] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_top.png", renderer);
	tableau_texture[12] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right.png", renderer);
	tableau_texture[13] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left.png", renderer);
	tableau_texture[14] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_bot.png", renderer);
	tableau_texture[15] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone.png", renderer);

	tableau_texture[four] = load_texture_from_image(PATH_FOUR, renderer);
	tableau_texture[tuyauVertical] = load_texture_from_image(PATH_TUYAU_VERTICAL, renderer);
	tableau_texture[tuyauVirage] = load_texture_from_image(PATH_TUYAU_VIRAGE, renderer);
	tableau_texture[solBase] = load_texture_from_image(PATH_SOL_BASE, renderer);
	tableau_texture[caseSurgligne] = load_texture_from_image(PATH_CASE_SURLIGNEE, renderer);
	tableau_texture[caseNonOrientee] = load_texture_from_image(PATH_TUYAU_AUCUNE_ORIENTATION, renderer);
}