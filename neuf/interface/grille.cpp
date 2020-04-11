/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include "./../unites.h"
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

void affichageTexture(GLuint texture, int longueur, int largeur){
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
