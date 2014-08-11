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
// Defines all major classes for the trie implementation.
//
// Date: 05/08/2014
//
// ---------------------------------------------------------------------------

#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include<stdexcept>
#include<stack>
#include <iostream>


namespace ds{


class Alphabet{

public:

Alphabet(char a[], int size);

//copy constructor

Alphabet(const Alphabet& ref);

//assignment operator

Alphabet& operator=(const Alphabet& ref);

virtual ~Alphabet();

void printAlphabetChars();

int getIndex(char c);

int getAlphabetSize();

void validateAgainstAlphabet(std::string);

private:

std::vector<char> alph;

std::map <char, int> alphIndex; //latter could be unsigned char



};

template <typename T>
class TrieI{

public:
virtual long size() =0;

virtual void add(std::string key, const T& data) =0;

virtual std::set<T> remove(std::string key) =0;

virtual bool contains(std::string key) =0;

virtual std::set<std::string> getAllKeys() =0;

virtual std::set<T> getAllValues(std::string key) =0;

virtual ~TrieI(){};

};

template <typename T>
class Trie: public TrieI<T> {

public: 

Trie();

Trie(Alphabet& alph);

//copy constructor

Trie(const Trie& ref);

//assignment operator

Trie& operator=(const Trie& ref);

virtual ~Trie();

//TrieI methods
long size();

void add(std::string key, const T& data);

std::set<T> remove(std::string key);

bool contains(std::string key);

std::set<std::string> getAllKeys();

void printAlphabet();

std::set<T> getAllValues(std::string key);

private:

class TNode;

long _size;

static char defaultAlphabet[];

static Alphabet& defaultA;

Alphabet& a;

TNode* root;



//Trie node
class TNode{
friend class Trie;
public:

    TNode(const T&);

	TNode(int, bool);
    
	virtual ~TNode();
		
private:
	bool leaf; //leaves are the data nodes
	std::set<T> values; //allow multiple entries per key
	bool special;
	std::vector<TNode*> children;

	bool hasChildren();
 };





};

}

//TRIE
template<typename T>
char ds::Trie<T>::defaultAlphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z' };

template<typename T>
ds::Alphabet& ds::Trie<T>::defaultA = *(new ds::Alphabet(
		ds::Trie<T>::defaultAlphabet, sizeof(ds::Trie<T>::defaultAlphabet)));

template<typename T>
ds::Trie<T>::Trie() :
		_size(0), a(defaultA), root(NULL) {

}

template<typename T>
ds::Trie<T>::Trie(Alphabet& alph) :
		_size(0), a(alph), root(NULL) {
}

template<typename T>
ds::Trie<T>::~Trie() {
	delete &defaultA;
}

//copy constructor

template<typename T>
ds::Trie<T>::Trie(const Trie& ref) :
		_size(ref._size), a(ref.a) {

//we need deep copying here ?

}

//assignment operator
template<typename T>
ds::Trie<T>& ds::Trie<T>::operator=(const Trie& ref) {

	if (this == &ref) {
		return (*this);
	}

	this->_size = ref._size;

	this->a = ref.a;

	return (*this);

}





//Trie interface methods

template<typename T>
long ds::Trie<T>::size() {
	return _size;
}



template<typename T>
void ds::Trie<T>::add(std::string key, const T& data) {

	if (key.length() == 0) {

		throw std::invalid_argument("key cannot be emtpy...");
	}

(this->a).validateAgainstAlphabet(key);

	if (_size == 0) {
		//create new root
		ds::Trie<T>::TNode* tempRoot = new ds::Trie<T>::TNode(
				(this->a).getAlphabetSize(), false);

		this->root = tempRoot;
	}

	int length = key.length();

	ds::Trie<T>::TNode* current;
	ds::Trie<T>::TNode* next;
	current = root;

	for (int i = 0; i < length; ++i) {
		next = (current->children).at((this->a).getIndex(key.at(i)));

		if (next == NULL) {
			//create node

			if (i == length - 1) {

				ds::Trie<T>::TNode* temp = new ds::Trie<T>::TNode(data);
				current->children[(this->a).getIndex(key.at(i))] = temp;
				next = temp;

			} else {
				ds::Trie<T>::TNode* temp = new ds::Trie<T>::TNode(
						(this->a).getAlphabetSize(), false);
				current->children[(this->a).getIndex(key.at(i))] = temp;
				next = temp;
			}

		} else {

			if (i == length - 1) {

				if (next->leaf || next->special) //already in
						{
					(next->values).insert(data);
				} else { //make it special

					(next->values).insert(data);
					next->special = true;
				}

			} else {

				if (next->leaf) {
					next->special = true;
					next->leaf = false;
					next->children = std::vector<ds::Trie<T>::TNode*>(
							(this->a).getAlphabetSize(), NULL);
				}

			}

		}
		current = next;
	}

	++_size;

}

