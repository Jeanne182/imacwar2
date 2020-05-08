/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"
#include "interface/text.h"
#include "game/game.h"
using namespace std;

bool placementUnite(Joueur *joueur, SDL_Event e, Game* game, int typeUnite){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite.id =id;
      unite.distance=3;
      unite.zoneDeTir=6;
      unite.type = typeUnite;
      unite.vie = 25;
      unite.force = 0.5;
      unite.defense = 0.4;


      //MODIFIé AVEC STEEVE
      int x=-1;
      int y=-1;

      selectionCoordonnee(&x,&y, e, game->surface);
      cout << "x : " << x << " y : " << y << endl;

      cout <<"choux 2 :"<<typeUnite<<endl;
      if(verificationZone(*joueur, x, y, game)==true && verificationCaseLibre(game, x, y)==true){

        insertionCoordonnees(game, &unite, x, y, joueur->tour);
        joueur->unites[id] = unite;

        joueur->nbUnites ++;
        joueur->nbUnitesInitial++;

        cout << "Type 2: "<< game->joueur1.unites[0].type<<endl;
        return true;
      }
    }
    return false;
}

bool placementUnitesJoueurs(Game* game, SDL_Event e){
  switch (game->etapeAchatUnite) {
    case ACHAT_UNITE:
      if (game->tour == TOUR_JOUEUR1){
        game->achat_type = selectioBoutonUniteJ1(game, e);
        cout << "achat type : " << game->achat_type << endl;
        game->etapeAchatUnite = CHOIX_EMPLACEMENT;
        return true;
      }
      else {
        game->achat_type = selectioBoutonUniteJ2(game, e);
        cout << "achat type : " << game->achat_type << endl;

        game->etapeAchatUnite = CHOIX_EMPLACEMENT;
        return true;
      }

    break;

      case CHOIX_EMPLACEMENT:
        if (game->tour == TOUR_JOUEUR1){
          if(placementUnite(&game->joueur1, e, game, game->achat_type)==true){
            game->achat_type = SANS_TYPE;
            game->tour = TOUR_JOUEUR2;
            game->etapeAchatUnite = ACHAT_UNITE;
            return true;
          }
        }
        else {
          if(placementUnite(&game->joueur2, e, game, game->achat_type)==true){
            game->achat_type = SANS_TYPE;
            game->tour = TOUR_JOUEUR1;
            game->etapeAchatUnite = ACHAT_UNITE;
            return true;
          }
        }
      break;

    default:
      break;
  }

  return false;
}

void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){
  int xNew=-1;
  int yNew=-1;

  selectionCoordonnee(&xNew,&yNew, e, game->surface);
  
  if(verificationCaseLibre(game, xNew, yNew)==true && verificationDistance(*joueur, xNew, yNew, id, game)==true){

    insertionCoordonnees(game, &joueur->unites[id], xNew, yNew, joueur->tour);
    cout << "case libre" << endl;

    // Changement de tour
    if(game->tour == TOUR_JOUEUR2){
      game->tour = TOUR_JOUEUR1;
    }
    else{
      game->tour = TOUR_JOUEUR2;
    }
    game->choix = RIEN;
    game->etapeJeu = SELECTION_UNITE;
  }
  else{
    cout << "Cette case est déjà occupée, veuillez choisir une autre case OU Votre distance de déplacement n'est pas respectée" << endl;
  }
}

void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int id, SDL_Event e, Game* game){
  int xAttaque=-1;
  int yAttaque=-1;
  int idEnnemi=-1;
  selectionCoordonnee(&xAttaque, &yAttaque, e, game->surface);
  if(verifUniteEnnemie(joueurEnnemi->tour, game, xAttaque, yAttaque)==true && verificationZoneTir(*joueurTour, xAttaque, yAttaque, id, game)==true){//rajouter zone de tire
    cout << "attaque gooo" << endl;

    // combat
    idEnnemi = selectionIdUnite(xAttaque, yAttaque, *joueurEnnemi);
    joueurEnnemi->unites[idEnnemi].vie -= (joueurTour->unites[id].force*(1 - joueurEnnemi->unites[idEnnemi].defense))*joueurTour->unites[id].vie;
    //if(distance respectée)
    joueurTour->unites[id].vie -= (joueurEnnemi->unites[idEnnemi].force*(1 - joueurTour->unites[id].defense))*joueurEnnemi->unites[idEnnemi].vie;
    cout << "force unite ennemie = " << joueurEnnemi->unites[idEnnemi].force<< endl;
    cout << "vie unite ennemie = " << joueurEnnemi->unites[idEnnemi].vie<< endl;
    cout << "force unite tour = " << joueurTour->unites[id].force<< endl;
    cout << "vie unite tour = " << joueurTour->unites[id].vie<< endl;

    //-----------A OPTIMISER ?----------//
    // Si une unite ennemie est tuee :
    if (joueurEnnemi->unites[idEnnemi].vie<=0){
      joueurEnnemi->unites[idEnnemi].vie=0;
      joueurEnnemi->nbUnites-=1;
      insertionCoordonnees(game, &joueurEnnemi->unites[idEnnemi], 0, 0, game->tour); //A voir si on les mets vraiment en (0,0)
      cout << "L'unite ennemie est morte" << endl;
    }
    // Si une unite du joueur est tuee :
    if (joueurTour->unites[id].vie<=0){
      joueurTour->unites[id].vie=0;
      joueurTour->nbUnites-=1;
      insertionCoordonnees(game, &joueurTour->unites[id], 0, 0, game->tour);

      cout << "Votre unite est morte" << endl;
    }

    // Changement de tour
    if(game->tour == TOUR_JOUEUR2){
      game->tour = TOUR_JOUEUR1;
    }
    else{
      game->tour = TOUR_JOUEUR2;
    }
    game->choix = RIEN;
    game->etapeJeu = SELECTION_UNITE;
  }
  else{
    cout << "Vous attaquez une de vos unites OU La distance de tir n'est pas respectée" << endl;
  }
}


void etatUnite(SDL_Event e, Game* game){
  int x = 0;
  int y = 0;
  selectionCoordonnee(&x, &y, e, game->surface);
  int id = selectionIdUnite(y,x,game->joueur1);
  if(id != -1){
    //cout<<"Coordonnées unité J1: "<< game->joueur1.unites[id].coord[0] <<" "<< game->joueur1.unites[id].coord[1]<<endl;
  }
  else{
    id = selectionIdUnite(y,x,game->joueur2);
    if(id != -1){
      //cout<<"Coordonnées unité J2: "<< game->joueur2.unites[id].coord[0] <<" "<< game->joueur2.unites[id].coord[1]<<endl;
    }
  }

  // if(id!=-1){
  //   cout <<"x : "<< x<<" y : "<<y<<"id : "<<id<<endl;
  // }
  // if(x >= 0 && x<= 1){
  //
  // }

  // GLuint vie;
  // char* contenuTexteVie = "Vie : ";
  // creationTexte(&vie, "src/fonts/SummitAttack.ttf", 65, contenuTexteVie, SDL_Color{0, 255, 0});
  // affichageTexture(vie, 1,0.1,1,0);
}
