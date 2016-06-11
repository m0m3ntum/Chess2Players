#include <iostream>
#define BLACK false
#define WHITE true

using namespace std;

//An abstract class where all the pieces inherit
class Piece{
      protected:
                bool color;   //Color of the piece 1.false=black 2.true=white   
                int x,y;      //Current position of piece 
      public:
                virtual bool CheckMove(int,int)=0; //Virtual function that checks a requested move
                virtual char GetType()=0;         //Virtual function that returns the type of piece. ex Q=Queen
                inline virtual bool HasMoved(){}  //Returns if the piece has done a move
                inline virtual void ChangeMove()=0;//The piece has done at least one move. (ex.hasmoved in King becomes true)
                inline void SetPos(int i,int j){x=i;y=j;}//Change the position of piece
                inline bool GetColor(){return color;} //Return The color of the piece
                inline int Getx(){return x;} //Return x value
                inline int Gety(){return y;} //Return y value
};

class King : public Piece{
      private:
              bool hasmoved; //False if has done at least 1 move 
      public:
            inline King(bool clr){hasmoved=false;color=clr;} //Constructors
            inline King(const King& temp){hasmoved=temp.hasmoved;color=temp.color;x=temp.x;y=temp.y;hasmoved=temp.hasmoved;}
            inline ~King(){} //Destructors
            inline char GetType(){return 'K';}
            bool CheckMove(int,int);
            inline bool HasMoved(){return hasmoved;}
            inline virtual void ChangeMove(){hasmoved=true;}
};

class Queen : public Piece{
      private:
      
      public:
           inline Queen(bool clr){color=clr;}//Constructors
           inline Queen(const Queen& temp){color=temp.color;x=temp.x;y=temp.y;}
           inline ~Queen(){}//Destructors
           inline char GetType(){return 'Q';}
           bool CheckMove(int,int);
           inline void ChangeMove(){};
};

class Tower : public Piece{
      private:
           bool hasmoved;//False if has done at least 1 move
      public:
           inline Tower(bool clr){hasmoved=false;color=clr;} //Constructors
           inline Tower(const Tower& temp){hasmoved=temp.hasmoved;color=temp.color;x=temp.x;y=temp.y;}
           inline ~Tower(){} //Destructor
           inline char GetType(){return 'T';}
           bool CheckMove(int,int);
           inline bool HasMoved(){return hasmoved;}
           inline void ChangeMove(){hasmoved=true;}
};

class Horse : public Piece{
      private:

      public:
           inline Horse(bool clr){color=clr;}//Constructors
           inline Horse(const Horse& temp){color=temp.color;x=temp.x;y=temp.y;}
           inline ~Horse(){}//Destructor
           inline char GetType(){return 'H';}
           bool CheckMove(int,int);
           inline void ChangeMove(){};
};

class Bishop : public Piece{
      private:
      
      public:
           inline Bishop(bool clr){color=clr;} //Constructors
           inline Bishop(const Bishop& temp){color=temp.color;x=temp.x;y=temp.y;}
           inline ~Bishop(){}//Destructor
           inline char GetType(){return 'B';}
           bool CheckMove(int,int);
           inline virtual void ChangeMove(){};
};

class Pawn : public Piece{
      private:
            bool enpassant;//its true if pawn has done enpassant. Enpassant:When a pawn moves two ranks forward from its starting position               
      public:
           inline Pawn(bool clr){color=clr;enpassant=false;}//Constructors
           inline Pawn(const Pawn& temp){color=temp.color;x=temp.x;y=temp.y;enpassant=temp.enpassant;}
           inline ~Pawn(){}//Destructor
           inline char GetType(){return 'P';}
           bool CheckMove(int,int);
           inline void ChangeMove(){if(enpassant) enpassant=false; else enpassant=true;}
           inline bool HasMoved(){return enpassant;}
};

//The class of the chessboard
class Chessboard{
      private:
              Piece * board[8][8]; //Table8x8 filled with Piece type objects
              bool play;         //Shows who is currently playing
              int curx,cury;       //x,y of selected piece
              bool CheckKing(int,int);
              bool CheckQueen(int,int);
              bool CheckTower(int,int);
              bool CheckBishop(int,int);
              bool CheckPawn(int,int);
      public:
              Chessboard();
              inline ~Chessboard(){delete[] board;}
              void SetPiece(Piece *,int,int);
              bool ChoosePiece(int,int); 
              bool CheckMove(int,int);
              bool IsThreated(int,int);   //Returns if the new selected position is threaten
              void ChosenPiece();
              int Move(int,int);
              void PrintChessBoard();
              void Clear(); 
};
