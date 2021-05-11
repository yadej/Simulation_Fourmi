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
  
  // Méthodes
  int TailleGrille();
  int SubTailleGrille();
  Place chargePlace(Coord c) const;
  void rangePlace(Place p);
  void linearisePheroNid();
  void diminuePheroSucre();
  //Affichage
  void dessine();
  void affichePheroSucre();
  void affichePheroNid();


};

void placeNid(Grille &g, EnsCoord e,int colonie);
void placeSucre(Grille &g, EnsCoord e);
void placeFourmis(Grille &g, vector<Fourmi> f);
void lineariserPheroNid(Grille &g,int colonie);
Grille initialiseGrille(vector<Fourmi> v, EnsCoord s, EnsCoord n);

//Test Coherence
void Check_Ind_Fourmi(std::vector<Fourmi>F);
void Check_Place_Grille(Grille g);
void Check_Fourmi_Grille(Grille g,std::vector<Fourmi>F);
void Check_Grille_Fourmi(Grille g,std::vector<Fourmi>F);

//1) //A Faire quand on aura codé les colonies
void tue(Fourmi &f, Place &P1, Place &P2);
bool tue_ondition(Fourmi f, Place P1, Place P2);

//2)
void prendSucre(Fourmi &f, Place &P1, Place &P2);
bool prendSucre_condition(Fourmi f, Place P1, Place P2);    
    
//3)
void poseSucre(Fourmi &f, Place &P1, Place &P2); //, int &nbSucreNid)
bool poseSucre_condition(Fourmi f, Place P1, Place P2);

//4)
void chercheNid(Fourmi &f, Place &P1, Place &P2);
bool chercheNid_condition(Fourmi f, Place P1, Place P2);
    
//5)
void chercheSucreSurPiste(Fourmi &f, Place &P1, Place &P2);
bool chercheSucreSurPiste_condition(Fourmi f, Place P1, Place P2);
    
//6)    
void cherchePiste(Fourmi &f, Place &P1, Place &P2);
bool cherchePiste_condition(Fourmi f, Place P1, Place P2);    
    
//7)
void chercheSansPiste(Fourmi &f, Place &P1, Place &P2);
bool chercheSansPiste_condition(Fourmi f, Place P1, Place P2);

void mettreAJourEnsFourmi(Grille &g, vector<Fourmi> &F);

void mettreAJourFourmi(Grille &g, Fourmi &f);

bool condition_n(int r, Fourmi f, Place P1, Place P2);

void action_n(int r, Fourmi &f, Place &P1, Place &P2);



#endif // GRILLE_HPP
