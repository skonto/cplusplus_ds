#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "trie.h"
/*
For reference
unsigned int Factorial( unsigned int number ) {
  return number > 1 ? Factorial(number-1)*number : 1;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}*/


TEST_CASE("Trie initialization2", "Trie2"){

ds::Trie<int> * val = new ds::Trie<int>();

REQUIRE( (* val).size() == 0);

std::string name1 = "stavros";
std::string name2 = "giorgos";
std::string name3 = "nikos";

(*val).add(name1, 1);

(*val).add(name2, 2);

(*val).add(name3, 3);

REQUIRE( (*val).size() == 3);

std::set<int> ret1=(*val).remove(name1);

REQUIRE( ret1.size() == 1);

REQUIRE( (*val).size() == 2);

std::set<int> ret2=(*val).remove(name2);

REQUIRE( ret2.size() == 1);

REQUIRE( (*val).size() == 1);

std::set<int> ret3=(*val).remove(name3);

REQUIRE( ret3.size() == 1);

REQUIRE( (*val).size() == 0);

delete val;

}

