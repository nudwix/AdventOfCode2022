#include <fstream>
#include <iostream>
#include <set>
#include <string>

void printMarkerIndex(std::string& line, int len)
{
    for (int i{ len - 1 }; i < line.size(); ++i)
    {
        std::set<char> seq{};
        for (int j{ i - (len - 1)  }; j <= i; ++j) seq.insert(line[j]);
        if (seq.size() == len)
        {
            std::cout << i + 1 << '\n';
            return;
        }
    }
}


int main()
{
    std::fstream input;
    input.open("../Day6/res/input.txt");
    if (input.is_open())
    {
        std::string line;
        std::getline(input, line);

        printMarkerIndex(line, 4);
        printMarkerIndex(line, 14);

        input.close();
    }
    return 0;
}