template<typename T>
std::set<T> ds::Trie<T>::remove(std::string key) {

if (key.length() == 0) {

	throw std::invalid_argument("key cannot be emtpy...");
}

(this->a).validateAgainstAlphabet(key);

if (_size == 0) {
return std::set<T>();
} else {

		int length = key.length();

		ds::Trie<T>::TNode* current;
		ds::Trie<T>::TNode* next;
		std::stack<ds::Trie<T>::TNode*> ptrs;

		current = root;
		ptrs.push(current);



		for (int i = 0; i < length; ++i) {

			next = (current->children).at((this->a).getIndex(key.at(i)));

			if (next == NULL) {
				return std::set<T>();
			} else {

				if (next->leaf && i != length - 1) {
					return std::set<T>();

				}

				current = next;

				ptrs.push(current);
			}

		}

		if (current->leaf) {

			//remove current leaf, go up and remove nodes which have no children , if we met a special node make it a leaf
			std::set<T> tempSet= current->values;
			int curPos =key.length()-1;
			ds::Trie<T>::TNode* currentDelete = ptrs.top();
			ptrs.pop();

		  	while(ptrs.size()!=0)
			{
							
				ds::Trie<T>::TNode* parentPtr=  ptrs.top();
				ptrs.pop();

				if(currentDelete->leaf){  //remove node
				  

					delete currentDelete; //free mem  
					(parentPtr->children).at((this->a).getIndex(key.at(curPos)))=NULL;
					--_size;
					--curPos;


				}

				else{
					if((*currentDelete).hasChildren())
					{

					

						break; //we are done

					}else{

						if(currentDelete->special) //make it leaf
						{
					   	currentDelete->leaf = true;
					   	currentDelete->special = false;

					   	break; //we are done

						}else{ //normal node remove it

							(parentPtr->children).at((this->a).getIndex(key.at(curPos)))=NULL;
							delete currentDelete; //free mem
							--curPos;
						
						}
					}
				}

				currentDelete = parentPtr;
				

			}
			
			if(_size==0){
				root=NULL;
			}

			return tempSet;

		}else if(current->special){

			//it has other children just make it non special and we are done.
			
			std::set<T> tempSet= current->values;
			(current->values).clear();
			current->special =false;
			--_size;
			return tempSet;
			
		}
}

return std::set<T>();


}

template<typename T>
bool ds::Trie<T>::contains(std::string key) {

	if (key.length() == 0) {

		throw std::invalid_argument("key cannot be emtpy...");
	}

	(this->a).validateAgainstAlphabet(key);

	if (_size == 0) {
		return false;
	} else {

		int length = key.length();

		ds::Trie<T>::TNode* current;
		ds::Trie<T>::TNode* next;
		current = root;

		for (int i = 0; i < length; ++i) {

			next = (current->children).at((this->a).getIndex(key.at(i)));

			if (next == NULL) {
				return false;
			} else {

				if (next->leaf && i != length - 1) {

					
					return false;

				}

				current = next;
			}

		}

		if (current->leaf || current->special) {
			return true;
		}
	}

	return false;
}

template<typename T>
std::set<std::string> ds::Trie<T>::getAllKeys() {
	return std::set<std::string>();

}

template<typename T>
void ds::Trie<T>::printAlphabet() {

	a.printAlphabetChars();
}

template<typename T>
std::set<T> ds::Trie<T>::getAllValues(std::string key) {
std::set<T> s;
return s;

}

//TNode

template<typename T> //data node
ds::Trie<T>::TNode::TNode(const T& data) {
	(this->values).insert(data);
	this->leaf = true;
	this->special = false;
}

template<typename T>  //internal node
ds::Trie<T>::TNode::TNode(int numOfChildren, bool special) {

	this->children = std::vector<ds::Trie<T>::TNode*>(numOfChildren,NULL);
	this->leaf = false;
	this->special = special;
}

template<typename T>
ds::Trie<T>::TNode::~TNode() { //recursively remove nodes from the tree

}

template<typename T>
bool ds::Trie<T>::TNode::hasChildren(){

for (typename std::vector<ds::Trie<T>::TNode*>::iterator it = (this->children).begin() ; it != (this->children).end(); ++it)
{

	if((*it)!=NULL){

	
		return true;
	}

}
return false;

}


#endif
