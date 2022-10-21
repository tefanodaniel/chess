//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

//Tianyue Ou tou3  Justin Chen jchen 242

#include <string>
#include <utility>
#include <map>
#include "Knight.h"
#include <iostream>


using std::string;
using std::map;
using std::pair;
using std::make_pair;

bool Knight::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //when piece has not moved                                                                                                                   
  if(scol == ecol && srow == erow){
    return false;
  }

  //when piece moves in a knight's way
  if((ecol-scol) == 2 || (ecol - scol) == -2){
    if((erow - srow) == 1 || (erow - srow) == -1){
      return true;
    }
    return false;
  } else if((ecol-scol) == 1 || (ecol - scol) == -1) {
    if((erow - srow) == 2 || (erow - srow) == -2) {
      return true;
    }
    return false;
  }
  return false;
}

bool Knight::legal_capture_shape(std::pair<char, char> start , std::pair<char, char> end ) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //when piece has not moved                                                                                                                   
  if(scol == ecol && srow == erow){
    return false;
  }

  //when piece moves in a knight's way
  if((ecol-scol) == 2 || (ecol - scol) == -2){
    if((erow - srow) == 1 || (erow - srow) == -1){
      return true;
    }
    return false;
  } else if((ecol-scol) == 1 || (ecol - scol) == -1) {
    if((erow - srow) == 2 || (erow - srow) == -2) {
      return true;
    }
    return false;
  }
  return false;
}
