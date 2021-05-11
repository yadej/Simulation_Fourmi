#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stdlib.h>
#include "doctest.h"
using namespace std;

#include "Coord.hpp"
//Constructeurs
Coord::Coord(int a,int b){
    if(a < 0 or b < 0 or a >= TAILLEGRILLE or b >= TAILLEGRILLE){
        throw invalid_argument("Position qui n'est pas dans la Grille ");
    }
    lig = a;
    col = b;
};
TEST_CASE("test Coord") {
    Coord k(5,6);
    CHECK(k==Coord{5,6});
    CHECK_THROWS_AS(Coord(-2,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(21,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,60),invalid_argument);
    CHECK_THROWS_AS(Coord(-2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(20,60),invalid_argument);
}
EnsCoord::EnsCoord(){
    tab = {};
};

EnsCoord::EnsCoord(vector<Coord> Ens):tab{Ens}{};

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

ostream &operator<<(ostream &out, const Coord &coord){
    return out<<"("<<coord.get_lig()<<","<<coord.get_col()<<")"<<endl;
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

Coord EnsCoord::iem(int n)const{
    if(n<0 or n>int(tab.size())-1)throw invalid_argument("Indice incorrect");
    return tab[n];
}
TEST_CASE("test EnsCoord") {
    EnsCoord b({Coord(1,6),Coord(2,6),Coord(3,6),Coord(4,6)});
    CHECK(b.taille()==4);
    CHECK(b.iem(0)==Coord{1,6});
    CHECK(b.contient(Coord{2,6}));
    CHECK(b.contient(Coord{3,6}));
    CHECK(b.contient(Coord{4,6}));
    CHECK(b.iem(0)==Coord{1,6});
    CHECK(b.iem(1)==Coord{2,6});
    CHECK(b.iem(2)==Coord{3,6});
    CHECK(b.iem(3)==Coord{4,6});
    b.ajoute(Coord{1,6});
    CHECK(b.taille()==4);
    CHECK_THROWS_AS(b.supprime(Coord(0,6)),invalid_argument);
    b.supprime(Coord(1,6));
    CHECK_FALSE(b.contient(Coord{1,6}));
    CHECK(b.taille()==3);
    CHECK(b.iem(0)==Coord{2,6});
    CHECK(b.iem(1)==Coord{3,6});
    CHECK(b.iem(2)==Coord{4,6});
    b.ajoute(Coord{1,6});
    b.ajoute(Coord{5,6});
    CHECK(b.taille()==5);
    CHECK(b.contient(Coord{3,6}));
    CHECK(b.iem(0)==Coord{2,6});
    CHECK(b.iem(1)==Coord{3,6});
    CHECK(b.iem(2)==Coord{4,6});
    CHECK(b.iem(3)==Coord{1,6});
    CHECK(b.iem(4)==Coord{5,6});
    CHECK(EnsCoord{{}}.estVide());
}

EnsCoord voisines(Coord a){
    EnsCoord Tout = EnsCoord();
    int imin = max(a.get_lig()-1,0);
    int imax = min(a.get_lig()+1,TAILLEGRILLE-1);
    int jmin = max(a.get_col()-1,0);
    int jmax = min(a.get_col()+1,TAILLEGRILLE-1);
    for(int i=imin;i<=imax;i++){
        for(int j=jmin;j<=jmax;j++){
            Coord k(i,j);
            if(k!=a)Tout.ajoute(k);
        }
    }
    return Tout;
}

TEST_CASE("Test voisine"){
    CHECK_THROWS_AS(voisines(Coord{50,50}),invalid_argument);
    CHECK_THROWS_AS(voisines(Coord{-1,10}),invalid_argument);
    CHECK_THROWS_AS(voisines(Coord{10,-1}),invalid_argument);
    CHECK_THROWS_AS(voisines(Coord{21,10}),invalid_argument);
    CHECK_THROWS_AS(voisines(Coord{10,21}),invalid_argument);

    // Verifions un milieu
    CHECK(voisines(Coord{10,10}).taille()==8);
    CHECK(voisines(Coord{10,10}).contient(Coord{11,11}));
    CHECK(voisines(Coord{10,10}).contient(Coord{11,10}));
    CHECK(voisines(Coord{10,10}).contient(Coord{11,9}));
    CHECK(voisines(Coord{10,10}).contient(Coord{9,11}));
    CHECK(voisines(Coord{10,10}).contient(Coord{10,11}));
    CHECK(voisines(Coord{10,10}).contient(Coord{9,9}));
    CHECK(voisines(Coord{10,10}).contient(Coord{10,9}));
    CHECK(voisines(Coord{10,10}).contient(Coord{9,10}));
    // Verifions le coin en haut a gauche
    CHECK(voisines(Coord{0,0}).taille()==3);
    CHECK(voisines(Coord{0,0}).contient(Coord{1,0}));
    CHECK(voisines(Coord{0,0}).contient(Coord{1,1}));
    CHECK(voisines(Coord{0,0}).contient(Coord{0,1}));
    // Verifions le mileu a gauche
    CHECK(voisines(Coord{0,10}).taille()==5);
    CHECK(voisines(Coord{0,10}).contient(Coord{0,11}));
    CHECK(voisines(Coord{0,10}).contient(Coord{0,9}));
    CHECK(voisines(Coord{0,10}).contient(Coord{1,11}));
    CHECK(voisines(Coord{0,10}).contient(Coord{1,9}));
    CHECK(voisines(Coord{0,10}).contient(Coord{1,10}));
    // Check un point au hasard dans le mileu
    int k = rand()%10 + 5; // 5 <= k <= 14
    int l = rand()%10 + 5; // 5 <= l <= 14
    CHECK(voisines(Coord{k,l}).taille()==8);
    CHECK(voisines(Coord{k,l}).contient(Coord{k+1,l+1}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k+1,l}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k+1,l-1}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k,l+1}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k-1,l+1}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k-1,l-1}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k-1,l}));
    CHECK(voisines(Coord{k,l}).contient(Coord{k,l-1}));
    // Verifions pour un point au hasard sur le bord haut,
    // mais pas dans un coin
    int m = rand()%18 + 1; // 1<= m <= 18
    int n = 0;
    CHECK(voisines(Coord{m, n}).taille() == 5);
    CHECK_FALSE(voisines(Coord{m, n}).contient(Coord{m, n}));
    CHECK(voisines(Coord{m, n}).contient(Coord{m-1, n}));
    CHECK(voisines(Coord{m, n}).contient(Coord{m+1, n}));
    CHECK(voisines(Coord{m, n}).contient(Coord{m+1, n+1}));
    CHECK(voisines(Coord{m, n}).contient(Coord{m, n+1}));
    CHECK(voisines(Coord{m, n}).contient(Coord{m-1, n+1}));
    // Verifions pour un point au hasard sur le bord droit,
    // mais pas dans un coin
    int p = TAILLEGRILLE - 1;
    int q = rand()%18 + 1; // 1 <= q <= 18
    CHECK(voisines(Coord{p, q}).taille() == 5);
    CHECK_FALSE(voisines(Coord{p, q}).contient(Coord{p, q}));
    CHECK(voisines(Coord{p, q}).contient(Coord{p, q-1}));
    CHECK(voisines(Coord{p, q}).contient(Coord{p-1, q-1}));
    CHECK(voisines(Coord{p, q}).contient(Coord{p-1, q}));
    CHECK(voisines(Coord{p, q}).contient(Coord{p-1, q+1}));
    CHECK(voisines(Coord{p, q}).contient(Coord{p, q+1}));
    // Vérifions pour un point au hasard sur le bors du  bas
    // mais pas dans un coin
    int r = rand()%18 + 1; // 1<= r <= 18
    int s = TAILLEGRILLE - 1;
    CHECK(voisines(Coord{r, s}).taille() == 5);
    CHECK_FALSE(voisines(Coord{r, s}).contient(Coord{r, s}));
    CHECK(voisines(Coord{r, s}).contient(Coord{r-1, s}));
    CHECK(voisines(Coord{r, s}).contient(Coord{r-1, s-1}));
    CHECK(voisines(Coord{r, s}).contient(Coord{r, s-1}));
    CHECK(voisines(Coord{r, s}).contient(Coord{r+1, s-1}));
    CHECK(voisines(Coord{r, s}).contient(Coord{r+1, s}));
    // Verifions tout les points au centres
    /*
    for(int i=1;i<TAILLEGRILLE-1;i++){
        for(int j=1;j<TAILLEGRILLE-1;j++){
            CHECK(voisines(Coord{i,j}).taille()==8);
            CHECK(voisines(Coord{i,j}).contient(Coord{i+1,j+1}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i+1,j}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i+1,j-1}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i,j+1}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i-1,j+1}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i-1,j-1}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i-1,j}));
            CHECK(voisines(Coord{i,j}).contient(Coord{i,j-1}));
        }
    }
    */
    
    //Plus de test à faire pour mieux vérifier
    
    
}

Coord EnsCoord::choixHasard(){
  if(taille() == 0){
    throw invalid_argument("L'ensemblde de coordonnées est vide");
  }
  srand (time(NULL));
  int i = rand()%(taille());
  return tab[i];
}

TEST_CASE("Fonction choixHasard"){
    EnsCoord k({Coord(1,6),Coord(2,6),Coord(3,6),Coord(4,6)});
    for(int i = 0; i < 50; i++){
        Coord h = k.choixHasard();
        CHECK(k.contient(h));
    }

}












