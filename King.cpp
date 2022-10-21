//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2        

#include <string>
#include <utility>
#include <map>
#include "King.h"
#include <iostream>


using std::string;
using std::map;
using std::pair;
using std::make_pair;


//define the function legal_move_shape, which takes in two references, one to the start string, the other to the end string and test if such move is legal for a king.
bool King::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  if(scol == ecol && srow == erow){
    return false;
  }
  if(scol-ecol > 1 || scol-ecol < -1 || srow - erow > 1 || srow - erow < -1) {
    return false;
  }
  return true;
}

//Legalcap shape check
bool King::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  if(scol == ecol && srow == erow){
    return false;
  }
  if(scol-ecol > 1 || scol-ecol < -1 || srow - erow > 1 || srow - erow < -1) {
    return false;
  }
  return true;
}



 
