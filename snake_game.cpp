#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

class Posn {
public:
    int x, y;
};

class SnakeGame {
private:
    const int width = 75;
    const int height = 20;
    Posn head;
    Posn target;
    vector<Posn> body;
    int length;
    int score;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction MovingTowards;
    bool ifGameOver;

public:
    SnakeGame() {
        Init();
    }

    void Init() {
        ifGameOver = false;
        MovingTowards = STOP;
        head.x = width / 2;
        head.y = height / 2;
        target.x = rand() % width;
        target.y = rand() % height;
        score = 0;
        length = 0;
        body.clear();
    }

    void startGame(const string& name) {
        system("cls");
        // Now we will create walls;
        for (int i = 0; i < width + 1; i++) {
            cout << "-"; // Top wall
        }
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width + 1; j++) {
                if (j == 0 || j == width) cout << "|"; // Side walls
                else if (i == head.y && j == head.x) cout << "o"; // Snake's starting position
                else if (i == target.y && j == target.x) cout << "$"; // Target
                else {
                    bool ifSnakeBody = false;
                    for (int k = 0; k < length; k++) {
                        if (body[k].x == j && body[k].y == i) {
                            cout << "o";
                            ifSnakeBody = true;
                            break;
                        }
                    }
                    if (ifSnakeBody == false) cout << " "; // Empty Space
                }
            }
            cout << endl;
        }

        for (int i = 0; i < width + 1; i++) {
            cout << "-"; // Bottom wall
        }
        cout << endl;

        cout << "Use a, s, d, w keys (c to stop)." << endl;
        cout << name << "'s score: " << score << endl;
    }

    void Move() {
        body.insert(body.begin(), head);

        switch (MovingTowards) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        }

        // If Collisions Happen
        if (head.x < 0 || head.y < 0 || head.x >= width || head.y >= height) ifGameOver = true;
        for (int i = 0; i < length; i++) {
            if (body[i].x == head.x && body[i].y == head.y) ifGameOver = true;
        }

        // If target achieved
        if (head.x == target.x && head.y == target.y) {
            score += 1;
            target.x = rand() % width;
            target.y = rand() % height;
            length++;
        }
    }

    int DifficultyLevel() {
        int level;
        cout << "\n"
            "Difficulty Levels\n"
            "1) Easy\n"
            "2) Medium\n"
            "3) Hard\n"
            "4) Expert\n"
            "Choose: ";
        cin >> level;
        if (level != 1 && level != 2 && level != 3 && level != 4) level = 2;
        // If invalid input, set difficulty to medium
        return ((5 - level) * 50); // For easier difficulty, we will have higher waiting timea
    }

    void Input() {
        if (_kbhit()) { // Checks if there is a user input
            switch (_getch()) {
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

    bool isGameOver() {
        return ifGameOver;
    }
};

int main() {
    string name;
    cout << "Enter name: ";
    cin >> name;
    SnakeGame game;
    int difficulty = game.DifficultyLevel();
    srand(time(0));
    game.Init();

    while (!game.isGameOver()) {
        game.startGame(name);
        game.Input();
        game.Move();
        Sleep(difficulty);
    }

    return 0;
}
