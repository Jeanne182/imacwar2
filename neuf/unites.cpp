/*
Fanny Joseph
Jeanne Lebigre

IMAC 1 - Projet Prog&Algo S1
*/

#include <iostream>
#include "unites.h"
#include "grille.h"
#include <stdlib.h>
#include <cstring>
using namespace std;

//---------------------- Fonctions concernant le jeu en lui-meme et la gestion des créatures ----------------------//



// Fonction affichant les regles du jeu

int reglesJeu(){

  ligne(13);
  cout << endl<<endl<< "\033[32m" << "Vous vous trouvez maintenant en Terre du Milieu." << endl;
  cout << "Hobbits, nains, orques ou en encore Nazguls, mettez dans votre camp les créatures qui vous permettront de décimer l’équipe adverse." <<endl;
  cout << "Quel est le but de la partie ? Anéantir le camp ennemi." << endl;
  cout << endl <<"\033[32m" << "Tapez 0 " << "\033[37m" << "pour continuer de lire, ou " << "\033[32m" << "tapez 1" << "\033[37m"<< " pour passer à la présentation des niveaux de jeu ? " << endl;
  char choix1;
  cin >> choix1;

  while (choix1!='0' && choix1!='1'){
    messageErreur(13);
    cout << endl <<"\033[32m" << "Tapez 0 " << "\033[37m" << "pour continuer de lire, ou " << "\033[32m" << "tapez 1" << "\033[37m"<< " pour passer à la présentation des niveaux de jeu ? " << endl;
    cin >> choix1;
  }

  if (choix1=='0'){

    ligne(13);
    cout << endl<< "\033[32m" <<"Vous et votre adversaire devrez dans un premier temps acheter et placer les créatures que vous souhaitez dans votre camp." << endl;
    cout << "Chacune d’entre elles dispose de caractéristiques différentes." <<endl;
    cout << "Attention, votre bourse dispose d’une quantité limitée de pièces d’or !" << endl << endl;
    cout << "Puis, la bataille peut commencer." << endl;
    cout << "A chaque tour de jeu, vous pourrez faire agir chacune de vos créatures, une seule fois." << endl;
    cout << "Vous aurez alors le choix de la faire se déplacer sur le champ de guerre (représenté par une grille) ou bien d’attaquer, s’il lui est possible, une créature du camp ennemi. " <<endl;
    cout << endl <<"\033[32m" << "Tapez 0 " << "\033[37m" << "pour continuer de lire, ou " << "\033[32m" << "tapez 1" << "\033[37m"<< " pour passer à la présentation des niveaux de jeu ? " << endl;
    char choix2;
    cin >> choix2;

    while(choix2!='0' && choix2!='1'){
      messageErreur(13);
      cout << endl <<"\033[32m" << "Tapez 0 " << "\033[37m" << "pour continuer de lire, ou " << "\033[32m" << "tapez 1" << "\033[37m"<< " pour passer à la présentation des niveaux de jeu ? " << endl;
      cin >> choix2;
    }

    if(choix2=='0'){

      ligne(13);
      cout << endl<< "\033[32m" <<"Pour se déplacer ou attaquer, rien de plus simple !" << endl;
      cout << "Chaque créature possède une mobilité et une zone d’attaque qui lui est propre." <<endl;
      cout << "Il suffira dans un premier temps de choisir les coordonnées de la créature que vous souhaitez faire agir, puis d’indiquer quelle action elle fera." << endl << endl;
      cout << "Dans le cas d’un déplacement, il suffira d’indiquer de nouvelles coordonnées." << endl;
      cout << "Pour une attaque, il suffira d’indiquer les coordonnées de la créature que vous souhaitez décimer." << endl;
      cout << "Un combat sanguinaire éclatera, qui fera perdre des points de vies aussi bien à la créature ennemie qu’à la vôtre ! " <<endl;
      cout << "Préférez vous jouer les gros bras et infliger beaucoup de dégât, ou jouer sur la défensive et utiliser vos capacités de guérison ? " << endl;
      cout << "A vous de voir ! Que la bataille commence !" << endl;
      cout << endl<<"\033[37m"<<"Passer à la présentation des niveaux de jeu (" << "\033[32m" << "0" << "\033[37m" << ") ou Quitter (" << "\033[32m" << "1" << "\033[37m" << ") ?" << endl;
      char choix3;
      cin >> choix3;

      while(choix3!='0' && choix3!='1'){
        messageErreur(13);
        cout << endl<<"\033[37m"<<"Passer à la présentation des niveaux de jeu (" << "\033[32m" << "0" << "\033[37m" << ") ou Quitter (" << "\033[32m" << "1" << "\033[37m" << ") ?" << endl;
        cin >> choix3;
      }
      if(choix3=='0'){return 1;}
      else if (choix3=='1'){exit(1);}

    }
    else if (choix2=='1'){return 1;}
  }
  else if (choix1=='1'){return 1;}

  return 0;

} // fin reglesJeu()

