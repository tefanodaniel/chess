//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     


#include <string>
#include <utility>
#include <map>
#include "Queen.h"
#include <iostream>


using std::string;
using std::map;
using std::pair;
using std::make_pair;

bool Queen::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //when piece has not moved
  if(scol == ecol && srow == erow){
    return false;
  }
  //move diagnolly
  else if((scol - ecol) == (srow - erow) || (scol - ecol) == -(srow - erow)){
    return true;
  }
  //move vertically or horozontally
  else if(scol == ecol || srow == erow){
    return true;
  }
  
  return false;  
}

bool Queen::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;
  //when piece has not moved
  if(scol == ecol && srow == erow){
    return false;
  }
  //move diagnolly
  else if((scol - ecol) == (srow - erow) || (scol - ecol) == -(srow - erow)){
    return true;
  }
  //move vertically or horozontally
  else if(scol == ecol || srow == erow){
    return true;
  }
  
  return false;  
}
