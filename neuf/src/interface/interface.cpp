/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"


/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 900;
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
    SDL_Surface* surface_temp = SDL_SetVideoMode(
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp)
    {
        fprintf(
            stderr,
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;
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

int initialisationSDL(GLuint* textureMap, SDL_Surface* surface){

  /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(
            stderr,
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    creationTexture(textureMap, "src/img/quadrillage.jpg");


    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    surface = SDL_SetVideoMode(
        WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    if(NULL == surface)
    {
        fprintf(
            stderr,
            "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    /* Initialisation du titre de la fenetre */
	   SDL_WM_SetCaption(WINDOW_TITLE, NULL);
     return 1;
}

int finProgrammeSDL(GLuint* textureMap){
    /* Liberation des ressources associees a la SDL */
    glDeleteTextures(1, textureMap);
    //SDL_FreeSurface(image);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void creationTexture(GLuint *texture, char* chemin_image){

  SDL_Surface* image = IMG_Load(chemin_image);

  if(image==NULL){
    printf("L'image de la carte n'a pas pu se charger");
    exit(1);
  }


  glGenTextures(1, texture);

  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);


}

void affichageTexture(GLuint texture, float longueur, float largeur){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glBegin(GL_QUADS);

  glTexCoord2f(1, 0);
  glVertex2f(longueur, largeur);

  glTexCoord2f(0, 0); //angle haut gauche
  glVertex2f(0,largeur);

  glTexCoord2f(0, 1);
  glVertex2f(0, 0);

  glTexCoord2f(1, 1);
  glVertex2f(longueur, 0);

  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}


void conversionOpenGLRepere(int* x, int* y, SDL_Surface* surface){
  *x = (int)(1+10*(*x)*aspectRatio/(float)surface->w);
  *y = (int)(1+10*(*y)/(float)surface->h);
}
