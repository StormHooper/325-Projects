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
        char rank;
        char suit;

    public:
        Card(char suit='X', char rank='X'): suit(suit), rank(rank)
        {}

        void display()
        {
            if (rank == 'T')
                cout << "10" << suit;
            else
                cout << rank << suit;
        }

        int compare(Card other)
        {
            char order[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
            int cardIndex, otherIndex = 0;

            for (int i = 0; i < 13; i++)
            {
                if (rank == order[i])
                {
                    cardIndex = i;
                }
                if (other.rank == order[i])
                {
                    otherIndex = i;
                }
            }
            return (cardIndex > otherIndex) ? 1 : (cardIndex < otherIndex) ? -1 : 0;
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
            ++index;
            return mainDeck[index-1];
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
    int rounds;
    int pointsP1 {0};
    int pointsP2 {0};
    int ties {0};
    
    // Get player names and number of rounds.
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;
    cout << "How many games will they play? ";
    cin >> rounds;
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
    for (int round = 1; round <= rounds; round++)
    {
        Card cardP1 {};
        Card cardP2 {};

        try
        {
            cardP1 = deck.deal();
            cardP2 = deck.deal();
        }
        catch(const char* error)
        {
            cout << error;
            break;
        }
        
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
