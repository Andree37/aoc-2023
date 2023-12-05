#include <iostream>
#include <map>
#include <sstream>
#include <string>


void part1()
{
    int sum_callibrations = 0;

    std::istringstream input(R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)");
    std::string line;
    while (getline(input, line, '\n'))
    {
        char left = '0';
        char right = '0';
        for (const char c : line)
        {
            if (c >= '0' && c <= '9')
            {
                if (left == '0')
                {
                    left = c;
                }
                right = c;
            }
        }
        std::string callibration_str;
        callibration_str += left;
        callibration_str += right;
        sum_callibrations += atoi(callibration_str.c_str());
    }

    std::cout << sum_callibrations;
}

void part2()
{
    int sum_callibrations = 0;
    std::istringstream input(R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)");

    std::map<std::string, char> mappings;
    mappings["one"] = '1';
    mappings["two"] = '2';
    mappings["three"] = '3';
    mappings["four"] = '4';
    mappings["five"] = '5';
    mappings["six"] = '6';
    mappings["seven"] = '7';
    mappings["eight"] = '8';
    mappings["nine"] = '9';
    mappings["1"] = '1';
    mappings["2"] = '2';
    mappings["3"] = '3';
    mappings["4"] = '4';
    mappings["5"] = '5';
    mappings["6"] = '6';
    mappings["7"] = '7';
    mappings["8"] = '8';
    mappings["9"] = '9';


    std::string line;
    while (getline(input, line, '\n'))
    {
        int left_index = 0;
        int right_index = static_cast<int>(line.length());

        char left = 'x';
        char right = 'x';

        for (int i = 0; i < line.length(); i++)
        {
            int max_length = 6;
            while (max_length > 0)
            {
                if (std::string left_str = line.substr(left_index, max_length); left == 'x' && mappings[left_str])
                {
                    left = mappings[line.substr(left_index, max_length)];
                }

                if (right_index - max_length >= 0)
                {
                    if (std::string right_str = line.substr(right_index - max_length, max_length); right == 'x' &&
                        mappings[right_str])
                    {
                        right = mappings[right_str];
                    }
                }
                --max_length;
            }

            ++left_index;
            --right_index;
        }

        std::string callibration_str;
        callibration_str += left;
        callibration_str += right;

        std::cout << callibration_str << std::endl;
        sum_callibrations += atoi(callibration_str.c_str());
    }

    std::cout << sum_callibrations;
}


int main()
{
    part2();
}
