#include "g2048.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <windows.h>

void g2048::showGame()
{
    std::cout << "Score: " << score << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, board[i][j]);
            double result = std::pow(2, board[i][j]) == 1 ? 0 : std::pow(2, board[i][j]);
            if (board[i][j] < 4)
            {
                std::cout << "[-" << result << "--]";
            }
            else if (board[i][j] < 7)
            {
                std::cout << "[-" << result << "-]";
            }
            else if (board[i][j] < 10)
            {
                std::cout << "[" << result << "-]";
            }
            else
            {
                std::cout << "[" << result << "]";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void g2048::addRandomNumber()
{
    bool done = false;
    bool hasZero = false;
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 0)
            {
                hasZero = true;
            }
        }
    }
    if (!hasZero)
    {
        gameOver = true;
    }
    while (!done && hasZero)
    {
        int randCol = rand() % size;
        int randRow = rand() % size;
        int value = rand() % 4 == 0 ? 2 : 1;

        if (board[randCol][randRow] == 0)
        {
            board[randCol][randRow] = value;
            done = true;
        }
    }
}

void g2048::move(int direction)
{
    const std::vector<std::vector<int>> oldBoard = board;
    switch (direction)
    {
    case 0: // move up
        for (int i = 0; i < size; i++)
        {
            std::vector<int> nonZero;

            for (int j = 0; j < size; j++)
            {
                if (board[j][i] != 0)
                {
                    nonZero.push_back(board[j][i]);
                }
            }
            for (int j = 0; j < size; j++)
            {
                nonZero.push_back(0);
            }

            for (int j = 0; j < size; j++)
            {
                board[j][i] = nonZero[j];
            }
        }
        break;
    case 1: // move left
        for (int i = 0; i < size; i++)
        {
            std::vector<int> nonZero;

            for (int j = 0; j < size; j++)
            {
                if (board[i][j] != 0)
                {

                    nonZero.push_back(board[i][j]);
                }
            }
            for (int j = 0; j < size; j++)
            {
                nonZero.push_back(0);
            }

            for (int j = 0; j < size; j++)
            {
                board[i][j] = nonZero[j];
            }
        }
        break;
    case 2: // move down
        for (int i = 0; i < size; i++)
        {
            std::vector<int> nonZero;

            for (int j = 0; j < size; j++)
            {
                if (board[size - 1 - j][i] != 0)
                {

                    nonZero.push_back(board[size - 1 - j][i]);
                }
            }
            for (int j = 0; j < size; j++)
            {
                nonZero.push_back(0);
            }

            for (int j = 0; j < size; j++)
            {
                board[size - 1 - j][i] = nonZero[j];
            }
        }
        break;
    case 3: // move right
        for (int i = 0; i < size; i++)
        {
            std::vector<int> nonZero;

            for (int j = 0; j < size; j++)
            {
                if (board[i][size - 1 - j] != 0)
                {

                    nonZero.push_back(board[i][size - 1 - j]);
                }
            }
            for (int j = 0; j < size; j++)
            {
                nonZero.push_back(0);
            }

            for (int j = 0; j < size; j++)
            {
                board[i][size - 1 - j] = nonZero[j];
            }
        }
        break;
    default:
        break;
    }

    // verify if board and oldBoard still the same
}

void g2048::concat(int direction)
{
    switch (direction)
    {
    case 0: // concat up
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (board[j][i] == board[j + 1][i] && board[j][i] != 0)
                {
                    score += board[j][i];
                    board[j][i]++;
                    board[j + 1][i] = 0;
                }
            }
        }
        break;
    case 1: // concat left
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (board[i][j] == board[i][j + 1] && board[i][j] != 0)
                {
                    score += board[i][j];
                    board[i][j]++;
                    board[i][j + 1] = 0;
                }
            }
        }
        break;
    case 2: // concat down
        for (int i = 0; i < size; i++)
        {
            for (int j = size - 1; j > 0; j--)
            {
                if (board[j][i] == board[j - 1][i] && board[j][i] != 0)
                {
                    score += board[j][i];
                    board[j][i]++;
                    board[j - 1][i] = 0;
                }
            }
        }

        break;
    case 3: // concat right
        for (int i = 0; i < size; i++)
        {
            for (int j = size; j > 0; j--)
            {
                if (board[i][j] == board[i][j - 1] && board[i][j] != 0)
                {
                    score += board[i][j];
                    board[i][j]++;
                    board[i][j - 1] = 0;
                }
            }
        }
        break;
    default:
        break;
    }
}

int g2048::getInput()
{
    std::string input;
    std::cout << "input (wasd ou z para reverter): ";
    std::getline(std::cin, input);

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    int intInput;
    if (input == "w")
    {
        intInput = 0;
    }
    else if (input == "a")
    {
        intInput = 1;
    }
    else if (input == "s")
    {
        intInput = 2;
    }
    else if (input == "d")
    {
        intInput = 3;
    }
    else if (input == "z")
    {
        intInput = 4;
    }
    else
    {
        intInput = 5;
    }
    return intInput;
}

int g2048::boardChanged()
{
    bool boardsAreEqual = true;

    for (int i = 0; i < size && boardsAreEqual; i++)
    {
        for (int j = 0; j < size && boardsAreEqual; j++)
        {
            if (board[i][j] != previousBoard[i][j])
            {
                boardsAreEqual = false;
            }
        }
    }
    return boardsAreEqual ? 0 : 1;
}

std::vector<std::vector<int>> g2048::generateEmptyBoard()
{
    std::vector<std::vector<int>> board(size, std::vector<int>(size, 0));
    return board;
}

void g2048::revertGame()
{
    score = previousScore;
    board = previousBoard;
}

void g2048::playGame()
{
    board = generateEmptyBoard();

    addRandomNumber();
    addRandomNumber();
    previousBoard = board;

    showGame();
    while (!gameOver)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        int input = getInput();
        if (input == 4)
        {
            revertGame();
        }
        else
        {
            previousBoard = board;
            previousScore = score;
            move(input);
            concat(input);
            move(input);
            if (boardChanged())
                addRandomNumber();
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        showGame();
    }
}

g2048::g2048() : size(4) {}
g2048::g2048(int boardSize) : size(boardSize) {}