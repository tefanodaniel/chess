//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
using std::make_pair;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board( void ){}

const Piece* Board::operator()( std::pair< char , char > position ) const
{

  std::map<std::pair<char, char>, Piece*>::const_iterator it;
  for (it = _occ.cbegin(); it != _occ.cend(); it++) {
    if (it->first == position) {
      return it->second;
    }
  }
	return NULL;
}

//Copy Constructor
Board::Board(const Board& _board) {
  std::map<std::pair<char, char>, Piece*> _occ;
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      if (_board._occ.find(pos) != _board._occ.end()) {
	add_piece(pos, _board(pos)->to_ascii());
      }
    }
  }
}

//Adds piece
bool Board::add_piece( std::pair< char , char > position , char piece_designator )
{
  Piece* test = create_piece(piece_designator);
  if (test == NULL) {
    //Beta
    delete test;
    return false;
  }
  delete test;
  if (_occ.find(position) != _occ.end()) {
    return false;
  }
  if (position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8') {
    return false;
  }
	_occ[ position ] = create_piece( piece_designator );
	return true;
}

//Checks if it has_valid_kings. I interpreted this as having 2 kings always one black one white.
bool Board::has_valid_kings( void ) const
{
  int bKingCount = 0;
  int wKingCount = 0;
  for (std::map<std::pair<char, char>, Piece*>::const_iterator it = _occ.cbegin(); it != _occ.cend(); it++) {
    char piece = it->second->to_ascii();
    if (piece == 'K') {
      wKingCount += 1;
    } else if (piece == 'k') {
      bKingCount += 1;
    }
  }
  if (bKingCount != 1 || wKingCount != 1) {
    return false;
  }
  return true;
}

//Checks for valid move
bool Board::valid_move( std:: pair< char, char > start, std::pair< char , char > end, bool white) const {

    bool legal_move = true;
    char scol = start.first;
    char ecol = end.first;
    char srow = start.second;
    char erow = end.second;
    //check if location are valid
    if(scol > 'H' || scol < 'A' || ecol > 'H' || ecol < 'A' || srow > '8' || srow < '1' || erow > '8' || erow < '1'){
        return false;
    }
    
    //check if it acctually moved
    if (start == end) {
      return false;
    }
    
    // check that piece exists at start location
    if (_occ.find(start) == _occ.end()) {
      return false;
    }
    
    Piece* moving = _occ.at(start);
    // check that piece belongs to whoever's turn it is
    if (white) {
        if (!moving->is_white()) {
            return false;
        }
    } else {
        if (moving->is_white()) {
            return false;
        }
    }
   
    // check if move is capturing something and if something is opposite color
    bool capture = false;
    Piece* attacked = NULL;
    if (_occ.find(end) != _occ.end()) {
      attacked = _occ.at(end);
      if (moving->is_white() != !attacked->is_white()) {
	return false;
      } else {
	capture = true;
      }
    }

    // check that valid piece move shape
    if (capture) {
      if (!(moving->legal_capture_shape(start, end))) {
            return false;
        }
    } else {
      if (!(moving->legal_move_shape(start, end))) {
            return false;
        }
    }
    // check that nothing is blocking this piece from its target destination.
    char pShape = path_shape(start, end);
    if (pShape == 's') {
      if (!path_legal(start, end)) {
	return false;
      }
    } else if (pShape == 'd') {
      if (!path_legal_diagnol(start, end)) {
	return false;
      }
    } else if (pShape == 'r') {
      //Do Nothing
      legal_move = legal_move;
    }
    
    return legal_move;
}

//Checks if diagonal path is clear
bool Board::path_legal_diagnol( std::pair< char , char > start , std::pair< char , char > end) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  int difference;
  bool blocking = false;
  //get the postive difference between ending and starting position
  if(_occ.find(start)!=_occ.end()){
    if(ecol - scol > 0){
      difference = ecol - scol;

    }
    else{
      difference = scol - ecol;
    }
    
    for(int i = 1 ; i < difference ; ++i){
      if(_occ.find(make_pair(scol + (((ecol-scol)/difference)*i),srow + (((erow-srow)/difference)*i))) != _occ.end()){
	blocking = true;
	break;
      }
    }
    return !blocking;
  }
  else{
    std::cout << "no piece at position" << std::endl;
    return false;
  }
}

