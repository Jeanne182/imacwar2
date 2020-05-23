#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"
#include "game/a_star.h"

#include <cstring>


int main(){

  Game game;
  initialisationGame(&game);

  initialisationTextes(game.surfaceTextes, game.policeTextes, game.textureTextes);

  creationTexture(&game.textfond,game.surffond);

  int loop = 1;

  int xDepart = 2;
  int yDepart = 5;

  int xCible= 7;
  int yCible= 8;
  list<Noeud> chemin = a_star(xDepart, yDepart, xCible, yCible);
  caseOptimaleAtteignable(&xDepart, &yDepart, 3, chemin);

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

              case JOUEUR1:{
                affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                int id = selectionIdUnite(i+1, j+1, game.joueur1);
                affichageTexture(game.textureUnites[game.joueur1.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                break;
              }


              case JOUEUR2:{
                affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                int id = selectionIdUnite(i+1, j+1, game.joueur2);
                affichageTexture(game.textureUnites[game.joueur2.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
                break;
              }

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
      initBoutonUnites(game.boutonHobbit);
      initBoutonUnites(game.boutonHumain);
      initBoutonUnites(game.boutonNain);
      initBoutonUnites(game.boutonElfe);
      initBoutonUnites(game.boutonGandalf);
      initBoutonUnites(game.boutonSmeagol);
      initBoutonUnites(game.boutonOrque);
      initBoutonUnites(game.boutonUrukhai);
      initBoutonUnites(game.boutonNazgul);
      initBoutonUnites(game.boutonSaruman);
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
        //affichageTexture(descriptionNain, game.boutonAchat.longueur,game.boutonAchat.hauteur,game.boutonAchat.x,game.boutonAchat.y);
        // if(game.textureTextes[TEXTE_PV]!=NULL){
        //   affichageTextureTextes(game.textureTextes[TEXTE_PV], game.boutonAchat.longueur,game.boutonAchat.hauteur,game.boutonAchat.x,game.boutonAchat.y);
        // }
          switch (game.tour) {
            case TOUR_JOUEUR1:
              affichageTexture(game.textureUnites[HOBBIT],game.boutonHobbit.longueur,game.boutonHobbit.hauteur,game.boutonHobbit.x,game.boutonHobbit.y);
              affichageTexture(game.textureUnites[HUMAN],game.boutonHumain.longueur,game.boutonHumain.hauteur,game.boutonHumain.x,game.boutonHumain.y);
              affichageTexture(game.textureUnites[NAIN],game.boutonNain.longueur,game.boutonNain.hauteur,game.boutonNain.x,game.boutonNain.y);
              affichageTexture(game.textureUnites[ELFE],game.boutonElfe.longueur,game.boutonElfe.hauteur,game.boutonElfe.x,game.boutonElfe.y);
              affichageTexture(game.textureUnites[GANDALF],game.boutonGandalf.longueur,game.boutonGandalf.hauteur,game.boutonGandalf.x,game.boutonGandalf.y);
              break;
            case TOUR_JOUEUR2:
              affichageTexture(game.textureUnites[SMEAGOL],game.boutonSmeagol.longueur,game.boutonSmeagol.hauteur,game.boutonSmeagol.x,game.boutonSmeagol.y);
              affichageTexture(game.textureUnites[ORQUE],game.boutonOrque.longueur,game.boutonOrque.hauteur,game.boutonOrque.x,game.boutonOrque.y);
              affichageTexture(game.textureUnites[URUK],game.boutonUrukhai.longueur,game.boutonUrukhai.hauteur,game.boutonUrukhai.x,game.boutonUrukhai.y);
              affichageTexture(game.textureUnites[NAZGUL],game.boutonNazgul.longueur,game.boutonNazgul.hauteur,game.boutonNazgul.x,game.boutonNazgul.y);
              affichageTexture(game.textureUnites[SAROUMANE],game.boutonSaruman.longueur,game.boutonSaruman.hauteur,game.boutonSaruman.x,game.boutonSaruman.y);
            break;
          }
          break;

        case ACTIONS:
          bouton(game.boutonDeplacement);
          bouton(game.boutonAttaque);
          glColor3f(1,1,1);
          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON_DEPLACEMENT], game.textureTextes[TEXTE_BOUTON_DEPLACEMENT], (float)game.boutonDeplacement.x+0.008, (float)game.boutonDeplacement.y+0.004); //, 1.5, 0.02, 0,0
          affichageTextureTextes(&game.surfaceTextes[TEXTE_BOUTON_ATTAQUE], game.textureTextes[TEXTE_BOUTON_ATTAQUE], (float)game.boutonAttaque.x+0.04, (float)game.boutonAttaque.y+0.004); //, 1.5, 0.02, 0,0

          if(game.tour == TOUR_JOUEUR1 && game.choix == DEPLACEMENT){
            zoneSurbrillance(game.joueur1,game.id1, game.map, DEPLACEMENT);
          }
          if(game.tour == TOUR_JOUEUR2 && game.choix == DEPLACEMENT){
            zoneSurbrillance(game.joueur2,game.id2, game.map, DEPLACEMENT);
          }
          if(game.tour == TOUR_JOUEUR1 && game.choix == ATTAQUE){
            zoneSurbrillance(game.joueur1,game.id1, game.map, ATTAQUE);
          }
          if(game.tour == TOUR_JOUEUR2 && game.choix == ATTAQUE){
            zoneSurbrillance(game.joueur2,game.id2, game.map, ATTAQUE);
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

              gererClic(&game,e);


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
