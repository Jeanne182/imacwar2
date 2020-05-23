#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"

#include <cstring>


int main(){

  Game game;
  initialisationGame(&game);

  initialisationTextes(game.surfaceTextes, game.policeTextes, game.textureTextes);

  creationTexture(&game.textfond,game.surffond);

  int loop = 1;

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      /* Placer ici le code de dessin */
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

      glColor3f(1,1,1);

      if(game.etapeJeu != MENU){
        for(int i = 0; i<10; i++){
          for(int j = 0; j<10; j++){
            switch(game.map[j][i]){
              case PLAINE:
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              break;

              case EAU:
              affichageTexture(game.textureCases[EAU],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              break;

              case ARBRE:
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              affichageTexture(game.textureCases[ARBRE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              break;

              case JOUEUR1:
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              break;

              case JOUEUR2:
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              break;

            }

          }
        }
      }
      // for(int x=0; x<=10; x++){
      //   for(int y=0; y<=10; y++){
      //     if(game.map[y-1][x-1]==PLAINE){
      //       carre(x,y,game.joueur1);
      //     }
      //   }
      // }

      //affichageTexture(texteDeplacement, game.boutonDeplacement.longueur, game.boutonDeplacement.hauteur,game.boutonDeplacement.x,game.boutonDeplacement.y);
      initBoutonUnites(game.boutonVikingWoman, 0, 0, 0, 0);
      initBoutonUnites(game.boutonVikingMan, 0, 0, 0, 0);
      initBoutonUnites(game.boutonVikingBeast, 0, 0, 0, 0);
      initBoutonUnites(game.boutonVikingWizard, 0, 0, 0, 0);
      initBoutonUnites(game.boutonVikingChief, 0, 0, 0, 0);
      initBoutonUnites(game.boutonDeadKnight, 0, 0, 0, 0);
      initBoutonUnites(game.boutonDeadBeast, 0, 0, 0, 0);
      initBoutonUnites(game.boutonDeadWizard, 0, 0, 0, 0);
      initBoutonUnites(game.boutonDeadMan, 0, 0, 0, 0);
      initBoutonUnites(game.boutonDeadChief, 0, 0, 0, 0);
      glColor3f(1,1,1);

      switch (game.etapeJeu) { //Tous les trucs statiques qui ne dépendent pas des clics,
        case MENU:
          affichageTexture(game.textfond,game.aspectRatio,1,0,0);
          bouton(game.bouton1Joueur);
          bouton(game.bouton2Joueurs);
          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON1J], game.textureTextes[TEXTE_BOUTON1J], (float)game.bouton1Joueur.x+0.023, (float)game.bouton1Joueur.y+0.002);
          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON2J], game.textureTextes[TEXTE_BOUTON2J], (float)game.bouton2Joueurs.x+0.015, (float)game.bouton2Joueurs.y+0.002);

          break;


        case PLACEMENT_UNITES:
        bouton(game.boutonAchat);
        glColor3f(1,1,1);
        surbrillanceAchat(game.achat_type, game);

        if(game.tour == TOUR_JOUEUR1){
          for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                if(game.zonePlacement[j][i]==1){
                  carre(i+1,j+1, game.joueur1, ACHAT_UNITE);
                }
            }
          }
        }
        else{
          for(int i = 0; i<10; i++){
            for(int j = 0; j<10; j++){
                if(game.zonePlacement[j][i]==2){
                  carre(i+1,j+1, game.joueur2, ACHAT_UNITE);
                }
            }
          }
        }
        glColor3f(1,1,1);


        //affichageTexture(descriptionVikingBeast, game.boutonAchat.longueur,game.boutonAchat.hauteur,game.boutonAchat.x,game.boutonAchat.y);
        // if(game.textureTextes[TEXTE_PV]!=NULL){
        //   affichageTextureTextes(game.textureTextes[TEXTE_PV], game.boutonAchat.longueur,game.boutonAchat.hauteur,game.boutonAchat.x,game.boutonAchat.y);
        // }
          switch (game.tour) {
            case TOUR_JOUEUR1:
              affichageTexture(game.textureUnites[VIKINGWOMAN],game.boutonVikingWoman.longueur,game.boutonVikingWoman.hauteur,game.boutonVikingWoman.x,game.boutonVikingWoman.y);
              affichageTexture(game.textureUnites[VIKINGMAN],game.boutonVikingMan.longueur,game.boutonVikingMan.hauteur,game.boutonVikingMan.x,game.boutonVikingMan.y);
              affichageTexture(game.textureUnites[VIKINGBEAST],game.boutonVikingBeast.longueur,game.boutonVikingBeast.hauteur,game.boutonVikingBeast.x,game.boutonVikingBeast.y);
              affichageTexture(game.textureUnites[VIKINGWIZARD],game.boutonVikingWizard.longueur,game.boutonVikingWizard.hauteur,game.boutonVikingWizard.x,game.boutonVikingWizard.y);
              affichageTexture(game.textureUnites[VIKINGCHIEF],game.boutonVikingChief.longueur,game.boutonVikingChief.hauteur,game.boutonVikingChief.x,game.boutonVikingChief.y);
              break;
            case TOUR_JOUEUR2:
              affichageTexture(game.textureUnites[DEADKNIGHT],game.boutonDeadKnight.longueur,game.boutonDeadKnight.hauteur,game.boutonDeadKnight.x,game.boutonDeadKnight.y);
              affichageTexture(game.textureUnites[DEADBEAST],game.boutonDeadBeast.longueur,game.boutonDeadBeast.hauteur,game.boutonDeadBeast.x,game.boutonDeadBeast.y);
              affichageTexture(game.textureUnites[DEADWIZARD],game.boutonDeadWizard.longueur,game.boutonDeadWizard.hauteur,game.boutonDeadWizard.x,game.boutonDeadWizard.y);
              affichageTexture(game.textureUnites[DEADMAN],game.boutonDeadMan.longueur,game.boutonDeadMan.hauteur,game.boutonDeadMan.x,game.boutonDeadMan.y);
              affichageTexture(game.textureUnites[DEADCHIEF],game.boutonDeadChief.longueur,game.boutonDeadChief.hauteur,game.boutonDeadChief.x,game.boutonDeadChief.y);
            break;
          }
          break;

        // case SELECTION_UNITE:
        // carre((int)game.joueur1.unites[game.id1].coord[0],(int)game.joueur1.unites[game.id1].coord[1], game.joueur1, CLIC);

        case ACTIONS:
          bouton(game.boutonDeplacement);
          bouton(game.boutonAttaque);
          glColor3f(1,1,1);

          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON_DEPLACEMENT], game.textureTextes[TEXTE_BOUTON_DEPLACEMENT], (float)game.boutonDeplacement.x+0.008, (float)game.boutonDeplacement.y+0.004); //, 1.5, 0.02, 0,0
          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON_ATTAQUE], game.textureTextes[TEXTE_BOUTON_ATTAQUE], (float)game.boutonAttaque.x+0.04, (float)game.boutonAttaque.y+0.004); //, 1.5, 0.02, 0,0


          if(game.tour == TOUR_JOUEUR1){
            //if(game.choix == RIEN){
              //carre((int)game.joueur1.unites[game.id1].coord[0],(int)game.joueur1.unites[game.id1].coord[1], game.joueur1, CLIC);

            //}

              if(game.choix == DEPLACEMENT){
                zoneSurbrillance(game.joueur1,game.id1, game.map, DEPLACEMENT);
              }
              else if(game.choix == ATTAQUE){
                zoneSurbrillance(game.joueur1,game.id1, game.map, ATTAQUE);
              }
          }
          if(game.tour == TOUR_JOUEUR2){
            //carre((int)game.joueur2.unites[game.id2].coord[0],(int)game.joueur2.unites[game.id2].coord[1], game.joueur2, CLIC);
              if(game.choix == DEPLACEMENT){
                zoneSurbrillance(game.joueur2,game.id2, game.map, DEPLACEMENT);
              }
              else if(game.choix == ATTAQUE){
                zoneSurbrillance(game.joueur2,game.id2, game.map, ATTAQUE);
              }
          }
          // if(game.tour == TOUR_JOUEUR2 && game.choix == DEPLACEMENT){
          //   zoneSurbrillance(game.joueur2,game.id2, game.map, DEPLACEMENT);
          // }
          // if(game.tour == TOUR_JOUEUR1 && game.choix == ATTAQUE){
          //   zoneSurbrillance(game.joueur1,game.id1, game.map, ATTAQUE);
          // }
          // if(game.tour == TOUR_JOUEUR2 && game.choix == ATTAQUE){
          //   zoneSurbrillance(game.joueur2,game.id2, game.map, ATTAQUE);
          // }

          if(game.ySurvol>0 && game.ySurvol<=10 && game.xSurvol>0 && game.xSurvol<=10){
            switch(game.map[game.ySurvol-1][game.xSurvol-1]){
              case JOUEUR1:
                zoneSurbrillance(game.joueur1,game.idUniteSurvolee, game.map, DEPLACEMENT);
                break;
              case JOUEUR2:
                zoneSurbrillance(game.joueur2,game.idUniteSurvolee, game.map, DEPLACEMENT);
                break;
            }
          }

          break;

          case FIN_JEU:

            if(game.joueur1.nbUnites == 0 && game.joueur2.nbUnites != 0){
              cout << "Gagnant : Joueur 2" << endl;
            }
            else if(game.joueur1.nbUnites != 0 && game.joueur2.nbUnites == 0){
              cout << "Gagnant : Joueur 1" << endl;
            }
            else if(game.joueur1.nbUnites == 0 && game.joueur2.nbUnites == 0){
              cout << "Les deux joueurs ont perdus" << endl;
            }
          break;
      }

      glColor3f(1,1,1);

      if(game.etapeJeu != MENU){
        for(int i = 0; i<10; i++){
          for(int j = 0; j<10; j++){
            switch(game.map[j][i]){


              case JOUEUR1:{
                if(game.etapeJeu == PLACEMENT_UNITES || (game.choix == ATTAQUE && game.tour == TOUR_JOUEUR1)){
                  affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                }
                int id = selectionIdUnite(i+1, j+1, game.joueur1);
                affichageTexture(game.textureUnites[game.joueur1.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                break;
              }


              case JOUEUR2:{
                if(game.etapeJeu == PLACEMENT_UNITES || (game.choix == ATTAQUE && game.tour == TOUR_JOUEUR2)){
                  affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                }
                int id = selectionIdUnite(i+1, j+1, game.joueur2);
                affichageTexture(game.textureUnites[game.joueur2.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                break;
              }

            }

          }
        }
      }



      glColor3f(1,1,1);

      if(game.textureTextes[TEXTE_PV]!=NULL){
        glDeleteTextures(1, &game.textureTextes[TEXTE_PV]);


      }
      if(game.textureTextes[TEXTE_FORCE]!=NULL){
        glDeleteTextures(1, &game.textureTextes[TEXTE_FORCE]);

      }
      if(game.textureTextes[TEXTE_ZONE]!=NULL){
        glDeleteTextures(1, &game.textureTextes[TEXTE_ZONE]);

      }
      if(game.textureTextes[TEXTE_RANGE]!=NULL){
        glDeleteTextures(1, &game.textureTextes[TEXTE_RANGE]);
      }

      char* pv = conversionTexteDyna(20, "Points de vie : ");
      char* force = conversionTexteDyna(70, "Force : ");
      char* zone = conversionTexteDyna(20, "Zone de tir : ");
      char* deplacement = conversionTexteDyna(20, "Distance de déplacement : ");

      creationTexte(&game.surfaceTextes[TEXTE_PV], game.policeTextes[TITRES], &game.textureTextes[TEXTE_PV], pv, SDL_Color{255,255,255});
      affichageTextureTextes(&game.surfaceTextes[TEXTE_PV], game.textureTextes[TEXTE_PV], 1.4, 0.5);

      creationTexte(&game.surfaceTextes[TEXTE_FORCE], game.policeTextes[TITRES], &game.textureTextes[TEXTE_FORCE], force, SDL_Color{255,255,255});
      affichageTextureTextes(&game.surfaceTextes[TEXTE_FORCE], game.textureTextes[TEXTE_FORCE], 1.4, 0.6);

      creationTexte(&game.surfaceTextes[TEXTE_ZONE], game.policeTextes[TITRES], &game.textureTextes[TEXTE_ZONE], zone, SDL_Color{255,255,255});
      affichageTextureTextes(&game.surfaceTextes[TEXTE_ZONE], game.textureTextes[TEXTE_ZONE], 1.4, 0.7);

      creationTexte(&game.surfaceTextes[TEXTE_RANGE], game.policeTextes[TITRES], &game.textureTextes[TEXTE_RANGE], deplacement, SDL_Color{255,255,255});
      affichageTextureTextes(&game.surfaceTextes[TEXTE_RANGE], game.textureTextes[TEXTE_RANGE], 1.4, 0.8);



      free(deplacement);
      free(zone);
      free(force);
      free(pv);
      /* Boucle traitant les evenements */
      SDL_Event e;

      while(SDL_PollEvent(&e))
      {
          /* L'utilisateur ferme la fenetre : */
          if(e.type == SDL_QUIT)
          {
              loop = 0;
              break;
          }

          selectionCoordonnee(&game.xSurvol, &game.ySurvol, e, game.surface);
          game.idUniteSurvolee = selectionIdUnite(game.xSurvol, game.ySurvol,game.joueur1);
          if(game.idUniteSurvolee==-1){
            game.idUniteSurvolee = selectionIdUnite(game.xSurvol, game.ySurvol,game.joueur2);
          }
          etatUnite(e,&game);

          switch(e.type) {
            case SDL_MOUSEBUTTONDOWN:
              if (e.button.button == SDL_BUTTON_LEFT){
                gererClic(&game,e);
              }

              break;
            // case SDL_MOUSEMOTION:
            //   cout<<"Coucou"<<endl;
            //   break;

            // default:
            //       break;
          }
      }


      /* Echange du front et du back buffer : mise a jour de la fenetre */
      SDL_GL_SwapBuffers();

      /* Calcul du temps ecoule */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* Si trop peu de temps s'est ecoule, on met en pause le programme */
      if(elapsedTime < game.framerate_milliseconds){
          SDL_Delay(game.framerate_milliseconds - elapsedTime);
      }
  }
  //finProgrammeSDL(&game.textureMap[PLAINE]);
  glDisable(GL_TEXTURE_2D);

  TTF_CloseFont(game.policeTextes[TITRES]);

  // je comprends pas pq quand on enleve tout ca il met plus free() invalid pointer
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_BOUTON_DEPLACEMENT]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_BOUTON_ATTAQUE]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_BOUTON1J]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_BOUTON2J]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_PV]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_FORCE]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_ZONE]);
  SDL_FreeSurface(&game.surfaceTextes[TEXTE_RANGE]);


  finProgrammeSDL(&game);

  return 0;

};
