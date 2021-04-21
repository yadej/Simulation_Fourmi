CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= tests

all: tests
# Regle generique
tests: tests.o coords.o
	$(CXX) -o $@ $^ $(LDFLAGS)
    
tests.o:test.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

coords.o: Coord.cpp Coord.hpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC_FILES)