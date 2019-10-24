#include <iostream>
#include <string>
#include "hand.hpp"
#include "cardDeck.hpp"
int newGame(Hand& playerHand, Hand& computerHand){
    system("clear");
    CardDeck deck;
    deck.shuffleDeck();
    deck.dealHand(playerHand);
    deck.dealHand(computerHand);
    std::cout << playerHand.wholeHand << "\n";
    std::string discards = "";
    std::cout << "Discards (e.g. 124 or 0 to stand pat): ";
    std::cin >> discards;
    if(discards != "0"){
        deck.drawCards(playerHand, discards);
        std::cout << playerHand.wholeHand << "\n";
    }
    playerHand.saveHand();
    std::cout << computerHand.wholeHand << "\n";
    discards = computerHand.getDiscards();
    std::cout << "Computer discards " << discards << "\n";
    if(discards != ""){
        deck.drawCards(computerHand, discards);
        std::cout << computerHand.wholeHand << "\n";
    }
    computerHand.saveHand();
    getWinner(playerHand, computerHand);
    std::cout << "New game? (y/n): ";
    char c;
    std::cin >> c;
    if(c == 'y'){
        newGame(playerHand, computerHand);
    }
}
int main(){
    system("clear");
    Hand playerHand;
    Hand computerHand;
    std::cout << "Player name: ";
    std::cin >> playerHand.name;
    computerHand.name = "Computer";
    newGame(playerHand, computerHand);
}