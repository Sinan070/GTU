#include "BoardGameBase.h"

class PegSolitaire  : public BoardGame2D{
    private :      
        enum class cellType :int{
            empty=1 , peg=2, space =0
        };
        /* board*/
        vector<vector<cellType>> *pegBoard;
        int _rowChoice;
        int _collumnChoice;
        char _directionChoice;   
    public:
        PegSolitaire();
        ~PegSolitaire();
        int boardScore() const;
        void initialize();
    private:
        
        string getRandomMove();
        void print(ostream& out) const;
        void parseMove();
        void makeMove();
        bool canMove();
        bool endGame() const;
        bool isMoveValid() const;
}; 