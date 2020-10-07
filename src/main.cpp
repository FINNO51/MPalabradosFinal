/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */



#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"
#include "window.h"
#include "AnsiTerminal.h"
using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define GENERAL_ERROR 4

// Alumno1: Conde Molina Jordi
// Alumno2: Sanchez Alcaraz Antonio

/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errordata);

void loadMatch(const string & ifilematch, int & score, Game &game, int &h, int &w);

int movementScore(const Game &game, Move &move);
/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    Move move, singlemove;
    Tiles copy;
    Game game;
    int w=-1, h=-1, wait=0, Id=-1, score=0;
    string lang="",ifilematch="", ofilematch="",
            external_bag="",hand="";
    ifstream ifile; ofstream ofile;
    bool end=false, confirm=false;
	char c;
    
    /// Check arguments
    string sarg;
    for(int arg=1; arg<nargs; ) {
        sarg = args[arg];
        if (sarg=="-open"){
            arg++; 
            if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ifilematch=args[arg++];
        }else if (sarg=="-save"){
            arg++; 
            if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                ofilematch=args[arg++];
        }else if (sarg== "-l") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                lang=args[arg++];
        } else if (sarg== "-r") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                Id = atoi(args[arg++]);
        } else if (sarg== "-b") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                external_bag = args[arg++];
        }else if (sarg== "-w") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                w = atoi(args[arg++]);
        } else if (sarg== "-h") {
                arg++; 
                if (arg>=nargs) errorBreak(ERROR_ARGUMENTS, "");
                h = atoi(args[arg++]);
        }  else
            errorBreak(ERROR_ARGUMENTS, "");
    }
    // Process arguments
    if  ((lang=="" && ifilematch=="") ||( ifilematch=="" &&  (w <0 ||  h <0)))
        errorBreak(ERROR_ARGUMENTS, "");

    /// load data
    if (ifilematch == ""){
        game.language.setLanguage(lang);
        game.score=score;
        if(Id >= 0)
            game.bag.setRandom(Id);
        if(external_bag != "")
            game.bag.set(toISO(external_bag));
        else
            game.bag.define(game.language);
        game.tiles.setSize(h,w);
        hand=game.bag.extract(MAXPLAYER);
        game.player.add(hand);
    }else
        loadMatch(ifilematch, score, game, h, w);
    game.setWindowSize();
    if(game.tiles.isEmpty()){
        while(!confirm){
            game.crosswords.clear();
            game.doPaint();
            cin>>move;
            if(move.getLetters()!="_"){
                score=movementScore(game,move);
                if(!game.language.query(move.getLetters()))
                    score=NONEXISTENT_WORD;
                move.setScore(score);
                game.crosswords+=move;
                if(score<0){
                    game.doBadCrosswords("Invalid movement");
                    game.rejectedmovements+=move;
                }else if(game.doConfirmCrosswords("Start with this move?")){
                    confirm=true;
                    game.acceptedmovements+=move;
                }
            }else
                confirm=true;
        }
    }
    while (!end)  {
        game.player.extract(move.getLetters());
        game.player.add(game.bag.extract(MAXPLAYER - game.player.size()));
        confirm=false;
        if (move.getLetters()=="_")
            end=true;
        else{
            score=game.crosswords.getScore();
            game.score+=score;
            game.tiles.add(move);
            while(!confirm){
                game.doPaint();
                cin>>move;
                if(move.getLetters()!="_"){
                    game.crosswords=game.tiles.findCrosswords(move,game.language);
                    game.crosswords.setScore(game.language);
                    if(game.tiles.get(move.getRow()-1,move.getCol()-1)!=EMPTY){
                        move.setScore(NOT_FREE);
                        game.crosswords.clear();
                        game.crosswords+=move;
                        game.doBadCrosswords("Invalid movement");
                        game.rejectedmovements+=move;
                    }else{
                        if(game.crosswords.size()==1){
                            if(move.getLetters()==game.crosswords.get(0).getLetters())
                                score=MISSING_CROSSWORDS;
                            else{
                                singlemove=game.crosswords.get(0);
                                singlemove.setScore(game.language);
                                score=singlemove.getScore();
                            }
                        }else if(game.crosswords.getScore()>=0)
                            score=game.crosswords.getScore();
                        else{
                            score=movementScore(game,move);
                            move.setScore(score);
                        }
                        if(score<=0){
                            if(score==INFEASIBLE_WORD){
                                game.crosswords.clear();
                                game.crosswords+=move;
                            }
                            game.doBadCrosswords("Invalid movement");
                            game.rejectedmovements+=move;
                        }else if(game.doConfirmCrosswords("Score with this movement:")){
                            confirm=true;
                            game.acceptedmovements+=move;
                        }
                    }
                }else
                    confirm=true;
            }
        }
    }
    
    cout<<endl<<"%%%OUTPUT"<<endl;
    if(ofilematch!=""){
        ofile.open(ofilematch);
        if(!ofile)
            errorBreak(ERROR_OPEN,ofilematch);
        cout<<PASSWORD<<endl;
        ofile<<PASSWORD<<endl;
        ofile<<game;
    }
    cout<<game;
    cout<<game.acceptedmovements.size()<<endl<<game.acceptedmovements<<endl;
    cout<<game.rejectedmovements.size()<<endl<<game.rejectedmovements<<endl;
    
    return 0;
}



