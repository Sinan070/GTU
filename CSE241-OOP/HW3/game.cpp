#include "game.h"
#include <vector> 

/*Peg_Solitaire Constructors*/
/*Constructor for default game board choose*/
Peg_Solitaire::Peg_Solitaire(const int choice) : choice(choice){

    create_default_board(); /* create and fill default board with respect to the choice*/

}


/* Cell Constructors*/

/* default constructor*/
Peg_Solitaire::Cell::Cell(){ 
    
}

/* Constructor for Cell Movement*/
 
Peg_Solitaire::Cell::Cell( const char position, const  int row ){ 
    set_position(position); /* Set column position*/ 
    set_row(row); /* Set row position*/
    
}

/*The constructor used to make the assignment to the Board.*/
Peg_Solitaire::Cell::Cell(const char position , const int row_num , const cell_type cell_Type){
    
    set_row(row_num); /* set row position of cell*/
    set_position(position); /* set column position of cell*/
    set_cell_type(cell_Type); /* set type of cell*/ /*Empty, space or peg*/

}



// getter ,setter for cell

/* get position of the cell*/
char Peg_Solitaire::Cell::get_position() const{
    
    return this->position;
}

/* set position of the cell*/
void Peg_Solitaire::Cell::set_position(const char position)
{   
    this->position= position; 
}

/* get row position of the cell*/ 
int Peg_Solitaire::Cell::get_row() const {

    return this->row;
}

/* set row position of the cell*/
void Peg_Solitaire::Cell::set_row(const int row){
    this->row = row;

}

/* get type of the cell*/
Peg_Solitaire::cell_type Peg_Solitaire::Cell::get_cell_type() const
{
    return this->cell_Type;
}

/* Set type of the cell*/
void Peg_Solitaire::Cell::set_cell_type(const cell_type cell_Type)
{
    this->cell_Type= cell_Type;

}


/* Create game of the board empty with respect to row and column size*/ 
void Peg_Solitaire::create_board()
{   
    board.clear();
    board.resize(0,vector<Cell>(0));
    board.resize(this->row_number , vector<Cell>(this->col_number));
    
}

/* Print board of the game*/
void Peg_Solitaire::display() const
{   
    cout<<"\n";
    cout <<"      ****** BOARD *******\n";
    int i,j;
    char letter= 'a';
    int num=1;
    cout<<"      ";
    for(i=0;i<row_number;++i){
        cout<<letter<<"  ";
        ++letter;
    }

    cout<<endl<<endl;
    
    for(auto object : board){
            cout<<num<<"    ";
            ++num;
        for(auto element : object){
            if(element.get_cell_type() == cell_type::empty){
                
                cout<<" . ";    
            }
            if(element.get_cell_type() == cell_type::peg) {
               
                cout<<" P ";
            }
            if(element.get_cell_type() == cell_type::space){
                cout<<"   ";
            }
                   
        }
        cout<<"\n\n";
    }
    
    cout<<"\n\n";
}

/* Check the move is valid or not. If the movement is valid return true else return false*/ 
bool Peg_Solitaire::can_move(const char position, const int row, const char direction) const{


int flag=0;
int i,j;
    
    j = (int)(position -97);
    i = (row-1);

   
    if(direction =='r'){
        if( j > col_number-3){
            flag=1;
        }
        if(flag==0 && (board)[i][j].get_cell_type()== cell_type::peg && 
            (board)[i][j +1].get_cell_type()== cell_type::peg && 
            (board)[i][j +2].get_cell_type() == cell_type::empty){
            
            return true;
        }
    }   

    else if(direction =='l'){
        if(j < 2){
            flag=1;
        }
    
        if(flag==0 && (board)[i][j].get_cell_type() == cell_type::peg && 
        (board)[i][j -1].get_cell_type() == cell_type::peg && 
        (board)[i][j -2].get_cell_type() == cell_type::empty){
            return true;
        }
    } 
    else if(direction == 'u'){
        if(i <2){
            flag=1;
    }
        if(flag==0 && (board)[i][j].get_cell_type() == cell_type::peg 
        && (board)[i-1][j].get_cell_type() == cell_type::peg 
        && (board)[i -2][j].get_cell_type() == cell_type::empty){
            return true;
        }
    }
    else if(direction == 'd'){
        if(i > row_number -3){
            flag=1;
        }
        if(flag==0 && (board)[i][j].get_cell_type() == cell_type::peg 
        && (board)[i +1][j].get_cell_type() == cell_type::peg 
        && (board)[i +2][j].get_cell_type() == cell_type::empty){
            return true;
        }
    }
    
    return false;
}


