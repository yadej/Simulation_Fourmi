#ifndef Coord_HPP
#define Coord_HPP

#include <vector>
#include <string>
#include <iostream>

const int TAILLEGRILLE = 50;

class Coord{
  // Attribus
  int lig; // La ligne où se positionne la coordonnée
  int col; // La colonne où se positionne la coordonnée
  
  public:
    
  //Constructeur
    
  //* @param[in] lig : la ligne
  //* @param[in] col : la colonne
  //* @param[out] c : [Coord] la coordonnée
  //* [error] lève une erreur si la ligne
  //* ou la colonne <0 ou >TAILLEGRILLE-1
  Coord(int lig, int col);
    
  //Methodes
    
  //* Retourne la ligne d'une coordonnée
  //*  @return : [int] lig
  int get_lig() const;

  //* Retourne la colonne d'une coordonnée
  //*  @return : [int] col
  int get_col() const; 

};

// Surcharge d'opérateurs de coordonnées

// L'affichage
std::ostream& operator<<(std::ostream& out, Coord c);

// L'opérateur ==
bool operator==(const Coord& a, const Coord& b);

// L'opérateur !=
bool operator!=(const Coord& a, const Coord& b);

class EnsCoord{
  // Attribus
  std::vector<Coord> tab; // Un vecteur contenant les coordonnées
    
   // Méthodes
    
  //* @param[in] c : la coordonnée recherchée
  //* @param[out] i : [int] l'indice de la première
  //* apparition de la coordonnée dans l'ensemble de coordonnées
  int Position(Coord c)const;
  
  public:
  //Constructeur
  //* @param[out] tab: [EnsCoord] un ensemble de coordonnées vide
  EnsCoord();

  //* @param[in] t : un vecteur de Coord
  //* @param[out] tab: [EnsCoord] ensemble de coordonnées
  EnsCoord(std::vector<Coord> Ens);  
    
  // Getter
  //* @param[out] tab: [vector<Coord>] le tableau
  //* de l'ensemble de coordonnées
  std::vector<Coord> get_tab() const;
    
  // Méthodes
  
  //* @param[in] c : la coordonnée recherchée
  //* @param[out] : [bool] true si la coordonnée
  //* est dans l'ensemble, false sinon
  bool contient(Coord c) const;
  
  //* @param[in] c : la coordonnée à ajouter
  //* ne la rajoute que si elle n'y est pas déjà
  void ajoute(Coord c);
  
  //* @param[in] c : la coordonnée à supprimer
  //* [error] revoie une erreur si elle n'y est pas
  void supprime(Coord c);
  
  //* @param[out] : [bool] true si l'EnsCoord est vide
  //* false sinon
  bool estVide()const;
    
  //* @param[out] : [int] la taille de l'EnsCoord
  int taille()const;
  
  //* @param[in] n : la position de la coordonnée
  //* @param[out] : [Coord] la n-ième coordonnée
  //* lève une erreur si n < 0 ou n > taille()-1
  Coord iem(int n)const;
    
  //* @param[out] : [Coord] une coordonnée au hasard
  //* [error] lève une erreur si l'EnsCoord est vide
  Coord choixHasard();
  std::ostream& print(std::ostream& out) const;
};

std::ostream &operator<<(std::ostream &out, const EnsCoord &coordtotal);
bool operator==(EnsCoord const& a, EnsCoord const& b);


//* @param[in] c : la coordonnée
//* @param[out] v : [EnsCoord] toutes les
//* coordonnées voisines
EnsCoord voisines(Coord c);

// Fonction pour tester affichages
void testAffichageCoordonnees();

#endif  
