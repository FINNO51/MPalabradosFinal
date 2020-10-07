/**
 * @file window.h
 * @author DECSAI
 * @note Fully implemented. No further implementation required.
 */
#ifndef WINDOW_H
#define WINDOW_Hfurther
#include "tiles.h"
#include "language.h"
#include "player.h"
#include "movelist.h"
#include <string>

class Window {
public:
	bool silent=false;
	bool grayscale=false;	
	int wait=0;
	/**
	 * @brief Basic constructor e initializer 
	 */
	Window();
	/**
	 * @brief Basic destructor  
	 */
	~Window();
	/**
	 * @brief Fixes the size of the terminal and calculates internal data
	 * to layout the information
	 * @param r Number of rows
	 * @param c Number of columns
	 */
	void setWindowSize(int rows, int columns);
	void setWindowPos(int x, int y);
	void setWindowFrame(int frame, int colorbackground, int ctext);
	void setDialog(std::string menu, std::string triggers); 
	/**
	 *	@brief Displays the basic information of the game 
	 * @param tiles	The set of tiles
	 * @param p			The tiles owned by the player
	 * @param good		Record of good movements
	 * @param bad		Record of bad movements
	 * @param l			Language chosen
	 */
	char showWindow();
	void setMessage(std::string text);

protected:
	int wx, wy, ww, wh;
	int wframe, wbackground, wtext;
	std::string wtriggers, wmenu, wmessage;
};

/**
 * @class window
 * @brief Class to show the output in a coloured, formatted terminal
 */
class Game : public Window{
public:
	Language language;				// The dictionary, as usual
	Tiles tiles;						// The matrix of letters
	Player player;						// The 7 letters owned by the player
	Bag bag;								// The bag with the remaining letters
	Movelist acceptedmovements,	// The list of correct movements
	rejectedmovements,				// The list of bad movements
	crosswords;							// The list used to store the crosswords found 
											// after each player turn
	int score,							// Accumulated score
	random;								// Seed of the random generator
	/**
	 * @brief Basic constructor e initializer 
	 */
	Game();
	/**
	 * @brief Basic destructor  
	 */
	~Game();
	/**
	 * @brief Fixes the size of the terminal and calculates internal data
	 * to layout the information
	 */
	void setWindowSize();
	/**
	 *	@brief Displays the basic information of the game 
	 * @param tiles	The set of tiles
	 * @param p			The tiles owned by the player
	 * @param good		Record of good movements
	 * @param bad		Record of bad movements
	 * @param l			Language chosen
	 */
	void doPaint();
	/**
	 * @brief Once Game.crosswords has been set, it shows the resulting crosswords
	 * in the screen for a better understanding of the movement made by the player
	 * and its main outcomes.
	 * @return A string that concatenates the movements contained in crosswords.
	 */	
	std::string showCrosswords();
	/**
	 * @brief Shows a valid crosswords in the screen and asks for confirmation to 
	 * the player. If positive, the movement which created the crosswords is stored
	 * definitely in Tiles, otherwise it is simply ignored.
	 * @param message
	 * @return 
	 */
	bool doConfirmCrosswords(std::string message);
	/**
	 * @brief Shows a bad crosswords in the screen and asks for confirmation to 
	 * continue playing
	 * @param message
	 * @return 
	 */
	bool doBadCrosswords(std::string message);
	// Friend functions
	friend std::ostream & operator<<(std::ostream & os, const Game &game);
	friend std::istream & operator>>(std::istream & is, Game &game);
	
	
protected:
	int xCell(int x) const;
	int yCell(int y) const;
	void paintCell(char letter, int r, int c, int forcecolor=-1);
	int colorCell(int r, int c);
	int  f, evencell, oddcell,
        evenmargin, oddmargin, tile, goodletter, badletter, scoreletter, number,
		  tilesx, tilesy, 
		  playerx, playery, inputx, inputy, movesx, movesy,
		  movesw,
		  scorex, scorey, titlex, titley,
		  wterminal, hterminal, goodmove, badmove;
};

#endif 
