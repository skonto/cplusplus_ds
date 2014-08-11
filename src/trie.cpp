// ----------------------------------------------------------------------------
// Copyright 2014 Stavros Kontopoulos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and 
// limitations under the License. 
//
// Implements all major classes for the trie implementation.
//
// Date: 05/08/2014
//
// ---------------------------------------------------------------------------

#include "trie.h"
#include <iostream>
#include <algorithm> 
#include <stdexcept>
#include <chrono>
#include <random>

//ALPHABET

void printFunction(char i) {  // function:
	std::cout << i << ' ';
}

ds::Alphabet::Alphabet(char a[], int size) {
	this->alph = std::vector<char>(a, a + size);
	std::map<char, int> temp;
	std::vector<char>& v = this->alph;
	int i = 0;

	for (std::vector<char>::iterator it = v.begin(); it != v.end(); ++it, ++i) {

		temp.insert(std::pair<char, int>((*it), i));
	}

	this->alphIndex = temp; //copy constructor for map is called here

}

ds::Alphabet::~Alphabet() {
}

//copy constructor

ds::Alphabet::Alphabet(const Alphabet& ref) {

	this->alph = ref.alph;

}

//assignment operator

ds::Alphabet& ds::Alphabet::operator=(const Alphabet& ref) {

	if (this == &ref) {
		return (*this);
	}

	this->alph = ref.alph;

	return (*this);
}

void ds::Alphabet::printAlphabetChars() {
	for_each(alph.begin(), alph.end(), printFunction);
}

int ds::Alphabet::getIndex(char c) {
	return this->alphIndex.at(c);

}

int ds::Alphabet::getAlphabetSize() const {

	return this->alph.size();
}


void ds::Alphabet::validateAgainstAlphabet(std::string input){

for ( unsigned int i = 0 ; i < input.length(); i++)
  {
         if((this->alphIndex).find(input[i]) ==  (this->alphIndex).end() ){
		std::string c= std::string(1, input[i]);
		std::string msg ="char " + c +  " is not part of the alphabet...";
		throw std::invalid_argument(msg);
	}
  }

}


ds::Alphabet::RandomCharStream::RandomCharStream(const ds::Alphabet& a):aRef(a){

this->generator = new std::default_random_engine(this->seed);
this->distr =new std::uniform_int_distribution<int>(0,a.getAlphabetSize());

}

ds::Alphabet::RandomCharStream::~RandomCharStream(){

delete this->generator;
delete this->distr;


}

ds::Alphabet::RandomCharStream* ds::Alphabet::getRandomCharStream(const ds::Alphabet& a){

return new ds::Alphabet::RandomCharStream(a);

}

char ds::Alphabet::RandomCharStream::getNextRandomChar(){

return (this->aRef).alph.at((*(this->distr))(*generator));


}

std::string ds::Alphabet::RandomCharStream::getNextRandomString(int length){

std::vector<char> temp;

for(int i=0; i<length; ++i){

	temp.push_back(getNextRandomChar());
} 

std::string str(temp.begin(),temp.end());

return str;
}







