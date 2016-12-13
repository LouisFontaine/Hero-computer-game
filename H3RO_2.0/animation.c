/**Fichier permettant d'animer les entit�s et de passer d'une animation � une autre contenant paintObject et modifyAnimation*/

#include "animation.h"

/**Fonction permettant d'animer les entit�s */
void paintObject(GameObject *entity)
{
    // Si notre timer arrive � z�ro
    if (entity->frameTimer <= 0)
    {
        //On le reset
        entity->frameTimer = TIME_BETWEEN_2_FRAMES;

        //Et on incr�mente notre variable qui compte les images pour passer � la suivante
        entity->frameNumber++;

        //Si on d�passe la derniere image, il faut revenir � la premi�re
        if(entity->frameNumber >= entity->sprite->w / entity->w) entity->frameNumber = 0;

    }
    //Sinon, on d�cr�mente notre timer
    else entity->frameTimer--;

    //rectangle de destination � coller
    SDL_Rect dest;

    // On soustrait les coordonn�es du h�ro � celles du d�but de la map pour qu'il puisse suivre avec le scrolling
    dest.x = entity->x - map.startX;
    dest.y = entity->y - map.startY;
    dest.w = entity->w;
    dest.h = entity->h;

    // Rectangle de la source � coller
    SDL_Rect src;

    //Pour conna�tre la position de la bonne image � coller, il suffit de multiplier la largeur de l'entit� par le num�ro de l'image � afficher
    src.x = entity->frameNumber * entity->w;
    src.y = 0;
    src.w = entity->w;
    src.h = entity->h;

    //Affiche l'entit� aux coordonn�es x et y
    SDL_BlitSurface(entity->sprite, &src, game.screen, &dest);
}

/**Fonction permettant de passer d'une animation � une autre*/
void modifyAnimation(GameObject *entity, char *name)
{
    //On lib�re l'animation pr�c�dente
    if (entity->sprite != NULL){SDL_FreeSurface(entity->sprite);}
    //On charge la nouvelle
    entity->sprite = loadImage(name);
    //On r�initialise le timer et l'image de l'entit� pour revenir � la premi�re
    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES;
}
