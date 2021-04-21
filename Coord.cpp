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
EnsCoord::EnsCoord(vector<Coord> Ens):k{}{
    for(auto i:Ens)k.push_back(i);
}

//Fonction getter
int Coord::get_lig()const{
    return lig;
}
int Coord::get_col()const{
    return col;
}
int EnsCoord::get_ksize()const{
    return k.size();
}
Coord EnsCoord::get_kpos(int i)const{
    return k[i];
}
int EnsCoord::Position(Coord co)const{
    int a=0;
    for(auto i:k){
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
ostream &operator<<(ostream &out, const EnsCoord &coordtotal){
    int p=coordtotal.get_ksize();
    for(int i=0;i<p;i++){
        out<<coordtotal.get_kpos(i);   
    }
    return out;
}
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
    if(Position(co)==-1)return;
    k.push_back(co);
}
void EnsCoord::supprime(Coord co){
    if(!contient(co))throw invalid_argument("Cette position n'est pas dans le tableau");
    k.erase(k.begin()+Position(co));
}
bool EnsCoord::estVide() const {
    return k.empty();
}
int EnsCoord::taille()const{
    return get_ksize();
}

Coord EnsCoord::ieme(int n)const{
    if(n<0)return get_kpos(0);
    else if(n>get_ksize())return get_kpos(get_ksize()-1);
    else return get_kpos(n);
}















