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
  game->surfaceUnites[HUMAN] = IMG_Load("src/img/human.png");
  game->surfaceUnites[HOBBIT] = IMG_Load("src/img/hobbit.png");
  game->surfaceUnites[ELFE] = IMG_Load("src/img/elfe.png");
  game->surfaceUnites[NAIN] = IMG_Load("src/img/nain.png");
  game->surfaceUnites[GANDALF] = IMG_Load("src/img/Gandalf.png");
  game->surfaceUnites[URUK] = IMG_Load("src/img/uruk.png");
  game->surfaceUnites[NAZGUL] = IMG_Load("src/img/nazgul.png");
  game->surfaceUnites[SMEAGOL] = IMG_Load("src/img/smeagol.png");
  game->surfaceUnites[SAROUMANE] = IMG_Load("src/img/saroumane.png");
  game->surfaceUnites[ORQUE] = IMG_Load("src/img/herb.png");
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

  //Initialisation des unites
  // Gentils :
  game->Nain.force = 0.6;
  game->Nain.defense = 0.3;
  game->Nain.zoneDeTir = 1;
  game->Nain.distance = 2;
  game->Nain.prix = 20;

  game->Hobbit.force = 0.4;
  game->Hobbit.defense = 0.4;
  game->Hobbit.zoneDeTir = 2;
  game->Hobbit.distance = 2;
  game->Hobbit.prix = 20;

  game->Elfe.force = 0.3;
  game->Elfe.defense = 0.6;
  game->Elfe.zoneDeTir = 4;
  game->Elfe.distance = 4;
  game->Elfe.prix = 30;

  game->Humain.force = 0.5;
  game->Humain.defense = 0.5;
  game->Humain.zoneDeTir = 1;
  game->Humain.distance = 2;
  game->Humain.prix = 30;

  game->Gandalf.force = 0.6;
  game->Gandalf.defense = 0.6;
  game->Gandalf.zoneDeTir = 2;
  game->Gandalf.distance = 2;
  game->Gandalf.prix = 50;

  //Mechants :
  game->Orque.force = 0.6;
  game->Orque.defense = 0.3;
  game->Orque.zoneDeTir = 1;
  game->Orque.distance = 2;
  game->Orque.prix = 20;

  game->Smeagol.force = 0.4;
  game->Smeagol.defense = 0.4;
  game->Smeagol.zoneDeTir = 2;
  game->Smeagol.distance = 2;
  game->Smeagol.prix = 20;

  game->Urukhai.force = 0.3;
  game->Urukhai.defense = 0.6;
  game->Urukhai.zoneDeTir = 4;
  game->Urukhai.distance = 4;
  game->Urukhai.prix = 30;

  game->Nazgul.force = 0.5;
  game->Nazgul.defense = 0.5;
  game->Nazgul.zoneDeTir = 1;
  game->Nazgul.distance = 2;
  game->Nazgul.prix = 30;

  game->Saruman.force = 0.6;
  game->Saruman.defense = 0.6;
  game->Saruman.zoneDeTir = 2;
  game->Saruman.distance = 2;
  game->Saruman.prix = 50;

  //Initialisation des boutons
  game->boutonDeplacement.x = 1.1; //Rose
  game->boutonDeplacement.y = 0.8;
  game->boutonDeplacement.longueur = 0.15;
  game->boutonDeplacement.hauteur = 0.05;
  game->boutonDeplacement.r = 0;
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
