#include "Board.h"

Board::Board(int n, bool multiGrabber)
{
    board = std::vector(n, std::deque<char>());
    isMultiGrabberEnabled = multiGrabber;
}

void Board::placeBox(char box, std::deque<char>& col, char mode = 'f')
{
    // place box (crate) into board column or grabber
    // two modes: f - for placing box on top (used for moving commands)
    //            b - for placing box underneath (used for initial placement commands)
    switch (mode)
    {
        case 'f':
            col.push_front(box);
            return;
        case 'b':
            col.push_back(box);
            return;
    }
}

char Board::liftBox(std::deque<char>& col)
{
    // return lifted box and pop it from column
    char box{ col.front() };
    col.pop_front();
    return box;
}

void Board::replaceBox(std::deque<char>& fromCol, std::deque<char>& toCol)
{
    // place box from column to column or between column and grabber
    placeBox(liftBox(fromCol), toCol);
}

std::string Board::translateCommand(std::string& line)
{
    // translation of initial placement lines
    // example input line "[G] [H] [G] [Q]     [G]     [D]    "
    std::string res(board.size(), ' ');
    for (int i{}; i < line.size(); ++i)
    {
        // using only uppercase letters
        if (line[i] >= 'A' && line[i] <= 'Z')
        {
            // letters placed in every fourth position starting from 2, (- 1) to transform into 0-index
            res[((i + 3) / 4) - 1] = line[i];
        }
    }
    return res;
}

void Board::translateCommand(int& fromCol, int& toCol, int& amount, std::string& line)
{
    // translation of moving commands
    // example input line move 3 from 4 to 6

    size_t start{ line.find(' ') };
    size_t end{ line.find(' ', start + 1) };

    // first number - amount of boxes to move
    amount = stoi(line.substr(start + 1, end));

    start = line.find(' ', end + 1);
    end = line.find(' ', start + 1);

    // second number - number of column to move box from
    fromCol = stoi(line.substr(start + 1, end)) - 1;

    start = line.find(' ', end + 1);

    // third number - number of column to move box to
    toCol = stoi(line.substr(start + 1)) - 1;
}

void Board::fillBoard(std::string line)
{
    // clean up input line
    line = translateCommand(line);

    // for every valid character place box on board in corresponding column
    for (int i{}; i < line.size(); ++i)
    {
        if (line[i] != ' ')
        {
            placeBox(line[i], board[i], 'b');
        }
    }
}

void Board::executeCommand(std::string& line)
{
    // perform moving based on moving command
    int fromCol{}, toCol{}, amount{};

    // translating commands and populating variables
    translateCommand(fromCol, toCol, amount, line);

    // checking if our Board has multi grabbing feature
    if (!isMultiGrabberEnabled)
    {
        // perform classic box movement (upside down result of movement)
        for (; amount > 0; --amount) replaceBox(board[fromCol], board[toCol]);
    } else
    {
        // perform multigrabber box movement (saving box order)
        for (; amount > 0; --amount) replaceBox(board[fromCol], grabber);
        while (!grabber.empty()) replaceBox(grabber, board[toCol]);
    }
}

std::string Board::returnTopRow()
{
    // return top box from every column
    std::string topRow;
    for (std::deque<char> col: board) topRow.push_back(col.front());
    return topRow;
}
