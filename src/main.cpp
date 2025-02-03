#include <iostream>
#include <windows.h> 
#include <conio.h> //for _kbhit()
#include <time.h>
#include <vector>
#include <fstream> //for file handeling

using namespace std;

void writedata(int width, int height, int highscore){
    ofstream file("userdata.txt",  std::ios::out | std::ios::trunc); //ios::trunc will always clear the file if it exists
    if(file.is_open()){
        file<<width<<endl;
        file<<height<<endl;
        file<<highscore<<endl;
        file.close();
    }
    else{
        cout<<"Unable to open file";
    }
}


vector<int> readdata(){ //return the array of data [width, height, highscore]
    ifstream file("userdata.txt");
    if(file.is_open()){

        vector<int>data(3, 0);

        for(int i=0;i<3;i++){
            file>>data[i];
        }
        file.close();
        return data;
    }else{
        writedata(50, 25, 0); 
        file.close();
        return readdata(); //if file not found return default values
    }
}

//  basic required functions and global variables
vector<int> data=readdata();
int WIDTH = (data[0] > 2) ? data[0]: 50;
int HEIGHT = (data[1] > 2) ? data[1]: 25;
vector<vector<int>> map(HEIGHT, vector<int>(WIDTH, 0));//defining 2D vector as it can compile at runtime

int difficulty=1;



