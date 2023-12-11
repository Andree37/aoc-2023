#include <iostream>
#include <sstream>
#include <string>


void part1()
{
    std::istringstream input(
        R"(Time:      7  15   30
Distance:  9  40  200)");

    std::vector<int> times;
    std::vector<int> distances;
    std::string token;

    std::string time_line;
    getline(input, time_line, '\n');
    std::stringstream time_stream(time_line);
    time_stream >> token;
    while (time_stream >> token)
    {
        times.push_back(atoi(token.c_str()));
    }

    std::string distance_line;
    getline(input, distance_line, '\n');
    std::stringstream distance_stream(distance_line);
    distance_stream >> token;
    while (distance_stream >> token)
    {
        distances.push_back(atoi(token.c_str()));
    }


    int total_wins = 1;
    for (int i = 0; i < times.size(); ++i)
    {
        int ways_to_win = 0;
        for (int t = 0; t < times[i]; ++t)
        {
            if (t * (times[i] - t) > distances[i])
            {
                ++ways_to_win;
            }
        }
        std::cout << ways_to_win << std::endl;
        total_wins *= ways_to_win;
    }

    std::cout << total_wins << std::endl;
}


void part2()
{
    std::istringstream input(
        R"(Time:      7  15   30
Distance:  9  40  200)");

    std::string token;
    std::string time_string;
    std::string distance_string;

    std::string time_line;
    getline(input, time_line, '\n');
    std::stringstream time_stream(time_line);
    time_stream >> token;
    while (time_stream >> token)
    {
        time_string += token;
    }

    long time = strtol(time_string.c_str(), nullptr, 10);

    std::string distance_line;
    getline(input, distance_line, '\n');
    std::stringstream distance_stream(distance_line);
    distance_stream >> token;
    while (distance_stream >> token)
    {
        distance_string += token;
    }

    long distance = strtol(distance_string.c_str(), nullptr, 10);

    int total_wins = 1;
    int ways_to_win = 0;
    for (long t = 0; t < time; ++t)
    {
        if (t * (time - t) > distance)
        {
            ++ways_to_win;
        }
    }
    total_wins *= ways_to_win;

    std::cout << total_wins << std::endl;
}


int main()
{
    part1();
    part2();
}
