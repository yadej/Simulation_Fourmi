#ifndef Coord_HPP
#define Coord_HPP

#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int TAILLEGRILLE = 20;

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
        std::ostream& print(std::ostream& out) const;
};

ostream &operator<<(ostream &out, const Coord &coord);
bool operator==(Coord const& a, Coord const& b);
bool operator!=(Coord const& a, Coord const& b);

class EnsCoord{
    // Attributs
    vector<Coord>k;
    // Methode
    int Position(Coord co)const;
    public:
        // Constructeurs:
        EnsCoord(vector<Coord> Ens);
        // Methodes:
        Coord get_kpos(int i)const;
        Coord ieme(int n)const;
        int get_ksize()const;
        int taille()const;
        bool contient(Coord co)const;
        bool estVide()const;
        void ajoute(Coord co);
        void supprime(Coord co);
};
ostream &operator<<(ostream &out, const EnsCoord &coordtotal);
#endif  