void gotoxy(int x, int y){ //from stacksoverflow
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
void setColor(int color) { //color for console fonts(stack overflow)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//classes 

class Game{
private:
    bool gameOver;
    int score;
    bool ateFood;

public:
    Game() : gameOver(false), score(0), ateFood(false) {}
    
    bool isGameOver() {return gameOver;}
    void setGameOver(bool state) {gameOver = state;}
    int getScore() { return score;}
    void incrementScore() {score++; }
    bool hasEatenFood() {return ateFood; }
    void setAteFood(bool state) {ateFood = state; }
};

class Snake{
private:
    int x, y;   //coordinates for head
    vector<int> xTail;
    vector<int> yTail;
    int nTail;  //length of tail 
    char dir;
    Game* game;

public:
    Snake(Game* gameInstance) : game(gameInstance), nTail(3), dir('U') {
        x = WIDTH / 2;
        y = HEIGHT / 2;
        for (int i =0;i <nTail;i++) { //inputing the coordinates for the tail
            xTail.push_back(WIDTH / 2);
            yTail.push_back(HEIGHT / 2 + i);
        }
    }

    void draw() { map[y][x] = 1; }
    void drawTails() {
        for (int i = 0;i <nTail;i++){

        map[yTail[i]][xTail[i]] = 2;

        }

    }

    void move() {
            moveTails();
            if(dir =='U' && !collision(x, y-1)) y--;
            if(dir =='D' && !collision(x, y+1)) y++;
            if(dir =='L' && !collision(x-1, y)) x--;
            if(dir =='R' && !collision(x+1, y)) x++;
        }

    void moveTails() {
        if (nTail > int(xTail.size())) { //resizeing the vectors to store more data(double size than before)
            xTail.push_back(xTail.back());
            yTail.push_back(yTail.back());
        }
// updating the parts of body
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

        map[prevY][prevX] = 0; //clearing the remaining parts of body
    }

    bool collision(int x, int y) {

        if (map[y][x] == 9 || map[y][x] == 2) game->setGameOver(true); //here 9=bordered collision and 2= collision with boady
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

void Startmenu(){
    system("cls");
    setColor(11); //Light blue color
    cout<<"\n\n\tWelcome to Snake Game by Team Falcons!\n\n"<<endl;
    setColor(6); //Yellow color
    cout<<"             \t1. Start Game"<<endl;
    cout<<"             \t2. Set Difficulty"<<endl;
    cout<<"             \t3. Set Grid Size"<<endl;
    cout<<"             \t4. Exit Game"<<endl;
    setColor(7); //White color

    int choice;
    cin>>choice;

    switch(choice){
        case 1:
            break;
        case 2:
            system("cls");
            setColor(1); //blue
            cout<<"Choose Difficulty(1-Easy 2-Medium 3-Hard):  ";
            int diff;
            cin>>diff;
            difficulty = (diff==1) ? 1 : (diff==2)? 2 : (diff==3)? 3: 4;

            switch(difficulty){
                case 1:
                    cout<<"\n\n            \tDifficulty set to ";
                    setColor(11); //cyan
                    cout<<"1-Easy";
                    Sleep(1000);
                    break;
                case 2:
                    cout<<"\n\n            \tDifficulty set to ";
                    setColor(14); //light yellow
                    cout<<"2-Medium";
                    Sleep(1000);
                    break; 
                case 3:
                    cout<<"\n\n            \tDifficulty set to ";
                    setColor(4);
                    cout<<"3-Hard";
                    Sleep(1000);
                    break;
                default:
                    setColor(4); //red
                    cout<<"\t           Invalid choice!"<<endl;
                    cout<<"\t      difficulty set to 1-Easy(default)";
                    Sleep(1000);
                    difficulty=1;
            }

            setColor(7); //reset color
            Startmenu();
            break;

        case 3:
            unsigned int x,y;
            system("cls");
            cout<<"Enter New Grid Size (Width x Height) Current Value ["<<readdata()[0]<<'x'<<readdata()[1]<<"]: ";
            cin>>x>>y;
            if (cin.fail()) {  //cin.fail() detects the invalid input
                cin.clear();  //this will clear the remaining buffer
                cout<<"Invalid Input"<<endl;
                Sleep(4000);
                Startmenu();
            }

            if(x <15 || y <15 || x > 75 || y >30){
                setColor(4); //red
                cout<<"\n\n\n           Warning!!";
                cout<<"\n\t     This Grid Size is not suggested game might not work properly \n\n\n";
                setColor(1);// blue
                cout<<"            Do You Want to Continue(y/n): ";

                char ch;
                cin>>ch;

                if(ch== 'y' || ch =='Y'){
                    writedata(x, y, data[2]);
                    cout<<"\n           Grid Size Updated"<<endl;
                    cout<<"             Restarting....."<<endl;
                    Sleep(4000);
                    setColor(7);//white
                    data =readdata(); //resetting the grid
                    WIDTH =data[0];
                    HEIGHT =data[1];
                    map =vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
                    Startmenu();
                    break;
                }
                else{
                    setColor(7);
                    cout <<"Grid size set to Default value: "<<50<<'x'<<25<<endl;
                    writedata(50, 25, data[2]);
                }
                writedata(x, y, data[2]);
                cout<<"\n            Grid Size Updated"<<endl;
                cout<<"              Restarting..."<<endl;
                Sleep(3000);
                data =readdata(); //resetting the grid
                WIDTH =data[0];
                HEIGHT =data[1];
                map =vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
                Startmenu();
                break;

            }
            writedata(x, y, data[2]);
            cout<<"\n            Grid Size Updated"<<endl;
            cout<<"              Restarting..."<<endl;
            Sleep(3000);
            data = readdata(); // Reseeting thr Grid 
            WIDTH = data[0];
            HEIGHT = data[1];
            map = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
            Startmenu();
            break;


        case 4:
            exit(0);
            break;
        default:
            setColor(4); 
            cout<<"\tInvalid Choice!";
            Sleep(1000);
            Startmenu();
    }
}

void layout(){
    for(int i= 0;i <HEIGHT;i++){
        for(int j= 0; j <WIDTH; j++){
            if(i== 0 || i ==HEIGHT-1 || j ==0 || j ==WIDTH-1) map[i][j] = 9;
            else map[i][j]= 0; //empty space
        }
    }
}

void display(){
    gotoxy(2,1); 
    cout << "Score: " << game.getScore() << "   Highest: "<< readdata()[2];

    layout();
    snake.draw();
    snake.drawTails();
    food.draw();

    for(int i =0; i <HEIGHT; i++){
        for(int j =0; j< WIDTH;j++){
            gotoxy(j+2, i+3);
            if(map[i][j] == 9) cout << char(219); //border
            if(map[i][j] == 1) cout << 'O';  //snake head
            if(map[i][j] == 2) cout << 'o';  //snake tail
            if(map[i][j] == 3) cout << char(232); //food
            if(map[i][j] == 0) cout << ' '; //food
        }
    }
}

void input(){
    if(_kbhit()){
        char ch=_getch();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // clear extra inputs
        switch (ch) {
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


void gameOverScreen() {
    system("cls"); 
    gotoxy(WIDTH/2 -5, HEIGHT/2 - 2);
    setColor(4);
    cout << "GAME OVER!";
    setColor(1);
    gotoxy(WIDTH/2- 10, HEIGHT/2);
    cout << "Score: " << game.getScore();
    gotoxy(WIDTH/2+ 5, HEIGHT/2);
    cout << "Highest: " << readdata()[2];
    gotoxy(WIDTH/2 - 15, HEIGHT/2 + 2);
    setColor(2); 
    cout << "Press 'R' to Restart or 'Q' to Quit";
    setColor(7); //white

    while (true) {
        if (_kbhit()) {
            char choice = _getch();

            if (choice == 'r' || choice == 'R') {
                break;  // restart the game
            } else if (choice == 'q' || choice == 'Q') {
                exit(0);
            }
        }
    }
}

int main(){
    HWND s = GetConsoleWindow(); //idea from stackoverflow
    MoveWindow(s, 300, 100, 480, 620, true);
    hideCursor();
    system("cls");


RESTART:
    Startmenu();
    system("cls");
    game = Game();
    snake = Snake(&game);
    food = Food();
    while(!game.isGameOver()){
        display();
        input();
        movements();
        Sleep(200/(difficulty+1));
        if(game.getScore() > data[2]) writedata(WIDTH, HEIGHT, game.getScore()); //Updating High Score live in Runtime
    }
    gameOverScreen();
    goto RESTART;

    return 0;
}
