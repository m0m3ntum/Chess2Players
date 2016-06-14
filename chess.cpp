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
            int tempx,tempy;//Help attributes to check squares if there is any object
            if(i+j==curx+cury){//The move is on left diagonal
              if(cury-j>0){//Up and left
                tempx=curx+1;       //Start one position up and left   
                tempy=cury-1;
                while(tempy>j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy--;
                }
                if(board[i][j]!=0){///!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j<0  Here is down right
                tempx=curx-1;       
                tempy=cury+1;
                while(tempy<j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy++;
                }
                if(board[i][j]!=0){///!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go   
              }
            }else{//i-j==curx-cury Here is right diagonal
              if(cury-j<0){//Here is up and right
                tempx=curx+1;       
                tempy=cury+1;
                while(tempy<j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx++;
                     tempy++;
                }
                if(board[i][j]!=0){///!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }else{//chy-j>0 Here is down and left
                tempx=curx-1;       
                tempy=cury-1;
                while(tempy>j){    //Checking all squares until target square 
                     if(board[tempx][tempy]!=0) 
                        return false;   
                     tempx--;
                     tempy--;
                }
                if(board[i][j]!=0){///!!!Here we are on target. Check if there is something
                  if(board[i][j]->GetColor()==board[curx][cury]->GetColor()) return false;//If they have same color, can't go there
                  else return true;//Else CAN go there
                }else return true;//Here there is nothing in the square. CAN go
              }
            }           
}

bool Chessboard::CheckPawn(int i,int j){
            if(board[curx][cury]->GetColor()){  //For white pawn
               if(j==cury){//Move forward
                  if(i==3 && curx==1){      //Checking if the move is 2 squares forward
                     if(board[2][cury]==0 && board[3][cury]==0)  //Checking if there is something in front of it 
                        return true;
                     else
                        return false;
                     }
                  if(i==curx+1){    //Checking if the move is 1 square forward
                     if(board[i][cury]==0)  //Checking if there is something in front of it    
                        return true;
                     else
                        return false;           
                  }
                }
               if(j==cury-1){             //Here is trying to capture one piece left
                  if(board[curx+1][j]!=0){ 
                     if(board[curx+1][j]->GetColor()==BLACK)          
                        return true;
                     else
                        return false;
                     }
                  else{ //If there is NOT any object then check for enpassat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==BLACK)){//Checking if there is any
                           if(board[curx][j]->HasMoved()){//black pawn and has done 2 squares move
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;
                  }
                }
               if(j==cury+1){             //Here is trying to capture one piece right
                  if(board[curx+1][j]!=0){ 
                     if(board[curx+1][j]->GetColor()==BLACK)          
                        return true;
                     else
                        return false;
                     }
                  else{ //If there is NOT any object then check for enpassat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==BLACK)){//Checking if there is any 
                           if(board[curx][j]->HasMoved()){//black pawn and has done 2 squares move
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;
                  }
               }
            }
            else{    //For black pawns
               if(j==cury){
                  if(i==4 && curx==6){     //Checking if the move is 2 squares forward
                     if(board[5][cury]==0 && board[4][cury]==0)  //Checking if there is something in front of it  
                        return true;
                     else
                        return false;
                     }
                  if(i==curx-1){    //Checking if the move is 1 square forward
                     if(board[i][cury]==0)  //Check if there is anything in front of it  
                        return true;
                     else
                        return false;           
                  }
                }
               if(j==cury-1){             //Here is trying to capture one piece left
                  if(board[curx-1][j]!=0){ 
                     if(board[curx-1][j]->GetColor()==WHITE)          
                        return true;
                     else
                        return false;
                     }
                  else{ //If there is NOT any object then check for enpassat   
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==WHITE)){//Checking if there is any 
                           if(board[curx][j]->HasMoved()){//white pawn and has done 2 squares move
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;
                  }    
                }
               if(j==cury+1){             //Here is trying to capture one piece right
                  if(board[curx-1][j]!=0){ 
                     if(board[curx-1][j]->GetColor()==WHITE)          
                        return true;
                     else
                        return false;
                     } 
                  else{ //If there is NOT any object left then check for enpassat  
                     if(board[curx][j]!=0){
                        if((board[curx][j]->GetType()=='P') && (board[curx][j]->GetColor()==WHITE)){//Checking if there is any 
                           if(board[curx][j]->HasMoved()){//white pawn and has done 2 squares move
                              return true;
                           }else return false;  
                        }else return false;                      
                     }else return false;
                  }
               }
            }
}
//-----END PRIVATE FUNCTIONS OF Checkboard-----//

//Constructor
Chessboard::Chessboard(){
            play=WHITE;
            curx=-1;
            cury=-1;
            for(int i=0;i<8;i++)
               for(int j=0;j<8;j++)
                   board[i][j]=0;                  
}

//Put a piece on chessboard
void Chessboard::SetPiece(Piece * p,int i,int j){
            board[i][j]=p;           //Update table with piece           
            board[i][j]->SetPos(i,j); //Update the position of the specified object
}

//Print chessboard on cmd
void Chessboard::PrintChessBoard(){
            HANDLE hConsole;
            hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
            for(int i=7;i>=0;i--){
               SetConsoleTextAttribute(hConsole,0x0002 | 0x0008);
               cout<<i;
               for(int j=0;j<8;j++){
                   if((i+j)%2==0)                //Check the color that the square has
                     SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                   else
                     SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                   cout<<" ";
                   if(board[i][j]!=0){  //Check the color of the piece 
                      if(board[i][j]->GetColor()){     //Color is White
                         if((i+j)%2==0)                //Check the color that the square has
                           SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                         else
                           SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);   
                         cout<<board[i][j]->GetType();
                      }else{                            //Color is Black
                         SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                         if((i+j)%2==0)                //Check the color that the square has
                           SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                         else
                           SetConsoleTextAttribute(hConsole,BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                         cout<<board[i][j]->GetType();
                      }
                      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |  FOREGROUND_INTENSITY);
                   }else
                      {cout<<" ";}
                   if(j==7){ 
                     if((i+j)%2==0)                //Check the color that the square has
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

//Clear all objects from chessboard
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

//Here we choose the piece that is going to play
bool Chessboard::ChoosePiece(int i,int j){
            if(board[i][j]!=0){
               if(board[i][j]->GetColor()==play){//If the selected object has the color of the player, then keep x,y
                  curx=i;
                  cury=j;
                  return true;
               }
            }
            return false;
}

//PrintChessBoard calls this function and prints what object is selected and where it is 
void Chessboard::ChosenPiece(){ 
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

//Function that checks if a square is threaten or not. Scan all chessboard and checks if any piece threats the selected square
bool Chessboard::IsThreated(int x,int y){//x,y posible position
            int i,j,tempx,tempy;
            bool tem;
            char ch;
            for(i=0;i<8;i++){
               for(j=0;j<8;j++){//Scan all the chessboard
                  if(board[i][j]!=0){ //Find piece
                    if(board[i][j]->GetColor()!=play){ //If color of found piece is not the same with the player who plays
                      ch=board[i][j]->GetType(); //Read the type of object
                      if((ch=='K') || (ch=='H')){ //if King or Horse found
                         tem=board[i][j]->CheckMove(x,y); //Check if can go to the selected position
                      }   
                      if(ch=='P'){//Here Pawns are checked
                           if(((y==board[i][j]->Gety()) && (x==board[i][j]->Getx()+1))  
                             ||  ((y==board[i][j]->Gety()) && (x==board[i][j]->Getx()-1)))
                             {tem=false;}//δεν απειλεί
                           else tem=board[i][j]->CheckMove(x,y);
                      }
                      if(tem==true) return true;//Treaten
                    }
                  }                 
               }                 
            }
            //Here queen tower are checked
            i=x+1;
            j=y;
            while(i<8){//check column up
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else i=15;//END WHILE
               }
               i++;    
            }
            
            i=x-1;
            j=y;
            while(i>-1){//check column down
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else i=-15;//END WHILE
               }
               i--;
            }    
            
            i=x;
            j=y+1;
            while(j<8){//check row right
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else j=15;//END WHILE
               }
               j++;
            }

            i=x;
            j=y-1;
            while(j>-1){//check row left
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='T') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else j=-15;//END WHILE
               }
               j--;
            }
            
            //Here Bishop is checked
            i=x+1;
            j=y-1;
            while((i<8) && (j>-1)){//Check left diagonal up
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=15;j=-15;}//END WHILE
               }
               i++;
               j--;
            }
            
            i=x-1;
            j=y+1;
            while((i>-1) && (j<8)){//Check left diagonal down
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=-15;j=15;}//END WHILE
               }
               i--;
               j++;
            }
            
            i=x+1;
            j=y+1;
            while((i<8) && (j<8)){//Check right diagonal up
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=15;j=15;}//END WHILE
               }
               i++;
               j++;
            }
            
            i=x-1;
            j=y-1;
            while((i>-1) && (j>-1)){//Check right diagonal down
               if(board[i][j]!=0){
                  if((board[i][j]->GetColor()!=play) && ((board[i][j]->GetType()=='B') || (board[i][j]->GetType()=='Q'))){
                    return true;
                  }
                  else {i=-15;j=-15;}//END WHILE
               }
               i--;
               j--;
            }
            
            return false;//Here square is not threaten
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

              
//This function does the moves of pieces in chessboard. If a white king captured returns 1, for black king 2, anything else 0
int Chessboard::Move(int i,int j){
            HANDLE hConsole;
            hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
            
            if(board[i][j]!=0){//If there is a piece in the new position
               if(board[i][j]->GetType()=='K'){   //If a King is captures the game is over
                 if(board[i][j]->GetColor()==WHITE){ 
                   SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                   return 1;
                 }else
                   return 2;  
               }
               board[i][j]->~Piece();//The existing piece is deleted from new position
            }
            if(board[curx][cury]->GetType()=='P'){//Check moves of pawns
               if(((i==curx+2) && (curx==1)) || ((i==curx-2) && (curx==6))){
                  board[curx][cury]->ChangeMove();//enpassat takes place
               }else
               /*if((i==curx+1) || (i==curx-1))*/{
                  if(board[curx][cury]->HasMoved())//If pawn makes a move, we check if the pawn has done 2 square move before
                     board[curx][cury]->ChangeMove();//then the pawn(object) is informed that cant be captured with enpassant      
               }
               if(j==cury-1){//If pawn goes left
                  if(board[i][j]==0){//If there is nothing in the new position then left enpassant                                   
                     board[curx][j]->~Piece();
                     board[curx][j]=0;
                  }
               }
               if(j==cury+1){//If paen goes right
                  if(board[i][j]==0)//If there is nothing in the new position then right enpassant                                   
                     board[curx][j]->~Piece();
                     board[curx][j]=0;
               }
               if(i==7){
                   int ch;             //Checking promotion of pawns(here white)                                   
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
                   cin.ignore();
              }else{if(i==0){     //Checking promotion of pawns(here black)
                      int ch;                                    
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
                    cin.ignore();//Removing \n from cin
                    }//end if(i==0)
              }                                   
            }
            if((board[curx][cury]->GetType()=='T') || (board[curx][cury]->GetType()=='K')){ //right roque 
              if((board[curx][cury]->GetType()=='K') && (i==board[curx][cury]->Getx() && j==board[curx][cury]->Gety()+2)){
                 if(play){
                   board[0][7]->ChangeMove();//Tower moved
                   board[0][7]->SetPos(0,5);
                   board[0][5]=board[0][7];
                   board[0][7]=0;
                 }else{
                   board[7][7]->ChangeMove();//Tower moved
                   board[7][7]->SetPos(7,5);
                   board[7][5]=board[7][7];
                   board[7][7]=0;    
                 } //αριστερό roque
              }else{if((board[curx][cury]->GetType()=='K') && (i==board[curx][cury]->Getx() && j==board[curx][cury]->Gety()-2))
                 if(play){
                   board[0][0]->ChangeMove();//Tower moved
                   board[0][0]->SetPos(0,3);
                   board[0][3]=board[0][0];
                   board[0][0]=0;
                 }else{
                   board[7][0]->ChangeMove();//Tower moved
                   board[7][0]->SetPos(7,3);
                   board[7][3]=board[7][0];
                   board[7][0]=0;    
                 } 
              }
              board[curx][cury]->ChangeMove();//King moved
            }
            board[curx][cury]->SetPos(i,j);//Selected piece informed with his new position
            board[i][j]=board[curx][cury]; //Piece moved to new position in chessboard
            board[curx][cury]=0;           //Old position sets empty
            curx=i;
            cury=j;
            play=!play;//Change current player
            return 0;
}
//-----------------------End Chessboard-----------------------//
