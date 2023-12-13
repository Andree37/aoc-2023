#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::tuple<std::string, std::string, std::string> parseTree(const std::string& data)
{
    std::string rootStr, leftStr, rightStr;
    std::istringstream iss(data);

    std::getline(iss, rootStr, '=');
    rootStr.erase(std::remove_if(rootStr.begin(), rootStr.end(), isspace), rootStr.end());

    std::getline(iss, leftStr, ',');
    leftStr = leftStr.substr(leftStr.find('(') + 1);
    std::getline(iss, rightStr);
    rightStr = rightStr.substr(rightStr.find(' ') + 1);
    rightStr.pop_back();


    return {rootStr, leftStr, rightStr};
}

void part1()
{
    std::istringstream input(
    R"(LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ))");

    std::string paths;
    input >> paths;

    std::map<std::string, std::pair<std::string, std::string>> nodes;
    std::string token;

    while (getline(input, token, '\n'))
    {
        if (token.empty())
        {
            continue;
        }

        auto parsed = parseTree(token);
        nodes[std::get<0>(parsed)] = {std::get<1>(parsed), std::get<2>(parsed)};
    }


    std::string final_path = "ZZZ";
    std::string node_to_find = "AAA";
    int steps = 0;
    while (node_to_find != final_path)
    {
        if (char chosen_path = paths[steps % paths.size()]; chosen_path == 'L')
        {
            node_to_find = nodes[node_to_find].first;
        }
        else
        {
            node_to_find = nodes[node_to_find].second;
        }

        ++steps;
    }

    std::cout << steps << std::endl;
}


int main()
{
    part1();
}
