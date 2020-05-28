#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"

//#include "game/a_star.h"

#include <cstring>


void affichage(Game* game){
  /* Placer ici le code de dessin */
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1,1,1);

  if(game->etapeJeu != MENU){
    affichageCarte(game);
  }


  // for(int x=0; x<=10; x++){
  //   for(int y=0; y<=10; y++){
  //     if(game->map[y-1][x-1]==PLAINE){
  //       carre(x,y,game->joueur1);
  //     }
  //   }
  // }

  //affichageTexture(texteDeplacement, game->boutonDeplacement.longueur, game->boutonDeplacement.hauteur,game->boutonDeplacement.x,game->boutonDeplacement.y);
  initialisationBoutons(game);
  glColor3f(1,1,1);

  switch (game->etapeJeu) { //Tous les trucs statiques qui ne dépendent pas des clics,
    case MENU:
      affichageTexture(game->textfond[IMG_MENUDEBUT],game->aspectRatio,1,0,0);
      bouton(game->bouton1Joueur);
      bouton(game->bouton2Joueurs);
      affichageTexture(game->texturebouton,game->bouton1Joueur.longueur,game->bouton1Joueur.hauteur,game->bouton1Joueur.x,game->bouton1Joueur.y);
      affichageTexture(game->texturebouton,game->bouton2Joueurs.longueur,game->bouton2Joueurs.hauteur,game->bouton2Joueurs.x,game->bouton2Joueurs.y);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON1J], game->textureTextes[TEXTE_BOUTON1J], (float)game->bouton1Joueur.x+0.055, (float)game->bouton1Joueur.y+0.01);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON2J], game->textureTextes[TEXTE_BOUTON2J], (float)game->bouton2Joueurs.x+0.046, (float)game->bouton2Joueurs.y+0.01);

      break;


    case PLACEMENT_UNITES:


    switch (game->etapeAchatUnite) {

      case ACHAT_UNITE:
      affichageTextureTextes(&game->surfaceTextes[TEXTE_CHOIX], game->textureTextes[TEXTE_CHOIX], 1.21, 0.12);
      bouton(game->boutonAchat);
      affichageTexture(game->texturebouton,game->boutonAchat.longueur,game->boutonAchat.hauteur,game->boutonAchat.x,game->boutonAchat.y);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON_ACHAT], game->textureTextes[TEXTE_BOUTON_ACHAT], (float)game->boutonAchat.x+0.07, (float)game->boutonAchat.y+0.01);

      //etatUnite(2, &game);
      glColor3f(1,1,1);
      surbrillanceAchat(game->achat_type, game);
      if(game->achat_type!=SANS_TYPE){
        etatUnite(game->unites[game->achat_type], game);
      }

      //affichageTexture(descriptionVikingBeast, game->boutonAchat.longueur,game->boutonAchat.hauteur,game->boutonAchat.x,game->boutonAchat.y);
      // if(game->textureTextes[TEXTE_PV]!=NULL){
      //   affichageTextureTextes(game->textureTextes[TEXTE_PV], game->boutonAchat.longueur,game->boutonAchat.hauteur,game->boutonAchat.x,game->boutonAchat.y);
      // }
        switch (game->tour) {
          case TOUR_JOUEUR1:{
            if(game->textureTextes[TEXTE_PIECESJ1]!=NULL){
              glDeleteTextures(1, &game->textureTextes[TEXTE_PIECESJ1]);
            }
            affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR1], game->textureTextes[TEXTE_JOUEUR1], 1.35, 0.05);
            char* piecesj1 = conversionTexteDyna(game->joueur1.pieces, "Pièces joueur 1 : ");
            creationTexte(&game->surfaceTextes[TEXTE_PIECESJ1], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PIECESJ1], piecesj1 , SDL_Color{255,255,255});
            affichageTextureTextes(&game->surfaceTextes[TEXTE_PIECESJ1], game->textureTextes[TEXTE_PIECESJ1], 1.5, 0.53);
            affichageTexture(game->textureUnites[VIKINGWOMAN],game->boutonVikingWoman.longueur,game->boutonVikingWoman.hauteur,game->boutonVikingWoman.x,game->boutonVikingWoman.y);
            affichageTexture(game->textureUnites[VIKINGMAN],game->boutonVikingMan.longueur,game->boutonVikingMan.hauteur,game->boutonVikingMan.x,game->boutonVikingMan.y);
            affichageTexture(game->textureUnites[VIKINGBEAST],game->boutonVikingBeast.longueur,game->boutonVikingBeast.hauteur,game->boutonVikingBeast.x,game->boutonVikingBeast.y);
            affichageTexture(game->textureUnites[VIKINGWIZARD],game->boutonVikingWizard.longueur,game->boutonVikingWizard.hauteur,game->boutonVikingWizard.x,game->boutonVikingWizard.y);
            affichageTexture(game->textureUnites[VIKINGCHIEF],game->boutonVikingChief.longueur,game->boutonVikingChief.hauteur,game->boutonVikingChief.x,game->boutonVikingChief.y);
            free(piecesj1);}
            break;
          case TOUR_JOUEUR2:{
            if(game->textureTextes[TEXTE_PIECESJ2]!=NULL){
              glDeleteTextures(1, &game->textureTextes[TEXTE_PIECESJ2]);
            }
            affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR2], game->textureTextes[TEXTE_JOUEUR2], 1.35, 0.05);
            char* piecesj2 = conversionTexteDyna(game->joueur2.pieces, "Pièces joueur 2 : ");
            creationTexte(&game->surfaceTextes[TEXTE_PIECESJ2], game->policeTextes[SOUSTITRES], &game->textureTextes[TEXTE_PIECESJ2], piecesj2 , SDL_Color{255,255,255});
            affichageTextureTextes(&game->surfaceTextes[TEXTE_PIECESJ2], game->textureTextes[TEXTE_PIECESJ2], 1.5, 0.53);
            affichageTexture(game->textureUnites[DEADKNIGHT],game->boutonDeadKnight.longueur,game->boutonDeadKnight.hauteur,game->boutonDeadKnight.x,game->boutonDeadKnight.y);
            affichageTexture(game->textureUnites[DEADBEAST],game->boutonDeadBeast.longueur,game->boutonDeadBeast.hauteur,game->boutonDeadBeast.x,game->boutonDeadBeast.y);
            affichageTexture(game->textureUnites[DEADWIZARD],game->boutonDeadWizard.longueur,game->boutonDeadWizard.hauteur,game->boutonDeadWizard.x,game->boutonDeadWizard.y);
            affichageTexture(game->textureUnites[DEADMAN],game->boutonDeadMan.longueur,game->boutonDeadMan.hauteur,game->boutonDeadMan.x,game->boutonDeadMan.y);
            affichageTexture(game->textureUnites[DEADCHIEF],game->boutonDeadChief.longueur,game->boutonDeadChief.hauteur,game->boutonDeadChief.x,game->boutonDeadChief.y);
            free(piecesj2);}
          break;
        }





        // carre((int)game->joueur1.unites[game->id1].coord[0],(int)game->joueur1.unites[game->id1].coord[1], game->joueur1, CLIC);


      break;


      case CHOIX_EMPLACEMENT:
      affichageTextureTextes(&game->surfaceTextes[TEXTE_PLACEMENT], game->textureTextes[TEXTE_PLACEMENT], 1.28, 0.12);
      if(game->tour == TOUR_JOUEUR1){
        glColor3f(1,1,1);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR1], game->textureTextes[TEXTE_JOUEUR1], 1.35, 0.05);
        for(int i = 0; i<10; i++){
          for(int j = 0; j<10; j++){
              if(game->zonePlacement[j][i]==1){
                carre(i+1,j+1, game->joueur1, ACHAT_UNITE);
              }
          }
        }
      }
      else{
        glColor3f(1,1,1);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR2], game->textureTextes[TEXTE_JOUEUR2], 1.35, 0.05);
        for(int i = 0; i<10; i++){
          for(int j = 0; j<10; j++){
              if(game->zonePlacement[j][i]==2){
                carre(i+1,j+1, game->joueur2, ACHAT_UNITE);
              }
          }
        }
      }
      glColor3f(1,1,1);
      break;

    }
    break;
    case SELECTION_UNITE:
      switch (game->tour){
        case TOUR_JOUEUR1:
          affichageTextureTextes(&game->surfaceTextes[TEXTE_SELECTION], game->textureTextes[TEXTE_SELECTION], 1.2, 0.5);
          affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR1], game->textureTextes[TEXTE_JOUEUR1], 1.35, 0.4);
        break;
        case TOUR_JOUEUR2:
          affichageTextureTextes(&game->surfaceTextes[TEXTE_SELECTION], game->textureTextes[TEXTE_SELECTION], 1.2, 0.5);
          affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR2], game->textureTextes[TEXTE_JOUEUR2], 1.35, 0.4);
        break;

      }

    break;

    case ACTIONS:
      bouton(game->boutonPasser);
      bouton(game->boutonDeplacement);
      bouton(game->boutonAttaque);
      glColor3f(1,1,1);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_ACTION], game->textureTextes[TEXTE_ACTION], 1.2, 0.2);
      affichageTexture(game->texturebouton,game->boutonAttaque.longueur,game->boutonAttaque.hauteur,game->boutonAttaque.x,game->boutonAttaque.y);
      affichageTexture(game->texturebouton,game->boutonDeplacement.longueur,game->boutonDeplacement.hauteur,game->boutonDeplacement.x,game->boutonDeplacement.y);
      affichageTexture(game->texturebouton,game->boutonPasser.longueur,game->boutonPasser.hauteur,game->boutonPasser.x,game->boutonPasser.y);
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON_DEPLACEMENT], game->textureTextes[TEXTE_BOUTON_DEPLACEMENT], (float)game->boutonDeplacement.x+0.035, (float)game->boutonDeplacement.y+0.020); //, 1.5, 0.02, 0,0
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON_ATTAQUE], game->textureTextes[TEXTE_BOUTON_ATTAQUE], (float)game->boutonAttaque.x+0.08, (float)game->boutonAttaque.y+0.020); //, 1.5, 0.02, 0,0
      affichageTextureTextes(&game->surfaceTextes[TEXTE_BOUTON_PASSER], game->textureTextes[TEXTE_BOUTON_PASSER], (float)game->boutonPasser.x+0.09, (float)game->boutonPasser.y+0.020); //, 1.5, 0.02, 0,0


      if(game->tour == TOUR_JOUEUR1){
          affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR1], game->textureTextes[TEXTE_JOUEUR1], 1.35, 0.05);
          if(game->idUniteSurvolee==-1 && game->id1!=-1){
            etatUnite(game->joueur1.unites[game->id1], game);
          }

          carre((int)game->joueur1.unites[game->id1].coord[0],(int)game->joueur1.unites[game->id1].coord[1], game->joueur1, CLIC);

          if(game->choix == DEPLACEMENT){
            zoneSurbrillance(game->joueur1,game->id1, game->mapObstacles, DEPLACEMENT, game);
          }
          else if(game->choix == ATTAQUE){
            zoneSurbrillance(game->joueur1,game->id1, game->mapObstacles, ATTAQUE, game);
          }
      }
      if(game->tour == TOUR_JOUEUR2){
        affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR2], game->textureTextes[TEXTE_JOUEUR2], 1.35, 0.05);
        if(game->idUniteSurvolee==-1 && game->id2!=-1){
          etatUnite(game->joueur2.unites[game->id2], game);
        }

          carre((int)game->joueur2.unites[game->id2].coord[0],(int)game->joueur2.unites[game->id2].coord[1], game->joueur2, CLIC);

          if(game->choix == DEPLACEMENT){
            zoneSurbrillance(game->joueur2,game->id2, game->mapObstacles, DEPLACEMENT, game);
          }
          else if(game->choix == ATTAQUE){
            zoneSurbrillance(game->joueur2,game->id2, game->mapObstacles, ATTAQUE, game);
          }
      }
      // if(game->tour == TOUR_JOUEUR2 && game->choix == DEPLACEMENT){
      //   zoneSurbrillance(game->joueur2,game->id2, game->map, DEPLACEMENT);
      // }
      // if(game->tour == TOUR_JOUEUR1 && game->choix == ATTAQUE){
      //   zoneSurbrillance(game->joueur1,game->id1, game->map, ATTAQUE);
      // }
      // if(game->tour == TOUR_JOUEUR2 && game->choix == ATTAQUE){
      //   zoneSurbrillance(game->joueur2,game->id2, game->map, ATTAQUE);
      // }

      // if(game->ySurvol>0 && game->ySurvol<=10 && game->xSurvol>0 && game->xSurvol<=10){
      //   switch(game->map[game->ySurvol-1][game->xSurvol-1]){
      //     case JOUEUR1:
      //       zoneSurbrillance(game->joueur1,game->idUniteSurvolee, game->map, DEPLACEMENT);
      //       break;
      //     case JOUEUR2:
      //       zoneSurbrillance(game->joueur2,game->idUniteSurvolee, game->map, DEPLACEMENT);
      //       break;
      //   }
      // }

      if(game->ySurvol>0 && game->ySurvol<=10 && game->xSurvol>0 && game->xSurvol<=10 && game->etapeJeu!= PLACEMENT_UNITES){
        switch(game->mapObstacles[game->ySurvol-1][game->xSurvol-1]){
          case JOUEUR1:{
            zoneSurbrillance(game->joueur1,game->idUniteSurvolee, game->mapObstacles, DEPLACEMENT, game);



            // int xCoord = 0;
            // int yCoord = 0;
            // selectionCoordonnee(&xCoord, &yCoord, e, game->surface);
            // int id = selectionIdUnite(xCoord,yCoord,game->joueur1);
              Unite uniteCoord = game->joueur1.unites[game->idUniteSurvolee];
              if(game->idUniteSurvolee!=-1){

                etatUnite(uniteCoord, game);
              }
            }
            break;
          case JOUEUR2:
            zoneSurbrillance(game->joueur2,game->idUniteSurvolee, game->mapObstacles, DEPLACEMENT, game);
            Unite uniteCoord = game->joueur2.unites[game->idUniteSurvolee];
            if(game->idUniteSurvolee!=-1){
              etatUnite(uniteCoord, game);
            }
            break;
        }
      }

      break;

      case FIN_JEU:
        bouton(game->boutonRejouer);
        bouton(game->boutonQuitter);
        affichageTexture(game->textfond[IMG_MENU_FIN],game->aspectRatio,1,0,0);
        affichageTexture(game->texturebouton,game->boutonRejouer.longueur,game->boutonRejouer.hauteur,game->boutonRejouer.x,game->boutonRejouer.y);
        affichageTexture(game->texturebouton,game->boutonQuitter.longueur,game->boutonQuitter.hauteur,game->boutonQuitter.x,game->boutonQuitter.y);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_REJOUER], game->textureTextes[TEXTE_REJOUER], (float)game->boutonRejouer.x+0.055, (float)game->boutonRejouer.y+0.01);
        affichageTextureTextes(&game->surfaceTextes[TEXTE_QUITTER], game->textureTextes[TEXTE_QUITTER], (float)game->boutonQuitter.x+0.055, (float)game->boutonQuitter.y+0.01);
        if(game->joueur1.nbUnites == 0 && game->joueur2.nbUnites != 0){
          affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR2_GAGNANT], game->textureTextes[TEXTE_JOUEUR2_GAGNANT], 0.42, 0.3);
          cout << "Gagnant : Joueur 2" << endl;
        }
        else if(game->joueur1.nbUnites != 0 && game->joueur2.nbUnites == 0){
          affichageTextureTextes(&game->surfaceTextes[TEXTE_JOUEUR1_GAGNANT], game->textureTextes[TEXTE_JOUEUR1_GAGNANT], 0.37, 0.3);
          cout << "Gagnant : Joueur 1" << endl;
        }
        else if(game->joueur1.nbUnites == 0 && game->joueur2.nbUnites == 0){
          affichageTextureTextes(&game->surfaceTextes[TEXTE_EGALITE], game->textureTextes[TEXTE_EGALITE], 0.73, 0.3);
          cout << "Les deux joueurs ont perdus" << endl;
        }
      break;
  }

  glColor3f(1,1,1);

  if(game->etapeJeu != MENU  && game->etapeJeu != FIN_JEU){
    for(int i = 0; i<10; i++){
      for(int j = 0; j<10; j++){
        switch(game->mapObstacles[j][i]){


          case JOUEUR1:{
            int id = selectionIdUnite(i+1, j+1, game->joueur1);

            if(game->etapeJeu == PLACEMENT_UNITES || (game->choix == ATTAQUE && game->tour == TOUR_JOUEUR1 && id != game->id1)){
              affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            }
            affichageTexture(game->textureUnites[game->joueur1.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            break;
          }


          case JOUEUR2:{
            int id = selectionIdUnite(i+1, j+1, game->joueur2);
            if(game->etapeJeu == PLACEMENT_UNITES || (game->choix == ATTAQUE && game->tour == TOUR_JOUEUR2 && id != game->id2)){
              affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            }

            affichageTexture(game->textureUnites[game->joueur2.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            break;
          }

        }

      }
    }
  }
}

void affichageCarte(Game* game){
  affichageTexture(game->textfond[IMG_MENUNORMAL],0.875,1,1,0);
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      switch(game->map[j][i]){
        case PLAINE:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case PLAINECHG:
        affichageTexture(game->textureCases[PLAINECHG],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case EAU:
        affichageTexture(game->textureCases[EAU],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE1:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE1],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE2:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE2],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE4:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE4],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE5:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE5],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE6:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE6],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE7:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE7],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE8:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE8],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case ARBRE9:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[ARBRE9],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case EAUBD:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[EAUBD],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case EAUBG:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[EAUBG],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case EAUHG:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[EAUHG],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case EAUHD:
        affichageTexture(game->textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        affichageTexture(game->textureCases[EAUHD],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;
      }

    }
  }

  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      switch(game->mapObstacles[j][i]){
        case JOUEUR1:
        affichageTexture(game->textureCases[game->mapInit[j][i]],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;

        case JOUEUR2:
        affichageTexture(game->textureCases[game->mapInit[j][i]],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
        break;
      }
    }
  }
}

void initialisationBoutons(Game* game){
  initBoutonUnites(game->boutonVikingWoman, 0, 0, 0, 0);
  initBoutonUnites(game->boutonVikingMan, 0, 0, 0, 0);
  initBoutonUnites(game->boutonVikingBeast, 0, 0, 0, 0);
  initBoutonUnites(game->boutonVikingWizard, 0, 0, 0, 0);
  initBoutonUnites(game->boutonVikingChief, 0, 0, 0, 0);
  initBoutonUnites(game->boutonDeadKnight, 0, 0, 0, 0);
  initBoutonUnites(game->boutonDeadBeast, 0, 0, 0, 0);
  initBoutonUnites(game->boutonDeadWizard, 0, 0, 0, 0);
  initBoutonUnites(game->boutonDeadMan, 0, 0, 0, 0);
  initBoutonUnites(game->boutonDeadChief, 0, 0, 0, 0);
}
