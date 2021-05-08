#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include "doctest.h"
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"
#include "Grille.hpp"

using namespace std;

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

void placeSucre(Grille &g,EnsCoord C){
    for(int i=0;i<C.taille();i++){
         Coord k = C.iem(i);
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseSucre();
         g.rangePlace(p);
     }
}

void placeFourmis(Grille &g,std::vector<Fourmi> F){
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
    placeSucre(g,Sucre);
    placeFourmis(g,F);
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
  affichageGrillePheroNid(g);
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
  CHECK(P22.get_numeroFourmi() == f3.num());
  CHECK(P21.get_numeroFourmi() == -1);
  CHECK(P23.get_numeroFourmi() == -1);
  CHECK(P12.get_numeroFourmi() == -1);
  CHECK(P11.get_numeroFourmi() == f4.num());
  CHECK(P105.get_numeroFourmi() == -1);
  EnsCoord m = vector<Coord>{P23.get_coord(), P12.get_coord()};
  placeSucre(g, m);
  cout << " Sucre: " << P23.contientSucre() << endl;
  CHECK_THROWS_AS(deplaceFourmi(f3, P21, P22), invalid_argument); //La fourmi f3 n'est pas en {2,1}
  CHECK_THROWS_AS(deplaceFourmi(f3, P22, P23), invalid_argument); //On a posé du sucre en {2, 3}    
}

void Check_Ind_Fourmi(std::vector<Fourmi>F){
    for(size_t i=0;i < F.size();i++){
        //Pour ne pas avoir de warning
        int k = i; 
        if(k != F[i].num())throw runtime_error("Indice Fourmi different de l'indice du tableau");
    }
}
void Check_Place_Grille(Grille g){
    for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0; j<TAILLEGRILLE;j++){
            Coord k(i,j); 
            if( k != g.chargePlace(k).get_coord())throw runtime_error("Coord De Place a la mauvaise place");
        }
    }
}
void Check_Fourmi_Grille(Grille g,std::vector<Fourmi>F){
    for(size_t i=0;i < F.size();i++){
        Place P = g.chargePlace(F[i].coords());
        if(F[i].num() != P.get_numeroFourmi())throw runtime_error("Fourmi dans une case vide");
    }
}
void Check_Grille_Fourmi(Grille g,std::vector<Fourmi>F){
    for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0; j<TAILLEGRILLE;j++){
            Coord k(i,j);
            Place P = g.chargePlace(k);
            int Num = P.get_numeroFourmi();
            if( Num != -1 and P.get_coord() != F[Num].coords())throw runtime_error("Fourmi qui n'existe pas");
        }
    }
}

TEST_CASE("Test Coherence"){
    //A Faire
}



