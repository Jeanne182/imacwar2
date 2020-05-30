#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "joueur_ordi/a_star.h"
#include "joueur_ordi/joueur_ordi.h"
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
        case_selection(game, game->joueur1, 1);


          break;

        case TOUR_JOUEUR2:
        if(game->modeJeu==MULTIJOUEURS){
          if(selectionIdUnite(game->x, game->y, game->joueur2) != -1){
            if(game->uniteJouee[selectionIdUnite(game->x, game->y, game->joueur2)]==1){
              game->etapeJeu = SELECTION_UNITE;
              cout<<"Unité deja jouee" <<endl;
            }
            else{
              game->id2 = selectionIdUnite(game->x, game->y, game->joueur2);
              game->etapeJeu = ACTIONS;
            }
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
        case_actions(game, &game->joueur1, &game->joueur2, 1, e, game->id1);
          break;

        case TOUR_JOUEUR2:
          switch(game->modeJeu){

            case MULTIJOUEURS:
              case_actions(game, &game->joueur2, &game->joueur1, 2, e, game->id2);
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

void case_selection(Game* game, Joueur joueur, int id){
  if(selectionIdUnite(game->x, game->y, joueur) != -1){
    if(game->uniteJouee[selectionIdUnite(game->x, game->y, joueur)]==1){
      game->etapeJeu = SELECTION_UNITE;
      cout<<"Unité deja jouee" <<endl;
    }
    else{
      if(id==1){
        game->id1 = selectionIdUnite(game->x, game->y, joueur);
      }
      else{
        game->id2 = selectionIdUnite(game->x, game->y, joueur);
      }
      game->etapeJeu = ACTIONS;
    }
  }
}


void case_actions(Game* game, Joueur* joueurTour, Joueur* joueurEnnemi, int num, SDL_Event e, int id){
  switch (game->choix){

    case RIEN:
      case_rien(game, e, *joueurTour, num);
    break;

    case DEPLACEMENT:
      deplacement(joueurTour, id, e, game);
      case_deplacement(game, e);

    break;

    case ATTAQUE:
      attaque(joueurTour, joueurEnnemi, id, e, game);
      case_attaque(game, e);
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
  else if(selectionBouton(game, e) == RIEN){
    selectionCoordonnee(&game->x,&game->y, e, game->surface);
    if(selectionIdUnite(game->x, game->y, joueur)==-1){
      game->choix=RIEN;
      game->etapeJeu = SELECTION_UNITE;
      cout<<"Selection dans le vide" <<endl;
    }
    else {
      if(game->uniteJouee[selectionIdUnite(game->x, game->y, joueur)]==1){
      game->choix=RIEN;
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
