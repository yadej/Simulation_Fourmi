#include <iostream>     // pour cout
#include <iomanip>      // pour setfill, setw
#include <sstream>      // pour ostringstream
#include <fstream>      // pour ofstream
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Coord.hpp"
#include "Fourmi.hpp"
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
                    r = 0;
                    g = 255;
                    b = 0;
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }else{
                    r = 0;
                    g = 0;
                    b = 0;
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }
                }
            }
            fic<<endl;
        }
     }
}
int main (){
    Grille g = Grille();
    vector<Coord> h =  {{9, 9}, {9, 10},{10,9},{10,10}};
    vector<Coord> PourF = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    //vector<Coord> PourF = {{7,6}};
    vector<Coord> PourSucre = {{10,2},{10,18},{8,6}};
    EnsCoord j(h);
    EnsCoord F1(PourF);
    EnsCoord S(PourSucre);
    vector<Fourmi> F = creeTabFourmi(F1);
    placeNid(g, j);
    placeFourmis(g,F);
    placeSucre(g,S);
    lineariserPheroNid(g);
    DessinerGrille(g, 8);
    return 0;
}
