/**Fichier pour initialiser la SDL et la charger puis pour la libérer*/

#include "initialize.h"

/**Fonction pour initialiser tous les paramètres nécessaires pour le fonctionnement du game.en rapport avec la SDL*/
void initialize(char *title)
{

    // Initialise SDL Video Si ça ne fonctionne pas, on quitte
    if (SDL_Init(SDL_INIT_VIDEO ) < 0)
    {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    //Pour charger l'icone de la fenêtre
    SDL_WM_SetIcon(SDL_LoadBMP("graphics/icone.bmp"), NULL);

    // Ouverture de la fenêtre en fonction de la largeur et de la hauteur définies avec le doublebuf pour empêcher le scintillement
    game.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);

    //Sinon on quitte
    if (game.screen == NULL)
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }
    //Nom de la fenêtre
    SDL_WM_SetCaption(title, NULL);

    // Pour cacher la souris
    SDL_ShowCursor(SDL_DISABLE);

    // Lancement de SDL_TTF sinon on quitte
    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }

    //Nous chargeons la police en 32 points
    font = loadFont("font/Star Force TTF.ttf", 32);

    //Initialisation de SDL_MIX
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    // Création de canaux pour les sons
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }

    //Réduction du volume de la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME/10);

    //Réduction du son du canal des effets sonnores du jeu
    Mix_Volume(-1, MIX_MAX_VOLUME/10);

    //Nous allouons 32 canaux à mixer
    Mix_AllocateChannels(32);
}

/**Fonction pour charger les élements à ajouter au jeu*/
void load(void)
{
    // Charge l'image de fond du menu start et du jeu
    game.fondMenuStart = loadImage("graphics/fondMenuStart.png");

    changeMap();

    //On initialise le timer de la map
    map.mapTimer = TIME_BETWEEN_2_FRAMES*3;
    map.tileSetNumber = 0;

    // on initialise le nombre de lives du joueur et son nombre d'etoiles
    game.lives = LIVES_TOTAL;
    game.etoiles = 0;

    //Nous chargeons les HUDs de la vie
    game.HUD_vie = loadImage("graphics/life.png");

    //Nous chargeons le projectile et la plateforme
    game.Shuriken_image = loadImage("graphics/projectile.png");
    loadPlatform();

    //Lancement de la musique et des sons FX
    loadSong("music/Tezla - Music Is The Drug (Original Mix).mp3");
    loadSound();

    //Nous souhaitons le menu Start au début
    game.onMenu = 1;
    game.menuType = START;
}

void init_list_map(liste l)
{
    int i, x, y, z;
    for(i = 1; i <= LEVEL_MAX; i++)
    {
        x = 1 + rand() % 3;

        do
        {
            y = 1 + rand() % 3;
        }while(y == x);

        if(x < 3 && y < 3) z = 3;
        else z = abs(x - y);

        level->info = x;
        level->glob = i;
        level = level->succ;
        level->info = y;
        level->glob = i;
        level = level->succ;
        level->info = z;
        level->glob = i;
        level = level->succ;
    }
}

/**Fonction pour libérer toutes les données chargées*/
void clean()
{
    int i;

    //Libérations des fonds
    if (map.background != NULL)
    {
        SDL_FreeSurface(map.background);
    }
    if ( game.fondMenuStart != NULL )
    {
        SDL_FreeSurface(game.fondMenuStart);
    }

    //Libération des tileset
    if (map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }
    if (map.tileSetB != NULL)
    {
        SDL_FreeSurface(map.tileSetB);
    }

    //Libération du héro
    if (player.sprite != NULL)
    {
        SDL_FreeSurface(player.sprite);
    }

    //Libération des monstres
    for(i = 0 ; i < MONSTRES_MAX ; i++)
    {
        if (monster[i].sprite != NULL)
        {
        SDL_FreeSurface(monster[i].sprite);
        }
    }

    if (game.HUD_vie != NULL)
    {
        SDL_FreeSurface(game.HUD_vie);
    }

    //Libèration du projectile
    if (game.Shuriken_image != NULL)
    {
        SDL_FreeSurface(game.Shuriken_image);
    }

    //Libération de la plateforme
    if (game.Platform != NULL)
    {
        SDL_FreeSurface(game.Platform);
    }

    //Libération de la musique de fond
    if ( game.musique != NULL ) Mix_FreeMusic(game.musique);

    //Libérationh de la liste
    if(level != NULL) freeListe();

    //Libération des sons
    freeSound();

    Mix_CloseAudio();
    Mix_Quit();
    closeFont(font);
    TTF_Quit();
    SDL_Quit();
}
