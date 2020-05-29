#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "game/a_star.h"
#include "interface/text.h"
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
      //selection des coordonnées d'une unité du joueur dont c'est le tour
      selectionCoordonnee(&game->x,&game->y, e, game->surface);
      switch(game->tour){

        case TOUR_JOUEUR1:
        cout <<"joueur1"<<endl;

          if(selectionIdUnite(game->x, game->y, game->joueur1) != -1){
            if(game->uniteJouee[selectionIdUnite(game->x, game->y, game->joueur1)]==1){
              game->etapeJeu = SELECTION_UNITE;
              cout<<"Unité deja jouee" <<endl;
            }
            else{
              game->id1 = selectionIdUnite(game->x, game->y, game->joueur1);
              game->etapeJeu = ACTIONS;
              cout<<"Unité selectionnée, etape jeu :" << game->etapeJeu<<endl;
            }
          }

          break;

        case TOUR_JOUEUR2:
        cout <<"joueur2"<<endl;

        if(selectionIdUnite(game->x, game->y, game->joueur2) != -1){
          if(game->uniteJouee[selectionIdUnite(game->x, game->y, game->joueur2)]==1){
            game->etapeJeu = SELECTION_UNITE;
            cout<<"Unité deja jouee" <<endl;
          }
          else{
            game->id2 = selectionIdUnite(game->x, game->y, game->joueur2);
            game->etapeJeu = ACTIONS;
            cout<<"Unité selectionnée, etape jeu :" << game->etapeJeu<<endl;
          }
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
              case_rien(game, e, game->joueur1, 1);
            break;

            case DEPLACEMENT:
              deplacement(&game->joueur1, game->id1, e, game);
              case_deplacement(game, e);

            break;

            case ATTAQUE:
              attaque(&game->joueur1, &game->joueur2, game->id1, e, game);
              case_attaque(game, e);
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
                  //choixCible(xOrdi, yOrdi,&xCible,&yCible, game->map);
                  // list<Noeud> chemin = a_star(xOrdi,yOrdi, xCible, yCible, game->map);
                  // caseOptimaleAtteignable(&xOrdi, &yOrdi, game->joueur2.unites[idOrdi].distance, chemin);
                  // insertionCoordonnees(game, &game->joueur2.unites[idOrdi], xOrdi, yOrdi, JOUEUR2);
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
                  case_rien(game, e, game->joueur2, 2);
                break;

                case DEPLACEMENT:
                  deplacement(&game->joueur2, game->id2, e, game);
                  case_deplacement(game, e);
                break;

                case ATTAQUE:
                  attaque(&game->joueur2, &game->joueur1, game->id2, e, game);
                  case_attaque(game, e);
                break;
              }
              break;
          }
          break;

      }
      break;

      case FIN_JEU:
      if(selectionBouton(game, e) == REJOUER){
        enleveUnite(game->mapObstacles, game->joueur1, game->joueur2);
        initialisationDynamique(game);
      }
      else if(selectionBouton(game, e) == QUITTER){
        finJeu(game);
      }
      break;


    default:
      break;

  }
}

void case_rien(Game* game, SDL_Event e, Joueur joueur, int id){
  if(selectionBouton(game, e) == DEPLACEMENT){
    game->choix = DEPLACEMENT;
    cout<<"CHOIX : déplacement"<<endl;
  }
  else if(selectionBouton(game, e) == ATTAQUE){
    game->choix = ATTAQUE;
    cout<<"CHOIX : attaque"<<endl;
  }
  else if(selectionBouton(game, e) == PASSER){
    passerTour(game);
    cout<<"CHOIX : passer"<<endl;
  }
  else{
    selectionCoordonnee(&game->x,&game->y, e, game->surface);
    if(game->uniteJouee[selectionIdUnite(game->x, game->y, joueur)]==1){
      game->etapeJeu = SELECTION_UNITE;
      cout<<"Unité deja jouee" <<endl;
    }
    else{
      if(id==1){
        if(game->id1 != selectionIdUnite(game->x, game->y, joueur)){
          game->id1 = selectionIdUnite(game->x, game->y, joueur);
        }
      }
      else{
        if(game->id2 != selectionIdUnite(game->x, game->y, joueur)){
          game->id2 = selectionIdUnite(game->x, game->y, joueur);
        }
      }

    }
  }
}



void case_deplacement(Game* game, SDL_Event e){
  if(selectionBouton(game, e) == ATTAQUE){
    game->choix = ATTAQUE;
    cout<<"CHOIX : attaque"<<endl;
  }
  else if(selectionBouton(game, e) == PASSER){
    passerTour(game);
    cout<<"CHOIX : passer"<<endl;
  }
  else if(selectionBouton(game, e) == RIEN){
    game->choix=RIEN;
  }
  cout<<"Prochain tour de jeu:" <<game->tour<<endl;
}



void case_attaque(Game* game, SDL_Event e){
  if(selectionBouton(game, e) == DEPLACEMENT){
    game->choix = DEPLACEMENT;
    cout<<"CHOIX : déplacement"<<endl;
  }
  else if(selectionBouton(game, e) == PASSER){
    passerTour(game);
    cout<<"CHOIX : passer"<<endl;
  }
  else if(selectionBouton(game, e) == RIEN){
    game->choix=RIEN;
  }
  cout<<"Prochain tour de jeu:" <<game->tour<<endl;
}
