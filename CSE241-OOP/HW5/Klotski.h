
#include "BoardGameBase.h"


class Klotski : public BoardGame2D{
    private:
        
    vector<vector<char>> * klotskiBoard;
    int _blockNum;
    char _direction;



    public:
        Klotski();
        ~Klotski();
        int boardScore() const;  
        void print(ostream& out) const;
        void initialize();

    private:
        string getRandomMove();
        void parseMove();
        void makeMove();
        bool canMove();
        bool endGame() const;
        void findPos(int& i, int &j);
        bool isMoveValid() const;
};
