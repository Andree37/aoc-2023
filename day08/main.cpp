#include <iostream>
#include <map>
#include <sstream>
#include <string>

unsigned long long gcd(const unsigned long long a, const unsigned long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

unsigned long long lcm(const unsigned long long a, const unsigned long long b)
{
    return a / gcd(a, b) * b;
}

unsigned long long findLCM(const std::vector<int>& nums)
{
    unsigned long long result = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        result = lcm(result, nums[i]);
    }
    return result;
}


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

void part2()
{
    std::istringstream input(
        R"(LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX))");

    std::string paths;
    input >> paths;

    std::map<std::string, std::pair<std::string, std::string>> nodes;
    std::vector<std::string> starting_node_keys;
    std::string token;

    while (getline(input, token, '\n'))
    {
        if (token.empty())
        {
            continue;
        }

        auto parsed = parseTree(token);
        nodes[std::get<0>(parsed)] = {std::get<1>(parsed), std::get<2>(parsed)};

        if (std::get<0>(parsed).at(2) == 'A')
        {
            starting_node_keys.push_back(std::get<0>(parsed));
        }
    }


    std::vector<int> found_nums;
    std::vector<std::string> found_nodes = starting_node_keys;

    for (const auto& n : found_nodes)
    {
        int steps = 0;

        std::string node_to_find = n;
        while (node_to_find.at(2) != 'Z')
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
        found_nums.push_back(steps);
    }

    unsigned long long total = findLCM(found_nums);
    std::cout << total << std::endl;
}


int main()
{
    part1();
    part2();
}
