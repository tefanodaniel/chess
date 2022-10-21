//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

#include "Chess.h"


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess( void ) : _turn_white( true )
{
	// Add the pawns
	for( int i=0 ; i<8 ; i++ )
	{
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+1 ) , 'P' );
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+6 ) , 'p' );
	}

	// Add the rooks
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+7 ) , 'r' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+7 ) , 'r' );

	// Add the knights
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+7 ) , 'n' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+7 ) , 'n' );

	// Add the bishops
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+7 ) , 'b' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+7 ) , 'b' );

	// Add the kings and queens
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+0 ) , 'Q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+0 ) , 'K' );
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+7 ) , 'q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::make_move( std::pair< char , char > start , std::pair< char , char > end )
{
  bool legal_move = _board.valid_move(start, end, turn_white());
  if (!legal_move) {
    return false;
  }
  char startP = _board(start)->to_ascii();
  char endP = '0';
  if (_board(end) != NULL) {
    endP = _board(end)->to_ascii();
  }
  
  //when it is legal move
  if(legal_move){
    _board.erase(end);
    _board.add_piece(end, _board(start)->to_ascii());
    _board.erase(start);
    //If the move made it in check, reverses it
    if (in_check(_turn_white)) {
      _board.erase(end);
      if (endP != '0') {
	_board.add_piece(end, endP);
      }
      _board.add_piece(start, startP);
      legal_move = false;
      return legal_move;
    } else {
      _turn_white = !_turn_white;
    }
  }

  //It is impossible for a promotion to result in a check not caught before hand.
  //THis promotes the piece.
  if (_board(end)->to_ascii() == 'P' && end.second == '8') {
    _board.erase(end);
    _board.add_piece(end, 'Q');
  } else if (_board(end)->to_ascii() == 'p' && end.second == '1') {
    _board.erase(end);
    _board.add_piece(end, 'q');
  }

  return legal_move;
}

//Checks if in check and stuff
bool Chess::in_check( bool white ) const
{
  //Position of king
  std::pair<char, char>  king;
  //Finds positions of king.
  if (white) {
    king = find_king('K');
  } else {
    king = find_king('k');
  }

  //If vector of checkers is not 0, its being checked
  bool inCheck = true;
  Board boardCopy(_board);
  inCheck = checkers(king, boardCopy).size() == 0;
  return !inCheck;  
}

bool Chess::in_mate( bool white ) const
{
  //Positon of king
  std::pair<char, char> king;
  //Finds that position depending on color
  if (white) {
    king = find_king('K');
  } else {
    king = find_king('k');
  }

  //If its not in check, returns false
  if (!in_check(white)) {
    return false;
  }

  //Vector of all pieces that can be move for CHECKED PLAYER
  std::vector<std::pair<char, char>> pieces;
  //Loops through board to find CHECKED player pieces
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      if (_board(pos) != NULL && _board(pos)->is_white() == white) {
	pieces.push_back(pos);
      }
    }
  }

  //Takes EACH Checked Player Piece, loops through each position on board.
  //If that is a valid move, makes copy of board and makes that move ON THE
  //COPY. THen, it calls the checkers function to see if the king ON THE COPY
  //Is beging checked. If the size of the checkers vector is 0 for ANY position
  //Its not a mate.
  for (int x = 0; x < (int) pieces.size(); x++) {
    for (char row = '8'; row >= '1'; row--) {
      for (char col = 'A'; col <= 'H'; col++) {
	std::pair<char, char> pos = std::make_pair(col, row);
	if (_board.valid_move(pieces[x], pos, white)) {
	  Board boardCopy(_board);
	  if (boardCopy(pos) != NULL) {
	    boardCopy.erase(pos);
	  }
	  boardCopy.add_piece(pos, _board(pieces[x])->to_ascii());
	  boardCopy.erase(pieces[x]);
	  if (pieces[x] != king) {
	    pos = king;
	  }
	  if(checkers(pos, boardCopy).size() == 0) {
	    return false;
	  }
	}
      }
    }
  }

  //If the king cannot move out of the way AND no other piece can block/take
  //Its a checkmate.
  return true;
}

