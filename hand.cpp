#include <iostream>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include "hand.hpp"
void Hand::clearHand(){
    value = 0;
    for(int i = 0; i < 5; ++i){
        cards[i] = 0;
        values[i] = 0;
        highCards[i] = 0;
    }
}
void Hand::sortHand(){
    std::sort(cards.begin(), cards.end());
}
void Hand::sortValues(){
    std::sort(values.rbegin(), values.rend()); //sort values descending
}
void Hand::cardValuesAndSuits(){
    for(int i = 0; i < 5; i++){
        if(cards[i] >= 2 && cards[i] <= 14){
            values[i] = cards[i];
            suits[i] = "s";
        }
        if(cards[i] >= 15 && cards[i] <= 27){
            values[i] = cards[i] - 13;
            suits[i] = "h";
        }
        if(cards[i] >= 28 && cards[i] <= 40){
            values[i] = cards[i] - 26;
            suits[i] = "d";
        }
        if(cards[i] >= 41 && cards[i] <= 53){
            values[i] = cards[i] - 39;
            suits[i] = "c";
        }
        if(values[i] == 10){
            cardNames[i] = "T" + suits[i];
        }
        else if(values[i] == 11){
            cardNames[i] = "J" + suits[i];
        }
        else if(values[i] == 12){
            cardNames[i] = "Q" + suits[i];
        }
        else if(values[i] == 13){
            cardNames[i] = "K" + suits[i];
        }
        else if(values[i] == 14){
            cardNames[i] = "A" + suits[i];
        }
        else{
            cardNames[i] = std::to_string(values[i]) + suits[i];
        }
    }
}
void Hand::printHand(){
    std::cout << name << ": ";
    for(int i = 0; i < 5; i++){
        std::cout << cardNames[i] << " ";
    }
    std::cout << handValues[value] << "\n";

}
void Hand::handValue(){
    //flush and straigh flush
    if(suits[0] == suits[4]){
        if(values[0] - values[4] == 4){
            highCards[0] = values[0];
            value = 8; //straight flush
            return;
        }
        if(values[0] == 14 && values[1] == 5){
            highCards[0] = 5;
            value = 8; //straight flush
            return;
        }
        for(int i = 0; i < 5; i++){
            highCards[i] = values[i];
        }
        value = 5; //flush
        return;
    }
    //pairs, two pairs, trips, full houses and quads
    int pairs = 0;
    for(int i = 1; i < 5; i++){
        if(values[i] == values[i - 1]){
            ++pairs;
        }
    }
    //straight or high card
    if(pairs == 0){
        if(values[0] - values[4] == 4){
            highCards[0] = values[0];
            value = 4; //straight
            return;
        }
        if(values[4] == 14 && values[3] == 5){
            highCards[0] = 5;
            value = 4; //straight
            return;
        }
        for(int i = 0; i < 5; i++){
            highCards[i] = values[i];
        }
        value = 0; //high card
        return;
    }
    //one pair
    if(pairs == 1){
        for(int i = 1; i < 5; i++){
            if(values[i] == values[i - 1]){
                highCards[0] = values[i];
            }
            else{
                highCards[i] = values[i - 1];
            }
        }
        value = 1; //one pair
        return;
    }
    //two pairs or trips
    if(pairs == 2){
        if(values[0] == values[2] || values[1] == values[3] || values[2] == values[4]){
            highCards[0] = values[2];
            value = 3; //trips
            return;
        }
        highCards[0] = values[1];
        highCards[1] = values[3];
        if(values[0] != values[1]){
            highCards[2] = values[0];
        }
        else if(values[1] != values[2]){
            highCards[2] = values[2];
        }
        else if(values[3] != values[4]){
            highCards[2] = values[4];
        }
        value = 2; //two pairs
        return;
    }
    //full house or quads
    if(pairs == 3){
        highCards[0] = values[2];
        if(values[0] == values[3] || values[1] == values[4]){
            value = 7; //quads
            return;
        }
        value = 6; //full house
        return;
    }
}
std::string Hand::getDiscards(){
    std::string discards = "";
    if(value == 3){
        for(int i = 0; i < 5; i++){
            if(cards[i] != values[2] || cards[i] != values[2] + 13 
            || cards[i] != values[2] + 26 || cards[i] != values[2] + 39){
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 2){
        for(int i = 0; i < 5; i++){
            if((cards[i] != values[1] && cards[i] != values[3]) || 
            (cards[i] != values[1] + 13 && cards[i] != values[3] + 13) ||
            (cards[i] != values[1] + 26 && cards[i] != values[3] + 26) ||
            (cards[i] != values[1] + 39 && cards[i] != values[3] + 39)) {
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 1){
        for(int i = 0; i < 5; i++){
            if(cards[i] != highCards[0] && cards[i] != highCards[0] + 13 &&
            cards[i] != highCards[0] + 26 && cards[i] != highCards[0] + 39){
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 0){
        if(suits[0] == suits[3]){
            discards = "5";
        }
        else if(suits[1] == suits[4]){
            discards = "1";
        }
        else if(values[4] - values[1] == 3){
            for(int i = 0; i < 5; i++){
                if(cards[i] == values[0] || cards[i] == values[0] + 13 || cards[i] == values[0] + 26 || cards[i] == values[0] + 39){
                    discards = std::to_string(i + 1);
                }
            }
        }
        else if(values[3] - values[0] == 3){
            for(int i = 0; i < 5; i++){
                if(cards[i] == values[4] || cards[i] == values[4] + 13 || cards[i] == values[4] + 26 || cards[i] == values[4] + 39){
                    discards = std::to_string(i + 1);
                }
            }
        }
        else{
            for(int i = 0; i < 5; i++){
                if(cards[i] != highCards[0] && cards[i] != highCards[0] + 13 &&
                cards[i] != highCards[0] + 26 && cards[i] != highCards[0] + 39){
                    discards = discards + std::to_string(i + 1);
                }
            }
        }
    }
    return discards;
}
void getWinner(Hand& playerHand, Hand& computerHand){
    int winner = 0;
    if(playerHand.value > computerHand.value){
        winner = 1;
    }
    else if(playerHand.value < computerHand.value){
        winner = 2;
    }
    else{
        for(int i = 0; i < 5; i++){
            if(playerHand.highCards[i] > computerHand.highCards[i]){
                winner = 1;
                break;
            }
            else if(playerHand.highCards[i] < computerHand.highCards[i]){
                winner = 2;
                break;
            }
        }
    }
    if(winner == 1){
        std::cout << playerHand.name << " wins!\n";
    }
    else if(winner == 2){
        std::cout << computerHand.name << " wins!\n";
    }
    else{
        std::cout << "It's a tie!\n";
    }

}