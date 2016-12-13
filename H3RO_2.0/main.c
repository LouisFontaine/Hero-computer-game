/**Fichier principal du jeu*/

#include "main.h"

int main(int argc, char *argv[])
{
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);
    srand(time(NULL));

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go, i;
    liste l = NULL;

    //Appel � la fonction initialize pour lancer la SDL
    initialize("H3RO");

    //Initialisation de l'ordre des niveaux
    level = create_list(3 * LEVEL_MAX);
    l = level;
    init_list_map(level);
    level = l;

    //Puis appel de la fonction pour initialiser le joueur
    initializePlayer();

    //Chargement des ressources
    load();

    //A la fin du programme nous lib�rons toutes les donn�es en m�moire
    atexit(clean);

    //Boucle infinie pour lancer le jeu
    go = 1;
    while (go == 1)
    {
        //Appel de getInput pour attendre les entr�es de l'utilisateur
        getInput();

        //Si on n'est pas dans un menu
        if(game.onMenu == 0)
        {
            //Mise � jour du jeu
            verifyPowerUp(SDL_GetTicks());
            renewPlayer();
            doProjectiles();
            renewMonsters();
            doPlatform();
        }
        else
        {
            if(game.menuType == START) renewStartMenu();
            else if(game.menuType == PAUSE) renewPauseMenu();
            else if(game.menuType == ENDGAME)
            {
                level = l;
                renewEndMenu();
                init_list_map(level);
                level = l;
            }
        }

        //Si on n'est pas dans un menu
        if(game.onMenu == 0)
        {
            //On affiche tout le contenu � afficher
            paint();
        }
        else
        {
            if(game.menuType == START)
            {
                paintStartMenu();
                SDL_Flip(game.screen);
                SDL_Delay(1);
            }
            else if(game.menuType == PAUSE)
            {
                paintMap();
                paintObject(&player);
                for(i = 0 ; i < game.nombreMonstres ; i++)
                {
                    paintObject(&monster[i]);
                }
                paintPlatform();
                paintProjectiles();
                paintHud();
                paintPauseMenu();
                SDL_Flip(game.screen);
                SDL_Delay(1);
            }
            else if(game.menuType == ENDGAME)
            {
                paintEndMenu();
                SDL_Flip(game.screen);
                SDL_Delay(1);
            }
        }
        //Fonctiion pour limiter � 60fps
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
    }
    exit(0);
}
