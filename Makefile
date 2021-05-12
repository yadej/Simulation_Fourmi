CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= tests

all: tests
# Regle generique
tests: tests.o coords.o Fourmi.o Place.o Grille.o colonie.o
	$(CXX) -o $@ $^ $(LDFLAGS)

Affichage: Affichage.o coords.o Fourmi.o Place.o Grille.o
	$(CXX) -o $@ $^ $(LDFLAGS)
        
tests.o:test.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
    
Affichage.o:ecrfich.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
    
coords.o: Coord.cpp Coord.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Fourmi.o: Fourmi.cpp Fourmi.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
    
colonie.o: colonie.cpp colonie.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Place.o: Place.cpp Place.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)
    
Grille.o: Grille.cpp Grille.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC_FILES)