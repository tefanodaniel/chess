//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

//Tianyue Ou tou3                                                                                                                            
                                                                                                                                               

#include <string>
#include <utility>
#include <map>
#include "Piece.h"
#include "Rook.h"


using std::string;
using std::map;
using std::pair;
using std::make_pair;

//define the function legal_move_shape for rook, which takes in two references, one to the start string, the other to the end string, and test if the move is legal for a rook. Return true if yes and false otherwise
bool Rook::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //check if it is moving
  if(scol == ecol && srow == erow){
    return false;
  }
  //check if it is moving in a rook's way
  if(scol == ecol || srow == erow){
    return true;
  }
  return false;

}


//check if the capture move is legal for rook
bool Rook::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //check if it is moving
  if(scol == ecol && srow == erow){
    return false;
  }
  //check if it is moving in a rook's way
  if(scol == ecol || srow == erow){
    return true;
  }
  return false;
}



