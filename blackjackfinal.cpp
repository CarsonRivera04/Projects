#include "cards.h"
void ShuffleCards(Card arr[], const int size);
void Menu(char& input);
void SplitAction(int handNum, Hand& hand, int& counter, bool& canDouble, int& hitCount, bool& actionComplete, double& bankroll, double& betAmount, char& input, Card deck[], bool& playerBust);

int main()
{
    // intro screen 
    cout << "\x1b[2J";
    cout << endl;
    cout << "************************" << endl;
    cout << "- Welcome to Blackjack -" << endl;
    cout << "************************" << endl;
    
    int numOfDecks; 
    do
    // prompts user for amount of decks they want to play with 
    {
        cout << "Enter amount of decks (2-6): ";
        cin >> numOfDecks; 
    }
    while (numOfDecks < 2 || numOfDecks > 6);

    // creates array to specified deck size 
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

    ShuffleCards(deck, deckSize);   // shuffles deck before play begins 
 
    double bankroll;
    do
    // prompts user for amount of money they want to play with 
    {
        cout << "Enter bankroll ($1-$500): $"; 
        cin >> bankroll; 
    }
    while (bankroll < 1 || bankroll > 500);
    
    Hand dHand, pHand, psHand;  // dealer, player, and player-split hands 

    char input;     // char input for various menus 
    int counter = 0, hitCount;  // counters for total cards dealt and times player has to hit 
    double betAmount;           // amount player bets each hand 

    // checks various scenarios in blackjack e.g. if a player is able to split, if insurance 
    // is open, if a player can double, etc. 
    bool canSplit, canDouble, actionComplete, playerBust, blackjack, insurance, didSplit, playerBust2, pBlackjack;  
 
    do
    // this do-while loop encapsulates one hand of blackjack and continues until the player
    // quits or they run out of money 
    {
        cout << "\x1b[2J";  // clears screen 

        // clears dealer and player hands         
        dHand.Reset();
        pHand.Reset();
        psHand.Reset();

        // resets bools for various blackjack scenarios 
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
        // promtps user for bet amount before each hand 
        {
            cout << "Enter bet amount: $"; 
            cin >> betAmount; 
        }
        while (betAmount > bankroll || betAmount <= 0);
        
        bankroll -= betAmount;  // removes bet from player's bankroll  

        cout << endl; 
        cout << "*****************" << endl;
        cout << "- Dealer's Hand -" << endl;
        cout << "*****************" << endl; 
        
        for (int i = 0; i < 2; i++)
        // deals dealer first two cards 
        {
            dHand.SetCard(deck[counter], i);
            counter++;
        }

        dHand.GetCard(0).Print();   // prints first card 

        // prints second card face down 
        cout << " _____" << endl; 
        for (int i = 0; i < 4; i++)
            cout << "|     |" << endl; 
        cout << "|_____|" << endl; 
       
         
        cout << endl;  
        cout << "*****************" << endl;
        cout << "- Player's Hand -" << endl;
        cout << "*****************" << endl; 
        
        for (int i = 0; i < 2; i++)
        // deals and prints player's first two cards 
        {
            pHand.SetCard(deck[counter], i);
            pHand.GetCard(i).Print();
            counter++;
        }
        
        if (pHand.Total() == 21)
        // if player has blackjack, end hand and pay player 3:2 
        {
            pBlackjack = true; 
            bankroll += betAmount + (betAmount * 1.5);  
            cout << "BLACKJACK!!!" << endl;
        }
         
        if (dHand.GetCard(0).GetRank() == 1 && pBlackjack == false)
        // checks if dealer is showing an ace and prompts user for insurance 
        {
            do
            // promtps user 
            {
                cout << endl << "Would you like to take insurance (Y/N): ";
                cin >> input; 
            }
            while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');
            
            switch(input)
            {
                case 'Y':
                case 'y':
                // if player agrees to insurance 
                    bankroll -= (0.5 * betAmount);
                    if (dHand.Total() == 21)
                    // if insurance bet pays, player breaks even 
                    {
                        cout << endl; 
                        cout << "*****************" << endl;
                        cout << "- Dealer's Hand -" << endl;
                        cout << "*****************" << endl; 
                        dHand.GetCard(0).Print(); 
                        dHand.GetCard(1).Print(); 
                        bankroll += (1.5 * betAmount);  // player breaks even
                        cout << "Insurance bet won, PUSH" << endl; 
                        actionComplete = true;
                        insurance = true;  
                    }
                    else 
                    // play continues as normal, but insurance bet is lost 
                        cout << "Dealer does not have blackjack" << endl; 
                    break;
                case 'N':
                case 'n':
                // if player declines insurance 
                    cout << "Insurance declined, play continues" << endl; 
                    break;
            }
        }
        
        if (actionComplete == false && pBlackjack == false)
        // normal blackjack play where player can hit, stand, double, split 
        { 
            do
            // prompts user for action until action is complete e.g. player stands or busts 
            {
                actionComplete = false; 
                if ((pHand.GetCard(0).GetRank() >= 10 && pHand.GetCard(1).GetRank() >= 10) ||
                    ( pHand.GetCard(0).GetRank() == pHand.GetCard(1).GetRank()))
                // checks if player can split and displays option 
                {    
                    canSplit = true;
                    cout << "(X)plit ";
                }
                
                if (canDouble == true)
                // checks if player can double and displays option 
                    cout << "(D)ouble ";
                
     
                Menu(input);    // prints and prompts menu to user 
      
                switch(input)
                // menu options for player 
                {
                    case 'D':
                    case 'd':
                    // if player doubles 
                        if (canDouble == true && bankroll >= betAmount)
                        // checks if they can double 
                        {
                            // doubles down bet size 
                            bankroll -= betAmount; 
                            betAmount += betAmount; 
            
                            // deals player one extra card 
                            pHand.SetCard(deck[counter], hitCount); 
                            pHand.GetCard(hitCount).Print();
                            counter++;

                            canDouble = false;      // player can only double down once  
                            actionComplete = true;  // ends action after user doubles 
                            if (pHand.Total() > 21) 
                            // checks if player busted 
                                playerBust = true;  
                        }
                        else 
                            cout << "Unable to double" << endl; 
                        break; 
                    case 'H':
                    case 'h':   
                    // if player hits 
                        // deal player an additional card 
                        pHand.SetCard(deck[counter], hitCount);
                        pHand.GetCard(hitCount).Print();
                        hitCount++;
                        counter++;

                        canDouble = false;  // player can't double after they hit 
 
                        if (pHand.Total() == 21)
                        // end action if player reaches 21 
                            actionComplete = true; 
                        else if (pHand.Total() > 21)
                        // check if player busted 
                        {
                            actionComplete = true; 
                            playerBust = true; 
                        }
                        break; 
                    case 'S':
                    case 's':
                    // if player stands 
                        actionComplete = true; 
                        break; 
                    case 'X':
                    case 'x':
                    // if player splits 
                        if (bankroll >= betAmount)
                        // checks if they have enough money to split 
                        {
                            didSplit = true;    // player can only split once 
    
                            // puts player's second card into a new hand 
                            psHand.SetCard(pHand.GetCard(1), 0); 

                            // deals with action for both of player's hands 
                            SplitAction(1, pHand, counter, canDouble, hitCount, actionComplete, bankroll, betAmount, input, deck, playerBust);
                            SplitAction(2, psHand, counter, canDouble, hitCount, actionComplete, bankroll, betAmount, input, deck, playerBust2);

                            if (input == 'q' || input == 'Q')
                            // if player quits 
                                return 0;

                            bankroll -= betAmount;  // repeats bet amount on new hand 
                        }
                        else 
                            cout << "Unable to split" << endl; 
                        break; 
                    case 'q':
                    case 'Q':
                    // if user quits 
                        return 0;
                        break;
                }
            }
            while (actionComplete == false);  
        }
        else
            blackjack = true;

        if (insurance == false && pBlackjack == false) 
        // standard play for dealer if player doesn't bust or have blackjack or win insurance
        {
            cout << endl;
            cout << "*****************" << endl;
            cout << "- Dealer's Hand -" << endl;
            cout << "*****************" << endl; 
            
            // prints dealer's orginal 2 cards 
            dHand.GetCard(0).Print();
            dHand.GetCard(1).Print();
            
            bool dealerBust = false;    // resets dealer's bust status 
          
            if ((playerBust == false && didSplit == false) || (didSplit == true && (playerBust == false || playerBust2 == false)))
            // dealer receives cards until they reach a hand total of 17 
            {
                hitCount = 2; 
                
                while (dHand.Total() < 17)
                // deals dealer a card and prints it 
                {
                    dHand.SetCard(deck[counter], hitCount);
                    dHand.GetCard(hitCount).Print();
                    hitCount++;
                    counter++;
                }
            }
            
            if (dHand.Total() > 21)
            // checks if dealer busted 
                dealerBust = true; 
           
            cout << endl; 

            if (didSplit == true)
            // checks if player split during action 
            {
                if (playerBust == true)
                // if first hand busted 
                    cout << "First hand busts" << endl; 
                else if (playerBust == false && dealerBust == true)
                // if dealer busted and player's first hand didnt 
                {
                    bankroll += (betAmount * 2);
                    cout << "DEALER BUSTS! First hand wins!" << endl;  
                }
                else if (playerBust == false && dealerBust == false)
                // if neither dealer nor player's first hand busted  
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player's first hand: " << pHand.Total() << endl; 
                    if (pHand.Total() == dHand.Total())
                    // if dealer and player's first hand have the same total 
                    {
                        bankroll += betAmount; 
                        cout << "First hand PUSH" << endl; 
                    }
                    else if (pHand.Total() > dHand.Total())
                    // if player's first hand > dealer 
                    {
                        bankroll += (betAmount * 2);    
                        cout << "First hand wins!" << endl; 
                    }
                    else 
                        cout << "First hand loses..." << endl; 
                }
                
                if (playerBust2 == true)
                // if player's second hand busted 
                    cout << "Second hand busts" << endl; 
                else if (playerBust2 == false && dealerBust == true)
                // if dealer busted and player's second hand didn't 
                {
                    bankroll += (betAmount * 2);
                    cout << "DEALER BUSTS! Second hand wins!" << endl;  
                }
                else if (playerBust2 == false && dealerBust == false) 
                // if neither dealer nor player's second hand busted 
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player's second hand: " << psHand.Total() << endl; 
                    if (psHand.Total() == dHand.Total())
                    // if dealer and player's second hand have the same total 
                    {
                        bankroll += betAmount; 
                        cout << "Second hand PUSH" << endl; 
                    }
                    else if (psHand.Total() > dHand.Total())
                    // if player's second hand > dealer 
                    {
                        bankroll += (betAmount * 2);    
                        cout << "Second hand wins!" << endl; 
                    }
                    else 
                        cout << "Second hand loses..." << endl; 
                }
            }
            else
            // if player didn't split 
            {
                if (playerBust == true)
                // if player busted 
                    cout << "Player bust, you lose..." << endl; 
                else if (playerBust == false && dealerBust == true)    
                // if dealer busted and player didn't bust 
                {
                    bankroll += (betAmount * 2); 
                    cout << "DEALER BUSTS! YOU WIN!" << endl; 
                }
                else if (playerBust == false && dealerBust == false)
                // if neither player nor dealer busted 
                {
                    cout << "Dealer has: " << dHand.Total() << endl; 
                    cout << "Player has: " << pHand.Total() << endl; 
                    if (pHand.Total() == dHand.Total())
                    // if plyaer and dealer have same hand value 
                    {
                        bankroll += betAmount; 
                        cout << "PUSH" << endl; 
                    }
                    else if (pHand.Total() > dHand.Total())
                    // if player hand > dealer hand 
                    {
                        bankroll += (betAmount * 2); 
                        cout << "PLAYER WINS!" << endl; 
                    }
                    else 
                        cout << "Player loses..." << endl;
                }
            }
        } 

        cout << "Bankroll: $" << bankroll << endl;      // display's user's bankroll 
    
        do
        // prompts user after each hand if they want to continue play 
        {
            cout << "(C)ontinue (Q)uit" << endl;
            cout << "Input: ";
            cin >> input; 
        }
        while(input != 'C' && input != 'c' && input != 'Q' && input != 'q');
        
        if (input == 'q' || input == 'Q')
        // if user quits game 
            return 0; 
    }
    while (bankroll > 0);   // continues game until player runs out of money 

    cout << "The bank wins again..." << endl;     
}

void ShuffleCards(Card arr[], const int size)
// shuffles array of cards 
{
    // array of all possible indexes 
    int arrOfIndexes[size]; 
    for (int i = 0; i < size; i++)
        arrOfIndexes[i] = i;  
    
    int r;              // rng variable 
    Card tempArr[size]; // temp array 
    srand(time(0));     // seeds rng 

    for (int i = 0; i < size; i++)
    // generates random number and puts element to that index 
    {  
        do
            r = rand() % size;  
        while(arrOfIndexes[r] == -1);
        arrOfIndexes[r] = -1; 
        tempArr[i] = arr[r]; 
    } 

   for (int i = 0; i < size; i++)
   // copies temp array back into original array of cards
        arr[i] = tempArr[i]; 
}

void Menu(char& input)
// prints and prompts menu for player action 
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
// this function repeats standard action for each of a player's split hands. the only 
// difference between this and standard player action is the player cannot split once 
// they are already in split hand state 
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
