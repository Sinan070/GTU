
#ifndef BASE_H
#define BASE_H

#include <string>
#include <vector>
#include <iostream>
#include<sstream>
#include <time.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace std;

class BoardGame2D{
    protected:
        string _move;
        int _row;
        int _column;
        int _score;
        virtual bool canMove() =0;
        virtual void makeMove() =0;
        virtual void parseMove()=0;
        virtual string getRandomMove(){};
        virtual void  print(ostream & out) const=0;
        
        virtual bool endGame() const=0;
        virtual int boardScore() const =0;
        virtual bool isMoveValid() const =0;
    public:
        BoardGame2D();
        void playUser(const string & move);
        void virtual playUser() final;
        void playAuto();
        void virtual playAutoAll() final;
        friend ostream& operator<<(ostream & out,const  BoardGame2D &) ;
        static void playVector(vector<BoardGame2D*>);
        virtual void initialize()=0;           
};

    ostream& operator<<(ostream & out,const  BoardGame2D &);
    #endif