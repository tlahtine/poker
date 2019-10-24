#include "hand.hpp"

void Hand::clearHand(){
    value = 0;
    cards.clear();
    for(int i = 0; i < 5; ++i){
        highCards[i] = 0;
    }
}
void Hand::sortHand(){ 
    std::sort(cards.rbegin(), cards.rend());
}
void Hand::saveHand(){
    std::string filename = "hands.txt";
    std::fstream stream;
    stream.open(filename, stream.app | stream.out);
    if(!stream.is_open()){
        std::cerr << "cannot open " << filename << "\n";
        return;
    }
    stream << wholeHand << "\n";
}
void Hand::setHand(){
    wholeHand = name + ": ";
    for(int i = 0; i < 5; i++){
        if(cards[i].first == 10){
            wholeHand +="T";
        }
        else if(cards[i].first == 11){
            wholeHand +="J";
        }
        else if(cards[i].first == 12){
            wholeHand +="Q";
        }
        else if(cards[i].first == 13){
            wholeHand +="K";
        }
        else if(cards[i].first == 14){
            wholeHand +="A";
        }
        else{
            wholeHand += std::to_string(cards[i].first);
        }
        wholeHand += cards[i].second + " ";
    }
    wholeHand += handValues[value];
}
void Hand::handValue(){
    std::unordered_map<int, int> valueCount;
    for(int i = 0; i < 5; ++i){
        valueCount[cards[i].first]++;
    }
    std::vector<std::pair<int, int>> val;
    for (const auto& value : valueCount){
        val.emplace_back(value.second, value.first);
    }
    sort(val.rbegin(), val.rend());
    for(int i = 0; i < val.size(); ++i){
        highCards[i] = val[i].second;
    }
    //straight flushes, flushes, straights and high cards
    if(val[0].first == 1){
        bool flush = true;
        for(int i = 1; i < 5; i++){
            if(cards[i].second != cards[0].second){
                flush = false;
                break;
            }
        }
        //flush
        if(flush){
            if(cards[0].first - cards[4].first == 4){
                value = 8; //straight flush
                return;
            }
            if(cards[0].first == 14 && cards[1].first == 5){
                highCards[0] = 5;
                value = 8; //straight flush
                return;
            }
            value = 5; //flush
            return;
        }
        else{
            if(cards[0].first - cards[4].first == 4){
                value = 4; //straight
                return;
            }
            if(cards[0].first == 14 && cards[1].first == 5){
                highCards[0] = 5;
                value = 4; //straight
                return;
            }
            value = 0; //high card
            return;
        }
    }
    //pairs and two pairs
    else if(val[0].first == 2){
        if(val[1].first == 2){
            value = 2; //two pairs
            return;
        }
        else{
            value = 1; //one pair
            return;
        }
    }
    //trips and full houses
    else if(val[0].first == 3){
        if(val[1].first == 2){
            value = 6; //full house
            return;
        }
        else{
            value = 3; //three of a kind
            return;
        }
    }
    //four of a kind
    else if(val[0].first == 4){
        value = 7; //four of a kind
        return;
    }
}
std::string Hand::getDiscards(){
    std::string discards = "";
    if(value == 7){ //quads
        for(int i = 0; i < 5; i++){
            if(cards[i].first != highCards[0]){
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 3){ //trips
        for(int i = 0; i < 5; i++){
            if(cards[i].first != highCards[0]){
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 2){ //two pairs
        for(int i = 0; i < 5; i++){
            if(cards[i].first == highCards[2]) {
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 1){ //one pair
        for(int i = 0; i < 5; i++){
            if(cards[i].first != highCards[0]){
                discards = discards + std::to_string(i + 1);
            }
        }
    }
    if(value == 0){ //high card
        std::vector<std::string> suits;
        for(const auto& c : cards){
            suits.emplace_back(c.second);
        }
        std::sort(suits.rbegin(), suits.rend());
        if(suits[0] == suits[3] || suits[1] == suits[4]){ //4 to flush
            for(int i = 0; i < cards.size(); ++i){
                if(cards[i].second != suits[2]){
                    discards = std::to_string(i);
                }
            }
        }
        else if(cards[0].first - cards[3].first == 3){ //4 to straight
            discards = "5";
        }
        else if(cards[1].first - cards[4].first == 3){ //4 to straight
            discards = "1";
        }
        else{ //no good draws
            if(highCards[0] < 10){
                discards = "12345";
            }
            else{
                discards = "2345";
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