#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "doctest.h"
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"

using namespace std;

Place::Place(Coord c):coord{c}{
    numeroFourmi = -1;
    sucre = false;
    nid =false;
    pheroSucre = 0;
    pheroNid = 0;
}
Coord Place::get_coord() const{
    return coord;
}
int Place::get_pheroSucre() const{
    return pheroSucre;
}
float Place::get_pheroNid() const{
    return pheroNid;
}
int Place::get_numeroFourmi() const{
    return numeroFourmi;
}
bool Place::contientSucre() const{
    return sucre;
}
bool Place::contientNid() const{
    return nid;
}
bool Place::estSurUnePiste() const{
    if(pheroSucre==0)return false;else return true;
}
TEST_CASE("Test Constructeur Place"){
    Place p(Coord{3,4});
    CHECK(p.get_coord() == Coord{3, 4});
    CHECK(p.get_pheroSucre() == 0);
    CHECK(p.get_numeroFourmi() == -1);
    CHECK(p.get_pheroNid() == 0);
    CHECK_FALSE(p.contientSucre());
    CHECK_FALSE(p.contientNid());
    CHECK_FALSE(p.estSurUnePiste());
    CHECK_FALSE(p.get_coord() == Coord{1, 0});   
}
void Place::poseSucre(){
    if(contientNid())throw invalid_argument("Impossible de poser du sucre sur un nid");   
    if(get_numeroFourmi() != -1)throw invalid_argument("Impossible de poser du sucre sur une fourmi");   
    sucre = true;
    pheroSucre = 255;
}
void Place::enleveSucre(){
    sucre = false;
}
void Place::poseNid(){
    if(contientSucre())throw invalid_argument("Impossible de poser un nid sur un sucre"); 
    if(get_numeroFourmi() != -1)throw invalid_argument("Impossible de poser un nid sur une fourmi"); 
    nid = true;
}
void Place::poseFourmi(Fourmi g){
    if(contientNid())throw invalid_argument("Impossible de poser une fourmi sur un nid"); 
    if(contientSucre())throw invalid_argument("Impossible de poser une fourmi sur un sucre");
    if(get_coord()!=g.coords())throw invalid_argument("Coordonnées de Fourmi et place différentes !");
    numeroFourmi = g.num();
}
void Place::enleveFourmi(){
    numeroFourmi =-1;
}
void Place::posePheroNid(float a){
    if(a<0 or a>1)throw invalid_argument("pheroNid doit etre compris entre 0 et 1");
    pheroNid = a;
}
void Place::posePheroSucre(){
    pheroSucre = 255;
}
void Place::diminuePheroSucre(){
    if(pheroSucre <= 5)pheroSucre = 0;else pheroSucre -= 5;   
}
void deplaceFourmi(Fourmi f, Place p1, Place p2){
    Coord k = p1.get_coord();
    if(!(voisines(k).contient(p2.get_coord())))throw invalid_argument("Position de deplacement invalide");
    if(p2.contientSucre())throw invalid_argument("deja du sucre sur la place"); 
    if(p2.get_numeroFourmi() != -1)throw invalid_argument("deja une fourmi sur la place");
    if(p1.get_numeroFourmi() != f.num())throw invalid_argument("Different ind pour place et fourmi");
    if(p1.get_coord() != f.coords())throw invalid_argument("Different coord pour place et fourmi");
    f.deplace(p2.get_coord());
    p2.poseFourmi(f);
    p1.enleveFourmi();

}

bool estVide(Place p1){
    return(!(p1.contientSucre()) and !(p1.contientNid()) and p1.get_numeroFourmi() == -1);
}

