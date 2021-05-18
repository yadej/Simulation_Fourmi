#ifndef Fourmi_HPP
#define Fourmi_HPP
#include "Coord.hpp"
#include <vector>
#include <string>
#include <iostream>

class Fourmi{
    Coord _coord;// Les coord de la fourmi
    int _indice;    // Son indice (unique pour sa colonie)
    int _colonie;// Le numéro de sa colonie
    bool _sucre; // Si elle porte du sucre
    bool _Vivant;// Si elle est vivante
    public:
    //Constructeur
    //* @param[out] f : la fourmi
    //* @param[in] a : coordonnee de la fourmi
    //* @param[in] v : son numero
    //* vivante et ne portant pas de sucre
    Fourmi(Coord a,int indice);
    
    //* @param[in] c : coordonnee de la fourmi
    //* @param[in] indice : son numero
    //* @param[in] colonie : sun num de colonie
    //* @param[out] f : la fourmi vivante
    //* et ne portant pas de sucre
    Fourmi(Coord a,int indice,int colonie);
    //methode
    
//* @param[out] c : [Coord] la coord fourmi
    Coord coords()const;
    
    //* @param[out] i : [int] l'indice de la fourmi
    int num()const;
    
    //* @param[out] c : [int] le numéro de la colonie de la fourmi
    int get_colonie()const;
    
    //* @param[out] : [bool] true si elle est vivante, false sinon
    bool estVivant()const;
    
    //* @param[out] : [bool] true si elle porte du sucre, false sinon
    bool porteSucre()const;
    
    // Méthodes
    
    // Tue une fourmi
    void meurt();
    
    // La fourmi porte du sucre
    void prendSucre();
    
    // La fourmi ne porte plus de sucre
    void poseSucre();
    
    //* @param[in] p : coordonnee de 
    //* de déplacement de la fourmi
    //* [error] lève une erreur si la coord
    //* n'est pas valide ou située trop loin
    void deplace(Coord p);
        
    //* @param[in] i : numéro de la
    //* nouvelle colonie de la fourmi
    //* [error] lève une erreur si le num
    //* de colonie n'est pas valide
    void change_colonie(int i);

};
// Fonctions

//* @param[in] c : sun num de colonie
//* @param[out] k : un vecteur de fourmis constitué
//* des coordoonées en paramètre. Les fourmi sont vivantes
//* ne portent pas de sucre et n'appartiennent à aucun colonie
std::vector<Fourmi> creeTabFourmi(EnsCoord c);

// Surcharge d'opérateur

// Affichage complet d'une fourmi et ses attribus
std::ostream &operator<<(std::ostream &out, const Fourmi &fourmi);




#endif  
