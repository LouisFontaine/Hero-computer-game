#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255


/* Taille maxi de la map : on voit large : 400 x 300 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 300

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 39
#define PLAYER_HEIGTH 78

/* Taille du sprite de nos monstres (largeur = width et hauteur = heigth) */
#define MONSTER_WIDTH 39
#define MONSTER_HEIGHT 78

//Nombre de lives au lancement du jeu
#define LIVES_TOTAL 3

/* Constantes pour l'animation  */
#define TIME_BETWEEN_2_FRAMES 9

///Vitesse de déplacement en pixels du sprite POUR LA COKE!!!!!!!!!
#define PLAYER_SPEED 4

//Valeurs attribuées aux états/directions
#define WALK_RIGHT 1
#define WALK_LEFT 2
#define IDLE 3
#define JUMP_RIGHT 4
#define JUMP_LEFT 5
#define RIGHT 1
#define LEFT 2

// Constante définissant le seuil entre les tiles traversables (blank) et les tiles solides
#define BLANK_TILE 15

//Autres Tiles spéciales

#define TILE_RESSORT 17
#define TILE_CHECKPOINT 14
#define TILE_MONSTRE 22

#define TILE_POWER_UP_DEBUT 7
#define TILE_POWER_UP_FIN 13

#define TILE_Platform_DEBUT 20
#define TILE_Platform_FIN 21

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 12

//Nombre max de monstres à l'écran
#define MONSTRES_MAX 6

//Nombre maximum de levels
#define LEVEL_MAX 3

//Nombre maximum de projectiles sur l'écran
#define ProjectileS_MAX 3

//Constantes utilisées pour les plateformes
#define PLATFORMS_MAX 50
#define PLATFORMS_TILES_DEBUT 15
#define PLATFORMS_TILES_FIN 16
#define PLATFORM_SPEED 2
#define UP 3
#define DOWN 4

#define TIME_OF_POWER_UP_EFFECTS 10

enum
{
    BUMPER,
    DESTROY,
    JUMP,
    STAR
};

//state de jeu
enum
{
    START,
    PAUSE,
    ENDGAME
};
