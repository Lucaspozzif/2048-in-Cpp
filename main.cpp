#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <windows.h>

const int size = 4;
std::vector<std::vector<int>> board;
bool gameOver = false;

std::vector<std::vector<int>> generateEmptyBoard()
{
    std::vector<std::vector<int>> board(size, std::vector<int>(size, 0));
    return board;
}

void showGame()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 15 - board[i][j]);
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

void addRandomNumber()
{
    bool done = false;
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

void move(int direction)
{
    const std::vector<std::vector<int>> oldBoard = board;
    switch (direction)
    {
    case 0: // move up
        for (int i = 0; i < size; i++)
        {
            int nonZero[size];
            int *currentIndex = nullptr;

            for (int j = 0; j < size; j++)
            {
                if (currentIndex == nullptr)
                {
                    currentIndex = new int;
                    *currentIndex = 0;
                }
                if (board[j][i] != 0)
                {
                    nonZero[*currentIndex] = board[j][i];
                    (*currentIndex)++;
                }
            }
            for (; (*currentIndex < size); (*currentIndex)++)
            {
                nonZero[*currentIndex] = 0;
            }

            currentIndex = nullptr;
            for (int j = 0; j < size; j++)
            {
                board[j][i] = nonZero[j];
            }
            delete currentIndex;
        }
        break;
    case 1: // move left
        for (int i = 0; i < size; i++)
        {
            int nonZero[size];
            int *currentIndex = nullptr;

            for (int j = 0; j < size; j++)
            {
                if (currentIndex == nullptr)
                {
                    currentIndex = new int;
                    *currentIndex = 0;
                }
                if (board[i][j] != 0)
                {
                    nonZero[*currentIndex] = board[i][j];
                    (*currentIndex)++;
                }
            }
            for (; (*currentIndex < size); (*currentIndex)++)
            {
                nonZero[*currentIndex] = 0;
            }

            currentIndex = nullptr;
            for (int j = 0; j < size; j++)
            {
                board[i][j] = nonZero[j];
            }
            delete currentIndex;
        }
        break;
    case 2: // move down
        for (int i = 0; i < size; i++)
        {
            int nonZero[size];
            int *currentIndex = nullptr;

            for (int j = 0; j < size; j++)
            {
                if (currentIndex == nullptr)
                {
                    currentIndex = new int;
                    *currentIndex = 0;
                }
                if (board[size - 1 - j][i] != 0)
                {
                    nonZero[*currentIndex] = board[size - 1 - j][i];
                    (*currentIndex)++;
                }
            }
            for (; (*currentIndex < size); (*currentIndex)++)
            {
                nonZero[*currentIndex] = 0;
            }

            currentIndex = nullptr;
            for (int j = 0; j < size; j++)
            {
                board[size - 1 - j][i] = nonZero[j];
            }
            delete currentIndex;
        }
        break;
    case 3: // move right
        for (int i = 0; i < size; i++)
        {
            int nonZero[size];
            int *currentIndex = nullptr;

            for (int j = 0; j < size; j++)
            {
                if (currentIndex == nullptr)
                {
                    currentIndex = new int;
                    *currentIndex = 0;
                }
                if (board[i][size - 1 - j] != 0)
                {
                    nonZero[*currentIndex] = board[i][size - 1 - j];
                    (*currentIndex)++;
                }
            }
            for (; (*currentIndex < size); (*currentIndex)++)
            {
                nonZero[*currentIndex] = 0;
            }

            currentIndex = nullptr;
            for (int j = 0; j < size; j++)
            {
                board[i][size - 1 - j] = nonZero[j];
            }
            delete currentIndex;
        }
        break;
    default:
        break;
    }

    // verify if board and oldBoard still the same
}

void concat(int direction)
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
                    board[i][j]++;
                    board[i][j + 1] = 0;
                }
            }
        }
        break;
    case 2: // concat down
        for (int i = 0; i < size; i++)
        {
            for (int j = size; j > 0; j--)
            {
                if (board[j][i] == board[j - 1][i] && board[j][i] != 0)
                {
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

int getInput()
{
    std::string input;
    std::cout << "input: ";
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
    else
    {
        intInput = 4;
    }
    return intInput;
}

bool boardsAreEqual(std::vector<std::vector<int>> oldBoard)
{
    bool boardsAreEqual = true;

    for (int i = 0; i < size && boardsAreEqual; i++)
    {
        for (int j = 0; j < size && boardsAreEqual; j++)
        {
            if (board[i][j] != oldBoard[i][j])
            {
                boardsAreEqual = false;
            }
        }
    }
    return boardsAreEqual;
}

void playGame()
{
    board = generateEmptyBoard();

    addRandomNumber();
    addRandomNumber();

    showGame();
    while (!gameOver)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        int input = getInput();
        const std::vector<std::vector<int>> oldBoard = board;

        move(input);
        concat(input);
        move(input);
        addRandomNumber();
        showGame();
    }
}

int main()
{
    playGame();

    return 0;
}
