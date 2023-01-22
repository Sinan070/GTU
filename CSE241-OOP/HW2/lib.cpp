#include "lib.h"
using namespace std;
/* creating the desired board*/
void create_board(peg_board **board, const int row_size,const int col_size){

(*board)->resize(0, vector<peg_Type>(0));
(*board)->resize(row_size, vector<peg_Type>(col_size));


}

void create_board(peg_board *board, const int row_size,const int col_size){

board->resize(0, vector<peg_Type>(0));
board->resize(row_size, vector<peg_Type>(col_size));


}




/* if the desired board shape is like rectangular board, fill the board using this function*/
void fill_like_rectangular_board(peg_board *board,int row_size,int col_size,int left_end,int right_start,int up_end,int down_start,int empty_x,int empty_y){
    
    int i,j;
    
    for(i=0;i<row_size;i++){
            for(j=0;j<col_size;j++){
                if(!(((j<left_end || j>right_start) && (i<up_end || i>down_start) ))){
                    (*board)[i][j]=peg_Type::peg;
                }
                
            }
        }    
     (*board)[empty_x][empty_y]=peg_Type::empty;

}
/* fill all the board*/
void fill_board(peg_board *board,int choice){
    int i,j,k=0;

    /* col and row size iterator*/
    int iter_row=0;
    int iter_col=0;
    
    /* first create board then fill the board*/
    switch (choice)
    {
    case 1: /* first shape is not rectangular board so fill the this board differently*/
        create_board(&board,7,7);
        for(i = 3;i<6;i++ , iter_col=0){
            for(j =i ;j<5;j++){
                
                iter_col++;
            }
            for(k = 3;k<(i*2);k++){
                (*board)[i-3][iter_col]=peg_Type::peg;
                iter_col++;
         
            }
            while(iter_col<7){
                
                iter_col++;
            }     
        }

        for(i=0;i<7;i++){
            (*board)[3][i]=peg_Type::peg;
        }

        iter_row=3;
        for(i = 4;i>1;i-- ,iter_col=0){
            iter_row++;
            for(j = 4;j>i;j--){
                
                iter_col++;
            }
            for(k = 1;k<(i*2);k++){
                (*board)[iter_row][iter_col]=peg_Type::peg;
                iter_col++;
            }
      
            while(iter_col<7){
                
                iter_col++;
            }
        }
        (*board)[2][3]=peg_Type::empty;
        break;
    /* create board and fill the boards (2-3-4) like rectangular board*/
    case 2:
        create_board(&board,9,9);
        fill_like_rectangular_board(board,9,9,3,5,3,5,2,4);
       
        
        break;
    case 3:
        create_board(&board,8,8);
        fill_like_rectangular_board(board,8,8,2,4,3,5,3,3);
        
        break;

    case 4:
        create_board(&board,7,7);
        fill_like_rectangular_board(board,7,7,2,4,2,4,3,3);
       
        break;

    case 5:
        create_board(&board,9,9);
        for(i = 1;i<6;i++, iter_col=0){
			
            for(j =i ;j<5;j++){
         
         
         	
         iter_col++;
         
      }
      for(k = 1;k<(i*2);k++){
         
         (*board)[i-1][iter_col]=peg_Type::peg;
         iter_col++;
         
      }
      while (iter_col<9)
      {
          
         iter_col++;
      }
      
     
     
   }
        
        iter_row=4;
        for(i = 4;i>=1;i-- ,iter_col=0){
            iter_row++;
            for(j = 5;j>i;j--){
                
                iter_col++;
            }
            for(k = 1;k<(i*2);k++){
                (*board)[iter_row][iter_col]=peg_Type::peg;
                iter_col++;
            }
      
            while(iter_col<9){
                
                iter_col++;
            }
        }
        (*board)[4][4]=peg_Type::empty;
        break;
        
    case 6:
        /* create triangular board and fill it*/
        create_board(&board,5,9);
        for(i = 0; i < 5; i++ ,iter_col=0){
            for(int space = 5; space > i+1; space--){
                iter_col++;       
            }
            
            for(j=0; j<=i; j++){
                (*board)[i][iter_col]=peg_Type::peg;
                
                iter_col++;
                iter_col++;
                }
               
    }
        (*board)[0][4]=peg_Type::empty;
        
        break;
    default:
        break;
    }

}

