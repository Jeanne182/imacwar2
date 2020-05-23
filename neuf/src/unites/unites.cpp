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

    Unite unite;
    unite = game->unites[typeUnite];

    //MODIFIé AVEC STEEVE
    int x=-1;
    int y=-1;

    selectionCoordonnee(&x,&y, e, game->surface);
    cout << "x : " << x << " y : " << y << endl;

    if(verificationZone(*joueur, x, y, game)==true && verificationCaseLibre(game, x, y)==true){

      insertionCoordonnees(game, &unite, x, y, joueur->tour);
      joueur->unites[id] = unite;
      joueur->nbUnites ++;
      joueur->nbUnitesInitial++;
      joueur->pieces -= unite.prix;
      cout << "Pieces du joueur après achat : " << joueur->pieces  << endl;
      return true;
    }

    cout << "Vous êtes hors de votre zone de placement, veuillez placer votre unité dans votre zone." << endl;
    return false;
}

bool placementUniteOrdi(Joueur *joueur, int x, int y, Game* game, int typeUnite){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite = game->unites[typeUnite];

      if(verificationZone(*joueur, x, y, game)==true && verificationCaseLibre(game, x, y)==true){

        insertionCoordonnees(game, &unite, x, y, joueur->tour);
        joueur->unites[id] = unite;
        joueur->nbUnites ++;
        joueur->nbUnitesInitial++;
        joueur->pieces -= unite.prix;
        cout << "Pieces du joueur après achat : " << joueur->pieces  << endl;
        return true;
      }
    }
    cout << "Vous êtes hors de votre zone de placement, veuillez placer votre unité dans votre zone." << endl;
    return false;
}

void placementUnitesJoueurs(Game* game, SDL_Event e){
  switch (game->etapeAchatUnite) {
    case ACHAT_UNITE:
      if (game->tour == TOUR_JOUEUR1){
        if(selectionBouton(game, e) == ACHAT && game->achat_type != SANS_TYPE && verificationPrix(game->joueur1, game->unites[game->achat_type])==true){
          cout<<"ETAPE : achat"<<endl;
          game->etapeAchatUnite = CHOIX_EMPLACEMENT;
        }
        else {
          game->achat_type = selectionBoutonUnite(game, e);
          

        }
      }
      else {
        if(game->modeJeu ==MULTIJOUEURS){
          if(selectionBouton(game, e) == ACHAT && game->achat_type != SANS_TYPE && verificationPrix(game->joueur2, game->unites[game->achat_type])==true){
            cout<<"ETAPE : achat"<<endl;
            game->etapeAchatUnite = CHOIX_EMPLACEMENT;
          }
          else {
            game->achat_type = selectionBoutonUnite(game, e);
          }
        }
        else {game->etapeAchatUnite = CHOIX_EMPLACEMENT;}
      }

      cout << "achat type : " << game->achat_type << endl;
    break;

      case CHOIX_EMPLACEMENT:
        if (game->tour == TOUR_JOUEUR1){
          if(placementUnite(&game->joueur1, e, game, game->achat_type)==true){
            if(game->joueur2.pieces==0){
              game->tour = TOUR_JOUEUR1;
            }
            else{
              game->tour = TOUR_JOUEUR2;
            }
            game->achat_type = SANS_TYPE;
            game->etapeAchatUnite = ACHAT_UNITE;

          }
        }
        else {
          if(game->modeJeu == MULTIJOUEURS){
            if(placementUnite(&game->joueur2, e, game, game->achat_type)==true){
              if(game->joueur1.pieces==0){
                game->tour = TOUR_JOUEUR2;
              }
              else{
                game->tour = TOUR_JOUEUR1;
              }
              game->achat_type = SANS_TYPE;
              game->etapeAchatUnite = ACHAT_UNITE;

            }
          }

          else{ /////JOUEUR = ORDI
            int rand_unite = rand()%5 + 5;
            cout<<"rand_unite : "<< rand_unite<<endl;
            while (verificationPrix(game->joueur2, game->unites[rand_unite])==false){
              rand_unite = rand()%5 + 5;
              cout<<"rand_unite : "<< rand_unite<<endl;
            }
            int rand_x = rand()%10 + 1; //?
            int rand_y = rand()%10 + 1; //?

            while(placementUniteOrdi(&game->joueur2, rand_x, rand_y, game, rand_unite)==false){
              rand_x = rand()%10 + 1; //?
              rand_y = rand()%10 + 1;
              cout<<"x,y: "<< rand_x<< ", "<<rand_y<<" puis ";
            }
            cout<<endl;
            if(game->joueur1.pieces==0){
              game->tour = TOUR_JOUEUR2;
            }
            else{
              game->tour = TOUR_JOUEUR1;
            }
            game->achat_type = SANS_TYPE;
            game->etapeAchatUnite = ACHAT_UNITE;

          }
        }
      break;
    }
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

    if(joueurTour->nbUnites == 0 || joueurEnnemi->nbUnites == 0){
      game->etapeJeu = FIN_JEU;
    }
    else{
      if(game->tour == TOUR_JOUEUR2){
        game->tour = TOUR_JOUEUR1;
      }
      else{
        game->tour = TOUR_JOUEUR2;
      }
      game->choix = RIEN;
      game->etapeJeu = SELECTION_UNITE;
    }

  }
  else{
    cout << "Vous attaquez une de vos unites OU La distance de tir n'est pas respectée" << endl;
  }
}

