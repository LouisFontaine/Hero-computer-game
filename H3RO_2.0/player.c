/**Fichier contenant toutes les fonction utiles pour le joueur, c�d l'initialisation des
attributs du joueur, la mise � jour du joueur, le coordonn�es pour le scrolling, la prise
d'item pour le joueur*/

#include "player.h"

/**Fonction qui a pour r�le d'initialiser les atributs du joueur*/
void initializePlayer(void)
{
    //Initialisation de ses points de vie
    player.life = 3;

    //Initialisation du timer d'invincibilt� utilis� plus tard lors de la mort du joueur
    player.invincibleTimer = 0;

    //Initialisation du nombre de projectiles
    game.numberProjectiles = 0;

    //Initialisation du nombre de plateformes
    game.numberPlatforms = 0;

    //Charge l'animation de d�part du joueur
    modifyAnimation(&player, "graphics/walkright.png");

    //Initialisation de la direction et de l'�tat de d�part
    player.direction = RIGHT;
    player.state = IDLE;

    //Initialisation des coordonn�es de d�part
    if(player.checkpointActif == 1)
    {
        player.x = player.respawnX;
        player.y = player.respawnY;
    }
    else
    {
        player.x = 0;
        player.y = 0;
    }

    //D�finition de la hauteur et largeur du h�ro grace au def.h
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGHT;

    //Variables utiles pour le fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;

    //Initialisation du nombre de monstres
    game.nombreMonstres = 0;

    //Initialisation des effets des powersUp
    player.onCanabis = 0;
    player.timeSinceCanabis = -TIME_OF_POWER_UP_EFFECTS;

    player.onCocaine = 0;
    player.timeSinceCocaine = -TIME_OF_POWER_UP_EFFECTS;

    player.onEcstasy = 0;
    player.timeSinceEcstasy = -TIME_OF_POWER_UP_EFFECTS;

    player.onMethamphetamine = 0;
    player.timeSinceMethamphetamine = -TIME_OF_POWER_UP_EFFECTS;
}

/**Fonction permettant d'animer le joueur en fonction des inputs*/
void renewPlayer(void)
{
  //Timer pour qu'on ne g�re le joueur que s'il est en vie
  if (player.timerMort == 0)
  {
    if(player.invincibleTimer > 0) player.invincibleTimer--;

    //On remet le vecteur de direction � 0 pour ne pas que la vitesse augmente progressivement
    player.dirX = 0;

    //On soumet le perso � la gravit� et aux effets des powerups
    player.dirY += GRAVITY_SPEED;

    //On limite la gravit� pour ne pas que le perso tombe trop vite
    if (player.dirY >= MAX_FALL_SPEED) player.dirY = MAX_FALL_SPEED;

    //Change la direction du h�ro si le input est � gauche
    if (input.left == 1)
    {
        if (player.onCanabis == 1 && player.onCocaine == 0) player.dirX -= PLAYER_SPEED / 2;
        else if (player.onCanabis == 0 && player.onCocaine == 1) player.dirX -= PLAYER_SPEED * 2;
        else player.dirX -= PLAYER_SPEED;
        player.direction = LEFT;

        if(player.state != WALK_LEFT && player.onGround == 1)
        {
            player.state = WALK_LEFT;
            modifyAnimation(&player, "graphics/walkleft.png");
        }
    }
    else if (input.right == 1)
    {
        if (player.onCanabis == 1 && player.onCocaine == 0) player.dirX += PLAYER_SPEED / 2;
        else if (player.onCanabis == 0 && player.onCocaine == 1) player.dirX += PLAYER_SPEED * 2;
        else player.dirX += PLAYER_SPEED;
        player.direction = RIGHT;

        if(player.state != WALK_RIGHT && player.onGround == 1)
        {
            player.state = WALK_RIGHT;
            modifyAnimation(&player, "graphics/walkright.png");
        }
    }

    //Fait l'animation d'inactivit� si le joueur est sur le sol et qu'il ne fait rien
    else if(input.right == 0 && input.left == 0 && player.onGround == 1)
    {
        //On v�rifie que le joueur n'�tait pas d�ja innactif pour ne pas recharger l'animation
        if(player.state != IDLE)
        {
            player.state = IDLE;

            //Animation en fonction de la direction
            if(player.direction == LEFT) modifyAnimation(&player, "graphics/IdleLeft.png");

            else modifyAnimation(&player, "graphics/IdleRight.png");
        }
    }

    //Gestion du saut
    if (input.jump == 1)
    {
        if(player.onGround == 1)
        {
            //Gestion de la drogue, nous modifions la hauteur du saut
            if (player.onEcstasy == 1) player.dirY = -JUMP_HEIGHT - 3;
            else player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
            playSoundFx(JUMP);
        }
        //gestion du deuxi�me saut
        else if (player.jump == 1)
        {
            if (player.onEcstasy == 1) player.dirY = -JUMP_HEIGHT - 3;
            else player.dirY = -JUMP_HEIGHT;
            player.jump = 0;
            playSoundFx(JUMP);
        }
        //On r�initialise les inputs
        input.jump = 0;
    }

    if(input.enter == 1)
    {
        //on met le jeu en pause si il y a l'input ad�quat
        game.onMenu = 1;
        game.menuType = PAUSE;
        input.enter = 0;
    }

    //lanc� des projectiles
    if(input.attack == 1)
    {
        createProjectile();
        input.attack = 0;
    }

    //r�active la possibilit� du double saut des qu'on est sur le sol
    if (player.onGround == 1) player.jump = 1;

    //Animation du saut
    if(player.onGround == 0)
    {
        if(player.direction == RIGHT && player.state != JUMP_RIGHT)
        {
            player.state = JUMP_RIGHT;
            modifyAnimation(&player, "graphics/JumpRight.png");
        }
        else if(player.direction == LEFT && player.state != JUMP_LEFT)
        {
            player.state = JUMP_LEFT;
            modifyAnimation(&player, "graphics/JumpLeft.png");
        }
    }

    //On d�tecte les collisions et on centre le personnages
    mapCollision(&player);
    centerScrollingOnPlayer();
  }

    //On g�re la mort lorsque le h�ro tombe dans le vide
    //Quand timer mort different de 0, le hero est mort et on le r�initialise
    //Dans ce cas on ne fait rien d'avant et on va directement dans cette boucle
    if (player.timerMort > 0)
    {
        player.timerMort--;

        if (player.timerMort == 0)
        {
            //Si on est mort
            game.lives--;
            if(game.lives < 0)
            {
                //retour au menu START
                game.onMenu = 1;
                game.menuType = START;
            }
            initializePlayer();
            changeMap();
        }
    }
}

