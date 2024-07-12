#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
using namespace std;

const int width = 75;
const int height = 20;

int x,y;                            // Head Coordinates
int targetX, targetY;               // Target Coordinates
vector<int> bodyX, bodyY;           // Coordinates for body of snake
int length;                         // Snake's length
int score;                          // Player's score

enum Direction { STOP = 0 , LEFT , RIGHT , UP , DOWN };
Direction MovingTowards;

bool ifGameOver;

void Init(){
    ifGameOver = false;
    MovingTowards = STOP;
    x = width/2;
    y = height/2;
    targetX = rand() % width;
    targetY = rand() % height;
    score = 0;
    length = 0;
    bodyX.clear();
    bodyY.clear();
}

void startGame(string name){
    system("cls");
    // Now we will create walls;
    for(int i = 0 ; i < width + 1 ; i++){
        cout << "-";                // Top wall
    }
    cout << endl;

    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width + 1 ; j++){
            if(j == 0 || j == width) cout << "|";   // Side walls

            else if(i == y && j == x) cout << "o";  // Snake's starting position

            else if(i == targetY && j == targetX) cout << "$";  // Target

            else{
                bool ifSnakeBody = false;
                for(int k = 0 ; k < length ; k++){
                    if(bodyX[k] == j && bodyY[k] == i){
                        cout << "o";
                        ifSnakeBody = true;
                        break;
                    }
                }
                if(ifSnakeBody == false) cout << " ";           // Empty Space
            }
        }
        cout << endl;
    }

    for(int i = 0 ; i < width + 1 ; i++){
        cout << "-";                // Bottom wall
    }
    cout << endl;

    cout << name << "'s score: " << score << endl;
}

void Move(){
    bodyX.insert(bodyX.begin(), x);
    bodyY.insert(bodyY.begin(), y);

    switch(MovingTowards){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // If Collisions Happen

    if(x < 0 || y < 0 || x >= width || y >= height) ifGameOver = true;

    for(int i = 0 ; i < length ; i++){
        if(bodyX[i] == x && bodyY[i] == y) ifGameOver = true;
    }

    // If target achieved
    if(x == targetX && y == targetY){
        score += 1;
        targetX = rand() % width;
        targetY = rand() % height;
        length++;
    }
}

int DifficultyLevel(){
    int level;

    cout << "\n"
            "Difficulty Levels\n"
            "1) Easy\n"
            "2) Medium\n"
            "3) Hard\n"
            "Choose: ";

    cin >> level;

    if(level != 1 && level != 2 && level != 3) level = 2;
    // If invalid input, set difficulty to medium

    return ((4-level) * 50);            // For easier difficulty, we will have higher waiting timea
}

void Input(){
    if(_kbhit()){                       // Checks if there is a user input
        switch(_getch()){
            case 'a':
                MovingTowards = LEFT;
                break;
            case 's':
                MovingTowards = DOWN;
                break;
            case 'd':
                MovingTowards = RIGHT;
                break;
            case 'w':
                MovingTowards = UP;
                break;
            case 'c':
                ifGameOver = true;
                break;
        }
    }
}

int main(){
    string name;
    cout << "Enter name: ";
    cin >> name;
    int difficulty = DifficultyLevel();

    Init();
    while(ifGameOver == false){
        startGame(name);
        Input();
        Move();
        Sleep(difficulty);
    }

    return 0;
}