//------------------------------------------------------------------------------------------------------------//

// Fonction presentant les differents niveaux du jeu et fait choisir aux joueurs le niveau avec lequel ils souhaient jouer

int reglesNiveaux(){
  ligne(13);
  cout << endl << endl << "\033[32m" << "ImacWar peut se jouer avec trois niveaux différents." << endl << endl;

  cout << "\033[32m" << "Niveau 1 :" <<endl;
  cout << "\033[37m" << "Vous disposez de 60 pièces d'or pour acheter vos créatures." << endl;
  cout << "La carte est une grille de 6 par 6." << endl;
  cout << "Au début de la partie, vous ne pouvez placer vos créatures que sur les 2 premières et dernières colonnes de la grille." << endl << endl;

  cout << "\033[32m" << "Niveau 2 :" <<endl;
  cout << "\033[37m" << "Vous disposez de 150 pièces d'or pour acheter vos créatures." << endl;
  cout << "La carte est une grille de 10 par 10." << endl;
  cout << "Au debut de la partie, vous ne pouvez placer vos créatures que sur les 4 premières et dernières colonnes de la grille." << endl << endl;

  cout << "\033[32m" << "Niveau 3 :" <<endl;
  cout << "\033[37m" << "Vous disposez de 200 pièces d'or pour acheter vos créatures." << endl;
  cout << "La carte est une grille de 14 par 14." << endl;
  cout << "Au debut de la partie, vous ne pouvez placer vos créatures que sur les 6 premières et dernières colonnes de la grille." << endl<< endl;

  cout << "\033[32m" << "A quel niveau de difficulté souhaitez-vous jouer ? Tapez 1, 2 ou 3." << endl;
  char niv;
  cin >> niv;
  cout << endl << endl;

  while(niv!='1' && niv!='2' && niv!='3'){
    messageErreur(13);
    cout << endl << "\033[32m" << "A quel niveau de difficulté souhaitez-vous jouer ? Tapez 1, 2 ou 3." << endl;
    cin >> niv;
    cout << endl << endl;
  }
  if (niv=='1'){
    return 1;
  }
  else if (niv=='2'){
    return 2;
  }
  else if (niv=='3'){
    return 3;
  }

  return 0;

} // fin reglesNiveaux()

//------------------------------------------------------------------------------------------------------------//

// Fonction corps du jeu :

int jeuPartie(int niveau, int tailleGrille){

    // Création des joueurs

    Joueur joueur1, joueur2;
    creationJoueurs(&joueur1, &joueur2, niveau);

    // Boucle de tour de jeu pour les deux joueurs, tant qu'ils ont au moins une unite

    while(joueur1.nbUnitesJoueur > 0 && joueur2.nbUnitesJoueur > 0){

     // Joueur 1 qui joue :
     gestionUnitesEnUnTour(&joueur1, &joueur2, tailleGrille);

     // Joueur 2 qui joue :
     gestionUnitesEnUnTour(&joueur2, &joueur1, tailleGrille);

   }

   // Fin de la partie : affichage du gagnant


   if(joueur1.nbUnitesJoueur==0 && joueur2.nbUnitesJoueur==0){
     dessinerGrille(tailleGrille, joueur1, joueur2);
     cout << "\033[37m" << "Fin de partie. Toutes les creatures ont été anéanties ! "<< endl;
     cout <<"Personne n'est le grand gagnant de IMACWAR !" << endl << endl;
     return 1;
   }

   else if(joueur1.nbUnitesJoueur==0){
     dessinerGrille(tailleGrille, joueur1, joueur2);
     cout << joueur2.couleur << joueur2.pseudo << " vos créatures ont pour coordonnées : "<< endl<<endl;
    for (int id=0; id<joueur2.nbUnitesInitial; id++){
      if (joueur2.unites[id].vie > 0){
      etatUnites(joueur2,id);
     }
   }
     cout << "\033[37m" << "Fin de partie. " << joueur2.pseudo << " a gagné !" << endl;
     cout << joueur2.couleur << "Bravo " << joueur2.pseudo << " vous êtes le grand gagnant de IMACWAR !" << endl << endl;
     return 1;
   }
   else if(joueur2.nbUnitesJoueur==0){
     dessinerGrille(tailleGrille, joueur1, joueur2);
     cout << joueur1.couleur << joueur1.pseudo << " vos créatures ont pour coordonnees : "<< endl<<endl;
     for (int id=0; id<joueur1.nbUnitesInitial; id++){
       if (joueur1.unites[id].vie > 0){
       etatUnites(joueur1,id);
      }
    }
     cout << "\033[37m" << "Fin de partie. " << joueur1.pseudo << " a gagné !" << endl;
     cout << joueur1.couleur << "Bravo " << joueur1.pseudo << " vous êtes le grand gagnant de IMACWAR !" << endl << endl;
     return 1;
   }

   return 0;


} // fin jeuPartie()

