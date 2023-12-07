#include <iostream>
#include <cctype>
#include <map>
#include <sstream>
#include <string>

bool is_special(const char c)
{
    return !isalpha(c) && !isdigit(c) && c != '.';
}

void part1()
{
    std::istringstream input(
    R"(467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..)");

    size_t real_num_counter = 0;
    std::vector matrix(1000, std::vector<char>(1000));
    std::string line;
    size_t row = 0;
    size_t column = 0;
    while (getline(input, line, '\n'))
    {
        column = line.length();
        for (size_t i = 0; i < line.length(); ++i)
        {
            matrix[row][i] = line[i];
        }
        ++row;
    }


    for (int i = 0; i < row; ++i)
    {
        bool is_real = false;
        std::string num;

        for (int j = 0; j < column; ++j)
        {
            if (isdigit(matrix[i][j]))
            {
                num += matrix[i][j];

                std::vector<std::pair<int, int>> coords;
                if (i - 1 >= 0)
                {
                    if (j - 1 >= 0)
                    {
                        coords.emplace_back(i - 1, j - 1);
                    }
                    if (j + 1 < column)
                    {
                        coords.emplace_back(i - 1, j + 1);
                    }
                    coords.emplace_back(i - 1, j);
                }
                if (i + 1 < row)
                {
                    if (j - 1 >= 0)
                    {
                        coords.emplace_back(i + 1, j - 1);
                    }
                    if (j + 1 < column)
                    {
                        coords.emplace_back(i + 1, j + 1);
                    }
                    coords.emplace_back(i + 1, j);
                }
                if (j - 1 >= 0)
                {
                    coords.emplace_back(i, j - 1);
                }

                if (j + 1 < column)
                {
                    coords.emplace_back(i, j + 1);
                }

                if (i - 1 >= 0)
                {
                    coords.emplace_back(i - 1, j);
                }

                if (i + 1 < row)
                {
                    coords.emplace_back(i + 1, j);
                }

                for (auto [i_coord, j_coord] : coords)
                {
                    if (is_special(matrix[i_coord][j_coord]))
                    {
                        std::cout << matrix[i][j] << ": " << matrix[i_coord][j_coord] << std::endl;
                        is_real = true;
                    }
                }
            }

            if (j == column - 1 || !isdigit(matrix[i][j]))
            {
                if (is_real && !num.empty())
                {
                    int actual_num = atoi(num.c_str());
                    //std::cout << actual_num << std::endl;
                    real_num_counter += actual_num;
                }
                num = "";
                is_real = false;
            }
        }
    }
    std::cout << real_num_counter << std::endl;
}

int main()
{
    part1();
}
