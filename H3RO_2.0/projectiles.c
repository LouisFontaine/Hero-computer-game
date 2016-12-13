/**Fichier contenant toutes les fonctions relatives aux projectiles*/

#include "projectiles.h"

/**Fonction qui permet de creer un projectile*/
void createProjectile(void)
{
    //Si on peut , on cré un projectile
    if (game.nombreProjectiles < ProjectileS_MAX)
    {
        //On enregistre sa taille dans la structure
        shuriken[game.nombreProjectiles].w = game.Shuriken_image->w;
        shuriken[game.nombreProjectiles].h = game.Shuriken_image->h;

        //Direction de la boule de feu en fonction de la direction du personnage
        if ( player.direction == RIGHT )
            {
                shuriken[game.nombreProjectiles].x = player.x + 15;
                shuriken[game.nombreProjectiles].y = player.y + 35;
                shuriken[game.nombreProjectiles].direction = 1;
            }
        else
            {
                shuriken[game.nombreProjectiles].x = player.x - 15;
                shuriken[game.nombreProjectiles].y = player.y + 35;
                shuriken[game.nombreProjectiles].direction = 0;
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
        if (shuriken[i].direction == 1)
        {
            shuriken[i].x += 10;
        }
        //On deplace vers la gauche sinon
        else
        {
            shuriken[i].x -= 10;
        }

        //On supprime le projectil si il sort de l'écran
        if (shuriken[i].x < map.startX ||shuriken[i].x > map.startX + SCREEN_WIDTH)
        {
             shuriken[i] = shuriken[game.nombreProjectiles-1];
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
        paintImage(game.Shuriken_image, shuriken[i].x - map.startX, shuriken[i].y - map.startY);
    }
}