/* Making the movement*/
void Peg_Solitaire::peg_move(const char position, const int row, const char direction)
{   

        int i,j;
        
        j = (int)(position -97);
        i = (row-1);

        switch (direction)
        {
        case 'r' :

            board[i][j].set_cell_type(cell_type::empty); 
            board[i][j+2].set_cell_type(cell_type::peg);
            board[i][j+1].set_cell_type(cell_type::empty); 


            break;
        case 'l' :
            (board)[i][j].set_cell_type(cell_type::empty);
            (board)[i][j-2].set_cell_type(cell_type::peg);
            (board)[i][j-1].set_cell_type(cell_type::empty);
            break;
        case 'u':
            (board)[i][j].set_cell_type(cell_type::empty);
            (board)[i-2][j].set_cell_type(cell_type::peg);
            (board)[i-1][j].set_cell_type(cell_type::empty); 
            break;
        case 'd':
            (board)[i][j].set_cell_type(cell_type::empty);
            (board)[i+2][j].set_cell_type(cell_type::peg);
            (board)[i+1][j].set_cell_type(cell_type::empty); 
            break;

        default:
            break;
        }



}


/* getter for board number of row*/
int Peg_Solitaire::get_row_number() const
{
    return row_number;
}
/* getter for board number of column*/
int Peg_Solitaire::get_col_number() const
{
    return col_number;
}
/* setter for board number of row. If the number of row is greater than 4 then set*/
void Peg_Solitaire::set_row_number(const int row)
{
    if(row>4){
        
        this->row_number = row;
    }
}

/* setter for board number of column. If the number of column is greater than 4 then set*/
void Peg_Solitaire::set_col_number(const int col)
{
    if(col>4){
        this->col_number = col;
    }
}


/* This function plays the game by asking
the user the board type first then automatically plays the game until it ends. The boards should be printed to the screen.*/

void Peg_Solitaire::play_game()
{

    char direction;
    int row;
    char col_position;
    

    while (is_game_finished()==0){
        
        
    
        
        direction = get_random_direction();
        row = get_random_row_position();
        col_position = get_random_col_position();
        

        
        if(can_move(col_position, row , direction)){ 
            peg_move(col_position, row , direction);
            ++extracted_peg;
            
        }
            
    }


cerr<< "The game is over";
cout<<endl;

}

/* plays the game for a single step */
void Peg_Solitaire::play()
{   
    char direction;
    int row;
    char col_position;
    int status =0;


        while (status==0)
        {   

                
            direction = get_random_direction();
            row = get_random_row_position();
            col_position = get_random_col_position();
        

            if(can_move(col_position, row , direction)){
                peg_move(col_position, row , direction);
                ++extracted_peg;
                
                status = 1;
            }
            if(is_game_finished()==true) 
            {
                status =1;
                cerr<<" The game is over\n\n";
            
            };
        }   
                   
        cout<<endl;

}

/*This function takes a cell position and direction and played by the user*/
void Peg_Solitaire::play(const Cell &cell, const char direction)
{   if(can_move(cell.get_position(), cell.get_row(), direction)) peg_move(cell.get_position(), cell.get_row(),direction);
    else{ cout<< "!!Invalid Move!!\n\n";};
    


}

