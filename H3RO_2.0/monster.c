/**Fichier contenant les fonctions qui gèrent les monstres dans le game.*/

#include "monster.h"

/**Fonction qui initialise les monstres dans le game. (graphiques, direction, etc..)*/
void initializeMonster(int x, int y)
{
    /**On initialize tous les monstres du game. en parcourant le tableau de monstre jusqu'à
    ce que on arrive au nombre de monstre max défini dans le def.h*/
    if (game.nombreMonstres < MONSTRES_MAX )
    {
        //On charge l'image du monstre
        monster[game.nombreMonstres].sprite = loadImage("graphics/monster1.png");

        //On initialise sa direction à gauche pour qu'il aille vers le perso
        monster[game.nombreMonstres].direction = LEFT;

        //On réinitialise le timer d'animation
        monster[game.nombreMonstres].frameNumber = 0;
        monster[game.nombreMonstres].frameTimer = TIME_BETWEEN_2_FRAMES;

        //Ses coordonnées pour le démarages vont envoyés en argument
        monster[game.nombreMonstres].x = x;
        monster[game.nombreMonstres].y = y;

        //On initialise la taille grâce au def.h
        monster[game.nombreMonstres].w = MONSTER_WIDTH;
        monster[game.nombreMonstres].h = MONSTER_HEIGHT;

        //On initialise les variables utiles aux colisions
        monster[game.nombreMonstres].timerMort = 0;
        monster[game.nombreMonstres].onGround = 0;

        //On parcour le tableau
        game.nombreMonstres++;

    }

}

/**Fonction qui  permet de mettre à jour les monstres en vérifiant les colisions*/
void renewMonsters(void)
{
    int i, a;
    //On utilise une boucle for pour parcourir tous les monstres de la liste
    for ( i = 0; i < game.nombreMonstres; i++ )
    {
        // On test les collisions entre les monstres et le boulles de feu
        for ( a = 0; a < game.nombreProjectiles; a++ )
        {
            if (collide(&monster[i], &shuriken[a]))
            {
                //Timer à 1 pour le tuer
                monster[i].timerMort = 1;
                playSoundFx(DESTROY);

                shuriken[a] = shuriken[game.nombreProjectiles-1];
                game.nombreProjectiles--;
            }
        }
        if (monster[i].timerMort == 0)
        {
            monster[i].dirX = 0;
            monster[i].dirY += GRAVITY_SPEED;

            if (monster[i].dirY >= MAX_FALL_SPEED)
                monster[i].dirY = MAX_FALL_SPEED;

            //Test de si le moonstre est arrive dans un mur
            if (monster[i].x == monster[i].saveX || checkFall(monster[i]) == 1 )
            {
                if (monster[i].direction == LEFT)
                {
                    monster[i].direction = RIGHT;
                    modifyAnimation(&monster[i], "graphics/monster1right.png");
                }
                else
                {
                    monster[i].direction = LEFT;
                    modifyAnimation(&monster[i], "graphics/monster1.png");
                }
            }

            //Deplacement du monstre en fonction de la direction du monstre
            if(monster[i].direction == LEFT)
                monster[i].dirX -= 2;
            else
                monster[i].dirX += 2;


            //On sauvegarde les coordonnées du monstre pour pouvoir gérer les demi-tours
            //avant que mapCollision modifie.
            monster[i].saveX = monster[i].x;

            //On fait comme pour le joueur, on detecte les collisions avec la map
            monsterCollisionWithMap(&monster[i]);

            //Detection des collisions avec le joueur
            //Si c'est égal à 1,  on diminue ses points de vie
            if (collide(&player, &monster[i]) == 1)
            {
                if(player.life > 1)
                {
                    //quand le timer d'invincibilité est à 0 on enleve un coeur et obn reaugment le timer
                    if(player.invincibleTimer == 0 && player.onMethamphetamine != 1)
                    {
                        player.life--;
                        player.invincibleTimer = 60;
                        //Son
                        playSoundFx(DESTROY);
                        //On met le timer de mort du monstre à 1 pour qu'il meurt instant
                        monster[i].timerMort = 1;
                        player.dirY = -JUMP_HEIGHT;
                    }
                }
                else if(player.onMethamphetamine != 1)
                {
                    //On met le timer à 1 pour tuer le joueur intantanément
                    player.timerMort = 1;
                    //son
                    playSoundFx(DESTROY);
                }
            }
            else if (collide(&player, &monster[i]) == 2)
            {
                //On tue le monstre en mettant son timer à 1
                monster[i].timerMort = 1;
                playSoundFx(DESTROY);
            }
          }

        //Si le monstre meurt, on active une tempo
        if (monster[i].timerMort > 0)
        {
            monster[i].timerMort--;
            /* Et on le remplace simplement par le dernier du tableau puis on
            rétrécit le tableau d'une case (on ne peut pas laisser de case vide) */
            if (monster[i].timerMort == 0)
            {
                /* Libère le sprite pour eviter les fuites memoires :) */
                if (monster[i].sprite != NULL)
                {
                    SDL_FreeSurface(monster[i].sprite);
                }
                monster[i] = monster[game.nombreMonstres-1];
                game.nombreMonstres--;
            }
        }
    }
}

/**Fonction qui gère les collisions*/
int collide(GameObject *player, GameObject *monster)
 {
    //Test de collisions entre deux gameObject
    if ((player->x >= monster->x + monster->w) || (player->x + player->w <= monster->x)
    || (player->y >= monster->y + monster->h) || (player->y + player->h <= monster->y))
    return 0; //pas collision

    //Sinon quand il y a collision, si le joueur est au-dessus du monstre, on renvoie 2.
    //On gerera plus tard la mort du monstre et le rebond du joueur
    else if (player->y + player->h <= monster->y + 10)
    {
        player->dirY =- JUMP_HEIGHT;
        return 2;
    }
    //sinon le joueur meurt et on renvoit donc 1
    else return 1;
}

/**Fonction qui teste si le monstre va tomber et qui renvoie 1 si il doit tombe, sinon 0*/
int checkFall(GameObject monster)
{
    int x, y;
    //On test la direction pour savoir si on doit prendre en compte la largeur du monstre
    if (monster.direction == LEFT)
    {
        //On calcul la futur position pour gérer le cas où il sortirait de la map
        x = (int)(monster.x + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) /  TILE_SIZE;
        if (y < 0)
            y = 1;
        if (y > MAX_MAP_Y)
            y = MAX_MAP_Y;
        if (x < 0)
            x = 1;
        if (x > MAX_MAP_X)
            x = MAX_MAP_X;

        //On vérifie si il y a du vide en dessous du monstre
        if (map.tile[y + 1][x] < BLANK_TILE) return 1;
        else return 0;
    }
    else
    {
        //Même chose quand on va à droite
        x = (int)(monster.x + monster.w + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) / TILE_SIZE;
        if (y <= 0)
            y = 1;
        if (y >= MAX_MAP_Y)
            y = MAX_MAP_Y - 1;
        if (x <= 0)
            x = 1;
        if (x >= MAX_MAP_X)
            x = MAX_MAP_X - 1;

        if (map.tile[y + 1][x] < BLANK_TILE) return 1;
        else return 0;
    }
}
