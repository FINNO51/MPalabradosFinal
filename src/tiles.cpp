/**
 * @file tiles.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include "tiles.h"

using namespace std;

Tiles::Tiles() {
    cell=nullptr;
    columns=0;
    rows=0;
}

Tiles::Tiles(int r, int c) {
    cell=nullptr;
    allocate(r,c);
}

Tiles::Tiles(const Tiles& orig) {
    cell = nullptr;
    copy(orig);
}

Tiles::~Tiles() {
    deallocate();
}

Tiles& Tiles::operator=(const Tiles& orig) {
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}

bool Tiles::isEmpty() const {
    bool empty=true;
    for (int row = 0; row < getHeight(); ++row) 
        for (int column = 0; column < getWidth(); ++column) 
            if(get(row,column)!=EMPTY)
                empty=false;
        
    return empty;
}

void Tiles::setSize(int r, int c) {
    allocate(r,c);
}

void Tiles::add(const Move& m) {
    if (cell != nullptr) {
        string word = m.getLetters();

        int x = m.getCol() - 1, y = m.getRow() - 1; // translate coords to pos into the matrix
        if (y >= 0 && x >= 0)
            for (int i = 0; i < word.size() && y < getHeight() && x < getWidth(); ) {
                if(get(y,x)==EMPTY){
                    set(y, x, word[i]);
                    i++;
            }
                if (m.isHorizontal())
                    x++;
                else
                    y++;
            }
    }
}

int Tiles::getWidth() const {
    return columns;
}

int Tiles::getHeight() const {
    return rows;
}

char Tiles::get(int r, int c) const  {
    assert (cell != nullptr && r >=0 && r<getHeight() && 0<=c && c < getWidth());
    return cell[r][c];
}

void Tiles::set(int r, int c, char l) {
    assert (cell != nullptr && r>= 0 && r<getHeight() && c >= 0 && c < getWidth());
    cell[r][c] = l;    
}
	 
void Tiles::print(std::ostream &os) const {
    os << getHeight() << " " << getWidth() << endl;
    for (int f = 0; f < getHeight(); ++f) {
        for (int c = 0; c < getWidth(); ++c) {
            os << toUTF(get(f,c))<<" ";
        }
        os << endl;
    }
    os << endl;
} 

bool Tiles::read(std::istream &is){
    int n, m;
    string car;
    is >> n >> m;
    deallocate();
    allocate(n,m);
    for (int f = 0; f < getHeight(); f++) {
        for (int c = 0; c < getWidth(); c++) {
            is >> car;
            set(f,c, toISO(car)[0]);
        }
    }
}

Move Tiles::findMaxWord(int r, int c, bool hrz) const{
    int x = r - 1, y = c - 1;
    Move MaxWord;
    string word="";
    if(hrz){
        for(int i=y-1; i >= 0 && get(x,i) != EMPTY; i--)
            y--;
        for(int i=y; i < getWidth() && get(x,i) != EMPTY; i++)
            word+=get(x,i);
        if(word.size()>1)
            MaxWord.set(x+1,y+1,'h',word);
    }else{
        for(int i=x-1; i >= 0 && get(i,y) != EMPTY; i--)
            x--;
        for(int i=x; i < getHeight() && get(i,y) != EMPTY; i++)
            word+=get(i,y);
        if(word.size()>1)
            MaxWord.set(x+1,y+1,'v',word);
    }
    return MaxWord;
}

Movelist Tiles::findCrosswords(const Move& m, const Language& l) const{
    Tiles premove(*this);
    string word = m.getLetters();
    int x = m.getRow(), y = m.getCol();
    Movelist crosswords;
    if (y >= 0 && x >= 0){
        for (int i = 0; i < word.size() && x <= getHeight() && y <= getWidth(); ) {
            if(premove.get(x-1,y-1)==EMPTY){
                premove.set(x-1,y-1,word[i]);
                i++;
                crosswords+=premove.findMaxWord(x,y,!m.isHorizontal());
            }
                if (m.isHorizontal())
                    y++;
                else
                    x++; 
        }
        crosswords+=premove.findMaxWord(m.getRow(),m.getCol(),m.isHorizontal());
        crosswords.zip2();
        if(crosswords.size()==1 && crosswords.get(0).getLetters()==m.getLetters()){
            Move nocrosswords=m;
            nocrosswords.setScore(MISSING_CROSSWORDS);
            crosswords.set(0, nocrosswords);
        }
    }
    return crosswords;  
}

std::ostream& operator <<(std::ostream& os, const Tiles &t){
    os << t.getHeight() << " " << t.getWidth() << endl;
    for (int f = 0; f < t.getHeight(); ++f) {
        for (int c = 0; c < t.getWidth(); ++c) {
            os << toUTF(t.get(f,c))<<" ";
        }
        os << endl;
    }
    os << endl;
    return os;
}

std::istream& operator >>(std::istream& is, Tiles &t){
    int n, m;
    string car;
    is >> n >> m;
    t.deallocate();
    t.allocate(n,m);
    for (int f = 0; f < t.getHeight(); f++) {
        for (int c = 0; c < t.getWidth(); c++) {
            is >> car;
            t.set(f,c, toISO(car)[0]);
        }
    }
    return is;
}

/// Privados

void Tiles::allocate(int r, int c) {
    assert (r > 0 && c> 0);
    columns=c;
    rows=r;
    cell = new char*[r];
    cell[0] = new char[r * c];
    for (int i = 1; i < r; ++i)
        cell[i] = cell[i - 1] + c;
    for (int row = 0; row < r; ++row) {
        for (int column = 0; column < c; ++column) {
            set(row,column,EMPTY);
        }
    }
}

void Tiles::deallocate() {
    if (cell != nullptr) {
        delete[] cell[0];
        delete[] cell;
        cell = nullptr;
    }
}

void Tiles::copy(const Tiles& otro) {
    allocate(otro.getHeight(), otro.getWidth());
    for (int f = 0; f < otro.getHeight(); ++f) {
        for (int c = 0; c < otro.getWidth(); ++c) {
            set(f,c, otro.get(f,c));
        }
    }
}
