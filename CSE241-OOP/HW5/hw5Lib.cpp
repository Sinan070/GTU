#include "Klotski.h" 
#include "PegSolitaire.h"
#include "Puzzle.h"
#include <algorithm> /* using for shuffle method*/


using namespace std;

/* BoardGame2D base class non- virtual functions implementation*/


/* BoardGame2D default constructor*/
BoardGame2D::BoardGame2D() : _move(""), _row(0), _column(0), _score(0){}

/* Play automatically only once*/
void BoardGame2D::playAuto(){
   while (1)
   {
      this->_move = getRandomMove();
      parseMove();
      
      if(canMove()){
         makeMove();
         //cout<<(*this)<<endl;
         break;
      }
   }
}

/* Play automatically until the game is finished*/
void BoardGame2D::playAutoAll(){
   
   while (!endGame()) {   playAuto() ;/*std::this_thread::sleep_for (std::chrono::milliseconds(20))*/;}

}


/* Play by user only once turn*/
void  BoardGame2D::playUser(const string& move){
    
    
    bool status = false;    
    //cout << (*this);
    
    _move = move;
    
    parseMove();
    if(canMove())   makeMove();
    
    else{
       std::cout<<"Could not make a move\n";
    }
}

/* Play by user until the game is finished*/
void BoardGame2D::playUser(){
   do{
      bool status = false;    
      cout << (*this);
      
      do{

        try{

            cout <<"Please Enter the Move : ";
            getline(std::cin,this->_move);
            isMoveValid();
            status = true;

        }
        catch(const char* e )
        {   
            cerr <<e;
        }
    
      }while (!status);
      
      
      parseMove();
      
      if(canMove())   makeMove();
      else{
         std::cout<<"Could not make a move\n";
      }
   }while (!endGame());
}


/* Get Board games and play them automatically until the games is finished*/
void BoardGame2D::playVector(vector<BoardGame2D*> games){
    for(auto game : games)  { 
        cout <<*game<<endl<<endl; game->playAutoAll(); cout <<endl<<*game<<endl<<endl;; /*std::this_thread::sleep_for (std::chrono::seconds(10))*/;
        
        }
}

/* Stream instertion operator to print game's board*/
ostream& operator<<(ostream & out,const  BoardGame2D & base){
    /*out << "\x1b[2J"; 
        out << "\033[0;0H"; // move cursor to 0,0*/
        out << endl << endl;
    base.print(out);
    return out;
}



/* BoardGame2D base class virtual functions implementation with respecto game types*/

/* Solitaire Game*/

/*Peg Solitaire Default Constructor*/
PegSolitaire::PegSolitaire() : BoardGame2D(), _rowChoice(0), _collumnChoice(0), _directionChoice('\0'){
    initialize();
}






/* Print Peg Solitaire Game Board*/
void PegSolitaire::print(ostream & out) const{
    cout<<"\n";
    cout <<"      ****** BOARD *******\n";
    int i,j;
    char letter= 'a';
    int num=1;
    out<<"      ";
    for(i=0;i<_row;++i){
        out<<letter<<"  ";
        ++letter;
    }

    out<<endl<<endl;
    
    for(auto object : (*pegBoard)){
            out<<num<<"    ";
            ++num;
        for(auto element : object){
            if(element == cellType::empty) out<<" . ";    
            
            else if(element == cellType::peg)   out<<" P ";
            
            else if(element == cellType::space)     out<<"   ";
            
        }
        out<<"\n\n";
    }
    out <<"Score : " << boardScore();
    out<<"\n\n";
}


/* Getting Game Score*/

int PegSolitaire::boardScore() const{
    return _score;
}

/* Initialize Peg Solitaire Game Board*/
void PegSolitaire::initialize(){
      this->pegBoard = new vector<vector<cellType>>({

            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},                        
            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},
            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},

            {cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg},
            {cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::empty,cellType::peg,cellType::peg,cellType::peg,cellType::peg},
            {cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg,cellType::peg},
            
            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},
            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},
            {cellType::space,cellType::space,cellType::space,cellType::peg,cellType::peg,cellType::peg,cellType::space,cellType::space,cellType::space},
   });
   _row =9;
   _column =9;
   _score = 44; /* Inıtial Score is initial number of Pegs of Board*/
}


