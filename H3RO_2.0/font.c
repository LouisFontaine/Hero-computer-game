/**Ce fichier permet de gérer tout ce qui concerne les ecritures en SDL*/

#include "font.h"

/**fonction qui charge la police de caractère*/
TTF_Font *loadFont(char *name, int size)
{
    //Chargement de la police choisie avec SDL_TTF
    TTF_Font *font = TTF_OpenFont(name, size);

    if (font == NULL)
    {
        printf("Failed to open Font %s: %s\n", name, TTF_GetError());
        exit(1);
    }

    return font;
}

/**Fonction pour fermer la police*/
void closeFont(TTF_Font *font)
{
    // Ferme la police à la fin du programme lorsque nous n'en avons plus besoin

    if (font != NULL)
    {
        TTF_CloseFont(font);
    }
}

/**Fonction pour ecrire la chaine de caractère*/
void paintString(char *text, int x, int y, TTF_Font *font)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor;

    //Nous définissons la couleur sur le noir
    foregroundColor.r = 255;
    foregroundColor.g = 255;
    foregroundColor.b = 255;


    //Avec SDL_TTF, nous génerons la chaine de caractère à écrire

    surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);


    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());
        return;
    }

    // On colle cette Surface à l'écran
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_BlitSurface(surface, NULL, game.screen, &dest);

    // On libère cette surface
    SDL_FreeSurface(surface);
}
