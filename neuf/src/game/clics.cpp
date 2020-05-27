#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "game/a_star.h"
using namespace std;

void gererClic(Game* game, SDL_Event e){
  switch(game->etapeJeu){
    case MENU:
      if(selectionBoutonMenu(game, e) == MULTIJOUEURS){
        game->etapeJeu = PLACEMENT_UNITES;
        game->modeJeu = MULTIJOUEURS;
      }
      if(selectionBoutonMenu(game, e) == ORDI_MODE){
        game->etapeJeu = PLACEMENT_UNITES;
        game->modeJeu = ORDI_MODE;
      }
      break;

    //Première partie du jeu : placement des unités :
    case PLACEMENT_UNITES:

      placementUnitesJoueurs(game, e);

      cout<<game->etapeJeu<<endl;

      if(game->joueur1.pieces==0 && game->joueur2.pieces==0){
        game->etapeJeu = SELECTION_UNITE;
        game->tour = TOUR_JOUEUR1;
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
            game->etapeJeu = ACTIONS;
            game->id1 = selectionIdUnite(game->x, game->y, game->joueur1);
            cout<<"Unité selectionnée, etape jeu :" << game->etapeJeu<<endl;
          }
          break;

        case TOUR_JOUEUR2:
          if(selectionIdUnite(game->x, game->y, game->joueur2) != -1){
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
              if(game->id1 != selectionIdUnite(game->x, game->y, game->joueur1)){
                game->id1 = selectionIdUnite(game->x, game->y, game->joueur1);
              }
              if(selectionBouton(game, e) == DEPLACEMENT){
                game->choix = DEPLACEMENT;
                cout<<"CHOIX : déplacement"<<endl;
              }
              else if(selectionBouton(game, e) == ATTAQUE){
                game->choix = ATTAQUE;
                cout<<"CHOIX : attaque"<<endl;
              }
              break;

            case DEPLACEMENT:
              deplacement(&game->joueur1, game->id1, e, game);
              if(selectionBouton(game, e) == ATTAQUE){
                game->choix = ATTAQUE;
                cout<<"CHOIX : attaque"<<endl;
              }
              cout<<"Prochain tour de jeu:" <<game->tour<<endl;
            break;

            case ATTAQUE:
              attaque(&game->joueur1, &game->joueur2, game->id1, e, game);
              if(selectionBouton(game, e) == DEPLACEMENT){
                game->choix = DEPLACEMENT;
                cout<<"CHOIX : déplacement"<<endl;
              }
              cout<<"Prochain tour de jeu:" <<game->tour<<endl;
            break;

          }

          break;

        case TOUR_JOUEUR2:
          switch(game->modeJeu){
            case ORDI_MODE:{
              for(int idOrdi=0; idOrdi<game->joueur2.nbUnitesInitial; idOrdi++){
                int xCible = -1;
                int yCible = -1;
                int xOrdi = game->joueur2.unites[idOrdi].coord[0];
                int yOrdi = game->joueur2.unites[idOrdi].coord[1];
                if(game->joueur2.unites[idOrdi].vie!=0){
                  choixCible(xOrdi, yOrdi,&xCible,&yCible, game->map);
                  list<Noeud> chemin = a_star(xOrdi,yOrdi, xCible, yCible, game->map);
                  caseOptimaleAtteignable(&xOrdi, &yOrdi, game->joueur2.unites[idOrdi].distance, chemin);
                  insertionCoordonnees(game, &game->joueur2.unites[idOrdi], xOrdi, yOrdi, JOUEUR2);
                }
              }
              // game->joueur2.unites[idOrdi].coord[0] = xOrdi;
              // game->joueur2.unites[idOrdi].coord[1] = yOrdi;
              // game->map[yOrdi-1][xOrdi-1]= JOUEUR2;
              }
              break;

            case MULTIJOUEURS:
              switch (game->choix){

                case RIEN:
                  if(game->id2 != selectionIdUnite(game->x, game->y, game->joueur2)){
                    game->id2 = selectionIdUnite(game->x, game->y, game->joueur2);
                  }
                  if(selectionBouton(game, e) == DEPLACEMENT){
                    game->choix = DEPLACEMENT;
                    cout<<"CHOIX : déplacement"<<endl;
                  }
                  else if(selectionBouton(game, e) == ATTAQUE){
                    game->choix = ATTAQUE;
                    cout<<"CHOIX : attaque"<<endl;
                  }
                  break;

                case DEPLACEMENT:
                  deplacement(&game->joueur2, game->id2, e, game);
                  if(selectionBouton(game, e) == ATTAQUE){
                    game->choix = ATTAQUE;
                    cout<<"CHOIX : attaque"<<endl;
                  }
                  cout<<"Prochain tour de jeu:" <<game->tour<<endl;
                break;

                case ATTAQUE:
                  attaque(&game->joueur2, &game->joueur1, game->id2, e, game);
                  if(selectionBouton(game, e) == DEPLACEMENT){
                    game->choix = DEPLACEMENT;
                    cout<<"CHOIX : déplacement"<<endl;
                  }
                  cout<<"Prochain tour de jeu:" <<game->tour<<endl;
                break;
              }
              break;
          }
          break;

      }
      break;



    default:
      break;

  }
}