/* Get random value to play automatically*/
string PegSolitaire::getRandomMove(){
    string tempMove;
    vector<char> direction = {'u' , 'd', 'r', 'l'};
    char directionType = direction[rand () % 4];
    char randRow= rand () % this->_row+1 + 48;
    char randCol = rand () % (this->_column+1) +97;
    ostringstream os;
    os << randRow<< randCol<<" "<<directionType;

    return os.str();
}

/* Check if the Move syntax is valid or not*/
bool PegSolitaire::isMoveValid() const{
    bool status = true;
    

    if(_move.size()>4) status =false;
    else if(_move[0] <'1' || _move[0]> '9') status = false;
    else if(_move[1]<'a' || _move[1]>'i') status =false;
    else if(_move[2]!= ' ') status = false;
    else if(!(_move[3] == 'd' || _move[3] == 'l' || _move[3] == 'r' || _move[3] == 'u')) status = false;
    
    if(status == false) throw "Invalid Move Syntax\n";

    return status;
}

/* Chech if the move is proper or not*/
bool PegSolitaire::canMove(){
   int flag=0;
   int i,j;
   bool status = false;
    j = _collumnChoice;
    i = _rowChoice;
   

    if(_directionChoice =='r'){
        
        if( j > _column-3)  flag=1;
        
        if(flag==0 && (*pegBoard)[i][j]== cellType::peg && 
            (*pegBoard)[i][j +1]== cellType::peg && 
            (*pegBoard)[i][j +2] == cellType::empty){
            status = true;
        }
    }   

    else if(_directionChoice  =='l'){
        if(j < 2)   flag=1;
        
    
        if(flag==0 && (*pegBoard)[i][j] == cellType::peg && 
        (*pegBoard)[i][j -1] == cellType::peg && 
        (*pegBoard)[i][j -2] == cellType::empty){
            status = true;

        }
    } 
    else if(_directionChoice == 'u'){
        if(i <2)    flag=1;
    
        if(flag==0 && (*pegBoard)[i][j] == cellType::peg 
        && (*pegBoard)[i-1][j] == cellType::peg 
        && (*pegBoard)[i -2][j] == cellType::empty){
            status = true;

        }
    }
    else if(_directionChoice == 'd'){
        if(i > _row -3)     flag=1;
        
        if(flag==0 && (*pegBoard)[i][j] == cellType::peg 
        && (*pegBoard)[i +1][j] == cellType::peg 
        && (*pegBoard)[i +2][j] == cellType::empty){
            status = true;

        }
    }
    
    return status;
}

/* Make Move*/
void PegSolitaire::makeMove(){
   
        int i,j;
        
        j = _collumnChoice ;
        i = _rowChoice ;

        switch (_directionChoice)
        {
        case 'r' :

            (*pegBoard)[i][j] = (cellType::empty); 
            (*pegBoard)[i][j+2] = (cellType::peg);
            (*pegBoard)[i][j+1] = (cellType::empty); 


            break;
        case 'l' :
            (*pegBoard)[i][j] = (cellType::empty);
            (*pegBoard)[i][j-2] = (cellType::peg);
            (*pegBoard)[i][j-1] = (cellType::empty);
            break;
        case 'u':
            (*pegBoard)[i][j] = (cellType::empty);
            (*pegBoard)[i-2][j] = (cellType::peg);
            (*pegBoard)[i-1][j] = (cellType::empty); 
            break;
        case 'd':
            (*pegBoard)[i][j] = (cellType::empty);
            (*pegBoard)[i+2][j] = (cellType::peg);
            (*pegBoard)[i+1][j] = (cellType::empty); 
            break;

        default:
            break;
        }
        --_score;
}

/* Parse Move*/
void PegSolitaire::parseMove(){

    this->_rowChoice = (int)(_move[0] - 49);
    this->_collumnChoice = (int)(_move[1] - 97);
    this->_directionChoice = _move[3];
    
}

/* Check if the game is finished or not*/

