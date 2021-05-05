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
void deplaceFourmi(Fourmi &f, Place &p1, Place &p2){
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
  Fourmi f2(Coord{1,2}, 1);
  Fourmi f3(Coord{2,0}, 3);
  CHECK_THROWS_AS(deplaceFourmi(f2, p3, p2), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(f1, p3, p1), invalid_argument);
  p1.enleveSucre();
  CHECK_THROWS_AS(deplaceFourmi(f1, p3, p1), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(f1, p1, p3), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(f3, p2, p3), invalid_argument);
  CHECK_THROWS_AS(deplaceFourmi(f3, p3, p2), invalid_argument);
  // Rajouter qql tests pour les erreurs
  deplaceFourmi(f1, p3, p2);
  //CHECK_THROWS_AS(deplaceFourmi(f1, p2, p1), invalid_argument);
  deplaceFourmi(f1, p2, p3);
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
void placeNid(Grille &g,EnsCoord C){
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
         p.posePheroNid(1);
         g.rangePlace(p);
     }
}

void PlaceSucre(Grille &g,EnsCoord C){
    for(int i=0;i<C.taille();i++){
         Coord k = C.iem(i);
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseSucre();
         g.rangePlace(p);
     }
}

void PlaceFourmi(Grille &g,std::vector<Fourmi> F){
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
void lineariserPheroNid(Grille &g){
    bool stable = false;
    while(stable == false){
        stable = true;
        for(int i=0; i<TAILLEGRILLE;i++){
            for(int j=0;j<TAILLEGRILLE;j++){
                Coord C1(i,j);
                Place p1 =  g.chargePlace(C1);
                if(p1.get_pheroNid()<1){
                    EnsCoord voisin = voisines(C1);
                    float maxPhero = 0;
                    for(Coord Cv: voisin.get_tab()){
                        Place p2 = g.chargePlace(Cv);
                        maxPhero = max(maxPhero, p2.get_pheroNid());
                    }
                    maxPhero = float(maxPhero - 1./TAILLEGRILLE);
                    if(maxPhero > p1.get_pheroNid()){
                        p1.posePheroNid(maxPhero);
                        g.rangePlace(p1);
                        stable = false;
                    }
                }
            }
        }
    }
}
void Grille::diminuePheroSucre(){
    for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            Coord C1(i,j);
            Place p1 = chargePlace(C1);
            if(!p1.contientSucre()){
                p1.diminuePheroSucre();
                rangePlace(p1);
            }
}
void affichageGrillePheroNid(Grille g){
    for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            Coord C1(i,j);
            Place p1 =  g.chargePlace(C1);
            cout<<setw(4);
            cout<<float(int(p1.get_pheroNid()*100))/100<<" ";
        }
        cout<<endl;
    }
}


TEST_CASE("Test constructeur grille"){
  Grille g = Grille();
  //affichageGrillePheroNid(g);
  for(int i = 0; i < g.TailleGrille(); i++){
    for(int j = 0; j < g.SubTailleGrille(); j++){
      Place a = g.chargePlace(Coord{i,j});
      CHECK(a.get_coord() == Coord{i,j});
      CHECK(a.get_pheroSucre() == 0);
      CHECK(a.get_pheroNid() == 0);
      CHECK(estVide(a));
    }
  }
}

TEST_CASE("Test Méthodes Grille"){
    Grille g = Grille();
    
    vector<Coord> h =  {{2, 0}, {2, 1}};
    EnsCoord j = h;
    placeNid(g, j);
    lineariserPheroNid(g);
    //affichageGrillePheroNid(g);
      /*
  Place k = g.chargePlace(h[0]);
  Fourmi f1 = {Coord{h[0]}, 1};
  Fourmi f2 = {Coord{h[1]}, 2};
  vector<Fourmi> F = {f1, f2};
  CHECK_THROWS_AS(placeSucre(g, j), invalid_argument);
  CHECK_THROWS_AS(placeFourmis(g, F), invalid_argument);
  CHECK(k.get_pheroNid() == 1);
  //On va poser des fourmis et les faire se déplacer
  Fourmi f3 = {Coord{2, 2}, 3};
  Fourmi f4 = {Coord{1, 1}, 4};
  vector<Fourmi> F2 = {f3, f4};
  placeFourmis(g, F2);
  CHECK(g.chargePlace(Coord{2, 2}).get_numeroFourmi() == 3);
  CHECK(g.chargePlace(Coord{1, 1}).get_numeroFourmi() == 4);
  Place P22 = g.chargePlace(Coord{2, 2});
  Place P105 = g.chargePlace(Coord{10, 5});
  Place P23 = g.chargePlace(Coord{2, 3});
  Place P12 = g.chargePlace(Coord{1, 2});
  Place P11 = g.chargePlace(Coord{1, 1});
  Place P21 = g.chargePlace(Coord{2, 1});
  CHECK_THROWS_AS(deplaceFourmi(f3, P22, P105), invalid_argument);// Cases trop éloignées
  deplaceFourmi(f3, P22, P23);
  deplaceFourmi(f3, P23, P22);
  deplaceFourmi(f3, P22, P12);
  CHECK_THROWS_AS(deplaceFourmi(f3, P12, P11), invalid_argument);//Une fourmi déjà sur ctte case
  deplaceFourmi(f3, P12, P22);
  CHECK_THROWS_AS(deplaceFourmi(f3, P22, P21), invalid_argument);// Il y a déjà un Nid en {2, 1}
  CHECK(P22.get_numeroFourmi() == f3.get_indice());
  CHECK(P21.get_numeroFourmi() == -1);
  CHECK(P23.get_numeroFourmi() == -1);
  CHECK(P12.get_numeroFourmi() == -1);
  CHECK(P11.get_numeroFourmi() == f4.get_indice());
  CHECK(P105.get_numeroFourmi() == -1);
  EnsCoord m = vector<Coord>{P23.get_coord(), P12.get_coord()};
  placeSucre(g, m);
  cout << " Sucre: " << P23.contientSucre() << endl;
  CHECK_THROWS_AS(deplaceFourmi(f3, P21, P22), invalid_argument); //La fourmi f3 n'est pas en {2,1}
  CHECK_THROWS_AS(deplaceFourmi(f3, P22, P23), invalid_argument); //On a posé du sucre en {2, 3}    
  */
}






