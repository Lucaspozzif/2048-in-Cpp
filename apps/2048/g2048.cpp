#include "g2048.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <windows.h>
#include <fstream>

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

std::vector<std::vector<int>> g2048::generateEmptyBoard()
{
    std::vector<std::vector<int>> board(size, std::vector<int>(size, 0));
    return board;
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

bool g2048::hasZero()
{
    bool hasZero = false;
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
    return hasZero;
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

void g2048::revertGame()
{
    score = previousScore;
    board = previousBoard;
}

void g2048::addRandomNumber()
{
    bool done = false;
    srand(time(NULL));

    while (!done)
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

void g2048::loadScores()
{
    std::ifstream file("2048-scores");
    if (file.is_open())
    {
        int score;
        while (file >> score)
        {
            scores.push_back(score);
        }
        file.close();
    }
}

void g2048::saveScores()
{
    std::ofstream file("2048-scores");
    if (file.is_open())
    {
        for (const int &score : scores)
        {
            file << score << "\n";
        }
        file.close();
    }
}

void g2048::logScore()
{
    scores.push_back(score);
    std::cout << "Seu Score: " << score << std::endl;
    saveScores();
}

void g2048::logScoreHistory()
{
    std::cout << "Histórico de Scores:\n";
    for (const int &score : scores)
    {
        std::cout << "[" << score << "]\n";
    }
}

void g2048::askDisplayScoreHistory()
{
    char response;
    std::cout << "Quer ver o histórico de Scores? (s/n): ";
    std::cin >> response;

    if (response == 's' || response == 'S')
    {
        logScoreHistory();
    }
}

bool g2048::isNumber(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

void g2048::playGame()
{
    bool validSize;
    std::string stringInput;
    while (!validSize)
    {
        std::cout << "Qual vai ser o tamanho do seu jogo? ";
        std::getline(std::cin, stringInput);
        if (isNumber(stringInput))
        {
            validSize = true;
        }
    }
    size = stoi(stringInput);
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
            else
            {
                if (!hasZero())
                {
                    gameOver = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        showGame();
    }
    loadScores();
    logScore();
    askDisplayScoreHistory();
}

g2048::g2048() : size(4) {}
g2048::g2048(int boardSize) : size(boardSize) {}