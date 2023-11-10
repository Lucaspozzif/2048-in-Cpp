#include <iostream>
#include <vector>

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
            std::cout << "[" << board[i][j] << "]";
        }
        std::cout << std::endl;
    }
}

void addRandomNumber()
{
    bool done = false;
    while (!done)
    {
        int randCol = rand() % size;
        int randRow = rand() % size;
        int value = rand() % 4 == 0 ? 4 : 2;

        if (board[randCol][randRow] == 0)
        {
            board[randCol][randRow] = value;
            done = true;
        }
    }
}

void move(int direction) // Direction will a int value that represents a direction, it can be 0,1,2 or 3
{
    switch (direction)
    {
    case 0: // move up

        for (int i = 0; i < size; i++)
        {
            int nonZero;
            int *currentIndex = 0;
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] != 0)
                {
                    nonZero[currentIndex] = board[i][j];
                }
            }
            std::cout << nonZero << std::endl;
        }

        break;
    case 1: // move left
        break;
    case 2: // move down
        break;
    case 3: // move right
        break;

    default:
        break;
    }
}

int main()
{
    board = generateEmptyBoard();

    addRandomNumber();
    addRandomNumber();
    showGame();
    move(0);

    return 0;
}
