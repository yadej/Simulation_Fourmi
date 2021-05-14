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
                    }else if(P.get_numeroColonie() == 2){
                        r = 255;
                        g = 255;
                        b = 0;
                    }else if(P.get_numeroColonie() == 3){
                        r = 255;
                        g = 0;
                        b = 255;
                    }else{
                        r = 255;
                        g = 255;
                        b = 128;
                    }
                    fic<<r<<" "<<g<<" "<<b<<"  ";
                }else{
                    /*
                    if(P.get_pheroSucre(0)>0){
                        r = 0;
                        g = 128;
                        b = 0;
                    }else if(P.get_pheroSucre(1)>0){
                        r = 128;
                        g = 0;
                        b = 0;
                    }else if(P.get_pheroSucre(2)>0){
                        r = 128;
                        g = 128;
                        b = 0;
                    }else if(P.get_pheroSucre(3)>0){
                        r = 128;
                        g = 0;
                        b = 128;
                    }else{
                        r = 0;
                        g = 0;
                        b = 0;
                    }
                    */
                    int pheroSucreMax = 0;
                    int colonieMax = -1;
                    for(int m = 0; m < 4; m++){
                        if(P.get_pheroSucre(m) > pheroSucreMax){
                            pheroSucreMax = P.get_pheroSucre(m);
                            colonieMax = m;
                        }
                    }
                    switch(colonieMax){
                        case -1: r = 0; g = 0; b = 0; break;
                        case 0: r = 0; g = int(pheroSucreMax)/2; b = 0; break;
                        case 1: r = int(pheroSucreMax)/2; g = 0; b = 0; break;
                        case 2: r = int(pheroSucreMax)/2; g = int(pheroSucreMax)/2; b = 0; break;
                        case 3: r = int(pheroSucreMax)/2; g = 0; b = int(pheroSucreMax)/2; break;
                        default: throw runtime_error("Colonie invalide affichage");
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
    colonie k = colonie(4);
    vector<Coord> PourN1 =  {{9, 9}, {9, 10},{10,9},{10,10}};
    vector<Coord> PourN2 =  {{35, 35}, {34, 35},{35,34},{34,34}};
    vector<Coord> PourN3 =  {{25, 30}, {24, 30},{25,29},{24,29}};
    vector<Coord> PourN4 =  {{20, 37}, {21, 37},{20,38},{21,38}};
    vector<Coord> PourF1 = {{8,8},{8,9},{9,8},{11,11},{11,10},{10,11},{9,11},{10,8},{8,10},{11,8},{8,11},{11,9}};
    vector<Coord> PourF2 = {{33,33},{33,35},{33,36},{36,33},{35,33},{34,33},{33,34},{36,34},{34,36},{35,36},{36,35},{36,36}};
    vector<Coord> PourF3 = {{23,28},{23,29},{23,30},{23,31},{24,28},{24,31},{25,31},{25,28},{26,30},{26,28},{26,31},{26,29}};
    vector<Coord> PourF4 = {{19,36},{19,37},{19,38},{19,39},{20,36},{20,39},{21,36},{21,39},{22,36},{22,37},{22,38},{22,39}};
    vector<Coord> PourSucre = {{10,2},{10,5},{10,18},{5,10},{7,18},{14,9},{7,7},{25,25},{34,38},{29,40},{27,36},{39,25},{16,25},{40,45},{40,46},{6,45},{15,45},{38,40},{19,45},{41,45}};
    EnsCoord N1(PourN1);
    EnsCoord N2(PourN2);
    EnsCoord N3(PourN3);
    EnsCoord N4(PourN4);
    EnsCoord F1(PourF1);
    EnsCoord F2(PourF2);
    EnsCoord F3(PourF3);
    EnsCoord F4(PourF4);
    EnsCoord S(PourSucre);
    vector<Fourmi> FC1 = creeTabFourmi(F1);
    vector<Fourmi> FC2 = creeTabFourmi(F2);
    vector<Fourmi> FC3 = creeTabFourmi(F3);
    vector<Fourmi> FC4 = creeTabFourmi(F4);
    k.ajoute_colonie(FC1);
    k.ajoute_colonie(FC2);
    k.ajoute_colonie(FC3);
    k.ajoute_colonie(FC4);
    k.ajoute_Nid_colonie(N1);
    k.ajoute_Nid_colonie(N2);
    k.ajoute_Nid_colonie(N3);
    k.ajoute_Nid_colonie(N4);
    Grille g = initialiseGrille(k,S,4);
    lineariserPheroNid(g,0);
    lineariserPheroNid(g,1);
    lineariserPheroNid(g,2);
    lineariserPheroNid(g,3);
    //g.dessine();
    for(int i=0;i<100;i++){
        mettreAJourFourmiAvecColonie(g,k);
        NouvelleFourmi(g,k);
        DessinerGrille(g,4);
        g.diminuePheroSucre();
    } 
    return 0;
}
