#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include "doctest.h"
using namespace std;
#include "Coord.hpp"
#include "Fourmi.hpp"

Fourmi::Fourmi(Coord a,int indice):coord_{a},indice_{indice}{
    sucre_ = false;
    Vivant_ = true;
    colonie_ = -1;
}
Fourmi::Fourmi(Coord a,int indice,int colonie):coord_{a},indice_{indice},colonie_{colonie}{
    sucre_ = false;
    Vivant_ = true;
}

Coord Fourmi::coords()const{
    return coord_;
}
int Fourmi::num()const{
    return indice_;
}
int Fourmi::get_colonie()const{
    return colonie_;
}
bool Fourmi::porteSucre()const{
    return sucre_;
}
bool Fourmi::estVivant()const{
    return Vivant_;
}


ostream &operator<<(ostream &out, const Fourmi &fourmi){
    out<<"Les coords de la fourmi sont "<<fourmi.coords()<<" et son num est"<<fourmi.num();
    if(fourmi.porteSucre())out<<" et porte du sucre";
    out << "et elle appartient à la colonie " << fourmi.get_colonie();   
    return out;
}

void Fourmi::change_colonie(int i){
    colonie_ = i;
}

void Fourmi::prendSucre(){
    sucre_=true;
}
void Fourmi::poseSucre(){
    sucre_=false;
}
void Fourmi::deplace(Coord k){
    EnsCoord a = voisines(coord_);
    if(a.contient(k)){
        coord_=k;
    }else{
        throw invalid_argument("Position trop loin");
    }
}
void Fourmi::meurt(){
    Vivant_ = false;
}
TEST_CASE("Test du constructeur Fourmi"){
  Fourmi f(Coord(0, 1), 2, 0);
  CHECK(f.coords() == Coord(0, 1));
  CHECK(f.num() == 2);
  CHECK(f.get_colonie() == 0);
  CHECK(f.estVivant());
  CHECK_FALSE(f.get_colonie() == 1);
  CHECK_FALSE(f.porteSucre());
  f.prendSucre();
  CHECK(f.porteSucre());
  f.poseSucre();
  CHECK_FALSE(f.porteSucre());
  f.deplace(Coord(1, 2));
  CHECK(f.coords() == Coord(1, 2));
  CHECK_THROWS_AS(f.deplace(Coord(0,0)), invalid_argument);
  CHECK_FALSE(f.get_colonie() == -1);
  CHECK(f.get_colonie() == 0);
  f.change_colonie(1);
  CHECK_FALSE(f.get_colonie() == 0);
  CHECK(f.get_colonie() == 1);
  CHECK(f.estVivant());
  f.meurt();
  CHECK_FALSE(f.estVivant());
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
TEST_CASE("Test de la fonction creeTabFourmis"){
  vector<Coord> t = {Coord(0, 0), Coord(0, 1), Coord(2, 0)};
  EnsCoord d = t;
  vector<Fourmi> G = creeTabFourmi(d);
  CHECK(G.size() == 3);
  CHECK(G[0].coords() == Coord(0, 0));
  CHECK(G[1].coords() == Coord(0, 1));
  CHECK(G[2].coords() == Coord(2, 0));
  CHECK(G[0].num() == 0);
  CHECK(G[1].num() == 1);
  CHECK(G[2].num() == 2);
  CHECK(G[0].get_colonie() == -1);
  CHECK(G[1].get_colonie() == -1);
  CHECK(G[2].get_colonie() == -1);
  vector<Coord> s = {Coord(0, 0), Coord(0, 1), Coord(0, 0)};
  EnsCoord e = s;
  CHECK_THROWS_AS(creeTabFourmi(s), invalid_argument);
}



