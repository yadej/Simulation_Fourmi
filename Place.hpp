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
  //* Coordonnées de la place
  Coord coord_;
    
  //* Le numéro de la fourmi si elle en contient, sinon -1
  int numeroFourmi_;
    
  //* Numéro de colonie du Nid/Fourmi si elle contient
  //* l'un des deux, sinon -1
  int numeroColonie_;
    
  //* true si elle contient du sucre, false sinon
  bool sucre_;
    
  //* true si elle contient un nid, false sinon
  bool nid_;
  
  //* Tableau contenant en indice 0, l'intensité des phéromones
  //* de sucre de la colonie 0, puis celle de la colonie 2,...
  std::vector<int> pheroSucre_;
    
  //* Tableau contenant en indice 0, l'intensité des phéromones
  //* de sucre de la colonie 0, puis celle de la colonie 2,...
  std::vector<float> pheroNid_;

    
  public:
  // Constructeur
    
  //* @param[in] c : coordonnee de la place
  //* @param[out] : une place avec cette coordonnée,
  //* ne contenant pas de fourmi, ni de sucre, ni de
  //* nid, ni de colonie, avec les pheromones de nid
  //* & sucre vides
  Place(Coord c);
    
  //* @param[in] c : coordonnee de la fourmi
  //* @param[in] nbColonies : le nombre de colonies
  //* @param[out] : une place avec cette coordonnée,
  //* ne contenant pas de fourmi, ni de sucre, ni de
  //* nid, ni de colonie, avec les pheromones de nid
  //* & sucre à 0 et de même dimension que le nombre
  //* de colonies
  Place(Coord c,int colonie);
  
  // Methodes
  //* @param[out] : la coordonnée de la place
  Coord get_coord() const;
    
  //* @param[out] : le tableau des phéromones
  //* de sucre de cette place
  std::vector<int> get_pheroSucre() const;
    
  //* @param[in] i : le numéro de la colonie ciblée
  //* @param[out] : l'intensité des phéromones de
  //* de sucre de la colonie i
  int get_pheroSucre(int i) const;
    
  //* @param[out] : le tableau des phéromones
  //* de nid de cette place
  std::vector<float> get_pheroNid() const;
    
  //* @param[in] i : le numéro de la colonie ciblée
  //* @param[out] : l'intensité des phéromones de
  //* de nid de la colonie ind
  float get_pheroNid(int ind) const;
    
  //* @param[out] : le numéro de la fourmi
  //* de cette place ou -1 si aucune fourmi
  int get_numeroFourmi() const;
    
  //* @param[out] : le numéro de la colonie de
  //* cette place ou -1 si aucune fourmi ou nid
  int get_numeroColonie() const;
  
  // Prédicats sur une place

  //* @param[out] : true si la place contient
  //* un sucre, false sinon
  bool contientSucre() const;
    
  //* @param[out] : true si la place contient
  //* un nid, false sinon
  bool contientNid() const;
    
  //* @param[out] : true si la place est sur une
  //* piste de phéromone de nid de la colonie 0
  bool estSurUnePiste() const;
   
  //* @param[in] ind : numéro de la colonie
  //* @param[out] : true si la place est sur une
  //* piste de phéromone de nid de la colonie ind
  bool estSurUnePiste(int ind) const;


  //Modifications sur une place 
    
  //* Pose du sucre sur la place
  //* [error] : lève une erreur si il
  //* y a déjà une fourmi, un nid, ou
  //* un autre sucre sur cette place
  void poseSucre();
    
  //* Enleve du sucre de la place
  //* [error1] : lève une erreur si il
  //* y a déjà une fourmi sur cette place
  //* [error2] : lève une erreur si il
  //* y a déjà un nid sur cette place
  //* [error3] : lève une erreur si il
  //* y a déjà un autre sucre sur cette place
  void enleveSucre();
    
  //* @param[in] ind : numéro de la colonie
  //* pose un nid de la colonie ind sur cette
  //* place
  //* [error1] : lève une erreur si il
  //* y a déjà une fourmi sur cette place
  //* [error2] : lève une erreur si il
  //* y a déjà un autre nid sur cette place
  //* [error3] : lève une erreur si il
  //* y a déjà un sucre sur cette place
  void poseNid(int ind);
  
  //* @param[in] g : une fourmi
  //* pose la fourmi sur cette place
  //* [error1] : lève une erreur si il y a 
  //* déjà une autre fourmi sur cette place
  //* [error2] : lève une erreur si il
  //* y a déjà un nid sur cette place
  //* [error3] : lève une erreur si il
  //* y a déjà un sucre sur cette place
  void poseFourmi(Fourmi g);
    
  //* Enleve la fourmi de cette place s'
  //* il y en a une
  void enleveFourmi();
    
  //* @param[in] a : une intensité de 
  //* phéromone de nid
  //* @param[in] ind : un numéro de colonie
  //* Pose des phéromones de nid sur cette
  //* place, d'intenstié a et de colonie ind
  //* [error1] : lève une erreur si le phéromone
  //* n'est pas compris entre 0 et 1 inclus
  //* [error2] : lève une erreur si le numéro 
  //* de colonie et inférieur à 0 ou supérieur
  //* au nombre de colonies total
  void posePheroNid(float a, int ind);
    
  //* Pose sur cette place des phéromones de
  //* sucre d'intensité maximale 255 de la colonie 0
  void posePheroSucre();
    
  //* @param[in] ind : un numéro de colonie
  //* Pose sur cette place des phéromones de
  //* sucre d'intensité maximale 255 de la colonie ind
  void posePheroSucre(int ind);
    
  //* Diminue de 5 les phéromones de sucre de toutes
  //* les colonies
  void diminuePheroSucre();

};

// Modification sur deux places

//* @param[in] f : une fourmi
//* @param[in] p1 : la place de départ
//* @param[in] p2 : la place d'arrivée
//* déplace la fourmi de la place p1 à p2
//* [error1] : lève une erreur si la place de
//* départ ne contient pas le numéro de la fourmi
//* [error2] : lève une erreur si la place et la fourmi
//* n'ont pas les mêmes coordonnées
//* [error3] : lève une erreur si la place d'arrivée
//* contient déjà une autre fourmi
//* [error4] : lève une erreur si la place d'arrivée
//* contient déjà un sucre
//* [error5] : lève une erreur si la place d'arrivée
//* contient déjà un nid
void deplaceFourmi(Fourmi &f, Place &p1, Place &p2);

//* @param[in] p1 : une place
//* @param[out] : true si la place ne contient ni
//* de fourmi, ni de nid, ni de sucre
bool estVide(Place p1);

//* @param[in] p1 : une place
//* @param[in] p2 : une autre place
//* @param[in] int : un numéro de colonie
//* @param[out] : true si l'intensité de phéromones
//* de nid de la colonie ind est strictement plus fort
//* sur la place p1 que sur la place p2, false sinon
//* [error] : lève une erreur si le numéro de colonie
//* est inférieur à 0 ou supérieur au nombre de colonies -1 
bool estPlusProcheNid(Place p1, Place p2, int ind);

//* @param[in] p1 : une place
//* @param[in] p2 : une autre place
//* @param[in] int : un numéro de colonie
//* @param[out] : true si l'intensité de phéromones
//* de nid de la colonie ind est strictement moins fort
//* sur la place p1 que sur la place p2, false sinon
//* [error] : lève une erreur si le numéro de colonie
//* est inférieur à 0 ou supérieur au nombre de colonies -1 
bool estPlusLoinNid(Place p1, Place p2, int ind);




#endif //PLACE_HPP
