/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include "./../unites/unites.h"
#include "interface.h"
#include "./../unites.h"
#include <stdlib.h>
using namespace std;

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 1500;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Imacwar II";


/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;
static float aspectRatio;
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

int affichageInterface(){

  /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(
            stderr,
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
    GLuint textureMap ;
    creationTexture(&textureMap, "src/img/quadrillage.jpg");


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

    /* Boucle principale */
    int loop = 1;
    while(loop)
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glTranslatef(, -5,0);

        affichageTexture(textureMap,1,1);

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
            float aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
            switch(e.type) {
              case SDL_MOUSEBUTTONUP:

                selectionCoordonnee(0,0, e, aspectRatio, surface);
                break;

              default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS)
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associees a la SDL */
    glDeleteTextures(1, &textureMap);
    //SDL_FreeSurface(image);

    SDL_Quit();

    return EXIT_SUCCESS;


} // fin de dessinerGrille()
