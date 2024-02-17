#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std; 

// defines enumeration for each suit 
enum Suit {CLUBS, SPADES, DIAMONDS, HEARTS};

class Card
// defines class for a single playing card 
{
    public:
        Card(); // default constructor 
        Card(int rank, Suit suit);  // constructor w/ parameters
        int GetRank() const;        // getter for card rank 
        int GetSuit() const;        // getter for card suit 
 
        void Print() const;         // prints card to user 
         
    private:
        int rank;   // rank of card
        Suit suit;  // suit of card
};

class Hand
// defines a class for a blackjack hand 
{
    public:
        Hand(); // default constructor 
        void SetCard(const Card& c, const int itemNumber);  // puts a card in a hand  
        Card GetCard(const int itemNumber) const;           // gets a card from a hand 
        int Total();        // returns total of hand 
        void Reset();       // resets hand 
    private:
        Card hand[11];      // array of card objects (11 = max possible cards in blackjack)
};  


