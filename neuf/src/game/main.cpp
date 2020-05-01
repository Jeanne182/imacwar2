#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"

int main(){
  SDL_Surface *texte = NULL;
  TTF_Font *police = NULL;

  Game game;
  initialisationGame(&game);
  TTF_Init();

  GLuint texture;

  creationTexte(&texture, "src/fonts/SummitAttack.ttf", 65, "Steeve le BG", SDL_Color{0, 255, 0});

  int loop = 1;

  while(loop){
      /* Recuperation du temps au debut de la boucle */
      Uint32 startTime = SDL_GetTicks();

      /* Placer ici le code de dessin */
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

      glColor3f(1,1,1);

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
            affichageTexture(game.textureUnites[HUMAN],(float)1/10,(float)1/10,(float)i/10,(float)j/10);

            case JOUEUR2:
            affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
            affichageTexture(game.textureUnites[HUMAN],(float)1/10,(float)1/10,(float)i/10,(float)j/10);

          }

        }
      }
      affichageTexture(texture, 1, 1,0,0);

      bouton(game.boutonDeplacement);
      bouton(game.boutonAttaque);

      glColor3f(1,1,1); //pour que les textures ne soient pas de couleur bizarre lol

      //affichageUnite(game.joueur1, &game);
      //affichageUnite(game.joueur2, &game);

      /* Echange du front et du back buffer : mise a jour de la fenetre */
      SDL_GL_SwapBuffers();
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

          switch(e.type) {
            case SDL_MOUSEBUTTONUP:

              gererClic(&game,e);
              break;

            default:
                  break;
          }
      }

      /* Calcul du temps ecoule */
      Uint32 elapsedTime = SDL_GetTicks() - startTime;
      /* Si trop peu de temps s'est ecoule, on met en pause le programme */
      if(elapsedTime < game.framerate_milliseconds){
          SDL_Delay(game.framerate_milliseconds - elapsedTime);
      }
  }
  //finProgrammeSDL(&game.textureMap[PLAINE]);
  glDisable(GL_TEXTURE_2D);
  TTF_CloseFont(police);
  TTF_Quit();

  SDL_FreeSurface(texte);
  finProgrammeSDL(&game);

  return 0;

};
