#include "unites/unites.h"
#include "interface/interface.h"

void bouton(Bouton bouton){
  float x = bouton.x;
  float y = bouton.y;
  float longueur = bouton.longueur;
  float hauteur = bouton.hauteur;
  float r = bouton.r;
  float g = bouton.g;
  float b = bouton.b;

  glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(r,g,b);
    glVertex2f(x, y);
    glVertex2f(x + longueur, y);
    glVertex2f(x + longueur, y + hauteur);
    glVertex2f(x, y + hauteur);
    glEnd();
  glPopMatrix();
}
