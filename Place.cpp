#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "doctest.h"
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"
#include "colonie.hpp"

using namespace std;

Place::Place(Coord c):coord_{c}{
    numeroFourmi_ = -1;
    numeroColonie_ = -1;
    sucre_ = false;
    nid_ =false;
    pheroSucre_ = {0};
    pheroNid_ = {0};
}
Place::Place(Coord c,int colonie):coord_{c}{
    numeroFourmi_ = -1;
    sucre_ = false;
    nid_ =false;
    pheroSucre_ = {};
    pheroNid_ = {};
    numeroColonie_ = -1;
    for(int i = 0; i<colonie;i++){
        pheroNid_.push_back(0);
        pheroSucre_.push_back(0);
    }
}
Coord Place::get_coord() const{
    return coord_;
}
vector<int> Place::get_pheroSucre() const{
    return pheroSucre_;
}
int Place::get_pheroSucre(int i) const{
    return pheroSucre_[i];
}
std::vector<float>  Place::get_pheroNid() const{
    return pheroNid_;
}
float Place::get_pheroNid(int i) const{
    return pheroNid_[i];
}
int Place::get_numeroFourmi() const{
    return numeroFourmi_;
}
int Place::get_numeroColonie() const{
    return numeroColonie_;
}
bool Place::contientSucre() const{
    return sucre_;
}
bool Place::contientNid() const{
    return nid_;
}
bool Place::estSurUnePiste() const{
    if(pheroSucre_[0]==0)return false;else return true;
}
bool Place::estSurUnePiste(int ind) const{
    if(pheroSucre_[ind]==0)return false;else return true;
}
TEST_CASE("Test Constructeur Place"){
    Place p(Coord{3,4},3);
    CHECK(p.get_coord() == Coord(3, 4));
    CHECK(p.get_pheroSucre().size() == 3);
    CHECK(p.get_pheroSucre(0) == 0);
    CHECK(p.get_numeroFourmi() == -1);
    CHECK(p.get_pheroNid().size() == 3);
    CHECK(p.get_pheroNid(0) == 0);
    CHECK_FALSE(p.contientSucre());
    CHECK_FALSE(p.contientNid());
    CHECK_FALSE(p.estSurUnePiste());
    CHECK_FALSE(p.get_coord() == Coord{1, 0});   
}
void Place::poseSucre(){
    if(contientNid())throw invalid_argument("Impossible de poser du sucre sur un nid");   
    if(get_numeroFourmi() != -1)throw invalid_argument("Impossible de poser du sucre sur une fourmi");  
    if(contientSucre())throw invalid_argument("Impossible de poser du sucre sur un sucre"); 
    sucre_ = true;
    for(size_t i=0;i<pheroSucre_.size();i++){
        pheroSucre_[i] = 255;
    }
}
void Place::enleveSucre(){
    sucre_ = false;
}
void Place::poseNid(int i){
    if(contientSucre())throw invalid_argument("Impossible de poser un nid sur un sucre"); 
    if(get_numeroFourmi() != -1)throw invalid_argument("Impossible de poser un nid sur une fourmi"); 
    nid_ = true;
    pheroNid_[i] = 1;
    numeroColonie_ = i;

}
void Place::poseFourmi(Fourmi g){
    if(contientNid())throw invalid_argument("Impossible de poser une fourmi sur un nid"); 
    if(contientSucre())throw invalid_argument("Impossible de poser une fourmi sur un sucre");
    if(get_coord()!=g.coords())throw invalid_argument("Coordonnées de Fourmi et place différentes !");
    numeroFourmi_ = g.num();
    numeroColonie_ = g.get_colonie();
}
void Place::enleveFourmi(){
   if(numeroFourmi_ != -1){
        numeroFourmi_ = -1;
        numeroColonie_ = -1;
    } 

}
void Place::posePheroNid(float a,int i){
    if(a<0 or a>1)throw invalid_argument("pheroNid doit etre compris entre 0 et 1");
    int h = pheroNid_.size() - 1;
    if(i < 0 or i > h)throw invalid_argument("La colonie n'est pas valide");   
    pheroNid_[i] = a;
}
void Place::posePheroSucre(){
    pheroSucre_[0] = 255;
}
void Place::posePheroSucre(int ind){
    pheroSucre_[ind] = 255;
}
void Place::diminuePheroSucre(){
    for(size_t i=0;i<pheroSucre_.size();i++){
        if(pheroSucre_[i] <= 5)pheroSucre_[i] = 0;else pheroSucre_[i] -= 5;   
    }
}
void deplaceFourmi(Fourmi &f, Place &p1, Place &p2){
    Coord k = p1.get_coord();
    if(!(voisines(k).contient(p2.get_coord())))throw invalid_argument("Position de deplacement invalide");
    if(p2.contientSucre())throw invalid_argument("deja du sucre sur la place"); 
    if(p2.get_numeroFourmi() != -1)throw invalid_argument("deja une fourmi sur la place");
    if(p1.get_numeroFourmi() != f.num())throw invalid_argument("Different ind pour place et fourmi");
    if(p1.get_numeroColonie() != f.get_colonie())throw invalid_argument("Different ind de colonie pour place et fourmi");
    if(p1.get_coord() != f.coords())throw invalid_argument("Different coord pour place et fourmi");
    f.deplace(p2.get_coord());
    p2.poseFourmi(f);
    p1.enleveFourmi();
    if(!estVide(p1))throw runtime_error("LA place ne s'est pas vidé");
}

