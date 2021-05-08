#ifndef Fourmi_HPP
#define Fourmi_HPP
#include "Coord.hpp"
#include <vector>
#include <string>
#include <iostream>

class Fourmi{
    Coord coord;
    int ind;
    bool aSucre;
    public:
    //Constructeur
    //* @param[out] f : la fourmi
    //* @param[in] a : coordonnee de la fourmi
    //* @param[in] v : son numero
    Fourmi(Coord a,int indice);
    //methode
    //* Retourne les coord de la fourmi
    //*  @return : coord
    Coord coords()const;
    //* Retourne le numero de la fourmi
    //*  @return : ind
    int num()const;
    //* Test si la fourmi porte du sucre
    //* @return : un booléen selon le résultat du test
    bool porteSucre()const;
    //* La fourmi prend un sucre
    void prendSucre();
    //* La fourmi pose un sucre
    void poseSucre();
    //* La fourmi se deplace aleatoirement
    void deplace();
    //* La fourmi se deplace dans cette coordonnee si elle est bien proche
    //* @param[in] k : les coordonnees 
    void deplace(Coord k);
    //* Change l'indice de la Fourmi
    //* @param[in] n: la nouvelle indice
    void newind(int n);
};
std::vector<Fourmi> creeTabFourmi(EnsCoord c);
std::ostream &operator<<(std::ostream &out, const Fourmi &fourmi);



#endif  