//------------------------------------------------------------------------------------------------------------//

//Fonction qui permet de gérer toutes les unités d'un joueur en un seul tour

void gestionUnitesEnUnTour(Joueur* joueurTour, Joueur* joueurEnnemi, int tailleGrille){

  int tabID[nombreUnitesMAX];

  for (int i=0; i<nombreUnitesMAX; i++){
    tabID[i] = nombreUnitesMAX + 1;
  }


  if (joueurTour->nbUnitesJoueur>0 && joueurEnnemi->nbUnitesJoueur> 0){
    cout << endl << joueurTour->couleur << "C'est a "<< joueurTour->pseudo << " de jouer."<<endl<<endl;

      for (int i=0 ; i < joueurTour->nbUnitesJoueur ; i ++){

        cout << joueurTour->couleur << joueurTour->pseudo << " souhaitez-vous voir l'état de toutes les créatures (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), faire agir dès maintenant une de vos créatures (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou arreter votre tour maintenant (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ? " << endl;
        char choix1;
        cin >> choix1;

        while(choix1!='0' && choix1!='1' && choix1!='2'){
          messageErreur(13);
          cout << joueurTour->couleur << joueurTour->pseudo << " souhaitez-vous : voir l'état de toutes les créatures (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), faire agir dès maintenant une de vos créatures (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou arreter votre tour maintenant (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ? " << endl;
          cin >> choix1;
        }

        if(choix1=='0'){
          cout << joueurTour->couleur << joueurTour->pseudo << " vos créatures ont pour coordonnees : "<< endl<<endl;
          for (int id=0; id<joueurTour->nbUnitesInitial; id++){
            if (joueurTour->unites[id].vie > 0){
            etatUnites(*joueurTour,id);
           }
          }
          cout << joueurEnnemi->couleur << joueurEnnemi->pseudo << " vos créatures ont pour coordonnees : "<< endl<<endl;
         for (int id=0; id<joueurEnnemi->nbUnitesInitial; id++){
           if (joueurEnnemi->unites[id].vie > 0){
           etatUnites(*joueurEnnemi,id);
          }
         }
         selectionUnite(joueurTour, joueurEnnemi, tabID, tailleGrille);
        }

        else if (choix1=='1'){
          if(joueurTour->nbUnitesJoueur > 0 && joueurEnnemi->nbUnitesJoueur > 0){
            cout << "\033[37m";
            selectionUnite(joueurTour, joueurEnnemi, tabID, tailleGrille);
          }
        }

       else if (choix1=='2'){
          for (int j=0; j < joueurTour->nbUnitesInitial ; j++){
            if (j == tabID[j]){
              j +=1;
            }

            else{
              tabID[j]=j;
            }
          }
         i=joueurTour->nbUnitesJoueur;
      }
    }

  }
}// fin gestionUnitesEnUnTour

//------------------------------------------------------------------------------------------------------------//

// Fonction attribuant aux joueurs et a la grille leurs differents parametres
// Elle demande ensuite aux joueurs d'acheter puis de placer leurs unites

