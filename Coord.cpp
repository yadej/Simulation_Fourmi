#include <iostream>
#include <stdexcept>
#include <vector>
#include "doctest.h"
using namespace std;

#include "Coord.hpp"
//Constructeurs
Coord::Coord(int a,int b){
    if(a < 0 or b < 0 or a > TAILLEGRILLE or b > TAILLEGRILLE){
        throw invalid_argument("Position qui n'est pas dans la Grille ");
    }
    lig = a;
    col = b;
};
EnsCoord::EnsCoord(vector<Coord> Ens):tab{Ens}{
};

//Fonction getter
int Coord::get_lig()const{
    return lig;
}
int Coord::get_col()const{
    return col;
}

int EnsCoord::Position(Coord co)const{
    int a=0;
    for(auto i:tab){
        if(i==co)return a;
        a++;
    }
    return -1;
}

//Surcharge d'operateur

std::ostream& Coord::print(std::ostream& out) const{
    out<<"("<<lig<<col<<")"<<endl;
    return out;
}
ostream &operator<<(ostream &out, const Coord &coord){
    return coord.print(out);
}
std::ostream& EnsCoord::print(std::ostream& out) const{
    for(long unsigned int i=0;i<tab.size();i++){
        out<<tab[i];
    }
    return out;
}
ostream &operator<<(ostream &out, const EnsCoord &coordtotal){
    return coordtotal.print(out);
}
/*
ostream &operator<<(ostream &out, const EnsCoord &coordtotal){
    int p=coordtotal.get_ksize();
    for(int i=0;i<p;i++){
        out<<coordtotal.get_kpos(i);   
    }
    return out;
}
*/
bool operator==(Coord const& a, Coord const& b){
    return a.get_lig()==b.get_lig() and a.get_col()==b.get_col();
}
bool operator!=(Coord const& a, Coord const& b){
    return !(a==b);
}

//Fonction

bool EnsCoord::contient(Coord co)const{
    if(Position(co)==-1)return false;else return true;
}
void EnsCoord::ajoute(Coord co){
    if(!contient(co))tab.push_back(co);
}
void EnsCoord::supprime(Coord co){
    if(!contient(co))throw invalid_argument("Cette position n'est pas dans le tableau");
    tab.erase(tab.begin()+Position(co));
}
bool EnsCoord::estVide() const {
    return tab.empty();
}
int EnsCoord::taille()const{
    return(int(tab.size()));
}

Coord EnsCoord::ieme(int n)const{
    if(n<0 or n>int(tab.size())-1)throw invalid_argument("Indice incorrect");
    return tab[n];
}















