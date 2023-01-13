#include "Board.h"

#include <fstream>
#include <iostream>
#include <string>

constexpr int boardWidth{ 9 };

int main()
{
    std::fstream input;
    input.open("../Day5/res/input");

    if (input.is_open())
    {
        Board board1(boardWidth);
        Board board2(boardWidth, true);

        std::string line{ "string" };
        while (!line.empty())
        {
            std::getline(input, line);
            board1.fillBoard(line);
            board2.fillBoard(line);
        }

        while (std::getline(input, line))
        {
            if (!line.empty())
            {
                board1.executeCommand(line);
                board2.executeCommand(line);
            }
        }

        input.close();

        std::cout << board1.returnTopRow() << '\n';
        std::cout << board2.returnTopRow() << '\n';
    }

    return 0;
}