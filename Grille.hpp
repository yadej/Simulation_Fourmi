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
};

void placeNid(Grille &g, EnsCoord e);
void placeSucre(Grille &g, EnsCoord e);
void placeFourmis(Grille &g, vector<Fourmi> f);
Grille initialiseGrille(vector<Fourmi> v, EnsCoord s, EnsCoord n);

//Test Coherence
void Check_Ind_Fourmi(std::vector<Fourmi>F);
void Check_Place_Grille(Grille g);
void Check_Fourmi_Grille(Grille g,std::vector<Fourmi>F);
void Check_Grille_Fourmi(Grille g,std::vector<Fourmi>F);

#endif // GRILLE_HPP