void creationJoueurs(Joueur *joueur1, Joueur *joueur2, int niveauPartie){

  // Attribution des parametres en fonction du niveau choisi

  int tailleGrille, zonePlacement;
  int fonds;

  if (niveauPartie==1){
    tailleGrille = 6;
    fonds = 60;
    zonePlacement=2;
  }
  else if (niveauPartie==2){
    tailleGrille = 10;
    fonds=150;
    zonePlacement=4;
  }
  else {
    tailleGrille = 14;
    fonds=200;
    zonePlacement=6;
  }

  // Définition des caractéristiques des joueurs

  strcpy(joueur1->couleur,"\033[36m");
  strcpy(joueur2->couleur,"\033[35m");

  cout << joueur1->couleur << "Entrez un pseudo pour le premier joueur." << endl;
  cin >> joueur1->pseudo;
  cout << endl <<joueur2->couleur << "Entrez un pseudo pour le second joueur."<< endl;
  cin >> joueur2->pseudo;

  cout << "\033[37m";

  joueur1->idJoueur=1;
  joueur2->idJoueur=2;

  joueur1->nbUnitesJoueur = 0;
  joueur2->nbUnitesJoueur = 0;
  joueur1->nbUnitesInitial = 0;
  joueur2->nbUnitesInitial = 0;

  joueur1->pieces = fonds;
  joueur2->pieces = fonds;


  // Achat et placement des créatures sur la carte

  dessinerGrille(tailleGrille, *joueur1, *joueur2);
  cout << endl<< "Chaque joueur dispose initialement de "<< fonds <<" pièces d'or. "<< endl << endl;

  Unite unite;
  int id =0;

  // Remplissage du tableau des créatures du joueur 1

  cout << joueur1->couleur << joueur1->pseudo << " c'est vous qui commencez à placer vos créatures sur la carte." << endl <<endl;

  while(joueur1->pieces > 0){
    cout << "\033[37m" << joueur1->pseudo << " vous disposez de "<<joueur1->pieces<< " pièces d'or."<<endl;
    typeUnites(*joueur1, &unite);
    while (unite.prix>joueur1->pieces){
      cout << "\033[37m" << "Vous n'avez pas assez d'argent pour acheter cette créature. Veuillez acheter une autre créature."<<endl;
      typeUnites(*joueur1, &unite);
    }

    unite.idUnite = id;
    joueur1->pieces -= unite.prix;
    int coordonneesJoueur1[MAX];

    cout << endl << joueur1->couleur << joueur1->pseudo << " rentrez les coordonnees de cette créature. "<< endl << endl<< "x = ";
    cin >> coordonneesJoueur1[0];
    cout << "y = ";
    cin >> coordonneesJoueur1[1];

    while(verificationZone(*joueur1, coordonneesJoueur1[0], coordonneesJoueur1[1], tailleGrille, zonePlacement)==0){
      cout <<endl <<  "x = ";
      cin >> coordonneesJoueur1[0];
      cout << "y = ";
      cin >> coordonneesJoueur1[1] ;
    }
    if(joueur1->nbUnitesJoueur != 0){

    while(verificationCaseLibre(*joueur1, *joueur2, coordonneesJoueur1[0], coordonneesJoueur1[1])==0){
      cout << endl << "x = ";
      cin >> coordonneesJoueur1[0];
      cout << "y = ";
      cin >> coordonneesJoueur1[1] ;
    }
  }
    joueur1->unites[id]= unite;
    joueur1->unites[id].coordUnite[0] = coordonneesJoueur1[0];
    joueur1->unites[id].coordUnite[1] = coordonneesJoueur1[1];
    joueur1->nbUnitesJoueur += 1;
    joueur1->nbUnitesInitial +=1 ;
    cout << "\033[37m";
    dessinerGrille(tailleGrille, *joueur1, *joueur2);
    id ++;

  }
  id =0;

  // Remplissage du tableau des créatures du joueur 2

  cout << joueur2->couleur << joueur2->pseudo << " c'est maintenant à vous de placer vos créatures sur la carte." << endl <<endl;

  while(joueur2->pieces > 0){
    cout << "\033[37m" << joueur2->pseudo << " vous disposez de "<<joueur2->pieces<< " pièces d'or."<<endl;
    typeUnites(*joueur2, &unite);
    while (unite.prix>joueur2->pieces){
      cout << "\033[37m" << "Vous n'avez pas assez d'argent pour acheter cette créature. Veuillez acheter une autre créature."<<endl;
      typeUnites(*joueur2, &unite);
    }

    unite.idUnite = id;
    joueur2->pieces -= unite.prix;

    int coordonneesJoueur2[MAX];

    cout << endl << joueur2->couleur << joueur2->pseudo << " rentrez les coordonnees de cette créature. "<< endl << endl << "x = ";
    cin >> coordonneesJoueur2[0];
    cout << "y = ";
    cin >> coordonneesJoueur2[1];

    while(verificationZone(*joueur2, coordonneesJoueur2[0], coordonneesJoueur2[1], tailleGrille, zonePlacement)==0){
      cout <<endl<< "x = ";
      cin >> coordonneesJoueur2[0];
      cout << "y = ";
      cin >> coordonneesJoueur2[1] ;
    }
    if(joueur2->nbUnitesJoueur != 0){

    while(verificationCaseLibre(*joueur2, *joueur1, coordonneesJoueur2[0], coordonneesJoueur2[1])==0){
      cout <<endl<< "x = ";
      cin >> coordonneesJoueur2[0];
      cout << "y = ";
      cin >> coordonneesJoueur2[1] ;
    }
  }
    joueur2->unites[id]= unite;
    joueur2->unites[id].coordUnite[0] = coordonneesJoueur2[0];
    joueur2->unites[id].coordUnite[1] = coordonneesJoueur2[1];
    joueur2->nbUnitesJoueur += 1;
    joueur2->nbUnitesInitial +=1;
    cout << "\033[37m";
    dessinerGrille(tailleGrille, *joueur1, *joueur2);
    id++;

  }

  // Fin du placement de toutes les créatures sur la carte. Etat du jeu avant la partie :

  ligne(13);
  cout << endl << endl << " Fin du placement de toutes les créatures. LE JEU PEUT COMMENCER ! " << endl << endl ;
  ligne(13);

} // fin creationJoueurs()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui tous les tours fait selectionner au joueur une unite

