#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"

class Grille{
  // Attribut
    
  //* Un vecteur de vecteur contenant des places
  std::vector<std::vector<Place>> tab_;
    
  public:
    
  // Constructeur

  //* @param[out] : Une grille de taille
  //* TAILLEGRILLE x TAILLEGRILLe, avec
  //* que des places vides
  Grille();
    
  //* @param[in] : nbColonie, le nombre de colonies
  //* @param[out] : Une grille de taille
  //* TAILLEGRILLE x TAILLEGRILLe, avec
  //* que des places vides, sauf qu'elles ont
  //* leurs attribus initialisés pour nbColonies
  //* colonies
  Grille(int nbColonies);
  
  // Méthodes
         
  //* @param[out] : la hauteur de la grille
  int TailleGrille();
         
  //* @param[out] : la largeur de la grille
  int SubTailleGrille();
         
  //* @param[in] c : des coordonnées d'une place
  //* @param[out] renvoie une copie conforme de 
  //* la place de la grille en coord fourni en entrée
  Place chargePlace(Coord c) const;
         
  //* @param[in] p : une place
  //* remplace dans la grille la place
  //* correspondant aux coord de celle en entrée
  void rangePlace(Place p);
         
  //* Diminue de 5 les phéromones de sucre de 
  //* chaque place de la grille. S'ils sont déjà
  //* inférieurs à 5, alors les met à 0
  void diminuePheroSucre();
         
  //* Ajoute dans une place vide aléatoire de la
  //* grille du sucre
  void ajouteSucreAlea();
    
  //Affichage
         
  //* Affiche dans le terminal la grille.
  //* Chaque sucre est représenté par un 'S'
  //* Chaque nid est représenté par un 'N'
  //* suivi du numéro de colonie
  //* Chaque fourmi est représenté par une lettre
  //* à partir de f pour la colonie 0, puis la colonie
  //* suivante est représenté par la lettre suivante 
  //* dans l'ordre alphabétique. Puis la lettre est 
  //* suivie de l'indice de la fourmi (max 99)
  //* Si une fourmi porte un sucre, alors sa lettre
  //* apparaît en majuscule
  void dessine();
         
  //* @param[in] ind : une numéro de colonie
  //* Affiche dans le terminal chaque intensité
  //* de phéromone de sucre de chaque place de la
  //* colonie ind
  //* [error1] : lève une erreur si le num de
  //* colonie est inférieur à 0
  //* [error2] : lève une erreur si le num de 
  //* colonie est supérieur au nombre maximum de
  //* colonie
  void affichePheroSucre(int ind);
    
  //* @param[in] ind : une numéro de colonie
  //* Affiche dans le terminal chaque intensité
  //* de phéromone de nid de chaque place de la
  //* colonie ind
  //* [error1] : lève une erreur si le num de
  //* colonie est inférieur à 0
  //* [error2] : lève une erreur si le num de 
  //* colonie est supérieur au nombre maximum de
  //* colonie
  void affichePheroNid(int colonie);
};

// Fonctions pour initialiser une grille

//* @param[in] g : une grille
//* @param[in] C : une colonie
//* Place dans la grille un nid dans les
//* places spécifiées dans la colonie
//* [error1] : lève une erreur si il n'y a pas 
//* assez de coord de nid dans la colonie
//* [error2] : lève une erreur si les coord
//* spécfiées dans la colonies ne sont pas dans
//* la grille
void placeNid(Grille &g, colonie C);

//* @param[in] g : une grille
//* @param[in] C : un ensemble de coord
//* Place dans la grille un sucre dans chaque
//* coord de l'ensemble de coord
//* [error] : lève une erreur si une des coord de
//* l'ensemble de coord n'est pas dans la grille
void placeSucre(Grille &g, EnsCoord e);