bool PegSolitaire::endGame() const {
    int peg_num=0;
    int flag=0;
    for(int i=0;i<_row;++i){
        for(int j=0;j<_column;++j){
            
            if((*pegBoard)[i][j]== cellType::peg){
                ++peg_num;
                
                if(j-2>=0 && (*pegBoard)[i][j-2]== cellType::empty && (*pegBoard)[i][j-1]== cellType::peg){
                    
                    flag=1;
                }
                if(j+2 < _column && (*pegBoard)[i][j+2]== cellType::empty && (*pegBoard)[i][j+1]== cellType::peg){
                   
                    flag=1;
                }
                if(i-2>=0 && (*pegBoard)[i-2][j] == cellType::empty && (*pegBoard)[i-1][j] == cellType::peg){
                   
                   flag=1;
                }
                if(i+2<(*pegBoard).size() && (*pegBoard)[i+2][j] == cellType::empty && (*pegBoard)[i+1][j] == cellType::peg){
                    
                    flag=1;
                }
                if(flag==1){
                    
                    return 0;
                }

            }
            
        }
    
    }
    /* if ther is a only one pegs, the game is finished by best score*/
    if(peg_num == 1){
        cout<< "The game is over succesffuly. Well Done\n\n";
        return 1;
    }
    return 1;
}

/* Destructor for Peg Solitiare Game*/
PegSolitaire::~PegSolitaire(){
    delete this->pegBoard;
}










/* Klotski*/

/* Klotski default Constructor*/
Klotski::Klotski() : BoardGame2D(), _direction('\0'), _blockNum(0) { 

initialize();


}

/* Initialize Klotski Board*/
void Klotski::initialize(){

    this->klotskiBoard = new vector<vector<char>>({

        {'1', '2', '2','3'},
        {'1', '2', '2','3'},
        {'4', '5', '5','6'},
        {'4', '7', '8','6'},
        {'9', 'e', 'e','0'}

    });
    _row =5;
    _column =4;
    _score =0; /* Set score zero initially, Low score is much better*/
}

/* Get Klotski Random Move to play Automatically*/
string Klotski::getRandomMove(){
    
    int randBlock = rand() % 10 +0;
    vector<char> direction = {'r' , 'l', 'd', 'u'};
    char directionType = direction[rand () % 4];

    ostringstream os;
    os<<randBlock<<" "<<directionType;
    
    return os.str();
}

/* Print Klotski Game*/

void Klotski::print(ostream& out) const{

int i,j;
        
out <<"\tKLOTSKI BOARD\n";
for(int i =0 ; i<_row; ++i){
         
         for(int j=0 ; j<_column ; ++j){

            out<<" "<<(*klotskiBoard)[i][j];
         }
         out<<endl;
     }
     out <<"Score :" <<boardScore();
out <<endl<<endl;

}

/* Parse Klotski Move into direction and block number*/
void Klotski::parseMove(){
    this->_blockNum = _move[0]-48;
    this-> _direction = _move[2];

}


/* Find Block Number Location*/
void Klotski::findPos(int &row, int &col){

     for(int i =0 ; i<_row; i++){
         for(int j=0 ; j<_column ; j++){
             if((_blockNum +48 )== (*klotskiBoard)[i][j]){
                 row = i;
                 col =j;
                 
                  i= _row;
                  j=_column;
             }
         }
     }
       
 }

/* Check if the Klotski Move is Valid or not*/
bool Klotski::isMoveValid() const{
    bool status = true;
    if(_move.size()!=3) status = false;
    else if(_move[0] < '0' || _move[0] > '9') status = false;
    else if(_move[1] != ' ') status = false;
    else if(!(_move[2] == 'u' || _move[2] == 'd' ||  _move[2] == 'l' ||  _move[2] == 'r')) status = false;
    if(status == false) throw "Invalid Move Syntax\n";
    return status;
}