void selectionUnite(Joueur *joueurTour, Joueur *joueurEnnemi, int tabID[nombreUnitesMAX], int tailleGrille){

    cout << joueurTour->couleur << joueurTour->pseudo << " sélectionnez une de vos créatures en rentrant ses coordonnees : " << endl;
    int x, y;
    cout << "x = ";
    cin >> x;
    cout << "y = ";
    cin >> y;


    int indiceUnite;
    int bonneCase = 0;

    for(int compteur = 0; compteur < joueurTour->nbUnitesInitial ; compteur++){
      if (joueurTour->unites[compteur].coordUnite[0]==x && joueurTour->unites[compteur].coordUnite[1]==y){
          indiceUnite = compteur;
          bonneCase = 1;
      }
    }

    // Verifie qu'il s'agit bien d'une unite du joueur concerné

    if(bonneCase == 0){
      cout << "\033[37m" << "Vous n'avez pas sélectionné une de vos créatures."<<endl;
      selectionUnite(joueurTour, joueurEnnemi, tabID, tailleGrille);
    }

    // Verifie si La créature n'a pas deja ete jouee pendant ce tour, si ok le joueur choisi de la deplacer ou de lui faire attaquer

    else if (bonneCase==1){
      if (indiceUnite == tabID[indiceUnite]){
        cout << "\033[37m" << "Vous avez déjà agit avec cette créature durant ce tour. Veuillez recommencer avec une autre créature." << endl;
        selectionUnite(joueurTour, joueurEnnemi, tabID, tailleGrille);
      }

      else{
        tabID[indiceUnite]=indiceUnite;

        // Choix de se déplacer ou d'attaquer

        cout << joueurTour->couleur << endl << "Désirez-vous déplacer cette créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou ne rien faire avec ? (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ? "<< endl ;
        char choix;
        cin >> choix;

        while(choix!='0' && choix!='1' && choix!='2'){
          messageErreur(13);
          cout << joueurTour->couleur << endl << "Désirez-vous déplacer cette créature (" << "\033[32m" << "tapez 0" << joueurTour->couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour->couleur << ") ou ne rien faire avec ? (" << "\033[32m" << "tapez 2" << joueurTour->couleur << ") ? "<< endl ;
          cin >> choix;
        }

        if (choix == '0'){
          deplacement(*joueurTour, *joueurEnnemi, &joueurTour->unites[indiceUnite].coordUnite[0], &joueurTour->unites[indiceUnite].coordUnite[1], indiceUnite, tailleGrille);
          dessinerGrille(tailleGrille, *joueurTour, *joueurEnnemi);
        }

        else if (choix == '1'){
          attaque(joueurTour, joueurEnnemi, &joueurTour->unites[indiceUnite].coordUnite[0], &joueurTour->unites[indiceUnite].coordUnite[1], tailleGrille);
          dessinerGrille(tailleGrille, *joueurTour, *joueurEnnemi);
        }

      }
    }


} // fin selectionUnite()

//------------------------------------------------------------------------------------------------------------//

// Fonction attribuant aux differents types d'créatures leurs caracteristiques
// Elle permet aussi aux joueurs de pouvoir choisir quelles créatures ils souhaient acheter

