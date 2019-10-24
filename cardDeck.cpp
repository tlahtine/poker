#include "cardDeck.hpp"
#include <iostream>
#include <bits/stdc++.h> 
#include <string>
#include <cstring>
#include <algorithm>
#include <random>
#include <chrono>
void CardDeck::shuffleDeck(){
    cards.clear();
    std::array<std::string, 4> suit = {"s", "h", "d", "c"};
    for(int j = 0; j < 4; ++j){
        for(int i = 2; i <= 14; ++i){
            cards.emplace_back(i, suit[j]);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cards.begin(), cards.end(), std::default_random_engine(seed));
}
void CardDeck::dealHand(Hand& hand){
    hand.clearHand();
    for(int i = 0; i < 5; ++i){
        hand.cards.emplace_back(cards[i]);
    }
    cards.erase(cards.begin(), cards.begin() + 5);
    hand.sortHand();
    hand.handValue();
    hand.setHand();
}
void CardDeck::drawCards(Hand& hand, std::string str){
    std::set<int> setDiscards;
    std::vector<int> discards;
    for(int i = 0; i < str.size(); ++i){
        int d = int(str[i] - 48);
        if(d >= 1 && d <= 5){
            setDiscards.insert(d);
        }
    }
    for(int i : setDiscards){
        discards.emplace_back(i);
    }
    std::sort(discards.rbegin(), discards.rend());
    for(int i : discards){
        hand.cards.erase(hand.cards.begin() + (i - 1));
    }
    for(int i = 0; i < discards.size(); ++i){
        hand.cards.emplace_back(cards[i]);
    }
    cards.erase(cards.begin(), cards.begin() + discards.size());
    hand.sortHand();
    hand.handValue();
    hand.setHand();

}