/* make Klotski game move*/
void Klotski::makeMove(){
    
    int i,j;

    findPos(i,j); 
    switch (_direction)
    {
    case 'u':
        if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6 )){
            (*klotskiBoard)[i-1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i][j] = (*klotskiBoard)[i+1][j];
            (*klotskiBoard)[i+1][j] = 'e';

        }   
        else if(_blockNum == 5){
            (*klotskiBoard)[i-1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i-1][j+1] = (*klotskiBoard)[i][j+1];
            (*klotskiBoard)[i][j] = 'e';
            (*klotskiBoard)[i][j+1] = 'e';
        } 
        else if(_blockNum ==2){
            (*klotskiBoard)[i-1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i-1][j+1] = (*klotskiBoard)[i][j+1];
            (*klotskiBoard)[i][j] = (*klotskiBoard)[i+1][j];
            (*klotskiBoard)[i][j+1] = (*klotskiBoard)[i+1][j+1];
            (*klotskiBoard)[i+1][j] = 'e';
            (*klotskiBoard)[i+1][j+1] = 'e';

            
        }
        else if(_blockNum ==8 || _blockNum == 9 || _blockNum == 7 || _blockNum == 0){
            (*klotskiBoard)[i-1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i][j] = 'e';

        }
        break;
    case 'd':
        if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6 )){
            (*klotskiBoard)[i+2][j] = (*klotskiBoard)[i+1][j];
            (*klotskiBoard)[i+1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i][j] = 'e';

        }   
        else if(_blockNum == 5){
            (*klotskiBoard)[i+1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i+1][j+1] = (*klotskiBoard)[i][j+1];
            (*klotskiBoard)[i][j] = 'e';
            (*klotskiBoard)[i][j+1] = 'e';
        } 
        else if(_blockNum ==2){
            (*klotskiBoard)[i+2][j] = (*klotskiBoard)[i+1][j];
            (*klotskiBoard)[i+2][j+1] = (*klotskiBoard)[i+1][j+1];
            (*klotskiBoard)[i+1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i+1][j+1] = (*klotskiBoard)[i][j+1];
            (*klotskiBoard)[i][j] = 'e';
            (*klotskiBoard)[i][j+1] = 'e';

        }
        else if(_blockNum ==8 || _blockNum == 9 || _blockNum == 7 || _blockNum == 0){
            (*klotskiBoard)[i+1][j] = (*klotskiBoard)[i][j];
            (*klotskiBoard)[i][j] = 'e';

        }
        
        break;
        case 'r':
            if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6 )){
                (*klotskiBoard)[i][j+1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i+1][j+1] = (*klotskiBoard)[i+1][j];
                (*klotskiBoard)[i][j] = 'e';
                (*klotskiBoard)[i+1][j] = 'e';

            }   
            else if(_blockNum == 5){
                (*klotskiBoard)[i][j+2] = (*klotskiBoard)[i][j+1];
                (*klotskiBoard)[i][j+1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i][j] = 'e';
            } 
            else if(_blockNum ==2){
                (*klotskiBoard)[i][j+2] = (*klotskiBoard)[i][j+1];
                (*klotskiBoard)[i][j+1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i+1][j+2] = (*klotskiBoard)[i+1][j+1];
                (*klotskiBoard)[i+1][j+1] = (*klotskiBoard)[i+1][j+1];
                (*klotskiBoard)[i][j] = 'e';
                (*klotskiBoard)[i+1][j] = 'e';

            }
            else if(_blockNum ==8 || _blockNum == 9 || _blockNum == 7 || _blockNum == 0){
                (*klotskiBoard)[i][j+1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i][j] = 'e';

            }
            break;
        case 'l':
            if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6 )){
                (*klotskiBoard)[i][j-1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i+1][j-1] = (*klotskiBoard)[i+1][j];
                (*klotskiBoard)[i][j] = 'e';
                (*klotskiBoard)[i+1][j] = 'e';

            }   
            else if(_blockNum == 5){
                (*klotskiBoard)[i][j-1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i][j] = (*klotskiBoard)[i][j-1];
                (*klotskiBoard)[i][j+1] = 'e';
            } 
            else if(_blockNum ==2){
                (*klotskiBoard)[i][j-1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i][j] = (*klotskiBoard)[i][j-1];
                (*klotskiBoard)[i+1][j-1] = (*klotskiBoard)[i+1][j];
                (*klotskiBoard)[i+1][j] = (*klotskiBoard)[i+1][j-1];
                (*klotskiBoard)[i][j+1] = 'e';
                (*klotskiBoard)[i+1][j+1] = 'e';

            }
            else if(_blockNum ==8 || _blockNum == 9 || _blockNum == 0 || _blockNum == 7){
                (*klotskiBoard)[i][j-1] = (*klotskiBoard)[i][j];
                (*klotskiBoard)[i][j] = 'e';

            }
            break;
        
    default:
        break;
    }
    ++_score; 
}

