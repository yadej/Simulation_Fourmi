#ifndef Fourmi_HPP
#define Fourmi_HPP
#include "Coord.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Fourmi{
    Coord coord;
    int ind;
    bool aSucre;
    public:
        //Constructeur
        Fourmi(Coord a,int indice);
        //methode
        Coord coords()const;
        int num()const;
        bool porteSucre()const;
        void prendSucre();
        void poseSucre();
        void deplace();
};

#endif  
