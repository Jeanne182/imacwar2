#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
#include "interface/text.h"

/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 1500;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Imacwar II";


/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;
static float aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
static const float GL_VIEW_SIZE =1.;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


//-------------------------------------- Fonctions concernant la grille --------------------------------------//



// Fonction qui dessine la grille et les unites presentes
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{
    /*SDL_Surface* surface_temp = SDL_SetVideoMode(
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);*/
    /*if(NULL == surface_temp)
    {
        fprintf(
            stderr,
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }*/
    //*surface = surface_temp;
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
  /* Initialisation de la SDL */
    //if(-1 == SDL_Init(SDL_INIT_VIDEO))
//    {
//        fprintf(
//            stderr,
//            "Impossible d'initialiser la SDL. Fin du programme.\n");
//        return EXIT_FAILURE;
//    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    game->surface = SDL_SetVideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_DOUBLEBUF); //SDL_GL_DOUBLEBUFFER //SDL_OPENGL
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

// void initialisationTexturesCarte(GLuint textureCases[3], SDL_Surface* surfaceCases[3]){
//     creationTexture(&textureCases[PLAINE], surfaceCases[PLAINE]);
//     creationTexture(&textureCases[EAU], surfaceCases[EAU]);
//     creationTexture(&textureCases[ARBRE], surfaceCases[ARBRE]);
// }

// void initialisationTexturesUnites(GLuint textureUnites[3], SDL_Surface* surfaceUnites[3], EnumUnites unite){
//     creationTexture(&textureUnites[unite], surfaceUnites[unite]);
// }

int finProgrammeSDL(Game* game){
    /* Liberation des ressources associees a la SDL */
    glDeleteTextures(1, &game->textureCases[PLAINE]);
    glDeleteTextures(1, &game->textureCases[EAU]);
    glDeleteTextures(1, &game->textureCases[ARBRE]);
    glDeleteTextures(1, &game->textureUnites[HUMAN]);
    glDeleteTextures(1, &game->textureUnites[HOBBIT]);
    glDeleteTextures(1, &game->textureUnites[NAIN]);
    glDeleteTextures(1, &game->textureUnites[ELFE]);
    glDeleteTextures(1, &game->textureUnites[GANDALF]);
    glDeleteTextures(1, &game->textureUnites[ORQUE]);
    glDeleteTextures(1, &game->textureUnites[SMEAGOL]);
    glDeleteTextures(1, &game->textureUnites[URUK]);
    glDeleteTextures(1, &game->textureUnites[NAZGUL]);
    glDeleteTextures(1, &game->textureUnites[SAROUMANE]);

    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON_DEPLACEMENT]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON_ATTAQUE]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON1J]);
    glDeleteTextures(1, &game->textureTextes[TEXTE_BOUTON2J]);
    //SDL_FreeSurface(image);

    SDL_Quit();

    return EXIT_SUCCESS;
}



void carre(float x, float y, Joueur joueur, int choix){
  glPushMatrix();
    glTranslatef((x-1)/10,(y-1)/10,0);
    glBegin(GL_POLYGON);
    if (joueur.id == 1){
      if(choix==ATTAQUE){
        glColor4f(0.55, 0.42, 0.26,0.4);
      }
      else{
        glColor4f(1,1,1,0.4);
      }
    }
    else {
      if(choix==ATTAQUE){
        glColor4f(0.55, 0.42, 0.26,0.4);
      }
      else{
        glColor4f(0,0,0,0.4);
      }
    }
    glVertex2f(0.1, 0.1);
    glVertex2f(0,0.1);
    glVertex2f(0, 0);
    glVertex2f(0.1, 0);
    glEnd();
    glPopMatrix();
    //glColor3f(1,1,1);
}



void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface){
  *x = (int)(1+10*(*x)*aspectRatio/(float)surface->w);
  *y = (int)(1+10*(*y)/(float)surface->h);
}
