#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{

    std::multiset<int> calorieCounts{};

    std::fstream input;
    input.open("../Day1/res/input.txt", std::ios_base::in);

    if (input.is_open())
    {
        int currentCalories{};
        std::string line;
        while(std::getline(input, line))
        {
            if (!line.empty())
            {
                currentCalories += stoi(line);
            }
            else
            {
                calorieCounts.insert(currentCalories);
                currentCalories = 0;
            }
        }

        int maxCalories{ *calorieCounts.rbegin() };
        int sndCalories{ *std::next(calorieCounts.rbegin()) };
        int trdCalories{ *std::next(calorieCounts.rbegin(), 2) };

        // first answer: maximum amount of calories carried by an elf
        std::cout << maxCalories << '\n';
        // second answer: total amount of calories carried by top 3 elves
        std::cout << maxCalories + sndCalories + trdCalories << '\n';

        input.close();
    }

    return 0;
}
