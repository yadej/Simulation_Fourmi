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
Grille::Grille(int colonie){
    tab = {};
   for(int i=0;i<TAILLEGRILLE;i++){
        tab.push_back({});
        for(int j=0;j<TAILLEGRILLE;j++){
            tab[i].push_back(Place(Coord(i,j),colonie));
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
void placeNid(Grille &g,colonie C){
    for(int i=0;i<C.get_nbColonie();i++){
        if(C.Nidtaille()<= i)throw runtime_error("Pas assez de nid");
        EnsCoord a = C.get_coord_Nid(i);
        for(int j=0;j<a.taille();j++){
           Coord k = a.iem(j);
           if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
           Place p = g.chargePlace(k);
           p.poseNid(i);
           p.posePheroNid(1,i);
           g.rangePlace(p);
        
        }
    }
     /*
     for(int i=0;i<C.taille();i++){
         Coord k = C.iem(i);
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseNid();
         p.posePheroNid(1,colonie);
         g.rangePlace(p);
     }*/
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

void placeFourmis(Grille &g,colonie C){
    for(int i=0;i<C.get_nbColonie();i++){
        if(C.taille()<= i)throw runtime_error("Pas assez de colonie");
        vector<Fourmi> F = C.get_colonie_ind(i);
        for(size_t j=0;j<F.size();j++){
           Coord k = F[j].coords();
           if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
           Place p = g.chargePlace(k);
           p.poseFourmi(F[j]);
           g.rangePlace(p);
        }
    }
    /*
    for(size_t i=0;i<F.size();i++){
         Coord k = F[i].coords();
         if(g.TailleGrille()<k.get_lig() or g.SubTailleGrille()<k.get_col())throw invalid_argument("Coordonnee pas dans la Grille");
         Place p = g.chargePlace(k);
         p.poseFourmi(F[i]);
         g.rangePlace(p);
     }*/
}

Grille initialiseGrille(colonie C,EnsCoord Sucre,int colo){
    if(colo < 1 or colo > C.get_nbColonie())throw invalid_argument("indice trop haut ou bas");
    Grille g = Grille(colo);
    placeNid(g,C);
    placeSucre(g,Sucre);
    placeFourmis(g,C);
    return g;
}
void lineariserPheroNid(Grille &g,int colonie){
    bool stable = false;
    while(stable == false){
        stable = true;
        for(int i=0; i<TAILLEGRILLE;i++){
            for(int j=0;j<TAILLEGRILLE;j++){
                Coord C1(i,j);
                Place p1 =  g.chargePlace(C1);
                if(p1.get_pheroNid(colonie)<1){
                    EnsCoord voisin = voisines(C1);
                    float maxPhero = 0;
                    for(Coord Cv: voisin.get_tab()){
                        Place p2 = g.chargePlace(Cv);
                        maxPhero = max(maxPhero, p2.get_pheroNid(colonie));
                    }
                    maxPhero = float(maxPhero - 1./TAILLEGRILLE);
                    if(maxPhero > p1.get_pheroNid(colonie)){
                        p1.posePheroNid(maxPhero,colonie);
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
void Grille::dessine(){
  string ligne = "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤";
  string ligneHaut = "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐";
  string ligneBas = "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘";
  for(int i = 0; i < TAILLEGRILLE; i++){
    if(i == 0){
      cout << ligneHaut << endl;   
    }
    else{
      cout << ligne << endl;
    }
    for(int j = 0; j < TAILLEGRILLE; j++){
      Place p = chargePlace(Coord(j, i));
      if(p.get_numeroFourmi() != -1){
          if(p.get_numeroColonie() != -1){
              cout << "│f"<<p.get_numeroColonie()<<" ";  
          }else{
              cout << "│ f ";
          }
      }
      if(p.contientNid()){
        cout << "│ N ";   
      }
      if(p.contientSucre()){
        cout << "│ S ";   
      }
      if(estVide(p)){
        cout << "│   ";   
      }
    }
    cout << "│" << endl;
  }
  cout << ligneBas << endl;
}

void Grille::affichePheroSucre(){
  string ligne = "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤";
  string ligneHaut = "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐";
  string ligneBas = "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘";
  for(int i = 0; i < TAILLEGRILLE; i++){
    if(i == 0){
      cout << ligneHaut << endl;   
    }
    else{
      cout << ligne << endl;
    }
    for(int j = 0; j < TAILLEGRILLE; j++){
      Place p = chargePlace(Coord(j, i));
      cout << "│" << setw(3) << p.get_pheroSucre();
    }
    cout << "│" << endl;
  }
  cout << ligneBas << endl;
}

void Grille::affichePheroNid(int ind){
for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0;j<TAILLEGRILLE;j++){
            Coord C1(i,j);
            Place p1 =  chargePlace(C1);
            cout<<setw(4);
            cout<<float(int(p1.get_pheroNid(ind)*100))/100<<" ";
        }
        cout<<endl;
    }
}




TEST_CASE("Test constructeur grille"){
  Grille g = Grille();
  //g.affichePheroNid();
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
/*
TEST_CASE("Test Méthodes Grille"){
  Grille g = Grille();
  vector<Coord> h =  {{2, 0}, {2, 1}};
  EnsCoord j = h;
  placeNid(g, j,0);
  lineariserPheroNid(g,0);
  //g.affichePheroNid();
  Place k = g.chargePlace(h[0]);
  Fourmi f1(Coord{h[0]}, 1);
  Fourmi f2(Coord{h[1]}, 2);
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
  //g.dessine();
  //cout << " Sucre: " << P23.contientSucre() << endl;
  CHECK_THROWS_AS(deplaceFourmi(f3, P21, P22), invalid_argument); //La fourmi f3 n'est pas en {2,1}
  CHECK_THROWS_AS(deplaceFourmi(f3, P22, P23), invalid_argument); //On a posé du sucre en {2, 3}    
}
*/

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
void Check_Fourmi_Grille(Grille g,colonie C){
    for(int k =0 ; k<C.get_nbColonie();k++){
        if(k >= C.taille())throw runtime_error("Pas assez de colonie");
        vector<Fourmi> F = C.get_colonie_ind(k);
        if(C.get_colonie_ind(k).size()==0)continue;
        for(size_t i=0;i < F.size();i++){
            if(F[i].estVivant()){
                Place P = g.chargePlace(F[i].coords());
                if(F[i].num() != P.get_numeroFourmi() or F[i].get_colonie() != P.get_numeroColonie())throw runtime_error("Fourmi dans une case vide");
            }
        }
    }
}
void Check_Grille_Fourmi(Grille g,colonie C){
    for(int i=0; i<TAILLEGRILLE;i++){
        for(int j=0; j<TAILLEGRILLE;j++){
            Coord k(i,j);
            Place P = g.chargePlace(k);
            int Num = P.get_numeroFourmi();
            int Colo = P.get_numeroColonie();
            if( Num != -1 and Colo != -1 and P.get_coord() != C.get_colonie_ind(Colo)[Num].coords())throw runtime_error("Fourmi qui n'existe pas");
        }
    }
}
/*
TEST_CASE("Test Coherence"){
    //A Faire
    Fourmi a(Coord(1,2),0);
    Fourmi b(Coord(2,2),0);
    Fourmi c(Coord(3,2),2);
    vector<Fourmi> F1 = {a,b,c};
    CHECK_THROWS_AS(Check_Ind_Fourmi(F1),runtime_error);
    Fourmi d(Coord(4,2),1);
    vector<Fourmi> F2 = {a,d,c};
    Check_Ind_Fourmi(F2);
    Grille g = Grille();
    Check_Place_Grille(g);
    placeFourmis(g, F2);
    Check_Fourmi_Grille(g,F2);
    CHECK_THROWS_AS(Check_Grille_Fourmi(g,F1),runtime_error);
    Place P = g.chargePlace(Coord(2,2));
    P.enleveFourmi();
    g.rangePlace(P);
    CHECK_THROWS_AS(Check_Fourmi_Grille(g,F1),runtime_error);
    
}
*/
/*
void TourGrille(Grille &g,std::vector<Fourmi>&F,int &nbSucreNid){
    g.diminuePheroSucre();
    Check_Fourmi_Grille(g,F);
    Check_Grille_Fourmi(g,F);
    Check_Place_Grille(g);
    for(size_t i=0; i<F.size();i++){
        
        Place P1 = g.chargePlace(F[i].coords());
        EnsCoord k = voisines(F[i].coords());
        //Cas Si il a un Sucre
        if(!F[i].porteSucre()){
            for(Coord a:k.get_tab()){
                Place P2 = g.chargePlace(a);
                //Si nid a cote pose le sucre
                //Regle 3
                if(P2.contientNid()){
                    F[i].poseSucre();
                    nbSucreNid++;
                    break;
                }
            }
            //Si apres le tour il n'y a toujours pas de nid
            //Regle 4
            if(F[i].porteSucre()){
                for(Coord a:k.get_tab()){
                    Place P2 = g.chargePlace(a);
                    //Si la place est pas vide ou le pheronid est trop bas
                    if(estPlusProcheNid(P1,P2,0) or !estVide(P2))k.supprime(a);
                }
                //Si la Fourmi ne peut pas se rapprocher du nid il ne bouge pas et passe a la case suivante
                cout<<k<<endl;
                if(k.estVide())continue;
                Place P2 = g.chargePlace(k.choixHasard());
                deplaceFourmi(F[i],P1,P2);
                P2.posePheroSucre();
                g.rangePlace(P1);
                g.rangePlace(P2);
                Check_Fourmi_Grille(g,F);
                Check_Grille_Fourmi(g,F);
            }
            
         //Cas Fourmi ne portant pas de sucre  
        }else{
            bool Sucre = false;
            for(Coord a:k.get_tab()){
                Place P2 = g.chargePlace(a);
                //Si la fourmi est a cote d'un sucre
                //Regle 2
                if(P2.contientSucre()){
                    F[i].prendSucre();
                    P1.posePheroSucre();
                    g.rangePlace(P1);
                    break;
                }
                //Regle 5
                if(P1.estSurUnePiste() and P2.estSurUnePiste() and estPlusLoinNid(P1,P2,0) and estVide(P2)){
                    deplaceFourmi(F[i],P1,P2);
                    P2.posePheroSucre();
                    g.rangePlace(P1);
                    g.rangePlace(P2);
                    Check_Fourmi_Grille(g,F);
                    Check_Grille_Fourmi(g,F);
                    break;
                }
                if(P2.estSurUnePiste())Sucre=true;
            }
            if(F[i].porteSucre())continue;
            //Regle 6
            if(Sucre){
                for(Coord a:k.get_tab()){
                    Place P2 = g.chargePlace(a);
                    if(!P2.estSurUnePiste() or !estVide(P2))k.supprime(a);
                }
                Place P2 = g.chargePlace(k.choixHasard());
                deplaceFourmi(F[i],P1,P2);
                P2.posePheroSucre();
                g.rangePlace(P1);
                g.rangePlace(P2);
                Check_Fourmi_Grille(g,F);
                Check_Grille_Fourmi(g,F);
                continue;
            }
            //Regle 7
            for(Coord a:k.get_tab()){
                Place P2 = g.chargePlace(a);
                if(!estVide(P2))k.supprime(a);
            }
            Place P2 = g.chargePlace(k.choixHasard());
            deplaceFourmi(F[i],P1,P2);
            P2.posePheroSucre();
            g.rangePlace(P1);
            g.rangePlace(P2);
            Check_Fourmi_Grille(g,F);
            Check_Grille_Fourmi(g,F);
            
        }
    }
    Check_Place_Grille(g);
}
*/
//1)
void tue(Fourmi &f, Place &P1, Place &P2,colonie &C){
    //cout<< "Regle1" <<endl;
    if(f.get_colonie()==P2.get_numeroColonie())return;
    C.colonie_Fourmi_meurt(P2.get_numeroColonie(),P2.get_numeroFourmi());
    P2.enleveFourmi();
    deplaceFourmi(f, P1, P2);
}

bool tue_condition(Fourmi f, Place P1, Place P2){
    return P1.get_numeroColonie() != P2.get_numeroColonie() and P2.get_numeroFourmi() != -1; 
}
 
//2)
void prendSucre(Fourmi &f, Place &P1, Place &P2){
  //cout<< "Regle2" <<endl;
  f.prendSucre();
  P2.diminuePheroSucre();
  if(P2.get_pheroSucre()==0)P2.enleveSucre();
  P1.posePheroSucre(f.get_colonie());
}

bool prendSucre_condition(Fourmi f, Place P1, Place P2){
  return (not(f.porteSucre()) and P2.contientSucre());   
}

//3)
void poseSucre(Fourmi &f, Place &P1, Place &P2){ //, int &nbSucreNid à peut etre rajouter
  f.poseSucre();                              // Dans ce cas la, le rajouter dans le switch
  //nbSucreNid ++; 
}
void poseSucre(Fourmi &f, Place &P1, Place &P2,colonie &C){ 
  //cout<< "Regle3" <<endl;
  f.poseSucre();                              
  C.ajoute_Sucre(f.get_colonie()); 
}

bool poseSucre_condition(Fourmi f, Place P1, Place P2){
  return f.porteSucre() and P2.contientNid() and P2.get_numeroColonie()==f.get_colonie();   
}

//4)
void chercheNid(Fourmi &f, Place &P1, Place &P2){
  //cout<< "Regle4" <<endl;
  deplaceFourmi(f, P1, P2);
  P2.posePheroSucre(f.get_colonie());
}

bool chercheNid_condition(Fourmi f, Place P1, Place P2){
  return f.porteSucre() and estVide(P2) and estPlusLoinNid(P1,P2,f.get_colonie());   
}

//5)
void chercheSucreSurPiste(Fourmi &f, Place &P1, Place &P2){
  //cout<< "Regle5" <<endl;
  deplaceFourmi(f, P1, P2);
}

bool chercheSucreSurPiste_condition(Fourmi f, Place P1, Place P2){
  return not(f.porteSucre()) and P1.estSurUnePiste(f.get_colonie()) and estVide(P2) and P2.estSurUnePiste() and estPlusLoinNid(P2, P1,f.get_colonie());
}

//6)    
void cherchePiste(Fourmi &f, Place &P1, Place &P2){
  //cout<< "Regle6" <<endl;
  deplaceFourmi(f, P1, P2);
}

bool cherchePiste_condition(Fourmi f, Place P1, Place P2){
 return not(f.porteSucre()) and estVide(P2) and P2.estSurUnePiste(f.get_colonie());
}

//7)
void chercheSansPiste(Fourmi &f, Place &P1, Place &P2){
  //cout<< "Regle7" <<endl;
  deplaceFourmi(f, P1, P2);
}

bool chercheSansPiste_condition(Fourmi f, Place P1, Place P2){
  return not(f.porteSucre()) and estVide(P2);   
}
    
/*
void mettreAJourEnsFourmi(Grille &g, vector<Fourmi> &F){
    for(size_t i=0;i<F.size();i++){
      mettreAJourFourmi(g, F[i]);
      Check_Fourmi_Grille(g,F);
      Check_Grille_Fourmi(g,F);
    }
}


void mettreAJourFourmiSansColonie(Grille &g,vector<Fourmi> &F){
    for(size_t k = 0; k<F.size();k++){
        Coord c = F[k].coords();
        Place P = g.chargePlace(c);
        EnsCoord v = voisines(c);
        
        for(int i = 1; i < 8; i++){
            for(Coord cv : v.get_tab()){
              Place PlaceVoisin = g.chargePlace(cv);
              if(condition_n(i, F[k], P, PlaceVoisin,0)){
                 for(Coord cv : v.get_tab()){
                     Place PlaceVoisin = g.chargePlace(cv);
                     if(!condition_n(i, F[k], P, PlaceVoisin,0))v.supprime(cv);
                 }
                 Place PlaceVoisin = g.chargePlace(v.choixHasard());
                 action_n(i, F[k], P, PlaceVoisin);
                 g.rangePlace(P);
                 g.rangePlace(PlaceVoisin);
                 break;
                  }
            }
          }
    }
}
*/
void mettreAJourFourmiAvecColonie(Grille &g,colonie &C){
    srand(time(NULL));
    for(int j =0 ; j<C.get_nbColonie();j++){
        if(j >= C.taille())throw runtime_error("Pas assez de colonie");
        vector<Fourmi> F = C.get_colonie_ind(j);
        if(C.taille()==0)continue;
        for(size_t k = 0; k<F.size();k++){
            bool FaitRegle = false;
            if(!F[k].estVivant())continue;
            Coord c = F[k].coords();
            Place P = g.chargePlace(c);
            EnsCoord v = voisines(c);
            for(int i = 1; i < 8; i++){
                for(Coord cv : v.get_tab()){
                    Place PlaceVoisin = g.chargePlace(cv);
                    if(condition_n(i, F[k], P, PlaceVoisin)){
                        for(Coord cv : v.get_tab()){
                            Place PlaceVoisin = g.chargePlace(cv);
                            if(!condition_n(i, F[k], P, PlaceVoisin))v.supprime(cv);
                        }
                        Place PlaceVoisin = g.chargePlace(v.choixHasard());
                        action_n(i, F[k], P, PlaceVoisin,C);
                    
                        g.rangePlace(P);
                        g.rangePlace(PlaceVoisin);
                        FaitRegle = true;
                        break;
                    }      
                }
                if(FaitRegle)break;
            }
        }
        C.colonie_remplace(F,j);
        Check_Fourmi_Grille(g,C);
        Check_Grille_Fourmi(g,C);
    }
}

bool condition_n(int r, Fourmi f, Place P1, Place P2){
  switch(r) {
      case 1: return tue_condition( f,P1,P2); break;
      case 2: return prendSucre_condition(f, P1, P2); break;
      case 3: return poseSucre_condition(f, P1, P2); break;
      case 4: return chercheNid_condition(f, P1, P2); break;
      case 5: return chercheSucreSurPiste_condition(f, P1, P2); break;
      case 6: return cherchePiste_condition(f, P1, P2); break;
      case 7: return chercheSansPiste_condition(f, P1, P2); break;
      default: throw invalid_argument("Regle 1 utlisée, mais pas implantée ou regle inexistante"); break;    
  }
}

void action_n(int r, Fourmi &f, Place &P1, Place &P2,colonie &C){
  //cout<<f<<endl;
  switch(r) {
      case 1: tue(f,P1,P2,C); break;
      case 2: prendSucre(f, P1, P2); break;
      case 3: poseSucre(f, P1, P2,C); break;
      case 4: chercheNid(f, P1, P2); break;
      case 5: chercheSucreSurPiste(f, P1, P2); break;
      case 6: cherchePiste(f, P1, P2); break;
      case 7: chercheSansPiste(f, P1, P2); break;
      default: throw invalid_argument("Regle 1 utlisée, mais pas implantée ou regle inexistante"); break;    
  }
  //cout<<f<<endl;
}

void NouvelleFourmi(Grille &g,colonie &C){
    for(int i=0;i<C.get_nbColonie();i++){
        bool k = false;
        if(C.get_Sucre_ind(i)>=10){
            EnsCoord a = C.get_coord_Nid(i);
            C.SucreReset(i);
            for(Coord c1:a.get_tab()){
                EnsCoord PVoisin = voisines(c1);
                for(Coord c2:PVoisin.get_tab()){
                    Place P = g.chargePlace(c2);
                    if(estVide(P)){
                        k=true;
                        int s = C.get_colonie_ind(i).size();
                        C.ajoute_Fourmi(c2,i);
                        P.poseFourmi(C.get_colonie_ind(i)[s]);
                        g.rangePlace(P);
                        break;
                    }
                }
                if(k)break;
            }
        }
    }
}


TEST_CASE("Grille 1 Colonie"){
    /*
    Grille g = Grille();
    vector<Coord> h =  {{9, 9}, {9, 10},{10,9},{10,10}};
    vector<Coord> PourF = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    //vector<Coord> PourF = {{7,5}};
    vector<Coord> PourSucre = {{10,2},{10,18},{6,5}};
    EnsCoord j(h);
    EnsCoord F1(PourF);
    EnsCoord S(PourSucre);
    placeNid(g, j,0);
    lineariserPheroNid(g,0);
    g.affichePheroNid();
    vector<Fourmi> F = creeTabFourmi(F1);
    placeFourmis(g,F);
    placeSucre(g,S);
    g.dessine();
    for(int i=0;i<10;i++){
        mettreAJourFourmiAvecColonie(g,F);
        g.dessine();
        g.diminuePheroSucre();
    } 
    */
    colonie k = colonie(1);
    vector<Coord> PourN1 =  {{9, 9}, {9, 10},{10,9},{10,10}};
    //vector<Coord> PourF1 = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    vector<Coord> PourF1 = {{8,8},{8,9},{9,8},{11,11}};
    vector<Coord> PourSucre = {{10,2},{10,5},{10,18},{5,10},{7,18},{14,9},{7,7}};
    EnsCoord N1(PourN1);
    EnsCoord F1(PourF1);
    EnsCoord S(PourSucre);
    vector<Fourmi> FC1 = creeTabFourmi(F1);
    k.ajoute_colonie(FC1);
    k.ajoute_Nid_colonie(N1);
    Grille g = initialiseGrille(k,S,1);
    lineariserPheroNid(g,0);
    //g.dessine();
    for(int i=0;i<30;i++){
        mettreAJourFourmiAvecColonie(g,k);
        NouvelleFourmi(g,k);
        //Affiche_NbFourmiColonie(k);
        //cout<<k.get_Sucre_ind(0)<<endl;
        //g.dessine();
        g.diminuePheroSucre();
    } 
}

TEST_CASE("Grille 2 Colonie"){
    
    colonie k = colonie(2);
    vector<Coord> PourN1 =  {{9, 9}, {9, 10},{10,9},{10,10}};
    vector<Coord> PourN2 =  {{3, 3}, {3, 4},{4,3},{4,4}};
    vector<Coord> PourF1 = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    vector<Coord> PourF2 = {{2,2},{2,3},{3,2},{5,5},{5,4},{4,5},{3,5},{4,2},{2,4},{5,2},{2,5},{5,3}};
    vector<Coord> PourSucre = {{10,2},{10,5},{10,18},{5,10},{7,18},{14,9}};
    EnsCoord N1(PourN1);
    EnsCoord N2(PourN2);
    EnsCoord F1(PourF1);
    EnsCoord F2(PourF2);
    EnsCoord S(PourSucre);
    vector<Fourmi> FC1 = creeTabFourmi(F1);
    vector<Fourmi> FC2 = creeTabFourmi(F2);
    k.ajoute_colonie(FC1);
    k.ajoute_colonie(FC2);
    k.ajoute_Nid_colonie(N1);
    k.ajoute_Nid_colonie(N2);
    Grille g = initialiseGrille(k,S,2);
    lineariserPheroNid(g,0);
    lineariserPheroNid(g,1);
    //g.affichePheroNid(0);
    //cout<<endl;
    //g.affichePheroNid(1);
    //g.dessine();
    for(int i=0;i<100;i++){
        mettreAJourFourmiAvecColonie(g,k);
        NouvelleFourmi(g,k);
        //Affiche_NbFourmiColonie(k);
        //cout<<k.get_Sucre_ind(0)<<endl;
        //cout<<k.get_Sucre_ind(1)<<endl;
        //g.dessine();
        g.diminuePheroSucre();
    } 
    //g.dessine();
    
}


