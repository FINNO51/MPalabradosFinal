/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include <string>
#include <cassert>
#include "player.h"
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 */
void removeCString(char *cstr, int pos);

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 */
void sortCString(char *cstr);

Player::Player() {
    clear();
}

void Player::clear() {
     letters[0]='\0';
     // strcmp(letters,"");
}

int Player::size() const {
    return strlen(letters);
}

string Player::to_string() const {
    return letters;
}


bool Player::extract(const std::string &s) {
    bool res=true;
    char final[MAXPLAYER+1];
    
    strcpy(final, letters);
    for (int i=0;i<s.size() && res;i++) {
        char *p=strchr(final,s[i]);
        if (p>0) {
            removeCString(final,p-final);
        } else
            res = false;
    }
    if (res) {
        strcpy(letters, final);
        sortCString(letters);
    }
    return res;
}

bool Player::isValid(const std::string & s) const {
    Player aux = *this;
    bool res = false;
    if (s.length()>0 && aux.extract(s)) {
        res = true;
    }
    return res;
}

void Player::add(const std::string & frombag) {
    string s(frombag);
    int nlong = MAXPLAYER - size();  //how many it's need
    if (frombag.size()> nlong)
        s = s.substr(0,nlong);  // cut out 
    strcat(letters,s.c_str());  // copy into letter, once converted to cstring
    sortCString(letters);
}

void removeCString(char *cstr, int pos) {
    assert (0 <= pos && pos <strlen(cstr));
    for (int i=pos; i<strlen(cstr); i++)
        cstr[i] = cstr[i+1];
}

void sortCString(char *cstr) {
    int lowest;
    for (int i=0; i<strlen(cstr); i++) {
        lowest = i;
        for(int j=i; j<strlen(cstr); j++)
            if (cstr[j] < cstr[lowest])
                lowest = j;
        if (lowest != i) {
            char aux = cstr[i];
            cstr[i] = cstr[lowest];
            cstr[lowest] = aux;
        }
    }
}

