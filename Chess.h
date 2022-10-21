//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include <vector>
class Chess
{
public:
	// This default constructor initializes a board with the standard piece positions, and sets the state to white's turn
	Chess( void );

	// Returns a constant reference to the board 
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	const Board& board( void ) const { return _board; }

	// Returns true if it's white's turn
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	bool turn_white( void ) const { return _turn_white; }

	// Attemps to make a move. If successfull, the move is made and the turn is switched white <-> black
	bool make_move( std::pair< char , char > start , std::pair< char , char > end );

	// Returns true if the designated player is in check
	bool in_check( bool white ) const;

	// Returns true if the designated player is in mate
	bool in_mate( bool white ) const;

	// Returns true if the designated player is in mate
	bool in_stalemate( bool white ) const;

	Board& not_const_board( void ) { return _board; }
	
	friend std::istream& operator >> ( std::istream& is , Chess& chess );
private:
	// The board
	Board _board;

	// Is it white's turn?
	bool _turn_white;

	//Returns vector of all pieces checking king
	std::vector<std::pair<char, char>> checkers(std::pair<char, char> king, Board& _board) const;

	//Returns position of king(white or black);
	std::pair<char, char> find_king(char color) const;

	
};

// Writes the board out to a stream
std::ostream& operator << ( std::ostream& os , const Chess& chess );

// Reads the board in from a stream
std::istream& operator >> ( std::istream& is , Chess& chess );


#endif // CHESS_H
