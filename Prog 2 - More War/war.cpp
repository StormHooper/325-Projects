// Author: Tyler Pham
// CECS 325-02
// Prog 2 - More War
// Due 02/27/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card
{
    private:
        char rank {};
        char suit {};
        int value {};

    public:
        Card(char suit='X', char rank='X') : suit {suit}, rank {rank}
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

        void display()
        {
            if (rank == 'T')
                cout << "10" << suit;
            else
                cout << rank << suit;
        }

        int compare(Card other)
        {
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
};

class Deck
{
    private:
        Card mainDeck[52];
        size_t index {0};
    public:
        Deck()
        {
            int i {0};
            for (char suit: {'C', 'S', 'D', 'H'})
            {
                for (char rank:{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'})
                    mainDeck[i++] = Card(suit, rank);
            }
        }

        Card deal()
        {
            if (isEmpty())
                throw("Error - Deck is empty\n");
            return mainDeck[index];
        }

        void display()
        {
            for (size_t i {0}; i < sizeof(mainDeck) / sizeof(mainDeck[0]); ++i)
            {
                mainDeck[i].display();
                if ((i+1) % 13)
                    cout << ", ";
                else
                    cout << "\n";
            }
        }

        void shuffle()
        {
            srand(time(0));
            int j {};
            for (size_t i {0}; i < sizeof(mainDeck) / sizeof(mainDeck[0]); ++i)
            {
                j = rand() % (sizeof(mainDeck) / sizeof(mainDeck[0]));
                Card temp {mainDeck[j]};
                mainDeck[j] = mainDeck[i];
                mainDeck[i] = temp;
            }
        }

        bool isEmpty()
        {
            return index > sizeof(mainDeck) / sizeof(mainDeck[0]);
        }
};

int main() {
    // Construct deck, players, player points and ties.
    Deck deck;
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
