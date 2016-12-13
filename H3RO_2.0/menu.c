/**Fichier contenant les fonctions qui permettent d'afficher le menu de démarage du
game.et le menu pause*/

#include "menu.h"

/**Fonction qui va lire les imputs et qui va déplacer le curseur de start à quit en
fonction du choix de l'utilisateur et qui va se charger de lancer le game. quand
l'utilisateur le décide*/
void renewStartMenu(void)
{
    //Quand on appuie sur flêche du bas
    if(input.down == 1)
    {
        //Si choice égual à O (start), on le met sur 1 (quit)
        if(game.choice == 0) game.choice++;
        input.down = 0;
    }

    //Quand on appuie sur flêche du haut
    if(input.up == 1)
    {
        //Si choice égual à 1 (Quit), on le met sur 0 (Start)
        if(game.choice == 1) game.choice--;
        input.up = 0;
    }

    //Quand on appuie sur  la touche Enter et qu'on est déjà sur Start (0) alors on
    //recharge le game.et on quitte l'état menu (game.onMenu = 0)
    if(input.enter)
    {
        if(game.choice == 0)
        {
            player.checkpointActif = 0;
            initializePlayer();
            changeMap();
            //On réinitialise les variables du game.pour commencer une nouvelle partie
            game.lives = 3;
            game.etoiles = 0;
            game.onMenu = 0;
        }
        //Sinon, on quitte le jeu
        else if(game.choice == 1){exit(0);}
        input.enter = 0;
    }
}

///Fonction qui se charge de l'affichage du menu Start
void paintStartMenu(void)
{

    //On utilise une chaine de carractère qui va contenir notre texte à afficher
    char text[200];

    paintImage(game.fondMenuStart, 0, 0);

    //Si le curseur n'est pas sur l'élément on l'affiche normalement
    if(game.choice != 0)
    {
        sprintf(text, "  START");
        paintString(text, 440, 320, font);
    }
    if(game.choice != 1)
    {
        sprintf(text, "  QUIT");
        paintString(text, 440, 380, font);
    }

     //Si le curseur est sur l'élément on rajoute "-"
    if(game.choice == 0)
    {
        sprintf(text, "- START");
        paintString(text, 420, 320, font);
    }
    else if(game.choice == 1)
    {
        sprintf(text, "- QUIT");
        paintString(text, 420, 380, font);
    }

    //On affiche le copyright Team GHB original creator of awesome games
    sprintf(text, "TEAM GHB, 2016");
    paintString(text, 350, 500, font);


}

/**Fonction qui va lire les imputs pour pouvoir relancer le game. lorsque l'utilisateur
rappuie sur enter*/
void renewPauseMenu(void)
{

    //Si l'utilisateur appuie sur Enter alors quitte l'état Onmenu
    if(input.enter)
    {
        game.onMenu = 0;
        input.enter = 0;
    }

}

///Fonction qui se charge de l'affichage du menu Pause
void paintPauseMenu(void)
{
    char text[200];

    //On affiche juste pause à l'écran
    sprintf(text, "** PAUSE **");
    paintString(text, 470, 350, font);

}

void renewEndMenu(void)
{
    //Si l'utilisateur appuie sur Enter alors quitte l'état On passe au menu start
    if(input.enter)
    {
        //On ne nchange pas l'state onMenu mais on change le type de menu
        game.menuType = START;
        input.enter = 0;
    }
}

void paintEndMenu(void)
{
    //On utilise une chaine de carractère qui va contenir notre texte à afficher
    char text[200];

    paintImage(game.fondMenuStart, 0, 0);
    sprintf(text, "VOUS AVEZ GAGNE !");
    paintString(text, 295, 400, font);
    sprintf(text, "APPUYER SUR ENTREE POUR CONTINUER");
    paintString(text, 50, 600, font);


}