//Checks if piece is in the way?
bool Board::path_legal( std::pair< char , char > start , std::pair< char , char > end) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  int difference;
  char dir;
  bool blocking = false;
  //Beta Code
  if (_occ.find(start) == _occ.end()) {
    std::cout << "No Piece At Start" << std::endl;
    return false;
  }
  if (scol > 'H' || scol < 'A' || ecol > 'H' || ecol < 'A' || srow < '1' || srow > '8' || erow < '1' || erow > '8') {
    std::cout << "Out Of Bounds Start/End Position" << std::endl;
    return false;
  }
  //If its a knight, just return true.
  if (_occ.at(start)->to_ascii() == 'N' || _occ.at(start)->to_ascii() == 'n') {
    return true;
  }
  //Beta Code end
  //East
  if(ecol - scol > 0){
    difference = ecol - scol;
    dir = 'e';
  }
  //West
  else if(scol - ecol > 0){
    difference = scol - ecol;
    dir = 'w';
  }
  //North
  else if(erow - srow > 0){
    difference = erow - srow;
    dir = 'n';
  }
  //South
  else if (srow - erow > 0){
    difference = srow - erow;
    dir = 's';
  }
  //Beta Code
  std::pair<char, char> curr = start;
  if (dir == 'e') {
    for (int x = 1; x < difference; x++) {
      curr.first += 1;
      if (_occ.find(curr) != _occ.end()) {
	blocking = true;
	break;
      }
    }
  } else if (dir == 'w') {
    for (int x = 1; x < difference; x++) {
      curr.first -= 1;
      if (_occ.find(curr) != _occ.end()) {
	blocking = true;
	break;
      }
    }
  } else if (dir == 'n') {
    for (int x = 1; x < difference; x++) {
      curr.second += 1;
      if (_occ.find(curr) != _occ.end()) {
	blocking = true;
	break;
      }
    }
  } else if (dir == 's') {
    for (int x = 1; x < difference; x++) {
      curr.second -= 1;
      if (_occ.find(curr) != _occ.end()) {
	blocking = true;
	break;
      }
    }
  } else {
    std::cout << "Not Vertical/Horizontal Movement" << std::endl;
  }
  //Beta Code End
  return !blocking;
}

//Checks what shape the path is. For the mystery piece
char Board::path_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //Return s for straiht path shape
  if (start.second == end.second || start.first == end.first) {
    return 's';
  }

  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //Return d for diagonal path shape
  if((scol - ecol) == (srow - erow) || (scol - ecol) == -(srow - erow)){
    return 'd';
  }

  //Return r for random path shape
  return 'r';
}

//Erases piece at positon.
void Board::erase(std::pair<char, char> position) {
  std::map<std::pair<char, char>, Piece*>::iterator it = _occ.find(position);
  if (it != _occ.end()) {
    delete _occ[position];
    _occ[position] = NULL;
    _occ.erase(position);
  }
}

//THe display. Kinda sucks but it works.
void Board::display( void ) const
{
  for (char row = '8'; row >= '1'; row--) {
    for (char col = 'A'; col <= 'H'; col++) {
      std::pair<char, char> pos = std::make_pair(col, row);
      if (_occ.find(pos) != _occ.cend()) {
	std::cout << _occ.at(pos)->to_ascii();
      } else {
	std::cout << "_";
      }
    }
    std::cout << "" << std::endl;
  }
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator << ( std::ostream& os , const Board& board )
{
	for( char r='8' ; r>='1' ; r-- )
	{
		for( char c='A' ; c<='H' ; c++ )
		{
			const Piece* piece = board( std::pair< char , char >( c , r ) );
			if( piece ) os << piece->to_ascii();
			else        os << '-';
		}
		os << std::endl;
	}
	return os;
}
