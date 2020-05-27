#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"
using namespace std;

Game::Game():map{{ ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE },
                 { ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                 { ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                 { ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, EAUHG, EAU, EAUHD, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, EAU, EAU, EAUBD, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, EAU, EAU, PLAINE, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, EAUBG, EAUBD, PLAINE, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                 { PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, EAUHG, EAUHD, PLAINE, PLAINE, PLAINE }},
            mapInit{{ ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE },
                    { ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                    { ARBRE, ARBRE, ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                    { ARBRE, ARBRE, ARBRE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, EAUHG, EAU, EAUHD, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, EAU, EAU, EAUBD, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, EAU, EAU, PLAINE, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, EAUBG, EAUBD, PLAINE, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, PLAINE },
                    { PLAINE, PLAINE, PLAINE, PLAINE, PLAINE, EAUHG, EAUHD, PLAINE, PLAINE, PLAINE }},
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
  game->surfacebouton = IMG_Load("src/img/bouton.png");
  game->surffond[MENUDEBUT] = IMG_Load("src/img/fond.png");
  game->surffond[MENUNORMAL] = IMG_Load("src/img/fondlat.png");
  game->surfaceCases[PLAINE] = IMG_Load("src/img/plaine.png");
  game->surfaceCases[EAU] = IMG_Load("src/img/eau.png");
  game->surfaceCases[ARBRE] = IMG_Load("src/img/arbre.png");
  game->surfaceCases[EAUHG] = IMG_Load("src/img/eauhg.png");
  game->surfaceCases[EAUHD] = IMG_Load("src/img/eauhd.png");
  game->surfaceCases[EAUBG] = IMG_Load("src/img/eaubg.png");
  game->surfaceCases[EAUBD] = IMG_Load("src/img/eaubd.png");
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
  game->unites[VIKINGMAN].force = 0.4;
  game->unites[VIKINGMAN].vie = 100;
  game->unites[VIKINGMAN].defense = 0.4;
  game->unites[VIKINGMAN].zoneDeTir = 2;
  game->unites[VIKINGMAN].distance = 2;
  game->unites[VIKINGMAN].prix = 10;
  game->unites[VIKINGMAN].nom = "Guerrier fauve";
  game->unites[VIKINGMAN].type = VIKINGMAN;

  game->unites[VIKINGBEAST].force = 0.6;
  game->unites[VIKINGBEAST].vie = 100;
  game->unites[VIKINGBEAST].defense = 0.3;
  game->unites[VIKINGBEAST].zoneDeTir = 1;
  game->unites[VIKINGBEAST].distance = 2;
  game->unites[VIKINGBEAST].prix = 20;
  game->unites[VIKINGBEAST].nom = "Ours des montagnes";
  game->unites[VIKINGBEAST].type = VIKINGBEAST;

  game->unites[VIKINGWOMAN].force = 0.5;
  game->unites[VIKINGWOMAN].vie = 100;
  game->unites[VIKINGWOMAN].defense = 0.5;
  game->unites[VIKINGWOMAN].zoneDeTir = 1;
  game->unites[VIKINGWOMAN].distance = 2;
  game->unites[VIKINGWOMAN].prix = 30;
  game->unites[VIKINGWOMAN].nom = "Guerrière sanguinaire";
  game->unites[VIKINGWOMAN].type = VIKINGWOMAN;

  game->unites[VIKINGWIZARD].force = 0.3;
  game->unites[VIKINGWIZARD].vie = 100;
  game->unites[VIKINGWIZARD].defense = 0.6;
  game->unites[VIKINGWIZARD].zoneDeTir = 4;
  game->unites[VIKINGWIZARD].distance = 4;
  game->unites[VIKINGWIZARD].prix = 30;
  game->unites[VIKINGWIZARD].nom = "Mage de feu";
  game->unites[VIKINGWIZARD].type = VIKINGWIZARD;

  game->unites[VIKINGCHIEF].force = 0.6;
  game->unites[VIKINGCHIEF].vie = 100;
  game->unites[VIKINGCHIEF].defense = 0.6;
  game->unites[VIKINGCHIEF].zoneDeTir = 2;
  game->unites[VIKINGCHIEF].distance = 2;
  game->unites[VIKINGCHIEF].prix = 50;
  game->unites[VIKINGCHIEF].nom = "Chef viking";
  game->unites[VIKINGCHIEF].type = VIKINGCHIEF;

  //Mechants :
  game->unites[DEADMAN].force = 0.4;
  game->unites[DEADMAN].vie = 100;
  game->unites[DEADMAN].defense = 0.4;
  game->unites[DEADMAN].zoneDeTir = 2;
  game->unites[DEADMAN].distance = 2;
  game->unites[DEADMAN].prix = 10;
  game->unites[DEADMAN].nom = "Marcheur noir";
  game->unites[DEADMAN].type = DEADMAN;

  game->unites[DEADBEAST].force = 0.6;
  game->unites[DEADBEAST].vie = 100;
  game->unites[DEADBEAST].defense = 0.3;
  game->unites[DEADBEAST].zoneDeTir = 1;
  game->unites[DEADBEAST].distance = 2;
  game->unites[DEADBEAST].prix =20;
  game->unites[DEADBEAST].nom = "Loup des glaces";
  game->unites[DEADBEAST].type = DEADBEAST;

  game->unites[DEADKNIGHT].force = 0.5;
  game->unites[DEADKNIGHT].vie = 100;
  game->unites[DEADKNIGHT].defense = 0.5;
  game->unites[DEADKNIGHT].zoneDeTir = 1;
  game->unites[DEADKNIGHT].distance = 2;
  game->unites[DEADKNIGHT].prix = 30;
  game->unites[DEADKNIGHT].nom = "Chevalier noir";
  game->unites[DEADKNIGHT].type = DEADKNIGHT;

  game->unites[DEADWIZARD].force = 0.3;
  game->unites[DEADWIZARD].vie = 100;
  game->unites[DEADWIZARD].defense = 0.6;
  game->unites[DEADWIZARD].zoneDeTir = 4;
  game->unites[DEADWIZARD].distance = 4;
  game->unites[DEADWIZARD].prix = 30;
  game->unites[DEADWIZARD].nom = "Mage noir";
  game->unites[DEADWIZARD].type = DEADWIZARD;

  game->unites[DEADCHIEF].force = 0.6;
  game->unites[DEADCHIEF].vie = 100;
  game->unites[DEADCHIEF].defense = 0.6;
  game->unites[DEADCHIEF].zoneDeTir = 2;
  game->unites[DEADCHIEF].distance = 2;
  game->unites[DEADCHIEF].prix = 50;
  game->unites[DEADCHIEF].nom = "Agent de la mort";
  game->unites[DEADCHIEF].type = DEADCHIEF;

  //Initialisation des boutons
  game->bouton1Joueur.x = 0.8;
  game->bouton1Joueur.y = 0.6;
  game->bouton1Joueur.longueur = 0.3;
  game->bouton1Joueur.hauteur = 0.1;
  game->bouton1Joueur.r = 0.035;
  game->bouton1Joueur.g = 0.32;
  game->bouton1Joueur.b = 0.15;
  game->bouton1Joueur.a = 0;
  game->bouton1Joueur.valeur = ORDI_MODE;

  game->bouton2Joueurs.x = 0.8; //Rose
  game->bouton2Joueurs.y = 0.8;
  game->bouton2Joueurs.longueur = 0.3;
  game->bouton2Joueurs.hauteur = 0.1;
  game->bouton2Joueurs.r = 0.035;
  game->bouton2Joueurs.g = 0.32;
  game->bouton2Joueurs.b = 0.15;
  game->bouton2Joueurs.a = 0;
  game->bouton2Joueurs.valeur = MULTIJOUEURS;


  game->boutonDeplacement.x = 1.1; //Rose
  game->boutonDeplacement.y = 0.5;
  game->boutonDeplacement.longueur = 0.3;
  game->boutonDeplacement.hauteur = 0.1;
  game->boutonDeplacement.r = 1;
  game->boutonDeplacement.g = 0;
  game->boutonDeplacement.b = 1;
  game->boutonDeplacement.a = 0;
  game->boutonDeplacement.valeur = DEPLACEMENT;

  //game->boutonAttaque.x = 1.5;
  //game->boutonAttaque.y = 0.8;
  game->boutonAttaque.x = 1.48;
  game->boutonAttaque.y = 0.5;
  game->boutonAttaque.longueur = 0.3;
  game->boutonAttaque.hauteur = 0.1;
  game->boutonAttaque.r = 0; //bleu
  game->boutonAttaque.g = 0;
  game->boutonAttaque.b = 1;
  game->boutonAttaque.a = 0;
  game->boutonAttaque.valeur = ATTAQUE;

  game->boutonPasser.x = 1.29;
  game->boutonPasser.y = 0.65;
  game->boutonPasser.longueur =0.3;
  game->boutonPasser.hauteur =0.1;
  game->boutonPasser.r = 1;
  game->boutonPasser.g = 0;
  game->boutonPasser.b = 0;
  game->boutonPasser.a = 0;
  game->boutonPasser.valeur = PASSER;

  game->boutonAchat.x = 1.31;
  game->boutonAchat.y = 0.82;
  game->boutonAchat.longueur = 0.25;
  game->boutonAchat.hauteur = 0.08;
  game->boutonAchat.r = 0;
  game->boutonAchat.g = 0;
  game->boutonAchat.b = 0;
  game->boutonAchat.a = 0;
  game->boutonAchat.valeur = ACHAT;

  game->boutonVikingMan.x = 1.1;
  game->boutonVikingMan.y = 0.15;
  game->boutonVikingMan.longueur = 0.15;
  game->boutonVikingMan.hauteur = 0.15;
  game->boutonVikingMan.valeur = VIKINGMAN;

  game->boutonVikingBeast.x = 1.36;
  game->boutonVikingBeast.y = 0.15;
  game->boutonVikingBeast.longueur = 0.15;
  game->boutonVikingBeast.hauteur = 0.15;
  game->boutonVikingBeast.valeur = VIKINGBEAST;

  game->boutonVikingWoman.x = 1.62;
  game->boutonVikingWoman.y = 0.15;
  game->boutonVikingWoman.longueur = 0.15;
  game->boutonVikingWoman.hauteur = 0.15;
  game->boutonVikingWoman.valeur = VIKINGWOMAN;

  game->boutonVikingWizard.x = 1.1;
  game->boutonVikingWizard.y = 0.35;
  game->boutonVikingWizard.longueur = 0.15;
  game->boutonVikingWizard.hauteur = 0.15;
  game->boutonVikingWizard.valeur = VIKINGWIZARD;

  game->boutonVikingChief.x = 1.36;
  game->boutonVikingChief.y = 0.35;
  game->boutonVikingChief.longueur = 0.15;
  game->boutonVikingChief.hauteur = 0.15;
  game->boutonVikingChief.valeur = VIKINGCHIEF;

  game->boutonDeadMan.x = 1.1;
  game->boutonDeadMan.y = 0.15;
  game->boutonDeadMan.longueur = 0.15;
  game->boutonDeadMan.hauteur = 0.15;
  game->boutonDeadMan.valeur = DEADMAN;

  game->boutonDeadBeast.x = 1.36;
  game->boutonDeadBeast.y = 0.15;
  game->boutonDeadBeast.longueur = 0.15;
  game->boutonDeadBeast.hauteur = 0.15;
  game->boutonDeadBeast.valeur = DEADBEAST;

  game->boutonDeadKnight.x = 1.62;
  game->boutonDeadKnight.y = 0.15;
  game->boutonDeadKnight.longueur = 0.15;
  game->boutonDeadKnight.hauteur = 0.15;
  game->boutonDeadKnight.valeur = DEADKNIGHT;

  game->boutonDeadWizard.x = 1.1;
  game->boutonDeadWizard.y = 0.35;
  game->boutonDeadWizard.longueur = 0.15;
  game->boutonDeadWizard.hauteur = 0.15;
  game->boutonDeadWizard.valeur = DEADWIZARD;

  game->boutonDeadChief.x = 1.36;
  game->boutonDeadChief.y = 0.35;
  game->boutonDeadChief.longueur = 0.15;
  game->boutonDeadChief.hauteur = 0.15;
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


  game->policeTextes[TITRES] = TTF_OpenFont("src/fonts/anirm.ttf", 35);
  game->policeTextes[TITRES_BOUTONS] = TTF_OpenFont("src/fonts/anirm.ttf", 25);

  game->policeTextes[SOUSTITRES] = TTF_OpenFont("src/fonts/anirm.ttf", 20); //Steeve a dit de l'initialiser ici
  game->policeTextes[NORMAL] = TTF_OpenFont("src/fonts/normal.ttf", 25);



  reshape(&game->surface, game->window_width, game->window_height);

  initialisationTexturesCarte(game->textureCases, game->surfaceCases); //Steeve a dit de mettre ce deux fonctions ici car avant on le faisait ailleurs, ce qui est pas super logique au final je crois

  initialisationTexturesUnites(game->textureUnites, game->surfaceUnites);//à appeler à condition que l'unité se trouve dans les unités choisies par le joueur



}
