/**Fichier contenant toutes les fonctions relatives à l'audio dans le jeu
Attention différence entre une musique et un son, une musique c'est le
bruit de fond permanent du jeu alors que les sons sont les bruits utilisés
lors d'une action (un saut, mort, kill, etc...)*/

#include "sounds.h"

/**Fonction permettant de charger une musique*/
void loadSong( char filename[200] )
{
     //S'il y avait une chanson avant on la libère
     if (game.musique != NULL)
     {
        Mix_HaltMusic();
        Mix_FreeMusic(game.musique);
     }

     //On charge la nouvelle musique
     game.musique = Mix_LoadMUS( filename );
     if (game.musique == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

    //On joue la musique à l'infini
    if(Mix_PlayMusic(game.musique, -1) == -1) printf("Mix_PlayMusic: %s\n", Mix_GetError());
}

/**Fonction permettant de charger les sons*/
void loadSound(void)
{
    //Son lors d'un rebond sur un ressort
    game.bumper_sound = Mix_LoadWAV("sounds/bumper.wav");
    if (game.bumper_sound == NULL)
    {
        fprintf(stderr, "Can't read the bumper sound FX \n");
        exit(1);
    }

    //Son lors d'un kill
    game.destroy_sound = Mix_LoadWAV("sounds/destroy.wav");
    if (game.destroy_sound == NULL)
    {
        fprintf(stderr, "Can't read the destroy sound FX \n");
        exit(1);
    }

    //Son lors d'un saut
    game.jump_sound = Mix_LoadWAV("sounds/jump.wav");
    if (game.jump_sound == NULL)
    {
        fprintf(stderr, "Can't read the jump sound FX \n");
        exit(1);
    }

    //Son lors d'une prise d'étoile
    game.star_sound = Mix_LoadWAV("sounds/star.wav");
    if (game.star_sound == NULL)
    {
        fprintf(stderr, "Can't read the star sound FX \n");
        exit(1);
    }
}

/**Fonction de libération des sons*/
void freeSound(void)
{
    Mix_FreeChunk(game.bumper_sound);
    Mix_FreeChunk(game.destroy_sound);
    Mix_FreeChunk(game.jump_sound);
    Mix_FreeChunk(game.star_sound);
}

/**Fonction qui fait jouer un son en fonction du type de son passé en argument*/
void playSoundFx(int type)
{
    switch (type)
    {
        case BUMPER:
            Mix_PlayChannel(-1, game.bumper_sound, 0);
        break;

        case DESTROY:
            Mix_PlayChannel(-1, game.destroy_sound, 0);
        break;

        case JUMP :
            Mix_PlayChannel(-1, game.jump_sound, 0);
        break;

        case STAR:
            Mix_PlayChannel(-1, game.star_sound, 0);
        break;
   }
}
