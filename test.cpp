#include "Coord.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("test Constructeur") {
    Coord k(5,6);
    CHECK(k==Coord{5,6});
    CHECK_THROWS_AS(Coord(-2,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(21,6),invalid_argument);
    CHECK_THROWS_AS(Coord(2,60),invalid_argument);
    CHECK_THROWS_AS(Coord(-2,-6),invalid_argument);
    CHECK_THROWS_AS(Coord(20,60),invalid_argument);
}