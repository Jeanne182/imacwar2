#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

void gererClic(Game* game, SDL_Event e){
  switch(game->etapeJeu){

    //Première partie du jeu : placement des unités :
    case PLACEMENT_UNITES:
      if(placementUnitesJoueurs(game, e)==false){
        cout << "Vous êtes hors de votre zone de placement, veuillez placer votre unité dans votre zone." << endl;
      }
      cout<<game->etapeJeu<<endl;

      if(game->joueur1.nbUnites==2 && game->joueur2.nbUnites==2){ //A CHANGER
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
          switch (game->choix){

            case RIEN:
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

    default:
      break;

  }
}
