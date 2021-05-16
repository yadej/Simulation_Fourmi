#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Coord.hpp"
#include "Fourmi.hpp"
#include "Place.hpp"
#include "Grille.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

namespace SimFourmi{
    const int FPS = 15;
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;
    const int CELL_SIZE = 20;
    const int CELL_WIDTH = WINDOW_WIDTH / CELL_SIZE;
    const int CELL_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

    const sf::Color White     (255, 255, 255);
    const sf::Color Black     (  0,   0,   0);
    const sf::Color Blue      (  0,   0, 255);
    const sf::Color BlueNid   (  0,   0, 200);
    const sf::Color BlueTrail (  0,   0, 128);
    const sf::Color Red       (255,   0,   0);
    const sf::Color RedNid    (200,   0,   0);
    const sf::Color RedTrail  (128,   0,   0);
    const sf::Color Green     (  0, 255,   0);
    const sf::Color GreenNid  (  0, 200,   0);
    const sf::Color GreenTrail(  0, 128,   0);
    const sf::Color Jaune     (255, 255,   0);
    const sf::Color JauneNid  (200, 200,   0);
    const sf::Color JauneTrail(128, 128,   0);
    const sf::Color DarkGray ( 40,  40,  40);

    void drawGrid(sf::RenderWindow& window){
        sf::RectangleShape rectVerticale(sf::Vector2f(1, WINDOW_HEIGHT));
        rectVerticale.setFillColor(DarkGray);
        for (int x = 0; x < WINDOW_WIDTH; x += CELL_SIZE){
            rectVerticale.setPosition(x, 0);
            window.draw(rectVerticale);
        }

        sf::RectangleShape rectHorizontal(sf::Vector2f(WINDOW_WIDTH, 1));
        rectHorizontal.setFillColor(DarkGray);
        for (int y = 0; y < WINDOW_HEIGHT; y += CELL_SIZE){
            rectHorizontal.setPosition(0, y);
            window.draw(rectHorizontal);
        }
    }
    void drawNid(sf::RenderWindow& window, const colonie& c){
        sf::RectangleShape outerSegment(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        outerSegment.setFillColor(Blue);

        //sf::RectangleShape innerSegment(sf::Vector2f(CELL_SIZE - 8, CELL_SIZE - 8));
        //innerSegment.setFillColor(Green);
        for(int i = 0 ; i<c.Nidtaille();i++ ){
            if (i==0)outerSegment.setFillColor(BlueNid);
            if (i==1)outerSegment.setFillColor(RedNid);
            if (i==2)outerSegment.setFillColor(GreenNid);
            if (i==3)outerSegment.setFillColor(JauneNid);
            for(const Coord& s : c.get_coord_Nid(i).get_tab()){
                outerSegment.setPosition(s.get_lig() * CELL_SIZE, s.get_col() * CELL_SIZE);
                window.draw(outerSegment);
            }
        }
    }
    void drawFourmi(sf::RenderWindow& window, const colonie& c){
        sf::RectangleShape outerSegment(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        outerSegment.setFillColor(Blue);

        //sf::RectangleShape innerSegment(sf::Vector2f(CELL_SIZE - 8, CELL_SIZE - 8));
        //innerSegment.setFillColor(Green);
        for(int i = 0 ; i<c.taille();i++ ){
            if (i==0)outerSegment.setFillColor(Blue);
            if (i==1)outerSegment.setFillColor(Red);
            if (i==2)outerSegment.setFillColor(Green);
            if (i==3)outerSegment.setFillColor(Jaune);
            for(const Fourmi& F : c.get_colonie_ind(i)){
                if(!F.estVivant())continue;
                outerSegment.setPosition(F.coords().get_lig() * CELL_SIZE, F.coords().get_col() * CELL_SIZE);
                window.draw(outerSegment);
            }
        }
    }
    void drawSucre(sf::RenderWindow& window, const Grille& g){
        for(int i=0; i<TAILLEGRILLE;i++){
            for(int j=0; j<TAILLEGRILLE;j++){
                if(!g.chargePlace(Coord(i,j)).contientSucre())continue;
                sf::RectangleShape SucreShape(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                SucreShape.setFillColor(White);
                SucreShape.setPosition(i * CELL_SIZE + 1, j * CELL_SIZE + 1);
                window.draw(SucreShape);
            }
        }
    }
    void drawTrail(sf::RenderWindow& window, const Grille& g){

        for(int i=0; i<TAILLEGRILLE;i++){
            for(int j=0; j<TAILLEGRILLE;j++){
                Place P = g.chargePlace(Coord(i,j));
                int pheroSucreMax = 0;
                int colonieMax = -1;
                sf::RectangleShape TrailShape(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                for(size_t m = 0;m<P.get_pheroSucre().size();m++){
                     if(P.get_pheroSucre(m) > pheroSucreMax){
                            pheroSucreMax = P.get_pheroSucre(m);
                            colonieMax = m;
                     }
                }
                if(colonieMax==-1)continue;
                switch(colonieMax){
                    case 0: TrailShape.setFillColor(sf::Color{ 0, 0,sf::Uint8(pheroSucreMax/2)}); break;
                    case 1: TrailShape.setFillColor(sf::Color{ sf::Uint8(pheroSucreMax/2), 0, 0 }); break;
                    case 2: TrailShape.setFillColor(sf::Color{ 0, sf::Uint8(pheroSucreMax/2), 0 }); break;
                    case 3: TrailShape.setFillColor(sf::Color{ sf::Uint8(pheroSucreMax/2),sf::Uint8(pheroSucreMax/2),0}); break;
                    default: throw runtime_error("Colonie invalide affichage");
                }
                TrailShape.setPosition(i * CELL_SIZE + 1, j * CELL_SIZE + 1);
                window.draw(TrailShape);
            }
        }

    }
    void runGame(sf::RenderWindow& window,Grille& g,colonie& c){
        int a = 0;
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        sf::Vector2i Position = sf::Mouse::getPosition(window);
                        int x = int(Position.x/CELL_SIZE);
                        int y = int(Position.y/CELL_SIZE);
                        Place P = g.chargePlace(Coord(x,y));
                        if(estVide(P))P.poseSucre();
                        g.rangePlace(P);
                    }
                }

            }
            mettreAJourFourmiAvecColonie(g,c);
            NouvelleFourmi(g,c);
            if(a%20==0)g.ajouteSucreAlea();
            g.diminuePheroSucre();
            drawGrid(window);
            drawTrail(window,g);
            drawNid(window,c);
            drawFourmi(window,c);
            drawSucre(window,g);
            window.display();
            window.clear();
            a++;
            }

    }



}

int main()
{
    sf::VideoMode videoMode(SimFourmi::WINDOW_WIDTH, SimFourmi::WINDOW_HEIGHT);
    sf::RenderWindow window(videoMode, "SimFourmi");
    window.setFramerateLimit(SimFourmi::FPS);

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

    while (window.isOpen())
    {
        SimFourmi::runGame(window,g,k);
    }
}
