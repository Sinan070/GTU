
#ifndef LIB_h
#define LIB_H


#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;








class Peg_Solitaire{

    public:
        class validation{
            
            public :

            static bool is_move_valid(const string move, const Peg_Solitaire &);
            static bool is_numeric(const int value);
            static bool is_menu_choice_valid(const int value) ;
            static bool is_play_type_valid(const int value);
            static bool is_default_board_choice_valid(const int value);
        };


    /* Cell type enum class*/
    enum  class cell_type : char{
            peg = 'P' , empty= '.' , space =' '
    };
    /* Cell informations*/
    
    public: class Cell{
        private:
            char position; /* Position of the cell*/
            int row; // Row position of the cell
            cell_type cell_Type; // Type of the cell
        public:
            Cell();
            Cell(const char position, const int row);
            Cell(const char positon, const int row_number, const cell_type cell_Type);
            char get_position() const; // Getter function for position
            void set_position(const char position); // Setter function for position
            int get_row() const;
            void set_row(const int row);
            
            
            cell_type get_cell_type() const; // Getter function for cell type
            void set_cell_type(const cell_type cell_Typed); // Setter function for cell_type
    };
        


    private:



        static bool fail_Flag;
        int game_id;
        string file_name;
        int row_number; /* Row number of board*/
        int col_number; // Column numbe of board
        int choice;
        static int peg_number , empty_cell_number; /* Static variables for current state of the board*/
        int extracted_peg=0;
        
        vector<vector<cell_type>> * cells;     
        
        void create_board();  /* Create board*/
        void create_default_board();
        void fill_board();
        void peg_move(const char position, const int row, const char direction); /* Peg move*/
        bool is_game_finished();
        bool can_move(const char position, const int row, const char direction) const;

        vector<vector<Cell>> board;  // Board
        
        

        
       
        void set_row_number(const int row); // Setter function for row number of board
        void set_col_number(const int col); // Setter function for column number of board
         // Compare current board with another
        
        char get_random_direction();
        int get_random_row_position();
        char get_random_col_position();
        
        static string move;
        
        int get_row_number() const; // Getter function for row number of board
        int get_col_number() const; // Getter function for column number of board



    public:
        
       

        void show_current_games_id(const vector<Peg_Solitaire>& ) const;
        bool static get_fail_flag();
        void set_file_name(string file_name);

        static Peg_Solitaire* find_with_game_id(const int game_id, vector<Peg_Solitaire> &);
        Peg_Solitaire() {} ;
        /* Constructorx*/
        Peg_Solitaire(const int choice);
       
        
        
        

        void play_game(); // Play game until the game is finished
        void play(); // Play one step automatically
        void play(const Cell &, const char direction); // Play one step by user
       
        void display() const; // Display the board
        
        /* show number of pegs, number of empty cells,  number of extracted pegs*/  
        static void show_game_info(const Peg_Solitaire &board);

        bool operator > (const Peg_Solitaire &) const;
        


        bool load_board();
        bool save_board();
        void set_game_id(const int game_id);
        
        

        
};

    




#endif