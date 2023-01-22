#include "game.h" /* Peg Solitaire Library*/

int main(){
    
    srand(time(NULL)); /* this function used to get different random value*/
    
    int flag=0; /* main menu flag*/
    
    int game_id; /* game id*/
    
    /* movement variables*/
    char position; int row;
    char direction;

    string move; /* move*/
    string file_name; /* file name */


    int main_board_choice; /* this variable determine how to select the board.*/ 
    
    int default_board_choice; /* this variable determine default board between 1-6*/

    vector<Peg_Solitaire> peg_solitaires; /* vector of peg_solitaires to store all games*/
    Peg_Solitaire *iter; /* peg_solitaire pointer */
    
    int play_type;
    int status =0;
        /* main menu*/
        while (1)
        {   cout << "\n       ******MAIN MENU******\n";
            cout<< "Please enter 1 to chooce default boards\n";
            cout<< "Please enter 2 to load board from textfile\n";
            cout << "Please enter 3 to load with game id\n";
            cout<< "Please enter 0 to exit\n";

            cin >> main_board_choice;
            cout<<endl;
            /* validation*/
            if(!Peg_Solitaire::validation::is_menu_choice_valid(main_board_choice)) {continue;};
            
            /* submenu*/
            while (1)
            {
                
                if(main_board_choice==1){
                    cout<<"Please enter the chooce between 1-6 :";
                    cin>> default_board_choice;
                    cout<<endl; 
                    /* validation*/
                    if(!Peg_Solitaire::validation::is_default_board_choice_valid(default_board_choice)){
                        continue;
                    }
                    
                    peg_solitaires.push_back(Peg_Solitaire(default_board_choice));
                    
                    cout << "Please enter the game id :";
                    cin >> game_id;
                    cout<<endl;
                    /* validation*/
                    if(!Peg_Solitaire::validation::is_numeric(game_id)) continue;
                    peg_solitaires.back().set_game_id(game_id);
                    
                   
                    
                }
                else if(main_board_choice==2){
                    peg_solitaires.push_back(Peg_Solitaire());
                    
                    cout<<"Please enter the name of the text file: ";
                    cin>> file_name;
                    cout<<endl;
                    peg_solitaires.back().set_file_name(file_name);
                    if(!peg_solitaires.back().load_board()){flag=1  ; break;}; /* validation*/
                    
                   

                    cout << "Please enter the game id :";
                    cin >> game_id;
                    cout<<endl;
                    if(!Peg_Solitaire::validation::is_numeric(game_id)) continue; /* validation*/
                    
                    peg_solitaires.back().set_game_id(game_id);
                    
                    
                    
                }
                else if(main_board_choice ==3){
                    cout<<"Please Enter the Game Id :";
                    cin >> game_id;
                    cout<<endl;
                    if(!Peg_Solitaire::validation::is_numeric(game_id)) continue; /* validation*/
                    
                }
                else if(main_board_choice==0){
                    cout<<"Good bye\n\n";
                    return 0;
                }
                
                


                break;
            }    
            if(flag==1){ flag=0; continue;}
                
            iter = Peg_Solitaire::find_with_game_id(game_id, peg_solitaires);
            if(iter==NULL) continue;
        
            (*iter).display();
            
            /* play menu*/
            while (status==0)
            {
                cout<<"\n";
                cout<< "        ******PLAY MENU******\n";
                cout<<"Please enter the 1 to play one steep\n";
                cout <<"Please enter the 2 to play one step automatically\n";
                cout<<"Please enter the 3 to play until the game is finished automatically\n";
                cout<< "Please enter 4 to compare game with another status\n";
                cout << "Please enter 5 to save board to the file\n";
                cout << "Please enter the 0 to back choce board again\n" ;
                cin >>play_type;
                cout<<endl;
                
                if(!Peg_Solitaire::validation::is_play_type_valid(play_type)){ /* validation*/

                    (*iter).display();
                       
                    continue;}
                
                if(play_type == 1){
                    cout<< "Please enter the move (ex: b4-r) :";
                    cin >> move;
                    cout<<endl;
                    
                    if(!Peg_Solitaire::validation::is_move_valid(move, (*iter))){ /* validation*/
                        (*iter).display();
                        Peg_Solitaire::show_game_info(*iter);
                        cerr<< "Invalid move\n";
                        continue;
                    }
                    position = move[0];
                    row = move[1]-48;
                    direction = move[3];
                
                    (*iter).play(Peg_Solitaire::Cell(position, row) , direction); 
                    (*iter).display();
                    Peg_Solitaire::show_game_info(*iter);
                }
                else if(play_type == 2){
                    
                    (*iter).play();
                    (*iter).display();
                    Peg_Solitaire::show_game_info(*iter);
                }
                else if(play_type == 3){
                    (*iter).play_game();
                    (*iter).display();
                    Peg_Solitaire::show_game_info(*iter);
                }
                else if(play_type == 4){
                    
                    Peg_Solitaire *iter2;
                    
                    (*iter).show_current_games_id(peg_solitaires);
                    cout<<"Please enter the game id :";
                    cin >> game_id;
                    cout<<endl;

                    if(!Peg_Solitaire::validation::is_numeric(game_id)){ (*iter).display();continue;}; /* validation*/
                    iter2 = Peg_Solitaire::find_with_game_id(game_id, peg_solitaires);
                    if (Peg_Solitaire::get_fail_flag() == true || iter2 == NULL)
                    {
                        continue;
                    }
                    


                    if((*iter) > (*iter2)){
                        cout<<"First Game has more pegs\n";
                    }
                    
                }
                else if(play_type == 5){
                    cout<<"Please enter the name of the text file: ";
                    cin>> file_name;
                    cout<<endl;
                    (*iter).set_file_name(file_name);
                    (*iter).save_board();
                    



                }
                else if(play_type == 0){
                    status=1;
                }
        
                
            }
        status=0;
        }
        

    return 0;
}