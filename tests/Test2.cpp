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

(*val).add("hello", 1);
(*val).add("helloss", 1);
(*val).add("hellos", 1);

REQUIRE( (*val).contains("hello") == true);

REQUIRE( (*val).contains("h") == false);

REQUIRE( (*val).contains("zzzzzzzzz") == false);

REQUIRE( (*val).size() == 3);

(*val).remove("hello");
(*val).remove("helloss");
(*val).remove("hellos");


REQUIRE( (*val).contains("hello") == false);

REQUIRE( (*val).size() == 0);

(*val).add("h", 1);

(*val).remove("h");

REQUIRE( (*val).size() == 0);

(*val).add("asfsdfqwfwff", 1);

REQUIRE( (*val).size() == 1);

delete val;

}

/*int main(){
ds::Trie<int> * val = new ds::Trie<int>();

(*val).add("hello", 1);
(*val).add("helloss", 1);
(*val).add("hellos", 1);


(*val).remove("hello");
(*val).remove("helloss");


delete val;

return 0;
}*/
