/**Fichier contenant toutes les fonction utiles pour le joueur, càd l'initialisation des
attributs du joueur, la mise à jour du joueur, le coordonnées pour le scrolling, la prise
d'item pour le joueur*/

#include "player.h"

/**Fonction qui a pour rôle d'initialiser les atributs du joueur*/
void initializePlayer(void)
{
    //Initialisation de ses points de vie
    player.life = 3;

    //Initialisation du timer d'invincibilté utilisé plus tard lors de la mort du joueur
    player.invincibleTimer = 0;

    //Initialisation du nombre de projectiles
    game.nombreProjectiles = 0;

    //Initialisation du nombre de plateformes
    game.nombrePlatforms = 0;

    //Charge l'animation de départ du joueur
    modifyAnimation(&player, "graphics/walkright.png");

    //Initialisation de la direction et de l'état de depart
    player.direction = RIGHT;
    player.state = IDLE;

    //Initialisation des coordonnées de depart
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

    //Définition de la hauteur et largeur du héro grace au def.h
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //Variables utiles pour le fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;

    //Initialisation du nombre de monstre
    game.nombreMonstres = 0;

    //Initialisation des effets des poxersUp
    player.onCanabis = 0;
    player.timeSinceCanabis = - TIME_OF_POWER_UP_EFFECTS;
    player.onCocaine = 0;
    player.timeSinceCocaine = - TIME_OF_POWER_UP_EFFECTS;
    player.onEcstasy = 0;
    player.timeSinceEcstasy = - TIME_OF_POWER_UP_EFFECTS;
    player.onMethamphetamine = 0;
    player.timeSinceMethamphetamine = -TIME_OF_POWER_UP_EFFECTS;

}

/**Fonction permettant d'animer le joueur en fonction des imputs*/
void renewPlayer(void)
{

  //Timer pour qu'on ne gère le joueur que si il est en vie
  if (player.timerMort == 0)
  {
    if(player.invincibleTimer > 0)
        player.invincibleTimer--;

    //On remet le vecteur de direction à 0 pour pas que la vitesse augment progressivement
    player.dirX = 0;

    //On soumet le perso à la gravité et aux effects des powerups
    player.dirY += GRAVITY_SPEED;

    //On limite la gravité pour pas que le perso tombe trop vite
    if (player.dirY >= MAX_FALL_SPEED)
    {
        player.dirY = MAX_FALL_SPEED;
    }

    //Change la direction du hero si le imput est à gauche
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

    //Fait l'annimation d'inactivité si le jooueur est sur le sol et qu'il ne fait rien
    else if(input.right == 0 && input.left == 0 && player.onGround == 1)
    {
        //On varifie que le joueur n'était pas deja innactif pour pas recharger l'animation
        if(player.state != IDLE)
        {
            player.state = IDLE;
            //Animation en fonction de la direction
            if(player.direction == LEFT)
            {
                modifyAnimation(&player, "graphics/IdleLeft.png");
            }
            else
            {
                modifyAnimation(&player, "graphics/IdleRight.png");
            }
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
        //gestion deuxième saut
        else if (player.jump == 1)
        {
            if (player.onEcstasy == 1) player.dirY = -JUMP_HEIGHT - 3;
            else player.dirY = -JUMP_HEIGHT;
            player.jump = 0;
            playSoundFx(JUMP);
        }
        //On réinitialise les imputs
        input.jump = 0;
    }

    if(input.enter == 1)
    {
        //on met le game. en pause si il y a l'imput adéquat
        game.onMenu = 1;
        game.menuType = PAUSE;
        input.enter = 0;
    }

    //lancé des projectiles
    if(input.attack == 1)
    {
        createProjectile();
        input.attack = 0;
    }

    //réactive la possibilité du double saut des qu'on est sur le sol
    if (player.onGround == 1)
        player.jump = 1;


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

    //On detecte les collisions et on centre le personnage
    mapCollision(&player);
    centerScrollingOnPlayer();
  }

    //On gère la mort lorsque le héro tombe dans le vide
    //Quand timer mort different de 0, le hero est mort et on le réinitialise
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

/**Fonction qui a pour but de calculer les coordonnées d'affichage de la map en fonction
des coordonnées du joueur c'est à dire un demi ecran avant le joueur*/
void centerScrollingOnPlayer(void)
{
    map.startX = player.x - (SCREEN_WIDTH / 2);

    if (map.startX < 0) map.startX = 0;
    else if (map.startX + SCREEN_WIDTH >= map.maxX) map.startX = map.maxX - SCREEN_WIDTH;

    map.startY = player.y - (SCREEN_HEIGHT / 2);

    if (map.startY < 0) map.startY = 0;
    else if (map.startY + SCREEN_HEIGHT >= map.maxY) map.startY = map.maxY - SCREEN_HEIGHT;
}

/**Fonction qui au ojueur de recuperer les etoiles et les coeurs*/
void getItem(int itemNumber)
{
    switch(itemNumber)
    {
        //Pour les etoiles
        case 1:
            //On augment de 1 le nombre d'étoiles du joueur
            game.etoiles++;
            playSoundFx(STAR);

            //Quand il y a 100 étoiles on reinitialise le compteur et on rajoute un coeur
            if(game.etoiles >= 100)
            {
                game.etoiles = 0;
                game.lives++;
            }
        break;

        //Pour les coeurs
        case 2:
            //On incrémente le compteur de coeur
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

        //Pourle powerUp Ecstasy
        case 5:
            player.onMethamphetamine = 1;
            player.timeSinceMethamphetamine = SDL_GetTicks();
        break;

        case 6:


        break;

        case 7:
            player.onEcstasy = 1;
            player.timeSinceEcstasy = SDL_GetTicks();
        break;

        default:
        break;
    }
}

/**Fonction qui verifie que le joueur est encore sous les effets des power up et qui remet
les états des onPowerUp à 0 sinon*/
void verifyPowerUp(int timeOfTheGame)
{
    if (player.onCanabis == 1 && timeOfTheGame > player.timeSinceCanabis + 10 * 1000) player.onCanabis = 0;
    if (player.onCocaine == 1 && timeOfTheGame > player.timeSinceCocaine + 10 * 1000) player.onCocaine = 0;
    if (player.onEcstasy == 1 && timeOfTheGame > player.timeSinceEcstasy + 10 * 1000) player.onEcstasy = 0;
    if (player.onMethamphetamine == 1 && timeOfTheGame > player.timeSinceMethamphetamine + 10 * 1000) player.onMethamphetamine = 0;

    return;
}
