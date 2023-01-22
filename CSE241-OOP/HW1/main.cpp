
#include "lib.h"
#include <iostream>

int main(){
    srand (time(NULL)); /* to get random value different*/
    int i,j; 
    peg_board  board; /* board*/
     
    int game_choice=5; /* game choice between computer and human*/
    int board_choice=6; /* board  choice between 1-6*/
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
    
    /* to check that board is triangular shape or not, default value is false*/
    bool is_triangular_board = false;
        
        while (1)
        {
             
            if(flag==0){
                while (board_choice!=0)
                {
                /* getting board choice and checking the input is valid or not*/
                cout<<"Please Choice Peg Board Between 1-6 (Exit=0) "<<endl;
                cin>>board_choice;
                if(board_choice==0){
                    cout<<"See You\n\n";
                    return 0;
                }
                if(board_choice<0 || board_choice>6){
                    continue;
                }
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                    
                }
                else{
                    /* check the choice is equal to triangular shape*/
                    if(board_choice==6){
                        is_triangular_board=true;
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
                print_board(&board);
                while (game_choice!=0)
                {   /* get the game type choice, 1 is human played , 2 is computer played, and check the value is valid or not*/
                    cout<<"Please enter Game Type (Human =1, Computer =2, Exit =0) : " ;
                    cin>>game_choice;
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
                }
            
            
            /* human played game*/
            if(game_choice==1){
                while (!is_game_finished(&board,&score,is_triangular_board)) /* check the board whether there is a valid move or not, 
                if there is not game is finished
                */
                {
                    /* print board*/
                    print_board(&board);  
                    /* get move*/
                    cout<<"Please Enter Move Coordination (Row-Col-Direction Ex:(d1-d , a5-l, c4-u, b7-r))  (Exit =0) \n";           
                    cin>>move;
                    if(move[0]=='0' && move.size()<2){
                        break;
                    }
                    while(flag2==0){

                        
                        if((is_move_syntax_valid(move,board.size(),board[0].size()))){ /* Check the move input if syntax is valid or not*/
                            move_seperator(move,&move_x,&move_y,&dir); /*  Break movement input into its components.*/
                            if(peg_move(&board,move_x,move_y,dir,is_triangular_board)){ /* check if the move is valid or not*/ 
                                flag2=1; /* set flag2 1 if move is valid*/
                            }
                        
                        }
                        /* if move is invalid , ask user to enter the valid move*/
                        if(flag2==0){

                            print_board(&board);
                            cout<<"Please Enter Proper Move  (Row-Col-Direction Ex:(d1-d , a5-l, c4-u, b7-r))\n\n";
                            cin>>move;

                            }    
                        }
                    /* reset flags*/
                    flag2=0;
                    flag1=0;
                }
                continue;
            }
            
            /* computer played game*/
            else if(game_choice==2){
                
                do{
                    /* first print board to the screen*/
                    print_board(&board);
                    do{   
                        /* get computer move choice and check it until the move is valid and then check if the game is finsihed or not */
                        get_computer_choice(&move_x,&move_y,&dir,&board);
                        
                    }while ((!peg_move(&board,move_x,move_y,dir,is_triangular_board)));
                /* print computer move to the screen*/
                cout<<"Computer's Move Selection : "<<endl;
                out << (char)(move_x+97) << move_y+1 << '-'<< (char)dir <<" ";
                cout<<out.str()<<endl;
                out.str("");
                /* set default score 0*/ 
                score=0;
                
                }while(!is_game_finished(&board,&score,is_triangular_board));
                
                print_board(&board);
            
            }
            
            /* print the score to the screen, score is the remainig pegs number*/       
            cout<<"Game is finished. Score is : "<<score<<endl<<endl;
            flag=0;
            continue;
        }

    return 0;
}