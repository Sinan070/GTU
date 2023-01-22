
#include "lib.h"


int main(){
    srand (time(NULL)); /* to get random value different*/
    int i,j; 
    peg_board  board; /* board*/
     
    int game_choice=5; /* game choice between computer and human*/
    int board_choice=85; /* board  choice between 1-6*/
    string move; /* to get movement*/
    
    /* moves*/
    int move_x; 
    int move_y;
    direction dir;
    
    /* to make move concatenation*/
    ostringstream out;
    
    /* flags*/
    int flag1=0;
    int flag2=0;
    int score=0;
    int flag=0;
    int flag3=0;
    int flag4 =0;
    
    /* FILE STREAM*/
    ofstream output;
    ifstream input;
    /* FILE NAME AND COMMAND STRINGS*/
    string file_name;
    string command;
    string buffer;
    /* TO STORE BOARD INSIDE STRING VECTOR*/
    vector<string> lines;
    /* to check that board is triangular shape or not, default value is false*/
    bool is_triangular_board = false;
        
        while (1)
        {
            flag4=0;
            if(flag==0){
                    while (board_choice!=0)
                    {  


                        /* choice of default peg board or board inside the text file*/
                        cout<<"Please Choice Peg Board Between 1-6 or Press 7 to Load Board from Text File (Exit=0) "<<endl;
                        /* get choice*/
                        cin>>board_choice;
                        /* choice error check*/
                        if(cin.fail()){
                            
                            cin.clear();
                            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                            board_choice=85;
                            cerr<<" !! Wrong Choice !! "<<endl<<endl;
                            continue;
                            
                        }
                        if(board_choice==0){
                            cout<<"See You\n\n";
                            return 0;
                        }
                        if(board_choice<0 || board_choice>7){
                            continue;
                        }
                        
                        
                        /* choice is proper*/
                        else{
                            /* check the choice is equal to triangular shape*/
                            if(board_choice==6){
                                is_triangular_board=true;
                            }
                            /* if the choice is 7, then get the desired file name to be load*/
                            if(board_choice==7){
                                cout<<"Please Enter the File Name (Without file extension) : ";
                                cin>>file_name;
                                /* check the file name if it is invalid or not*/ 
                                if(cin.fail()){
                                
                                cin.clear();
                                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                                cerr<<"!!  Wrong Entery  !!"<<endl<<endl;
                                continue;
                                
                                }

                                /* first load text file to string vector , if this procces work properly then load board with string vector*/
                                else{
                                    ostringstream out1;
                                    out1<<file_name<<".txt";
                                if(load_from_text(&input,file_name,&lines)){
                                        int row,col;
                                        row=lines.size()-2; 
                                        col=lines[0].size()-1;
                                        create_board(&board,row,col);
                                        load_board_from_text(lines,&board);
                                        lines.clear();
                                        flag=1;
                            
                                        break;    
                                    }
                                else
                                    continue;                
                                }

                            }

                            /* fill board according to board type*/
                            fill_board(&board,board_choice);
                            /* set flag 1 and do not back to peg board choice menu*/
                            flag=1;
                            break;
                        }
                                   
                }
            }
                /* print board to screen*/
                cout<<"-------------BOARD--------------\n\n";
                print_board(&board);
                do
                {
                    
                    
                       /* get the game type choice, 1 is human played , 2 is computer played, and check the value is valid or not*/
                    cout<<"Please enter Game Type (Human =1, Computer =2, Exit =0) : " ;
                    cin>>game_choice;
                    if(game_choice==0){
                        flag=0;
                        break;
                    }
                    if(game_choice!=1 && game_choice!=2){
                        continue;
                    }
                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    else{
                        break;
                    }
                    
                }while (game_choice!=0);
            
                cout<<endl;
            /* human played game*/
            if(game_choice==1){
                if(!is_game_finished(&board,&score,is_triangular_board)) /* check the board whether there is a valid move or not, 
                if there is not game is finished
                */
                {
                    
                      
                    /* get move*/
                    cout<<"Please Enter Move Coordination (Row-Col-Direction Ex:(d1-d , a5-l, c4-u, b7-r))  (Exit =0) : ";           
                    cin>>move;
                    if(move[0]=='0' && move.size()<2){
                        continue;
                    }
                    while(flag2==0){

                        
                        if((is_move_syntax_valid(move,board.size(),board[0].size()))){ /* Check the move input if syntax is valid or not*/
                            parse_move(move,&move_x,&move_y,&dir); /*  Break movement input into its components.*/
                            if(peg_move(&board,move_x,move_y,dir,is_triangular_board)){ /* check if the move is valid or not*/ 
                                flag2=1; /* set flag2 1 if move is valid*/
                            }
                           
                        }
                        /* if move is invalid , ask user to enter the valid move*/
                        if(flag2==0){

                            cout<<"Please Enter Proper Move  (Row-Col-Direction Ex:(d1-d , a5-l, c4-u, b7-r))\n\n";
                            cin>>move;

                            }    
                        }
                    /* reset flags*/
                    flag2=0;
                    flag1=0;
                    flag3=0;
                    flag4=0;
                    
                    /* getting choice for save or load current board to-from text file*/
                    while (flag3==0)
                    {
                        
                        
                        flag3=0;
                        
                        cout<<"\nPress Enter the Key ('\\n') or Command ( Ex : (  load sampletext / save sampletext )) : ";
                        /* clearing stdin buffer*/
                        if(flag4==0){

                            cin.ignore(256,'\n');
                            flag4=0;
                        }
                        /* get the choice*/
                        getline(std::cin,buffer);
                        
                        /* parse string to the command and file name*/
                        if(buffer[0]!='\n') {parse_string(buffer,&command,&file_name);}
                        else{ command= "";file_name="";};       
                        /* if command is 'save' , then save the board to the desired text*/
                        if(command == "save"){

                            save_to_text(&board,&output,file_name,true,move);
                            flag3=1;
                        }
                        /* if the command is 'load' , then load the board from the desired text*/
                        else if(command == "load"){
                            if(load_from_text(&input,file_name,&lines)){
                                int row,col;
                                row=lines.size()-2;
                                col=lines[0].size()-1;
                                create_board(&board,row,col);
                                load_board_from_text(lines,&board);
                                flag3=1;
                                lines.clear();
                            }
                            else {
                                flag3=1; flag4=1;
                            }
                        }


                        /* if the user enter enter keyword then ,do nothing */
                        else if(buffer.empty()){ flag3=1;}
                        /* check if the command is valid or not, then show error message*/
                        else{
                            cerr<<"!!  Wrong Command  !!"<<endl<<endl;
                            if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');   
                            }
                            else {cerr<<"!!  Wrong Command  !!"<<endl<<endl; flag4=1;};
                        }
                    }
                    cout<<endl;
                }
            
                else{
                     /* print the score to the screen, score is the remainig pegs number*/   
                      cout<<"Game is finished. Score is : "<<score<<endl<<endl; 
                      flag=0;
                        

                }
                 
                continue;
            }
            
            /* computer played game*/
            else if(game_choice==2){
               
                if(!is_game_finished(&board,&score,is_triangular_board)){
                        
                
                    /* first print board to the screen*/
                    cout<<"-------------BOARD--------------\n\n";
                    print_board(&board);
                    do{   
                        
                        /* get computer move choice and check it until the move is valid and then check if the game is finsihed or not */
                        get_computer_choice(&move_x,&move_y,&dir,&board);
                        
                    }while ((!peg_move(&board,move_x,move_y,dir,is_triangular_board)));
                /* print computer move to the screen*/
                cout<<"Computer's Move Selection : ";
                out << (char)(move_x+97) << move_y+1 << '-'<< (char)dir <<" ";
                cout<<out.str()<<endl<<endl;
                decltype(out.str()) move= out.str();
                out.str("");

                /* set default score 0*/ 
                score=0;
               
                flag3=0;
                flag4=0;
                
                 /* getting choice for save or load current board to-from text file*/
                    while (flag3==0)
                    {
                        
                        flag3=0;
                        
                        cout<<"\nPress Enter the Key ('\\n') or Command ( Ex: ( load sampletext / save sampletext )) : ";
                        
                        /* clearing stdin buffer*/
                        if(flag4==0){
                            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                            flag4=0;
                        }
                        
                        /* get the command and file name together*/
                        getline(std::cin,buffer);
                        /* parse string to the command and file name*/
                        if(buffer[0]!='\n') {parse_string(buffer,&command,&file_name);}
                        else{ command= "";file_name="";}; 
                        
                       
                        
                        /* if command is 'save' , then save the board to the desired text*/
                        if(command == "save"){

                            save_to_text(&board,&output,file_name,false,move);
                            flag3=1;
                        }
                        /* if the command is 'load' , then load the board from the desired text*/
                        else if(command == "load"){
                            
                            if(load_from_text(&input,file_name,&lines)){
                                int row,col;
                                row=lines.size()-2;
                                col=lines[0].size()-1;
                                create_board(&board,row,col);
                                load_board_from_text(lines,&board);
                                flag3=1;
                                lines.clear();
                            }
                            else{
                                flag3=1; flag4=1;
                            }
                        }
                        /* if the user enter enter keyword then ,do nothing */
                        else if(buffer.empty()){ flag3=1;}
                        
                        /* check if the command is valid or not, then show error message*/
                        else{
                            
                            if(cin.fail()){
                                
                                cin.clear();
                                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                                cerr<<"!!  Wrong Command  !!"<<endl<<endl;
                            }
                            
                            else {cerr<<"!! Wrong Command  !!"<<endl<<endl; flag4=1;};

                        }
                        command="";
                        file_name="";

                    }
                    cout<<endl;
                }
                else{
                     /* print the score to the screen, score is the remainig pegs number*/      
                    cout<<"Game is finished. Score is : "<<score<<endl<<endl;
                    flag=0;
                    continue;
                }
                
                
            
            }
                    
            continue;
        }

    return 0;
}