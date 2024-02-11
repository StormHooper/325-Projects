// Author: Tyler Pham
// CECS 325-02
// Prog 1 - War
// Due 02/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "Card.h"
using namespace std;

Card::Card(char rank, char suit) : rank(rank), suit(suit) 
{
    switch(rank)
    {
        case('A'):
            value = 1;
            break;
        case('T'):
            value = 10;
            break;
        case('J'):
            value = 11;
            break;
        case('Q'):
            value = 12;
            break;
        case('K'):
            value = 13;
            break;
        default:
            value = static_cast<int>(rank) - 48;
            break;
    }
}

void Card::display() {
    if (rank == 'T')
    {
        cout << "10" << suit;
    }
    else
    {
        cout << rank << suit;
    }
}

int Card::compare(Card other) {
    if (value == other.value)
    {
        return 0;
    }
    else if (value > other.value)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
