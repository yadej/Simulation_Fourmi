#ifndef PLACE_HPP
#define PLACE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"

class Place{
  // Attribus
  Coord coord;
  int numeroFourmi;
  bool sucre;
  bool nid;
  int pheroSucre;
  float pheroNid;

    
  public:
  // Constructeur
  Place(Coord c);
  
  // Methodes
  Coord get_coord() const;
  int get_pheroSucre() const;
  float get_pheroNid() const;
  int get_numeroFourmi() const;
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
  void posePheroNid(float a);
  void posePheroSucre();
  void diminuePheroSucre();
};

// Modification sur deux places
void deplaceFourmi(Fourmi &f, Place &p1, Place &p2);

bool estVide(Place p1);

bool estPlusProcheNid(Place p1, Place p2);

class Grille{
    std::vector<std::vector<Place>>tab;
    public:
    Grille();
    //Methodes
    int TailleGrille();
    int SubTailleGrille();
    Place chargePlace(Coord k)const;
    //Modifications
    void rangePlace(Place p);
    void linearisePheroNid();
    void diminuePheroSucre();
};
void placeNid(Grille &g,EnsCoord C);
void PlaceSucre(Grille &g,EnsCoord C);
void PlaceFourmi(Grille &g,std::vector<Fourmi> F);
Grille initialiseGrille(std::vector<Fourmi> F,EnsCoord Sucre,EnsCoord Nid);
void lineariserPheroNid(Grille &g);
void affichageGrillePheroNid(Grille g);

#endif //PLACE_HPP
