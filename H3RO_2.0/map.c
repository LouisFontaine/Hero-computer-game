/**Fichier permettant d'afficher la map et de tester les collisions du joueur et des monstres avec la map*/

#include "map.h"

/**Fonction pour lire le fichier de la map et puis la charger*/
void loadMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");

    //Si on n'arrive pas � charger le fichier, on quitte
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    //Boucle pour lire le fichier contenant tous les �lements de la map
    map.maxX = map.maxY = 0;

    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            //Lecture du num�ro de la tile et copie dans le tableau de la map
            fscanf(fp, "%d", &map.tile[y][x]);

            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX)
                {
                    map.maxX = x;
                }

                if (y > map.maxY)
                {
                    map.maxY = y;
                }
            }
        }
    }

    //maxX et maxY correspondent aux coordonn�es de la fin de la map, pour les trouver, en lisant le fichier, d�s qu'il n'y a plus que des z�ros apr�s le dernier �lement
    map.maxX = (map.maxX + 1) * TILE_SIZE;
    map.maxY = (map.maxY + 1) * TILE_SIZE;

    //R�initialise les coordonn�es de d�part de la map
    map.startX = map.startY = 0;

    fclose(fp);
}

/**Fonction pour afficher la map et ses �lements*/
void paintMap(void)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    //Nous initialisons mapX � la 1�re colonne qu'on doit blitter
    mapX = map.startX / TILE_SIZE;

    // Coordonn�es de la SDL pour l'affichage de la map pour d�terminer les coordonn�es de la 1e colonne
    x1 = (map.startX % TILE_SIZE) * -1;

    //Nous calculons les coordonn�es de la fin de la map
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    //De m�me pour y
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    //Nous cr�ons un timer afin d'animer le game.avec les deux tilesets
    if(map.mapTimer <= 0)
    {
        if(map.tileSetNumber == 0)
        {
            map.tileSetNumber = 1;
            map.mapTimer = TIME_BETWEEN_2_FRAMES*3;
        }
        else
        {
            map.tileSetNumber = 0;
            map.mapTimer = TIME_BETWEEN_2_FRAMES*3;
        }
    }
    else
    map.mapTimer--;

    //Nous dessinons ici la map en blittant ligne par ligne
    for (y = y1; y < y2; y += TILE_SIZE)
    {
        //R�initialisation de mapX pour revenir au d�but de la ligne
        mapX = map.startX / TILE_SIZE;

        for (x = x1; x < x2; x += TILE_SIZE)
        {
            //Si la tile n'est pas une tile vide
            if (map.tile[mapY][mapX] != 0)
            {
                //Si c'est une tile monstre
                if (map.tile[mapY][mapX] == TILE_MONSTRE)
                {
                    //On initialise le monstre au coordonn�es o� nous sommes
                    initializeMonster(mapX * TILE_SIZE, mapY * TILE_SIZE - 17); //-17 pour ajuster la hauteur du monstre

                    //Puis on l'efface du tableau
                    map.tile[mapY][mapX] = 0;
                }
                //Si c'est une tile comprise entre le d�but des plateformes et la fin
                else if (map.tile[mapY][mapX] >= TILE_Platform_DEBUT && map.tile[mapY][mapX] <= TILE_Platform_FIN)
                {
                    //On initialise la plateforme flottante
                    initPlatform(mapX * TILE_SIZE, mapY * TILE_SIZE, map.tile[mapY][mapX] - TILE_Platform_DEBUT +1);

                    //Puis on l'efface du tableau
                    map.tile[mapY][mapX] = 0;
                }
            }

            //On d�coupe le tileset en fonction du num�ro de notre tile
            a = map.tile[mapY][mapX];

            //calcul des coordonn�es sur le tileset
            ysource = a / 10 * TILE_SIZE;
            xsource = a % 10 * TILE_SIZE;

            //nous blittons la bonne tile aux bonnes coordonn�es
            if(map.tileSetNumber == 0) paintTile(map.tileSet, x, y, xsource, ysource);
            else paintTile(map.tileSetB, x, y, xsource, ysource);
            mapX++;
        }
        mapY++;
    }
}

