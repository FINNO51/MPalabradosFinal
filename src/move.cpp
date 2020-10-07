/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include "language.h"
#include "move.h"

using namespace std;

Move::Move() {
        row = column = -1;
        score = 0;
        letters="";
}

void Move::set(int r, int c, char h, const string & l) {
    setRow(r);
    setCol(c);
    setHorizontal(h);
    setLetters(l);
}

void Move::setRow(int r){
    row = r;
}
void Move::setCol(int c){
    column=c;
}
void Move::setHorizontal(char h){
    ishorizontal = ( h == 'H' || h == 'h');
}
void Move::setLetters(const string &l){
    letters = normalizeWord(l);
}

void Move::setScore(int s) {
    score = s;
}

int Move::findScore(const Language &l) const {
    int _score;
    if (l.query(getLetters()))  {
        _score=0;
        for (int let=0; let<getLetters().size(); let++){
            _score += l.getScore(getLetters()[let]);
        }
    } else{
        _score = NONEXISTENT_WORD;
    }
    return _score;
}

void Move::setScore(const Language& l){
    int _score=findScore(l);
    setScore(_score);
}

int Move::getScore() const{
    return score;
}
//int Move::getScore(const Language &l) const{
//    int score = 0;
//    for (int i=0; i<letters.size(); i++)
//        score += l.getScore(letters[i]);
//    return score;
//}

int Move::getRow() const {
        return row;
}
int Move::getCol() const{
        return column;
}
bool Move::isHorizontal() const{
        return ishorizontal;
}
string Move::getLetters() const{
        return letters;
}

void Move::print( std::ostream &os) const {
    os << (ishorizontal? 'H':'V')<< " "  << row << " " << column 
            << " " << toUTF(letters);    
}

void Move::read( std::istream &is) {
    char h;
    int _row, _column;
    string _letters;
    is >> h >> _row >> _column  >> _letters;
    set(_row,_column, h, _letters);
}


std::ostream& operator<<(std::ostream& os, const Move & m)  {
    os << (m.ishorizontal? 'H':'V')<< " "  << m.row << " " << m.column 
            << " " << toUTF(m.letters);
    return os;
}

std::istream& operator>>(std::istream& is, Move & m) {
    char h;
    int _row, _column;
    string _letters;

    is >> h >> _row >> _column  >> _letters;
    if (is.eof())
        return is;
    m.set(_row,_column, h, _letters);
    return is;
}

