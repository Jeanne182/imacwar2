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
    int x=-1;
    int y=-1;

    selectionCoordonnee(&x,&y, e, game->surface);
    cout << "Selection en --> x : " << x << " y : " << y << endl;

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


/* FOnction qui gère l'achat des unités puis leur placement sur la carte (dans la bonne zone et sur une case vide) */
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


/* Fonction qui déplace l'unité après vérifications */
void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){
  int xNew=-1;
  int yNew=-1;

  selectionCoordonnee(&xNew,&yNew, e, game->surface);

  if(verificationCaseLibre(game, xNew, yNew)==true && verificationDistance(*joueur, xNew, yNew, id, game)==true){

    insertionCoordonnees(game, &joueur->unites[id], xNew, yNew, joueur->tour);
    cout << "Case libre" << endl;
    game->uniteJouee[id]=1;
    verificationFinTour(game, joueur->nbUnites);
  }
  else{
    cout << "Cette case est déjà occupée, veuillez choisir une autre case OU Votre distance de déplacement n'est pas respectée" << endl;
  }
}

/* Fonction d'attaque après vérification, et traite les unités mortes */
void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int id, SDL_Event e, Game* game){

  int xAttaque=-1;
  int yAttaque=-1;
  int idEnnemi=-1;
  selectionCoordonnee(&xAttaque, &yAttaque, e, game->surface);

  if(verifUniteEnnemie(joueurEnnemi->tour, game->mapObstacles, xAttaque, yAttaque)==true && verificationZoneTir(*joueurTour, xAttaque, yAttaque, id)==true){
    cout << "Attaque commence" << endl;
    game->uniteJouee[id]=1;
    idEnnemi = selectionIdUnite(xAttaque, yAttaque, *joueurEnnemi);

    int pvAvantEnnemi = joueurEnnemi->unites[idEnnemi].vie;
    int pvAvantAmi = joueurTour->unites[id].vie;

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

    int pvApresEnnemi = joueurEnnemi->unites[idEnnemi].vie;
    int pvApresAmi = joueurTour->unites[id].vie;


    if(game->textureTextes[TEXTE_PV_PERDUS_J1]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J1]);
    }
    if(game->textureTextes[TEXTE_PV_PERDUS_J2]!=0){
      glDeleteTextures(1, &game->textureTextes[TEXTE_PV_PERDUS_J2]);
    }

    int pvPerdusEnnemisMulti = pvAvantEnnemi - pvApresEnnemi;
    char* textePvPerdusEnnemisMulti = conversionTexteDyna(pvPerdusEnnemisMulti, (char*)"- ");
    int pvPerdusAmi = pvAvantAmi - pvApresAmi;
    char* textePvPerdusAmi = conversionTexteDyna(pvPerdusAmi, (char*)"- ");


    creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_J1], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_J1], textePvPerdusEnnemisMulti , SDL_Color{0,0,0});
    creationTexte(&game->surfaceTextes[TEXTE_PV_PERDUS_J2], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PV_PERDUS_J2], textePvPerdusAmi , SDL_Color{0, 0 ,0});
    affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_J1], game->textureTextes[TEXTE_PV_PERDUS_J1], joueurEnnemi->unites[idEnnemi].coord[0]/10 - 0.11 , joueurEnnemi->unites[idEnnemi].coord[1]/10 - 0.12);
    affichageTextureTextes(&game->surfaceTextes[TEXTE_PV_PERDUS_J2], game->textureTextes[TEXTE_PV_PERDUS_J2], joueurTour->unites[id].coord[0]/10 - 0.11 ,joueurTour->unites[id].coord[1]/10 - 0.12);
    affichageTextureTextes(&game->surfaceTextes[TEXTE_ATTAQUE], game->textureTextes[TEXTE_ATTAQUE], 1.18, 0.35);

    free(textePvPerdusEnnemisMulti);
    free(textePvPerdusAmi);

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


/* Ce tableau permet de savoir quelle unité a été jouée, il est ici réinitialisé à chaque début d'un nouveau tour */
void initialiseUniteJouee(int tableau[10]){
  for(int i=0; i<10 ; i++){
    tableau[i]=0;

  }
}


/* Affiche des zones de surbrillance pour la zone de déplacement et d'attaque */
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
        if ((i+j) <= range && (i+j) >= -range && (i-j) <= range && (i-j) >= -range && !(i==0 && j==0)){
          if(game->modeJeu==MULTIJOUEURS){
            if((map[y-1+j][ x-1 + i]!=OBSTACLE && map[y-1+j][ x-1 + i]!=joueur.tour) && x-1+i<10 && y-1+j<10){
              carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
            }
          }
          else{
            if((map[y-1+j][ x-1 + i]!=OBSTACLE && map[y-1+j][ x-1 + i]!=JOUEUR1) && x-1+i<10 && y-1+j<10){
              carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          }

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
          if(map[y-1+j][ x-1 + i]==VIDE && x-1+i<10 && y-1+j<10){
            carre(joueur.unites[id].coord[0]+i,joueur.unites[id].coord[1]+j,joueur, choix);
          }
        }
      }
    }
  }

}
