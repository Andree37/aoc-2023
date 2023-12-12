#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::vector card_order = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
std::vector card_order_joker = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

bool poker_rank(const std::tuple<std::string, long, long>& q, const std::tuple<std::string, long, long>& p)
{
    return std::get<2>(p) < std::get<2>(q);
}

bool poker_joker_rank(const std::tuple<std::string, long, long, char, std::string>& q,
                      const std::tuple<std::string, long, long, char, std::string>& p)
{
    return std::get<2>(p) < std::get<2>(q);
}

bool hand_rank(const std::tuple<std::string, long, long>& q, const std::tuple<std::string, long, long>& p)
{
    if (std::get<2>(p) == std::get<2>(q))
    {
        long p_index = 0;
        long q_index = 0;
        const auto p_elem = std::get<0>(p);
        const auto q_elem = std::get<0>(q);
        for (auto i = 0; i < p_elem.size(); i++)
        {
            if (p_elem[i] == q_elem[i])
            {
                continue;
            }

            // If element was found
            if (const auto it = std::find(card_order.begin(), card_order.end(), p_elem[i]); it != card_order.end())
            {
                p_index = it - card_order.begin();
            }

            if (const auto it = std::find(card_order.begin(), card_order.end(), q_elem[i]); it != card_order.end())
            {
                q_index = it - card_order.begin();
            }

            return q_index > p_index;
        }
    }

    return std::get<2>(p) > std::get<2>(q);
}

bool hand_rank_joker(const std::tuple<std::string, long, long, char, std::string>& q,
                     const std::tuple<std::string, long, long, char, std::string>& p)
{
    if (std::get<2>(p) == std::get<2>(q))
    {
        long p_index = 0;
        long q_index = 0;
        const auto p_elem = std::get<4>(p);
        const auto q_elem = std::get<4>(q);
        for (auto i = 0; i < p_elem.size(); i++)
        {
            if (p_elem[i] == q_elem[i])
            {
                continue;
            }

            // If element was found
            if (const auto it = std::find(card_order_joker.begin(), card_order_joker.end(), p_elem[i]); it !=
                card_order_joker.end())
            {
                p_index = it - card_order_joker.begin();
            }

            if (const auto it = std::find(card_order_joker.begin(), card_order_joker.end(), q_elem[i]); it !=
                card_order_joker
                .end())
            {
                q_index = it - card_order_joker.begin();
            }

            return q_index > p_index;
        }
    }

    return std::get<2>(p) > std::get<2>(q);
}

void part1()
{
    std::istringstream input(
        R"(32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483)");

    std::string line;
    std::vector<std::tuple<std::string, long, long>> hands;

    while (getline(input, line, '\n'))
    {
        std::stringstream line_stream(line);
        std::string poker_hand;
        std::string value_str;
        line_stream >> poker_hand;
        line_stream >> value_str;

        hands.emplace_back(poker_hand, strtol(value_str.c_str(), nullptr, 10), 0);
    }

    // poker rank, add to the pair as the last value to later sort by it
    for (auto& [hand, _, rank] : hands)
    {
        std::map<char, long> card_count;
        for (auto c : hand)
        {
            card_count[c] += 1;
        }

        for (auto [card, count] : card_count)
        {
            // full house
            if (rank == 3 && count == 2)
            {
                rank = 4;
                break;
            }
            if (rank == 1 & count == 3)
            {
                rank = 4;
                break;
            }

            // two pairs
            if (rank == 1 && count == 2)
            {
                rank = 2;
                break;
            }

            // five or four of a kind
            if (count >= 4)
            {
                rank = count + 1;
                break;
            }

            // three of a kind
            if (count == 3)
            {
                rank = 3;
            }
            // one pair
            else if (count == 2)
            {
                rank = 1;
            }
        }
    }

    // sort the hands based on the poker ranking
    std::sort(hands.begin(), hands.end(), poker_rank);
    std::sort(hands.begin(), hands.end(), hand_rank);


    long total = 0;
    for (int i = 0; i < hands.size(); ++i)
    {
        std::cout << std::get<0>(hands[i]) << " " << std::get<1>(hands[i]) << " " << std::get<2>(hands[i]) << " " << i +
            1 << std::endl;
        total += std::get<1>(hands[i]) * (i + 1);
    }

    std::cout << total;
}

