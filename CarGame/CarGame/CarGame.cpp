// CarGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ', '=', '=', ' ',
                    '=', '=', '=', '=',
                    ' ', '=', '=', ' ',
                    '=', '=', '=', '=' };

int carPos = WIN_WIDTH / 2;
int score = 0;

void goToXY(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setCursor(bool visible, DWORD size) {
    if (size == 0) {
        size = 20;
    }

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 17; j++) {
            goToXY(0 + j, i);
            cout << "[";
            goToXY(WIN_WIDTH - j, i);
            cout << "]";
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        goToXY(SCREEN_WIDTH, i); 
        cout << "+";
    }
}

void generateEnemy(int id) {
    enemyX[id] = 17 + rand() % (33);
}

void drawEnemy(int id) {
    if (enemyFlag[id]) {
        goToXY(enemyX[id], enemyY[id] + 0); cout << "++++";
        goToXY(enemyX[id], enemyY[id] + 1); cout << " ++ ";
        goToXY(enemyX[id], enemyY[id] + 2); cout << "++++";
        goToXY(enemyX[id], enemyY[id] + 3); cout << " ++ ";
    }
}

void eraseEnemy(int id) {
    if (enemyFlag[id]) {
        goToXY(enemyX[id], enemyY[id] + 0); cout << "    ";
        goToXY(enemyX[id], enemyY[id] + 1); cout << "    ";
        goToXY(enemyX[id], enemyY[id] + 2); cout << "    ";
        goToXY(enemyX[id], enemyY[id] + 3); cout << "    ";
    }
}

void resetEnemy(int id) {
    eraseEnemy(id);
    enemyY[id] = 1;
    generateEnemy(id);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            goToXY(j + carPos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            goToXY(j + carPos, i + 22); cout << " ";
        }
    }
}

int collision() {
    if (enemyY[0] + 4 >= 23) {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9) {
            return 1;
        }
    }
    if (enemyY[1] + 4 >= 23) {
        if (enemyX[1] + 4 - carPos >= 0 && enemyX[1] + 4 - carPos < 9) {
            return 1;
        }
    }

    return 0;
}

void gameOver() {
    system("cls");
    cout << endl;
    cout << "\t\t-------------------------------------" << endl;
    cout << "\t\t------------Game over----------------" << endl;
    cout << "\t\t-------------------------------------" << endl;
    cout << "\t\tPress any key to go back to menu     " << endl;
    _getch();
}

void updateScore() {
    goToXY(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n-------------------------------";
    cout << "\nAvoid Cars by moving left or right";
    cout << "\n\n Press 'a' to move left";
    cout << "\n Press 'd' to move right";
    cout << "\n Press 'esc' to exit";
    cout << "\n Press any key to go back to menu";
    _getch();
}

void play() {
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    generateEnemy(0);
    generateEnemy(1);
    
    goToXY(WIN_WIDTH + 7, 2); cout << "Car Game";
    goToXY(WIN_WIDTH + 6, 4); cout << "--------";
    goToXY(WIN_WIDTH + 6, 6); cout << "--------";
    goToXY(WIN_WIDTH + 7, 12); cout << "Controls";
    goToXY(WIN_WIDTH + 7, 13); cout << "--------";
    goToXY(WIN_WIDTH + 2, 14); cout << "A key - Left";
    goToXY(WIN_WIDTH + 2, 15); cout << "D key - Right";

    goToXY(18, 5); cout << "Press any key to start";
    _getch();

    goToXY(18, 5); cout << "                         ";
    
    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 18) {
                    carPos -= 4;
                }
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < 50) {
                    carPos += 4;
                }
            }
            if (ch == 27) {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1) {
            gameOver();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10) {
            if (enemyFlag[1] == 0) {
                enemyFlag[1] = 1;
            }
        }

        if (enemyFlag[0] == 1) {
            enemyY[0] += 1;
        }

        if (enemyFlag[1] == 1) {
            enemyY[1] += 1;
        }

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }

}


int main()
{
    setCursor(0, 0);
    srand((unsigned)time(NULL));
    
    do {
        system("cls");
        goToXY(10, 5);  cout << "------------------------";
        goToXY(10, 6);  cout << "|       Car Game       |";
        goToXY(10, 7);  cout << "------------------------";
        goToXY(10, 9);  cout << "1. Start game";
        goToXY(10, 10); cout << "2. Instruction";
        goToXY(10, 11); cout << "3. Quit    ";
        goToXY(10, 13); cout << "Select option: ";
        int option = _getche();
        option -= 48;

        switch (option)
        {
        case 1: play(); break;
        case 2: instructions(); break;
        case 3: exit(0);
        }
    } while (1);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
