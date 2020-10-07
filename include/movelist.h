
/**
 * @file movelist.h
 * @author DECSAI
 * @note To be implemented by students
 */

#ifndef MOVELIST_H
#define MOVELIST_H

#include "move.h"
#include "language.h"

#define PASSWORD "MPALABRADOS-V2"

/**
 * @class Movelist
 * @brief Class used to store a sequence of single movements, where every movement is described in move.h
 */
class Movelist {
    private:
	Move* moves;		/// Dynamic vector of movements
	int nMove;			/// Number of recorded movements

	/**
	 * @brief Allocates memory
	 * @param n The number of movements to be reserved
	 */
	void allocate(int n);
	/**
	 * @brief Frees the memory reserved
	 */
	void deallocate();
	/**
	 * @brief Copy an existing set of movements
	 * @param ml The set of movements to be copied
	 */
	void copy(const Movelist& ml);
        /**
         * reset the component to initial values
         */
        void initialize(){  
            moves = nullptr;
            nMove = 0;
        }
public:
	/**
	 * @brief Basic constructor and initializer
	 */
	Movelist();

	/**
	 * @brief Constructor for @p n number of movements
	 * @param nmov Number of movements to store
	 */
	Movelist(int nmov);

	/**
	 * @brief Copy constructor
	 * @param orig The list of movements to be copied
	 */
	Movelist(const Movelist& orig); 

	/**
	 * @brief Destructor
	 */
	~Movelist(); 
	/**
	 * @brief Assign the content of the object parameters to this object
	 * @param orig Right hand side of the assignement
	 
	 */
        
	void assign (const Movelist& orig); 
	/**
	 * @brief Overloads the assignment operator
	 * @param orig Right hand side of the assignement
	 * @return this Left hand side of the assignement
	 */
	Movelist& operator=(const Movelist& orig); 

	/**
	 * @brief Query the set of movements stored
	 * @param p The position of the set, numbered from 0 to size()-1
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 * @return A copy of the movement in the position p.
	 */
	Move get(int p) const;

	/**
	 * @brief Inserts a new movement in the (already existing) position of the set of movements
	 * @param p The position to insert the movement.
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 * @param m The movement to insert
	 */
	void set(int p, const Move & m);

	/**
	 * @brief Query the number of existing movements in the class 
	 * @return The size of the set of movements
	 */
	inline int size() const { return nMove; };

	/**
	 * @brief Searches a movement in the set of recorded movements. Two movements are equal if all their data members coincide.
	 * @param mov The movement to be seeked
	 * @return The position of the movement in the set, @retval -1 when the movement is not found
	 */
	int find(const Move &mov) const;

	/**
	 * @brief Adds a copy of the movement at the end of the existing set, incrementing its size in one more movement
	 * @param mov The new movement
	 */
	void add(const Move &mov);
	/**
	 * @brief Remove the movement from the list and reduces the size in one less movement. If the specified movement
	 * does not exist, the method does nothing 
	 * @param mov The movement to be removed
	 */
	void remove(const Move&mov);
        void remove2(int);
	/**
	 * @brief Remove the movement stored in the position p and reduces the size in one less movement.
	 * @param p The position to be removed
	 * @precond @p p must be in the interval [0, size()) otherwise, it throws an exception
	 */
	void remove(int p);
	/**
	 * @brief Overload the operator += It is equivalent to add a movement at the end of the set, increasing its size in one more movement
	 * @param mov The new movement to be inserted
	 * @return The left hand side of the operator
	 */
	Movelist & operator+=(const Move &mov);
	/**
	 * @brief Removes all the movements that contain a word that does not have at least 2 letters
	 * or that does not exist in the given language 
	 * @param l The language 
	 */
	void zip(const Language &l);
        /**
         * @brief Removes all the movements with one letters words
         */
        void zip2();
	/**
	 * @brief Resets the set and leaves it empty 
	 */
   void clear();
	/**
	 * @brief Computes the whole score of the list of movements by adding the individual scores of each movement contained in the set
	 * of movements. It does not need the language to compute the scores because this is done inside each movement. 
	 * See move.h for more details. If at least one movement scores -1, then 
	 * the full list of movements will score -1.
	 * @return The score of the full set of movements
	 */
	int getScore() const;
        /**
         * @brief Sets the score for every movement in the list
         * @param l The language
         * @return 
         */
        void setScore(const Language &l);
	/**
	 * @brief Insert the data of the list of movements into an ostream (either cout or file)
	 * @param os The ostream
	 * @param scores If true, it prints the scores of every single movement. False by default
	 * @return true if there was no problen inserting/writing data
	 */
	bool print(std::ostream &os, bool scores=false) const;
	/**
	 * @brief Reads the movement from an istream until the last movement is marked
	 * as a "H 0 0 @" movement, that is, "H 0 0 _" normalized
	 * @param is The istream
	 * @return True if there was no problem reading data, false otherwise.
	 */
	bool read(std::istream &is);
        
        friend std::ostream & operator<<(std::ostream & os, const Movelist & s);
	friend std::istream & operator>>(std::istream & os, Movelist & s);
        
        /**
         * @brief Save the content of the object to a file, in a specific format (see details in the documentation of the project)
         * @param filename, a cstring with the name of the file for writing on it. 
         * @return ok if the saving process is ok.
         */
        bool save(const char *filename) const;
        
        /**
         * @brief Load the content of a file of movements to the object when the format is correct (see details in the documentation of the project)
         * @param filename a cstring with the name of the file from where to read.
         * @return ok if the reading process is ok.
         */
        bool loadFile(const char *filename);
};

/**
 * @brief Overload of the insertion operator
 * @param os Output stream (cout)
 * @param m The class to be inserted in the stream
 * @return The output stream (cout)
 */
//std::ostream & operator<<(std::ostream & os, const Movelist & i);

/**
 * @brief Overload of the extraction operator
 * @param os Input stream (cin)
 * @param m The class to be extracted from the stream
 * @return The input stream (cin)
 */
//std::istream & operator>>(std::istream & is, Movelist & i);
#endif

