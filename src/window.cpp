/**
 * @file window.cpp
 * @author DECSAI
 * @note Fully implemented. No further implementation required.
 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <unistd.h>
#include "language.h"
#include "player.h"
#include "bag.h"
#include "window.h"
#include "AnsiTerminal.h"
#include "bag.h"
using namespace std;
const string windowFrames[][6]={{"┌","┐","└","┘","─","│"},
                                {"+","+","+","+","-","|"}};

void paintText(int x1, int y1, int x2, int y2, string text) {
    int lx=x1, ly=y1;
    int c=0;
    bool end=false;
    while (!end){        
        if (lx>x2 || (text[c]=='\n' && ++c)) {
            lx=x1;
            if (ly<y2)
                ly++;
            else 
                end=true;                
        } else {
            setCursorXY(lx++, ly);
            cout << toUTF(text[c++]);
            if (c>=text.length())
                end=true;
        }
    }
}

Window::Window() {
    wx = wy = ww = wh = 0;
    wframe=0; wbackground=blue; wtext=white;
    wmenu=""; wtriggers="";
}
Window::~Window() {
    
}
void Window::setWindowSize(int columns, int rows) {
    wh = rows;
    ww = columns;
}
void Window::setWindowPos(int x, int y) {
    wx = x; wy = y;
}
void Window::setWindowFrame(int frame, int colorbackground, int ctext) {
    wframe = frame;
    wbackground = colorbackground;
    wtext = ctext;
}
void Window::setDialog(std::string menu, std::string triggers) {
    wmenu = menu; wtriggers=triggers;
} 
void Window::setMessage(std::string text) {
    wmessage = text;
} 
char Window::showWindow() {
    char letter;
    int oldb=getBackground(), oldt=getText();
    int tx1=wx, ty1=wy,tx2=wx+ww, ty2=wy+wh;
    if (!silent) {
        doRectangle(wx,wy,ww,wh, wbackground);
        setText(wtext);
        setBackground (wbackground);
        if (wframe>=0)      {
            for (int x=wx; x<wx+ww;x++) {
                setCursorXY(x,wy);
                cout<<windowFrames[wframe][4];
                setCursorXY(x,wy+wh);
                cout<<windowFrames[wframe][4];
            }
            for (int y=wy; y<wy+wh;y++) {
                setCursorXY(wx,y);
                cout<<windowFrames[wframe][5];
                setCursorXY(wx+ww,y);
                cout<<windowFrames[wframe][5];
            };
            setCursorXY(wx,wy); cout << windowFrames[wframe][0];
            setCursorXY(wx+ww,wy); cout << windowFrames[wframe][1];
            setCursorXY(wx+ww,wy+wh); cout << windowFrames[wframe][3];
            setCursorXY(wx,wy+wh); cout << windowFrames[wframe][2];
            tx1=wx+1; ty1=wy+1; tx2=wx+ww-1; ty2=wy+wh-1;  
        } else {
            tx1=wx; ty1=wy; tx2=wx+ww; ty2=wy+wh;  
        }
        if (wmenu != "") {
            setText(wtext);
            paintText(wx+ww-wmenu.length()-4,wy+wh,wx+ww-3,wy+wh, "["+wmenu+"]");
        }
        setText(wtext);
        setBackground(wbackground);
        paintText(tx1,ty1,tx2,ty2,wmessage);
    }
    setCursorOn();
    char res;
    if (wmenu!= "") {
        do {
            setCursorXY(wx+ww-2,wy+wh);
            cin >> letter;            
        } while (wtriggers.find(letter)==string::npos);
        res = letter;
   } else
        res = '\0';
    setText(oldt);
    setBackground(oldb);
    if (wait>0)
        usleep(wait*100000);
    setCursorOff();
    return res;
}



Game::Game() {    
    // Set paramenters
    f=3;
    setWindowPos(1,1);
    setDialog("","");
}

Game::~Game() {
}

void Game::setWindowSize() {
    assert (tiles.getHeight()>0 && tiles.getWidth()>0);
    wx=1;
    wy=1;
    ww = tiles.getWidth();
    wh = tiles.getHeight();
    // Coordinates in 3x2 cells
    titlex=1;
    titley=1;
    tilesx=titlex+2; 
    tilesy=titley+2;
    playerx=tilesx;
    playery=tilesy+wh+2;
    inputx = playerx;
    inputy = playery+2;
    f=3;
    wterminal=xCell(tilesx+max(7,ww)+2)-1; 
    hterminal = yCell(wh+8);
    setSize(hterminal,wterminal);
    showWindow();
}


void Game::doPaint() {
    int b=getBackground(), t=getText();
    int m;

    // Adjust colors
    if (!grayscale) {
    // Set color
        setWindowFrame(-1,blue,white);
        evencell=setColor(0.75,0.75,0.5);
        oddcell=setColor(0.8,0.8, 0.5);
        goodletter=setColor(0.8,0,0);
        evenmargin=setColor(0.6,0.6,0.6);
        oddmargin = setColor(0.8,0.8,0.8);
        number=black;
        scoreletter=gray;
        goodmove = setColor(0,0.8,0);
        badmove = setColor(0.8,0.4,0.4);
        tile=black;
    } else {
        // Set grayscale
        setWindowFrame(-1,white,black);
        evencell=setColor(0.75,0.75,0.75);
        oddcell=setColor(0.85,0.85, 0.85);
        goodletter=setColor(0,0,0);
        badletter=setColor(0.5,0.5,0.5);
        evenmargin=setColor(0.1,0.1,0.1);
        oddmargin = setColor(0.3,0.3,0.3);
        number=white;
        scoreletter=setColor(0.6,0.6, 0.6);
        goodmove = white;
        badmove = setColor(0.4,0.4,0.4);
        tile=black;
    }
    // Clean the screen
    setBackground(wbackground);
    setText(wtext);
    clearScreen();
    
    // Layout
    doRectangle(xCell(titlex),yCell(titley), wterminal, 1, badmove);
    setText(white);
    // Title
    setCursorXY(xCell(titlex),yCell(titley));
    setBackground(badmove);
    if (ww >= 13)
        cout << " MPALABRADOS  " <<tiles.getHeight()<<"x"<<tiles.getWidth()<<" ["<<language.getLanguage()<<"]  SCORE [" << score<< "]  BAG ["<<bag.size()<<"]";
    else
        cout << " MPALABRADOS |" <<tiles.getHeight()<<"x"<<tiles.getWidth()<<"|"<<language.getLanguage()<<"|" << score<< " p|"<<bag.size()<<" l";
    // Player
    for (int i=0; i<7; i++) {
        doRectangle(xCell(i+playerx),yCell(playery), f,f-1, colorCell(-1,i));
        if (i<player.size())
            paintCell(player.to_string()[i],-1,i);
    }
    // Board. Top and bottom margins
    for (int i=0; i<ww; i++) {
        int b=(i+1)%2==1?oddmargin:evenmargin;
        doRectangle(xCell(i+tilesx),yCell(tilesy-1), f,f-1, b);
        doRectangle(xCell(i+tilesx),yCell(wh+tilesy), f,f-1, b);
        setBackground(b);
        setText(number);
        setCursorXY(xCell(i+tilesx),yCell(tilesy-1));
        cout << i+1;
        setCursorXY(xCell(i+tilesx),yCell(wh+tilesy));
        cout << i+1;
    }
    // Board. Left and right margins
    for (int j=0; j<wh; j++) {
        int b=(j+1)%2==1?oddmargin:evenmargin;
        doRectangle(xCell(tilesx-1),yCell(j+tilesy), f,f-1, b);
        doRectangle(xCell(ww+tilesx),yCell(j+tilesy), f,f-1, b);
        setBackground(b);
        setText(number);
        setCursorXY(xCell(tilesx-1),yCell(j+tilesy));
        cout << j+1;
        setCursorXY(xCell(ww+tilesx),yCell(j+tilesy));
        cout << j+1;
    }
    // Board
    for (int i=0; i<ww; i++) {
        for (int j=0; j<wh; j++){ 
            doRectangle(xCell(i+tilesx),yCell(j+tilesy), f,f-1, colorCell(j,i));
            if (tiles.get(j,i) != EMPTY) {
                paintCell(tiles.get(j,i),j,i);
            } 
        }
    }
    // Return to former parameters
    setBackground(wbackground);
    setText(wtext);
    setCursorXY(xCell(inputx), yCell(inputy));
}

std::string Game::showCrosswords() {
    int cw;
    string res="";
    for (int m=0; m<crosswords.size(); m++) {
        Move move = crosswords.get(m);
        res = res+(move.isHorizontal()?"H ":"V ")+
                    to_string(move.getRow())+" "+to_string(move.getCol())+ " "+
                    move.getLetters();
        if (move.getScore()>=0) {
            cw = goodmove;
            res+=" ("+to_string(move.getScore())+")\n";
        }
        else {
            cw = badmove;
            switch (move.getScore()) {
                case BOARD_OVERFLOW:
                    res+=" (BOARD OVERFLOW)\n";
                    break;
                case NONEXISTENT_WORD:
                    res+=" (NONEXISTENT WORD)\n";
                    break;
                case INFEASIBLE_WORD:
                    res+=" (INFEASIBLE WORD)\n";
                    break;
                case NOT_FREE:
                    res+=" (NOT FREE)\n";
                    break;
                case MISSING_CROSSWORDS:
                    res+=" (MISSING CROSSWORDS)\n";
                    break;
                default:
                    res+=" (X)\n";
                    break;
            }
        }
        int row = move.getRow()-1, column = move.getCol()-1;
        for (int letter=0; letter<move.getLetters().length() && row < tiles.getHeight() && column<tiles.getWidth();letter++) {
            doRectangle(xCell(column+tilesx),yCell(row+tilesy), f,f-1, cw);
            paintCell(move.getLetters()[letter], row,column, cw);
            row += (move.isHorizontal()?0:1);
            column += (move.isHorizontal()?1:0);
        }
    }    
    return res;
}
    
bool Game::doConfirmCrosswords(std::string message) {
    Window popUp;
    string cw;
    cw = showCrosswords();
    popUp.silent=silent;
    popUp.wait = wait;
    popUp.setWindowPos(1,yCell(playery-1));
    popUp.setWindowSize(wterminal,yCell(4));
    popUp.setWindowFrame(0,goodmove,wtext);
    popUp.setDialog("Press Y|N","yYnN");
    popUp.setMessage(message+"\n"+cw);
    char letter=popUp.showWindow();
    return letter=='y' || letter == 'Y';
}
bool Game::doBadCrosswords(std::string message) {
    Window popUp;
    string cw;
    if (crosswords.size()==1 && crosswords.getScore()>0) {
        Move badmove=crosswords.get(0);
        badmove.setScore(MISSING_CROSSWORDS);
        crosswords.set(0,badmove);
    }
    cw = showCrosswords();
    popUp.silent=silent;
    popUp.wait = wait;
    popUp.setWindowPos(1,yCell(playery-1));
    popUp.setWindowSize(wterminal,yCell(4));
    popUp.setWindowFrame(0,badmove,wtext);
    popUp.setDialog("Press Y to CONTINUE","yY");
    popUp.setMessage(message+"\n"+cw);
    popUp.showWindow();
    return true;
}
int Game::xCell(int x) const{
    return f*(x-1)+1;
}

int Game::yCell(int y) const {
    return (f-1)*(y-1)+1;
}

void Game::paintCell(char letter, int r, int c, int forcecolor) {

    setText(goodletter);
    if (forcecolor >= 0)
        setBackground(forcecolor);
    else
        setBackground(colorCell(r,c));
    if (r>=0)
        setCursorXY(xCell(c+tilesx),yCell(r+tilesy));
    else
        setCursorXY(xCell(c+playerx),yCell(playery));
    cout << toUTF(letter);
    setText(scoreletter);
    if (r>=0)
        setCursorXY(xCell(c+tilesx)+1,yCell(r+tilesy)+1);
    else
        setCursorXY(xCell(c+playerx)+1,yCell(playery)+1);
    cout << language.getScore(letter);
}

int Game::colorCell(int r, int c) {
    if (r>=0)
        return (r+c)%2==1?oddcell:evencell;
    else
        return c%2==1?oddcell:evencell;
}





