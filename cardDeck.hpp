#ifndef CARDDECK_HPP
#define CARDDECK_HPP
#include <array>
#include <vector>
#include "hand.hpp"
struct CardDeck{
    void shuffleDeck();
    void dealHand(Hand& hand);
    void drawCards(Hand& hand, std::string discards);
    std::vector<std::pair<int, std::string>> cards;
};
#endif