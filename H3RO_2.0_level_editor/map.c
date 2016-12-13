/**Fichier permettant d'afficher la map et de tester les collisions du joueur et des monstres avec la map*/
#include "map.h"

/**Fonction pour lire le fichier de la map et puis la charger*/
void loadMap(char *name)
 {
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);

        exit(1);
    }

    //Lit les donn�es du fichier et les mets dans le tableau map
    map.maxX = map.maxY = 0;

    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            //On lit le num�ro de la tile et on le copie dans notre tableau
            fscanf(fp, "%d", &map.tile[y][x]);

            //Permet de d�terminer la taille de la map (voir plus bas)
            if (map.tile[y][x] > 0)
            {
                if (x > map.maxX) map.maxX = x;
                if (y > map.maxY) map.maxY = y;
            }
        }
    }

    //On change ces coordonn�es pour qu'on puisse scroller et �diter la map au maximum
    map.maxX = MAX_MAP_X * TILE_SIZE;
    map.maxY = MAX_MAP_Y * TILE_SIZE;

    //Remet � 0 les coordonn�es de d�part de la map
    map.startX = map.startY = 0;

    //Et on referme le fichier
    fclose(fp);
}

/**Fonction pour afficher la map et ses �lements*/
void paintMap(void)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    //Nous initialisons mapX � la 1�re colonne qu'on doit blitter
    mapX = map.startX / TILE_SIZE;

    //Coordonn�es de la SDL pour l'affichage de la map pour d�terminer les coordonn�es de la 1e colonne
    x1 = (map.startX % TILE_SIZE) * -1;

    //Nous calculons les coordonn�es de la fin de la map
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    //De m�me pour y
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


    //Nous dessinons ici la map en blittant ligne par ligne
    for (y = y1; y < y2; y += TILE_SIZE)
    {
        //R�initialisation de mapX pour revenir au d�but de la ligne
        mapX = map.startX / TILE_SIZE;

        for (x = x1; x < x2; x += TILE_SIZE)
        {
            //On d�coupe le tileset en fonction du num�ro de notre tile
            a = map.tile[mapY][mapX];

            //calcul des coordonn�es sur le tileset
            ysource = a / 10 * TILE_SIZE;
            xsource = a % 10 * TILE_SIZE;

            //nous blittons la bonne tile aux bonnes coordonn�es
            paintTile(map.tileSet, x, y, xsource, ysource);

            mapX++;
        }

        mapY++;
    }

    //On affiche la tile qu'il faut � cot� du curseur
    ysource = cursor.tileID / 10 * TILE_SIZE;
    xsource = cursor.tileID % 10 * TILE_SIZE;
    paintTile(map.tileSet, cursor.x, cursor.y, xsource, ysource);
  }

/**Fonction pour sauvegarder la map dans un fichier*/
void saveMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "wb");
    //Si on peut pas ouvrir le fichier on quitte
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    //Sinon on sauvegarde la map
    for (y=0;y<MAX_MAP_Y;y++)
    {
        for (x=0;x<MAX_MAP_X;x++)
        {
            fprintf(fp, "%d ", map.tile[y][x]);
        }
        fprintf(fp, "\n");
    }

    //On referme le fichier
    fclose(fp);
 }

 /**Fonction pour reinitialiser la map*/
void reinitMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "wb+");

    //Si on peut pas ouvrir le fichier on quitte
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    //Remplit la map de 0
    for (y=0;y<MAX_MAP_Y;y++)
    {
        for (x=0;x<MAX_MAP_X;x++)
        {
            fprintf(fp, "0 ");
        }
        fprintf(fp, "\n");
    }

    //On referme le fichier
    fclose(fp);
 }
