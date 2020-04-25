#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"

void gererClic(Game* game, SDL_Event e){
  //Première partie du jeu : placement des unités
  if (game->etapeJeu ==0){
    placementUnitesJoueurs(game, e);
    if(game->joueur1.nbUnites==4 && game->joueur2.nbUnites==4){ //A CHANGER
      game->etapeJeu++;
    }
  }

  //Partie du jeu où les joueurs attaquent et se déplacent
  else{
    //sélection des coordonnées d'une unité du joueur dont c'est le tour
    if(game->etapeJeu==1){
      selectionCoordonnee(&game->x,&game->y, e, game->surface);
      if((game->tour ==1 && selectionIdUnite(game->x, game->y, game->joueur1) != -1)
              ||(game->tour ==2 && selectionIdUnite(game->x, game->y, game->joueur2) != -1)){
        game->etapeJeu++;
      }
    }
    //Le joueur choisi d'attquer ou de se déplacer
    else if(game->etapeJeu==2){
      if (game->tour == 1){
        int id1 = selectionIdUnite(game->x, game->y, game->joueur1);
        deplacement(&game->joueur1, id1, game->x, game->y, e, game->surface);
          game->tour = 2;
      }
      else{
        int id2 = selectionIdUnite(game->x, game->y, game->joueur2);
        deplacement(&game->joueur2, id2, game->x, game->y, e, game->surface);
        game->tour = 1;
      }
      game->etapeJeu = 1;
    }
  }

}