/* Check the game is finished or not, If the game was finished return 1 ,else return 0*/
bool Peg_Solitaire::is_game_finished(){

    int peg_num=0;
    int flag=0;

    for(int i=0;i<row_number;++i){
        for(int j=0;j<col_number;++j){
            
            if((board)[i][j].get_cell_type()== cell_type::peg){
                ++peg_num;
                
                if(j-2>=0 && (board)[i][j-2].get_cell_type()== cell_type::empty && (board)[i][j-1].get_cell_type()== cell_type::peg){
                    
                    flag=1;
                }
                if(j+2 < col_number && (board)[i][j+2].get_cell_type()== cell_type::empty && (board)[i][j+1].get_cell_type()== cell_type::peg){
                   
                    flag=1;
                }
                if(i-2>=0 && (board)[i-2][j].get_cell_type() == cell_type::empty && (board)[i-1][j].get_cell_type() == cell_type::peg){
                   
                   flag=1;
                }
                if(i+2<(board).size() && (board)[i+2][j].get_cell_type() == cell_type::empty && (board)[i+1][j].get_cell_type() == cell_type::peg){
                    
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
        cerr<< "The game is over succesffuly. Well Done\n\n";
        return 1;
    }
    return 1;


}


/* Operator for compare two Peg Solitaire Games. It returns true is the first game has more pegs, otherwise it returns false.  */
bool Peg_Solitaire::operator > (const Peg_Solitaire & peg_solitaire) const{


    bool flag=0;

    int max_row, max_col;
    int peg_number1 = 0 ; int peg_number2=0;


    if(peg_solitaire.row_number > this->row_number){
        max_row = peg_solitaire.row_number;
    }   
    else{ max_row = this->row_number;}

    
    if(peg_solitaire.col_number > this->col_number){
        max_col = peg_solitaire.col_number;
    }   
    else{ max_col = this->col_number;}


    for(int i=0 ; i < max_row ; ++i){
        for(int j= 0; j< max_col ; j++){
            
            if(i< peg_solitaire.row_number && j<peg_solitaire.col_number){
                if(peg_solitaire.board[i][j].get_cell_type() == cell_type::peg) { ++peg_number1;}
            }        

            if(i< this->row_number && j < this->col_number){
                if(board[i][j].get_cell_type() == cell_type::peg) { ++peg_number2;}
            }     
        }
    }

    if(peg_number2 > peg_number1){
        flag =1;
    }
    else{ flag= 0;}

    return flag;

}


/*this function shows the number of pegs, number of empty cells, and number of pegs*/
void Peg_Solitaire::show_game_info(const Peg_Solitaire & game)
{   
    
    for(auto object : game.board){
            
        for(auto element : object){
            
            if(element.get_cell_type() == cell_type::peg){
                ++peg_number;
            }
            if(element.get_cell_type() == cell_type::empty){
                ++empty_cell_number;
            }
            
                    
        }
        
    }

    cout<<endl<< "Number of Pegs: "<<peg_number <<endl<<"Empty Cells Number: "<<empty_cell_number <<endl<<"Extreacted Pegs Number : "<< game.extracted_peg << endl<<endl;

    empty_cell_number=0;
    peg_number= 0;
    

}

/* this function creates and fill the default boards. There are 6 predefined 2d cell_type vector*/ 
void Peg_Solitaire::create_default_board(){
    
    switch (this->choice)
    {
    case 1:
        set_col_number(7);
        set_row_number(7);
        

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space},
            
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::empty,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            
            {cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},

        });

        break;
    case 2:

        set_col_number(9);
        set_row_number(9);
       

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},                        
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},

            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::empty,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            
            

        });
        

        break;
    case 3:

        set_col_number(8);
        set_row_number(8);
        

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},                 
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},

            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::empty,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            
        });
        break;

    case 4:

        set_col_number(7);
        set_row_number(7);
       

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::empty,cell_type::peg,cell_type::peg,cell_type::peg},
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
        });
        break;
    
    case 5:
        set_col_number(9);
        set_row_number(9);
        

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::space,cell_type::space,cell_type::space,cell_type::space},                        
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space},
            
            {cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::empty,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg},
            
            
            {cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::peg,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::space,cell_type::space,cell_type::space,cell_type::space},
            
            

        });


        break;
    case 6:

        set_col_number(9);
        set_row_number(5);
        

        this->cells = new vector<vector<cell_type>>({

            {cell_type::space,cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::space,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::space},
            {cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space},
            {cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg,cell_type::space,cell_type::peg},

        });
        break;

    default:
        break;
    }

    
    this->create_board();
    fill_board();
    delete cells;

}
/* This function fill the board */
void Peg_Solitaire::fill_board(){
    char position = 'a';
    int counter=0;
    for(int i =0; i< this->row_number; ++i){
        position = 'a';
        for(int j=0 ; j < this->col_number ; ++j)
        {
            
            board[i][j] = Peg_Solitaire::Cell(position, (i+1) , (*cells)[i][j]);
            ++position;
        
        }
        
 
    }
    
}
/* This function is inline. It returns random direction between u, d, r, l*/
inline char Peg_Solitaire::get_random_direction(){
    vector<char> direction = {'u' , 'd', 'r', 'l'};
    
    return direction[rand () % 4];
     
        

}
/* This function is inline. It returns random row position*/
inline int Peg_Solitaire::get_random_row_position(){

    int rand_val= rand () % this->row_number +1 ; 
    return rand_val;

}
/*This function is inlime. It returns random column position*/
inline char Peg_Solitaire::get_random_col_position(){
    char rand_value;
    
    rand_value =  rand () % (this->col_number) +97;

    return rand_value;  
}

