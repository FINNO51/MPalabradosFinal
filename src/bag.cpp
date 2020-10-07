/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <cstring>
#include <string>
#include <cassert>
#include <random>
#include <fstream>
#include <algorithm>
#include "bag.h"
#include "language.h"
#include "mi_random.h"
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;


/**
 * @brief USING mi_random class. Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @param id Seed for the random sorting
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);


/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 * @warning TO BE IMPLEMENTED
 */
void removeVector(char *s, int & n, int p);


Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

void Bag::setRandom(int mid) {
    id = mid;
}
void Bag::define(const Language &l) {
    string forletters = l.getLetterSet();
    nletters = 0;
    for (int i = 0; i < forletters.size(); i++)
        nletters += l.getFrequency(forletters[i]);  
    assert(nletters <= MAXBAG); // para comprobar que hay espacio en el vector, sino excepción!
    for (int k = 0, i = 0; i < forletters.size(); i++)
        for (int j = 0; j < l.getFrequency(forletters[i]); j++)
            set(k++, forletters[i]);
    shuffleVector(letters, nletters, id);
}


int Bag::size() const {
    return nletters;
}

string Bag::to_string() const  {
    string s(nletters,'-');
    for (int i=0;i <nletters; i++)
        s[i]=get(i);
    return s;
}

void Bag::set(std::string s) {
    assert(s.size()<=MAXBAG);
    nletters = s.size();
    for (int i=0;i<s.size(); i++)
        set(i,s[i]);
}


string Bag::extract(int n) {
    string result="";
    if (n > nletters)
        n = nletters;
    for (int i=0; i<n; i++) {
        result.append(1,get(0));
        removeVector(letters, nletters, 0);
    }
    return result;
}

/// Private

char Bag::get(int p) const {
    assert (0<=p && p<nletters);
    return letters[p];
}

void Bag::set(int p, char c) {
    assert (0<=p && p<nletters);
    letters[p] = c;
}

// Auxiliary functions 


/**
 * @brief USING mi_random class. Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @param id Seed for the random sorting
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id) {
    mi_shuffle(s, s+n, mi_random(id));
}

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 */
void removeVector(char *s, int & n, int p){
    assert (0<=p && p<n);
    for (int i=p; i<n-1; i++)
        s[i] = s[i+1];
    n--;
}

