#include "joueur_ordi/a_star.h"
#include "joueur_ordi/joueur_ordi.h"
#include "interface/interface.h"
#include "unites/unites.h"
#include "interface/text.h"
#include "game/game.h"

/* Appelle les fonctions spécifiques au joueur ordinateur */
void tour_Ordi(Game* game){
  if(game->tour == TOUR_JOUEUR2 && game->modeJeu == ORDI_MODE){
    if(game->etapeJeu==SELECTION_UNITE){
      game->etapeJeu=ACTIONS;
    }
    switch(game->etapeJeu){

    case PLACEMENT_UNITES:
      choixPlacementUniteOrdi(game);
      break;
    case ACTIONS:
      choixActionsOrdi(game);
      break;
    }

  }
}

/* Choisi la cible à attaquer */
void choixCible(int xOrdi,int yOrdi, int *xCible, int *yCible, int map[10][10]){
  int xOptimal = -1;
  int yOptimal = -1;
  for(int i = 0; i<10; i++){
    for(int j=0; j<10; j++){
      if(map[j][i]==JOUEUR1){
        if(xOptimal==-1 && yOptimal==-1){
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


/* Regarde si la cible à attaquer se trouve dans sa zone de déplacement */
bool cibleInZone(int xOrdi,int yOrdi, int xCible, int yCible, int zoneAttaque){
  if(abs(xCible-xOrdi)+abs(yCible-yOrdi)>zoneAttaque){
    cout<<"Cible hors zone d'attaque"<<endl;
    return false;
  }
  cout<<"Cible dans zone d'attaque"<<endl;
  return true;
}


/* Si cible hors de la zone : choisi la case la plus proche dans sa zone de placement */
void caseOptimaleAtteignable(int *x, int *y, int zoneDeplacement, Noeud* chemin){
  int xChemin = chemin->parent->x;
  int yChemin = chemin->parent->y;
  while(abs(*x-xChemin)+abs(*y-yChemin) > zoneDeplacement){
    chemin = chemin->parent;
    xChemin = chemin->x;
    yChemin = chemin->y;
  }
  *x = xChemin;
  *y = yChemin;
  cout << "x et y séléctionnés : " << *x <<" , "<<*y<<endl;
}


void attaqueOrdi(Joueur *joueurTour, Joueur *joueurEnnemi, int id, int idEnnemi, Game* game){

  cout << "L'ordinateur attaque" << endl;

  /* L'ennemi perd des pv en premier */
    joueurEnnemi->unites[idEnnemi].vie -= (joueurTour->unites[id].force*(1 - joueurEnnemi->unites[idEnnemi].defense))*joueurTour->unites[id].vie;

    if (joueurEnnemi->unites[idEnnemi].vie<=0){
      joueurEnnemi->unites[idEnnemi].vie=0;
    }

    /* L'attaquant perd ensuite des pv */
    joueurTour->unites[id].vie -= (joueurEnnemi->unites[idEnnemi].force*(1 - joueurTour->unites[id].defense))*joueurEnnemi->unites[idEnnemi].vie;

    if (joueurTour->unites[id].vie<=0){
      joueurTour->unites[id].vie=0;
    }

    cout << "Force unite ennemie = " << joueurEnnemi->unites[idEnnemi].force<< endl;
    cout << "Vie unite ennemie post combat = " << joueurEnnemi->unites[idEnnemi].vie<< endl;
    cout << "Force unite attaquante = " << joueurTour->unites[id].force<< endl;
    cout << "Vie unite attaquante post combat = " << joueurTour->unites[id].vie<< endl;

    // Si une unite ennemie a été tuee :
    if (joueurEnnemi->unites[idEnnemi].vie==0){
      joueurEnnemi->nbUnites-=1;
      insertionCoordonnees(game, &joueurEnnemi->unites[idEnnemi], 0, 0, joueurEnnemi->tour);
      cout << "L'unite ennemie est morte" << endl;
    }
    // Si une unite du joueur a été tuee :
    if (joueurTour->unites[id].vie==0){
      joueurTour->nbUnites-=1;
      insertionCoordonnees(game, &joueurTour->unites[id], 0, 0, joueurTour->tour);
      cout << "Votre unite est morte" << endl;
    }

    cout<<"Nb unite joueurOrdi : "<<joueurTour->nbUnites<< "/ Nb unites joueur1 : "<<joueurEnnemi->nbUnites<<endl;

    if(joueurTour->nbUnites == 0 || joueurEnnemi->nbUnites == 0){
      cout<<"FIN JEU"<<endl;
      game->etapeJeu = FIN_JEU;
    }

}

/* L'ordinateur place aléatoirement ses unités */
void choixPlacementUniteOrdi(Game *game){
  int rand_unite = rand()%5 + 5;

  while (verificationPrix(game->joueur2.pieces, game->unites[rand_unite])==false){
    rand_unite = rand()%5 + 5;
  }
  int rand_x = rand()%10 + 1;
  int rand_y = rand()%10 + 1;

  while(placementUniteOrdi(&game->joueur2, rand_x, rand_y, game, rand_unite)==false){
    rand_x = rand()%10 + 1;
    rand_y = rand()%10 + 1;
  }

  finAchat(game, game->joueur1.pieces, TOUR_JOUEUR2, TOUR_JOUEUR1);
  if(game->joueur1.pieces ==0 && game->joueur2.pieces==0){
    game->etapeJeu= SELECTION_UNITE;
    game->tour=TOUR_JOUEUR1;
  }
}

/* L'ordinateur décide s'il peut attaquer ou s'il va devoir se déplacer */
void choixActionsOrdi(Game *game){
    int idOrdi = 0;
    while((game->joueur2.unites[idOrdi].vie <=0 || game->uniteJouee[idOrdi] ==1) && idOrdi<game->joueur2.nbUnitesInitial-1){
      idOrdi++;
    }

    game->uniteJouee[idOrdi]=1;
    int xCible = -1;
    int yCible = -1;
    int xOrdi = game->joueur2.unites[idOrdi].coord[0];
    int yOrdi = game->joueur2.unites[idOrdi].coord[1];

    if(game->joueur2.unites[idOrdi].vie!=0){
      choixCible(xOrdi, yOrdi,&xCible,&yCible, game->mapObstacles);
      if(cibleInZone(xOrdi, yOrdi,xCible,yCible, game->joueur2.unites[idOrdi].zoneDeTir)==true){
        int idEnnemi = selectionIdUnite(xCible, yCible, game->joueur1);
        cout<<"CHOIX ATTAQUE, idEnnemi : "<<idEnnemi<<endl;

        int pvAvantJoueur = game->joueur1.unites[idEnnemi].vie;
        int pvAvantOrdi = game->joueur2.unites[idOrdi].vie;

        attaqueOrdi(&game->joueur2, &game->joueur1, idOrdi, idEnnemi, game);

        int pvApresJoueur = game->joueur1.unites[idEnnemi].vie;
        int pvApresOrdi = game->joueur2.unites[idOrdi].vie;

        carre(xCible, yCible, game->joueur1, DEPLACEMENT);
        carre(xOrdi, yOrdi, game->joueur2, DEPLACEMENT);

        if(game->textureTextes[TEXTE_PV_PERDUS_JOUEUR]!=0){
          glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J1]);
        }
        if(game->textureTextes[TEXTE_PV_PERDUS_ORDI]!=0){
          glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J2]);
        }

        float pvPerdusJoueur = pvAvantJoueur - pvApresJoueur;
        char* textePvPerdusJoueur = conversionTexteDyna(pvPerdusJoueur, (char*)"- ");
        float pvPerdusOrdi = pvAvantOrdi - pvApresOrdi;
        char* textePvPerdusOrdi = conversionTexteDyna(pvPerdusOrdi, (char*)"- ");


        creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_JOUEUR], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_JOUEUR], textePvPerdusJoueur, SDL_Color{0,0,0});
        creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_ORDI], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_ORDI], textePvPerdusOrdi , SDL_Color{0, 0 ,0});
        affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_JOUEUR], game->textureTextes[TEXTE_PV_PERDUS_JOUEUR], game->joueur1.unites[idEnnemi].coord[0]/10 - 0.11 , game->joueur1.unites[idEnnemi].coord[1]/10 - 0.12);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_ORDI], game->textureTextes[TEXTE_PV_PERDUS_ORDI], game->joueur2.unites[idOrdi].coord[0]/10 - 0.11 , game->joueur2.unites[idOrdi].coord[1]/10 - 0.12);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_ATTAQUE], game->textureTextes[TEXTE_ATTAQUE], 1.18, 0.35);

        free(textePvPerdusJoueur);
        free(textePvPerdusOrdi);
      }

      else{
        Noeud cheminCible = *a_star(xOrdi,yOrdi, xCible, yCible, game->mapObstacles);
        //int i=0;
        // if(cheminCible.x == xOrdi && cheminCible.y == yOrdi){
        //   //i++;
        //   //nouvelleCible(xOrdi, yOrdi, &xCible,&yCible, game->mapObstacles);
        //   cheminCible = *a_star(xOrdi,yOrdi, xCible, yCible, game->mapObstacles);
        //   // if(i==4){ //A modifier, ça casse la boucle dès qu'il y a 4 rangées d'obstacles autour de l'unité cible
        //   //   break;
        //   // }
        // }

        if(cheminCible.x != xOrdi || cheminCible.y != yOrdi){
          Noeud copyChemin = cheminCible;
          cout<<"uniteOrdi :("<<xOrdi<<"'"<<yOrdi<<")"<<endl;
          affichageChemin(&copyChemin, xCible, yCible);
          SDL_Delay(1000);
          caseOptimaleAtteignable(&xOrdi, &yOrdi, game->joueur2.unites[idOrdi].distance, &cheminCible);
          carre(game->joueur2.unites[idOrdi].coord[0], game->joueur2.unites[idOrdi].coord[1], game->joueur2, DEPLACEMENT);
          affichageTextureTextes(&game->surfaceTextes[TEXTE_DEPLACEMENT], game->textureTextes[TEXTE_DEPLACEMENT], 1.18, 0.35);
          insertionCoordonnees(game, &game->joueur2.unites[idOrdi], xOrdi, yOrdi, game->joueur2.tour);

          cout<<"CHOIX DEPLACEMENT"<<endl;
       }



      }

    }

  int compteur =0;
  for(int i=0; i<game->joueur2.nbUnitesInitial;i++){
    if(game->uniteJouee[i]==1){
      compteur++;
    }
  }

  if (compteur >= game->joueur2.nbUnites){
    initialiseUniteJouee(game->uniteJouee);
    game->tour = TOUR_JOUEUR1;
    if(game->joueur1.nbUnites !=0 && game->joueur2.nbUnites !=0 ){
      game->etapeJeu= SELECTION_UNITE;
    }
    game->choix= RIEN;
  }

}


