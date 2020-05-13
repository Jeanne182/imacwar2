#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"
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
  game->joueur1.pieces = 100;

  game->joueur2.nbUnites=0;
  game->joueur2.nbUnitesInitial=0;
  game->joueur2.id = 2;
  game->joueur2.tour = JOUEUR2;
  game->joueur2.pieces = 100;

  //Initialisation des unites
  // Gentils :
  game->unites[NAIN].force = 0.6;
  game->unites[NAIN].defense = 0.3;
  game->unites[NAIN].zoneDeTir = 1;
  game->unites[NAIN].distance = 2;
  game->unites[NAIN].prix = 20;
  game->unites[NAIN].type = NAIN;

  game->unites[HOBBIT].force = 0.4;
  game->unites[HOBBIT].defense = 0.4;
  game->unites[HOBBIT].zoneDeTir = 2;
  game->unites[HOBBIT].distance = 2;
  game->unites[HOBBIT].prix = 20;
  game->unites[HOBBIT].type = HOBBIT;

  game->unites[ELFE].force = 0.3;
  game->unites[ELFE].defense = 0.6;
  game->unites[ELFE].zoneDeTir = 4;
  game->unites[ELFE].distance = 4;
  game->unites[ELFE].prix = 30;
  game->unites[ELFE].type = ELFE;

  game->unites[HUMAN].force = 0.5;
  game->unites[HUMAN].defense = 0.5;
  game->unites[HUMAN].zoneDeTir = 1;
  game->unites[HUMAN].distance = 2;
  game->unites[HUMAN].prix = 30;
  game->unites[HUMAN].type = HUMAN;

  game->unites[GANDALF].force = 0.6;
  game->unites[GANDALF].defense = 0.6;
  game->unites[GANDALF].zoneDeTir = 2;
  game->unites[GANDALF].distance = 2;
  game->unites[GANDALF].prix = 50;
  game->unites[GANDALF].type = GANDALF;

  //Mechants :
  game->unites[ORQUE].force = 0.6;
  game->unites[ORQUE].defense = 0.3;
  game->unites[ORQUE].zoneDeTir = 1;
  game->unites[ORQUE].distance = 2;
  game->unites[ORQUE].prix = 20;
  game->unites[ORQUE].type = ORQUE;

  game->unites[SMEAGOL].force = 0.4;
  game->unites[SMEAGOL].defense = 0.4;
  game->unites[SMEAGOL].zoneDeTir = 2;
  game->unites[SMEAGOL].distance = 2;
  game->unites[SMEAGOL].prix = 20;
  game->unites[SMEAGOL].type = SMEAGOL;

  game->unites[URUK].force = 0.3;
  game->unites[URUK].defense = 0.6;
  game->unites[URUK].zoneDeTir = 4;
  game->unites[URUK].distance = 4;
  game->unites[URUK].prix = 30;
  game->unites[URUK].type = URUK;

  game->unites[NAZGUL].force = 0.5;
  game->unites[NAZGUL].defense = 0.5;
  game->unites[NAZGUL].zoneDeTir = 1;
  game->unites[NAZGUL].distance = 2;
  game->unites[NAZGUL].prix = 30;
  game->unites[NAZGUL].type = NAZGUL;

  game->unites[SAROUMANE].force = 0.6;
  game->unites[SAROUMANE].defense = 0.6;
  game->unites[SAROUMANE].zoneDeTir = 2;
  game->unites[SAROUMANE].distance = 2;
  game->unites[SAROUMANE].prix = 50;
  game->unites[SAROUMANE].type = SAROUMANE;

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

  game->boutonAchat.x = 1.3;
  game->boutonAchat.y = 0.4;
  game->boutonAchat.longueur = 0.15;
  game->boutonAchat.hauteur = 0.05;
  game->boutonAchat.r = 0;
  game->boutonAchat.g = 1;
  game->boutonAchat.b = 1;
  game->boutonAchat.valeur = ACHAT;
/*
  game->boutonStopAchat.x = 1.3;
  game->boutonStopAchat.y = 0.6;
  game->boutonStopAchat.longueur = 0.15;
  game->boutonStopAchat.hauteur = 0.05;
  game->boutonStopAchat.r = 0.5;
  game->boutonStopAchat.g = 1.5;
  game->boutonStopAchat.b = 1;
  game->boutonStopAchat.valeur = STOP_ACHAT;
*/
  game->boutonHumain.x = 1.0;
  game->boutonHumain.y = 0.1;
  game->boutonHumain.longueur = 0.1;
  game->boutonHumain.hauteur = 0.1;
  game->boutonHumain.valeur = HUMAN;

  game->boutonGandalf.x = 1.80;
  game->boutonGandalf.y = 0.1;
  game->boutonGandalf.longueur = 0.1;
  game->boutonGandalf.hauteur = 0.1;
  game->boutonGandalf.valeur = GANDALF;

  game->boutonNain.x = 1.40;
  game->boutonNain.y = 0.1;
  game->boutonNain.longueur = 0.1;
  game->boutonNain.hauteur = 0.1;
  game->boutonNain.valeur = NAIN;

  game->boutonElfe.x = 1.60;
  game->boutonElfe.y = 0.1;
  game->boutonElfe.longueur = 0.1;
  game->boutonElfe.hauteur = 0.1;
  game->boutonElfe.valeur = ELFE;

  game->boutonHobbit.x = 1.20;
  game->boutonHobbit.y = 0.1;
  game->boutonHobbit.longueur = 0.1;
  game->boutonHobbit.hauteur = 0.1;
  game->boutonHobbit.valeur = HOBBIT;

  game->boutonOrque.x = 1.20;
  game->boutonOrque.y = 0.1;
  game->boutonOrque.longueur = 0.1;
  game->boutonOrque.hauteur = 0.1;
  game->boutonOrque.valeur = ORQUE;

  game->boutonSmeagol.x = 1.60;
  game->boutonSmeagol.y = 0.1;
  game->boutonSmeagol.longueur = 0.1;
  game->boutonSmeagol.hauteur = 0.1;
  game->boutonSmeagol.valeur = SMEAGOL;

  game->boutonUrukhai.x = 1.40;
  game->boutonUrukhai.y = 0.1;
  game->boutonUrukhai.longueur = 0.1;
  game->boutonUrukhai.hauteur = 0.1;
  game->boutonUrukhai.valeur = URUK;

  game->boutonNazgul.x = 1.0;
  game->boutonNazgul.y = 0.1;
  game->boutonNazgul.longueur = 0.1;
  game->boutonNazgul.hauteur = 0.1;
  game->boutonNazgul.valeur = NAZGUL;

  game->boutonSaruman.x = 1.80;
  game->boutonSaruman.y = 0.1;
  game->boutonSaruman.longueur = 0.1;
  game->boutonSaruman.hauteur = 0.1;
  game->boutonSaruman.valeur = SAROUMANE;


  game->etapeJeu = PLACEMENT_UNITES; //0 pour préparation, 1 pour attaque/déplacement
  game->tour = TOUR_JOUEUR1;
  game->choix = RIEN;
  game->etapeAchatUnite = ACHAT_UNITE;
  game->achat_type = SANS_TYPE;

  game->id1=-1;
  game->id2=-1;
  game->idUniteSurvolee=-1;
  game->xSurvol=-1;
  game->ySurvol=-1;
  //Initialisation textes
  //creationTexte(&game->textureTextes[1], "src/fonts/SummitAttack.ttf", 100, "Déplacement", SDL_Color{255,255,255});
  //initialisationTextes(game->textes);

  initialisationSDL(game);

  reshape(&game->surface, game->window_width, game->window_height);
}
