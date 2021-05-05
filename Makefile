CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= tests

all: tests
# Regle generique
tests: tests.o coords.o Fourmi.o Place.o
	$(CXX) -o $@ $^ $(LDFLAGS)
    
Affichage: Affichage.o coords.o Fourmi.o Place.o
	$(CXX) -o $@ $^ $(LDFLAGS)    
    
tests.o:test.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Affichage.o:Affichage.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

coords.o: Coord.cpp Coord.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Fourmi.o: Fourmi.cpp Fourmi.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

Place.o: Place.cpp Place.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC_FILES)