// Author: Tyler Pham
// CECS 325-02
// Prog 1 - War
// Due 02/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Deck.h"

Deck::Deck()
{
    for (char suit: {'C', 'S', 'D', 'H'})
    {
        for (char rank: {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'})
            mainDeck.push_back(Card(rank, suit));
    }
}

Card Deck::deal()
{
    Card top = mainDeck[0];
    mainDeck.erase(mainDeck.begin());
    return top;
}

void Deck::display()
{
    int counter {0};
    for (Card& card: mainDeck)
    {
        counter++;
        card.display();
        if (counter % 13)
            std::cout << ", ";
        else
            std::cout << '\n';
    }
}

void Deck::shuffle()
{
    std::srand(std::time(0));
    int j {};
    for (std::size_t i {0}; i < mainDeck.size(); ++i)
    {
        j = std::rand() % mainDeck.size();
        Card temp {mainDeck[j]};
        mainDeck[j] = mainDeck[i];
        mainDeck[i] = temp;
    }
}
