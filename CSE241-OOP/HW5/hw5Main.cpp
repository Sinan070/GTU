#include "Klotski.h"
#include "PegSolitaire.h"
#include "Puzzle.h"
#include <time.h>
#include <string>
#include <fstream>
namespace{

    void Test(vector<BoardGame2D *> games){
        
    
        cout << "Vector Function is testing\n";
        BoardGame2D::playVector(games);
        
        
            for(auto game : games){
                game->initialize();
                cout << "PlayAuto Function is testing\n";
                cout <<"Initial Board\n" <<*game;    
                game->playAuto();
                cout <<"Final Board"<<game<<endl<<endl;

                game->initialize();
                cout << "PlayAutoAll Function is testing\n";
                cout <<"Initial Board\n" <<*game;    
                game->playAutoAll();
                cout <<"Final Board"<<*game<<endl<<endl;
                
                
                
                game->initialize();
                cout << "PlayUser(string) Function is testing\n";
                cout <<"Initial Board\n" <<*game;    
                string move;
                cout <<"Please Enter the move : ";
                getline(std::cin, move);
                game->playUser(move);
                cout <<"Final Board"<<*game<<endl<<endl;


                game->initialize();
                cout << "PlayUser Function is testing\n";
                cout <<"Initial Board\n" <<*game;    
                game->playUser();
                cout <<"Final Board"<<*game<<endl<<endl;
            
            }
            
        
    }

}



int main(){
    srand(time(NULL));
    
    PegSolitaire *PegSolitaire1 = new PegSolitaire();
    PegSolitaire *PegSolitaire2 = new PegSolitaire();

    
    Klotski *Klotski1 = new Klotski();
    Klotski *Klotski2 = new Klotski();
    
    EightPuzzle *EightPuzzle1 = new EightPuzzle();
    EightPuzzle *EightPuzzle2 = new EightPuzzle();

    vector<BoardGame2D *> games;

    games.push_back(PegSolitaire1);
    games.push_back(PegSolitaire2);
    games.push_back(Klotski1);
    games.push_back(Klotski2);
    games.push_back(EightPuzzle1);
    games.push_back(EightPuzzle2);

    Test(games);
    
}
