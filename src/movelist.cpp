/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "move.h"
#include "movelist.h"

using namespace std;
//
// Private

void Movelist::allocate(int n) {
    if (n > 0) {
        moves = new Move[n];
        nMove = n;
    } else
        initialize();
}

void Movelist::deallocate() {
    if (nMove > 0) {
        delete[] moves;
    }
    initialize();
}

void Movelist::copy(const Movelist& otro) {
    allocate(otro.size());
    for (int i = 0; i < otro.size(); ++i) {
        set(i, otro.get(i));
    }
}
// public interface

Movelist::Movelist() {
    initialize();
}

Movelist::Movelist(int nmov) {
    initialize();
    allocate(nmov);
}

Movelist::Movelist(const Movelist& orig) {
    initialize();
    copy(orig);
}

Movelist::~Movelist() {
    deallocate();
}

void Movelist::assign(const Movelist& orig) {
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
}

Movelist& Movelist::operator=(const Movelist& orig) {
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}


Move Movelist::get(int p) const {    
    assert (p >= 0 && p < size());
    return moves[p];
}

void Movelist::set(int p, const Move & m) {
    assert (p >= 0 && p < size());
    moves[p] = m;
}

bool Movelist::save(const char *filename) const {
    ofstream flujo(filename, ios::out);
    cout << "Saving file "<< filename << endl;
    if (flujo) {
        flujo << *this << endl;
        if (flujo)  {
            flujo.close();
            return true;
        }
        cerr << "** ERROR saving data in " << filename << endl;
        return false;
    }
    cerr << "** ERROR opening file "<< filename << endl;
    return false;
}

bool Movelist::loadFile(const char *filename) {
    ifstream flujo(filename);
    string magica;
    cout << "opening file "<< filename << endl;
    if (flujo) {
        flujo >> magica;
        if (magica != PASSWORD)  {
            cerr << "ERROR: unknown format "<<endl;
            return false;
        }
        flujo >> *this;
        if (flujo) {
            flujo.close();
            return true;
        }
        cerr << "ERROR loading data from filename " << filename << endl;
        return false;
    } 
    cerr << "** ERROR opening file "<< filename << endl;
    return false;
}

int Movelist::find(const Move& mov) const {
   int pos = -1;
   for (int i = 0; i < size() && pos == -1; i++) {
        if (mov.getLetters() == get(i).getLetters()) { // OJO a completar posteriormetne
            pos = i;
        }
    }
    return -1;    
}    

void Movelist::add(const Move &mov) {
    int save_nMove= nMove;
    
    Movelist aux(*this); // copy movelist 
    deallocate ();
    allocate(save_nMove+1);
    for (int i=0; i< save_nMove; i++)
        set(i,aux.get(i));
    set(save_nMove, mov);
}

void Movelist::remove(const Move &mov) {
    int p = find(mov);
    if (p>=0)
        remove(p);
}


Movelist & Movelist::operator+=(const Move &m) {
    this->add(m);
    return *this;
}

//void Movelist::split(Movelist &good, Movelist &bad, const Language &lang) const {
//    good.clear();
//    bad.clear();
//    for (int i=0; i<size(); i++) {
//        if (lang.query(get(i).getLetters())){
//            good += get(i);
//        } else {
//            bad += get(i);
//        }
//    }
//}

void Movelist::clear() {
    deallocate();
}

int Movelist::getScore() const {
    int score=0;
    for (int i=0; i<size() && score >=0; i++) {
        if (get(i).getScore()>=0){
            score += get(i).getScore();
        } else {
            score = NONEXISTENT_WORD;
        }
    }
    return score;
}

void Movelist::setScore(const Language& l){
    for(int i=0;i<size();i++){
        if(moves[i].getScore()>=0)
        moves[i].setScore(l);
    }
}

void Movelist::remove(int p) {
    assert (p >= 0 && p < size());
    
    Movelist aux(size()-1);
    for (int i=0, j=0; i<size(); i++)
        if (i != p)
            aux.set(j++,get(i));
    *this = aux;

}

//void Movelist::zip(const Language &s)  {
//    int pos=0;
//    if (size()==0)
//        return;
//    do {
//        cerr << "QUERY: "<<toUTF(get(pos).getLetters())<<endl;
//        if (!s.query(get(pos).getLetters()))  {
//            cerr << "REMOVE: "<<toUTF(get(pos).getLetters())<<endl;
//            remove(pos);
//        }
//        else
//            pos ++;
//    } while (pos < size());
//}

void Movelist::zip(const Language &s)  {
    for (int pos=0; pos<size();)  {
        if (!s.query(get(pos).getLetters()))  {
            remove(pos);
        }
        else
            pos++;
    }
}

void Movelist::zip2() {
    for (int pos=0; pos<size();){
        if(get(pos).getLetters().size()<1){
            remove(pos);
        }
        else
            pos++;
    }
}

bool Movelist::print(std::ostream &os, bool scores) const {
    bool res=true;
    for (int i=0; i<size() && res; i++) {
        get(i).print(os);
        if (scores)
            os << " ("<<get(i).getScore()<<") - ";
        else
            os << " - ";
        if (os.bad())
            res=false;
    }
    return res;
}

bool Movelist::read(std::istream &is) {
    Move m;
    bool fin = false;
    
    deallocate();
    m.read(is);
                                
    while (m.getLetters().size() > 1 && !fin ) { // && m.getLetters() != "_") {
        
        add(m);
        m.read(is);
        if (is.eof())
            fin = true;
    }
    
    return !fin;
}

ostream& operator<<(ostream& os, const Movelist & d) {
    bool res=true;
    for (int i=0; i< d.nMove && res; i++) {
        os <<  d.moves[i] << " ";
        if (os.bad())
            res=false;
    }
    return os;
}

istream& operator>>(istream& is, Movelist& ml) {
    Move m;
    bool fin = false;
    ml.deallocate(); //  clear(); when defined operator>> is an external function
    is >> m; // m.read(is);
    while (m.getLetters() != "_"  && !fin ) { // && m.getLetters().size() > 1
        if (is.eof())
            fin = true;
        else {
            ml.add(m);
            is >> m;
        }
    }
    return is;
    
}