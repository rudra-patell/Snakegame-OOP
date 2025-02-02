#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <vector>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;
int map[HEIGHT][WIDTH];

void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor(){
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 100;
    cursor.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

class Game{
private:
    bool gameOver;
    int score;
    bool ateFood;

public:
    Game() : gameOver(false), score(0), ateFood(false) {}
    
    bool isGameOver() { return gameOver; }
    void setGameOver(bool state) { gameOver = state; }
    int getScore() { return score; }
    void incrementScore() { score++; }
    bool hasEatenFood() { return ateFood; }
    void setAteFood(bool state) { ateFood = state; }
};

class Snake{
private:
    int x, y;
    vector<int> xTail;
    vector<int> yTail;
    int nTail;
    char dir;
    int delay;
    int count_delay;
    Game* game;

public:
    Snake(Game* gameInstance) : game(gameInstance), nTail(10), dir('U'), delay(3), count_delay(0) {
        x = WIDTH / 2;
        y = HEIGHT / 2;
        for (int i = 0; i < nTail; i++) {
            xTail.push_back(WIDTH / 2);
            yTail.push_back(HEIGHT / 2 + i);
        }
    }

    void draw() { map[y][x] = 1; }
    void drawTails() {
        for (int i = 0; i < nTail; i++) map[yTail[i]][xTail[i]] = 2;
    }

    void move() {
        if(count_delay == delay){
            moveTails();
            if(dir =='U' && !collision(x, y-1)) y--;
            if(dir =='D' && !collision(x, y+1)) y++;
            if(dir =='L' && !collision(x-1, y)) x--;
            if(dir =='R' && !collision(x+1, y)) x++;
            count_delay = 0;
        }
        count_delay++;
    }

    void moveTails() {
        if (nTail > int(xTail.size())) {
            xTail.push_back(xTail.back());
            yTail.push_back(yTail.back());
        }

        int prevX = xTail[0];
        int prevY = yTail[0];
        int tempX, tempY;

        xTail[0] = x;
        yTail[0] = y;

        for (int i = 1; i < nTail; i++) {
            tempX = xTail[i];
            tempY = yTail[i];
            xTail[i] = prevX;
            yTail[i] = prevY;
            prevX = tempX;
            prevY = tempY;
        }

        map[prevY][prevX] = 0;
    }

    bool collision(int x, int y) {
        if (map[y][x] == 9 || map[y][x] == 2) game->setGameOver(true);
        if (map[y][x] == 3) {
            game->incrementScore();
            nTail++;
            game->setAteFood(true);
            xTail.push_back(xTail.back());
            yTail.push_back(yTail.back());
        }
        return game->isGameOver();
    }

//getters and setters
    char getDirection() { return dir; }
    void setDirection(char newDir) { dir = newDir; }

};

class Food{
private:
    int x, y;

public:
    Food() {
        move();
    }
    void draw() { map[y][x] = 3; }
    void move() {
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
        } while (map[y][x] != 0);
    }
};

Game game;
Snake snake(&game);
Food food;

void layout(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) map[i][j] = 9;
            else map[i][j] = 0;
        }
    }
}

void display(){
    gotoxy(2,1); 
    cout << "Score: " << game.getScore();

    layout();
    snake.draw();
    snake.drawTails();
    food.draw();

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            gotoxy(j+2, i+3);
            if(map[i][j] == 9) cout << char(219);
            if(map[i][j] == 1) cout << char(79);
            if(map[i][j] == 2) cout << char(111);
            if(map[i][j] == 3) cout << char(232);
            if(map[i][j] == 0) cout << char(32);
        }
    }
}

void input(){
    if(_kbhit()){
        switch (_getch()) {
            case 'w': if(snake.getDirection() != 'D') snake.setDirection('U'); break;
            case 's': if(snake.getDirection() != 'U') snake.setDirection('D'); break;
            case 'a': if(snake.getDirection() != 'R') snake.setDirection('L'); break;
            case 'd': if(snake.getDirection() != 'L') snake.setDirection('R'); break;

        }
    }
}

void movements(){
    snake.move();
    if(game.hasEatenFood()){
        food.move();
        game.setAteFood(false);
    }
}

int main(){
    HWND s = GetConsoleWindow();
    MoveWindow(s, 300, 100, 480, 620, true);
    hideCursor();
    system("cls");
    while(!game.isGameOver()){
        display();
        input();
        movements();
        Sleep(50);
    }
}
