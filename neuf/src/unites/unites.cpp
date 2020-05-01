/*
Fanny Joseph
Jeanne Lebigre
Mattéo Popoff

IMAC 1 - Projet Prog&Algo S1
*/

#include "unites/unites.h"
#include "interface/interface.h"
#include "game/game.h"
using namespace std;

bool placementUnite(Joueur *joueur, SDL_Event e, Game* game){

    int id = joueur->nbUnites;
    if(joueur->nbUnites <= 3){
      Unite unite;
      unite.id =id;
      unite.distance=3;
      unite.type = HUMAN;


      //MODIFIé AVEC STEEVE
      int x=0;
      int y=0;
      selectionCoordonnee(&x,&y, e, game->surface);
      cout << "x : " << x << " y : " << y << endl;
      if(verificationZone(*joueur, x, y, game)==true && verificationCaseLibre(*joueur, x, y)==true){
        insertionCoordonnees(&unite, x, y);
        joueur->unites[id] = unite;
        joueur->nbUnites ++;
        joueur->nbUnitesInitial++;
        return true;
      }
    }
    return false;
}


bool placementUnitesJoueurs(Game* game, SDL_Event e){
  if (game->tour == TOUR_JOUEUR1){
    if(placementUnite(&game->joueur1, e, game)==true){
      game->tour = TOUR_JOUEUR2;
      return true;
    }
  }
  else {
    if(placementUnite(&game->joueur2, e, game)==true){
      game->tour = TOUR_JOUEUR1;
      return true;
    }
  }
  return false;
}

void deplacement(Joueur* joueur, int id, SDL_Event e, Game* game){

  int xNew, yNew;
  selectionCoordonnee(&xNew,&yNew, e, game->surface);
  if(verificationCaseLibre(game->joueur1, xNew, yNew)==true && verificationCaseLibre(game->joueur2, xNew, yNew)==true && verificationDistance(*joueur, xNew, yNew, id, game)==true){
    insertionCoordonnees(&joueur->unites[id], xNew, yNew);
    cout << "case libre" << endl;
    if(game->tour == TOUR_JOUEUR2){
      game->tour = TOUR_JOUEUR1;
    }
    else{
      game->tour = TOUR_JOUEUR2;
    }
    game->choix = RIEN;
    game->etapeJeu = SELECTION_UNITE;
  }
  else{
    cout << "Cette case est déjà occupée, veuillez choisir une autre case OU Votre distance de déplacement n'est pas respectée" << endl;
  }
}

