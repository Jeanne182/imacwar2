#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"

/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 1500;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Imac Wars II - Ice Version";


/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;
static float aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
static const float GL_VIEW_SIZE =1.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

//int frame = 0;




void reshape(SDL_Surface** surface, unsigned int width, unsigned int height){

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1)
    {
        gluOrtho2D(
        0, GL_VIEW_SIZE * aspectRatio,
         GL_VIEW_SIZE, 0);
    }
    else
    {
        gluOrtho2D( GL_VIEW_SIZE, 0, 0, GL_VIEW_SIZE * aspectRatio);
    }
}

int initialisationSDL(Game* game){

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    game->surface = SDL_SetVideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_DOUBLEBUF);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    reshape(&game->surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(NULL == game->surface)
    {
        fprintf(
            stderr,
            "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    /* Initialisation du titre de la fenetre */
	   SDL_WM_SetCaption(WINDOW_TITLE, NULL);
     TTF_Init();
     return 1;
}


void finJeu(Game* game){
  glDisable(GL_TEXTURE_2D);
  finProgrammeSDL(game);
};


int finProgrammeSDL(Game* game){
    /* Liberation des ressources associees a la SDL */
    glDeleteTextures(1, &game->textureCases[PLAINE]);
    glDeleteTextures(1, &game->textureCases[PLAINECHG]);
    glDeleteTextures(1, &game->textureCases[EAU]);
    glDeleteTextures(1, &game->textureCases[ARBRE]);
    glDeleteTextures(1, &game->textureCases[ARBRE1]);
    glDeleteTextures(1, &game->textureCases[ARBRE2]);
    glDeleteTextures(1, &game->textureCases[ARBRE4]);
    glDeleteTextures(1, &game->textureCases[ARBRE5]);
    glDeleteTextures(1, &game->textureCases[ARBRE6]);
    glDeleteTextures(1, &game->textureCases[ARBRE7]);
    glDeleteTextures(1, &game->textureCases[ARBRE8]);
    glDeleteTextures(1, &game->textureCases[ARBRE9]);
    glDeleteTextures(1, &game->textureCases[EAUBD]);
    glDeleteTextures(1, &game->textureCases[EAUBG]);
    glDeleteTextures(1, &game->textureCases[EAUHD]);
    glDeleteTextures(1, &game->textureCases[EAUHG]);

    glDeleteTextures(1, &game->textureUnites[VIKINGMAN]);
    glDeleteTextures(1, &game->textureUnites[VIKINGWOMAN]);
    glDeleteTextures(1, &game->textureUnites[VIKINGBEAST]);
    glDeleteTextures(1, &game->textureUnites[VIKINGWIZARD]);
    glDeleteTextures(1, &game->textureUnites[VIKINGCHIEF]);
    glDeleteTextures(1, &game->textureUnites[DEADBEAST]);
    glDeleteTextures(1, &game->textureUnites[DEADKNIGHT]);
    glDeleteTextures(1, &game->textureUnites[DEADWIZARD]);
    glDeleteTextures(1, &game->textureUnites[DEADMAN]);
    glDeleteTextures(1, &game->textureUnites[DEADCHIEF]);

    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON_DEPLACEMENT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON_ATTAQUE]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON1J]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON2J]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_PRIX]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_PIECESJ1]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_PIECESJ2]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_JOUEUR1]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_JOUEUR2]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_NOM_UNIT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_PLACEMENT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_CHOIX]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_SELECTION]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_ACTION]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_JOUEUR1_GAGNANT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_JOUEUR2_GAGNANT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_EGALITE]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_CARACTERISTIQUES]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_QUITTER]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_REJOUER]);

    glDeleteTextures(1, &game->textfond[IMG_MENUDEBUT]);
    glDeleteTextures(1, &game->textfond[IMG_MENUNORMAL]);
    glDeleteTextures(1, &game->textfond[IMG_MENU_FIN]);
    glDeleteTextures(1, &game->texturebouton);

    SDL_FreeSurface(game->surface);

    TTF_CloseFont(game->policeTextes[TITRES]);
    TTF_CloseFont(game->policeTextes[TITRE_MEDIUM]);
    TTF_CloseFont(game->policeTextes[TITRES_BOUTONS]);
    TTF_CloseFont(game->policeTextes[SOUSTITRES]);
    TTF_CloseFont(game->policeTextes[NORMAL]);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}


/* Dessine un carré  et lui attribut une couleur : utilisé pour la surbrillance et la selection des unites */
void carre(float x, float y, Joueur joueur, int choix){
  glPushMatrix();
    glTranslatef((x-1)/10,(y-1)/10,0);
    glBegin(GL_POLYGON);
    if (joueur.id == 1){
      if(choix==ATTAQUE){
        glColor4f(0.1, 0.1, 0.1, 0.2);
      }
      else if(choix==DEPLACEMENT || choix==ACHAT_UNITE){
        glColor4f(0.78, 0.27, 0.003,0.4);
      }
      else if(choix==CLIC){
        glColor4f(0.78, 0.27, 0.003,0.55);
      }
      else if(choix==UNITE_PAS_JOUEE){
        glColor4f(0.78, 0.27, 0.003,0.20);
      }
    }
    else {
      if(choix==ATTAQUE){
        glColor4f(0.1, 0.1, 0.1, 0.2);
      }
      else if(choix==DEPLACEMENT || choix==ACHAT_UNITE){
        glColor4f(0.40,0.01,0.33,0.4);
      }
      else if(choix==CLIC){
        glColor4f(0.40,0.01,0.33,0.55);
      }
      else if(choix==UNITE_PAS_JOUEE){
        glColor4f(0.40,0.01,0.33,0.20);
      }
    }
    glVertex2f(0.1, 0.1);
    glVertex2f(0,0.1);
    glVertex2f(0, 0);
    glVertex2f(0.1, 0);
    glEnd();
    glPopMatrix();
    glColor3f(1,1,1);
}



void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface){
  *x = (int)(1+10*(*x)*aspectRatio/(float)surface->w);
  *y = (int)(1+10*(*y)/(float)surface->h);
}


/* Met en evidence l'unite selectionnée au moment de l'achat */
void surbrillanceAchat(int type, Game* game){
  if(type==VIKINGMAN){
    initBoutonUnites(game->boutonVikingMan,0.78, 0.27, 0.003,0.4);
  }
  if(type==VIKINGCHIEF){
    initBoutonUnites(game->boutonVikingChief,0.78, 0.27, 0.003,0.4);
  }
  if(type==VIKINGBEAST){
    initBoutonUnites(game->boutonVikingBeast,0.78, 0.27, 0.003,0.4);
  }
  if(type==VIKINGWIZARD){
    initBoutonUnites(game->boutonVikingWizard,0.78, 0.27, 0.003,0.4);
  }
  if(type==VIKINGWOMAN){
    initBoutonUnites(game->boutonVikingWoman,0.78, 0.27, 0.003,0.4);
  }
  if(type==DEADBEAST){
    initBoutonUnites(game->boutonDeadBeast,0.40,0.01,0.33,0.4);
  }
  if(type==DEADKNIGHT){
    initBoutonUnites(game->boutonDeadKnight,0.40,0.01,0.33,0.4);
  }
  if(type==DEADWIZARD){
    initBoutonUnites(game->boutonDeadWizard,0.40,0.01,0.33,0.4);
  }
  if(type==DEADMAN){
    initBoutonUnites(game->boutonDeadMan,0.40,0.01,0.33,0.4);
  }
  if(type==DEADCHIEF){
    initBoutonUnites(game->boutonDeadChief,0.40,0.01,0.33,0.4);
  }
}
