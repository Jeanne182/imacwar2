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

  //Initialisation de la carte
  game->longueurCarte = 10;
  game->hauteurCarte = 10;

  /*game->map[] = {{ 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
                      { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                      { 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
                      { 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
                      { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 }};*/

  /*game->map[0][0]=2;
  game->map[0][1]=2;
  game->map[0][2]=2;
  game->map[0][3]=0;
  game->map[0][4]=0;
  game->map[0][5]=0;
  game->map[0][6]=0;
  game->map[0][7]=0;
  game->map[0][8]=0;
  game->map[0][9]=0;

  game->map[1][0]=0;
  game->map[1][1]=0;
  game->map[1][2]=0;
  game->map[1][3]=0;
  game->map[1][4]=0;
  game->map[1][5]=0;
  game->map[1][6]=0;
  game->map[1][7]=0;
  game->map[1][8]=0;
  game->map[1][9]=0;

  game->map[2][0]=0;
  game->map[2][1]=0;
  game->map[2][2]=1;
  game->map[2][3]=1;
  game->map[2][4]=1;
  game->map[2][5]=1;
  game->map[2][6]=1;
  game->map[2][7]=1;
  game->map[2][8]=1;
  game->map[2][9]=1;

  game->map[3][0]=0;
  game->map[3][1]=0;
  game->map[3][2]=1;
  game->map[3][3]=0;
  game->map[3][4]=0;
  game->map[3][5]=0;
  game->map[3][6]=0;
  game->map[3][7]=0;
  game->map[3][8]=0;
  game->map[3][9]=0;

  game->map[4][1]=0;
  game->map[4][2]=1;
  game->map[4][3]=0;
  game->map[4][4]=1;
  game->map[4][5]=1;
  game->map[4][6]=0;
  game->map[4][7]=1;
  game->map[4][8]=0;
  game->map[4][9]=0;

  game->map[5][0]=0;
  game->map[5][1]=0;
  game->map[5][2]=1;
  game->map[5][3]=0;
  game->map[5][4]=1;
  game->map[5][5]=0;
  game->map[5][6]=0;
  game->map[5][7]=1;
  game->map[5][8]=1;
  game->map[5][9]=0;

  game->map[6][0]=0;
  game->map[6][1]=2;
  game->map[6][2]=0;
  game->map[6][3]=0;
  game->map[6][4]=1;
  game->map[6][5]=1;
  game->map[6][6]=0;
  game->map[6][7]=1;
  game->map[6][8]=0;
  game->map[6][9]=1;

  game->map[7][0]=0;
  game->map[7][1]=0;
  game->map[7][2]=1;
  game->map[7][3]=0;
  game->map[7][4]=1;
  game->map[7][5]=0;
  game->map[7][6]=0;
  game->map[7][7]=1;
  game->map[7][8]=0;
  game->map[7][9]=0;

  game->map[8][0]=0;
  game->map[8][1]=0;
  game->map[8][2]=1;
  game->map[8][3]=0;
  game->map[8][4]=1;
  game->map[8][5]=1;
  game->map[8][6]=0;
  game->map[8][7]=1;
  game->map[8][8]=0;
  game->map[8][9]=0;

  game->map[9][0]=0;
  game->map[9][1]=0;
  game->map[9][2]=1;
  game->map[9][3]=0;
  game->map[9][4]=0;
  game->map[9][5]=0;
  game->map[9][6]=0;
  game->map[9][7]=0;
  game->map[9][8]=0;
  game->map[9][9]=0;

  game->map[10][0]=0;
  game->map[10][1]=0;
  game->map[10][2]=1;
  game->map[10][3]=1;
  game->map[10][4]=1;
  game->map[10][5]=1;
  game->map[10][6]=1;
  game->map[10][7]=1;
  game->map[10][8]=1;
  game->map[10][9]=1;*/


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