void typeUnites(Joueur joueur, Unite *uniteJoueur){

  char typeUnite[][MAX]={"Nain", "Orque", "Hobbit", "Elfe", "Nazgul", "Smeagol"};
  int nbTypes = 6;
  Unite nain, orque, hobbit, elfe, nazgul, smeagol;

  char descriptionUnite[][300] = {
  "Petit mais puissant ! Le nain possède une puissance et une défense de 50%. \nSes petites jambes lui permettent de se déplacer de deux cases, et ses coups de hache peuvent attaquer à une case de distance. \nPRIX : 30 pieces.",
  "Ce guerrier redoutable est utile pour le corps à corps. Il possède une puissance de 60% et une defense de 30%. \nIl peut se deplacer de 2 cases et tirer d'une case. \nPRIX : 20 pieces.",
  "Cette créature aux pieds poilus possède une puissance et une défense de 40%. \nHabitué à traverser toute la Terre du Milieu, il peut se deplacer de 4 cases, et sa distance de tir est de 2 cases. \nPRIX : 20 pieces.",
  "Etre presque immortel, il possède une puissance de 30% mais sa défense est de 60% grâce à son pouvoir de guérison. \nIl se déplace de 2 cases mais ses flèches ont une portée de tir de 4 cases. \nPRIX : 30 pieces.",
  "Ce spectre de l'anneau doit sa force à sa malédiction. Il possède une puissance de 70% et une défense de 50%. \nIl peut se déplacer de 2 cases et donne des coup d'épée à une case de distance. \nPRIX : 50 pieces.",
  "Cet être tout rabougri possède une puissance et une défense de 30%. \nSa fourberie lui permet de se déplacer de 6 cases et il peut tirer jusqu'à une distance de 2 cases grâce à son lance-pierre. \nPRIX : 10 pieces."
  };

  nain.type = 0;
  nain.force = 0.5;
  nain.defense = 0.5;
  nain.distance = 2;
  nain.zoneDeTir = 1;
  nain.prix = 30;

  orque.type = 1;
  orque.force = 0.6;
  orque.defense = 0.3;
  orque.distance = 2;
  orque.zoneDeTir = 1;
  orque.prix = 20;

  hobbit.type = 2;
  hobbit.force = 0.4;
  hobbit.defense = 0.4;
  hobbit.distance = 4;
  hobbit.zoneDeTir = 2;
  hobbit.prix = 20;

  elfe.type = 3;
  elfe.force = 0.3;
  elfe.defense = 0.6;
  elfe.distance = 2;
  elfe.zoneDeTir = 4;
  elfe.prix = 30;

  nazgul.type = 4;
  nazgul.force = 0.7;
  nazgul.defense = 0.5;
  nazgul.distance = 2;
  nazgul.zoneDeTir = 1;
  nazgul.prix =  50;

  smeagol.type = 5;
  smeagol.force = 0.3;
  smeagol.defense = 0.3;
  smeagol.distance = 6;
  smeagol.zoneDeTir = 2;
  smeagol.prix = 10;

  char choix, creature;
  cout << joueur.couleur << "Souhaitez-vous avoir le descriptif des créatures (" << "\033[32m" << "tapez 0" << joueur.couleur << ") ou passer directement a la suite (" << "\033[32m" << "tapez 1" << joueur.couleur << ") ?" <<endl;
  cin >> choix;

  while(choix!='0' && choix!='1'){
    messageErreur(13);
    cout << endl << joueur.couleur << joueur.pseudo << " souhaitez-vous avoir le descriptif des créatures (" << "\033[32m" << "tapez 0" << joueur.couleur << ") ou passer directement a la suite (" << "\033[32m" << "tapez 1" << joueur.couleur << ") ?" <<endl;
    cin >> choix;
  }

  // Affiche le descriptif des créatures pour aider le joueur a choisir

  if (choix == '0'){
    for (int i = 0; i < nbTypes; i++){
      cout << endl;
      cout << "\033[32m" << typeUnite[i] << " :" << endl << "\033[37m" << descriptionUnite[i]<< endl << endl;
    }
  }


  ligne(13);
  cout << endl << joueur.couleur << "Choisissez la créature que vous souhaitez placer : " << endl << endl;
  cout << "\033[37m" << typeUnite[0] << " (" << "\033[32m"<< "tapez n" <<"\033[37m" << ") " ;
  cout << typeUnite[1] << " (" << "\033[32m"<< "tapez O" <<"\033[37m" << ") " ;
  cout << typeUnite[2] << " (" << "\033[32m"<< "tapez H" <<"\033[37m" << ") " ;
  cout << typeUnite[3] << " (" << "\033[32m"<< "tapez E" <<"\033[37m" << ") " ;
  cout << typeUnite[4] << " (" << "\033[32m"<< "tapez N" <<"\033[37m" << ") " ;
  cout << typeUnite[5] << " (" << "\033[32m"<< "tapez S" <<"\033[37m" << ") " ;
  cout<<endl;
  cin >> creature;
  while(creature != 'n' && creature != 'O' && creature != 'H' && creature != 'E' && creature != 'N' && creature != 'S'){
    messageErreur(13);
    cout << endl << joueur.couleur << "Choisissez la créature que vous souhaitez placer : " << endl << endl;
    cout << "\033[37m" << typeUnite[0] << " (" << "\033[32m"<< "tapez n" <<"\033[37m" << ") " ;
    cout << typeUnite[1] << " (" << "\033[32m"<< "tapez O" <<"\033[37m" << ") " ;
    cout << typeUnite[2] << " (" << "\033[32m"<< "tapez H" <<"\033[37m" << ") " ;
    cout << typeUnite[3] << " (" << "\033[32m"<< "tapez E" <<"\033[37m" << ") " ;
    cout << typeUnite[4] << " (" << "\033[32m"<< "tapez N" <<"\033[37m" << ") " ;
    cout << typeUnite[5] << " (" << "\033[32m"<< "tapez S" <<"\033[37m" << ") " ;
    cout<<endl;
    cin >> creature;
  }
  if(creature=='n'){*uniteJoueur = nain;}
  else if(creature=='O'){*uniteJoueur = orque;}
  else if(creature=='H'){*uniteJoueur = hobbit;}
  else if(creature=='E'){*uniteJoueur = elfe;}
  else if(creature=='N'){*uniteJoueur = nazgul;}
  else if(creature=='S'){*uniteJoueur = smeagol;}


  // Initialisation des points de vie des créatures à 100

  uniteJoueur->vie = vieU;

} // fin typeUnites()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui, lors du placement des créatures en debut de partie, verifie que le joueur place bien ses créatures dans la zone qui lui est reservee

