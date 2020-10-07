/**
 * @file tiles.h
 * @author DECSAI
 * @note To be implemented by students
 */

#ifndef TILES_H
#define TILES_H
#include <iostream>
#include "move.h"
#include "movelist.h"

#define EMPTY '.'

/**
 * @brief Class used to store a double-dimension matrix to store all the characters of the game Scrabble. 
 * See https://en.wikipedia.org/wiki/Scrabble for more details
 * By default, all the positions are initialized to the @p EMPTY value
 * **Please note that all the characters are stored in ISO8859 standard and in uppercase**
*/
class Tiles {
public:
	/**
	 * @brief Basic constructor and initializer 
	 */
   Tiles();
	/**
	 * @brief Basic constructor and initializer for @p r rows and @p c columns
	 * @param r Number of rows
	 * @param c Number of columns
	 */
	Tiles(int r, int c);
	/**
	 * @brief Copy constructor
	 * @param orig The matrix to be copied
	 */
   Tiles(const Tiles & orig);  
	/**
	 * @brief Basic destructor of the class 
	 */
   ~Tiles(); 

	// Basic methods
	
	/**
	 * @brief Sets the size of the matrix, deallocates previous memory, if there is such, and allocates new memory
	 * @param r Number of rows
	 * @param c Number of columns
	 */
	void setSize(int r, int c);
        /**
         * @brief Returns true if the matrix does not have any move written
         * @return Empty or not emtpy
         */
        bool isEmpty()const;
	/**
	 * @brief Overloads the assignment operator
	 * @param orig Right hand side of the assignement
	 * @return this Left hand side of the assignement
	 */
	Tiles& operator=(const Tiles& orig); // Operador asignación
	/**
	 * @brief Query the number of columns
	 * @return The number of columns
	 */
	int getWidth() const;
	/**
	 * @brief Query the number of rows
	 * @return The number of rows
	 */
	int getHeight() const;
	/**
	 *	@brief Query the position of the matrix 
	 * @param r Row
	 * @param c Column
	 * @precond @p r and @p c must be in the right values otherwise, it throws an exception
	 * @return The character at [@p r][@p c]
	 */
	char get(int r, int c) const;
	/**
	 * @brief Sets the position of the matrix
	 * @param r Row
	 * @param c Column
	 * @precond @p r and @p c must be in the right values otherwise, it throws an exception
	 * @param l Letter to be set at that position
	 */
	void set(int r, int c, char l);
	

	/**
	 * @brief Add a movement to the matrix. It does not take into account
	 * whether the movement is a valid one, but it might produce an exception if
	 * the limits of the matrix are exceeded, as long as the methods set() and get() 
	 * are exclusively used to access the matrix.
	 * @param m The movement to be added
	 * @warning Please use only the methods set() and get() above to access to the matrix
	 */
	void add(const Move&m);

	/**
	 * @brief Prints the matrix in an ostream
	 * @param os Output stream (cout)
	 */	
	void print(std::ostream &os) const;
	/**
	 * @brief Reads the matrix from an istream
	 * @param is Intput stream (cin)
	 */	
	bool read(std::istream &is);
        /**
	 * @brief Find the maximum number of consecutive letters in the matrix starting
	 * from the specified position and following the given direction. It must explore
	 * rows (columns) *before* and *after* to that indicated in the parameters until 
	 * reaching the limits of the matrix or an empty space. It stores that word as a
	 * move, whose values @p row and @p column must be found as to be the maximum number
	 * of consecutive letters. The word found is not checked in any language, it is a free
	 * sequence of letters, therefore it is not scored accoring to any language neither
	 * @param r Row
	 * @param c Column
	 * @param hrz Direction horizontal/vertical
	 * @return An instance of Move without checking whether it belongs to a 
	 * langauge or not, nor to compute its score
	 * @warning Please use only the methods set() and get() above to access to the matrix
	 */
	Move findMaxWord(int r, int c, bool hrz) const;	
        /**
	 * @brief  Given a move, it computes all the crosswords with the existing letters
	 * in the matrix. Each crossword is stored in an instance of the class Move,
	 * and the whole set of crosswords found in an instance of Movelist. Each crossword (move)
	 * stored in the result must be scored according to the given language as specified in move.h
	 * In the case that the specified movement does not fit within the bound of the matrix, it returns an 
	 * empty list of movements.
	 * @param m Movement 
	 * @param l Language
	 * @return A set of scored crosswords, each one stored as a movement within the list of movements. If the
	 * movement does not fit within the matrix, an empty list is returned
	 * @warning Please use only the methods set() and get() above to access to the matrix
	 */
	Movelist findCrosswords(const Move &m, const Language &l) const;
        
        friend std::ostream & operator<<(std::ostream & os, const Tiles &t);
	friend std::istream & operator>>(std::istream & is, Tiles &t);
private:
	char ** cell;			/// Dynamic 2D Matrix. Choosing another implementation is up to the student
	int columns,			/// Number of columns
		rows;					/// Number of rows

	/**
	 * @brief Allocates new memory and, if necessary, frees the existing one
	 * @param r Rows to allocate
	 * @param c Columns to allocate
	 */
	void allocate(int r, int c);
	/**
	 * @brief Frees the memory 
	 */
	void deallocate();
	/**
	 * @brief Copy data from another object
	 * @param t The object to be copied
	 */
	void copy(const Tiles & t);

};


#endif /* TILES_H */

