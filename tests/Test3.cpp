#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "trie.h"

TEST_CASE("Trie initialization3", "Trie3"){

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