/* This function load game board from text file*/
bool Peg_Solitaire::load_board(){

    bool status;
    extracted_peg=0;
    int row_num=0;
    int col_num =0;
    char position ='a';
    
	
    ifstream input_file;

    string line;
    /* add suffix extension the file name*/
    ostringstream out;
    out<< file_name<<".txt";
    
        input_file.clear();
        input_file.seekg(0, input_file.beg);
        
    
    /* open files and show error if the file could not open then return false*/ 
    input_file.open(out.str() , ios::in);   
	if (!(input_file)) {

		cerr << "FILE COULD NOT OPEN";
        status = false;
        input_file.close();
	}
    /* If file is open*/
	if(input_file){
        
        status = true;
        /* get the column number of text then convert to board column size*/
        if(getline(input_file,line)){

            col_num = (int)(line.back()-96);
            
        }
        set_col_number(col_num);/* set column number*/
        /* find row number*/
        while (1)
        {
            if(!getline((input_file),line)){
                
                break;
            }
            ++row_num;
            
        }
        
        set_row_number(row_num); /* set row_number*/
        
        create_board(); /* create board with respect to the row and column number*/
        

        int i=0;
        
        input_file.clear(); /* reset error bit*/ 
        input_file.seekg(col_num+2, input_file.beg); /* iter pointer to the second line*/
        
        
        
        /* get the board from text then assign to the board*/
        while (1)
        {   
            if(!getline((input_file),line)){
                
                break;
            }
            position = 'a';
            
            
            
            if(i < row_num){
                
                for(int j=1 ; j <= col_num ; ++j){
                
                    if(line[j] =='P'){
                        
                        (board)[i][j-1] =  Peg_Solitaire::Cell(position, i, cell_type::peg);
                    }
                    if(line[j] == '.'){
                        
                        (board)[i][j-1]=  Peg_Solitaire::Cell(position, i, cell_type::empty);
                    }
                    if(line[j]== ' '){
                        
                        (board)[i][j-1] =  Peg_Solitaire::Cell(position, i, cell_type::space);
                        
                    }
                    ++position;
                    
                }   
            
            ++i;
        
            }
            
        }


   /* close file and return true*/
    input_file.close();
    cerr << "Loading is succesfull\n\n";
   
    }

return status;

}


/* setter for file_name*/
void Peg_Solitaire::set_file_name(const string file_name){
    this->file_name =  file_name;
}


