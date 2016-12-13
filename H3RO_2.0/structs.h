/**Fichier contenant les différentes structures utilisées pour le jeux*/

#include "defs.h"

/**Structure pour l'input*/
typedef struct Input
{
    int left,
    right,
    up,
    down,
    jump,
    attack,
    enter,
    erase,
    pause;
} Input;

/**Structure utilisée pour les monstres et le héro*/
typedef struct GameObject
{
    // Sprite du héros
    SDL_Surface *sprite;

    // Points de vie
    int life, invincibleTimer;

    // Coordonnées du héro
    int x, y;

    // Largeur et hauteur du héro
    int h, w;

    // Checkpoint
    int checkpointActif;
    int respawnX, respawnY;

    // Variables utilisées pour l'animation du héro
    int frameNumber, frameTimer;
    int state, direction;

    // Variables pour les collisions et le temps de mort
    int onGround, timerMort;
    float dirX, dirY;

    // Variable pour le double saut
    int jump;

    // Variables pour gérer les Plateformes
    int beginX, beginY;
    int type, player_dessus;

    // Variables pour gérer les powerups
    int onCanabis;
    int timeSinceCanabis;

    int onCocaine;
    int timeSinceCocaine;

    int onEcstasy;
    int timeSinceEcstasy;

    int onMethamphetamine;
    int timeSinceMethamphetamine;

    int onChampi;
    int timeSinceChampi;

} GameObject;

/**Structure pour gérer un niveau */
typedef struct Gestion
{
    SDL_Surface *screen;
    int nombreMonstres;
    int level;
    int nombreProjectiles;
    int nombrePlatforms;

    // HUD
    SDL_Surface *HUD_vie, *Shuriken_image, *Platform;
    int lives, etoiles;

    // Musiques
    Mix_Music  *musique;

    // Son d'animation
    Mix_Chunk  *bumper_sound, *destroy_sound, *jump_sound, *star_sound;

    // Gestion des menus
    int onMenu, menuType, choice;
    SDL_Surface *fondMenuStart;

} Gestion;

/**Structure pour représenter la map*/
typedef struct Map
{
    SDL_Surface *background, *tileSet;
    SDL_Surface *tileSetB;

    // Coordonnées de depart pour afficher la map
    int startX, startY;

    // Coordonnées d'arrivée pour l'affichage de la map
    int maxX, maxY;

    // Tableau 2D représentant la map
    int tile[MAX_MAP_Y][MAX_MAP_X];

    // Timer et numéro du tileset à afficher pour animer la map
    int mapTimer, tileSetNumber;

} Map;

/**Structure liste qui va contenir des entiers permettants de définir l'ordre de passage des carttes dans le jeu*/
typedef struct node{
    //Données contenues dans la liste
    int info;
    int glob;

    // Pointeurs vers l'élément suivant de la liste
    struct node* succ;
}node;

typedef node* liste;
