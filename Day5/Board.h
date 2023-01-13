#ifndef ADVENTOFCODE2022_BOARD_H
#define ADVENTOFCODE2022_BOARD_H

#include <deque>
#include <string>
#include <vector>

class Board
// class for managing crates in space
{
private:
    bool isMultiGrabberEnabled;                                                        // can grabber carry several crates at once?
    std::deque<char> grabber;                                                          // grabber for several crates
    std::vector<std::deque<char>> board;                                               // representation of crates in space

    char liftBox(std::deque<char>& col);                                               // grabbing box
    void placeBox(char box, std::deque<char>& col, char mode);                         // placing crate to destination
    void replaceBox(std::deque<char>& beginCol, std::deque<char>& endCol);             // moving crate from A to B

    std::string translateCommand(std::string& line);                                   // translation for initial placement commands
    void translateCommand(int& beginCol, int& endCol, int& amount, std::string& line); // translation for moving commands

public:
    explicit Board(int n, bool multiGrabber=false);                                    // constructor

    void fillBoard(std::string line);                                                  // command for initial placement
    void executeCommand(std::string& line);                                            // moving command
    std::string returnTopRow();                                                        // top crate for every column

};

#endif //ADVENTOFCODE2022_BOARD_H
