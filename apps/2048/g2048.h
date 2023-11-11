#ifndef G_2048_H
#define G_2048_H

#include <iostream>
#include <vector>
#include <string>

class g2048
{
private:
    // Attributes
    int size;
    int previousScore{};
    int score{};
    bool gameOver;
    std::vector<std::vector<int>> previousBoard;
    std::vector<std::vector<int>> board;
    std::vector<int> scores;

    // Initialization and Display
    void showGame();
    std::vector<std::vector<int>> generateEmptyBoard();

    // User Input and Movement
    int getInput();
    void move(int direction);
    void concat(int direction);
    bool hasZero();
    int boardChanged();
    void revertGame();

    // Random Number and Game Logic
    void addRandomNumber();

    // File Operations
    void loadScores();
    void saveScores();

    // Scoring
    void logScore();
    void logScoreHistory();
    void askDisplayScoreHistory();

    // Utility
    bool isNumber(const std::string &s);

public:
    // Constructors
    g2048();
    g2048(int boardSize);

    // Main Game Logic
    void playGame();
};

#endif