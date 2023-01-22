
#include "BoardGameBase.h"

class EightPuzzle : public BoardGame2D{
   
    private:
        int _numberChoice;
        char _direction;
        vector<vector<int>> * eightPuzzleBoard;
    public :
        EightPuzzle();
        ~EightPuzzle();
        int boardScore() const;  
        void print(ostream& out) const;
        void initialize();

    private:
        
        string getRandomMove();
        void parseMove();
        void makeMove();
        bool canMove();
        bool endGame() const;
        bool is_solvable() const;
        void randomShuffle(vector<int>& );
        int getInversionNumber() const;
        vector<int> elements;
        void findPosition(int &, int&);
        bool isMoveValid() const;

};