void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int id, , SDL_Event e, Game* game){
  int xAttaque, yAttaque;
  selectionCoordonnee(&xAttaque, &yAttaque, e, game->surface);

  // Verifie que la créature selectionnee est bien une unite ennemie : A FAIRE EN FONCTION

}
/*
void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int *xSelection, int *ySelection, int tailleGrille){


  int idTour, idEnnemi;
  int x, y;
  char choix;



  if(verifUniteEnnemie(*joueurTour, *joueurEnnemi, x, y)==0){
    cout <<  joueurTour->couleur << "Voulez-vous finalement déplacer une créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), selectionner une autre creature ennemie à attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou alors ne rien faire (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ?" << endl << endl;
    char change;
    cin >> change;

    while(change!='0' && change!='1' && change!='2'){
        messageErreur(13);
        cout <<  joueurTour->couleur << "Voulez-vous finalement déplacer une créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), selectionner une autre creature ennemie à attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou alors ne rien faire (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ?" << endl << endl;
        cin >> change;
    }
    if(change=='0'){
      deplacement(*joueurTour, *joueurEnnemi, xSelection, ySelection, idTour, tailleGrille);
      dessinerGrille(tailleGrille, *joueurTour, *joueurEnnemi);
    }
    else if (change=='1'){
      attaque(joueurTour, joueurEnnemi, xSelection, ySelection, tailleGrille);
    }
  }

  // Verifie si la créature respecte sa zone de tir

  else if(abs(*xSelection-x)+abs(*ySelection-y)>joueurTour->unites[idTour].zoneDeTir){
      cout <<  "\033[37m" << "La créature ne peut pas attaquer à cet endroit (zone de tir insuffisante)." << endl;
      cout <<  joueurTour->couleur << "Voulez-vous déplacer cette créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), selectionner une autre creature ennemie à attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou alors ne rien faire (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ?" << endl << endl;
      cin >> choix;

      while(choix!='0' && choix!='1' && choix!='2'){
        messageErreur(13);
        cout <<  joueurTour->couleur << "Voulez-vous déplacer cette créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), selectionner une autre creature ennemie à attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou alors ne rien faire (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ?" << endl << endl;
        cin >> choix;
      }

      if(choix=='0'){
        deplacement(*joueurTour, *joueurEnnemi, xSelection, ySelection, idTour, tailleGrille);
        dessinerGrille(tailleGrille, *joueurTour, *joueurEnnemi);
      }
      else if (choix=='1'){
        attaque(joueurTour, joueurEnnemi, xSelection, ySelection, tailleGrille);
      }
    }

    // Tout est ok : COMBAT

  else{

    // Récupère l'identifiant de la créature ennemie

    for(int i = 0; i < joueurTour->nbUnitesInitial ; i++){
      if (joueurEnnemi->unites[i].coordUnite[0]==x && joueurEnnemi->unites[i].coordUnite[1]==y){
        idEnnemi = i;
      }
    }

    char fight;
    cout << endl << "\033[37m" << "Etes-vous pret a combattre ? C'est parti !" << endl;
    cout << "\033[32m" << "Tapez 0" << joueurTour->couleur <<" pour lancez l'attaque !" << endl;
    cin >> fight;

    while(fight!='0'){
      messageErreur(13);
      cout  << joueurTour->couleur <<"Lâche ! Vous avez peur du combat ?"<< "\033[32m" << "Tapez 0" << joueurTour->couleur <<" pour lancez l'attaque !" << endl;
      cin >> fight;
    }

    // Fait perdre les points de vie aux créatures concernees en fonction de leurs caracteristiques

    if (fight == '0'){
      joueurEnnemi->unites[idEnnemi].vie -= (joueurTour->unites[idTour].force*(1 - joueurEnnemi->unites[idEnnemi].defense))*100;
      joueurTour->unites[idTour].vie -= (joueurEnnemi->unites[idEnnemi].force*(1 - joueurTour->unites[idTour].defense))*100;

      // Si une unite ennemie est tuee :

      if (joueurEnnemi->unites[idEnnemi].vie<=0){
        joueurEnnemi->unites[idEnnemi].vie=0; // Bloque le nombre de points de vie à zéro
        joueurEnnemi->nbUnitesJoueur-=1; // Baisse le compteur du nombre d'unités
        joueurEnnemi->unites[idEnnemi].coordUnite[0]=0;
        joueurEnnemi->unites[idEnnemi].coordUnite[1]=0;
        cout << joueurTour->couleur << "BRAVO "<<joueurTour->pseudo<< " vous avez aneanti la créature ennemie !"<<endl;
      }

      // Si une unite du joueur est tuee :

      if (joueurTour->unites[idTour].vie<=0){
        joueurTour->unites[idTour].vie=0; // Bloque le nombre de points de vie à zéro sinon renvoie des négatifs
        joueurTour->nbUnitesJoueur-=1; // Baisse le compteur du nombre d'unités
        joueurTour->unites[idTour].coordUnite[0]=0;
        joueurTour->unites[idTour].coordUnite[1]=0;
        cout << joueurTour->couleur << "Mince alors ! "<<joueurTour->pseudo<< " vous avez perdu votre créature durant le combat !"<<endl;
      }
    }

    if(joueurTour->nbUnitesJoueur !=0 || joueurEnnemi->nbUnitesJoueur !=0){
      cout << endl << "Voici les créatures qui sont sorties vivantes du combat :"<<endl<<endl;
      etatUnites(*joueurTour,idTour);
      etatUnites(*joueurEnnemi,idEnnemi);
    }
  }


} // fin attaque()*/
