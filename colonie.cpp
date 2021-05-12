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

    
std::vector<Fourmi> colonie::get_colonie_ind(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice");
    return C[ind];
}
int colonie::get_Sucre_ind(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice");
    return NSucre[ind];
}
EnsCoord colonie::get_coord_Nid(int ind)const{
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice");
    return Nid[ind];
}
int colonie::get_nbColonie()const{
    return nbColonie;
}

void colonie::ajoute_colonie(vector<Fourmi> F){
    if(int(C.size())== nbColonie)throw invalid_argument("Toutes les colonies sont déja remplis");
    for(size_t i=0;i<F.size();i++){
        F[i].change_colonie(C.size());
    }
    C.push_back(F);
}
void colonie::ajoute_Fourmi(Fourmi F,int ind){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice");
    F.change_colonie(ind);
    C[ind].push_back(F);
}
void colonie::ajoute_Nid_colonie(EnsCoord C){
    if(int(Nid.size())== nbColonie)throw invalid_argument("Toutes les nids de colonies sont déja remplis");
    Nid.push_back(C);
}
void colonie::ajoute_Sucre(int ind){
    if(ind < 0 or ind >= nbColonie)throw invalid_argument("Mauvais indice");
    NSucre[ind] +=1;
}

TEST_CASE("Constructeur de colonie"){
    colonie k = colonie(1);
    EnsCoord N({Coord(1,2),Coord(1,1),Coord(2,1),Coord(2,2)});
    vector<Coord> PourF = {{10,2},{10,18},{6,5}};
    EnsCoord F1(PourF);
    vector<Fourmi> F = creeTabFourmi(F1);
    CHECK(k.get_nbColonie()==1);
    k.ajoute_colonie(F);
    CHECK_THROWS_AS(k.ajoute_colonie(F),invalid_argument);
    CHECK(k.get_colonie_ind(0).size()==3);
    Fourmi A(Coord(4,4),3);
    k.ajoute_Fourmi(A,0);
    CHECK(k.get_colonie_ind(0).size()==4);
    k.ajoute_Nid_colonie(N);
    CHECK(k.get_coord_Nid(0).taille()==4);
    k.ajoute_Sucre(0);
    CHECK(k.get_Sucre_ind(0)==1);
}
















