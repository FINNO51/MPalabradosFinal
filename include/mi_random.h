/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mi_random.h
 * Author: acid
 *
 * Created on 9 de marzo de 2020, 9:47
 */

#ifndef MI_RANDOM_H
#define MI_RANDOM_H

class mi_random {

public:
    typedef unsigned long  result_type;
    result_type mmin,mmax;
private:

    result_type xact;

public:
    mi_random() {
        xact = 1;
        mmin = 0;
        mmax = 98765432123;
    }

    mi_random(int seed) {
        xact = seed;
         mmin = 0;
        mmax = 98765432123;
    }
    result_type min(){return mmin;}
    result_type max(){return mmax;}
    result_type operator()()  {
        xact = (result_type) (123456 * xact + 1023013) % mmax;
        return xact;
    }

};
void mi_shuffle (char *first, char *last, mi_random g) {
  for (auto i=(last-first)-1; i>0; --i) {
    int pos = g() % i;
    char c = first[i];
    first[i] =  first[pos];
    first[pos]= c; //swap (first[i], first[d(g)]);
  }
}
#endif /* MI_RANDOM_H */