bool placementUniteOrdi(Joueur *joueur, int x, int y, Game* game, int typeUnite){
    int id = joueur->nbUnites;

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

    cout << "Vous êtes hors de votre zone de placement, veuillez placer votre unité dans votre zone." << endl;
    return false;
}

void nouvelleCible(int xOrdi, int yOrdi, int *xCible, int *yCible, int map[10][10]){
  int xHaut = *xCible;
  int yHaut = *yCible - 1;
  if(abs(*xCible-xOrdi)+abs(*yCible-yOrdi)>abs(xHaut-xOrdi)+abs(yHaut-yOrdi)/* && map[yHaut-1][xHaut-1] == VIDE*/){
    *xCible = xHaut;
    *yCible = yHaut;
  }

  int xBas = *xCible;
  int yBas = *yCible + 1;
  if(abs(*xCible-xOrdi)+abs(*yCible-yOrdi)>abs(xBas-xOrdi)+abs(yBas-yOrdi)/* && map[yBas-1][xBas-1] == VIDE*/){
    *xCible = xBas;
    *yCible = yBas;
  }

  int xDroite = *xCible + 1;
  int yDroite = *yCible;
  if(abs(*xCible-xOrdi)+abs(*yCible-yOrdi)>abs(xDroite-xOrdi)+abs(yDroite-yOrdi)/* && map[yDroite-1][xDroite-1] == VIDE*/){
    *xCible = xDroite;
    *yCible = yDroite;
  }

  int xGauche = *xCible - 1;
  int yGauche = *yCible;
  if(abs(*xCible-xOrdi)+abs(*yCible-yOrdi)>abs(xGauche-xOrdi)+abs(yGauche-yOrdi)/* && map[yDroite-1][xDroite-1] == VIDE*/){
    *xCible = xGauche;
    *yCible = yGauche;
  }

  cout <<"Nouvelle case cible : (" << *xCible<<","<<*yCible<<")"<<endl;
}