void  print_board(const peg_board *board){
    /* print board*/
    /* if board element is empty then print ".", if board element is peg print "P"*/    
    int i,j;
    char letter= 'a';
    int num=1;
    cout<<"      ";
    for(i=0;i<(*board)[0].size();i++){
        cout<<letter<<"  ";
        letter++;
    }
    cout<<endl<<endl;
    for(auto object : (*board)){
            cout<<num<<"    ";
            num++;
        for(auto element : object){
            if(element == peg_Type::empty){
                cout<<" . ";    
            }
            else if(element == peg_Type::peg) {
                cout<<" P ";
            }
            else{
                cout<<"   ";
            }
                    
        }
        cout<<"\n\n";
    }
        
    cout<<"\n\n";
}

/* to check if the move is valid to move or not*/
/* if the board type is trinagular , is_triangular_board parameter should be true*/
bool can_move(int move_x, int move_y,direction direction, peg_board *board,bool is_triangular_board){
    
    int flag=0;
    /* numbers showing how far to move.*/
    int num1,num2,num3,num4;
    
    num1=1;
    num2=2;
    num3=0;
    num4=0;
    int num5=1;
    int num6=2;

    /* if the board is triangular shape , fill the nums differently because movement is different*/
    if(is_triangular_board==true){
        num1=2;
        num2=4;
        num3=1;
        num4=2;

    }
    /* check the move value according to each direction*/
    /* if the movement exceed the board size set the flag 1, else check the move is valid the move*/

    if(direction =='r'){
        if(move_x>(*board)[0].size()-3){
            flag=1;
        }
        if( flag==0 && (*board)[move_y][move_x] == peg_Type::peg && (*board)[move_y][move_x+num1] == peg_Type::peg && (*board)[move_y][move_x+num2] == peg_Type::empty){
            return true;
        }
    }   

    else if(direction =='l'){
        if(move_x<2){
            flag=1;
    }
    
        if(flag==0 && (*board)[move_y][move_x] == peg_Type::peg && (*board)[move_y][move_x-num1] == peg_Type::peg && (*board)[move_y][move_x-num2] == peg_Type::empty){
            return true;
        }
    } 
    else if(direction == 'u'){
        if(move_y <2){
            flag=1;
    }
        if(flag==0 && (*board)[move_y][move_x] == peg_Type::peg && (*board)[move_y-num5][move_x+num3] == peg_Type::peg && (*board)[move_y-num6][move_x+num4] == peg_Type::empty){
            return true;
        }
    }
    else if(direction == 'd'){
        if(move_y>board->size()-3){
            flag=1;
        }
        if(flag==0 && (*board)[move_y][move_x] == peg_Type::peg && (*board)[move_y+num5][move_x-num3] == peg_Type::peg && (*board)[move_y+num6][move_x-num4] == peg_Type::empty){
            return true;
        }
    }
    return false;
}


