#ifndef HAND_HPP
#define HAND_HPP
#include <string>
#include <array>
struct Hand{
    void clearHand();
    void sortHand();
    void sortValues();
    void cardValuesAndSuits();
    void printHand();
    void handValue();
    std::string getDiscards();
    std::array<int, 5> cards;
    std::array<int, 5> values;
    std::array<std::string, 5> suits;
    std::array<std::string, 5> cardNames;
    int value = 0;
    std::string name = "";
    std::array<int, 5> highCards;
    std::array<std::string, 9> handValues = {"High card", "Pair", "Two pairs", "Three of a kind", 
    "Straight", "Flush", "Full house", "Four of a kind", "Straight flush"};

};
void getWinner(Hand& hand1, Hand& hand2);
#endif