#include "joueur_ordi/a_star.h"
#include "joueur_ordi/joueur_ordi.h"
#include "interface/interface.h"
#include "unites/unites.h"
#include "interface/text.h"

#include "game/game.h"


void choixCible(int xOrdi,int yOrdi, int *xCible, int *yCible, int map[10][10]){
  int xOptimal = -1;
  int yOptimal = -1;
  for(int i = 0; i<10; i++){
    for(int j=0; j<10; j++){
      if(map[j][i]==JOUEUR1){
        if(xOptimal==-1){
          xOptimal = i+1;
          yOptimal = j+1;
        }
        else{
          if(abs(xOptimal-xOrdi)+abs(yOptimal-yOrdi)>abs(i+1-xOrdi)+abs(j+1-yOrdi)){
            xOptimal = i+1;
            yOptimal = j+1;
          }
        }
      }
    }
  }
  *xCible = xOptimal;
  *yCible = yOptimal;
  cout<<"La cible a pour coordonnées : ("<<*xCible<<","<<*yCible<<")"<<endl;
}

bool cibleInZone(int xOrdi,int yOrdi, int xCible, int yCible, int zoneAttaque){
  if(abs(xCible-xOrdi)+abs(yCible-yOrdi)>zoneAttaque){
    cout<<"Cible hors zone d'attaque"<<endl;
    return false;
  }
  cout<<"Cible dans zone d'attaque"<<endl;
  return true;
}

