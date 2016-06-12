#include "Chess.h"
#include <windows.h>

//
//-----------------------King-----------------------//
bool King::CheckMove(int i,int j){ //Checks available moves
     if(i==x && (j==y+1 || j==y-1)){return true;}
     if(i==x-1 && (j==y+1 || j==y-1 || j==y)){return true;}
     if(i==x+1 && (j==y+1 || j==y-1 || j==y)){return true;}
     if(hasmoved==false && (i==0 && j==6) && (x==0 && y==4)){return true;}//Castling right for white
     if(hasmoved==false && (i==7 && j==6) && (x==7 && y==4)){return true;}//Castling right for black
     if(hasmoved==false && (i==0 && j==2) && (x==0 && y==4)){return true;}//Castling left for white
     if(hasmoved==false && (i==7 && j==2) && (x==7 && y==4)){return true;}//Castling left for black
     return false;
}
//-----------------------END King-----------------------//


//-----------------------Queen-----------------------//
bool Queen::CheckMove(int i,int j){//Checks available moves
     if(i==x && j==y){return false;}
     if(i==x || j==y){return true;}
     if((x+y==i+j) || (x-y==i-j)){return true;}
     return false;
}
//-----------------------END Queen-----------------------//


//-----------------------Tower-----------------------//
bool Tower::CheckMove(int i,int j){//Checks available moves
     if(i==x && j==y){return false;}
     if(i==x || j==y){return true;} 
     return false;
}
//-----------------------END Tower-----------------------//


//-----------------------Horse-----------------------//
bool Horse::CheckMove(int i,int j){//Checks available moves
     if((i==x+2 || i==x-2) && (j==y+1 || j==y-1)){return true;}   
     if((i==x+1 || i==x-1) && (j==y+2 || j==y-2)){return true;}
     return false;
}
//-----------------------END Horse-----------------------//


//-----------------------Bishop-----------------------//
bool Bishop::CheckMove(int i,int j){//Checks available moves
     if(i==x && j==y){return false;}
     if((x+y==i+j) || (x-y==i-j)){return true;}//Check the diagonal moves
     return false;
}
//-----------------------END Bishop-----------------------//


//-----------------------Pawn-----------------------//
bool Pawn::CheckMove(int i,int j){//Checks available moves
     if(color){          //white
          if((i==x+1) && (j==y)){return true;}      
          if(((i==3) && (x==1)) && (j==y)){return true;} //En passant move
          if(((j==y+1) || (j==y-1)) && i==x+1){return true;} //Trying to capture a piece
          }
     else{ //Black
          if((i==x-1) && (j==y)){return true;}                 
          if(((i==4) && (x==6)) && (j==y)){return true;}
          if(((j==y+1) || (j==y-1)) && i==x-1){return true;}
          }
     return false;
}
//-----------------------END Pawn-----------------------//


//-----------------------Chessboard-----------------------//

//-----PRIVATE FUNCTIONS OF Checkboard--------//

