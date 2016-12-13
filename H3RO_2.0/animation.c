/**Fichier permettant d'animer les entités et de passer d'une animation à une autre contenant paintObject et modifyAnimation*/

#include "animation.h"

/**Fonction permettant d'animer les entités */
void paintObject(GameObject *entity)
{
    // Si notre timer arrive à zéro
    if (entity->frameTimer <= 0)
    {
        //On le reset
        entity->frameTimer = TIME_BETWEEN_2_FRAMES;

        //Et on incrémente notre variable qui compte les images pour passer à la suivante
        entity->frameNumber++;

        //Si on dépasse la derniere image, il faut revenir à la première
        if(entity->frameNumber >= entity->sprite->w / entity->w) entity->frameNumber = 0;

    }
    //Sinon, on décrémente notre timer
    else entity->frameTimer--;

    //rectangle de destination à coller
    SDL_Rect dest;

    // On soustrait les coordonnées du héro à celles du début de la map pour qu'il puisse suivre avec le scrolling
    dest.x = entity->x - map.startX;
    dest.y = entity->y - map.startY;
    dest.w = entity->w;
    dest.h = entity->h;

    // Rectangle de la source à coller
    SDL_Rect src;

    //Pour connaître la position de la bonne image à coller, il suffit de multiplier la largeur de l'entité par le numéro de l'image à afficher
    src.x = entity->frameNumber * entity->w;
    src.y = 0;
    src.w = entity->w;
    src.h = entity->h;

    //Affiche l'entité aux coordonnées x et y
    SDL_BlitSurface(entity->sprite, &src, game.screen, &dest);
}

/**Fonction permettant de passer d'une animation à une autre*/
void modifyAnimation(GameObject *entity, char *name)
{
    //On libère l'animation précédente
    if (entity->sprite != NULL){SDL_FreeSurface(entity->sprite);}
    //On charge la nouvelle
    entity->sprite = loadImage(name);
    //On réinitialise le timer et l'image de l'entité pour revenir à la première
    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES;
}
