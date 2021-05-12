#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"
using namespace std;

class Grille{
  // Attribu
  vector<vector<Place>> tab;
  public:
  // Constructeur
  Grille();
  Grille(int colonie);
  // Méthodes
  int TailleGrille();
  int SubTailleGrille();
  Place chargePlace(Coord c) const;
  void rangePlace(Place p);
  void linearisePheroNid(int ind);
  void diminuePheroSucre();
  //Affichage
  void dessine();
  void affichePheroSucre();
  void affichePheroNid();


};

void placeNid(Grille &g, colonie C);
void placeSucre(Grille &g, EnsCoord e);
void placeFourmis(Grille &g, colonie C);
void lineariserPheroNid(Grille &g,int colonie);
Grille initialiseGrille(colonie C,EnsCoord Sucre,int colo);

//Test Coherence
void Check_Ind_Fourmi(std::vector<Fourmi>F);
void Check_Place_Grille(Grille g);
void Check_Fourmi_Grille(Grille g,std::vector<Fourmi>F);
void Check_Grille_Fourmi(Grille g,std::vector<Fourmi>F);

//1) //A Faire quand on aura codé les colonies
void tue(Fourmi &f, Place &P1, Place &P2);
bool tue_condition(Fourmi f, Place P1, Place P2);

//2)
void prendSucre(Fourmi &f, Place &P1, Place &P2);
bool prendSucre_condition(Fourmi f, Place P1, Place P2);    
    
//3)
void poseSucre(Fourmi &f, Place &P1, Place &P2); //, int &nbSucreNid)
void poseSucre(Fourmi &f, Place &P1, Place &P2,colonie &C);// Avec colonie
bool poseSucre_condition(Fourmi f, Place P1, Place P2);

//4)
void chercheNid(Fourmi &f, Place &P1, Place &P2,int ind);
bool chercheNid_condition(Fourmi f, Place P1, Place P2,int ind);
    
//5)
void chercheSucreSurPiste(Fourmi &f, Place &P1, Place &P2,int ind);
bool chercheSucreSurPiste_condition(Fourmi f, Place P1, Place P2,int ind);
    
//6)    
void cherchePiste(Fourmi &f, Place &P1, Place &P2);
bool cherchePiste_condition(Fourmi f, Place P1, Place P2);    
    
//7)
void chercheSansPiste(Fourmi &f, Place &P1, Place &P2);
bool chercheSansPiste_condition(Fourmi f, Place P1, Place P2);

void mettreAJourFourmiSansColonie(Grille &g,vector<Fourmi> &F);
void mettreAJourFourmiAvecColonie(Grille &g,colonie &C);

bool condition_n(int r, Fourmi f, Place P1, Place P2);

void action_n(int r, Fourmi &f, Place &P1, Place &P2,colonie &C);

void NouvelleFourmi(Grille &g,colonie &C);


#endif // GRILLE_HPP
