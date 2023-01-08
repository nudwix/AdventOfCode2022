#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>

int evaluateRound(std::string_view roundInput, std::map<char, std::map<char, int>> ruleSet)
{
    char enemyMove{ roundInput[0] };
    char playerMove{ roundInput[2] };
    return ruleSet[enemyMove][playerMove];
}

int main()
{
    /* rule set v1:
     *     moves: A - enemy plays rock, B - enemy plays paper, C - enemy plays scissors,
     *            X - player goes rock, Y - player goes paper, Z - player goes scissors.
     *     score: 1 - for playing rock, 2 - for playing paper, 3 - for playing scissors,
     *            plus 0 - for lose, 3 - for draw, or 6 - for win.
     */
    const std::map<char, std::map<char, int>> rules1{{ 'A', {{ 'X', 1 + 3 }, { 'Y', 2 + 6 }, { 'Z', 3 + 0 }}},
                                                     { 'B', {{ 'X', 1 + 0 }, { 'Y', 2 + 3 }, { 'Z', 3 + 6 }}},
                                                     { 'C', {{ 'X', 1 + 6 }, { 'Y', 2 + 0 }, { 'Z', 3 + 3 }}}};

    /* rule set v2:
     *     moves: A - enemy plays rock, B - enemy plays paper, C - enemy plays scissors,
     *            X - player should lose, Y - player should draw, Z - player should win.
     *     score: 1 - for playing rock, 2 - for playing paper, 3 - for playing scissors,
     *            plus 0 - for lose, 3 - for draw, or 6 - for win.
     */
    const std::map<char, std::map<char, int>> rules2{{ 'A', {{ 'X', 3 + 0 }, { 'Y', 1 + 3 }, { 'Z', 2 + 6 }}},
                                                     { 'B', {{ 'X', 1 + 0 }, { 'Y', 2 + 3 }, { 'Z', 3 + 6 }}},
                                                     { 'C', {{ 'X', 2 + 0 }, { 'Y', 3 + 3 }, { 'Z', 1 + 6 }}}};


    std::fstream input;
    input.open("../Day2/res/input.txt");
    if (input.is_open())
    {
        std::string line{};
        int totalScoreV1{};
        int totalScoreV2{};
        while (std::getline(input, line))
        {
            totalScoreV1 += evaluateRound(line, rules1);
            totalScoreV2 += evaluateRound(line, rules2);
        }
        input.close();

        std::cout << totalScoreV1 << '\n';
        std::cout << totalScoreV2 << '\n';
    }

    return 0;
}