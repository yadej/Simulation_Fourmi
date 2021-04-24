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
// Difficile de tester deplace sans beaucoup de condition
void Fourmi::deplace(){
    EnsCoord a = voisines(coord);
    //Deplacement aléatoire
    int k = rand() % a.taille();
    coord = a.iem(k);
}
TEST_CASE("Test Méthode prendSucre et PoseSucre"){
    Coord a(3,5);
    int p = 12;
    Fourmi k(a,p);
    CHECK_FALSE(k.porteSucre());
    k.prendSucre();
    CHECK(k.porteSucre());
    k.poseSucre();
    CHECK_FALSE(k.porteSucre());
    
}