bool estVide(Place p1){
    return(!(p1.contientSucre()) and !(p1.contientNid()) and p1.get_numeroFourmi() == -1);
}

bool estPlusProcheNid(Place p1, Place p2,int ind){
    return (p1.get_pheroNid(ind) > p2.get_pheroNid(ind));
}
bool estPlusLoinNid(Place p1, Place p2,int ind){
    return (p1.get_pheroNid(ind) < p2.get_pheroNid(ind));
}

TEST_CASE("Test des méthodes de la classe abstraite Place"){
  Place p1(Coord(2, 2),2);
  Place p2(Coord(2, 1),2);  
  Place p3(Coord(2, 0),2);
  CHECK_FALSE(p1.contientSucre());
  CHECK_FALSE(p2.contientSucre());
  CHECK_FALSE(p3.contientSucre());
  CHECK_FALSE(p1.contientNid());
  CHECK_FALSE(p2.contientNid());
  CHECK_FALSE(p3.contientNid());
  CHECK_FALSE(p1.estSurUnePiste(1));
  CHECK_FALSE(p2.estSurUnePiste(0));
  CHECK_FALSE(p3.estSurUnePiste(1));
  CHECK(p1.get_numeroFourmi() == -1);
  CHECK(p2.get_numeroFourmi() == -1);
  CHECK(p3.get_numeroFourmi() == -1);
  int h1 = p1.get_pheroNid().size();
  int h2 = p2.get_pheroNid().size();
  int h3 = p3.get_pheroNid().size();
  CHECK(h1 == 2);
  CHECK(h2 == 2);
  CHECK(h3 == 2);
  CHECK(estVide(p1));
  CHECK(estVide(p2));
  CHECK(estVide(p3));
  p1.poseSucre();
  CHECK(p1.contientSucre());
  CHECK(p1.get_pheroSucre(0) == 255);
  p1.enleveSucre();
  CHECK_FALSE(p1.contientSucre());
  p1.poseSucre();
  CHECK_THROWS_AS(p1.poseNid(1), invalid_argument);
  CHECK(p2.get_pheroSucre(0) == 0);
  p2.posePheroSucre();
  CHECK(p2.get_pheroSucre(0) == 255);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre(0) == 250);
  for(int i = 0; i < 49; i++){
    p2.diminuePheroSucre();   
  }
  CHECK(p2.get_pheroSucre(0) == 5);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre(0) == 0);
  p2.diminuePheroSucre();
  CHECK(p2.get_pheroSucre(0) == 0);
  CHECK_THROWS_AS(p2.posePheroNid(2, 0), invalid_argument);  // PheroNid > 1 
  CHECK_THROWS_AS(p2.posePheroNid(-2, 1), invalid_argument); // PheroNid < 0
  CHECK_THROWS_AS(p2.posePheroNid(1.01, 1), invalid_argument);  // PheroNid > 1
  CHECK_THROWS_AS(p2.posePheroNid(0.98, 3), invalid_argument);  // num de colonie > nb colonies
  p3.posePheroNid(0.5,1);
  CHECK_FALSE(p3.get_pheroNid(1) == 0);
  CHECK(p3.get_pheroNid(1) == 0.5);
  Fourmi f1 = {Coord{2, 0}, 1, 0};
  CHECK_THROWS_AS(p2.poseFourmi(f1), invalid_argument);
  p3.poseFourmi(f1);
  CHECK(p3.get_numeroFourmi() == 1);
  Fourmi f2 = {Coord{1,2}, 2, 1};
  CHECK_THROWS_AS(deplaceFourmi(f2, p3, p2), invalid_argument);
  deplaceFourmi(f1, p3, p2);
  CHECK_THROWS_AS(deplaceFourmi(f1, p2, p1), invalid_argument);
  deplaceFourmi(f1, p2, p3);
  p1.enleveSucre();
  CHECK(estVide(p1));
  p1.poseNid(0);
  CHECK(p1.contientNid());
  CHECK(estPlusProcheNid(p1, p2, 0));
  CHECK(estPlusProcheNid(p1, p3, 0));
  CHECK_FALSE(estVide(p3));
  CHECK(estVide(p2));
  p2.posePheroNid(0.3, 0);
  p3.posePheroNid(0.1, 0);
  CHECK(estPlusProcheNid(p2, p3, 0));


}





