/////////////////////////////////
// DO NOT MODIFY THIS FILE!!!! //
/////////////////////////////////
#ifndef MYSTERY_H
#define MYSTERY_H

#include <stdlib.h>
#include "Piece.h"

class Mystery : public Piece
{
public:
	bool legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const
	{
	  if ((abs(start.first - end.first) == 2) && (abs(start.second - end.second) == 3)) {
            return true;
          }
          if ((abs(start.first - end.first) == 3) && (abs(start.second - end.second) == 2)) {
            return true;
          }
          return false;
	}
	
	char to_ascii( void ) const { return is_white() ? 'M' : 'm'; }

private:
	Mystery( bool is_white ) : Piece( is_white ) {}

	friend Piece* create_piece( char );
};

#endif // MYSTERY_H
