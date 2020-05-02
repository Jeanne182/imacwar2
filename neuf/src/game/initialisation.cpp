#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

Game::Game():map{{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
                 { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                 { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                 { 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
                 { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                 { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 }},
            mapInit{{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
                    { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                    { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                    { 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
                    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 }},
            zonePlacement{{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },
                          { 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },
                          { 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
                          { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
                          { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
                          { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }}{}

void initialisationGame(Game *game){
   game->surface = NULL;
  //fenetre
  game->window_width = 1500;
  game->window_height = 800;
  game->bit_per_pixel = 32;
  game->framerate_milliseconds = 1000/60;
  game->aspectRatio = game->window_width / (float) game->window_height;

  //Initialisation textures

  game->surfaceCases[PLAINE] = IMG_Load("src/img/plaine.png");
  game->surfaceCases[EAU] = IMG_Load("src/img/eau.png");
  game->surfaceCases[ARBRE] = IMG_Load("src/img/arbre.png");
  game->surfaceUnites[HUMAN] = IMG_Load("src/img/Gandalf.png");
  //Initialisation de la carte
  game->longueurCarte = 10;
  game->hauteurCarte = 10;

  //Initialisation des joueurs
  game->joueur1.nbUnites=0;
  game->joueur1.nbUnitesInitial=0;
  game->joueur1.id = 1;
  game->joueur1.tour = JOUEUR1;


  game->joueur2.nbUnites=0;
  game->joueur2.nbUnitesInitial=0;
  game->joueur2.id = 2;
  game->joueur2.tour = JOUEUR2;


  //Initialisation des boutons
  game->boutonDeplacement.x = 1.1; //Rose
  game->boutonDeplacement.y = 0.8;
  game->boutonDeplacement.longueur = 0.15;
  game->boutonDeplacement.hauteur = 0.05;
  game->boutonDeplacement.r = 1;
  game->boutonDeplacement.g = 0;
  game->boutonDeplacement.b = 1;
  game->boutonDeplacement.valeur = DEPLACEMENT;

  //game->boutonAttaque.x = 1.5;
  //game->boutonAttaque.y = 0.8;
  game->boutonAttaque.x = 1.1;
  game->boutonAttaque.y = 0.5;
  game->boutonAttaque.longueur = 0.15;
  game->boutonAttaque.hauteur = 0.05;
  game->boutonAttaque.r = 0; //bleu
  game->boutonAttaque.g = 0;
  game->boutonAttaque.b = 1;
  game->boutonAttaque.valeur = ATTAQUE;

  game->etapeJeu = PLACEMENT_UNITES; //0 pour préparation, 1 pour attaque/déplacement
  game->tour = TOUR_JOUEUR1;
  game->choix = RIEN;




  initialisationSDL(game);

  reshape(&game->surface, game->window_width, game->window_height);
}
