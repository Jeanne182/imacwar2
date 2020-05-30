#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"
#include "game/a_star.h"
#include <GL/glut.h>
#include <cstring>


int main(){


  Game game;
  initialisationGame(&game);
  initialisationDynamique(&game);


  int loop = 1;

  // int xDepart = 2;
  // int yDepart = 5;
  //
  // int xCible= 7;
  // int yCible= 8;
  // Noeud* chemin = a_star(xDepart, yDepart, xCible, yCible, game.map);
  //caseOptimaleAtteignable(&xDepart, &yDepart, 3, chemin);

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      affichage(&game);
      if(game.tour == TOUR_JOUEUR2 && game.modeJeu == ORDI_MODE){
        if(game.etapeJeu==SELECTION_UNITE){
          game.etapeJeu=ACTIONS;
        }
        switch(game.etapeJeu){
        case ACTIONS:{

            int idOrdi = 0;
            while(game.joueur2.unites[idOrdi].vie ==0 || game.uniteJouee[idOrdi] ==1 || idOrdi>game.joueur2.nbUnitesInitial){
              idOrdi++;
            }

            game.uniteJouee[idOrdi]=1;
            cout << "idOrdi : "<<idOrdi<<endl<<endl;
          // for(int idOrdi=0; idOrdi<game.joueur2.nbUnitesInitial; idOrdi++){

            int xCible = -1;
            int yCible = -1;
            int xOrdi = game.joueur2.unites[idOrdi].coord[0];
            int yOrdi = game.joueur2.unites[idOrdi].coord[1];
            if(game.joueur2.unites[idOrdi].vie!=0){
              choixCible(xOrdi, yOrdi,&xCible,&yCible, game.mapObstacles);
              if(cibleInZone(xOrdi, yOrdi,xCible,yCible, game.joueur2.unites[idOrdi].zoneDeTir)==true){
                int idEnnemi = selectionIdUnite(xCible, yCible, game.joueur1);
                cout<<"CHOIX ATTAQUE, idEnnemi : "<<idEnnemi<<endl;
                attaqueOrdi(&game.joueur2, &game.joueur1, idOrdi, idEnnemi, &game);
                SDL_Delay(1000);
              }

              else{
                Noeud* chemin = a_star(xOrdi,yOrdi, xCible, yCible, game.mapObstacles);
                caseOptimaleAtteignable(&xOrdi, &yOrdi, game.joueur2.unites[idOrdi].distance, chemin);

                insertionCoordonnees(&game, &game.joueur2.unites[idOrdi], xOrdi, yOrdi, JOUEUR2);
                SDL_Delay(1000);
                cout<<"CHOIX DEPLACEMENT"<<endl;
              }

            }

          // }
          if (verificationUniteJouee(game.uniteJouee,game.joueur2.nbUnites)==true){
            initialiseUniteJouee(game.uniteJouee);
            game.tour = TOUR_JOUEUR1;
            game.etapeJeu= SELECTION_UNITE;
            game.choix= RIEN;
          }

          // game.tour = TOUR_JOUEUR1;
          }
          break;
          }

      }

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

          // int xCoord = 0;
          // int yCoord = 0;
          // selectionCoordonnee(&xCoord, &yCoord, e, game.surface);
          // int id = selectionIdUnite(xCoord,yCoord,game.joueur1);
          // Unite uniteCoord = game.joueur1.unites[id];
          // if(id!=-1){
          //   etatUnite(uniteCoord, &game);
          // }

          switch(e.type) {
            case SDL_MOUSEBUTTONDOWN:
              if (e.button.button == SDL_BUTTON_LEFT){
                cout<<"e.button " <<e.button.x<<" "<<e.button.y<<endl<<endl;
                // float xTest = 0;
                // float yTest = 0;
                // //selectionCoordonnee(&xTest, &yTest, e, game.surface);
                // //cout<<"Test"<<xTest<<" "<<yTest<<endl;
                // xTest = (float)(1+10*(e.button.x)*game.aspectRatio/(float)game.surface->w);
                // yTest = (float)(1+10*(e.button.y)/(float)game.surface->h);
                // cout<<"Test"<<xTest<<" "<<yTest<<endl<<endl;

                gererClic(&game,e);
              }

              break;

              case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE){
                  finJeu(&game);
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


  return 0;

};
