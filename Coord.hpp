#ifndef Coord_HPP
#define Coord_HPP

#include <vector>
#include <string>
#include <iostream>

const int TAILLEGRILLE = 50;

class Coord{
    // Attributs
    int lig;
    int col;
    public:
        // Constructeurs:
        Coord(int a,int b);
        // Methodes:
        int get_lig()const;
        int get_col()const;
};

std::ostream &operator<<(std::ostream &out, const Coord &coord);
bool operator==(Coord const& a, Coord const& b);
bool operator!=(Coord const& a, Coord const& b);

class EnsCoord{
    // Attributs
    std::vector<Coord>tab;
    // Methode
    int Position(Coord co)const;
    public:
        // Constructeurs:
        EnsCoord();
        EnsCoord(std::vector<Coord> Ens);
        // Methodes:
        std::vector<Coord> get_tab(){return tab;}
        Coord iem(int n)const;
        Coord choixHasard();
        int taille()const;
        bool contient(Coord co)const;
        bool estVide()const;
        void ajoute(Coord co);
        void supprime(Coord co);
        std::ostream& print(std::ostream& out) const;
};
std::ostream &operator<<(std::ostream &out, const EnsCoord &coordtotal);
bool operator==(EnsCoord const& a, EnsCoord const& b);
EnsCoord voisines(Coord a);
#endif  
