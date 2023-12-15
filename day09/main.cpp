#include <iostream>
#include <map>
#include <sstream>
#include <string>

void part1()
{
    std::istringstream input(
        R"(0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45)");

    std::vector<std::vector<int64_t>> all_readings;

    std::string line;
    while (getline(input, line, '\n'))
    {
        std::vector<int64_t> line_steps;
        std::string token;
        std::istringstream line_stream(line);

        while (line_stream >> token)
        {
            line_steps.push_back(strtoll(token.c_str(), nullptr, 10));
        }

        all_readings.push_back(line_steps);
    }

    // compute the history
    int64_t total = 0;
    for (const auto& readings : all_readings)
    {
        std::vector<std::vector<int64_t>> history;
        history.push_back(readings);

        bool b_history = false;
        while (!b_history)
        {
            std::vector<int64_t> prev_history = history[history.size() - 1];
            std::vector<int64_t> current_history;
            int64_t reading = prev_history[0];
            for (int64_t i = 1; i < prev_history.size(); ++i)
            {
                int64_t reading_value = prev_history[i] - reading;
                current_history.push_back(reading_value);
                reading = prev_history[i];
            }
            history.push_back(current_history);

            b_history = std::all_of(current_history.begin(), current_history.end(), [](const int i) { return i == 0; });
        }

        // compute the next step in the history
        auto t = history[history.size() - 1];
        int64_t step = t[t.size() - 1];
        for (int64_t i = history.size() - 2; i >= 0; --i)
        {
            std::vector<int64_t> v = history[i];
            step += v[v.size() - 1];
        }
        std::cout << step << std::endl;
        total += step;
    }

    std::cout << total << std::endl;
}

void part2()
{
    std::istringstream input(
        R"(0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45)");

    std::vector<std::vector<int64_t>> all_readings;

    std::string line;
    while (getline(input, line, '\n'))
    {
        std::vector<int64_t> line_steps;
        std::string token;
        std::istringstream line_stream(line);

        while (line_stream >> token)
        {
            line_steps.push_back(strtoll(token.c_str(), nullptr, 10));
        }

        all_readings.push_back(line_steps);
    }

    // compute the history
    int64_t total = 0;
    for (const auto& readings : all_readings)
    {
        std::vector<std::vector<int64_t>> history;
        history.push_back(readings);

        bool b_history = false;
        while (!b_history)
        {
            std::vector<int64_t> prev_history = history[history.size() - 1];
            std::vector<int64_t> current_history;
            int64_t reading = prev_history[0];
            for (int64_t i = 1; i < prev_history.size(); ++i)
            {
                int64_t reading_value = prev_history[i] - reading;
                current_history.push_back(reading_value);
                reading = prev_history[i];
            }
            history.push_back(current_history);

            b_history = std::all_of(current_history.begin(), current_history.end(), [](const int i) { return i == 0; });
        }


        // compute the next step in the history
        auto t = history[history.size() - 1];
        int64_t step = t[0];
        for (int64_t i = history.size() - 2; i >= 0; --i)
        {
            std::vector<int64_t> v = history[i];
            step = v[0] - step;
        }
        std::cout << step << std::endl;
        total += step;
    }

    std::cout << total << std::endl;
}


int main()
{
    part1();
    part2();
}
