#include "minigames/2048/g2048.h"

#include <iostream>
#include <string>

bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

int main()
{
    bool validSize;
    std::string stringInput;
    while (!validSize)
    {
        std::cout << "Qual vai ser o tamanho do seu jogo? ";
        std::getline(std::cin, stringInput);
        if (is_number(stringInput))
        {
            validSize = true;
        }
    }
    g2048 game(stoi(stringInput));
    game.playGame();

    return 0;
}
