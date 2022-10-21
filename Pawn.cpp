//Tianyue Ou tou3 Jianda Chen jchen242 Stefano Tusa stusa2                                                                                     

//Tianyue Ou tou3  Justin Chen jchen 242         
#include <string>
#include <utility>
#include <map>
#include "Pawn.h"
#include <iostream>


using std::string;
using std::map;
using std::pair;
using std::make_pair;

//check if the capture move is legal for Pawn
bool Pawn::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char scol = start.first;
  char ecol = end.first;
  char srow = start.second;
  char erow = end.second;

  
  if(is_white()){
    if((erow - srow) == 1 && ((ecol - scol) == 1 || (ecol - scol) == -1)){
      return true;
    }
  }
  else{
    if((erow - srow) == -1 && ((ecol - scol) == 1 || (ecol - scol) == -1)){
      return true;
    }
  }
  return false;
}

//check if the move is legal for pawn
bool Pawn::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const{
  char srow = start.second;
  char erow = end.second;
  char scol = start.first;
  char ecol = end.first;
  //when piece moves horozontally or has not moved
  if( srow == erow || scol != ecol){
    return false;
  }


  int difference = erow - srow;

  //when piece moves more than two steps
  if(difference != 1 && difference != -1 && difference != 2 && difference != -2) {
    return false;
  }
  
  //when piece moves backward                                                                                                                
  if(is_white()){
    if(difference < 0){
      return false;
    }
  }
  else{
    if(difference > 0){
      return false;
    }
  }

  //when piece moves more than 1 step when it has been moved
  if(is_white()){
    if(srow != '2' && difference != 1){
      return false;
    }
  } else {
    if(srow != '7' && difference != -1){
      return false;
    }
  }
  return true;
}
