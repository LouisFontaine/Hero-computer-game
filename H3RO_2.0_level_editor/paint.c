/**Fichier contenant toutes les fonction g�rent l'affichage*/
#include "paint.h"

/**Fonction qui permet d'afficher une image enti�re sur l'�cran aux coordonn�es x et y*/
void paintImage(SDL_Surface *image, int x, int y)
{
    SDL_Rect dest;

    //calcul de o� blitter l'image
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_BlitSurface(image, NULL, game.screen, &dest);
}

/**Fonction qui permet d'afficher une tile*/
void paintTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy)
{
    //Rectangle qu'on va afficher � la fin dans l'image de graphic
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

/**Fonction qui g�re l'affichage de tout l'�cran*/
void paint(void)
{

    //affichage du background � (0;0)
    paintImage(map.background, 0, 0);

    //affichage de toutes les tiles
    paintMap();

    //fonction SDL qui raffraichit l'ecran
    SDL_Flip(game.screen);

    //D�lai
    SDL_Delay(1);

}

/**Fonction qui charge les images et les renvoies en SDL_Surface*/
SDL_Surface *loadImage(char *name)
{
    //chargement d'une image temporaire
    SDL_Surface *temp = IMG_Load(name);
    SDL_Surface *image;

    //Si on n'arrive pas � la charger on quitte le programme et on affiche dans la commande le probl�me
    if (temp == NULL)
    {
        printf("Failed to load image %s\n", name);
        return NULL;
    }

    //Ajout de la transparence RVB � l'image d�finie dans le def.h
    SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL), SDL_MapRGB(temp->format, TRANS_R, TRANS_G,    TRANS_B));

    //Conversion au format de l'�cran
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

/**Fonction de gestion du d�lai pour avoir 60 FPS*/
void delay(unsigned int frameLimit)
{
    unsigned int ticks = SDL_GetTicks();
    if (frameLimit < ticks) return;
    if (frameLimit > ticks + 16) SDL_Delay(16);
    else SDL_Delay(frameLimit - ticks);
}
