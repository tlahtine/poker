#ifndef HAND_HPP
#define HAND_HPP
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h> 
#include <unordered_map>

struct Hand{
    void clearHand();
    void sortHand();
    void setHand();
    void saveHand();
    void handValue();
    std::string getDiscards();
    std::vector<std::pair<int, std::string>> cards;
    std::string wholeHand = "";
    int value = 0;
    std::string name = "";
    std::array<int, 5> highCards;
    std::array<std::string, 9> handValues = {"High card", "Pair", "Two pairs", "Three of a kind", 
    "Straight", "Flush", "Full house", "Four of a kind", "Straight flush"};
};
void getWinner(Hand& hand1, Hand& hand2);
#endif