#ifndef COLONIE_HPP
#define COLONIE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"

class colonie{
    // Attribus
   
    //* Un vecteur de vecteur contenant les
    //* fourmis de chaque colonie
    //* exemple: C[0] contient les fourmis
    //* de la colonie 0, C[1] celle de la 1
    std::vector<std::vector<Fourmi>> C_;   
    
    //* Un vecteur contenant le nombre de
    //* sucre dans chaque nid de colonie
    std::vector<int> NSucre_;
    
    //* Un vecteur contenant les coordonnées
    //* du nid de chaque colonie
    std::vector<EnsCoord> Nid_;
    
    //* Le nombre total de colonies
    int nbColonie_;
    public:
    //Constructeurs
    
    //* @param[in] colonie : le nombre colonies
    //* @param[out] : une colonie, avec n nombre
    //* de colonies différentes, sans fourmi, sans
    //* coord de nid et avec O de sucre pour 
    //* chaque colonie
    colonie(int colonie);
    //methodes
    
    //* @param[out] : le nombre de colonies non vide
    int taille()const;
    
    //* @param[out] : le nombre de nids
    int Nidtaille()const;
    
    //* @param[in] : le numéro de la colonie 
    //* @param[out] : Un vecteur de fourmis contenant
    //* les fourmis de la colonie ind
    //* [error] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur au
    //* nombre de colonies
    std::vector<Fourmi> get_colonie_ind(int ind)const;
    
    //* @param[in] : le numéro de la colonie 
    //* @param[out] : Le nombre de sucre dans
    //* le nid de la colonie ind
    //* [error] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur au
    //* nombre de colonies
    int get_Sucre_ind(int ind)const;
    
    //* @param[in] : le numéro de la colonie 
    //* @param[out] : Un ensemble de coord contenant
    //* les coordoonées du nid de la colonie ind
    //* [error] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur au
    //* nombre de colonies
    EnsCoord get_coord_Nid(int ind)const;
    
    //* @param[out] : Le nombre de colonie max
    int get_nbColonie()const;
    
    // Méthodes
    
    //* @param[in] : Un vecteur de fourmis
    //* ajoute une colonie contenant les fourmis
    //* en entrée, ajuste leur numéro de colonie
    //* au plus petit numéro de colonie vide
    //* [error] : lève une erreur si il n'y a déjà
    //* que des colonies non vides
    void ajoute_colonie(std::vector<Fourmi> F);
    
    //* @param[in] : La coord de la fourmi
    //* @param[in] : Indice colonie
    //* ajoute une fourmi à la colonie ind
    //* [error] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur 
    //* au nombre maximal de colonies
    void ajoute_Fourmi(Coord Ca,int ind);
    
    //* @param[in] : Un ensemble de coord du nid
    //* ajoute des coord du nid de la première
    //* colonie n'ayant pas de coord de nird
    //* [error] : Toutes les colonies ont déjà des
    //* coord de nid
    void ajoute_Nid_colonie(EnsCoord Ca);
    
    //* @param[in] : indice de la colonie
    //* ajoute du sucre dans le nid de la colonie
    //* ind
    //* [error] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur 
    //* au nombre maximal de colonies
    void ajoute_Sucre(int ind);
    
    //* @param[in] : Un vecteur de fourmis
    //* @param[in] : L'indice de la colonie
    //* Change les fourmis d'une colonie par celle
    //* en entrée, ajuste leur numéro de colonie
    //* à ind
    void colonie_remplace(std::vector<Fourmi>, int ind);
    
    //* @param[in] : Un numéro de colonie
    //* @param[in] : L'indice de la fourmi
    //* Tue la fourmi d'indice pos, de la colonie ind
    //* [error1] : lève une erreur si le numéro de
    //* colonie est inférieur à 0 ou supérieur 
    //* au nombre maximal de colonies
    //* [error2] : lève une erreur si le numéro de
    //* ma fourmi est inférieur à 0 ou supérieur au
    //* nombre de fourmis dans la colonie ind
    void colonie_Fourmi_meurt(int ind, int pos);
    
    //* @param[in] : Un numéro de colonie
    //* @param[out] : true si le nid de la
    //* colonie ind contient 10 sucres ou plus
    //* et diminue son nombre de sucre de 10
    //* return false sinon et ne fait rien
    bool SucreReset(int ind);

    
};

// Affichage

//* @param[in] : Un numéro de colonie
//* Affiche le num de la colonie ainsi que
//* le nombre de fourmis vivantes qu'elle contient

void Affiche_NbFourmiColonie(colonie C);


#endif