void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> [-b <bag> -r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> [-save <matchfile>]"<<endl;            
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
        case GENERAL_ERROR:
            cerr<<"Error: "<<errordata << endl;
            break;
    }
    std::exit(1);
}

void loadMatch(const string & ifilematch, int & score, Game &game, int &h, int &w){
    ifstream ifile;
    string word, lang;
    Tiles tiles;
    int n;
    
    ifile.open(ifilematch);
        if (!ifile)
            errorBreak(ERROR_OPEN,ifilematch);
        ifile >> word;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        if (word != PASSWORD)
            errorBreak(ERROR_DATA,ifilematch);
        ifile >> score;
        ifile >> lang;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        ifile >> tiles;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        ifile >> n;
        ifile >> word;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        ifile >> n;
        if (!ifile)
            errorBreak(ERROR_DATA,ifilematch);
        ifile.close();
        
        ifile.open(ifilematch);
        ifile >> game;
        h = game.tiles.getHeight();
        w = game.tiles.getWidth();
        
        ifile.close();
}

std::ostream & operator<<(std::ostream & os, const Game &game)  {
    os<<game.score<<endl;
    os<<game.language.getLanguage()<<endl;
    os<<game.tiles;
    os<<game.player.size()<<" "<<toUTF(game.player.to_string())<<endl;
    os<<game.bag.size()<<" "<<toUTF(game.bag.to_string())<<endl;
    return os;
}

std::istream & operator>>(istream & is, Game &game) {
    string word, lang;
    int n;
    
        is >> word;
        is >> game.score;
        is >> lang;
        game.language.setLanguage(lang);
        is >> game.tiles;
        
        is >> n;
        if (n>0) {
            is >> word;
            game.player.add(toISO(word));
        }
        is >> n;
        if (n>0) {
            is >> word;
            game.bag.set(toISO(word));
        }
        is >> n;
        if (n>0)
            is >> game.acceptedmovements;
        is >> n;
        if (n>0)
            is >> game.rejectedmovements;
}

int movementScore(const Game &game, Move &move){
    int score;
    int x = move.getCol() - 1, y = move.getRow() - 1, i=0;;
    if (y >= 0 && x >= 0){
        for (i ; i < move.getLetters().size() && y < game.tiles.getHeight() && x < game.tiles.getWidth(); ) {
            if(game.tiles.get(y,x)==EMPTY)
                i++;
            if (move.isHorizontal())
                x++;
            else
                y++;
            }
    }
    if(move.getRow() < 0 || move.getCol() < 0 || i<move.getLetters().size()){
        score=BOARD_OVERFLOW;
     //   if(move.isHorizontal())
     //       move.setCol(move.getCol()+i-1);
     //   else
     //       move.setRow(move.getRow()+i-1);
    }
    else if(!game.player.isValid(move.getLetters()))
        score=INFEASIBLE_WORD;
    else
        score=move.findScore(game.language);
    
    return score;
}