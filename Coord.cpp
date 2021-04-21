#include <iostream>
#include <stdexcept>
#include "doctest.h"
using namespace std;

#include "Coord.hpp"

Coord::Coord(int a,int b){
    if(a < 0 or b < 0 or a > TAILLEGRILLE or b > TAILLEGRILLE){
        throw invalid_argument("Position qui n'est pas dans la Grille ");
    }
    lig = a;
    col = b;
};
EnsCoord(vector<Coord>Ens){
    k=Ens;
}

int Coord::get_lig()const{
    return lig;
}
int Coord::get_col()const{
    return col;
}
int EnsCoord::get_ksize()const{
    return k.size();
}
int EnsCoord::get_kpos(int i)const{
    return k[i];
}

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
