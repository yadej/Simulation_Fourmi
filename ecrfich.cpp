#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "colonie.hpp"
#include "Place.hpp"
#include "Grille.hpp"



using namespace std;
// variable globale permettant de creer des noms de fichiers differents
int compteurFichier = 0;
// action dessinant un damier
void dessinerDamier(){
  int i,j;
  int r,g,b;
  ostringstream filename;
  // creation d'un nouveau nom de fichier de la forme img347.ppm
  filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
  compteurFichier++;
  cout << "Ecriture dans le fichier : " << filename.str() << endl;
  // ouverture du fichier
  ofstream fic(filename.str(), ios::out | ios::trunc);
  // ecriture de l'entete
  fic << "P3" << endl
      << 4 << " " << 4 << " " << endl
      << 255 << " " << endl;
  // ecriture des pixels
  for (i = 0; i < 4; i++){
      for (j = 0; j < 4; j++){
        // calcul de la couleur
        if (i == j) { r = 255; g = 0; b = 0; }
        else { r = 0; g = 255; b = 0; }
        // ecriture de la couleur dans le fichier
        fic << r << " " << g << " " << b << "    ";
      }
    // fin de ligne dans l'image
    fic << endl;
  }
  // fermeture du fichier
  fic.close();
}

void DessinerGrille(Grille g1,int taille){
    int r,g,b;
    ostringstream filename;
    filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
    compteurFichier++;
    cout << "Ecriture dans le fichier : " << filename.str() << endl;
    // ouverture du fichier
    ofstream fic(filename.str(), ios::out | ios::trunc);
     fic << "P3" << endl
         << TAILLEGRILLE * taille << " " << TAILLEGRILLE * taille<< " " << endl
         << 255 << " " << endl;
     // ecriture des pixels
     for (int i = 0; i < TAILLEGRILLE; i++){
        //on erit la ligne *taille pour qu'on puisse voir ou sont les choses
        for(int k=0; k < taille; k++){
            for (int j = 0; j < TAILLEGRILLE; j++){
                Coord k(i,j);
                Place P = g1.chargePlace(k);
                for(int a=0;a<taille;a++){
                if(P.contientNid()){
                    r = 0;
                    g = 0;
                    b = 255;
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }else if(P.contientSucre()){
                    r = 255;
                    g = 255;
                    b = 255;
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }else if(P.get_numeroFourmi()!=-1){
                    if(P.get_numeroColonie() == 0){
                        r = 0;
                        g = 255;
                        b = 0;
                    }else if(P.get_numeroColonie() == 1){
                        r = 255;
                        g = 0;
                        b = 0;
                    }else{// if(P.get_numeroColonie() == 3){
                        r = 128;
                        g = 128;
                        b = 0;
                    }
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }else{
                    if(P.get_pheroSucre(0)>0){
                        r = 0;
                        g = 128;
                        b = 0;
                    }else if(P.get_pheroSucre(1)>0){
                        r = 128;
                        g = 0;
                        b = 0;
                    }else{
                        r = 0;
                        g = 0;
                        b = 0;
                    }
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }
                }
            }
            fic<<endl;
        }
     }
}
int main (){
    colonie k = colonie(2);
    vector<Coord> PourN1 =  {{9, 9}, {9, 10},{10,9},{10,10}};
    vector<Coord> PourN2 =  {{3, 3}, {3, 4},{4,3},{4,4}};
    vector<Coord> PourF1 = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    vector<Coord> PourF2 = {{2,2},{2,3},{3,2},{5,5},{5,4},{4,5},{3,5},{4,2},{2,4},{5,2},{2,5},{5,3}};
    vector<Coord> PourSucre = {{10,2},{10,5},{10,18},{5,10},{7,18},{14,9},{7,7}};
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
    //g.dessine();
    for(int i=0;i<100;i++){
        mettreAJourFourmiAvecColonie(g,k);
        NouvelleFourmi(g,k);
        DessinerGrille(g,8);
        g.diminuePheroSucre();
    } 
    return 0;
}
