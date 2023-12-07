#include <iostream>
#include <sstream>
#include <string>
#include <cmath>


void part1()
{
    std::istringstream input(
        R"(Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11)");

    std::string line;
    float total = 0;
    while (getline(input, line, '\n'))
    {
        float counter = -1;
        std::stringstream line_stream(line);
        line_stream.ignore();
        line_stream.ignore();

        std::vector<std::string> card;

        std::string token;
        while (line_stream >> token)
        {
            if (token == "|")
            {
                break;
            }

            card.push_back(token);
        }

        while (line_stream >> token)
        {
            for (const auto& c : card)
            {
                if (c == token)
                {
                    ++counter;
                }
            }
        }
        if (counter > -1)
        {
            total += powf(2, counter);
        }
    }
    std::cout << total << std::endl;
}

int main()
{
    part1();
}
