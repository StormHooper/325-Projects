// Author: Tyler Pham
// CECS 325-02
// Prog 1 - War
// Due 02/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "Card.h"
#include "Deck.h"
using namespace std;

int main() {
    // Declare players, player points and ties, and number of rounds.
    string player1;
    string player2;
    int pointsP1 {0};
    int pointsP2 {0};
    int ties {0};

    // Get player names.
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;
    cout << "\n";

    // Constructs and displays deck pre- and post-shuffle.
    Deck deck;
    cout << "Original Deck \n";
    deck.display();
    cout << '\n';
    deck.shuffle();
    cout << "Shuffled Deck \n";
    deck.display();
    cout << '\n';

    // It's time to d-d-d-d-d-d-d-d-d-d-duel!
    for (int round = 1; round <= 26; round++)
    {
        Card cardP1 {deck.deal()};
        Card cardP2 {deck.deal()};

        cout << "Game " << round << '\n' << "--------\n\t" << player1 << "=>";
        cardP1.display();
        cout << "\n\t" << player2 << "=>";
        cardP2.display();
        cout << '\n';

        int winner = cardP1.compare(cardP2);
        if (winner == 1)
        {
            cout << player1 << "=> Winner\n" << endl;
            pointsP1++;
        }
        else if (winner == -1)
        {
            cout << player2 << "=> Winner\n" << endl;
            pointsP2++;
        }
        else
        {
            cout << "Tie game\n" << endl;
            ties++;
        }
    }
    
    // Final results.
    cout << "------Final Stats------\n\t" << 
    player1 << " vs. " << player2 <<
    "\nWins\t" << pointsP1 << '\t' << pointsP2 <<
    "\nLosses\t" << pointsP2 << '\t' << pointsP1 <<
    "\nTies\t" << ties << '\t' << ties << endl;
}