/**Fonction pour tester les collisions avec le joueur*/
void mapCollision(GameObject *entity)
{

    int i, x1, x2, y1, y2;

    entity->onGround = 0;

    //On r�ajuste les sprites � la taille d'une tile
    if(entity->h > TILE_SIZE) i = TILE_SIZE;
    else i = entity->h;

    //Nous executons une boucle infinie que l'on interrompra en fonction des r�sultats de nos calculs
    for (;;)
    {
        //Nous calculons les coordonn�es des coins du sprite pour conna�tre les tiles qu'il touche en x
        x1 = (entity->x + entity->dirX) / TILE_SIZE;
        x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        //De m�me en y mais nous allons monter petit � petit avec la variable i
        y1 = (entity->y) / TILE_SIZE;
        y2 = (entity->y + i - 1) / TILE_SIZE;

        //Nous allons maintenant tester les mouvements de renewPlayer et v�rifier que dirX et dirY sont bien dans l'�cran
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si le mouvement est vers la droite
            if (entity->dirX > 0)
            {
                //Nous testons si le h�ro est sur une tile power up
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);

                    //On remplace la tile par une tile transparente
                    map.tile[y1][x2] = 0;
                }
                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);

                    //On remplace la tile par une tile transparente
                    map.tile[y2][x2] = 0;
                }


                //Nous testons si le h�ro est sur une tile checkpoint
                if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    //Nous changeons la valeur du bool�en du checkpoint
                    entity->checkpointActif = 1;

                    //Nous changeons donc les coordonn�es de respawn
                    entity->respawnX = x2 * TILE_SIZE;
                    entity->respawnY = (y1 * TILE_SIZE) - entity->h;

                    //Nous mettons la tile de checkpoint valid�
                    map.tile[y1][x2] += 1;
                }
                else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    //Nous changeons la valeur du bool�en du checkpoint
                    entity->checkpointActif = 1;

                    //Nous changeons donc les coordonn�es de respawn
                    entity->respawnX = x2 * TILE_SIZE;
                    entity->respawnY = (y2 * TILE_SIZE) - entity->h;

                    //Nous mettons la tile de checkpoint valid�
                    map.tile[y2][x2] += 1;
                }

                //nous testons si c'est une tile solide
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    //Si oui on le place le plus pr�s possible
                    entity->x = x2 * TILE_SIZE;
                    entity->x -= entity->w + 1;
                    entity->dirX = 0;
                }
            }

            //Nous faisons de m�me � gauche
            else if (entity->dirX < 0)
            {
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
                    && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);
                    map.tile[y1][x1] = 0;
                }
                else if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
                    && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    map.tile[y2][x1] = 0;
                }

                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x1 * TILE_SIZE;
                    entity->respawnY = (y1 * TILE_SIZE) - entity->h;

                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x1 * TILE_SIZE;
                    entity->respawnY = (y2 * TILE_SIZE) - entity->h;

                    map.tile[y2][x1] += 1;
                }

                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
                {
                    entity->x = (x1 + 1) * TILE_SIZE;
                    entity->dirX = 0;
                }
            }
        }

        //Nous sortons de la boucle for si nous avons tout test� sur la hauteur du personnage
        if (i == entity->h)
        {
            break;
        }

        //Sinon nous testons les tiles sup�rieures sans d�passer la hauteur du sprite
        i += TILE_SIZE;
        if (i > entity->h)
        {
            i = entity->h;
        }
    }

    //Nous faisons de m�me avec les mouvements verticaux
    if(entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;

    for (;;)
    {
        x1 = (entity->x) / TILE_SIZE;
        x2 = (entity->x + i) / TILE_SIZE;

        y1 = (entity->y + entity->dirY) / TILE_SIZE;
        y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //D�placement vers le bas
            if (entity->dirY > 0)
            {
                if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT && map.tile[y2][x1] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);
                    map.tile[y2][x1] = 0;
                }
                else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT && map.tile[y2][x2] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);
                    map.tile[y2][x2] = 0;
                }

                if (map.tile[y2][x1] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x1 * TILE_SIZE;
                    entity->respawnY = (y2 * TILE_SIZE) - entity->h;

                    map.tile[y2][x1] += 1;
                }
                else if (map.tile[y2][x2] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x2 * TILE_SIZE;
                    entity->respawnY = (y2 * TILE_SIZE) - entity->h;

                    map.tile[y2][x2] += 1;
                }

                //Nous allons tester les interactions avec le ressort
                if ((map.tile[y2][x1] == TILE_RESSORT ) || (map.tile[y2][x2] == TILE_RESSORT ))
                {
                    entity->dirY = -20;
                    entity->onGround = 1;
                    //Nous lan�ons le son du ressort
                    playSoundFx(BUMPER);
                }
                else if (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    entity->y = y2 * TILE_SIZE;
                    entity->y -= entity->h;
                    entity->dirY = 0;
                    entity->onGround = 1;
                }

                //Nous testons les collisions avec les plateformes
                int j;

                if (game.numberPlatforms > 0)
                {
                    for (j = 1 ; j <= game.numberPlatforms ; j++)
                    {
                        if (entity->x + entity->w >= Platform[j].x && entity->x <= Platform[j].x + Platform[j].w && entity->y + entity->h >= Platform[j].y && entity->y + entity->h < Platform[j].y + 32)
                        {
                            entity->y = Platform[j].y - entity->h;
                            entity->dirY = 0;
                            entity->onGround = 1;
                            Platform[j].player_dessus = 1;
                        }
                        else Platform[j].player_dessus = 0;
                    }
                }
            }

            //D�placement vers le bas
            else if (entity->dirY < 0)
            {
                if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
                    && map.tile[y1][x1] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);

                    map.tile[y1][x1] = 0;
                }
                if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT
                    && map.tile[y1][x2] <= TILE_POWER_UP_FIN)
                {
                    getItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);
                    map.tile[y1][x2] = 0;
                }

                if (map.tile[y1][x1] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x1 * TILE_SIZE;
                    entity->respawnY= (y1 * TILE_SIZE) - entity->h;

                    map.tile[y1][x1] += 1;
                }
                else if (map.tile[y1][x2] == TILE_CHECKPOINT)
                {
                    entity->checkpointActif = 1;

                    entity->respawnX = x2 * TILE_SIZE;
                    entity->respawnY= (y1 * TILE_SIZE) - entity->h;

                    map.tile[y1][x2] += 1;
                }


                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
                {
                    entity->y = (y1 + 1) * TILE_SIZE;
                    entity->dirY = 0;
                }
            }
        }

        //Nous testons maintenant pour la largeur comme nous l'avions fait pour la hauteur pr�cedemment
        if (i == entity->w) break;

        i += TILE_SIZE;

        if (i > entity->w) i = entity->w;
    }

    //On effectue donc le mouvement en donnant les coordonn�es des vecteurs � l'entit� si on n'est pas bloqu�
    entity->x += entity->dirX;
    entity->y += entity->dirY;

    //On limite les d�placements � la taille de l'�cran
    if (entity->x < 0) entity->x = 0;
    //Si on touche le bord droit
    else if (entity->x + entity->w >= map.maxX)
    {
        level=level->succ;
        //Si on  est au dessus du niveau max, on compte la fin de map comme un mur invisible
        if(level->glob > LEVEL_MAX)
        {
            game.onMenu = 1;
            game.menuType = ENDGAME;
        }
        //Si nous passons au niveau suivant, nous chargeons la nouvelle map et nous r�initialisons le joueur
        else
        {
            entity->checkpointActif = 0;
            changeMap();
            initializePlayer();
        }
    }
    //Si le joueur sort de l'ecran par le bas, nous r�initialisons le joueur avec un timer pour ne pas r�apparaitre
    if (entity->y > map.maxY) entity->timerMort = 60;
}