int verificationZone(Joueur joueurTour, int x,int y, int tailleGrille, int zonePlacement){

  if (joueurTour.idJoueur==1){
    if (x>zonePlacement || x<1 || y > tailleGrille || y <1){
      cout << endl << "\033[37m" << "Vous etes hors de la zone de placement. Rappel : vous disposez des " << zonePlacement << " premières colonnes pour placer vos créatures." << endl;
      cout << joueurTour.couleur << "Veuillez rentrer de nouvelles coordonnees." << endl;
      return 0;
    }
  }

  else if (joueurTour.idJoueur==2){
    if (x<= tailleGrille-zonePlacement || x>tailleGrille || y > tailleGrille || y <1){
      cout <<endl << "\033[37m" << "Vous etes hors de la zone de placement. Rappel : vous disposez des " << zonePlacement << " dernières colonnes pour placer vos créatures" << endl;
      cout << joueurTour.couleur << "Veuillez rentrer de nouvelles coordonnees." << endl;
      return 0;
    }
  }

  return 1;
} // fin verificationZone()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui verifie que la case est libre pour qu'un joueur puisse y mettre une unite, autrement dit que les coordonees ne sont pas deja utilisees

int verificationCaseLibre(Joueur joueurTour, Joueur joueurEnnemi, int x,int y){

  for(int i=0; i<joueurTour.nbUnitesInitial; i++){
    if (x==joueurTour.unites[i].coordUnite[0] && y==joueurTour.unites[i].coordUnite[1]){
        cout << endl <<"\033[37m" << "Ces coordonnees sont deja utilisees par une de vos créatures." << endl ;
        return 0;
    }
  }

  for(int i=0; i<joueurEnnemi.nbUnitesInitial; i++){
    if (x==joueurEnnemi.unites[i].coordUnite[0] && y==joueurEnnemi.unites[i].coordUnite[1]){
        cout << endl <<"\033[37m" << "Ces coordonnees sont deja utilisees par une créature ennemie." << endl ;
        return 0;
    }
  }
  return 1;

} // fin verificationCaseLibre()

//------------------------------------------------------------------------------------------------------------//


// Fonction qui permet de deplacer une unite

void deplacement(Joueur joueurTour, Joueur joueurEnnemi, int *xInitial, int *yInitial, int idUnite, int tailleGrille){

  cout << joueurTour.couleur << joueurTour.pseudo << " entrez les nouvelles coordonnees de votre créature : " << endl;
  int coordonneesJoueur[MAX];


  cout << "x = ";
  cin >> coordonneesJoueur[0];
  cout << "y = ";
  cin >> coordonneesJoueur[1];

  // Vérifie que la case est libre

  if(verificationCaseLibre(joueurTour, joueurEnnemi, coordonneesJoueur[0] , coordonneesJoueur[1])==0){
    cout << joueurTour.couleur << "Voulez-vous déplacer cette créature à un autre endroit (" << "\033[32m" << "tapez 0" << joueurTour.couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour.couleur << ") ou ne rien faire avec elle (" << "\033[32m" << "tapez 2" << joueurTour.couleur << ") ?"<<endl;

    char choix;
    cin >> choix;
    while (choix != '0' && choix != '1' && choix !='2'){
      cout << joueurTour.couleur << "Voulez-vous déplacer cette créature à un autre endroit (" << "\033[32m" << "tapez 0" << joueurTour.couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour.couleur << ") ou ne rien faire avec elle (" << "\033[32m" << "tapez 2" << joueurTour.couleur << ") ?"<<endl;
      messageErreur(13);
      cin >> choix;
    }

    if (choix=='1'){
      attaque(&joueurTour, &joueurEnnemi, xInitial, yInitial, tailleGrille);

    }

    else {
      deplacement(joueurTour, joueurEnnemi, xInitial, yInitial, idUnite, tailleGrille);
    }

  }

  //Vérifie que La créature a le droit de se déplacer à cet endroit là en fonction de ses caractéristiques

  else if(abs(coordonneesJoueur[0]-*xInitial)+abs(coordonneesJoueur[1]-*yInitial)>joueurTour.unites[idUnite].distance || coordonneesJoueur[0] <1 || coordonneesJoueur[1] <1 || coordonneesJoueur[0]> tailleGrille || coordonneesJoueur[1]>tailleGrille){
      cout << "\033[37m" << "La créature ne peut pas se déplacer a cet endroit" << endl;
      cout << joueurTour.couleur << "Voulez-vous déplacer cette créature à un autre endroit (" << "\033[32m" << "tapez 0" << joueurTour.couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour.couleur << ") ou ne rien faire avec elle (" << "\033[32m" << "tapez 2" << joueurTour.couleur << ") ?"<<endl;

    char choix2;
    cin >> choix2;
    while (choix2 != '0' && choix2 != '1' && choix2 !='2'){
      cout << joueurTour.couleur << "Voulez-vous déplacer cette créature à un autre endroit (" << "\033[32m" << "tapez 0" << joueurTour.couleur << "), la faire attaquer (" << "\033[32m" << "tapez 1" << joueurTour.couleur << ") ou ne rien faire avec elle (" << "\033[32m" << "tapez 2" << joueurTour.couleur << ") ?"<<endl;
      messageErreur(13);
      cin >> choix2;
    }

    if (choix2=='1'){
      attaque(&joueurTour, &joueurEnnemi, xInitial, yInitial, tailleGrille);

    }

    else {
      deplacement(joueurTour, joueurEnnemi, xInitial, yInitial, idUnite, tailleGrille);
    }

  }


  else{
      *xInitial = coordonneesJoueur[0];
      *yInitial = coordonneesJoueur[1];
    }

} // fin deplacement()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui permet a La créature d'attaquer

