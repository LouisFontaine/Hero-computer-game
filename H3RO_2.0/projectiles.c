/**Fichier contenant toutes les fonctions relatives aux projectiles*/

#include "projectiles.h"

/**Fonction qui permet de créer un projectile*/
void createProjectile(void)
{
    //Si on peut, on créé un projectile
    if (game.numberProjectiles < PROJECTILES_MAX)
    {
        //On enregistre sa taille dans la structure
        projectile[game.numberProjectiles].w = game.Shuriken_image->w;
        projectile[game.numberProjectiles].h = game.Shuriken_image->h;

        //Direction du projectile en fonction de la direction du personnage
        if ( player.direction == RIGHT )
        {
            projectile[game.numberProjectiles].x = player.x + 15;
            projectile[game.numberProjectiles].y = player.y + 35;
            projectile[game.numberProjectiles].direction = 1;
        }
        else
        {
            projectile[game.numberProjectiles].x = player.x - 15;
            projectile[game.numberProjectiles].y = player.y + 35;
            projectile[game.numberProjectiles].direction = 0;
        }
        game.numberProjectiles++;
    }
}

/**Fonction qui permet le deplacement du projectile*/
void doProjectiles(void)
{
    int i;
    //On passe en boucle tous les projectiles
    for ( i = 0; i < game.numberProjectiles; i++ )
    {
        //On le fait se déplacer à droite si c'est sa direction
        if (projectile[i].direction == 1) projectile[i].x += 10;

        //On deplace vers la gauche sinon
        else projectile[i].x -= 10;

        //On supprime le projectile s'il sort de l'écran
        if (projectile[i].x < map.startX ||projectile[i].x > map.startX + SCREEN_WIDTH)
        {
             projectile[i] = projectile[game.numberProjectiles-1];
             game.numberProjectiles--;
        }
    }
}

/**Fonction qui affiche tous les projectile*/
void paintProjectiles(void)
{
    int i;
    //boucle for pour afficher tous les projectciles
    for ( i = 0; i < game.numberProjectiles; i++ ) paintImage(game.Shuriken_image, projectile[i].x - map.startX, projectile[i].y - map.startY);
}