// void blabla(Unite unite){
//   char* pv = conversionTexteDyna(unite.vie, "Points de vie (points): ");
//   char* force = conversionTexteDyna(unite.force*100, "Force (%) : ");
//   char* defense = conversionTexteDyna(unite.defense*100, "Défense (%) : ");
//   char* zone = conversionTexteDyna(unite.zoneDeTir, "Zone de tir (cases) : ");
//   char* deplacement = conversionTexteDyna(game->joueur1.unites[id].distance, "Distance de déplacement (cases) : ");
// }

// void etatUnite(SDL_Event e, Game* game){
//   int x = 0;
//   int y = 0;
//   selectionCoordonnee(&x, &y, e, game->surface);
//   int id = selectionIdUnite(x,y,game->joueur1);
void etatUnite(Unite unite, Game* game){ //int id,Game* game
  // if(unite != SANS_TYPE){
    // zoneSurbrillance(game->joueur1,id, game->map,DEPLACEMENT);
    // cout<<"Coordonnées unité J1: "<< game->joueur1.unites[id].coord[0] <<" "<< game->joueur1.unites[id].coord[1]<<endl;

    if(game->textureTextes[TEXTE_PRIX]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PRIX]);
    }
    if(game->textureTextes[TEXTE_PV]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PV]);
    }
    if(game->textureTextes[TEXTE_FORCE]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_FORCE]);
    }
    if(game->textureTextes[TEXTE_DEFENSE]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_DEFENSE]);
    }
    if(game->textureTextes[TEXTE_ZONE]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_ZONE]);
    }
    if(game->textureTextes[TEXTE_RANGE]!=NULL){
      glDeleteTextures(1, &game->textureTextes[TEXTE_RANGE]);
    }


    char* prix = conversionTexteDyna(unite.prix, "Prix : ");
    char* pv = conversionTexteDyna(unite.vie, "Points de vie : ");
    char* force = conversionTexteDyna(unite.force*100, "Force (%) : ");
    char* defense = conversionTexteDyna(unite.defense*100, "Défense (%) : ");
    char* zone = conversionTexteDyna(unite.zoneDeTir, "Zone de tir (cases) : ");
    char* deplacement = conversionTexteDyna(unite.distance, "Distance de déplacement (cases) : ");

    creationTexte(&game->surfaceTextes[TEXTE_PRIX], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_PRIX], prix, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_PRIX], game->textureTextes[TEXTE_PRIX], 1.4, 0.5);

    creationTexte(&game->surfaceTextes[TEXTE_PV], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_PV], pv, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_PV], game->textureTextes[TEXTE_PV], 1.4, 0.55);

    creationTexte(&game->surfaceTextes[TEXTE_FORCE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_FORCE], force, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_FORCE], game->textureTextes[TEXTE_FORCE], 1.4, 0.6);

    creationTexte(&game->surfaceTextes[TEXTE_DEFENSE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_DEFENSE], defense, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_DEFENSE], game->textureTextes[TEXTE_DEFENSE], 1.4, 0.65);

    creationTexte(&game->surfaceTextes[TEXTE_ZONE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_ZONE], zone, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_ZONE], game->textureTextes[TEXTE_ZONE], 1.4, 0.7);

    creationTexte(&game->surfaceTextes[TEXTE_RANGE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_RANGE], deplacement, SDL_Color{255,255,255});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_RANGE], game->textureTextes[TEXTE_RANGE], 1.4, 0.75);

    free(deplacement);
    free(zone);
    free(defense);
    free(force);
    free(pv);
    free(prix);
  }
  // else{
  //   if(unite != SANS_TYPE){
  //     if(game->textureTextes[TEXTE_PV]!=NULL){
  //       glDeleteTextures(1, &game->textureTextes[TEXTE_PV]);
  //
  //
  //     }
  //     if(game->textureTextes[TEXTE_FORCE]!=NULL){
  //       glDeleteTextures(1, &game->textureTextes[TEXTE_FORCE]);
  //
  //     }
  //     if(game->textureTextes[TEXTE_DEFENSE]!=NULL){
  //       glDeleteTextures(1, &game->textureTextes[TEXTE_DEFENSE]);
  //
  //     }
  //     if(game->textureTextes[TEXTE_ZONE]!=NULL){
  //       glDeleteTextures(1, &game->textureTextes[TEXTE_ZONE]);
  //
  //     }
  //     if(game->textureTextes[TEXTE_RANGE]!=NULL){
  //       glDeleteTextures(1, &game->textureTextes[TEXTE_RANGE]);
  //     }
  //     char* pv = conversionTexteDyna(unite.vie, "Points de vie (points): ");
  //     char* force = conversionTexteDyna(unite.force*100, "Force (%) : ");
  //     char* defense = conversionTexteDyna(unite.defense*100, "Défense (%) : ");
  //     char* zone = conversionTexteDyna(unite.zoneDeTir, "Zone de tir (cases) : ");
  //     char* deplacement = conversionTexteDyna(unite.distance, "Distance de déplacement (cases) : ");
  //
  //     creationTexte(&game->surfaceTextes[TEXTE_PV], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_PV], pv, SDL_Color{255,255,255});
  //     affichageTextureTextes(&game->surfaceTextes[TEXTE_PV], game->textureTextes[TEXTE_PV], 1.4, 0.5);
  //
  //     creationTexte(&game->surfaceTextes[TEXTE_FORCE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_FORCE], force, SDL_Color{255,255,255});
  //     affichageTextureTextes(&game->surfaceTextes[TEXTE_FORCE], game->textureTextes[TEXTE_FORCE], 1.4, 0.55);
  //
  //     creationTexte(&game->surfaceTextes[TEXTE_DEFENSE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_DEFENSE], defense, SDL_Color{255,255,255});
  //     affichageTextureTextes(&game->surfaceTextes[TEXTE_DEFENSE], game->textureTextes[TEXTE_DEFENSE], 1.4, 0.6);
  //
  //     creationTexte(&game->surfaceTextes[TEXTE_ZONE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_ZONE], zone, SDL_Color{255,255,255});
  //     affichageTextureTextes(&game->surfaceTextes[TEXTE_ZONE], game->textureTextes[TEXTE_ZONE], 1.4, 0.65);
  //
  //     creationTexte(&game->surfaceTextes[TEXTE_RANGE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_RANGE], deplacement, SDL_Color{255,255,255});
  //     affichageTextureTextes(&game->surfaceTextes[TEXTE_RANGE], game->textureTextes[TEXTE_RANGE], 1.4, 0.7);
  //
  //
  //     free(deplacement);
  //     free(zone);
  //     free(defense);
  //     free(force);
  //     free(pv);
  //   }
  //}

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
// }

