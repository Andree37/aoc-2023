#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <cctype>

bool first(const std::tuple<long, long, long, long>& p,
           const std::tuple<long, long, long, long>& q)
{
    return std::get<0>(p) < std::get<0>(q);
}

bool first_reversed(const std::tuple<long, long, long, long>& p,
                    const std::tuple<long, long, long, long>& q)
{
    return std::get<0>(q) < std::get<0>(p);
}

void part1()
{
    std::istringstream input(
        R"(seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4)");
    std::vector<long> seeds;
    std::map<long, std::vector<std::string>> filters;

    std::string line;
    getline(input, line, '\n');

    std::stringstream line_stream(line);
    std::string token;


    line_stream >> token;
    while (line_stream >> token)
    {
        seeds.push_back(strtol(token.c_str(), nullptr, 10));
    }

    long current_filter = -1;
    while (getline(input, line, '\n'))
    {
        if (line.empty())
        {
            continue;
        }

        if (!isdigit(line[0]))
        {
            // get the next filter step
            current_filter++;
            continue;
        }

        filters[current_filter].push_back(line);
    }


    // for each filter step, construct the filter mappings
    std::vector<std::tuple<long, long, long, long>> mappings;

    for (auto [key, values] : filters)
    {
        for (const auto& v : values)
        {
            std::stringstream v_stream(v);
            std::string target;
            std::string source;
            std::string amount;

            v_stream >> target;
            v_stream >> source;
            v_stream >> amount;


            long target_value = strtol(target.c_str(), nullptr, 10);
            long source_value = strtol(source.c_str(), nullptr, 10);
            long amount_value = strtol(amount.c_str(), nullptr, 10);


            mappings.emplace_back(key, source_value, target_value, amount_value);
        }
    }


    // sort the mappings based on the key
    std::sort(mappings.begin(), mappings.end(), first);

    // do the passings from each filter and get the lowest pass
    long min_pass = LONG_MAX;
    for (auto seed : seeds)
    {
        long passes = seed;
        for (int i = 0; i < filters.size(); ++i)
        {
            for (auto [key, source, target, amount] : mappings)
            {
                if (key == i)
                {
                    if (source <= passes && passes <= source + amount)
                    {
                        long diff = passes - source;
                        passes = target + diff;
                        break;
                    }
                }
            }
        }

        if (passes < min_pass)
        {
            min_pass = passes;
        }
    }

    std::cout << "result: " << min_pass << std::endl;
}

//

void part2()
{
    std::istringstream input(
        R"(seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4)");
    std::vector<std::pair<long, long>> seeds;
    std::map<long, std::vector<std::string>> filters;

    std::string line;
    getline(input, line, '\n');

    std::stringstream line_stream(line);
    std::string token;


    line_stream >> token;
    while (line_stream >> token)
    {
        std::string range;
        line_stream >> range;

        seeds.emplace_back(strtol(token.c_str(), nullptr, 10), strtol(range.c_str(), nullptr, 10));
    }

    long current_filter = -1;
    while (getline(input, line, '\n'))
    {
        if (line.empty())
        {
            continue;
        }

        if (!isdigit(line[0]))
        {
            // get the next filter step
            current_filter++;
            continue;
        }

        filters[current_filter].push_back(line);
    }


    // for each filter step, construct the filter mappings
    std::vector<std::tuple<long, long, long, long>> mappings;

    for (auto [key, values] : filters)
    {
        for (const auto& v : values)
        {
            std::stringstream v_stream(v);
            std::string target;
            std::string source;
            std::string amount;

            v_stream >> target;
            v_stream >> source;
            v_stream >> amount;


            long target_value = strtol(target.c_str(), nullptr, 10);
            long source_value = strtol(source.c_str(), nullptr, 10);
            long amount_value = strtol(amount.c_str(), nullptr, 10);


            mappings.emplace_back(key, source_value, target_value, amount_value);
        }
    }


    // sort the mappings based on the key
    std::sort(mappings.begin(), mappings.end(), first_reversed);

    // do the passings from each filter and get the lowest pass
    long found_location = 0;
    long location = 0;

    while (found_location == 0)
    {
        long passes = ++location;
        for (int i = filters.size(); i >= 0; --i)
        {
            for (auto [key, source, target, amount] : mappings)
            {
                if (key == i)
                {
                    if (target <= passes && passes <= target + amount)
                    {
                        long diff = passes - target;
                        passes = source + diff;
                        break;
                    }
                }
            }
        }

        // if there is a seed with this location
        for (auto [seed, range] : seeds)
        {
            if (passes >= seed && passes <= seed + range)
            {
                found_location = location - 1;
            }
        }
    }


    std::cout << "result: " << found_location << std::endl;
}


int main()
{
    part1();
    part2();
}
