/*main.c*/
#include "main.h"

int main()
{
    int running = 1;

    /*** Initialisation SDL ***/
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /*** Initialisation fenetre ***/
    SDL_Window *window;
    int width = LARGEUR_FENETRE;
    int height = HAUTEUR_FENETRE;

    window = SDL_CreateWindow("ça c'est lunaire dit donc !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }

    /*** Initialisation renderer ***/
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED);

    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

    /*** Initialisation TTF et font ***/
    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    }

    TTF_Font *font1 = NULL;

    font1 = TTF_OpenFont(PATH_FONT, 60);
    if (font1 == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }

    /*** Initialisation de la carte ***/
    // int carte[20][20];

    // for (int j = 0; j < 20; ++j)
    // {
    //     for (int i = 0; i < 20; ++i)
    //     {
    //         carte[i][j] = 0;
    //     }
    // }

    // /*** Charge les textures ***/
    // SDL_Texture **tableau_matiere = malloc(10 * sizeof(SDL_Texture *));
    // tableau_matiere[0] = load_texture_from_image(PATH_BACKGROUND, renderer);
    // tableau_matiere[1] = load_texture_from_image(PATH_TUYAU_VERTICAL, renderer);
    // tableau_matiere[2] = load_texture_from_image(PATH_TUYAU_VIRAGE, renderer);
    // tableau_matiere[3] = load_texture_from_image(PATH_TUYAU_AUCUNE_ORIENTATION, renderer);
    // tableau_matiere[4] = load_texture_from_image(PATH_CASE_SURLIGNEE, renderer);

    /*Charge les textures*/
    SDL_Texture **tableau_matiere = malloc(MAX_TEXTURE * sizeof(SDL_Texture *));

    tableau_matiere[1] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_browniron.png", renderer);
    tableau_matiere[2] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_silver.png", renderer);
    tableau_matiere[3] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_coal.png", renderer);
    tableau_matiere[4] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_gold.png", renderer);
    tableau_matiere[5] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/stone_iron.png", renderer);
    tableau_matiere[6] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone.png", renderer);
    tableau_matiere[7] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left_top.png", renderer);
    tableau_matiere[8] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right_top.png", renderer);
    tableau_matiere[9] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left_bot.png", renderer);
    tableau_matiere[10] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right_bot.png", renderer);
    tableau_matiere[11] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_top.png", renderer);
    tableau_matiere[12] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_right.png", renderer);
    tableau_matiere[13] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_left.png", renderer);
    tableau_matiere[14] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone_bot.png", renderer);
    tableau_matiere[15] = load_texture_from_image("./images/voxel-pack/PNG/Tiles/greystone.png", renderer);

    tableau_matiere[four] = load_texture_from_image(PATH_FOUR, renderer);
    tableau_matiere[tuyauVertical] = load_texture_from_image(PATH_TUYAU_VERTICAL, renderer);
    tableau_matiere[tuyauVirage] = load_texture_from_image(PATH_TUYAU_VIRAGE, renderer);
    tableau_matiere[solBase] = load_texture_from_image(PATH_SOL_BASE, renderer);
    tableau_matiere[caseSurgligne] = load_texture_from_image(PATH_CASE_SURLIGNEE, renderer);
    tableau_matiere[caseNonOrientee] = load_texture_from_image(PATH_TUYAU_AUCUNE_ORIENTATION, renderer);

    SDL_Texture *fond = dessin_arriere_plan(renderer, tableau_matiere);

    /***  code en dur a l'arache ***/
    map_t *map = NULL;
    map = malloc(sizeof(map_t));
    for (int i = 0; i < TAILLE_MAP; ++i)
    {
        for (int j = 0; j < TAILLE_MAP; j++)
        {
            // attention map code en dur dans dessin fond ecran
            map->vierge[i][j] = sol;
            map->batiment[i][j] = NULL;
            map->tuyau[i][j] = NULL;
        }
    }
    batiment_io_t *bat1 = malloc(sizeof(batiment_io_t));
    batiment_io_t *bat2 = malloc(sizeof(batiment_io_t));
    bat1->pos_x = 0;
    bat1->pos_y = 0;
    bat2->pos_x = 4;
    bat2->pos_y = 0;

    map->batiment[0][0] = bat1;
    map->batiment[0][4] = bat2;
    /*  code en dur a l'arache */

    /*** Creation de la liste des tuyau ***/
    listeTuyau_t *l_tuyau;
    initListeTuyau(&l_tuyau);
    // initTuyau(&l_tuyau); // car on commence en creant un tuyau

    SDL_Event event;
    int tick = 0;
    int affiche = 0;
    clock_t begin, end;
    begin = clock();
    enum EtatJeu status = etatClassique;
    int money = 5100;

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
                mainevent(event.button.x, event.button.y, &status, &money,
                          &l_tuyau, &map);
                affiche = 1;

                break;
            case SDL_QUIT:
                running = 0;
                break;
            }
            break;
        }
        end = clock();
        if (((end - begin) * 1000 / CLOCKS_PER_SEC) > 100) //1 tick = 100ms
        {
            tick = 1;
            begin = clock();
        }
        if (tick)
        {
            affiche = 1;
            tick = 0;
        }

        affichemenu(renderer, begin, font1, status);
        // dessin_arriere_plan(map->vierge, renderer, tableau_matiere);
        dessin_arriere_plan(renderer, tableau_matiere);
        dessin_tuyau(l_tuyau, map, tableau_matiere, renderer);

        if (affiche)
        {
            SDL_RenderCopy(renderer, fond, NULL, NULL);
            affichemenu(renderer, money, font1, status);
            dessin_bat(map->batiment, renderer, tableau_matiere);
            dessin_tuyau(l_tuyau, map, tableau_matiere, renderer);
            affiche = 0;
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(10);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for (int i = 0; i < MAX_TEXTURE; i++)
        SDL_DestroyTexture(tableau_matiere[i]);
    // printf("ici\n");
    free(tableau_matiere);
    SDL_DestroyTexture(fond);
    TTF_CloseFont(font1);
    TTF_Quit();
    SDL_Quit();
    return 0;
}