bool Chess::in_stalemate( bool white ) const
{

  //Position of the king
  std::pair<char, char>  king;
  //Finds positions of kings.
  if (white) {
    king = find_king('K');
  } else {
    king = find_king('k');
  }

  //Vector of all pieces that belong to color turn
  std::vector<std::pair<char, char>> pieces;
  //Finds those pieces and adds them to vector
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      if (_board(pos) != NULL && _board(pos)->is_white() == white) {
	pieces.push_back(pos);
      }
    }
  }

  //THis is nasty. For each piece, it loops through EVERY single
  //Position on board and sees if thats a valid move.
  //If it is, it creates a copy of the board and makes that move
  //ON THAT COPY. Then it checks if that puts king in check.
  //It checks by calling checkers function to get a vector of
  //all pieces that are checking the king. If that vector size
  //is zero for EVEN ONE position, returns false. Not stalemate.
  for (int x = 0; x < (int) pieces.size(); x++) {
    for (char row = '8'; row >= '1'; row--) {
      for (char col = 'A'; col <= 'H'; col++) {
	std::pair<char, char> pos = std::make_pair(col, row);
	if (_board.valid_move(pieces[x], pos, white)) {
	  Board boardCopy(_board);
	  if (boardCopy(pos) != NULL) {
	    boardCopy.erase(pos);
	  }
	  boardCopy.add_piece(pos, _board(pieces[x])->to_ascii());
	  boardCopy.erase(pieces[x]);
	  if (pieces[x] != king) {
	    pos = king;
	  }
	  if(checkers(pos, boardCopy).size() == 0) {
	    return false;
	  }
	}
      }
    }
  }

  //Other wise, its a stalemate
  return true;
}

//Returns a vector of all pieces able to capture king.
//Note, doesnt have to be king. Works for others as well, but not used that way.
std::vector<std::pair<char, char>> Chess::checkers(std::pair<char, char> king, Board& _board) const {
  //Vector of positions of pieces that can check king
  std::vector<std::pair<char, char>> checkers;
  //Loops through each position on Board
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      bool validMove = false;
      //If position has oppose king color piece, sees if its valid to take it
      if (_board(pos) != NULL && _board(pos)->is_white() != _board(king)->is_white()) {
	validMove = _board.valid_move(pos, king, _board(pos)->is_white());
      }
      //If yes, pushes that position to the vector
      if (validMove) {
	checkers.push_back(pos);
      }
    }
  }
  return checkers;
}

//Finds the king.
std::pair<char, char> Chess::find_king(char color) const {
  std::pair<char, char> kingPos;
  //Finds positions of kings.
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      if (_board(pos) != NULL) {
	//If the position is white king or black king
	if (_board(pos)->to_ascii() == color) {
	  kingPos = pos;
	} 
      }
    }
  }
  return kingPos;
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator << ( std::ostream& os , const Chess& chess )
{
	// Write the board out and then either the character 'w' or the character 'b', depending on whose turn it is
	return os << chess.board() << ( chess.turn_white() ? 'w' : 'b' );
}

std::istream& operator >> ( std::istream& is , Chess& chess )
{
  std::string row;
  for(char i = '8' ; i>='1'; --i){
    is >> row;
    for(char j = 'A'; j<='H'; ++j){
      chess.not_const_board().erase(std::make_pair(j,i));
      if(row[j-'A'] != '-'){
	chess.not_const_board().add_piece(std::make_pair(j,i),row[j-'A']);
      }
    }
  }
  std::string turn;
  is >> turn;
  if(turn[0] == 'w'){
    chess._turn_white = true;
  }
  else{
    chess._turn_white = false;
  }
  return is;
}
