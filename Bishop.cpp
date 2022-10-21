
//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     
//Tianyue Ou tou3  Justin Chen Jchen242

#include <string>
#include <utility>
#include <map>
#include "Bishop.h"
#include <iostream>

using std::string;
using std::map;
using std::pair;
using std::make_pair;


bool Bishop::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
  char scol = start.first;
  char ecol = end.first;
  int srow = start.second - '0';
  int erow = end.second - '0';
  //when piece is not moved
  if(scol == ecol && srow == erow){
    return false;
  }
  //move diagnolly                                                                                                                           
  else if((scol - ecol) == (srow - erow) || (scol - ecol) == -(srow - erow)){
    return true;
  }
  return false;  
}

bool Bishop::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //when piece is not moved
  if(scol == ecol && srow == erow){
    return false;
  }
  //move diagnolly                                                                                                                           
  else if((scol - ecol) == (srow - erow) || (scol - ecol) == -(srow - erow)){
    return true;
  }
  return false;  
}
