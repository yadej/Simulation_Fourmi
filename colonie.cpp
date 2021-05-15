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
#include "colonie.hpp"

using namespace std;

colonie::colonie(int colonie){
    nbColonie = colonie;
    C = {};
    Nid = {};
    NSucre ={};
    for(int i=0;i < nbColonie;i++){
        NSucre.push_back(0);
    }
}
int colonie::taille()const{
    return C.size();
}
int colonie::Nidtaille()const{
    return Nid.size();
}
    
vector<Fourmi> colonie::get_colonie_ind(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n1");
    return C[ind];
}
int colonie::get_Sucre_ind(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n2");
    return NSucre[ind];
}
EnsCoord colonie::get_coord_Nid(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n3");
    return Nid[ind];
}
int colonie::get_nbColonie()const{
    return nbColonie;
}

void colonie::ajoute_colonie(vector<Fourmi> F){
    if(int(C.size())== nbColonie)throw invalid_argument("Toutes les colonies sont déja remplis");
    for(size_t i=0;i<F.size();i++){
        F[i].change_colonie(C.size());
        if(F[i].num()!=int(i))throw invalid_argument("Mauvais indice de tableau");
    }
    C.push_back(F);
}
void colonie::ajoute_Fourmi(Coord Ca,int ind){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n4");
    Fourmi F = Fourmi(Ca,get_colonie_ind(ind).size(),ind);
    C[ind].push_back(F);
}
void colonie::ajoute_Nid_colonie(EnsCoord Ca){
    if(int(Nid.size())== nbColonie)throw invalid_argument("Toutes les nids de colonies sont déja remplis");
    Nid.push_back(Ca);
}
void colonie::ajoute_Sucre(int ind){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n5");
    NSucre[ind] +=1;
}
void colonie::colonie_remplace(vector<Fourmi> F,int ind){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n6");
    for(size_t i=0;i<F.size();i++){
        F[i].change_colonie(ind);
    }
    C[ind] = F;
}
void colonie::colonie_Fourmi_meurt(int ind,int pos){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice n7");
    if(pos > int(get_colonie_ind(ind).size()))throw invalid_argument("Pos trop grand");
    C[ind][pos].meurt();
}
bool colonie::SucreReset(int ind){
    if(NSucre[ind] >= 10){
        NSucre[ind] -= 10;
        return true;
    }
    return false;
}



void Affiche_NbFourmiColonie(colonie C){
    for(int i=0 ;i<C.taille();i++){
        vector<Fourmi> F = C.get_colonie_ind(i);
        int k = 0;
        for(size_t a = 0; a<F.size();a++){
            if(F[a].estVivant())k++;
        }
        cout<<"Colonie n'"<<i<<": "<<k<<" fourmis "<<endl;
    }
}

TEST_CASE("Constructeur de colonie"){
    srand(time(NULL));
    colonie k = colonie(1);
    CHECK(k.taille() == 0);
    CHECK(k.get_nbColonie() == 1);
    //CHECK(k.Nidtaille() == 0);
    //CHECK(k.get_colonie_ind(0).size() == 0);
    CHECK(k.get_Sucre_ind(0) == 0);
    //CHECK(k.get_coord_Nid(0).estVide());
    EnsCoord N({Coord(1,2),Coord(1,1),Coord(2,1),Coord(2,2)});
    vector<Coord> PourF = {{10,2},{10,18},{6,5}};
    EnsCoord F1(PourF);
    vector<Fourmi> F = creeTabFourmi(F1);
    CHECK(k.get_nbColonie()==1);
    k.ajoute_colonie(F);
    CHECK_THROWS_AS(k.ajoute_colonie(F),invalid_argument);
    CHECK(k.get_colonie_ind(0).size()==3);
    k.ajoute_Fourmi(Coord(4,4),0);
    CHECK(k.get_colonie_ind(0).size()==4);
    k.ajoute_Nid_colonie(N);
    CHECK(k.get_coord_Nid(0).taille()==4);
    k.ajoute_Sucre(0);
    CHECK(k.get_Sucre_ind(0)==1);
    CHECK_FALSE(k.SucreReset(0));
    for(int j = 0; j < 10; j ++){
       k.ajoute_Sucre(0);   
    }
    CHECK(k.get_Sucre_ind(0) == 11);
    CHECK(k.SucreReset(0));
    CHECK(k.get_Sucre_ind(0) == 1);
    vector<Coord> Pourf2 = {{11,2},{15,18},{6,8},{8,9},{11,12}};
    EnsCoord F2(Pourf2);
    vector<Fourmi> F3 = creeTabFourmi(F2);
    k.colonie_remplace(F3, 0);
    CHECK(k.get_colonie_ind(0).size() == 5);
    for(Fourmi f : k.get_colonie_ind(0)){
      CHECK(f.get_colonie() == 0);   
    }
    k.colonie_Fourmi_meurt(0, 2);
    CHECK_FALSE(k.get_colonie_ind(0)[2].estVivant());
}










