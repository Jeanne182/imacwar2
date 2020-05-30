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
#include <iostream>

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
        case_achat(game, e, game->joueur1.pieces);
      }
      else {
        if(game->modeJeu ==MULTIJOUEURS){
          case_achat(game, e, game->joueur2.pieces);
        }
        else {game->etapeAchatUnite = CHOIX_EMPLACEMENT;}
      }

      cout << "achat type : " << game->achat_type << endl;
    break;

      case CHOIX_EMPLACEMENT:
        if (game->tour == TOUR_JOUEUR1){
          if(placementUnite(&game->joueur1, e, game, game->achat_type)==true){
            finAchat(game, game->joueur2.pieces, TOUR_JOUEUR1, TOUR_JOUEUR2);
          }
        }
        else {
          if(game->modeJeu == MULTIJOUEURS){
            if(placementUnite(&game->joueur2, e, game, game->achat_type)==true){
              finAchat(game, game->joueur1.pieces, TOUR_JOUEUR2, TOUR_JOUEUR1);
            }
          }

          else{ /////JOUEUR = ORDI
            int rand_unite = rand()%5 + 5;
            cout<<"rand_unite : "<< rand_unite<<endl;
            while (verificationPrix(game->joueur2.pieces, game->unites[rand_unite])==false){
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
            finAchat(game, game->joueur1.pieces, TOUR_JOUEUR2, TOUR_JOUEUR1);
          }
        }
      break;
    }
}

void case_achat(Game* game, SDL_Event e, int pieces){
  if(selectionBouton(game, e) == ACHAT && game->achat_type != SANS_TYPE && verificationPrix(pieces, game->unites[game->achat_type])==true){
    cout<<"ETAPE : achat"<<endl;
    game->etapeAchatUnite = CHOIX_EMPLACEMENT;
  }
  else {
    game->achat_type = selectionBoutonUnite(game, e);
  }
}

void finAchat(Game* game, int pieces, int memeJoueur, int autreJoueur){
  if(pieces==0){
    game->tour = memeJoueur;
  }
  else{
    game->tour = autreJoueur;
  }
  game->achat_type = SANS_TYPE;
  game->etapeAchatUnite = ACHAT_UNITE;

}



void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){
  int xNew=-1;
  int yNew=-1;

  selectionCoordonnee(&xNew,&yNew, e, game->surface);

  if(verificationCaseLibre(game, xNew, yNew)==true && verificationDistance(*joueur, xNew, yNew, id, game)==true){

    insertionCoordonnees(game, &joueur->unites[id], xNew, yNew, joueur->tour);
    cout << "case libre" << endl;
    game->uniteJouee[id]=1;
    // Changement de tour

    verificationFinTour(game, joueur->nbUnites);
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

  cout << "x attaque" << xAttaque << endl;
  cout << "y attaque" << yAttaque << endl;


  if(verifUniteEnnemie(joueurEnnemi->tour, game->mapObstacles, xAttaque, yAttaque)==true && verificationZoneTir(*joueurTour, xAttaque, yAttaque, id)==true){
    cout << "attaque gooo" << endl;
    game->uniteJouee[id]=1;
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
      insertionCoordonnees(game, &joueurEnnemi->unites[idEnnemi], 0, 0, game->tour);
      cout << "L'unite ennemie est morte" << endl;
    }
    // Si une unite du joueur est tuee :
    if (joueurTour->unites[id].vie<=0){
      game->uniteJouee[id]=0;
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
      verificationFinTour(game, joueurTour->nbUnites);
    }

  }
  else{
    cout << "Vous attaquez une de vos unites OU La distance de tir n'est pas respectée" << endl;
  }
}

void attaqueOrdi(Joueur *joueurTour, Joueur *joueurEnnemi, int id, int idEnnemi, Game* game){

  cout << "attaque gooo" << endl;

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
    if(joueurTour->nbUnites == 0 || joueurEnnemi->nbUnites == 0){
      game->etapeJeu = FIN_JEU;
    }
}

void initialiseUniteJouee(int tableau[10]){
  cout << "c'est ok"<< endl;
  for(int i=0; i<10 ; i++){
    tableau[i]=0;

  }
}

