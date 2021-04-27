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

EnsFourmi::EnsFourmi(Coord a): coord(a){}

void EnsFourmi::creeFourmi(){
    Fourmi k(coord,Fourmigenere.size()+1);
    Fourmigenere.push_back(k);
}

void EnsFourmi::supprimeFourmi(int ind){
    if(ind<1 or ind>int(Fourmigenere.size()))throw invalid_argument("Indice incorrect");
    Fourmigenere.erase(Fourmigenere.begin()+ind-1);
    for(long unsigned int i=0;i<Fourmigenere.size();i++){
        Fourmigenere[i].newind(i+1);
    }
}
Fourmi EnsFourmi::iem(int n){
    if(n<1 or n>int(Fourmigenere.size()))throw invalid_argument("Indice incorrect");
    return Fourmigenere[n-1];
}

EnsCoord EnsFourmi::TotalPosFourmi(){
    EnsCoord k = EnsCoord();
    for(long unsigned int i = 0;i < Fourmigenere.size();i++){
        k.ajoute(Fourmigenere[i].coords());
    }
    return k;
}


TEST_CASE("Test EnsFourmi"){
    //A faire des test
}




