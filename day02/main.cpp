#include <iostream>
#include <map>
#include <sstream>
#include <string>


void part1()
{
    std::istringstream input(R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)");

    std::string line;
    size_t game_counter = 0;
    size_t sum_good_game_ids;

    // max number of cubes
    std::map<std::string, long> max_cubes = {{"red", 12}, {"green", 13}, {"blue", 14}};

    while (getline(input, line, '\n'))
    {
        ++game_counter;
        std::string game_line = line.erase(0, line.find(':'));

        std::vector<std::string> hands;

        size_t prev_hand_pos = 0;
        size_t hand_pos = game_line.find(';', 0);
        while (hand_pos != std::string::npos)
        {
            hands.push_back(game_line.substr(prev_hand_pos, hand_pos - prev_hand_pos));
            prev_hand_pos = hand_pos;
            hand_pos = game_line.find(';', hand_pos + 1);
        }
        hands.push_back(game_line.substr(prev_hand_pos, game_line.length()));

        bool found_bad_hand = false;
        for (const std::string& hand : hands)
        {
            std::stringstream hand_stream(hand);
            std::string token;

            while (hand_stream >> token)
            {
                char* p;
                long pull = strtol(token.c_str(), &p, 10);
                if (!*p)
                {
                    // the color
                    hand_stream >> token;
                    token.erase(std::remove(token.begin(), token.end(), ','), token.end());
                    if (max_cubes[token] < pull)
                    {
                        std::cout << game_counter << std::endl;
                        found_bad_hand = true;
                        break;
                    }
                }
            }
        }
        if (!found_bad_hand)
        {
            sum_good_game_ids += game_counter;
        }
    }
    std::cout << "good id count: " << sum_good_game_ids;
}

void part2()
{
    std::istringstream input(R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)");

    std::string line;
    size_t game_counter = 0;

    long count_cubes = 0;

    while (getline(input, line, '\n'))
    {
        std::map<std::string, long> cubes = {{"red", 1}, {"green", 1}, {"blue", 1}};

        ++game_counter;
        std::string game_line = line.erase(0, line.find(':'));

        std::vector<std::string> hands;

        size_t prev_hand_pos = 0;
        size_t hand_pos = game_line.find(';', 0);
        while (hand_pos != std::string::npos)
        {
            hands.push_back(game_line.substr(prev_hand_pos, hand_pos - prev_hand_pos));
            prev_hand_pos = hand_pos;
            hand_pos = game_line.find(';', hand_pos + 1);
        }
        hands.push_back(game_line.substr(prev_hand_pos, game_line.length()));

        for (const std::string& hand : hands)
        {
            std::stringstream hand_stream(hand);
            std::string token;

            while (hand_stream >> token)
            {
                char* p;
                long pull = strtol(token.c_str(), &p, 10);
                if (!*p)
                {
                    // the color
                    hand_stream >> token;
                    token.erase(std::remove(token.begin(), token.end(), ','), token.end());

                    if (cubes[token] == 1 || cubes[token] < pull)
                    {
                        cubes[token] = pull;
                    }
                }
            }
        }

        count_cubes += cubes["red"] * cubes["green"] * cubes["blue"];
    }
    std::cout << count_cubes;
}


int main()
{
    part2();
}
