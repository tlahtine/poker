#ifndef CARDDECK_HPP
#define CARDDECK_HPP
#include <array>
#include "hand.hpp"
struct CardDeck{
    void newDeck();
    void shuffleDeck();
    void dealHand(Hand& hand);
    void drawCards(Hand& hand, std::string discards);
    std::array<int, 52> cards;
};
#endif