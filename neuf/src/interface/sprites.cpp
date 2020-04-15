/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include "./../unites/unites.h"
#include "interface.h"
#include <stdlib.h>
using namespace std;

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>


//-------------------------------------- Fonctions concernant la grille --------------------------------------//

void affichageUnite(Joueur joueur, int longueurCarte, int largeurCarte, SDL_Surface* surface){
  if(joueur.nbUnites != 0){
    for(int i=0; i<joueur.nbUnites; i++){
      float x = joueur.unites[i].coord[0];
      float y = joueur.unites[i].coord[1];
      //conversionRepereOpenGL(&x,&y,surface);
      /*cout<<"x:"<<i<<x<<endl;
      cout<<"y="<<i<<y<<endl;*/
      glPushMatrix();
        glTranslatef((x-1)/10,(y-1)/10,0);
        glBegin(GL_POLYGON);
        glColor3f(0,1,0);
        glVertex2f(0.1, 0.1);
        glVertex2f(0,0.1);
        glVertex2f(0, 0);
        glVertex2f(0.1, 0);
        glEnd();
        glPopMatrix();
        //glColor3f(1,1,1);

    }
  }

}
