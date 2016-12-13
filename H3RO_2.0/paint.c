/**Fichier contenant les fonctions de blitage pour l'affichage*/

#include "paint.h"

/**Fonction qui permet d'afficher une image entière sur l'écran aux coordonnées x et y*/
void paintImage(SDL_Surface *image, int x, int y)
{
    SDL_Rect dest;
    //calcul de où blitter l'image
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_BlitSurface(image, NULL, game.screen, &dest);
}

/**Fonction qui permet d'afficher une tile*/
void paintTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy)
{
    //Rectangle qu'on va afficher à la fin dans l'image de graphic
    SDL_Rect dest;

    dest.x = destx;
    dest.y = desty;
    dest.w = TILE_SIZE;
    dest.h = TILE_SIZE;

    //Rectangle qu'il faut afficher
    SDL_Rect src;

    src.x = srcx;
    src.y = srcy;
    src.w = TILE_SIZE;
    src.h = TILE_SIZE;

    //Affichage
    SDL_BlitSurface(image, &src, game.screen, &dest);
}

/**Fonction qui gère l'affichage de tout l'écran*/
void paint(void)
{
    int i;
    //affichage du background à (0;0)
    paintImage(map.background, 0, 0);

    //affichage de toutes les tiles
    paintMap();

    //Affichage du joueur
    paintObject(&player);

    //Affhage de tous les monstres
    for(i = 0 ; i < game.nombreMonstres ; i++) paintObject(&monster[i]);

    //affichage des plateformes
    paintPlatform();

    //affichage des projectiles
    paintProjectiles();

    //Affichage du HUD (lives, etoiles, coeurs)
    paintHud();

    //fonction SDL qui raffraichit l'ecran
    SDL_Flip(game.screen);

   //Délai
    SDL_Delay(1);
}

/**Fonction qui charge les images et les renvoies en SDL_Surface*/
SDL_Surface *loadImage(char *name)
{
    //chargement d'une image temporaire
    SDL_Surface *temp = IMG_Load(name);
    SDL_Surface *image;

    //Si on n'arrive pas à la charger on quitte le programme et on affiche dans la commande le problème
    if (temp == NULL)
    {
        printf("Failed to load image %s\n", name);
        return NULL;
    }

    //Ajout de la transparence RVB à l'image définie dans le def.h
    SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL), SDL_MapRGB(temp->format, TRANS_R, TRANS_G, TRANS_B));

    //Conversion au format de l'écran
    image = SDL_DisplayFormat(temp);

    //On libere l'image temporaire
    SDL_FreeSurface(temp);

    if (image == NULL)
    {
        printf("Failed to convert image %s to native format\n", name);
        return NULL;
    }
    return image;
}

/**Fonction de gestion du délai pour avoir 60 FPS*/
void delay(unsigned int frameLimit)
{
    unsigned int ticks = SDL_GetTicks();
    if (frameLimit < ticks) return;

    if (frameLimit > ticks + 16) SDL_Delay(16);
    else SDL_Delay(frameLimit - ticks);
}

/**Fonction qui gère l'affichage de l'HUD*/
void paintHud(void)
{
    int ysource;
    int xsource;

    //Créé une variable de type text pour l'affichage du nombre de vies et de coeurs
    char text[200];

    int i;
    //Affiche le nombre de coeurs avec un decalage de 32 pixels
    for(i = 0; i < player.life; i++)
    {
        // Calcul pour découper le tileset comme dans la fonction paintMap()
        ysource = (TILE_POWER_UP_DEBUT + 1) / 10 * TILE_SIZE;
        xsource = (TILE_POWER_UP_DEBUT + 1) * TILE_SIZE;
        paintTile(map.tileSet, 60 + i * 32, 20, xsource, ysource);
    }

    //Affichage des vies en bas à droite de l'écran
    paintImage(game.HUD_vie, 900, 600);

    //On met le nombre de coeurs dans la chaîne de caractère
    sprintf(text, "%d", game.lives);

    //Puis on réutilise la fonction d'affichage de string créée précedement
    paintString(text, 970, 610, font);

    //Affichage du nombre d'étoiles
    ysource = (TILE_POWER_UP_DEBUT) / 10 * TILE_SIZE;
    xsource = (TILE_POWER_UP_DEBUT) * TILE_SIZE;

    paintTile(map.tileSet, 60, 60, xsource, ysource);
    sprintf(text, "%d", game.etoiles);
    paintString(text, 100, 57, font);
}
