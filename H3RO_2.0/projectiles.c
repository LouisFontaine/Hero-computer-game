/**Fichier contenant toutes les fonctions relatives aux projectiles*/

#include "projectiles.h"

/**Fonction qui permet de creer un projectile*/
void createProjectile(void)
{
    //Si on peut , on cré un projectile
    if (game.nombreProjectiles < ProjectileS_MAX)
    {
        //On enregistre sa taille dans la structure
        projectile[game.nombreProjectiles].w = game.Shuriken_image->w;
        projectile[game.nombreProjectiles].h = game.Shuriken_image->h;

        //Direction de la boule de feu en fonction de la direction du personnage
        if ( player.direction == RIGHT )
            {
                projectile[game.nombreProjectiles].x = player.x + 15;
                projectile[game.nombreProjectiles].y = player.y + 35;
                projectile[game.nombreProjectiles].direction = 1;
            }
        else
            {
                projectile[game.nombreProjectiles].x = player.x - 15;
                projectile[game.nombreProjectiles].y = player.y + 35;
                projectile[game.nombreProjectiles].direction = 0;
            }
        game.nombreProjectiles++;
    }
}

/**Fonction qui permet le deplacement du projectile*/
void doProjectiles(void)
{
    int i;
    //On passe en boucle tous les projectiles
    for ( i = 0; i < game.nombreProjectiles; i++ )
    {
        //On deplace vers la droite si il le faut
        if (projectile[i].direction == 1)
        {
            projectile[i].x += 10;
        }
        //On deplace vers la gauche sinon
        else
        {
            projectile[i].x -= 10;
        }

        //On supprime le projectil si il sort de l'écran
        if (projectile[i].x < map.startX ||projectile[i].x > map.startX + SCREEN_WIDTH)
        {
             projectile[i] = projectile[game.nombreProjectiles-1];
             game.nombreProjectiles--;
        }

    }

}

/**Fonction qui affiche tous les projectile*/
void paintProjectiles(void)
{
    int i;
    //boucle for pour afficher tous les projectciles
    for ( i = 0; i < game.nombreProjectiles; i++ )
    {
        paintImage(game.Shuriken_image, projectile[i].x - map.startX, projectile[i].y - map.startY);
    }
}
