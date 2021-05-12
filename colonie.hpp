#ifndef COLONIE_HPP
#define COLONIE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"

class colonie{
    std::vector<std::vector<Fourmi>> C;
    std::vector<int> NSucre;
    std::vector<EnsCoord>Nid;
    int nbColonie;
    public:
    //Constructeurs
    colonie(int colonie);
    //methodes
    std::vector<Fourmi> get_colonie_ind(int ind)const;
    int get_Sucre_ind(int ind)const;
    EnsCoord get_coord_Nid(int ind)const;
    int get_nbColonie()const;
    
    void ajoute_colonie(std::vector<Fourmi> F);
    void ajoute_Fourmi(Fourmi F,int ind);
    void ajoute_Nid_colonie(EnsCoord C);
    void ajoute_Sucre(int ind);
    
};


#endif