bool estPlusProcheNid(Place p1, Place p2){
    return (p1.get_pheroNid() > p2.get_pheroNid());
}
TEST_CASE("Test des méthodes de la classe abstraite Place"){
  Place p1(Coord{ 2, 2 });
  Place p2(Coord{ 2, 1 });  
  Place p3(Coord{ 2, 0 });
  CHECK_FALSE(p1.contientSucre());
  CHECK_FALSE(p2.contientSucre());
  CHECK_FALSE(p3.contientSucre());
  CHECK_FALSE(p1.contientNid());
  CHECK_FALSE(p2.contientNid());
  CHECK_FALSE(p3.contientNid());
  CHECK(p1.get_numeroFourmi() == -1);
  CHECK(p2.get_numeroFourmi() == -1);
  CHECK(p3.get_numeroFourmi() == -1);
  CHECK(estVide(p1));
  CHECK(estVide(p2));
  CHECK(estVide(p3));
  p1.poseSucre();
  CHECK(p1.contientSucre());
  CHECK(p1.get_pheroSucre() == 255);
  p1.enleveSucre();
  CHECK_FALSE(p1.contientSucre());
  p1.poseSucre();
  CHECK_THROWS_AS(p1.poseNid(), invalid_argument);
  CHECK(p2.get_pheroSucre() == 0);
  p2.posePheroSucre();
  CHECK(p2.get_pheroSucre() == 255);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre() == 250);
  for(int i = 0; i < 49; i++){
    p2.diminuePheroSucre();   
  }
  CHECK(p2.get_pheroSucre() == 5);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre() == 0);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre() == 0);
  CHECK_THROWS_AS(p2.posePheroNid(2), invalid_argument);
  CHECK_THROWS_AS(p2.posePheroNid(-2), invalid_argument);
  CHECK_THROWS_AS(p2.posePheroNid(1.01), invalid_argument);
  p3.posePheroNid(0.5);
  CHECK_FALSE(p3.get_pheroNid() == 0);
  CHECK(p3.get_pheroNid() == 0.5);
  Fourmi f1(Coord{2, 0}, 1);
  CHECK_THROWS_AS(p2.poseFourmi(f1), invalid_argument);
  
  p3.poseFourmi(f1);
  CHECK(p3.get_numeroFourmi() == 1);
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{1,2}, 1}, p3, p2), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{2,0}, 1}, p3, p1), invalid_argument);
  p1.enleveSucre();
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{2,0}, 1}, p3, p1), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{2,0}, 1}, p1, p3), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{2,1}, 3}, p2, p3), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(Fourmi{ Coord{2,1}, 3}, p3, p2), invalid_argument);
  // Rajouter qql tests pour les erreurs
  deplaceFourmi(f1, p3, p2);
  //CHECK_THROWS_AS(deplaceFourmi(f1, p2, p1), invalid_argument);
  //deplaceFourmi(f1, p2, p3);
  p1.enleveSucre();
  CHECK(estVide(p1));
  p1.poseNid();
  CHECK(p1.contientNid());
  CHECK(estPlusProcheNid(p3, p2));
  CHECK(estPlusProcheNid(p3, p1));
  CHECK_FALSE(estVide(p3));
  CHECK(estVide(p2));
  p2.posePheroNid(0.3);
  p3.posePheroNid(0.1);
  CHECK(estPlusProcheNid(p2, p3));
  // à compléter plus tard
}
Grille::Grille(){
   tab = {};
   for(int i=0;i<TAILLEGRILLE;i++){
        tab.push_back({});
        for(int j=0;j<TAILLEGRILLE;j++){
            tab[i].push_back(Place(Coord(i,j)));
        }
    } 
};

int Grille::TailleGrille(){
    return tab.size();
}
int Grille::SubTailleGrille(){
    return tab[0].size();
}

Place Grille::chargePlace(Coord k)const{
    /*
    for(int i=0;i<tailleGrille();i++){
        if(tab[i]).get_coord()==k)return tab[i].get_coord();
    }
    throw invalid_argument("Coordonnee pas dans la Grille");
    */
    return tab[k.get_lig()][k.get_col()];
}

void Grille::rangePlace(Place p){
    /*
    for(int i=0;i<tailleGrille();i++){
        if(tab[i]).get_coord()==p.get_coord())tab[i]=p;
    }
    */
    Coord k = p.get_coord();
    tab[k.get_lig()][k.get_col()]= p;
}
void placeNid(Grille g,EnsCoord C){
    /*
    for(int i=0;i<C.taille();i++){
        Coord k = C.iem(i);
        if(tab.size()<k.get_lig() or tab[0].size()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
        tab[k.get_lig()][k.get_col()].poseNid();
    }
    */
     for(int i=0;i<C.taille();i++){
         Coord k = C.iem(i);
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseNid();
         g.rangePlace(p);
     }
}

void PlaceSucre(Grille g,EnsCoord C){
    for(int i=0;i<C.taille();i++){
         Coord k = C.iem(i);
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseSucre();
         g.rangePlace(p);
     }
}

void PlaceFourmi(Grille g,std::vector<Fourmi> F){
    for(size_t i=0;i<F.size();i++){
         Coord k = F[i].coords();
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseFourmi(F[i]);
         g.rangePlace(p);
     }
}

Grille initialiseGrille(std::vector<Fourmi> F,EnsCoord Sucre,EnsCoord Nid){
    Grille g = Grille();
    placeNid(g,Nid);
    PlaceSucre(g,Sucre);
    PlaceFourmi(g,F);
    return g;
}

TEST_CASE("Grille Constructeur"){
    //A Faire Les Tests
}