bool Chessboard::CheckKing(int i,int j){
            if(((i==curx+1) && ((j==cury+1) || (j==cury-1) || (j==cury))) //Moves 1 square
               || ((i==curx-1) && ((j==cury+1) || (j==cury-1) || (j==cury)))
               || ((i==curx) && ((j==cury+1) || (j==cury-1)))){
               if(board[i][j]!=0){ //If this position is not empty
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()){ //If this position has the same color with the selected king
                    return false;
                  }                   
               }                 
               if(IsThreated(i,j)) return false;  //If is threaten in the new position
                return true; //Can do the move
              }//End of +1 square move   
            else{//If select castling   
                if(((i==7 && j==6) || (i==0 && j==6))){ //request right castling 
                  if(board[curx][cury]->HasMoved()) return false;//If King has moved castling unavailable
                  if(board[curx][cury]->GetColor()==WHITE){//If white king
                    if(IsThreated(curx,cury)) return false; //If is threaten castling unavailable
                    if(board[0][5]!=0 || board[0][6]!=0) return false;//If there is any piece in squares of castling
                    if(board[0][7]!=0){                                                   //If there is a piece in this potition
                       if(board[0][7]->GetType()=='T' && board[0][7]->GetColor()==WHITE){//and is a white tower
                         if(!board[0][7]->HasMoved()){                                   //and has not been moved
                              if(IsThreated(0,5)) return false;   //Check if the new move of the tower is threaten         
                              if(IsThreated(0,6)) return false;   //Check if the new move of the king is threaten        
                           return true;
                         }//return false;
                       }//return false;
                    }return false;//There is no piece in 0,7
                  }else{//if black king 
                    if(IsThreated(curx,cury)) return false;//If is threaten castling unavailable
                    if(board[7][5]!=0 || board[7][6]!=0) return false;//If there is any piece in squares of castling
                    if(board[7][7]!=0){                                                  //If there is a piece in this potition
                       if(board[7][7]->GetType()=='T' && board[7][7]->GetColor()==BLACK){//and is a black tower
                         if(!board[7][7]->HasMoved()){                                   //and has not been moved
                              if(IsThreated(7,5)) return false;   //Check if square 7,5 is threaten        
                              if(IsThreated(7,6)) return false;//Check if square 7,6 is threaten         
                           return true;
                         }//return false;
                       }//return false;
                    }return false;//there is no piece in 7,7         
                  }
                }else{//request left castling 
                      if(board[curx][cury]->HasMoved()) return false;//If King has moved 
                      if(board[curx][cury]->GetColor()==WHITE){//If white king
                         if(IsThreated(curx,cury)) return false; //If is threaten castling unavailable
                         if(board[0][1]!=0 || board[0][2]!=0 || board[0][3]!=0) return false;//If there is any piece in squares of castling
                         if(board[0][0]!=0){                                                  //If there is a piece in this potition
                            if(board[0][0]->GetType()=='T' && board[0][0]->GetColor()==WHITE){//and is a white tower
                               if(!board[0][0]->HasMoved()){                                   //and has not been moved
                                  if(IsThreated(0,1)) return false;   //Check if square 0,1 is threaten   
                                  if(IsThreated(0,2)) return false;   //Check if square 0,2 is threaten         
                                  if(IsThreated(0,3)) return false;   //Check if square 0,3 is threaten         
                                  return true;
                                  }//return false;
                               }//return false;
                            }return false;//there is no piece in 0,7
                      }else{//black king
                         if(IsThreated(curx,cury)) return false; //If is threaten castling unavailable
                         if(board[7][1]!=0 || board[7][2]!=0 || board[7][3]!=0) return false;//If there is any piece in squares of castling
                         if(board[7][0]!=0){                                                  //If there is a piece in this potition
                            if(board[7][0]->GetType()=='T' && board[7][0]->GetColor()==BLACK){//and is a black tower
                               if(!board[7][0]->HasMoved()){                                   //and has not been moved
                                  if(IsThreated(7,1)) return false;//Check if square 7,1 is threaten         
                                  if(IsThreated(7,2)) return false;//Check if square 7,2 is threaten        
                                  if(IsThreated(7,3)) return false;//Check if square 7,3 is threaten
                                  return true;
                               }//return false;
                            }//return false;//Its not black tower
                         }return false;//there is no piece in 7,7         
                      }
                }
            }
}

