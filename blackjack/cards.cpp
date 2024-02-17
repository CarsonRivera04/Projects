#include "cards.h"

Card::Card()
// default constructor for Card class 
{
    rank = 0; 
    suit = SPADES; 
}

Card::Card(int rank, Suit suit)
// constructor with parameters for Card class 
{
    this->rank = rank; 
    this->suit = suit;
}

int Card::GetRank() const
// getter for card rank 
{
    return rank;  
}

int Card::GetSuit() const
// getter for card suit 
{
    return suit; 
}

void Card::Print() const
// member function printing visual for card
{
    cout << " _____" << endl;
    cout << "|"; 
    switch(rank)
    {
        case 1:
            cout << "A";
            break;  
        case 10:
            cout << "10"; 
            break;  
        case 11:
            cout << "J";
            break;  
        case 12:
            cout << "Q";
            break;  
        case 13:
            cout << "K";
            break;  
        default:
            cout << rank; 
    }
    if (rank == 10)
        cout << "   |" << endl; 
    else 
        cout << "    |" << endl; 
    cout << "|     |" << endl; 
    cout << "|  "; 
    switch(suit)
    {
        case CLUBS:
            cout << "♣";
            break; 
        case SPADES:
            cout << "♠";
            break; 
        case DIAMONDS:
            cout << "♦";
            break; 
        case HEARTS:
            cout << "♥";
            break; 
    }
    cout << "  |" << endl; 
    cout << "|     |" << endl;
    cout << "|___"; 
    switch(rank)
    {
        case 1:
            cout << "_A";
            break;  
        case 10:
            cout << "10"; 
            break;  
        case 11:
            cout << "_J";
            break;  
        case 12:
            cout << "_Q";
            break;  
        case 13:
            cout << "_K";
            break;  
        default:
            cout << "_" << rank; 
    } 
    cout << "|" << endl; 
}

Hand::Hand()
// default constructor for hand class 
{
    for (int i = 0; i < 11; i++)
        hand[i] = Card(0, SPADES);
}


int Hand::Total()
// calculates hand total
{
    int total = 0; 
    int aceCount = 0; 
    for (int i = 0; i < 11; i++)
    {
        if (hand[i].GetRank() >= 10)
            total += 10;
        else if (hand[i].GetRank() == 1)
        {
            total += 11;     
            aceCount++;        
        }
        else 
            total += hand[i].GetRank(); 
    }   
    while (aceCount > 0 && total > 21)
    {
        total -= 10; 
        aceCount--; 
    }
    return total; 
}

void Hand::Reset()
// resets hand to have no cards 
{
    for (int i = 0; i < 11; i++)
        hand[i] = Card(0, SPADES);
}

void Hand::SetCard(const Card& c, const int itemNumber)
// puts a card in a hand array
{
    hand[itemNumber] = c;      
}

Card Hand::GetCard(const int itemNumber) const
// gets a card from a hand 
{
    return hand[itemNumber];
}
