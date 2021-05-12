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
    Vivant = true;
    colonie = -1;
}
Fourmi::Fourmi(Coord a,int indice,int colonie):coord{a},ind{indice},colonie{colonie}{
    aSucre = false;
    Vivant = true;
}

Coord Fourmi::coords()const{
    return coord;
}
int Fourmi::num()const{
    return ind;
}
int Fourmi::get_colonie()const{
    return colonie;
}
bool Fourmi::porteSucre()const{
    return aSucre;
}
bool Fourmi::estVivant()const{
    return Vivant;
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
void Fourmi::change_colonie(int i){
    colonie = i;
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
void Fourmi::meurt(){
    Vivant = false;
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
TEST_CASE("Test de la fonction creeTabFourmis"){
  vector<Coord> t = {Coord{0, 0}, Coord{0, 1}, Coord{2, 0}};
  EnsCoord d = t;
  vector<Fourmi> G = creeTabFourmi(d);
  CHECK(G.size() == 3);
  CHECK(G[0].coords() == Coord{0, 0});
  CHECK(G[1].coords() == Coord{0, 1});
  CHECK(G[2].coords() == Coord{2, 0});
  CHECK(G[0].num() == 0);
  CHECK(G[1].num() == 1);
  CHECK(G[2].num() == 2);
  vector<Coord> s = {Coord{0, 0}, Coord{0, 1}, Coord{0, 0}};
  EnsCoord e = s;
  CHECK_THROWS_AS(creeTabFourmi(s), invalid_argument);  
}



