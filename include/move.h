/**
 * @file move.h
 * @author DECSAI
 * @note To be implemented by students
 * @warning Adjust const and references when needed
 */
#ifndef MOVE_H
#define MOVE_H

//Alumno1 apellidos11 Apellidos12 nombre1
//Alumno2 apellidos21 Apellidos22 nombre2

#include <iostream>
#include "language.h"

#define UKNOWN              -1  // Error genérico
#define BOARD_OVERFLOW      -2  // La tirada se sale del tablero
#define NONEXISTENT_WORD    -3  // La palabra de la tirada no aparece en el diccionario
#define INFEASIBLE_WORD     -4  // La palabra de la tirada no es compatible con player
#define NOT_FREE            -5  // La palabra empieza en una celda que ya está ocupada
#define MISSING_CROSSWORDS  -6  // La palabra no se cruza con ninguna otra

/**
 * @class Move
 * @brief Class to represent both a single movement, which might not be
 * a recognizable word, and a crossword in the table, which must be a known
 * word in the chosen language.
 * 
 * **Please note that all the characters are stored in ISO8859 standard and in uppercase**
*/
class Move {
private:
	int row, column;		/// Coordinates of the first letter
	bool ishorizontal;	/// Horizontal or vertical
	std::string letters;	/// Letters of the movement
	int score;				/// Total value of movement according to the language chosen
public:
	/**
	 * @brief Basic constructor e initializator
	 */
	Move();
	/**
	 * @brief Sets the main data of the class 
	 * @param r row
	 * @param c column
	 * @param h 'H' horizontal or 'V' vertical
	 * @param l letters
	 */
	void set(int r, int c, char h, const std::string  &l);
	/**
	 * @brief Sets the main data of the class 
	 * @param r row
	 */
	void setRow(int r) ;
	/**
	 * @brief Sets the main data of the class 
	 * @param c Column
	 */
	void setCol(int c);
	/**
	 * @brief Sets the main data of the class 
	 * @param h 'H' horizontal or 'V' vertical
	 */
	void setHorizontal(char h);
	/**
	 * @brief Sets the main data of the class 
	 * @param l Letters
	 */
	void setLetters(const std::string &l);
	/**
	 * @brief Calculates the value of the movement by adding the value 
	 * each letter according to the chosen language. If the word contained in 
	 * the set of letters does not belong to the language, its score would be -1 
	 * @param l The language
	 * @return The sum of individual values according to the language, or -1 if the 
	 * word does not belong to the language.
	 */
	int findScore(const Language &l) const;
	/**
	 * @brief Sets the value of the movement which have been calculated elsewhere 
	 * @param s The value of the movement
	 */
	void setScore(int s);
        /**
         * @brief Calculates the value of the movement and sets it
         * @param l The language
         */
        void setScore(const Language &l);
	/**
	 * @brief Query data stored in the class
	 * @return The value stored
	 */
	int getScore() const;
	/**
	 * @brief Query data stored in the class
	 * @return The row stored
	 */
	int getRow() const;
	/**
	 * @brief Query data stored in the class
	 * @return The column stored
	 */
	int getCol() const;
	/**
	 * @brief Query data stored in the class
	 * @return @retval true if it is a horizontal move, @retval false otherwise
	 */
	bool isHorizontal() const;
	/**
	 * @brief Query data stored in the class
	 * @return The letters
	 */
	std::string getLetters() const;

	/**
	 * @brief Shows the values stored in the screen, except score 
	 */
	void print( std::ostream &os) const;
	/**
	 * @brief Reads from keyboard the values of the class, except score 
	 */
	void read( std::istream &is);
        friend std::ostream& operator<<(std::ostream& os, const Move & m);
	friend std::istream& operator>>(std::istream& is, Move & m);	
};


/**
 * @brief Overload of the insertion operator
 * @param os Output stream (cout)
 * @param m The class to be inserted in the stream
 * @return The output stream (cout)
 */
//std::ostream& operator<<(std::ostream& os, const Move & m);
/**
 * @brief Overload of the extraction operator
 * @param os Input stream (cin)
 * @param m The class to be extracted from the stream
 * @return The input stream (cin)
 */
//std::istream& operator>>(std::istream& is, Move & m);
#endif /* MOVE_H */
