#include "cards.h"
void ShuffleCards(Card arr[], const int size);
void Menu(char& input);
void SplitAction(int handNum, Hand& hand, int& counter, bool& canDouble, int& hitCount, bool& actionComplete, double& bankroll, double& betAmount, char& input, Card deck[], bool& playerBust);

int main()
{
    cout << "\x1b[2J";
    cout << endl;
    cout << "************************" << endl;
    cout << "- Welcome to Blackjack -" << endl;
    cout << "************************" << endl;
    
    int numOfDecks; 
    do
    {
        cout << "Enter amount of decks (2-6): ";
        cin >> numOfDecks; 
    }
    while (numOfDecks < 2 || numOfDecks > 6);

    int deckSize = numOfDecks * 52;
    Card deck[deckSize]; 

    for (int i = 0; i < numOfDecks; i++)
    // initializes deck to one of each card 
    {
        for (int j = 0; j < 13; j++)
        {
            deck[j+(52*i)] = Card(j+1,SPADES); 
            deck[j+13+(52*i)] = Card(j+1,CLUBS); 
            deck[j+26+(52*i)] = Card(j+1,HEARTS);; 
            deck[j+39+(52*i)] = Card(j+1,DIAMONDS); 
        }
    }    
    ShuffleCards(deck, deckSize);
 
    double bankroll;
    do
    {
        cout << "Enter bankroll ($1-$500): $"; 
        cin >> bankroll; 
    }
    while (bankroll < 1 || bankroll > 500);
    
    Hand dHand, pHand, psHand;  // dealer, player, and player-split hands 

    char input;  
    int counter = 0, hitCount;
    double betAmount;  
    bool canSplit, canDouble, actionComplete, playerBust, blackjack, insurance, didSplit, playerBust2, pBlackjack;  
 
    do
    {
        cout << "\x1b[2J";
        dHand.Reset();
        pHand.Reset();
        psHand.Reset();
        canSplit = false; 
        hitCount = 2;  
        canDouble = true;
        playerBust = false;  
        playerBust2 = false; 
        blackjack = false;
        actionComplete = false; 
        insurance = false; 
        didSplit = false; 
        pBlackjack = false; 
        
        if (counter > deckSize / 2)
        // shuffles deck when half of the cards are used 
        {
            ShuffleCards(deck, deckSize); 
            counter = 0; 
        }  
       
        cout << "Bankroll: $" << bankroll << endl; 
        do
        {
            cout << "Enter bet amount: $"; 
            cin >> betAmount; 
        }
        while (betAmount > bankroll || betAmount <= 0);
        
        bankroll -= betAmount; 

        cout << endl; 
        cout << "*****************" << endl;
        cout << "- Dealer's Hand -" << endl;
        cout << "*****************" << endl; 
        
        for (int i = 0; i < 2; i++)
        {
            dHand.SetCard(deck[counter], i);
            counter++;
        }
        dHand.GetCard(0).Print();

        cout << " _____" << endl; 
        for (int i = 0; i < 4; i++)
            cout << "|     |" << endl; 
        cout << "|_____|" << endl; 
       
         
        cout << endl;  
        cout << "*****************" << endl;
        cout << "- Player's Hand -" << endl;
        cout << "*****************" << endl; 
        
        for (int i = 0; i < 2; i++)
        {
            pHand.SetCard(deck[counter], i);
            pHand.GetCard(i).Print();
            counter++;
        }
        
        if (pHand.Total() == 21)
        {
            pBlackjack = true; 
            bankroll += betAmount + (betAmount * 1.5);  
            cout << "BLACKJACK!!!" << endl;
        }
         
        if (dHand.GetCard(0).GetRank() == 1 && pBlackjack == false)
        {
            do
            {
                cout << endl << "Would you like to take insurance (Y/N): ";
                cin >> input; 
            }
            while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');
            
            switch(input)
            {
                case 'Y':
                case 'y':
                    bankroll -= (0.5 * betAmount);
                    if (dHand.Total() == 21)
                    {
                        cout << endl; 
                        cout << "*****************" << endl;
                        cout << "- Dealer's Hand -" << endl;
                        cout << "*****************" << endl; 
                        dHand.GetCard(0).Print(); 
                        dHand.GetCard(1).Print(); 
                        bankroll += (1.5 * betAmount);
                        cout << "Insurance bet won, PUSH" << endl; 
                        actionComplete = true;
                        insurance = true;  
                    }
                    else 
                        cout << "Dealer does not have blackjack" << endl; 
                    break;
                case 'N':
                case 'n':
                    cout << "Insurance declined, play continues" << endl; 
                    break;
            }
        }
        
        if (actionComplete == false && pBlackjack == false)
        { 
            do
            {
                actionComplete = false; 
                if ((pHand.GetCard(0).GetRank() >= 10 && pHand.GetCard(1).GetRank() >= 10) ||
                    ( pHand.GetCard(0).GetRank() == pHand.GetCard(1).GetRank()))
                {    
                    canSplit = true;
                    cout << "(X)plit ";
                }
                
                if (canDouble == true)
                    cout << "(D)ouble ";
                
     
                Menu(input);           
      
                switch(input)
                {
                    case 'D':
                    case 'd':
                        if (canDouble == true && bankroll >= betAmount)
                        {
                            bankroll -= betAmount; 
                            betAmount += betAmount; 
                            pHand.SetCard(deck[counter], hitCount); 
                            pHand.GetCard(hitCount).Print();
                            counter++;
                            canDouble = false; 
                            actionComplete = true; 
                            if (pHand.Total() > 21) 
                                playerBust = true;  
                        }
                        else 
                            cout << "Unable to double" << endl; 
                        break; 
                    case 'H':
                    case 'h':
                        pHand.SetCard(deck[counter], hitCount);
                        pHand.GetCard(hitCount).Print();
                        hitCount++;
                        counter++;
                        canDouble = false; 
                        if (pHand.Total() == 21)
                            actionComplete = true; 
                        else if (pHand.Total() > 21)
                        {
                            actionComplete = true; 
                            playerBust = true; 
                        }
                        break; 
                    case 'S':
                    case 's':
                        actionComplete = true; 
                        break; 
                    case 'X':
                    case 'x':
                        if (bankroll >= betAmount)
                        {
                            didSplit = true; 
                            psHand.SetCard(pHand.GetCard(1), 0); 
                            SplitAction(1, pHand, counter, canDouble, hitCount, actionComplete, bankroll, betAmount, input, deck, playerBust);
                            SplitAction(2, psHand, counter, canDouble, hitCount, actionComplete, bankroll, betAmount, input, deck, playerBust2);

                            if (input == 'q' || input == 'Q')
                                return 0;
                            bankroll -= betAmount; 
                        }
                        else 
                            cout << "Unable to split" << endl; 
                        break; 
                    case 'q':
                    case 'Q':
                        return 0;
                        break;
                }
            }
            while (actionComplete == false);  
        }
        else
            blackjack = true;

        if (insurance == false && pBlackjack == false) 
        {
            cout << endl;
            cout << "*****************" << endl;
            cout << "- Dealer's Hand -" << endl;
            cout << "*****************" << endl; 
            
            dHand.GetCard(0).Print();
            dHand.GetCard(1).Print();
            
            bool dealerBust = false; 
          
            if ((playerBust == false && didSplit == false) || (didSplit == true && (playerBust == false || playerBust2 == false)))
            {
                hitCount = 2; 
                
                while (dHand.Total() < 17)
                {
                    dHand.SetCard(deck[counter], hitCount);
                    dHand.GetCard(hitCount).Print();
                    hitCount++;
                    counter++;
                }
            }
            
            if (dHand.Total() > 21)
                dealerBust = true; 
           
            cout << endl; 

            if (didSplit == true)
            {
                if (playerBust == true)
                    cout << "First hand busts" << endl; 
                else if (playerBust == false && dealerBust == true)
                {
                    bankroll += (betAmount * 2);
                    cout << "DEALER BUSTS! First hand wins!" << endl;  
                }
                else if (playerBust == false && dealerBust == false) 
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player's first hand: " << pHand.Total() << endl; 
                    if (pHand.Total() == dHand.Total())
                    {
                        bankroll += betAmount; 
                        cout << "First hand PUSH" << endl; 
                    }
                    else if (pHand.Total() > dHand.Total())
                    {
                        bankroll += (betAmount * 2);    
                        cout << "First hand wins!" << endl; 
                    }
                    else 
                        cout << "First hand loses..." << endl; 
                }
                
                if (playerBust2 == true)
                    cout << "Second hand busts" << endl; 
                else if (playerBust2 == false && dealerBust == true)
                {
                    bankroll += (betAmount * 2);
                    cout << "DEALER BUSTS! Second hand wins!" << endl;  
                }
                else if (playerBust2 == false && dealerBust == false) 
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player's second hand: " << psHand.Total() << endl; 
                    if (psHand.Total() == dHand.Total())
                    {
                        bankroll += betAmount; 
                        cout << "Second hand PUSH" << endl; 
                    }
                    else if (psHand.Total() > dHand.Total())
                    {
                        bankroll += (betAmount * 2);    
                        cout << "Second hand wins!" << endl; 
                    }
                    else 
                        cout << "Second hand loses..." << endl; 
                }
            }
            else
            {
                if (playerBust == true)
                    cout << "Player bust, you lose..." << endl; 
                else if (playerBust == false && dealerBust == true)    
                {
                    bankroll += (betAmount * 2); 
                    cout << "DEALER BUSTS! YOU WIN!" << endl; 
                }
                else if (playerBust == false && dealerBust == false)
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player has: " << pHand.Total() << endl; 
                    if (pHand.Total() == dHand.Total())
                    {
                        bankroll += betAmount; 
                        cout << "PUSH" << endl; 
                    }
                    else if (pHand.Total() > dHand.Total())
                    {
                        bankroll += (betAmount * 2); 
                        cout << "PLAYER WINS!" << endl; 
                    }
                    else 
                        cout << "Player loses..." << endl;
                }
            }
        } 

        cout << "Bankroll: $" << bankroll << endl;  
        do
        {
            cout << "(C)ontinue (Q)uit" << endl;
            cout << "Input: ";
            cin >> input; 
        }
        while(input != 'C' && input != 'c' && input != 'Q' && input != 'q');
        
        if (input == 'q' || input == 'Q')
            return 0; 
    }
    while (bankroll > 0);

    cout << "The bank wins again..." << endl;     
}