void etatUnite(Unite unite, Game* game){ //int id,Game* game
  // if(unite != SANS_TYPE){
    // zoneSurbrillance(game->joueur1,id, game->map,DEPLACEMENT);
    // cout<<"Coordonnées unité J1: "<< game->joueur1.unites[id].coord[0] <<" "<< game->joueur1.unites[id].coord[1]<<endl;

    if(game->textureTextes[TEXTE_NOM_UNIT]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_NOM_UNIT]);
    }
    if(game->textureTextes[TEXTE_PRIX]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PRIX]);
    }
    if(game->textureTextes[TEXTE_PV]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PV]);
    }
    if(game->textureTextes[TEXTE_FORCE]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_FORCE]);
    }
    if(game->textureTextes[TEXTE_DEFENSE]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_DEFENSE]);
    }
    if(game->textureTextes[TEXTE_ZONE]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_ZONE]);
    }
    if(game->textureTextes[TEXTE_RANGE]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_RANGE]);
    }

    char* nom = concatenation(unite.nom, (char*)"");
    char* prix = conversionTexteDyna(unite.prix, (char*)"Prix : ");
    char* pv = conversionTexteDyna(unite.vie, (char*)"Points de vie : ");
    char* force = conversionTexteDyna(unite.force*100, (char*)"Force (%) : ");
    char* defense = conversionTexteDyna(unite.defense*100, (char*)"Défense (%) : ");
    char* zone = conversionTexteDyna(unite.zoneDeTir, (char*)"Zone de tir (cases) : ");
    char* deplacement = conversionTexteDyna(unite.distance, (char*)"Capacité de déplacement (cases) : ");

    creationTexte(&game->surfaceTextes[TEXTE_NOM_UNIT], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_NOM_UNIT], nom, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_PV], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_PV], pv, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_FORCE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_FORCE], force, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_DEFENSE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_DEFENSE], defense, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_ZONE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_ZONE], zone, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_RANGE], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_RANGE], deplacement, SDL_Color{255,255,255});
    creationTexte(&game->surfaceTextes[TEXTE_PRIX], game->policeTextes[NORMAL], &game->textureTextes[TEXTE_PRIX], prix, SDL_Color{255,255,255});

    if(game->etapeJeu == PLACEMENT_UNITES){
      affichageTextureTextes(&game->surfaceTextes[TEXTE_NOM_UNIT], game->textureTextes[TEXTE_NOM_UNIT], 1.1, 0.53);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_PRIX], game->textureTextes[TEXTE_PRIX], 1.1, 0.58);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_PV], game->textureTextes[TEXTE_PV], 1.1, 0.61);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_FORCE], game->textureTextes[TEXTE_FORCE], 1.1, 0.64);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_DEFENSE], game->textureTextes[TEXTE_DEFENSE], 1.1, 0.67);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_ZONE], game->textureTextes[TEXTE_ZONE], 1.1, 0.70);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_RANGE], game->textureTextes[TEXTE_RANGE], 1.1, 0.73);
    }
    else{
      affichageTextureTextes(&game->surfaceTextes[TEXTE_CARACTERISTIQUES], game->textureTextes[TEXTE_CARACTERISTIQUES], 1.1, 0.63);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_NOM_UNIT], game->textureTextes[TEXTE_NOM_UNIT], 1.1, 0.7);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_PV], game->textureTextes[TEXTE_PV], 1.1, 0.75);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_FORCE], game->textureTextes[TEXTE_FORCE], 1.1, 0.78);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_DEFENSE], game->textureTextes[TEXTE_DEFENSE], 1.1, 0.81);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_ZONE], game->textureTextes[TEXTE_ZONE], 1.1, 0.84);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_RANGE], game->textureTextes[TEXTE_RANGE], 1.1, 0.87);
    }


    free(deplacement);
    free(zone);
    free(defense);
    free(force);
    free(pv);
    free(prix);
    free(nom);

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

void zoneSurbrillance(Joueur joueur, int id, int map[10][10], int choix, Game* game){
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
          // if(map[y-1+j][ x-1 + i]!=ARBRE &&
          //    map[y-1+j][ x-1 + i]!=EAU &&
          //    map[y-1+j][ x-1 + i]!=EAUHG &&
          //    map[y-1+j][ x-1 + i]!=EAUHD &&
          //    map[y-1+j][ x-1 + i]!=EAUBG &&
          //    map[y-1+j][ x-1 + i]!=EAUBD &&
          //    x-1+i<10 && y-1+j<10){ // PENSER A CHANGER LA TAILLE DU TABLEAU
          //   carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          // }
          if(map[y-1+j][ x-1 + i]!=OBSTACLE && map[y-1+j][ x-1 + i]!=game->tour && x-1+i<10 && y-1+j<10){
            // if((game->tour == TOUR_JOUEUR1 && game->mapObstacles[y-1+j][x-1+i]==JOUEUR2) || (game->tour == TOUR_JOUEUR2 && game->mapObstacles[y-1+j][x-1+i]==JOUEUR1)){
            //   affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)(x-1+i)/10,(float)(y-1+j)/10);
            // }
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
          // if((game->tour == TOUR_JOUEUR1 && map[y-1+j][x-1+i]==JOUEUR2) || (game->tour == TOUR_JOUEUR2 && map[y-1+j][x-1+i]==JOUEUR1)){
          //   cout << "rentre dedans" << endl;
          //   affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)(x-1+i)/10,(float)(y-1+j)/10);
          // }
          if(map[y-1+j][ x-1 + i]==VIDE && x-1+i<10 && y-1+j<10){ // PENSER A CHANGER LA TAILLE DU TABLEAU
            carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          }
        }
      }
    }
  }

}
