#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include "doctest.h"
using namespace std;
#include "Coord.hpp"
#include "Fourmi.hpp"

Fourmi::Fourmi(Coord a,int indice):coord{a},ind{indice}{
    aSucre = false;
}

Coord Fourmi::coords()const{
    return coord;
}
int Fourmi::num()const{
    return ind;
}
bool Fourmi::porteSucre()const{
    return aSucre;
}
void Fourmi::newind(int n){
    ind=n;
}

ostream &operator<<(ostream &out, const Fourmi &fourmi){
    out<<"Les coords de la fourmi sont "<<fourmi.coords()<<" et son num est"<<fourmi.num();
    if(fourmi.porteSucre())out<<" et porte du sucre";
    return out;
}
TEST_CASE("Test du constructeur des coordonnées"){
    Coord a(3,5);
    int p = 12;
    Fourmi k(a,p);
    CHECK(k.coords()==a);
    CHECK(k.num()==p);
    CHECK_FALSE(k.porteSucre());
}


void Fourmi::prendSucre(){
    aSucre=true;
}
void Fourmi::poseSucre(){
    aSucre=false;
}
void Fourmi::deplace(){
    EnsCoord a = voisines(coord);
    //Deplacement aléatoire
    int k = rand() % a.taille();
    coord = a.iem(k);
}
void Fourmi::deplace(Coord k){
    EnsCoord a = voisines(coord);
    if(a.contient(k)){
        coord=k;
    }else{
        throw invalid_argument("Position trop loin");
    }
}
TEST_CASE("Test Méthode prendSucre et PoseSucre + deplace"){
    Coord a(3,5);
    int p = 12;
    Fourmi k(a,p);
    CHECK_FALSE(k.porteSucre());
    CHECK_FALSE(voisines(k.coords()).contient(a));
    CHECK_THROWS_AS(k.deplace(Coord(8,8)),invalid_argument);
    k.deplace();
    CHECK(voisines(k.coords()).contient(a));
    k.prendSucre();
    CHECK(k.porteSucre());
    k.poseSucre();
    CHECK_FALSE(k.porteSucre());
    
}
vector<Fourmi> creeTabFourmi(EnsCoord total){
    for(int m = 0;m<total.taille();m++){
        for(int n=m+1;n<total.taille();n++){
            if(total.iem(n)==total.iem(m))throw invalid_argument("Plusieurs Fourmie meme case");
        }
    }
    vector<Fourmi>k= {};
    for(int i=0; i<total.taille();i++){
        k.push_back(Fourmi(total.iem(i),i));
    }
    return k;
}





