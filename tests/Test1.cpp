#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "trie.h"

TEST_CASE("Trie initialization", "Trie"){

ds::Trie<int> * val = new ds::Trie<int>();

REQUIRE( (* val).size() == 0);

(*val).add("hello", 1);

REQUIRE( (*val).contains("helloss") == false);

REQUIRE( (*val).contains("hello") == true);

REQUIRE( (*val).contains("h") == false);

REQUIRE( (*val).contains("zzzzzzzzz") == false);

delete val;

}