void caseOptimaleAtteignable(int *x, int *y, int zoneDeplacement, Noeud* chemin){
  int xChemin = chemin->x;
  int yChemin = chemin->y;
  // cout<<"X : " << xChemin <<" , Y : " << yChemin <<endl;
  while(abs(*x-xChemin)+abs(*y-yChemin) > zoneDeplacement){
    chemin = chemin->parent;
    xChemin = chemin->x;
    yChemin = chemin->y;
    // cout<<"X3 : " << xChemin <<" Y3 : " << yChemin <<endl;
  }
  *x = xChemin;
  *y = yChemin;
  cout << "x et y séléctionnés : " << *x <<" , "<<*y<<endl;
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

void choixPlacementUniteOrdi(Game *game){
  int rand_unite = rand()%5 + 5;
  // int rand_unite = 5;
  cout<<"rand_unite : "<< rand_unite<<endl;
  while (verificationPrix(game->joueur2.pieces, game->unites[rand_unite])==false){
    rand_unite = rand()%5 + 5;
    cout <<"Pieces joueur : "<<game->joueur2.pieces<<endl;
    cout<<"rand_unite : "<< rand_unite<<endl<<endl;
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
  if(game->joueur1.pieces ==0 && game->joueur2.pieces==0){
    game->etapeJeu= SELECTION_UNITE;
    game->tour=TOUR_JOUEUR1;
  }
}

void choixActionsOrdi(Game *game){
    int idOrdi = 0;
    while(game->joueur2.unites[idOrdi].vie ==0 || game->uniteJouee[idOrdi] ==1 || idOrdi>game->joueur2.nbUnitesInitial){
      idOrdi++;
    }

    game->uniteJouee[idOrdi]=1; //steeve a dit de le bouger dans la boucle
    cout << "idOrdi : "<<idOrdi<<endl<<endl;
  // for(int idOrdi=0; idOrdi<game.joueur2.nbUnitesInitial; idOrdi++){

    int xCible = -1;
    int yCible = -1;
    int xOrdi = game->joueur2.unites[idOrdi].coord[0];
    int yOrdi = game->joueur2.unites[idOrdi].coord[1];
    if(game->joueur2.unites[idOrdi].vie!=0){
      choixCible(xOrdi, yOrdi,&xCible,&yCible, game->mapObstacles);
      if(cibleInZone(xOrdi, yOrdi,xCible,yCible, game->joueur2.unites[idOrdi].zoneDeTir)==true){
        int idEnnemi = selectionIdUnite(xCible, yCible, game->joueur1);
        cout<<"CHOIX ATTAQUE, idEnnemi : "<<idEnnemi<<endl;

        float pvAvantEnnemi = game->joueur1.unites[idEnnemi].vie;
        float pvAvantOrdi = game->joueur2.unites[idOrdi].vie;
        //if(frame%10 == 0){
        attaqueOrdi(&game->joueur2, &game->joueur1, idOrdi, idEnnemi, game);
        //}
        float pvApresEnnemi = game->joueur1.unites[idEnnemi].vie;
        float pvApresOrdi = game->joueur2.unites[idOrdi].vie;

        carre(xCible, yCible, game->joueur1, DEPLACEMENT);
        carre(xOrdi, yOrdi, game->joueur2, DEPLACEMENT);
        if(game->textureTextes[TEXTE_PV_PERDUS_J1]!=0){
          glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J1]);
        }
        if(game->textureTextes[TEXTE_PV_PERDUS_J2]!=0){
          glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J2]);
        }

        // char* textePvPerdusEnnemis = pvmoins(pvAvantEnnemi, pvApresEnnemi);
        // char* textePvPerdusOrdi = pvmoins(pvAvantOrdi, pvApresOrdi);

        float pvPerdusEnnemis = pvAvantEnnemi - pvApresEnnemi;
        char* textePvPerdusEnnemis = conversionTexteDyna(pvPerdusEnnemis, (char*)"- ");
        float pvPerdusOrdi = pvAvantOrdi - pvApresOrdi;
        char* textePvPerdusOrdi = conversionTexteDyna(pvPerdusOrdi, (char*)"- ");
        //return textePvPerdus;

        creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_J1], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_J1], textePvPerdusEnnemis , SDL_Color{1,74,199});
        creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_J2], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_J2], textePvPerdusOrdi , SDL_Color{94, 0 ,46});
        //
        affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_J1], game->textureTextes[TEXTE_PV_PERDUS_J1], game->joueur1.unites[idEnnemi].coord[0]/10 - 0.11 , game->joueur1.unites[idEnnemi].coord[1]/10 - 0.12);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_J2], game->textureTextes[TEXTE_PV_PERDUS_J2], game->joueur2.unites[idOrdi].coord[0]/10 - 0.11 , game->joueur2.unites[idOrdi].coord[1]/10 - 0.12);

        affichageTextureTextes(&game->surfaceTextes[TEXTE_ATTAQUE], game->textureTextes[TEXTE_ATTAQUE], 1.18, 0.35);

        free(textePvPerdusEnnemis);
        free(textePvPerdusOrdi);

      }

      else{
        // Noeud* chemin = a_star(xOrdi,yOrdi, xCible, yCible, game->mapObstacles);
        // SDL_Delay(1000);
        // caseOptimaleAtteignable(&xOrdi, &yOrdi, game->joueur2.unites[idOrdi].distance, chemin);
        //
        // carre(game->joueur2.unites[idOrdi].coord[0], game->joueur2.unites[idOrdi].coord[1], game->joueur2, DEPLACEMENT);
        // affichageTextureTextes(&game->surfaceTextes[TEXTE_DEPLACEMENT], game->textureTextes[TEXTE_DEPLACEMENT], 1.18, 0.35);
        // insertionCoordonnees(game, &game->joueur2.unites[idOrdi], xOrdi, yOrdi, JOUEUR2);

        cout<<"frame"<<frame<<endl;
        //if(frame%10 == 0){
          //game->uniteJouee[idOrdi]=1;
          deplacementOrdi(xOrdi, yOrdi, xCible, yCible, idOrdi, game);
        //}
        cout<<"CHOIX DEPLACEMENT"<<endl;
      }

    }

  // }
  if (verificationUniteJouee(game->uniteJouee,game->joueur2.nbUnites)==true){
    initialiseUniteJouee(game->uniteJouee);
    game->tour = TOUR_JOUEUR1;
    game->etapeJeu= SELECTION_UNITE;
    game->choix= RIEN;
  }

  // game.tour = TOUR_JOUEUR1;
}

void deplacementOrdi(int xOrdi, int yOrdi, int xCible, int yCible, int idOrdi, Game* game){
  Noeud* chemin = a_star(xOrdi,yOrdi, xCible, yCible, game->mapObstacles);
  caseOptimaleAtteignable(&xOrdi, &yOrdi, game->joueur2.unites[idOrdi].distance, chemin);
  //if(frame%10 == 0){
    carre(game->joueur2.unites[idOrdi].coord[0], game->joueur2.unites[idOrdi].coord[1], game->joueur2, DEPLACEMENT);
  //}

  affichageTextureTextes(&game->surfaceTextes[TEXTE_DEPLACEMENT], game->textureTextes[TEXTE_DEPLACEMENT], 1.18, 0.35);
  insertionCoordonnees(game, &game->joueur2.unites[idOrdi], xOrdi, yOrdi, JOUEUR2);
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