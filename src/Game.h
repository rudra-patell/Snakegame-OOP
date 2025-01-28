#include <conio.h>

#ifndef Game_H
#define Game_H

class Game
{
private:
    bool State;
    int score;

public:
    Game() : State(true), score(0) {
                        
    } 

    void HandleInput(const char event){} 
    
    void Update() {}

    void Draw() {}

    void Reset() {
        State = true;
        score = 0;
    }
    bool isOver() {return !State;}

    int GetScore() {return score;}

    int updateScore(int value) {return score+value;}
    

};


#endif // Game_H