bool peg_move(peg_board *board,int move_x,int move_y,direction dir,bool is_triangular_board){
   int num1,num2,num3,num4;
    /* numbers showing how far to move.*/
    num1=1;
    num2=2;
    num3=0;
    num4=0;
    int num5=1;
    int num6=2;
    if(is_triangular_board==true){
        num1=2;
        num2=4;
        num3=1;
        num4=2;



    }
    /* check if the move is valid firstly*/
    if(can_move(move_x,move_y,dir,board,is_triangular_board)){
        
    /* then move the peg according to numbers required by directions*/
    switch (dir)
    { 
    case direction::right:
        
        (*board)[move_y][move_x] = peg_Type::empty;
        (*board)[move_y][move_x+num2] = peg_Type::peg;
        (*board)[move_y][move_x+num1] = peg_Type::empty;
            
        
       
        break;
    case direction::left:
       
        (*board)[move_y][move_x] = peg_Type::empty;
        (*board)[move_y][move_x-num2] = peg_Type::peg;
        (*board)[move_y][move_x-num1] = peg_Type::empty;
        
        
        break;

    case direction::up:
        
        (*board)[move_y][move_x] = peg_Type::empty;
        (*board)[move_y-num6][move_x+num4] = peg_Type::peg;
        (*board)[move_y-num5][move_x+num3] = peg_Type::empty;
        
        break;
    case direction::down:       
        
        (*board)[move_y][move_x] = peg_Type::empty;
        (*board)[move_y+num6][move_x-num4] = peg_Type::peg;
        (*board)[move_y+num5][move_x-num3] = peg_Type::empty;
                
        break;
    default:
        return 0;
        break;
    }
    }
    else {return 0;} /* return 0 if the move is invalid*/

    return 1; 
      
}   
/* break string move to each compenent then arrange by board vector's index*/
void parse_move(string move,int* move_x,int *move_y,direction *dir){
    *move_x = (int)(move[0]-97);
    *move_y =(int)(move[1]-49);
    
    *dir=(direction)move[3];
    
}

/* get int random value*/
int get_random_int(int max,int min){
    int rand_value = rand()% ((max-min)) +min;
    
    return rand_value;
}