void zoneSurbrillance(Joueur joueur, int id, int map[10][10], int choix){
  int x = (int)joueur.unites[id].coord[0];
  int y = (int)joueur.unites[id].coord[1];
  int range =joueur.unites[id].distance;
  if(choix==ATTAQUE){
    range=joueur.unites[id].zoneDeTir;
    for (int i = -range; i <= range; i++)
    {
      for (int j = -range; j <= range; j++)
      {
        if ((i+j) <= range && (i+j) >= -range && (i-j) <= range && (i-j) >= -range && !(i==0 && j==0))
        {
          if(map[y-1+j][ x-1 + i]!=ARBRE && map[y-1+j][ x-1 + i]!=EAU&& x-1+i<10 && y-1+j<10){ // PENSER A CHANGER LA TAILLE DU TABLEAU
            carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          }
        }
      }
    }
  }
  else if (choix==DEPLACEMENT){
    for (int i = -range; i <= range; i++)
    {
      for (int j = -range; j <= range; j++)
      {
        if ((i+j) <= range && (i+j) >= -range && (i-j) <= range && (i-j) >= -range && !(i==0 && j==0))
        {
          if(map[y-1+j][ x-1 + i]==PLAINE && x-1+i<10 && y-1+j<10){ // PENSER A CHANGER LA TAILLE DU TABLEAU
            carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          }
        }
      }
    }
  }

}