/**Fonction qui a pour but de calculer les coordonn�es d'affichage de la map en fonction
des coordonn�es du joueur c'est � dire un demi ecran avant le joueur*/
void centerScrollingOnPlayer(void)
{
    map.startX = player.x - (SCREEN_WIDTH / 2);

    if (map.startX < 0) map.startX = 0;
    else if (map.startX + SCREEN_WIDTH >= map.maxX) map.startX = map.maxX - SCREEN_WIDTH;

    map.startY = player.y - (SCREEN_HEIGHT / 2);

    if (map.startY < 0) map.startY = 0;
    else if (map.startY + SCREEN_HEIGHT >= map.maxY) map.startY = map.maxY - SCREEN_HEIGHT;
}

/**Fonction qui au joueur de r�cuperer les �toiles et les coeurs*/
void getItem(int itemNumber)
{
    char file[200];
    switch(itemNumber)
    {
        //Pour les etoiles
        case 1:
            //On augmente de 1 le nombre d'�toiles du joueur
            game.etoiles++;
            playSoundFx(STAR);

            //Quand il y a 100 �toiles on r�initialise le compteur et on rajoute un coeur
            if(game.etoiles >= 100)
            {
                game.etoiles = 0;
                game.lives++;
            }
        break;

        //Pour les coeurs
        case 2:
            //On incr�mente le compteur de coeur
            if(player.life < 3) player.life++;
            playSoundFx(STAR);
        break;

        //Pour le powerUp cannabis
        case 3:
            player.onCanabis = 1;
            player.timeSinceCanabis = SDL_GetTicks();
        break;

        //Pour le powerUp cocaine
        case 4:
            player.onCocaine = 1;
            player.timeSinceCocaine = SDL_GetTicks();
        break;

        //Pour le powerUp Methamphetamine
        case 5:
            player.onMethamphetamine = 1;
            player.timeSinceMethamphetamine = SDL_GetTicks();
        break;

        //Pour le powerUp Champi
        case 6:
            player.onChampi = 1;
            player.timeSinceChampi = SDL_GetTicks();

            if(map.background != NULL) SDL_FreeSurface(map.background);
            if(map.tileSet != NULL) SDL_FreeSurface(map.tileSet);
            if(map.tileSetB != NULL) SDL_FreeSurface(map.tileSetB);

            map.background = loadImage("graphics/background4.png");
            sprintf(file, "graphics/tileset4.png");
            map.tileSet = loadImage(file);
            sprintf(file, "graphics/tileset4B.png");
            map.tileSetB = loadImage(file);

        break;

        //Pour le powerUp Ecstasy
        case 7:
            player.onEcstasy = 1;
            player.timeSinceEcstasy = SDL_GetTicks();
        break;

        default:
        break;
    }
}

/**Fonction qui verifie que le joueur est encore sous les effets des power up et qui remet
les �tats des onPowerUp � 0 sinon*/
void verifyPowerUp(int timeOfTheGame)
{
    char file[200];

    //On remet les onPowerUP � 0 si le temps pass� est de 10 secondes

    if (player.onCanabis == 1 && timeOfTheGame > player.timeSinceCanabis + TIME_OF_POWER_UP_EFFECTS * 1000) player.onCanabis = 0;

    if (player.onCocaine == 1 && timeOfTheGame > player.timeSinceCocaine + TIME_OF_POWER_UP_EFFECTS * 1000) player.onCocaine = 0;

    if (player.onEcstasy == 1 && timeOfTheGame > player.timeSinceEcstasy + TIME_OF_POWER_UP_EFFECTS * 1000) player.onEcstasy = 0;

    if (player.onMethamphetamine == 1 && timeOfTheGame > player.timeSinceMethamphetamine + TIME_OF_POWER_UP_EFFECTS * 1000) player.onMethamphetamine = 0;

    //on remet le tileset du niveau apr�s les 10 secondes
    if (player.onChampi == 1 && timeOfTheGame > player.timeSinceChampi + TIME_OF_POWER_UP_EFFECTS * 1000)
    {
        player.onChampi = 0;

        if(map.background != NULL) SDL_FreeSurface(map.background);
        if(map.tileSet != NULL) SDL_FreeSurface(map.tileSet);
        if(map.tileSetB != NULL) SDL_FreeSurface(map.tileSetB);

        sprintf(file, "graphics/tileset%d.png", level->info);
        map.tileSet = loadImage(file);
        sprintf(file, "graphics/tileset%dB.png", level->info);
        map.tileSetB = loadImage(file);

        if(level->info == 1) map.background = loadImage("graphics/background1.png");
        if(level->info == 2) map.background = loadImage("graphics/background2.png");
        if(level->info == 3) map.background = loadImage("graphics/background3.png");
    }
    return;
}