//* @param[in] g : une grille
//* @param[in] C : une colonie
//* Place dans la grille les fourmis dans les
//* places spécifiées dans la colonie
//* [error1] : lève une erreur si il n'y a pas 
//* assez de vecteurs de fourmis dans la colonie
//* [error2] : lève une erreur si les coord
//* spécfiées dans la colonies ne sont pas dans
//* la grille
void placeFourmis(Grille &g, colonie C);

//* @param[in] g : une grille
//* @param[in] colonie : un numéro de colonie
//* Pour chaque place de la grille, modifie l
//* intensité des phéromones de Nid de la colonie
//* dont le numéro est spécifié en entrée de la facon
//* suivante:
//* si le phéromone de nid est déjà égal à 1 alors il le
// reste, sinon il est égal au maximum entre 0 et 
//* (1/TAILLEGRILLE) - l'intensité de phéomonone de nid
//* le plus élevé des places voisines
void lineariserPheroNid(Grille &g, int colonie);

// Méthode pour initialser la grille

//* @param[in] C : une colonie
//* @param[in] Sucre : un ens de coord pour les sucres
//* @param[in] colo : le nombre de colonies
//* @param[out] g : une grille dont on a placé les fourmis et nids
//* selon les valeurs de colonie, les sucres aux coord données par
//* l'ensemble de coord et dont ont a linearisé les phéromones de
//* nid pour chaque colonie
//* [error] : lève une erreur si le nombre de colonies est 
//* inférieur à 0 ou supérieur au nombre maximal de colonies
Grille initialiseGrille(colonie C,EnsCoord Sucre,int colo);

// Fonctions de test de grille

//* @param[in] F : un vecteur de fourmis
//* Vérifie que chaque numéro de fourmi du
//* du vecteur est égal à son indice dans
//* le vecteur de fourmis
//* [error] : lève une erreur si cette condition
//* n'est pas respectée
void Check_Ind_Fourmi(std::vector<Fourmi>F);

//* @param[in] g : une grille
//* Vérifie que chaque places de la grille
//* a pour coord les indices du tableau de
//* la grille
//* [error] : lève une erreur si cette condition
//* n'est pas respectée
void Check_Place_Grille(Grille g);

//* @param[in] g : une grille
//* @param[in] C : une colonie
//* Vérifie que chaque fourmi vivante de la grille
//* possède le même numéro et la même colonie que
//* ce qui est spécifié sur la place
//* [error1] : lève une erreur si cette condition
//* n'est pas respectée
//* [error2] : lève une erreur si il y a une colonie
//* sans aucune fourmi
void Check_Fourmi_Grille(Grille g, colonie C);

//* @param[in] g : une grille
//* @param[in] C : une colonie
//* Vérifie que chaque fourmi vivante de la grille
//* possède les même coord que la place où elle
//* se situe
//* [error] : lève une erreur si cette condition
//* n'est pas respectée
void Check_Grille_Fourmi(Grille g, colonie C);

// Les conditions et actions de déplacement des fourmis

// Règle n°1

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true si la P2 contient une fourmi d'
//* une colonie différente de celle en P2, sinon false
bool tue_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* @param[in] C : une colonie
//* Tue la fourmi située sur la place p2 et déplace
//* la fourmi f sur la place p2
void tue(Fourmi &f, Place &P1, Place &P2, colonie &C);



// Règle n°2

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true si la P2 contient du sucre et que
//* la fourmi f ne porte pas de sucre, false sinon
bool prendSucre_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* La fourmi f prend du sucre, puis l'intensité de
//* phéromone de sucre de P2 diminue de 5, si elle
//* atteint 0, enlève le sucre. Finalement la fourmi
//* pose des phéromones de sucre de sa colonie sur
//* la place où elle se situe
void prendSucre(Fourmi &f, Place &P1, Place &P2);
    
// Règle n°3

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true si la place P2 contient un nid de
//* la colonie de la fourmi f et qu'elle porte du sucre,
//* false sinon
bool poseSucre_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* @param[in] C : une colonie
//* La fourmi f enlève le sucre qu'elle portait et
//* ajoute un sucre au nid de sa colonie
void poseSucre(Fourmi &f, Place &P1, Place &P2, colonie &C);


