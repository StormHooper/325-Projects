// Author: Tyler Pham
// CECS 325-02
// Prog 1 - War
// Due 02/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>

class Deck
{
    public:
        Deck();
        Card deal();
        void display();
        void shuffle();

    private:
        std::vector<Card> mainDeck;
};

#endif