/* check the sytantax of move that entered by user*/
/* return 0 if the sytanx is improper*/ 
bool is_move_syntax_valid(const string move,const int board_row_size,int board_col_size){
    
    if(cin.fail() || move.size()>4 
    || (move[0]<'a' || move[0]>('a'+board_col_size)) 
    || (move[1]<'0' || move[1]>('0'+board_row_size)) 
    || move[2]!= '-'){
        
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    if(move[3]=='d' ||move[3]=='l' || move[3]=='r' || move[3]=='u') return 1;
    return 1;
}

/* check the if the game is finished or not*/
/* check the if the there is move to make or not*/
bool is_game_finished(const peg_board *board,int* peg_num,bool is_triangular_board){
    int i,j;
    int flag=0;
    int count=0;
    
    /* numbers showing how far to move.*/
    int num1,num2,num3,num4;
    num1=1,num2=2;
    num3=0,num4=0;
    if(is_triangular_board){
        num1=2;
        num2=4;
        num3=1;
        num4=2;
    }

    /* first find the remaining pegs then check if these pegs could be make movement or not anymore*/
    for(i=0;i<board->size();i++){
        for(j=0;j<(*board)[0].size();j++){
            
            if((*board)[i][j]==peg_Type::peg){
                (*peg_num)++;
                
                if(j-2>=0 && (*board)[i][j-num2]==peg_Type::empty && (*board)[i][j-num1]==peg_Type::peg){
                    
                    flag=1;
                }
                if(j+2<(*board)[0].size() && (*board)[i][j+num2]==peg_Type::empty && (*board)[i][j+num1]==peg_Type::peg){
                   
                    flag=1;
                }
                if(i-2>=0 && (*board)[i-2][j+num4]==peg_Type::empty && (*board)[i-1][j+num3]==peg_Type::peg){
                   
                   flag=1;
                }
                if(i+2<(*board).size() && (*board)[i+2][j-num4]==peg_Type::empty && (*board)[i+1][j-num3]==peg_Type::peg){
                    
                    flag=1;
                }
                if(flag==1){
                    
                    return 0;
                }

            }
            
        }
    
    }
    /* if ther is a only one pegs, the game is finished by best score*/
    if(count==1){
        return 1;
    }
    
    return 1;

}

/* get computers's movement choice randomly*/
void get_computer_choice(int *move_x, int* move_y, direction* dir,const peg_board *board){

    int rand_val= get_random_int(4,0);
            /* get movement direction randomly*/
            if(rand_val==0){
                *dir = direction::right;
            }
            else if(rand_val ==1) *dir=direction::left;
            else if(rand_val==2) *dir =direction::up;
            else if(rand_val==3) *dir=direction::down;
            
            /* get movement x and y randomly*/
            *move_x = get_random_int((*board)[0].size()+97,97);
            *move_y = get_random_int((*board).size()+1,1);
            
            /* reduce the move value to board vector index*/
            *move_x = (*move_x) -97;
            *move_y = (*move_y) -1; 

}
/* save the board to the desired text file*/
bool save_to_text(peg_board *board, ofstream *output,std::string file_name, bool computer_or_human,const string move){
    
    int i,j;
    char letter= 'a';
    int num=1;
    /* add suffix file extension to the file name*/
    std::string buffer;
    buffer += file_name;
    buffer += ".txt";
    
    /* open file, if the opening file could not open , show error messages then return false*/
    output->open(buffer, ios::out);
	if (!(*output)) {
		cerr<<"File could not be created"<<endl;
        output->close();
        return false;
    
    }
	
    
    (*output)<<" ";
    /* save to the file*/
    if(output->is_open()){

    for(i=0;i<(*board)[0].size();i++){
        (*output) << letter<<"";
        letter++;
    }
    (*output)<<endl;
    for(auto object : (*board)){
            (*output) << num<<"";
            num++;
        for(auto element : object){
            
            if(element == peg_Type::empty){
                (*output)<<".";    
            }
            else if(element == peg_Type::peg) {
                (*output)<<"P";
            }
            else{
                (*output)<<" ";
            }
                    
        }
        (*output)<<"\n";
    }
    } 

    if(computer_or_human==true){
        (*output)<<"Game Type : Human";
    }
    else if(computer_or_human==false){
        (*output)<<"Game Type: Computer";
    }
    (*output)<<"  Move : "<<move;



/* close file and return true*/
output->close();
return true;


}




/* load string vector with board data stored by text*/

bool load_from_text(std::ifstream *input, const std::string file_name,vector<string>* lines){



    int row_num=0;
    int col_num =0;
    /* add suffix extension the file name*/
	std::string buffer;
    buffer += file_name;
    buffer += ".txt";
    
    string line;

    /* string iterator that point out beginnig of the string vector*/
    vector<string>::iterator iter;
    iter= lines->begin();

    /* open files and show error if the file could not open then return false*/
    input->open(buffer, ios::out);
	if (!(*input)) {
        string error_type = "FILE COULD NOT OPEN";
		cerr << "Error type " << error_type << ":" << std::endl;
        input->close();
        return false;
	}
	
    /* get the column number of text then convert to board column size*/
    if(std::getline((*input),line)){
        
        col_num = (int)(line.back()-97);
        lines->insert(iter,line);

    }
    /* get the text to string vector*/
    while (1)
    {   iter = lines->end();
        if(!std::getline((*input),line)){
            break;
        }
        
        lines->insert(iter,line);
        
    }
    

   /* close file and return true*/
    input->close();
    return true;

}

/* pull the board from text and store to the board vector*/
void load_board_from_text(vector <string> lines ,peg_board *board){

    int col=lines[0].size() -1;
    int row = lines.size() -1;
    
    /* if the text character is P, then assign board with peg, if the text character is . ,then assign board with empty*/

    for(int i=1;i<=row;i++){

        for(int j=1;j<=col;j++){
            if(lines[i][j] =='P'){
                
                (*board)[i-1][j-1]= peg_Type::peg;
            }
            if(lines[i][j]== '.'){
                
                (*board)[i-1][j-1]= peg_Type::empty;
            }

        }
    }

}
/* string parsing*/
void parse_string(string to_be_parsed, string* to_parse0, string* to_parse1){

    std::istringstream iss(to_be_parsed);
    iss>>(*to_parse0)>>(*to_parse1);

}