// Règle n°4

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true si la place P2 est vide, que la
//* fourmi f porte du sucre et que l'intensité des phéromones
//* de nid de sa colonie est plus élevé sur p2 que p1, false
//* sinon
bool chercheNid_condition(Fourmi f, Place P1, Place P2);


//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* La fourmi f se déplace de la place p1 vers p2
//* puis ajoute des phéromones de sucre de sa colonie
//* sur la place p2
void chercheNid(Fourmi &f, Place &P1, Place &P2);

    
// Règle n°5

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true si la fourmi f ne porte pas de sucre, que les 
//* places p1 et p2 contienent des phéromones de sucre de la colonie 
//* de f que l'intensité des phéromones de nid de la colonie de f sont
//* moins élevés sur p2 que sur p1 et que p2 est vide, false sinon
bool chercheSucreSurPiste_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* La fourmi f se déplace de la place p1 vers p2
void chercheSucreSurPiste(Fourmi &f, Place &P1, Place &P2);

    
// Règle n°6

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true la fourmi f ne porte pas de sucre, que la
//* place p2 contient des phéromones de sucre de la colonie de f
//* et que p2 est vide, false sinon
bool cherchePiste_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* La fourmi f se déplace de la place p1 vers p2
void cherchePiste(Fourmi &f, Place &P1, Place &P2);
   
    
// Règle n°7

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de P1
//* @param[out] : true la fourmi f ne porte pas de sucre, que la
//* place p2 est vide, false sinon
bool chercheSansPiste_condition(Fourmi f, Place P1, Place P2);

//* @param[in] f : une fourmi
//* @param[in] p1 : la place où si situe la fourmi f
//* @param[in] p2 : une place voisine de p1
//* La fourmi f se déplace de la place p1 vers p2
void chercheSansPiste(Fourmi &f, Place &P1, Place &P2);

// Fonction pour déplacer les fourmis en suivant les 7 règles

//* @param[in] g : une grille
//* @param[in] c : une colonie
//* Pour chaque fourmi de chaque colonie déplace la fourmi
//* en applicant la première règlede déplacement possible, 
//* sur une des cases voisines aléatoire le permettant
//* [error] : lève une erreur si une des colonies ne
//* contient pas de fourmi
void mettreAJourFourmiAvecColonie(Grille &g, colonie &C);

//* @param[in] r : un numéro de règle
//* @param[in] f : une fourmi
//* @param[in] p1 : la place de départ de la fourmi
//* @param[in] p2 : une des cases voisines de p2
//* @param[out] true si la condition de la règle n°r
//* est validé, false sinon
//* [error] : lève une erreur si r n'est pas compris
//* entre 1 et 7 inclus
bool condition_n(int r, Fourmi f, Place P1, Place P2);

//* @param[in] r : un numéro de règle
//* @param[in] f : une fourmi
//* @param[in] p1 : la place de départ de la fourmi
//* @param[in] p2 : une des cases voisines de p2
//* La fourmi f applique l'action r
//* [error] : lève une erreur si r n'est pas compris
//* entre 1 et 7 inclus
void action_n(int r, Fourmi &f, Place&P1, Place &P2, colonie &C);

//* @param[in] g : une grille
//* @param[in] C : une colonie
//* Si le nid d'une colonie contient 10 sucres
//* ou plus, diminue ce nombre de 10, puis fait
//* appraitre une fourmi en gauche à du nid de
//* cette colonie, si ce n'est pas possible
//* car une autre fourmi, un autre nid ou un sucre
//* est présent sur cette case, essaye toutes les cas
//* dans le sens des aiguilles d'une montre autour du
//* nid. Si aucune des cases n'est disponible, aucune
//* fourmi ne nait alors
void NouvelleFourmi(Grille &g, colonie &C);



#endif // GRILLE_HPP
