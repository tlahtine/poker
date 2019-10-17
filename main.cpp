#include <iostream>
#include <string>
#include "hand.hpp"
#include "cardDeck.hpp"
int newGame(){
    system("clear");
    Hand playerHand;
    Hand computerHand;
    std::cout << "Player name: ";
    std::cin >> playerHand.name;
    computerHand.name = "Computer";
    CardDeck deck1;
    deck1.newDeck();
    deck1.shuffleDeck();
    playerHand.clearHand();
    computerHand.clearHand();
    deck1.dealHand(playerHand);
    deck1.dealHand(computerHand);
    playerHand.printHand();
    std::string discards = "";
    std::cout << "Discards (e.g. 124 or 0 to stand pat): ";
    std::cin >> discards;
    if(discards != "0"){
        deck1.drawCards(playerHand, discards);
        playerHand.printHand();
    }
    computerHand.printHand();
    discards = computerHand.getDiscards();
    std::cout << "Computer discards " << discards << "\n";
    if(discards != ""){
        deck1.drawCards(computerHand, discards);
        computerHand.printHand();

    }
    getWinner(playerHand, computerHand);
    std::cout << "New game? (y/n): ";
    char c;
    std::cin >> c;
    if(c == 'y'){
        newGame();
    }
}
int main(){
    newGame();
    return 0;
}