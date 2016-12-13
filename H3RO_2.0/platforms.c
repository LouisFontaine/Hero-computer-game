/**Fichier contenant toutes les fonction relatives à la gestion des plateformes*/

#include "platforms.h"

/**Fonction permettant de charger l'image de la plateforme*/
void loadPlatform(void)
{
    //Chargement de l'image
    game.Platform = loadImage("graphics/Platform.png");

    //Sinon on affiche une erreur dans la console
    if (game.Platform == NULL)
    {
        printf("Impossible de charger l'image de la Platform : graphics/Platform.png/n");
        exit(1);
    }
}

/**Fonction qui permet de charger toutes les plateformes*/
void initPlatform(int x, int y, int type)
{
    // On incrémente le nombre de plateformes dans notre jeu
    game.numberPlatforms++;

    //S'il y en a trop on quitte le jeu
    if (game.numberPlatforms > PLATFORMS_MAX)
    {
        printf("Trop de Plateformes initialisees !\nEnlevez-en ou changez leur nombre max.\n");
        exit(1);
    }

    //On remplit la structure
    Platform[game.numberPlatforms].x = Platform[game.numberPlatforms].beginX = x;
    Platform[game.numberPlatforms].y = Platform[game.numberPlatforms].beginY = y;
    Platform[game.numberPlatforms].w = game.Platform->w;
    Platform[game.numberPlatforms].h = game.Platform->h;
    Platform[game.numberPlatforms].type = type;

    //On indique son type (2 si elle monte sinon c'est qu'elle va à droite)
    if (Platform[game.numberPlatforms].type == 2) Platform[game.numberPlatforms].direction = UP;
    else Platform[game.numberPlatforms].direction = RIGHT;
}

/**Fonction animant les plateformes*/
void doPlatform(void)
{
    int i;
    for ( i = 1; i <= game.numberPlatforms; i++ )
    {
        // Pour le deplacement des plateformes de haut en bas
        if (Platform[i].type == 2)
        {
            if (Platform[i].direction == UP)
            {
                Platform[i].y -= PLATFORM_SPEED;
                //On oubli pas de deplacer le joueur avec si il est dessus
                if (Platform[i].player_dessus == 1) player.y -= PLATFORM_SPEED;
            }
            else
            {
                Platform[i].y += PLATFORM_SPEED;
                //On oubli pas de deplacer le joueur avec si il est dessus
                if (Platform[i].player_dessus == 1) player.y += PLATFORM_SPEED;
            }
            //Au bout d'un deplacement de 5 cases on inverse le sens de deplacement pour pas
            //qu'elles se deplacent à l'infini
            if (Platform[i].y > Platform[i].beginY + 5 * TILE_SIZE) Platform[i].direction = UP;
            if (Platform[i].y < Platform[i].beginY) Platform[i].direction = DOWN;
        }

        // Pour le deplacement des plateformes de gauche à droite c'est pareil pas besoin de commentaire
        else
        {
            if (Platform[i].direction == RIGHT)
            {
                Platform[i].x += PLATFORM_SPEED;
                if (Platform[i].player_dessus == 1) player.x += PLATFORM_SPEED;
            }
            else
            {
                Platform[i].x -= PLATFORM_SPEED;
                if (Platform[i].player_dessus == 1) player.x -= PLATFORM_SPEED;
            }
            if (Platform[i].x > Platform[i].beginX + 5 * TILE_SIZE) Platform[i].direction = LEFT;
            if (Platform[i].x < Platform[i].beginX) Platform[i].direction = RIGHT;
        }
    }
}

/**Fonction qui se charge de l'affichage des plateformes*/
void paintPlatform(void)
{
    int i;
    //Boucle for pour parcourir toutes les plateformes
    for ( i = 1; i <= game.numberPlatforms; i++ )
    {
        paintImage(game.Platform, Platform[i].x - map.startX, Platform[i].y - map.startY);
    }
}
