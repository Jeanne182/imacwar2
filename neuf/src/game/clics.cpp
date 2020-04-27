#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

void gererClic(Game* game, SDL_Event e){
  switch(game->etapeJeu){

    //Première partie du jeu : placement des unités :
    case PLACEMENT_UNITES:
      placementUnitesJoueurs(game, e);
      cout<<game->etapeJeu<<endl;
      if(game->joueur1.nbUnites==4 && game->joueur2.nbUnites==4){ //A CHANGER
        game->etapeJeu = SELECTION_UNITE;
      }
      break;

    //Partie du jeu où les joueurs sélectionnent l'unité avec laquelle ils vont agir
    case SELECTION_UNITE:
      //sélection des coordonnées d'une unité du joueur dont c'est le tour
      selectionCoordonnee(&game->x,&game->y, e, game->surface);
      switch(game->tour){

        case TOUR_JOUEUR1:
        cout <<"joueur1"<<endl;
          if(selectionIdUnite(game->x, game->y, game->joueur1) != -1){
            selectionCoordonnee(&game->x,&game->y, e, game->surface);
            game->etapeJeu = ACTIONS;
            game->id1 = selectionIdUnite(game->x, game->y, game->joueur1);
            cout<<"Unité selectionnée, etape jeu :" << game->etapeJeu<<endl;
          }
          break;

        case TOUR_JOUEUR2:
          if(selectionIdUnite(game->x, game->y, game->joueur2) != -1){
            selectionCoordonnee(&game->x,&game->y, e, game->surface);
            game->etapeJeu = ACTIONS;
            game->id2 = selectionIdUnite(game->x, game->y, game->joueur2);
            cout<<"Unité selectionnée, etape jeu :" << game->etapeJeu<<endl;
          }
          break;

        default:
          break;
      }

      break;

    //Partie du jeu où les joueurs attaquent et se déplacent :
    case ACTIONS:
      switch(game->tour){

        case TOUR_JOUEUR1:
          switch (game->choix){

            case RIEN:
              if(selectionBouton(game, e) == DEPLACEMENT){
                game->choix = DEPLACEMENT;
                cout<<"CHOIX : déplacement"<<endl;
              }
              break;

            case DEPLACEMENT:
              deplacement(&game->joueur1, game->id1, e, game);
              game->tour = TOUR_JOUEUR2;
              cout<<"Prochain tour de jeu:" <<game->tour<<endl;
              game->choix = RIEN;
              game->etapeJeu = SELECTION_UNITE;
              break;
          }

          break;

        case TOUR_JOUEUR2:
          switch (game->choix){

            case RIEN:
              if(selectionBouton(game, e) == DEPLACEMENT){
                game->choix = DEPLACEMENT;
                cout<<"CHOIX : déplacement"<<endl;

              }
              break;

            case DEPLACEMENT:
              deplacement(&game->joueur2, game->id2, e, game);
              game->tour = TOUR_JOUEUR1;
              cout<<"Prochain tour de jeu:" <<game->tour<<endl;
              game->choix = RIEN;
              game->etapeJeu = SELECTION_UNITE;
              break;
          }
          break;
      }


      break;

    default:
      break;

  }
}
