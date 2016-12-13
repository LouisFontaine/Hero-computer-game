#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

/* Valeur RVB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255


/* Taille maxi de la map : 400 x 300 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 300

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* N° de la tile transparente */
#define BLANK_TILE 0

/* MAX_TILES = numéro de la dernière tile */
#define MAX_TILES 22

/* Nombre maximum de levels */
#define LEVEL_MAX   3