/* This function save board to the text file*/
bool Peg_Solitaire::save_board(){

    ofstream output_file;

    ostringstream out;
    int i,j;
    char letter= 'a';
    int num=1;
    /* add suffix file extension to the file name*/
    out<<file_name<<".txt";
    
    /* open file, if the opening file could not open , show error messages then return false*/
    output_file.open(out.str(), ios::out);
	if (!(output_file)) {
		cerr<<"File could not be created"<<endl;
        output_file.close();
        return false;
    
    }
	
    
    output_file << " ";

    /* save to the file*/
    if(output_file.is_open()){

        for(i=0 ;i < this->col_number ; ++i){
            output_file << letter<<"";
            letter++;
        }
        output_file << endl;
        for(auto object : board){
                output_file << num << "";
                num++;
            for(auto element : object){
                
                if(element.get_cell_type() == cell_type::empty){
                    output_file << ".";    
                }
                else if(element.get_cell_type() == cell_type::peg) {
                    output_file << "P";
                }
                else{
                    output_file << " ";
                }
                        
            }
            output_file << "\n";
        }
    } 

    



/* close file and return true*/
cerr<<" Saving is succesfull\n\n";
output_file.close();
return true;


}


/* This function search the Peg Solitaire game with respect to the game id , then return it, if the there is no game with game id return null*/
Peg_Solitaire* Peg_Solitaire::find_with_game_id(const int game_id, vector<Peg_Solitaire> & Peg_Solitaires){
    
    Peg_Solitaire * ptr;
    
    for(int i=0 ; i< Peg_Solitaires.size(); ++i){

        if(Peg_Solitaires[i].game_id == game_id){
           
            ptr = &Peg_Solitaires[i];
            fail_Flag = false;        
            return ptr;
        }
    }
    cerr<<"Game was not found\n\n";
    
    fail_Flag= true;
    return NULL;
}

/* setter for game id*/
void Peg_Solitaire::set_game_id(const int game_id){

        this->game_id= game_id;
        
    
}

/* input validation*/
bool Peg_Solitaire::validation::is_numeric(const int value){
    bool status;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        status= false;
    }
    else{
        status = true;
    }
    return status;
}

bool Peg_Solitaire::validation::is_menu_choice_valid(const int value){
    bool status;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        status = false;
    }
    else if(value >3 || value<0) status =false;
    else{
        status = true;
    }
    return status;
    
}
bool Peg_Solitaire::validation::is_play_type_valid(const int value){
    
    bool status;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        status = false;
    }
    else if(value >5 || value<0) status =false;
    else{
        status = true;
    }


return status;

}

bool Peg_Solitaire::validation::is_move_valid(const  string move, const Peg_Solitaire & game){
    bool status;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        status = false;
    }
    
    else if(move.size()>4) status =false;
    else if(move[0] <'a' || move[0]> ('a'+ game.col_number)){
        status = false;
    }
    else if((move[1]<'0' || move[1]>('0'+ game.row_number))) status =false;
    else if(move[2]!= '-') status = false;
    else if((!(move[3]=='d' ||move[3]=='l' || move[3]=='r' || move[3]=='u'))) status = false;
    else { status = true;};
    return status;
    
}
bool Peg_Solitaire::validation::is_default_board_choice_valid(const int value){
    bool status;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        status = false;
    }
    else if(value >6 || value<1) status =false;
    else{
        status = true;
    }


return status;
}

/* getter for fail_flag*/
bool Peg_Solitaire::get_fail_flag(){

    return fail_Flag;

}
/* this function shows all games id*/
void Peg_Solitaire::show_current_games_id(const vector<Peg_Solitaire> &games) const{
    
    
    cout << "IDs of Currnet Games\n";
    for(int i=0; i< games.size() ; i++){
        cout<<(i+1)<<": "<< games[i].game_id<<endl;
    }
}

/* static variable initilization*/
bool Peg_Solitaire::fail_Flag;


string Peg_Solitaire::move;


 int Peg_Solitaire:: peg_number=0;
 int Peg_Solitaire:: empty_cell_number=0;