void attaque(Joueur *joueurTour, Joueur *joueurEnnemi, int *xSelection, int *ySelection, int tailleGrille){

  int idTour, idEnnemi;
  int x, y;
  char choix;

  // Récupère l'identifiant de la créature sélectionnée

  for(int i = 0; i < joueurTour->nbUnitesInitial ; i++){
    if (joueurTour->unites[i].coordUnite[0]==*xSelection && joueurTour->unites[i].coordUnite[1]==*ySelection){ //changer x et y récupérer fonction selection
      idTour = i;
    }
  }

  cout << endl << joueurTour->couleur << joueurTour->pseudo << " selectionnez une créature ennemie." << endl;
  cout << "x = ";
  cin >> x;
  cout << "y = ";
  cin >> y;

  // Verifie que la créature selectionnee est bien une unite ennemie

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


} // fin attaque()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui verifie que La créature selectionnee est bien une unite ennemie

int verifUniteEnnemie(Joueur joueurTour, Joueur joueurEnnemi, int xEnnemi, int yEnnemi){
  for(int compteur = 0; compteur < joueurEnnemi.nbUnitesInitial ; compteur++){
    if (joueurEnnemi.unites[compteur].coordUnite[0]==xEnnemi && joueurEnnemi.unites[compteur].coordUnite[1]==yEnnemi){
      return 1;
    }
  }
  cout << "\033[37m" <<  "Ces coordonnees n'appartiennent pas a une créature ennemie." << endl;
  return 0;
} // fin verifUniteEnnemie()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui donne l'etat des unites

void etatUnites(Joueur joueur, int idUnite){

  // Affichage du type et de la position des créatures + leurs differents caracteristiques

  //cout << joueur.couleur << joueur.pseudo << " vos créatures ont pour coordonnees : "<< endl<<endl;

  if (joueur.nbUnitesJoueur>0){
    //for (int i = 0; i < joueur.nbUnitesInitial ; i++){
      if (joueur.unites[idUnite].vie > 0){

          for (int j=0 ; j < 6 ; j++){
            if (joueur.unites[idUnite].type == j){
              char typeUnite[][MAX]={"Nain", "Orque", "Hobbit", "Elfe", "Nazgul", "Smeagol"};
              for(int l=0 ; l < 10 ; l++){
                cout << joueur.couleur << typeUnite[j][l] ;
              }
            }
          }
          cout << " en position (" << joueur.unites[idUnite].coordUnite[0] << ";" << joueur.unites[idUnite].coordUnite[1] << ")" << endl;
          cout << "\033[37m";
          cout << "Points de vie : " << joueur.unites[idUnite].vie<<endl;
          cout << "Force : " << joueur.unites[idUnite].force * 100 << "%" <<endl;
          cout << "Défense : " << joueur.unites[idUnite].defense * 100 << "%" <<endl;
          cout << "Possibilité de déplacement :  " << joueur.unites[idUnite].distance << " carreaux" <<endl;
          cout << "Zone de tir : " << joueur.unites[idUnite].zoneDeTir << " carreaux" <<endl<<endl;
      }

  }
  //else if (joueur.nbUnitesJoueur==0){
    //cout << joueur.couleur << joueur.pseudo<<" il semblerait que toutes vos créatures ont été tuées..."<< endl<<endl;
  //}


} // fin etatUnites()

//------------------------------------------------------------------------------------------------------------//

// Fonction qui affiche une erreur si le joueur s'est trompé en tapant un chiffre demandé

void messageErreur(int entier){
  cout <<endl;
  ligne(entier);
  cout<< endl<< "\033[37m"<< "ERREUR : vous n'avez pas tapé un numéro ou une lettre proposé(e). Veuillez recommencer.";
  ligne(entier);
  cout << endl;
} // fin messageErreur()
