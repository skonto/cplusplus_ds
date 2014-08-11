#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "trie.h"


TEST_CASE("Trie initialization4", "Trie4"){

int numOfStrings =10;
ds::Trie<int> * val = new ds::Trie<int>();

ds::Alphabet a=(*val).getDefaultAlphabet();

ds::Alphabet::RandomCharStream*  r= ds::Alphabet::getRandomCharStream(a);

for(int i=0; i<10 ;++i){
std::string rand1=(*r).getNextRandomString(10);

(*val).add(rand1, 1);
}

REQUIRE( (*val).size() == numOfStrings);

delete val;

}

