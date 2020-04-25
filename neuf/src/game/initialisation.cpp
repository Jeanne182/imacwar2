#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"

void initialisationGame(Game *game){
  //fenetre
  game->window_width = 1500;
  game->window_height = 800;
  game->bit_per_pixel = 32;
  game->framerate_milliseconds = 1000/60;
  game->aspectRatio = game->window_width / (float) game->window_height;

  //Initialisation de la largeur
  game->longueurCarte = 10;
  game->hauteurCarte = 10; 

  //Initialisation des joueurs
  game->joueur1.nbUnites=0;
  game->joueur1.nbUnitesInitial=0;
  game->joueur1.id = 1;


  game->joueur2.nbUnites=0;
  game->joueur2.nbUnitesInitial=0;
  game->joueur2.id = 2;


  //Initialisation des boutons
  game->boutonDeplacement.x = 1.1;
  game->boutonDeplacement.y = 0.8;
  game->boutonDeplacement.longueur = 0.05;
  game->boutonDeplacement.hauteur = 0.05;
  game->boutonDeplacement.r = 1;
  game->boutonDeplacement.g = 0;
  game->boutonDeplacement.b = 1;

  game->etapeJeu = 0 ; //0 pour préparation, 1 pour attaque/déplacement
  game->tour = 1;



  initialisationSDL(&game->textureMap,game->surface);

  reshape(&game->surface, game->window_width, game->window_height);
}
