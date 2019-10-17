#include "cardDeck.hpp"
#include <iostream>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include <random>
#include <chrono>
void CardDeck::newDeck(){
    for(int i = 2; i <= 53; i++){
        cards[i - 2] = i;
    }
}
void CardDeck::shuffleDeck(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cards.begin(), cards.end(), std::default_random_engine(seed));
}
void CardDeck::dealHand(Hand& hand){
    int count = 0;
    for(int i = 0; count < 5; i++){
        if(cards[i] != 0){
            hand.cards[count] = cards[i];
            cards[i] = 0;
            count++;
        }
    }
    hand.sortHand();
    hand.cardValuesAndSuits();
    hand.sortValues();
    hand.handValue();
}
void CardDeck::drawCards(Hand& hand, std::string discards){
    int cardCount = discards.size();
    int * card;
    card = new (std::nothrow) int[cardCount];
    for(int i = 0; i < cardCount; i++){
        card[i] = int(discards[i]) - 48;
        for(int j = 0; j < 52; j++){
            if(cards[j] != 0){
                hand.cards[card[i] - 1] = cards[j];
                cards[j] = 0;
                break;
            }
        }
    }
    hand.sortHand();
    hand.cardValuesAndSuits();
    hand.sortValues();
    hand.handValue();

}