/* Check if the move is proper or not*/
bool Klotski::canMove(){
    
    int i,j;
    findPos(i,j); 
    bool status = false;
    switch (_direction)
    {
    case 'u':
        if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6 || _blockNum==8 || _blockNum ==9 || _blockNum == 7 || _blockNum == 0) 
            && i>0 
            && (*klotskiBoard)[i-1][j] =='e') status = true;
        else if((_blockNum == 5 || _blockNum ==2) 
            && i>0 
            && (*klotskiBoard)[i-1][j] =='e' && (*klotskiBoard)[i-1][j+1] =='e' ) status = true;
        break;

    case 'd':
        if((_blockNum == 1 || _blockNum == 3 || _blockNum == 4 || _blockNum == 6) 
            && (i+1)<_row-1
            && (*klotskiBoard)[i+2][j] =='e') status = true;
        else if((_blockNum==8 || _blockNum ==9 || _blockNum == 7 || _blockNum == 0) 
            && i<_row-1
            && (*klotskiBoard)[i+1][j] =='e') status = true;

        else if((_blockNum == 5) 
            && i<_row -1
            && (*klotskiBoard)[i+1][j] =='e' && (*klotskiBoard)[i+1][j+1] =='e' ) status = true;
        else if((_blockNum ==2)
            && (i+1)<_row -1
            && (*klotskiBoard)[i+2][j] =='e' && (*klotskiBoard)[i+2][j+1] =='e' ) status = true;
        break;

        case 'r':
            if((_blockNum == 1  ||  _blockNum == 3 || _blockNum == 4 || _blockNum == 6) 
            && j < _column-1 
            && (*klotskiBoard)[i][j+1] =='e'
            && (*klotskiBoard)[i+1][j+1] =='e') status = true;
        else if((_blockNum == 2) 
            && (j+1) < _column-1 
            && (*klotskiBoard)[i][j+2] =='e'
            && (*klotskiBoard)[i+1][j+2] =='e') status = true;
        
        else if(( _blockNum==8 || _blockNum ==9 || _blockNum == 7 || _blockNum == 0) 
            && j < _column-1 
            && (*klotskiBoard)[i][j+1] =='e' ) status = true;
        else if((_blockNum == 5)
            && (j+1) < _column-1 
            && (*klotskiBoard)[i][j+2] =='e' ) status = true;
        break;
        case 'l':
           if((_blockNum == 1 || _blockNum == 2 ||  _blockNum == 3 || _blockNum == 4 || _blockNum == 6 ) 
            && j >0 
            && (*klotskiBoard)[i][j-1] =='e'
            && (*klotskiBoard)[i+1][j-1] =='e') status = true;

        else if((_blockNum == 5 || _blockNum == 7  || _blockNum==8 || _blockNum ==9  || _blockNum == 0) 
            && j > 0 
            && (*klotskiBoard)[i][j-1] =='e' ) status = true;
            break;
        
    default:
        break;
        return status;
    }

}

/* CHECK IF THE GAME IS FINISHED OR NOT*/
bool Klotski::endGame() const{
    if((*klotskiBoard)[3][1] == '2' && (*klotskiBoard)[3][2] == '2' && (*klotskiBoard)[4][1] == '2' && (*klotskiBoard)[4][2] == '2'){
        return true;
    }
    else return false;
}

/* Get Klotski Game Score, Score is increase by one in every move, Low Score is much better*/
int Klotski::boardScore() const{
    return _score;
}

/* Destructor for Klotski Game*/
Klotski::~Klotski(){
    delete this->klotskiBoard;
}





/* EightPuzzle Game*/


/* Eight Puzzle Default Constructor*/
EightPuzzle::EightPuzzle() : BoardGame2D(), _direction('\0') , _numberChoice(0){
    _row=3;
    _column=3;
    initialize(); 
}

/* If the Board is solvable then initialize the board*/ 
void EightPuzzle::initialize(){
     this->eightPuzzleBoard = new vector<vector<int>>(3, vector<int>(3));
    do
    {
        
        randomShuffle(elements);
        int counter =0;
        for(int i=0 ; i< _row ; ++i){
            for(int j =0 ; j<_column ; ++j, ++ counter){
                (*eightPuzzleBoard)[i][j] = elements[counter];  
            }
        }
    
    }while (!is_solvable());
    _score =0;
}



/* Eight Puzzle Destructor*/
EightPuzzle::~EightPuzzle(){
    delete eightPuzzleBoard;
}

 /* Get EightPuzzle Game Score, Score is increase by one in every move, Low Score is much better*/
int EightPuzzle::boardScore() const{
    return _score;
}



/* Print EightPuzzle Board*/
void EightPuzzle::print(ostream& out) const{
    
    out <<"\t3X3 PUZZLE\n";
    for(int i=0 ; i< _row ; ++i){
        for(int j =0 ; j<_column ; ++j){
            out<<" "<<(*eightPuzzleBoard)[i][j];  
        }
        out<<endl;
    }
    out <<"Score : "<< boardScore();
    out <<endl<<endl;

}


