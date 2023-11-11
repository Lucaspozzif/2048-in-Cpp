#ifndef G2048_H
#define G2048_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <windows.h>

class g2048
{
private:
    std::vector<std::vector<int>> previousBoard;
    std::vector<std::vector<int>> board;
    int previousScore{};
    int score{};
    bool gameOver = false;
    int size;

    void showGame();
    void addRandomNumber();
    void move(int direction);
    void concat(int direction);
    int getInput();
    int boardChanged();
    std::vector<std::vector<int>> generateEmptyBoard();
    void revertGame();

public:
    g2048();
    g2048(int boardSize);

    void playGame();
};

#endif