/**Fonction pour changer de map*/
void changeMap(void)
{
    char file[200];
    printf("%d-%d\n", level->glob, level->info);

    //Nous chargeons le fichier depuis le fichier la contenant
    sprintf(file, "map/map%d-%d.txt", level->glob, level->info );
    loadMap(file);

    if(map.background != NULL) SDL_FreeSurface(map.background);
    //Nous choisissons le bon fond
    if(level->info == 1) map.background = loadImage("graphics/background1.png");
    if(level->info == 2) map.background = loadImage("graphics/background2.png");
    if(level->info == 3) map.background = loadImage("graphics/background3.png");

    //Nous chargeons le tileset
    if(map.tileSet != NULL) SDL_FreeSurface(map.tileSet);
    if(map.tileSetB != NULL) SDL_FreeSurface(map.tileSetB);

    sprintf(file, "graphics/tileset%d.png", level->info );
    map.tileSet = loadImage(file);
    sprintf(file, "graphics/tileset%dB.png", level->info );
    map.tileSetB = loadImage(file);
}

/**Fonction pour tester les collisions avec les monstres*/
void monsterCollisionWithMap(GameObject *entity)
{
    int i, x1, x2, y1, y2;

    entity->onGround = 0;

    if(entity->h > TILE_SIZE) i = TILE_SIZE;
    else i = entity->h;

    for (;;)
    {
        x1 = (entity->x + entity->dirX) / TILE_SIZE;
        x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        y1 = (entity->y) / TILE_SIZE;
        y2 = (entity->y + i - 1) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Dans le cas du mouvement � droite
            if (entity->dirX > 0)
            {
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    entity->x = x2 * TILE_SIZE;
                    entity->x -= entity->w + 1;
                    entity->dirX = 0;
                }
            }
            //mouvement � gauche
            else if (entity->dirX < 0)
            {
                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
                {
                    entity->x = (x1 + 1) * TILE_SIZE;
                    entity->dirX = 0;
                }
            }
        }
        //Si on a test� toute la hauteur on peut quitter la boucle
        if (i == entity->h) break;

        //Sinon nous testons les tiles sup�rieures sans d�passer la hauteur du sprite
        i += TILE_SIZE;

        if (i > entity->h) i = entity->h;
    }

    //Nous faisons de m�me avec les y
    if(entity->w > TILE_SIZE) i = TILE_SIZE;
    else i = entity->w;

    for (;;)
    {
        x1 = (entity->x) / TILE_SIZE;
        x2 = (entity->x + i) / TILE_SIZE;

        y1 = (entity->y + entity->dirY) / TILE_SIZE;
        y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //mouvement vers le bas
            if (entity->dirY > 0)
            {
                if (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    entity->y = y2 * TILE_SIZE;
                    entity->y -= entity->h;
                    entity->dirY = 0;
                    entity->onGround = 1;
                }
            }
            //mouvement vers le haut
            else if (entity->dirY < 0)
            {
                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
                {
                    entity->y = (y1 + 1) * TILE_SIZE;
                    entity->dirY = 0;
                }
            }
        }
        //Tout comme pr�cedemment, nous testons la largeur
        if (i == entity->w) break;

        i += TILE_SIZE;

        if (i > entity->w) i = entity->w;
    }

    //Application des mouvements � l'entit�
    entity->x += entity->dirX;
    entity->y += entity->dirY;

    //blocage de l'entit� � la taille de l'ecran
    if (entity->x < 0) entity->x = 0;

    else if (entity->x + entity->w >= map.maxX) entity->x = map.maxX - entity->w - 1;
}