/* Get random move to play Automatically*/
string EightPuzzle::getRandomMove(){

    int randVal = rand() % 8 + 1;
    vector<char> direction = {'r' , 'l', 'd', 'u'};
    char directionType = direction[rand () % 4];

    ostringstream os;
    os<<randVal<<" "<<directionType;
    //cerr<<randVal<<" "<<directionType<<endl;
    return os.str();
}

/*Parse EightPuzzle Move into number choice and direction*/
void EightPuzzle::parseMove(){
    _numberChoice = _move[0]-48;
    _direction  = _move[2];
}


/* Make Move*/
void EightPuzzle::makeMove(){
    int i,j;
    findPosition(i,j);
    switch (_direction)
    {
        case 'u':
            (*eightPuzzleBoard)[i-1][j] = (*eightPuzzleBoard)[i][j];
            
            break;
        case 'd':
            (*eightPuzzleBoard)[i+1][j] = (*eightPuzzleBoard)[i][j];

            break;
        case 'r':
            (*eightPuzzleBoard)[i][j+1] = (*eightPuzzleBoard)[i][j];

            break;
        case 'l':
            (*eightPuzzleBoard)[i][j-1] = (*eightPuzzleBoard)[i][j];
            break;
        default:
            break;
    }
    (*eightPuzzleBoard)[i][j] = 0;
    ++_score;
}

/* Find the Position of the desired number*/
void EightPuzzle::findPosition(int &row, int& col){

    for(int i =0 ; i < _row; ++i){
        for(int j=0 ; j< _column ; ++j){
            if((*eightPuzzleBoard)[i][j] == _numberChoice){
                row =i;
                col =j;

                i =_row;
                j = _column;
            }
        }
    } 

}

/* Check if the move can be made or not*/
bool EightPuzzle::canMove(){
    int i,j;
    bool status = false;
    findPosition(i,j);


    switch (_direction)
    {
        case 'u':
            if(i>0 
            && (*eightPuzzleBoard)[i-1][j] == 0) status = true; 
            break;
        case 'd':
            if(i< _row-1 
            && (*eightPuzzleBoard)[i+1][j] == 0) status = true; 
            break;
        case 'r':
            if(j< _column-1 
            && (*eightPuzzleBoard)[i][j+1] == 0) status = true; 
            break;
        case 'l':
            if(j>0 
            && (*eightPuzzleBoard)[i][j-1] == 0) status = true; 
            break;
        default:
            break;
        return status;
    }

}


/* Check if the Puzzle is ended or not*/
bool EightPuzzle::endGame() const{
    bool status = true;
    int counter=0;
    int array[] = {1,2,3,4,5,6,7,8,0};
    for(int i =0 ; i < _row ; ++i){
        for(int j= 0 ; j< _column ; ++j, ++counter){
            if((*eightPuzzleBoard)[i][j] != array[counter]) { i= _row ; j = _column ;status = false;}
        }
    }
    return status;
}


/* Check if the initial board is solvable or not*/
bool EightPuzzle::is_solvable() const{
    
    int inversion = getInversionNumber();

    if(!(inversion & 1)) return true;
    else return false;

    
}

/* Get inversion Number of board to find solvability*/
int EightPuzzle::getInversionNumber() const{

    int inversionNumber = 0;
    for (int i = 0; i < 3 * 3 - 1; ++i)
    {
        for (int j = i + 1; j < 3 * 3; ++j)
        {
            if((elements[i] > elements[j]) && (elements[i] && elements[j]))   ++inversionNumber;
            
        }       
    }
    return   inversionNumber;



}

/* use STL algorithm to randomize location of number in the board*/
void EightPuzzle::randomShuffle(vector<int>& elements){
    
    for(int i=1 ; i< _row*_column; ++i){
        elements.push_back(i);

    }
    elements[8] = 0;
    random_shuffle(elements.begin(), elements.end());
    elements.clear();

}

/* Check the Puzzle move syntax is valid or not*/
bool EightPuzzle::isMoveValid() const{
   
    
    bool status = true;
    if(_move.size()!=3) status = false;
    else if(_move[0] < '1' || _move[0] > '8') status = false;
    else if(_move[1] != ' ') status = false;
    else if(!(_move[2] == 'u' || _move[2] == 'd' ||  _move[2] == 'l' ||  _move[2] == 'r')) status = false;
    if(status == false) throw "Invalid Move Syntax\n";
    return status;

}

/* End*/