void part2()
{
    std::istringstream input(
        R"(32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483)");

    std::string line;
    std::vector<std::tuple<std::string, long, long, char, std::string>> hands;

    while (getline(input, line, '\n'))
    {
        std::stringstream line_stream(line);
        std::string poker_hand;
        std::string value_str;
        line_stream >> poker_hand;
        line_stream >> value_str;

        hands.emplace_back(poker_hand, strtol(value_str.c_str(), nullptr, 10), 0, '0', "");
    }

    // poker rank, add to the pair as the last value to later sort by it
    for (auto& [hand, _, rank, winning, winning_hand] : hands)
    {
        std::map<char, long> card_count;
        for (auto c : hand)
        {
            card_count[c] += 1;
        }

        for (auto [card, count] : card_count)
        {
            if (card == 'J')
            {
                continue;
            }
            // full house
            if (rank == 3 && count == 2)
            {
                rank = 4;
                winning = card;
                winning_hand = hand;
                break;
            }
            if (rank == 1 & count == 3)
            {
                rank = 4;
                winning = card;
                winning_hand = hand;
                break;
            }

            // two pairs
            if (rank == 1 && count == 2)
            {
                rank = 2;
                winning = card;
                winning_hand = hand;
                break;
            }

            // five or four of a kind
            if (count >= 4)
            {
                rank = count + 1;
                winning = card;
                winning_hand = hand;
                break;
            }

            // three of a kind
            if (count == 3)
            {
                rank = 3;
                winning = card;
                winning_hand = hand;
            }
            // one pair
            else if (count == 2)
            {
                rank = 1;
                winning = card;
                winning_hand = hand;
            }
            else if (count == 1 && rank == 0)
            {
                rank = 0;
                winning = card;
                winning_hand = hand;
            }
        }
    }

    // jokerizing
    for (auto& [hand, _, rank, winning, winning_hand] : hands)
    {
        for (auto& c : hand)
        {
            if (c == 'J')
            {
                c = winning;
            }
        }

        std::cout << "after jokerizing: " << hand << " with winning: " << winning << std::endl;
        rank = 0;

        std::map<char, long> card_count;
        for (auto c : hand)
        {
            card_count[c] += 1;
        }

        for (auto [card, count] : card_count)
        {
            // full house
            if (rank == 3 && count == 2)
            {
                rank = 4;
                break;
            }
            if (rank == 1 & count == 3)
            {
                rank = 4;
                break;
            }

            // two pairs
            if (rank == 1 && count == 2)
            {
                rank = 2;
                break;
            }

            // five or four of a kind
            if (count >= 4)
            {
                rank = count + 1;
                break;
            }

            // three of a kind
            if (count == 3)
            {
                rank = 3;
            }
            // one pair
            else if (count == 2)
            {
                rank = 1;
            }
        }
        if (winning_hand.empty())
        {
            winning_hand = "JJJJJ";
        }
    }

    // sort the hands based on the poker ranking
    std::sort(hands.begin(), hands.end(), poker_joker_rank);
    std::sort(hands.begin(), hands.end(), hand_rank_joker);


    long total = 0;
    for (int i = 0; i < hands.size(); ++i)
    {
        std::cout << std::get<4>(hands[i]) << " " << std::get<1>(hands[i]) << " " << std::get<2>(hands[i]) << " " << i +
            1 << " " << std::get<0>(hands[i]) << std::endl;
        total += std::get<1>(hands[i]) * (i + 1);
    }

    std::cout << total;
}


int main()
{
    //part1();
    std::cout << std::endl;
    part2();
}