bool Chessboard::CheckQueen(int i,int j){//QUUEEN CAN DO THE SAME MOVES AS TOWER AND BISHOP
            int temp,tempx,tempy;//Help attributes, to check if there are objects between the current square and the last square
            if(curx==i){//If i is in the same line
              if(cury-j<0){//Right
                temp=cury+1;       //Start one position right   
                while(temp<j){    //Checking all squares until target square 
                     if(board[i][temp]!=0) 
                        return false;   
                     temp++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j>0 LEFT
                temp=cury-1;       //Start one position left
                while(temp>j){    //Checking all squares until target square 
                     if(board[i][temp]!=0) 
                        return false;   
                     temp--;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go    
              }
            }
            if(cury==j){//(chy==j) The move is on the same column
              if(curx-i<0){//Here is UP
                temp=curx+1;       //Start one position up
                while(temp<i){    //Checking all squares until target square 
                     if(board[temp][j]!=0) 
                        return false;   
                     temp++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go 
              }else{//chx-i>0 Here is DOWN
                temp=curx-1;       //Start one position down
                while(temp>i){    //Checking all squares until target square 
                     if(board[temp][j]!=0) 
                        return false;   
                     temp--;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }    
            }     
            if(i+j==curx+cury){//Here we check left diagonal
              if(cury-j>0){//If we are up and left
                tempx=curx+1;       //Start one position up and left   
                tempy=cury-1;
                while(tempy>j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy--;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j<0 Here is down and right
                tempx=curx-1;       
                tempy=cury+1;
                while(tempy<j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go    
              }
            }
            if(i-j==curx-cury){//i-j==chx-chy Here we check right diagonal
              if(cury-j<0){//The move is up and right
                tempx=curx+1;       //START one position up and right
                tempy=cury+1;
                while(tempy<j){    //Checking all squares until target square  
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j>0 Here is down and left
                tempx=curx-1;       //START one position DOWN and LEFT
                tempy=cury-1;
                while(tempy>j){    //Checking all squares until target square
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy--;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }
            }
}
     
bool Chessboard::CheckTower(int i,int j){
            int temp;//Help attribute to check if there are objects in squares
            if(curx==i){//Move is on the same line
              if(cury-j<0){//Here is right
                temp=cury+1;       //Start one position right   
                while(temp<j){    //Checking all squares until target square
                     if(board[i][temp]!=0) 
                        return false;   
                     temp++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j>0 Here is left
                temp=cury-1;       //Start one position left 
                while(temp>j){    //Checking all squares until target square 
                     if(board[i][temp]!=0) 
                        return false;   
                     temp--;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go   
              }
            }else{//(chy==j) move on the same column move
              if(curx-i<0){//Here is up
                temp=curx+1;       //Start one position up 
                while(temp<i){    //Checking all squares until target square 
                     if(board[temp][j]!=0) 
                        return false;   
                     temp++;
                }
                if(board[i][j]!=0){//!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chx-i>0 Here the move is down
                temp=curx-1;       //Start one position down
                while(temp>i){    //Checking all squares until target square  
                     if(board[temp][j]!=0) 
                        return false;   
                     temp--;
                }
                if(board[i][j]!=0){///!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }    
            }
}
     
bool Chessboard::CheckBishop(int i,int j){
            int tempx,tempy;//βοηθητικές μεταβλητές για τον έλεγχο των τετραγώνων αν έχουν αντικείμενο
            if(i+j==curx+cury){//Είναι στην αριστερή διαγώνιο
              if(cury-j>0){//Είναι πάνω αριστερά
                tempx=curx+1;       //Ξεκινά από μια θέση πιο πάνω και αριστερά   
                tempy=cury-1;
                while(tempy>j){    //Ελέγχει όλα τα τετράγωνα μέχρι πριν τον στόχο 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy--;
                }
                if(board[i][j]!=0){//!!!ΕΔΩ ΕΙΝΑΙ ΣΤΟΝ ΣΤΟΧΟ!!!Ελέγχει αν έχει κάτι στον στόχο
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//Αν έχουν το ίδιο χρώμα δεν μπορεί να πάει
                  else return true;//Αν δεν έχουν το ίδιο χρώμα επιστρέφει ΟΚ
                }else return true;//Aν δεν έχει τίποτα το τετραγωνάκι επιστρέφει ΟΚ
              }else{//chy-j<0 Είναι κάτω δεξιά
                tempx=curx-1;       //Ξεκινά από μια θέση πιο αριστερά
                tempy=cury+1;
                while(tempy<j){    //Ελέγχει όλα τα τετράγωνα μέχρι πριν τον στόχο 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy++;
                }
                if(board[i][j]!=0){//!!!ΕΔΩ ΕΙΝΑΙ ΣΤΟΝ ΣΤΟΧΟ!!!Ελέγχει αν έχει κάτι στον στόχο
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//Αν έχουν το ίδιο χρώμα δεν μπορεί να πάει
                  else return true;//Αν δεν έχουν το ίδιο χρώμα επιστρέφει ΟΚ
                }else return true;//Aν δεν έχει τίποτα το τετραγωνάκι επιστρέφει ΟΚ    
              }
            }else{//i-j==curx-cury Είναι στην δεξιά διαγώνιο
              if(cury-j<0){//Είναι πάνω δεξιά
                tempx=curx+1;       //Ξεκινά από μια θέση πιο πάνω δεξιά
                tempy=cury+1;
                while(tempy<j){    //Ελέγχει όλα τα τετράγωνα μέχρι πριν τον στόχο 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy++;
                }
                if(board[i][j]!=0){//!!!ΕΔΩ ΕΙΝΑΙ ΣΤΟΝ ΣΤΟΧΟ!!!Ελέγχει αν έχει κάτι στον στόχο
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//Αν έχουν το ίδιο χρώμα δεν μπορεί να πάει
                  else return true;//Αν δεν έχουν το ίδιο χρώμα επιστρέφει ΟΚ
                }else return true;//Aν δεν έχει τίποτα το τετραγωνάκι επιστρέφει ΟΚ
              }else{//chy-j>0 Είναι κάτω αριστερά
                tempx=curx-1;       //Ξεκινά από μια θέση πιο κάτω αριστερά
                tempy=cury-1;
                while(tempy>j){    //Ελέγχει όλα τα τετράγωνα μέχρι πριν τον στόχο 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy--;
                }
                if(board[i][j]!=0){//!!!ΕΔΩ ΕΙΝΑΙ ΣΤΟΝ ΣΤΟΧΟ!!!Ελέγχει αν έχει κάτι στον στόχο
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//Αν έχουν το ίδιο χρώμα δεν μπορεί να πάει
                  else return true;//Αν δεν έχουν το ίδιο χρώμα επιστρέφει ΟΚ
                }else return true;//Aν δεν έχει τίποτα το τετραγωνάκι επιστρέφει ΟΚ
              }
            }           
}

bool Chessboard::CheckPawn(int i,int j){
            if(board[curx][cury]->GetColor()){  //Για τα λευκά
               if(j==cury){//για να πάει στην αρχή 2 βήματα μπροστά ή γενικά 1 μπροστά
                  if(i==3 && curx==1){      //Έλεγχος αν στην αρχή προσπαθεί κίνηση 2 τετραγώνων
                     if(board[2][cury]==0 && board[3][cury]==0)  //ελέγχει αν έχει κάτι μπροστά του   
                        return true;
                     else
                        return false;
                     }
                  if(i==curx+1){    //Έλεγχος για μια κίνηση μπροστά
                     if(board[i][cury]==0)  //ελέγχει αν έχει κάτι μπροστά του   
                        return true;
                     else
                        return false;           
                  }
                }
               if(j==cury-1){             //Αν θέλει να πάει μπροστά αριστερά να "φάει" κάποιο αντίπαλο κομμάτι
                  if(board[curx+1][j]!=0){ 
                     if(board[curx+1][j]->GetColor()==BLACK)          
                        return true;
                     else
                        return false;
                     }
                  else{ //Αν δεν έχει αντικείμενο στη θέση αριστερά μπροστά ελέγχει για en passat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==BLACK)){//Ελέγχει αν έχει 
                           if(board[curx][j]->HasMoved()){//δίπλα του μαύρο πιόνι και έχει κάνει κίνηση 2 τετραγώνων
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;//δεν μπορεί να κάνει την κίνηση αριστερά αριστερά
                  }
                }
               if(j==cury+1){             //Αν θέλει να πάει μπροστά δεξιά να "φάει" κάποιο αντίπαλο κομμάτι
                  if(board[curx+1][j]!=0){ 
                     if(board[curx+1][j]->GetColor()==BLACK)          
                        return true;
                     else
                        return false;
                     }
                  else{ //Αν δεν έχει αντικείμενο στη θέση αριστερά μπροστά ελέγχει για en passat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==BLACK)){//Ελέγχει αν έχει 
                           if(board[curx][j]->HasMoved()){//δίπλα του μαύρο πιόνι και έχει κάνει κίνηση 2 τετραγώνων
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;//δεν μπορεί να κάνει την κίνηση αριστερά δεξιά
                  }
               }
            }
            else{    //Για τα μαύρα
               if(j==cury){//για να πάει στην αρχή 2 βήματα μπροστά ή γενικά 1 μπροστά
                  if(i==4 && curx==6){      //Έλεγχος αν στην αρχή προσπαθεί κίνηση 2 τετραγώνων
                     if(board[5][cury]==0 && board[4][cury]==0)  //ελέγχει αν έχει κάτι μπροστά του   
                        return true;
                     else
                        return false;
                     }
                  if(i==curx-1){    //Έλεγχος για μια κίνηση μπροστά
                     if(board[i][cury]==0)  //ελέγχει αν έχει κάτι μπροστά του   
                        return true;
                     else
                        return false;           
                  }
                }
               if(j==cury-1){             //Αν θέλει να πάει μπροστά αριστερά να "φάει" κάποιο αντίπαλο κομμάτι
                  if(board[curx-1][j]!=0){ 
                     if(board[curx-1][j]->GetColor()==WHITE)          
                        return true;
                     else
                        return false;
                     }
                  else{ //Αν δεν έχει αντικείμενο στη θέση αριστερά μπροστά ελέγχει για en passat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==WHITE)){//Ελέγχει αν έχει
                           if(board[curx][j]->HasMoved()){//δίπλα του μαύρο πιόνι και έχει κάνει κίνηση 2 τετραγώνων
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;//δεν μπορεί να κάνει την κίνηση αριστερά δεξιά
                  }    
                }
               if(j==cury+1){             //Αν θέλει να πάει μπροστά δεξιά να "φάει" κάποιο αντίπαλο κομμάτι
                  if(board[curx-1][j]!=0){ 
                     if(board[curx-1][j]->GetColor()==WHITE)          
                        return true;
                     else
                        return false;
                     } 
                  else{ //Αν δεν έχει αντικείμενο στη θέση αριστερά μπροστά ελέγχει για en passat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==WHITE)){//Ελέγχει αν έχει 
                           if(board[curx][j]->HasMoved()){//δίπλα του μαύρο πιόνι και έχει κάνει κίνηση 2 τετραγώνων
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;//δεν μπορεί να κάνει την κίνηση αριστερά δεξιά
                  }
               }
            }
}
//-----END PRIVATE FUNCTIONS OF Checkboard-----//


Chessboard::Chessboard(){
            play=WHITE;
            curx=-1;
            cury=-1;
            for(int i=0;i<8;i++)
               for(int j=0;j<8;j++)
                   board[i][j]=0;                  
}

void Chessboard::SetPiece(Piece * p,int i,int j){
            board[i][j]=p;           //Ενημέρωση πίνακα            
            board[i][j]->SetPos(i,j); //Ενημέρωση αντικειμένου
}

void Chessboard::PrintChessBoard(){
            HANDLE hConsole;
            hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
            for(int i=7;i>=0;i--){
               SetConsoleTextAttribute(hConsole,0x0002 | 0x0008);
               cout<<i;
               for(int j=0;j<8;j++){
                   if((i+j)%2==0)                //Έλεγχος για το χρώμα που έχει το κουτάκι
                     SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                   else
                     SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                   cout<<" ";
                   if(board[i][j]!=0){  //Έλεγχος για το χρώμα που έχει το κομμάτι
                      if(board[i][j]->GetColor()){     //Color is White
                         if((i+j)%2==0)                //Έλεγχος για το χρώμα που έχει το κουτάκι
                           SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                         else
                           SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);   
                         cout<<board[i][j]->GetType();
                      }else{                            //Color is Black
                         SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                         if((i+j)%2==0)                //Έλεγχος για το χρώμα που έχει το κουτάκι
                           SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                         else
                           SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                         cout<<board[i][j]->GetType();
                      }
                      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |  FOREGROUND_INTENSITY);
                   }else
                      {cout<<" ";}
                   if(j==7){ 
                     if((i+j)%2==0)                //Έλεγχος για το χρώμα που έχει το κουτάκι
                       SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                     else
                       SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                   }
               }
               cout<<endl;
            }  
            SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout<<"  ";
            for(int i=0;i<8;i++)
               cout<<i<<" ";
            cout<<"\n\n";
            if(play){     //checks who plays
               SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               cout<<"White player's turn\n";
            }else{
               SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               cout<<"Black player's turn\n";
            }
            SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Chessboard::Clear(){
            for(int i=0;i<8;i++){
               for(int j=0;j<8;j++){
                   if(board[i][j]!=0){//if contains an object
                      board[i][j]->~Piece();
                      board[i][j]=0;
                   } 
               }
            }
            play=WHITE;
}

bool Chessboard::ChoosePiece(int i,int j){
            if(board[i][j]!=0){
               if(board[i][j]->GetColor()==play){//Εαν έχει επιλεγεί κομμάτι από τα δικά του κρατά τις συντεταγμένες του
                  curx=i;
                  cury=j;
                  return true;
               }
            }
            return false;
}

void Chessboard::ChosenPiece(){ //Καλείτε από την PrintChessBoard και εμφανίζει τι είναι και που βρίσκεται 
            string type;                   
            switch(board[curx][cury]->GetType()){
                 case 'K' : {type="King";break;}                                   
                 case 'Q' : {type="Queen";break;}
                 case 'T' : {type="Tower";break;}                              
                 case 'B' : {type="Bishop";break;}
                 case 'H' : {type="Horse";break;}
                 case 'P' : {type="Pawn";break;}                              
            }     
            cout<<"\nYou choose "<<type<<" in ("<<curx<<","<<cury<<")\n";
}

bool Chessboard::IsThreated(int x,int y){//x,y μελλοντικές θέσεις
            int i,j,tempx,tempy;
            bool tem;
            char ch;
            for(i=0;i<8;i++){
               for(j=0;j<8;j++){//Σαρώνεται όλος ο πίνακας
                  if(board[i][j]!=0){
                    if(board[i][j]->GetColor()!=play){
                      ch=board[i][j]->GetType();
                      if((ch=='K') || (ch=='H')){
                         tem=board[i][j]->CheckMove(x,y);
                      }   
                      if(ch=='P'){//αν είναι πιόνι ρώταμε αν απειλεί ένα τετράγωνο μπροστά του τότε δεν απειλεί
                           if(((y==board[i][j]->Gety()) && (x==board[i][j]->Getx()+1))  
                             ||  ((y==board[i][j]->Gety()) && (x==board[i][j]->Getx()-1)))
                             {tem=false;}//δεν απειλεί
                           else tem=board[i][j]->CheckMove(x,y);
                      }
                      if(tem==true) return true;//αν απειλούν επιστρέφει ότι απειλείται
                    }
                  }                 
               }                 
            }
            //εδω θα γινεται έλεγχος για queen tower
            i=x+1;
            j=y;
            while(i<8){//έλεγχος στην στήλη(πάνω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else i=15;//βγαίνει από την επανάληψη
               }
               i++;    
            }
            
            i=x-1;
            j=y;
            while(i>-1){//έλεγχος στην στήλη(κάτω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else i=-15;//βγαίνει από την επανάληψη
               }
               i--;
            }    
            
            i=x;
            j=y+1;
            while(j<8){//έλεγχος στην γραμμή(δεξιά)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else j=15;//βγαίνει από την επανάληψη
               }
               j++;
            }

            i=x;
            j=y-1;
            while(j>-1){//έλεγχος στην γραμμή(αριστερά)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else j=-15;//βγαίνει από την επανάληψη
               }
               j--;
            }
            
            //εδω θα γινεται έλεγχος για queen bishop
            i=x+1;
            j=y-1;
            while((i<8) && (j>-1)){//έλεγχος στην αριστερή διαγώνιο (πάνω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=15;j=-15;}//βγαίνει από την επανάληψη
               }
               i++;
               j--;
            }
            
            i=x-1;
            j=y+1;
            while((i>-1) && (j<8)){//έλεγχος στην αριστερή διαγώνιο (κάτω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=-15;j=15;}//βγαίνει από την επανάληψη
               }
               i--;
               j++;
            }
            
            i=x+1;
            j=y+1;
            while((i<8) && (j<8)){//έλεγχος στην δεξιά διαγώνιο (πάνω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=15;j=15;}//βγαίνει από την επανάληψη
               }
               i++;
               j++;
            }
            
            i=x-1;
            j=y-1;
            while((i>-1) && (j>-1)){//έλεγχος στην δεξιά διαγώνιο (κάτω)
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=-15;j=-15;}//βγαίνει από την επανάληψη
               }
               i--;
               j--;
            }
            
            return false;//εδώ έχει περάσει όλους τους ελέγχους και αυτό σημαίνει ότι δεν απειλείται
}


bool Chessboard::CheckMove(int i,int j){
            if(!board[curx][cury]->CheckMove(i,j)){return false;}              
            switch(board[curx][cury]->GetType()){
                          case 'K' : {if(CheckKing(i,j)){return true;}else{return false;}}
                          case 'Q' : {if(CheckQueen(i,j)){return true;}else{return false;}}
                          case 'T' : {if(CheckTower(i,j)){return true;}else{return false;}}
                          case 'H' : {if(board[i][j]!=0){if(board[i][j]->GetColor()==play) return false;}return true;}
                          case 'B' : {if(CheckBishop(i,j)){return true;}else{return false;}}
                          case 'P' : {if(CheckPawn(i,j)){return true;}else{return false;}}
                          }
}

                                                
int Chessboard::Move(int i,int j){//Eπιστρέφει 1 αν "φαγωθει" o λευκός βασιλιάς, 2 αν είναι ο μαύρος και 0 για άλλη περίπτωση
            HANDLE hConsole;
            hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
            
            if(board[i][j]!=0){
               if(board[i][j]->GetType()=='K'){   //Aν φαγωθεί βασιλιάς τότε το παιχνίδι τελειώνει
                 if(board[i][j]->GetColor()==WHITE){ 
                   SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                   return 1;
                 }else
                   return 2;  
               }
               board[i][j]->~Piece();//Αν εκεί που θέλει να πάει έχει κομμάτι θα καταστραφεί
            }
            if(board[curx][cury]->GetType()=='P'){//Έλεγχος για κινήσεις πιονιών
               if(((i==curx+2) && (curx==1)) || ((i==curx-2) && (curx==6))){
                  board[curx][cury]->ChangeMove();//Eδώ έχει κάνει κίνηση 2 τετραγώνων και ενημερώνεται το πιόνι
               }else
               /*if((i==curx+1) || (i==curx-1))*/{
                  if(board[curx][cury]->HasMoved())//Aν κάνει γενικά μια κίνηση ελέγχει αν πιο πριν είχε κάνει διπλή κίνηση
                     board[curx][cury]->ChangeMove();//τότε ενημερώνεται το αντικείμενο ότι δεν μπορεί να φαγωθει με enpassant      
               }
               if(j==cury-1){//Αν πηγαίνει αριστερά
                  if(board[i][j]==0){//Αν δεν έχει τίποτα εκεί που πάει τότε αριστερά enpassant                                   
                     board[curx][j]->~Piece();
                     board[curx][j]=0;
                  }
               }
               if(j==cury+1){//Αν πηγαίνει δεξιά
                  if(board[i][j]==0)//Αν δεν έχει τίποτα εκεί που πάει τότε δεξιά enpassant                                   
                     board[curx][j]->~Piece();
                     board[curx][j]=0;
               }
               if(i==7){
                   int ch;             //Aν έχει φτάσει στην άλλη μεριά λευκό πιόνι                                    
                   char cho[5];
                   do{
                    cout<<"\nCHOOSE TYPE OF PROMOTION\n";
                    cout<<"1: QUEEN \n";
                    cout<<"2: BISHOP\n";
                    cout<<"3: TOWER \n";
                    cout<<"4: HORSE \n";
                    cin >> cho;
                    ch=atoi(cho);
                   }while(ch<1 || ch>4);  
                   switch(ch){
                          case 1 : {board[curx][cury]=new Queen(WHITE);break;}           
                          case 2 : {board[curx][cury]=new Bishop(WHITE);break;}
                          case 3 : {board[curx][cury]=new Tower(WHITE);break;}
                          case 4 : {board[curx][cury]=new Horse(WHITE);break;}    
                   }//end switch
                   cin.ignore();//Γιατί κρατάει το \n όταν επιλέγουμε πιο πάνω με την cin
              }else{if(i==0){     //Aν έχει φτάσει στην άλλη μεριά μαύρο πιόνι
                      int ch;             //Aν έχει φτάσει στην άλλη μεριά λευκό πιόνι                                    
                      char cho[5];
                      do{
                         cout<<"\nCHOOSE TYPE OF PROMOTION\n";
                         cout<<"1: QUEEN \n";
                         cout<<"2: BISHOP\n";
                         cout<<"3: TOWER \n";
                         cout<<"4: HORSE \n";
                         cout<<"Choose:";
                         cin >> cho;
                         ch=atoi(cho);
                         }while(ch<1 || ch>4);  
                         switch(ch){
                             case 1 : {board[curx][cury]=new Queen(BLACK);break;}           
                             case 2 : {board[curx][cury]=new Bishop(BLACK);break;}
                             case 3 : {board[curx][cury]=new Tower(BLACK);break;}
                             case 4 : {board[curx][cury]=new Horse(BLACK);break;}    
                         }//end switch      
                    cin.ignore();//Γιατί κρατάει το \n όταν επιλέγουμε πιο πάνω με την cin
                    }//end if(i==0)
              }                                   
            }
            if((board[curx][cury]->GetType()=='T') || (board[curx][cury]->GetType()=='K')){//δεξί roque 
              if((board[curx][cury]->GetType()=='K') && (i==board[curx][cury]->Getx() && j==board[curx][cury]->Gety()+2)){
                 if(play){
                   board[0][7]->ChangeMove();//Ο πύργος κινήθηκε
                   board[0][7]->SetPos(0,5);
                   board[0][5]=board[0][7];
                   board[0][7]=0;
                 }else{
                   board[7][7]->ChangeMove();//Ο πύργος κινήθηκε
                   board[7][7]->SetPos(7,5);
                   board[7][5]=board[7][7];
                   board[7][7]=0;    
                 } //αριστερό roque
              }else{if((board[curx][cury]->GetType()=='K') && (i==board[curx][cury]->Getx() && j==board[curx][cury]->Gety()-2))
                 if(play){
                   board[0][0]->ChangeMove();//Ο πύργος κινήθηκε
                   board[0][0]->SetPos(0,3);
                   board[0][3]=board[0][0];
                   board[0][0]=0;
                 }else{
                   board[7][0]->ChangeMove();//Ο πύργος κινήθηκε
                   board[7][0]->SetPos(7,3);
                   board[7][3]=board[7][0];
                   board[7][0]=0;    
                 } 
              }
              board[curx][cury]->ChangeMove();//Ο βασιλιάς κινήθηκε
            }
            board[curx][cury]->SetPos(i,j);//Το επιλεγμένο κομμάτι "μαθαίνει" ποια είναι η νέα του θέση
            board[i][j]=board[curx][cury]; //Μεταφέρεται το κομμάτι στη νέα του θέση 
            board[curx][cury]=0;           //Η παλία πλέον είναι κενή
            curx=i;
            cury=j;
            play=!play;//Αλλάζει ο παίκτης     
            return 0;
}
//-----------------------End Chessboard-----------------------//
