#ifndef PLACE_HPP
#define PLACE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "colonie.hpp"

class Place{
  // Attribus
  Coord coord;
  int numeroFourmi;
  int numeroColonie;
  bool sucre;
  bool nid;
  int pheroSucre;
  std::vector<float> pheroNid;

    
  public:
  // Constructeur
  Place(Coord c);
  Place(Coord c,int colonie);
  
  // Methodes
  Coord get_coord() const;
  int get_pheroSucre() const;
  float get_pheroNid() const;
  float get_pheroNid(int i) const;
  int get_numeroFourmi() const;
  int get_numeroColonie() const;
  // Prédicats sur une place
  bool contientSucre() const;
  bool contientNid() const;
  bool estSurUnePiste() const;
  //Modifications sur une place  
  void poseSucre();
  void enleveSucre();
  void poseNid();
  void poseFourmi(Fourmi g);
  void enleveFourmi();
  void posePheroNid(float a,int i);
  void posePheroSucre();
  void diminuePheroSucre();
};

// Modification sur deux places
void deplaceFourmi(Fourmi &f, Place &p1, Place &p2);

bool estVide(Place p1);

bool estPlusProcheNid(Place p1, Place p2,int ind);

bool estPlusLoinNid(Place p1, Place p2,int ind);

#endif //PLACE_HPP
