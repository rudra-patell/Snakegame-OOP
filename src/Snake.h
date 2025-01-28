#ifndef Snake_H
#define Snake_H

#include <vector>
#include "Board.h"

class Snake{
    private:
      int x, y;
      std::vector<int> tailX, tailY;
      int length;
      enum Direction{LEFT, RIGHT, UP, DOWN};
      Direction dir;

    public:

        Snake(int x=width/2, int y=height/2,int length=3): x(x), y(y), length(length) {
            // genrate snake with default parameters unless specified

        void ChangeDir(char dir){
            switch(dir){
                case 'a': dir==LEFT; break;
                case 'd': dir==RIGHT; break;
                case 'w': dir==UP; break;
                case 's': dir==DOWN; break;
            }
        }

       // int* GetBodydata(){ // will return a pointer to the body data structure(link list)}
       // void move(char dir){}     
       // void grow(int size){}
       
};


#endif //Snake_H