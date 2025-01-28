#include <iostream>
#include <windows.h>

#ifndef Board_H
#define Board_H

class Board{
    private:
        int width, height;
        char snake, border;
        std::string front_Color="0";

    public:

        Board(int w, int h, char snake='0',char border='*'): snake(snake), width(w), height(h), border(border)
        {

            char grid[w][h];
        }

        void gotoxy(int x, int y){ //for solving flickering problem
                COORD coord;
                coord.X = x;
                coord.Y = y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
    

        void printBoard(Board board){
            // system("cls");
            std::string front_Color="color "+ board.front_Color;
            system(front_Color.c_str());
            for(int i=0; i<width; i++){
                for(int j=0; j<height; j++){
                    if(i==0 || i==width-1 || j==height-1 || j==0 ){
                        std::cout<<border<<" ";
                    }
                    else{
                        std::cout<<"  ";
                    }
                }
                std::cout<< std::endl;
            }
        }


        void setFrontColor(int color){
            front_Color=color;
        }
        
        void Draw(Snake& snake, Food& food){
            
        }


};

#endif //Board.h