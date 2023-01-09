#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

char getIntersection(std::string &line1, std::string &line2)
{
    std::sort(line1.begin(), line1.end());
    std::sort(line2.begin(), line2.end());

    std::string res;
    std::set_intersection(line1.begin(), line1.end(), line2.begin(), line2.end(), std::back_inserter(res));

    return res[0];
}

char getIntersection(std::string &line1, std::string &line2, std::string &line3)
{
    // get intersection between lines 1 & 2
    std::string subRes{ getIntersection(line1, line2) };
    std::sort(line3.begin(), line3.end());

    std::string res;
    std::set_intersection(subRes.begin(), subRes.end(), line3.begin(), line3.end(), std::back_inserter(res));

    return res[0];
}

int getPriorityValue(char c)
{
    // Lowercase item types a through z have priorities  1 through 26.
    // Uppercase item types A through Z have priorities 27 through 52.
    return c - ((c >= 'a') ? ('a' - 1) : ('A' - 27));
}

int main()
{
    std::fstream input;
    input.open("../Day3/res/input");

    if (input.is_open())
    {
        int sumOfPrioritiesV1{};
        int sumOfPrioritiesV2{};

        // buffer for groups of three strings
        int tripleCounter{};
        std::vector<std::string> tripleLines(3);

        std::string line;
        while (std::getline(input, line))
        {
            // I - part with two parts of one rucksack
            // split strings in parts
            std::string part1{ line.substr(0, line.size() / 2) };
            std::string part2{ line.substr(line.size() / 2) };
            sumOfPrioritiesV1 += getPriorityValue(getIntersection(part1, part2));

            // II - part with three rucksacks
            // put string into buffer
            tripleLines[tripleCounter % 3] = line;

            // if three strings collected
            if (tripleCounter % 3 == 2)
                sumOfPrioritiesV2 += getPriorityValue(getIntersection(tripleLines[0], tripleLines[1], tripleLines[2]));

            ++tripleCounter;
        }

        std::cout << sumOfPrioritiesV1 << '\n';
        std::cout << sumOfPrioritiesV2 << '\n';
    }

    return 0;
}