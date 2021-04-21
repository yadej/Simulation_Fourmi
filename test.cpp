#include "Coord.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("test Coord") {
    Coord k(5,6);
    CHECK(k==Coord{5,6});
    CHECK_THROWS_AS(Coord(-2,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(21,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,60),invalid_argument);
    CHECK_THROWS_AS(Coord(-2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(20,60),invalid_argument);
}

TEST_CASE("test EnsCoord") {
    EnsCoord b({Coord(1,6),Coord(2,6),Coord(3,6),Coord(4,6)});
    CHECK(b.taille()==4);
    CHECK(b.ieme(0)==Coord{1,6});
    CHECK(b.contient(Coord{2,6}));
    CHECK(b.contient(Coord{3,6}));
    CHECK(b.contient(Coord{4,6}));
    CHECK(b.ieme(0)==Coord{1,6});
    CHECK(b.ieme(1)==Coord{2,6});
    CHECK(b.ieme(2)==Coord{3,6});
    CHECK(b.ieme(3)==Coord{4,6});
    b.ajoute(Coord{1,6});
    CHECK(b.taille()==4);
    CHECK_THROWS_AS(b.supprime(Coord(0,6)),invalid_argument);
    b.supprime(Coord(1,6));
    CHECK_FALSE(b.contient(Coord{1,6}));
    CHECK(b.get_ksize()==3);
    CHECK(b.ieme(0)==Coord{2,6});
    CHECK(b.ieme(1)==Coord{3,6});
    CHECK(b.ieme(2)==Coord{4,6});
    b.ajoute(Coord{1,6});
    b.ajoute(Coord{5,6});
    CHECK(b.taille()==5);
    CHECK(b.contient(Coord{3,6}));
    CHECK(b.ieme(0)==Coord{2,6});
    CHECK(b.ieme(1)==Coord{3,6});
    CHECK(b.ieme(2)==Coord{4,6});
    CHECK(b.ieme(3)==Coord{1,6});
    CHECK(b.ieme(4)==Coord{5,6});
    CHECK(EnsCoord{{}}.estVide());
}