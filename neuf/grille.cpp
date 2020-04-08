/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include "unites.h"
#include "grille.h"
#include <stdlib.h>
using namespace std;

//-------------------------------------- Fonctions concernant la grille --------------------------------------//



// Fonction qui dessine la grille et les unites presentes

void dessinerGrille(int taille, Joueur joueurA, Joueur joueurB){

  // Dessine la ligne des abscisses (avec les chiffres)
  cout << "\033[37m";
  cout << endl << "          |";
  for(int i = 1; i <= taille; i++){
    if(i>9){
      cout << "\033[37m" ;
      cout << "  " << i << " |" ;
    }
    else{
    cout << "\033[37m" ;
    cout << "  " << i << "  |" ;
    }

  }

  ligne(taille);

  //Dessine le reste de la grille

  // Pour les y :
  for (int i=1; i <= taille; i++){
    if(i>9){
      cout << "\033[37m" ;
      cout << "    " << i << "    |" ;
    }
    else{
      cout << "\033[37m" ;
      cout << "    " << i << "     |" ;
    }

    // Pour les x :
    for (int j=1; j <= taille; j++){ // pour les x
      int disponibilite = 1;

      // Dessine les unites du joueur 1 dans la grille :
      if (joueurA.nbUnitesJoueur > 0){
        for(int compteur = 0; compteur < joueurA.nbUnitesInitial ; compteur++){
          if (joueurA.unites[compteur].coordUnite[0]==j && joueurA.unites[compteur].coordUnite[1]==i){
            disponibilite = 0;
            if (joueurA.unites[compteur].type==0){
              cout << joueurA.couleur << "  n  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurA.unites[compteur].type==1){
              cout << joueurA.couleur << "  O  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurA.unites[compteur].type==2){
              cout << joueurA.couleur << "  H  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurA.unites[compteur].type==3){
              cout << joueurA.couleur << "  E  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurA.unites[compteur].type==4){
              cout << joueurA.couleur << "  N  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurA.unites[compteur].type==5){
              cout << joueurA.couleur << "  S  ";
              cout << "\033[37m" << "|" ;
            }
          }
        }
      }

      // Dessine les unites du joueur 2 dans la grille :
      if (joueurB.nbUnitesJoueur > 0){
        for(int compteur = 0; compteur < joueurB.nbUnitesInitial; compteur++){
          if (joueurB.unites[compteur].coordUnite[0]==j && joueurB.unites[compteur].coordUnite[1]==i){
            disponibilite = 0;
            if (joueurB.unites[compteur].type==0){
              cout << joueurB.couleur << "  n  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurB.unites[compteur].type==1){
              cout << joueurB.couleur << "  O  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurB.unites[compteur].type==2){
              cout << joueurB.couleur << "  H  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurB.unites[compteur].type==3){
              cout << joueurB.couleur << "  E  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurB.unites[compteur].type==4){
              cout << joueurB.couleur << "  N  ";
              cout << "\033[37m" << "|" ;
            }
            else if (joueurB.unites[compteur].type==5){
              cout << joueurB.couleur << "  S  ";
              cout << "\033[37m" << "|" ;
            }
          }
        }
      }

      if (disponibilite == 1){
        cout << "\033[37m" ;
        cout << "     |" ;
      }
    }

    ligne(taille);
  }
  cout << endl;

} // fin de dessinerGrille()


//------------------------------------------------------------------------------------------------------------//

// Fonction qui dessine une ligne pour separer les consignes et rendre le jeu plus lisible

void ligne(int taille){
  cout << "\033[37m" << endl;
  for (int i=0; i<= taille+1; i++){
    cout << "______" ;
  }
  cout << endl;
} // fin ligne()
