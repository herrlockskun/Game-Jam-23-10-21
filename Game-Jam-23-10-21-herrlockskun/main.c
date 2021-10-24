/*main.c*/
#include "main.h"

int main()
{
   if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
       // Initialisation de SDL_Mixer
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1; 
    }   

/*    Mix_Music* music = Mix_LoadMUS("musique-dascenseur.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
    
    Mix_Music* music_vie = Mix_LoadMUS("vie.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1; 
    }   
   
    Mix_Music* music_mort = Mix_LoadMUS("mort.mp3"); // Charge notre musique

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
    Mix_PlayMusic(music, -1); // Joue notre musique   

*/
    SDL_Window *window;
    int width = 1200;
    int height =900;
	int running=1;
	

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }
    SDL_SetWindowTitle(window, "Lunaire");
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
/*font de merde la*/
 if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError()); 
    }

    TTF_Font *font1=NULL;

    font1 = TTF_OpenFont("arial.ttf", 60);
    if (font1==NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }


/*Charge les textures*/
   SDL_Texture **tableau_matiere = malloc(25 * sizeof(SDL_Texture *));
    tableau_matiere[0] = load_texture_from_image("voxel-pack/PNG/Tiles/stone.png", renderer);
    tableau_matiere[1] = load_texture_from_image("voxel-pack/PNG/Tiles/stone_browniron.png", renderer);
    tableau_matiere[2] = load_texture_from_image("voxel-pack/PNG/Tiles/stone_silver.png", renderer);
    tableau_matiere[3] = load_texture_from_image("voxel-pack/PNG/Tiles/stone_coal.png", renderer);
    tableau_matiere[4] = load_texture_from_image("voxel-pack/PNG/Tiles/stone_gold.png", renderer);
    tableau_matiere[5] = load_texture_from_image("voxel-pack/PNG/Tiles/stone_iron.png", renderer);
    tableau_matiere[6] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone.png", renderer);
    tableau_matiere[7] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_left_top.png", renderer);
    tableau_matiere[8] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_right_top.png", renderer);
    tableau_matiere[9] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_left_bot.png", renderer);
    tableau_matiere[10] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_right_bot.png", renderer);
    tableau_matiere[11] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_top.png", renderer);
    tableau_matiere[12] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_right.png", renderer);
    tableau_matiere[13] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_left.png", renderer);
    tableau_matiere[14] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone_bot.png", renderer);
    tableau_matiere[15] = load_texture_from_image("voxel-pack/PNG/Tiles/greystone.png", renderer);
  tableau_matiere[16]= load_texture_from_image("horizontale.png", renderer );
	tableau_matiere[17]= load_texture_from_image("virage_2.png", renderer );
    tableau_matiere[18] = load_texture_from_image("voxel-pack/PNG/Tiles/oven.png", renderer);
	
	SDL_Texture* fond=dessin_arriere_plan(renderer, tableau_matiere);
	/*tuyau en dur*/

	listeTuyau_t  *l_tuyau=NULL;
	initListeTuyau(&l_tuyau);
	initTuyau(&l_tuyau);
	l_tuyau->liste[l_tuyau->taille-1]->lien_contenu_case[0][0]=0;
	l_tuyau->liste[l_tuyau->taille-1]->lien_contenu_case[0][1]=1;
	l_tuyau->liste[l_tuyau->taille-1]->orientation[0]=1;
	l_tuyau->liste[l_tuyau->taille-1]->taille=1;
	dessin_tuyau(l_tuyau,tableau_matiere,renderer);
	
/*	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,r_angle(1), r_miroir(1));
	dessin_texture(0,1,r_numero_texture(3),tableau_minerai,renderer,r_angle(3), r_miroir(3));
	dessin_texture(1,1,r_numero_texture(11),tableau_minerai,renderer,r_angle(11), r_miroir(11));
	dessin_texture(1,0,r_numero_texture(6),tableau_minerai,renderer,r_angle(6), r_miroir(6));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
	dessin_texture(0,0,r_numero_texture(1),tableau_minerai,renderer,angle(1), r_miroir(1));
  */

/*carte bat de merde*/
	batiment_io_t* carte_bat[20][20];
	for (int i=0; i<20; i++)
	{
		for (int j=0; j<20; j++)
			carte_bat[i][j]=NULL;
	}
		
    SDL_Event event;
    int tick=0;
    int affiche=0;
    clock_t begin,end;
    begin=clock();
    int status=0;
	 int money=5100;
    //liste_tuyau_t *ltuyau
    //initListeTuyau(&ltuyau)

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    running = 0;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    width = event.window.data1;
                    height = event.window.data2;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    break;
                }
                break;
					case SDL_MOUSEBUTTONDOWN:
                mainevent(event.button.x,event.button.y,&status,&money,carte_bat);
                affiche=1;
                break;
                 case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        end=clock();
        if (((end-begin)*1000/CLOCKS_PER_SEC)>10)   //1 tick = 100ms
        {
            tick=1;
            begin=clock();
        }
        if (tick)
        {
            affiche=1;
            tick=0;
        }  
 		  if (affiche)
        {
			SDL_RenderCopy(renderer,fond,NULL,NULL);	
            affichemenu(renderer,money,font1,status);	
			dessin_bat(carte_bat,renderer,tableau_matiere);
            affiche=0;
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(10);
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	for (int i=0; i<19; i++)
		SDL_DestroyTexture(tableau_matiere[i]);
    SDL_DestroyTexture(fond);
	free(tableau_matiere);
    TTF_CloseFont(font1);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
