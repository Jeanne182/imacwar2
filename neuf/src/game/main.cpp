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
  initialisationTextes(game.textureTextes);

  GLuint descriptionNain;
  creationTexte(&descriptionNain, "src/fonts/SummitAttack.ttf", 100, "Petit mais puissant ! Le nain possède une puissance et une défense de 50%. Ses petites jambes lui permettent de se déplacer de deux cases, et ses coups de hache peuvent attaquer à une case de distance. \nPRIX : 30 pieces.", SDL_Color{255,255,255});




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

            case JOUEUR1:{
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              int id = selectionIdUnite(i+1, j+1, game.joueur1);
              affichageTexture(game.textureUnites[game.joueur1.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              //cout << "type 1: "<<game.joueur1.unites[id].type << endl;
              break;
            }


            case JOUEUR2:{
              affichageTexture(game.textureCases[PLAINE],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              int id = selectionIdUnite(i+1, j+1, game.joueur2);
              affichageTexture(game.textureUnites[game.joueur2.unites[id].type],(float)1/10,(float)1/10,(float)i/10,(float)j/10);
              //cout << "type 2: "<<game.joueur2.unites[id].type << endl;
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
        case PLACEMENT_UNITES:
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
          affichageTexture(game.textureTextes[TEXTE_BOUTON_ATTAQUE], game.boutonAttaque.longueur,game.boutonAttaque.hauteur,game.boutonAttaque.x,game.boutonAttaque.y);
          affichageTexture(game.textureTextes[TEXTE_BOUTON_DEPLACEMENT], game.boutonDeplacement.longueur,game.boutonDeplacement.hauteur,game.boutonDeplacement.x,game.boutonDeplacement.y);

          //Surbrillance
          // if(game.tour == TOUR_JOUEUR1 && game.choix == DEPLACEMENT){
          //   zoneSurbrillance(game.joueur1);
          // }
          // if(game.tour == TOUR_JOUEUR2 && game.choix == DEPLACEMENT){
          //   zoneSurbrillance(game.joueur2);
          // }
          break;
      }

      affichageTexture(descriptionNain, 1,0.1,1,0);

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
          etatUnite(e,&game);

          switch(e.type) {
            case SDL_MOUSEBUTTONDOWN:
              cout << "couleur : "<< game.boutonNain.r<<endl;
              if(game.joueur1.nbUnites != 0){
              }
                cout << "Type : "<< game.joueur1.unites[0].type<<endl;


              gererClic(&game,e);
              break;
            // case SDL_MOUSEMOTION:
            //   cout<<"Coucou"<<endl;
            //   break;

            default:
                  break;
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
  TTF_CloseFont(police);
  TTF_Quit();

  SDL_FreeSurface(texte);
  finProgrammeSDL(&game);

  return 0;

};
