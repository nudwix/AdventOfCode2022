#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

void assertExamples();
void collectNumbers(const std::string& line, int& a, int& b, int& c, int& d);
bool isIncluding(int a, int b, int c, int d);
bool isOverlapping(int a, int b, int c, int d);

int main()
{
    assertExamples();
    
    std::fstream input;
    input.open("../Day4/res/input.txt");
    if (input.is_open())
    {
        int includeCount{};
        int overlapCount{};

        std::string line;
        while (std::getline(input, line))
        {
            int a{}, b{}, c{}, d{};
            collectNumbers(line, a, b, c, d);

            if (isIncluding(a, b, c, d)) includeCount++;
            if (isOverlapping(a, b, c, d)) overlapCount++;

        }

        std::cout << includeCount << '\n';
        std::cout << overlapCount << '\n';
    }

    return 0;
}

void assertExamples()
{
    // asserting examples from task
    assert(isIncluding(2, 4, 6, 8) == false);
    assert(isIncluding(2, 3, 4, 5) == false);
    assert(isIncluding(5, 7, 7, 9) == false);
    assert(isIncluding(2, 8, 3, 7) == true);
    assert(isIncluding(6, 6, 4, 6) == true);
    assert(isIncluding(2, 6, 4, 8) == false);

    assert(isOverlapping(2, 4, 6, 8) == false);
    assert(isOverlapping(2, 3, 4, 5) == false);
    assert(isOverlapping(5, 7, 7, 9) == true);
    assert(isOverlapping(2, 8, 3, 7) == true);
    assert(isOverlapping(6, 6, 4, 6) == true);
    assert(isOverlapping(2, 6, 4, 8) == true);
}

void collectNumbers(const std::string& line, int& a, int& b, int& c, int& d)
{
    // lookup for separators
    std::size_t mid{ line.find(',') };
    std::size_t sep1{ line.find('-') };
    std::size_t sep2{ line.find('-', mid) };

    // extracting each number
    a = stoi(line.substr(0, sep1));
    b = stoi(line.substr(sep1 + 1, mid - sep1 - 1));
    c = stoi(line.substr(mid + 1, sep2 - mid - 1));
    d = stoi(line.substr(sep2 + 1));
}

bool isIncluding(int a, int b, int c, int d)
{
    // including if [a {c d} b] or {c [a b] d}
    return a <= c && d <= b || c <= a && b <= d;
}

bool isOverlapping(int a, int b, int c, int d)
{
    // overlapping if [a {c b] d} or {c [a d} b] or including
    return a <= c && c <= b && b <= d || c <= a && a <= d && d <= b || isIncluding(a, b, c, d);
}
