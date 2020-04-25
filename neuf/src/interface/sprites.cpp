/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"


//-------------------------------------- Fonctions concernant la grille --------------------------------------//

void affichageUnite(Joueur joueur, int longueurCarte, int largeurCarte){
  if(joueur.nbUnites != 0){
    for(int i=0; i<joueur.nbUnites; i++){
      float x = joueur.unites[i].coord[0];
      float y = joueur.unites[i].coord[1];

      glPushMatrix();
        glTranslatef((x-1)/10,(y-1)/10,0);
        glBegin(GL_POLYGON);
        if (joueur.id == 1){
          glColor3f(0,0,1);
        }
        else {glColor3f(1,0,0);}
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
