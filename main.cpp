#include "Chess.h"

int main(int argc, char *argv[])
{
    //White pieces
    King whitek(WHITE);
    Queen whiteq(WHITE);
    Horse whitehr(WHITE),whitehl(WHITE);//white horse right   white horse left
    Bishop whitebr(WHITE),whitebl(WHITE);
    Tower whitetr(WHITE),whitetl(WHITE);
    Pawn wp1(WHITE),wp2(WHITE),wp3(WHITE),wp4(WHITE),wp5(WHITE),wp6(WHITE),wp7(WHITE),wp8(WHITE);
    //Black pieces
    King blackk(BLACK);
    Queen blackq(BLACK);
    Horse blackhr(BLACK),blackhl(BLACK);//black horse right   balck horse left
    Bishop blackbr(BLACK),blackbl(BLACK);
    Tower blacktr(BLACK),blacktl(BLACK);
    Pawn bp1(BLACK),bp2(BLACK),bp3(BLACK),bp4(BLACK),bp5(BLACK),bp6(BLACK),bp7(BLACK),bp8(BLACK);
    Chessboard cb;
    //Arxikopoiisi
    cb.SetPiece(&wp1,1,0);
    cb.SetPiece(&wp2,1,1);
    cb.SetPiece(&wp3,1,2);
    cb.SetPiece(&wp4,1,3);
    cb.SetPiece(&wp5,1,4);
    cb.SetPiece(&wp6,1,5);
    cb.SetPiece(&wp7,1,6);
    cb.SetPiece(&wp8,1,7);
    cb.SetPiece(&whitetl,0,0);
    cb.SetPiece(&whitehl,0,1);
    cb.SetPiece(&whitebl,0,2);
    cb.SetPiece(&whitek,0,4);
    cb.SetPiece(&whiteq,0,3);
    cb.SetPiece(&whitebr,0,5);
    cb.SetPiece(&whitehr,0,6);
    cb.SetPiece(&whitetr,0,7);
    cb.SetPiece(&bp1,6,0);
    cb.SetPiece(&bp2,6,1);
    cb.SetPiece(&bp3,6,2);
    cb.SetPiece(&bp4,6,3);
    cb.SetPiece(&bp5,6,4);
    cb.SetPiece(&bp6,6,5);
    cb.SetPiece(&bp7,6,6);
    cb.SetPiece(&bp8,6,7);
    cb.SetPiece(&blacktl,7,0);
    cb.SetPiece(&blackhl,7,1);
    cb.SetPiece(&blackbl,7,2);
    cb.SetPiece(&blackk,7,4);
    cb.SetPiece(&blackq,7,3);
    cb.SetPiece(&blackbr,7,5);
    cb.SetPiece(&blackhr,7,6);
    cb.SetPiece(&blacktr,7,7);
    //Telos arxikopoiisis
    
    /*cb.SetPiece(&bp5,3,3);        //Παράδειγμα λειτουργίας enpassant
    cb.SetPiece(&wp5,1,2);
    cb.SetPiece(&wp5,1,4);*/
    //cb.SetPiece(&whitetr,7,7);   //Παράδειγμα λειτουργίας promotion...(Αλλαγή πιονιού σε ότι θέλει) 
    //cb.SetPiece(&bp5,1,4);
    /*cb.SetPiece(&whitek,0,4);
    cb.SetPiece(&whitetr,0,7);
    cb.SetPiece(&blackq,4,6);
    cb.SetPiece(&whiteq,0,3);
    cb.SetPiece(&blackbr,3,0);
    cb.SetPiece(&blackhl,2,7);
    cb.SetPiece(&wp7,1,6);*/

    int cho,cho2,result;
    char chos[5];
    do{ 
    //Επιλογή κομματιού
     do{         
       do{
          system("cls");
          cb.PrintChessBoard();   
          cout<<"Choose a piece(x,y)\nx=";
          cin.getline(chos,5);
          cho=atoi(chos);
          cout<<"\ny=";
          cin.getline(chos,5);
          cho2=atoi(chos);
       }while((cho<0 || cho>7) && (cho2<0 || cho2>7));
     }while(cb.ChoosePiece(cho,cho2)==false);
    //Επιλογή νέας θέσης 
     do{
       do{
          system("cls");
          cb.PrintChessBoard();   
          cb.ChosenPiece();
          cout<<"Choose new position(x,y)\nx=";
          cin.getline(chos,5);
          cho=atoi(chos);
          cout<<"\ny=";
          cin.getline(chos,5);
          cho2=atoi(chos);
       }while((cho<0 || cho>7) && (cho2<0 || cho2>7));
     }while(cb.CheckMove(cho,cho2)==false);
     //Κίνηση κομματιού
     result=cb.Move(cho,cho2); 
     system("cls");
     cb.PrintChessBoard();
   }while(result==0);
//Το παιχνίδι τελειώνει με νικητή τον... 
   system("cls");              
   if(result==1)              
     cout<<"Black player WINS!!!!!!";            
   else
     cout<<"White player WINS!!!!!!";            
      cout<<"\n\nTHE END...\n";
   cout<<"Fotis Galanis 060092\n\n"; 
   system("PAUSE");
   return EXIT_SUCCESS;
}