void ShuffleCards(Card arr[], const int size)
{
    // array of all possible indexes 
    int arrOfIndexes[size]; 
    for (int i = 0; i < size; i++)
        arrOfIndexes[i] = i;  
    
    int r; 
    Card tempArr[size];
    srand(time(0));  

    for (int i = 0; i < size; i++)
    {  
        do
            r = rand() % size;  
        while(arrOfIndexes[r] == -1);
        arrOfIndexes[r] = -1; 
        tempArr[i] = arr[r]; 
    } 

   for (int i = 0; i < size; i++)
        arr[i] = tempArr[i]; 
}

void Menu(char& input)
{
    cout << "(H)it (S)tand (Q)uit" << endl; 
    do 
    {
        cout << "Input: ";
        cin >> input; 
    }
    while (input != 'Q' && input != 'q' &&
           input != 'H' && input != 'h' &&
           input != 'S' && input != 's' && 
           input != 'X' && input != 'x' &&
           input != 'D' && input != 'd'); 
}


void SplitAction(int handNum, Hand& hand, int& counter, bool& canDouble, int& hitCount, bool& actionComplete, double& bankroll, double& betAmount, char& input, Card deck[], bool& playerBust)
{  
    cout << endl; 
    cout << "*****************" << endl;
    cout << "- Player Hand-" << handNum << " -" << endl; 
    cout << "*****************" << endl; 
    hand.GetCard(0).Print(); 
    hand.SetCard(deck[counter], 1); 
    hand.GetCard(1).Print();
    counter++;

    canDouble = true; 
    hitCount = 2; 
    do
    {
        actionComplete = false;
        if (canDouble == true)
            cout << "(D)ouble ";
        cout << "(H)it (S)tand (Q)uit" << endl; 
        do 
        {
            cout << "Input: ";
            cin >> input; 
        }
        while (input != 'Q' && input != 'q' &&
               input != 'H' && input != 'h' &&
               input != 'S' && input != 's' && 
               input != 'D' && input != 'd'); 
        switch(input)
        {
            case 'D':
            case 'd':
                if (canDouble == true && bankroll >= betAmount)
                {
                    bankroll -= betAmount;
                    betAmount += betAmount; 
                    hand.SetCard(deck[counter], hitCount); 
                    hand.GetCard(hitCount).Print();
                    counter++;
                    canDouble = false; 
                    actionComplete = true;
                    if (hand.Total() > 21)
                        playerBust = true;  
                }
                else 
                    cout << "Unable to double" << endl; 
                break;
            case 'H':
            case 'h':
                hand.SetCard(deck[counter], hitCount);
                hand.GetCard(hitCount).Print();
                hitCount++;
                counter++;
                canDouble = false; 
                if (hand.Total() == 21)
                    actionComplete = true;
                else if (hand.Total() > 21)
                {
                    actionComplete = true; 
                    playerBust = true;  
                }
                 
                break;
            case 'S':
            case 's':
                actionComplete = true; 
                break;
            case 'Q':
            case 'q':
                actionComplete = true; 
                break;
        }
    }
    while (actionComplete == false);
}
