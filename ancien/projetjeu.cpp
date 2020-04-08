/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "unites.h"
#include "grille.h"
using namespace std;

int main(){

  // Lancement du Jeu - Page accueil

  cout << "\033[37m" << endl << endl << "Bienvenue dans ImacWar !" <<endl << endl;
  cout << "\033[32m"<< "Tapez 0" << "\033[37m"<<" pour lire les règles du jeu, ou "<<"\033[32m"<<"tapez 1 " <<"\033[37m" <<"pour commencer directement la bataille !"<<endl;
  cout << "\033[32m"<<"Tapez Q"<<"\033[37m"<<" pour quitter le jeu." << endl;

  char debutJeu ;
  int tailleGrille, niveau;
  cin >> debutJeu ;

  while(debutJeu!='0' && debutJeu!='1' && debutJeu!='Q'){
    messageErreur(13);
    cout << "\033[32m"<< "Tapez 0" << "\033[37m"<<" pour lire les règles du jeu, ou "<<"\033[32m"<<"tapez 1 " <<"\033[37m" <<"pour commencer directement la bataille !"<<endl;
    cout << "\033[32m"<<"Tapez Q"<<"\033[37m"<<" pour quitter le jeu." << endl;
    cin >> debutJeu;
    }

  // Si 0 : Affichage des regles du jeu puis du choix du niveau. Lance ensuite la partie.

  if(debutJeu=='0'){
    if (reglesJeu()==1){

      niveau = reglesNiveaux();

      if (niveau==1){tailleGrille = 6;}
      else if (niveau==2){tailleGrille = 10;}
      else {tailleGrille = 14;}

      jeuPartie(niveau, tailleGrille);
    }
  }

  // Si 1 : Choix du niveau puis lance la partie.

  else if (debutJeu=='1'){

      niveau = reglesNiveaux();

      if (niveau==1){tailleGrille = 6;}
      else if (niveau==2){tailleGrille = 10;}
      else {tailleGrille = 14;}

      if (jeuPartie(niveau, tailleGrille)==1){

        // Si jeuPartie() renvoie 1 c'est que la partie est terminée : un des joueurs a perdu toutes ses unites

        cout << endl <<"\033[37m" << "Voulez-vous relancer une partie (" << "\033[32m"<<"tapez 1"<< "\033[37m"<< ") ou quitter le jeu (" << "\033[32m"<<"tapez Q"<< "\033[37m"<< ") ?" << endl;
        char finJeu;
        cin >> finJeu;

        while(finJeu!='1' && finJeu!='Q'){
          messageErreur(13);
          cout <<endl << "\033[37m" << "Voulez-vous relancer une partie (" << "\033[32m"<<"tapez 1"<< "\033[37m"<< ") ou quitter le jeu (" << "\033[32m"<<"tapez Q"<< "\033[37m"<< ") ?" << endl;
          cin >> finJeu;
        }

        // Si 0 : Relance une nouvelle partie

        if(finJeu=='1'){
          main();
        }

        // Si 1 : Quitte le jeu

        else if (finJeu=='Q') {
          exit(1);
        }



      }
  }

    // Si 2 : Quitte le jeu

    else if(debutJeu=='Q'){
      exit(1);
    }

    return 0;

}
