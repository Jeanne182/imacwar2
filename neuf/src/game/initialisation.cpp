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
                          { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }},xSurvol(0),ySurvol(0){} //Steeve a dit de rajouter ca

void initialisationGame(Game *game){
    initialisationSDL(game);//Steeve a dit de le mettre la ca
  //fenetre
  game->window_width = 1500;
  game->window_height = 800;
  game->bit_per_pixel = 32;
  game->framerate_milliseconds = 1000/60;
  game->aspectRatio = game->window_width / (float) game->window_height;

  //Initialisation textures
  game->surffond = IMG_Load("src/img/fond.png");
  game->surfaceCases[PLAINE] = IMG_Load("src/img/plaine.png");
  game->surfaceCases[EAU] = IMG_Load("src/img/eau.png");
  game->surfaceCases[ARBRE] = IMG_Load("src/img/arbre.png");
  game->surfaceUnites[VIKINGMAN] = IMG_Load("src/img/vikingman.png");
  game->surfaceUnites[VIKINGWOMAN] = IMG_Load("src/img/vikingwoman.png");
  game->surfaceUnites[VIKINGWIZARD] = IMG_Load("src/img/vikingwizard.png");
  game->surfaceUnites[VIKINGBEAST] = IMG_Load("src/img/vikingbeast.png");
  game->surfaceUnites[VIKINGCHIEF] = IMG_Load("src/img/vikingchief.png");
  game->surfaceUnites[DEADWIZARD] = IMG_Load("src/img/deadwizard.png");
  game->surfaceUnites[DEADMAN] = IMG_Load("src/img/deadman.png");
  game->surfaceUnites[DEADKNIGHT] = IMG_Load("src/img/deadknight.png");
  game->surfaceUnites[DEADCHIEF] = IMG_Load("src/img/deadchief.png");
  game->surfaceUnites[DEADBEAST] = IMG_Load("src/img/deadbeast.png");

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
  game->unites[VIKINGBEAST].force = 0.6;
  game->unites[VIKINGBEAST].vie = 100;
  game->unites[VIKINGBEAST].defense = 0.3;
  game->unites[VIKINGBEAST].zoneDeTir = 1;
  game->unites[VIKINGBEAST].distance = 2;
  game->unites[VIKINGBEAST].prix = 20;
  game->unites[VIKINGBEAST].type = VIKINGBEAST;

  game->unites[VIKINGWOMAN].force = 0.4;
  game->unites[VIKINGWOMAN].vie = 100;
  game->unites[VIKINGWOMAN].defense = 0.4;
  game->unites[VIKINGWOMAN].zoneDeTir = 2;
  game->unites[VIKINGWOMAN].distance = 2;
  game->unites[VIKINGWOMAN].prix = 10;
  game->unites[VIKINGWOMAN].type = VIKINGWOMAN;

  game->unites[VIKINGWIZARD].force = 0.3;
  game->unites[VIKINGWIZARD].vie = 100;
  game->unites[VIKINGWIZARD].defense = 0.6;
  game->unites[VIKINGWIZARD].zoneDeTir = 4;
  game->unites[VIKINGWIZARD].distance = 4;
  game->unites[VIKINGWIZARD].prix = 30;
  game->unites[VIKINGWIZARD].type = VIKINGWIZARD;

  game->unites[VIKINGMAN].force = 0.5;
  game->unites[VIKINGMAN].vie = 100;
  game->unites[VIKINGMAN].defense = 0.5;
  game->unites[VIKINGMAN].zoneDeTir = 1;
  game->unites[VIKINGMAN].distance = 2;
  game->unites[VIKINGMAN].prix = 30;
  game->unites[VIKINGMAN].type = VIKINGMAN;

  game->unites[VIKINGCHIEF].force = 0.6;
  game->unites[VIKINGCHIEF].vie = 100;
  game->unites[VIKINGCHIEF].defense = 0.6;
  game->unites[VIKINGCHIEF].zoneDeTir = 2;
  game->unites[VIKINGCHIEF].distance = 2;
  game->unites[VIKINGCHIEF].prix = 50;
  game->unites[VIKINGCHIEF].type = VIKINGCHIEF;

  //Mechants :
  game->unites[DEADBEAST].force = 0.6;
  game->unites[DEADBEAST].vie = 100;
  game->unites[DEADBEAST].defense = 0.3;
  game->unites[DEADBEAST].zoneDeTir = 1;
  game->unites[DEADBEAST].distance = 2;
  game->unites[DEADBEAST].prix =20;
  game->unites[DEADBEAST].type = DEADBEAST;

  game->unites[DEADKNIGHT].force = 0.4;
  game->unites[DEADKNIGHT].vie = 100;
  game->unites[DEADKNIGHT].defense = 0.4;
  game->unites[DEADKNIGHT].zoneDeTir = 2;
  game->unites[DEADKNIGHT].distance = 2;
  game->unites[DEADKNIGHT].prix = 10;
  game->unites[DEADKNIGHT].type = DEADKNIGHT;

  game->unites[DEADWIZARD].force = 0.3;
  game->unites[DEADWIZARD].vie = 100;
  game->unites[DEADWIZARD].defense = 0.6;
  game->unites[DEADWIZARD].zoneDeTir = 4;
  game->unites[DEADWIZARD].distance = 4;
  game->unites[DEADWIZARD].prix = 30;
  game->unites[DEADWIZARD].type = DEADWIZARD;

  game->unites[DEADMAN].force = 0.5;
  game->unites[DEADMAN].vie = 100;
  game->unites[DEADMAN].defense = 0.5;
  game->unites[DEADMAN].zoneDeTir = 1;
  game->unites[DEADMAN].distance = 2;
  game->unites[DEADMAN].prix = 30;
  game->unites[DEADMAN].type = DEADMAN;

  game->unites[DEADCHIEF].force = 0.6;
  game->unites[DEADCHIEF].vie = 100;
  game->unites[DEADCHIEF].defense = 0.6;
  game->unites[DEADCHIEF].zoneDeTir = 2;
  game->unites[DEADCHIEF].distance = 2;
  game->unites[DEADCHIEF].prix = 50;
  game->unites[DEADCHIEF].type = DEADCHIEF;

  //Initialisation des boutons

  game->bouton1Joueur.x = 0.7; //Rose
  game->bouton1Joueur.y = 0.5;
  game->bouton1Joueur.longueur = 0.15;
  game->bouton1Joueur.hauteur = 0.05;
  game->bouton1Joueur.r = 0.035;
  game->bouton1Joueur.g = 0.32;
  game->bouton1Joueur.b = 0.15;
  game->bouton1Joueur.valeur = ORDI_MODE;

  game->bouton2Joueurs.x = 0.7; //Rose
  game->bouton2Joueurs.y = 0.8;
  game->bouton2Joueurs.longueur = 0.15;
  game->bouton2Joueurs.hauteur = 0.05;
  game->bouton2Joueurs.r = 0.035;
  game->bouton2Joueurs.g = 0.32;
  game->bouton2Joueurs.b = 0.15;
  game->bouton2Joueurs.valeur = MULTIJOUEURS;


  game->boutonDeplacement.x = 1.1; //Rose
  game->boutonDeplacement.y = 0.8;
  game->boutonDeplacement.longueur = 0.2;
  game->boutonDeplacement.hauteur = 0.05;
  game->boutonDeplacement.r = 1;
  game->boutonDeplacement.g = 0;
  game->boutonDeplacement.b = 1;
  game->boutonDeplacement.valeur = DEPLACEMENT;

  //game->boutonAttaque.x = 1.5;
  //game->boutonAttaque.y = 0.8;
  game->boutonAttaque.x = 1.1;
  game->boutonAttaque.y = 0.5;
  game->boutonAttaque.longueur = 0.2;
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

  game->boutonVikingMan.x = 1.0;
  game->boutonVikingMan.y = 0.1;
  game->boutonVikingMan.longueur = 0.1;
  game->boutonVikingMan.hauteur = 0.1;
  game->boutonVikingMan.valeur = VIKINGMAN;

  game->boutonVikingChief.x = 1.80;
  game->boutonVikingChief.y = 0.1;
  game->boutonVikingChief.longueur = 0.1;
  game->boutonVikingChief.hauteur = 0.1;
  game->boutonVikingChief.valeur = VIKINGCHIEF;

  game->boutonVikingBeast.x = 1.40;
  game->boutonVikingBeast.y = 0.1;
  game->boutonVikingBeast.longueur = 0.1;
  game->boutonVikingBeast.hauteur = 0.1;
  game->boutonVikingBeast.valeur = VIKINGBEAST;

  game->boutonVikingWizard.x = 1.60;
  game->boutonVikingWizard.y = 0.1;
  game->boutonVikingWizard.longueur = 0.1;
  game->boutonVikingWizard.hauteur = 0.1;
  game->boutonVikingWizard.valeur = VIKINGWIZARD;

  game->boutonVikingWoman.x = 1.20;
  game->boutonVikingWoman.y = 0.1;
  game->boutonVikingWoman.longueur = 0.1;
  game->boutonVikingWoman.hauteur = 0.1;
  game->boutonVikingWoman.valeur = VIKINGWOMAN;

  game->boutonDeadBeast.x = 1.40;
  game->boutonDeadBeast.y = 0.1;
  game->boutonDeadBeast.longueur = 0.1;
  game->boutonDeadBeast.hauteur = 0.1;
  game->boutonDeadBeast.valeur = DEADBEAST;

  game->boutonDeadKnight.x = 1.20;
  game->boutonDeadKnight.y = 0.1;
  game->boutonDeadKnight.longueur = 0.1;
  game->boutonDeadKnight.hauteur = 0.1;
  game->boutonDeadKnight.valeur = DEADKNIGHT;

  game->boutonDeadWizard.x = 1.60;
  game->boutonDeadWizard.y = 0.1;
  game->boutonDeadWizard.longueur = 0.1;
  game->boutonDeadWizard.hauteur = 0.1;
  game->boutonDeadWizard.valeur = DEADWIZARD;

  game->boutonDeadMan.x = 1.0;
  game->boutonDeadMan.y = 0.1;
  game->boutonDeadMan.longueur = 0.1;
  game->boutonDeadMan.hauteur = 0.1;
  game->boutonDeadMan.valeur = DEADMAN;

  game->boutonDeadChief.x = 1.80;
  game->boutonDeadChief.y = 0.1;
  game->boutonDeadChief.longueur = 0.1;
  game->boutonDeadChief.hauteur = 0.1;
  game->boutonDeadChief.valeur = DEADCHIEF;


  game->etapeJeu = MENU; //0 pour préparation, 1 pour attaque/déplacement
  game->modeJeu = ORDI_MODE;
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

  game->policeTextes[TEXTE_BOUTON_DEPLACEMENT] = NULL;
  game->textureTextes[TEXTE_BOUTON_DEPLACEMENT] = NULL;

  game->policeTextes[TEXTE_BOUTON_ATTAQUE] = NULL;
  game->textureTextes[TEXTE_BOUTON_ATTAQUE] = NULL;

  game->policeTextes[TEXTE_BOUTON1J] = NULL;
  game->textureTextes[TEXTE_BOUTON1J] = NULL;

  game->policeTextes[TEXTE_BOUTON2J] = NULL;
  game->textureTextes[TEXTE_BOUTON2J] = NULL;

  game->policeTextes[TEXTE_PV] = NULL;
  game->textureTextes[TEXTE_PV] = NULL;


  game->policeTextes[TITRES] = TTF_OpenFont("src/fonts/anirm.ttf", 20); //Steeve a dit de l'initialiser ici



  reshape(&game->surface, game->window_width, game->window_height);

  initialisationTexturesCarte(game->textureCases, game->surfaceCases); //Steeve a dit de mettre ce deux fonctions ici car avant on le faisait ailleurs, ce qui est pas super logique au final je crois

  initialisationTexturesUnites(game->textureUnites, game->surfaceUnites);//à appeler à condition que l'unité se trouve dans les unités choisies par le joueur



}
