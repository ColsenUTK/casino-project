#include "Casino.h"

string cardConvertString(int);      // converts the card number into the card name as a string

void printDivider();                // for formatting purposes

int vectorSum(vector<int> &);

bool checkForAce(vector<int> &);

void numToCard(int &card);

// done
void printDivider() {

    cout << "---------------------------------------------\n\n";

}

// done
int vectorSum(vector<int> &hand) {
    int sum = 0;

    for (size_t i = 0; i < hand.size(); i++)
        sum += hand[i];

    return sum;
}

// done
bool checkForAce(vector<int> &hand) {
    bool isAce = false;

    for ( size_t i = 0; i < hand.size(); i++ )
        if (hand[i] == 11)
            isAce = true;

    return isAce;
}

// done
void numToCard(int &card) {
    if ( card == 11 || card == 12 || card == 13 )
        card = 10;
    else if ( card == 1 )
        card = 11;
}

// done
string cardConvertString(int card) {
    if ( card == 11 ) {
        return "Jack";
    } else if ( card == 12 ) {
        return "Queen";
    } else if ( card == 13 ) {
        return "King";
    } else if ( card == 1 ) {
        return "Ace";
    } else {
        return to_string(card);
    }
}



// done
Casino::Casino(double startMoney) {   // constructor (default 1000)
    balance = startMoney;
}

// done
double Casino::getBalance() const {     // accessor for current balance
    return balance;
}

// done
bool Casino::checkValidBalance() const {    // returns true if balance is > 0 and < 1 billion
    bool non_zero = balance > 0;
    bool upper_lim = balance < 1000000000;

    return non_zero && upper_lim;
}

// done
void Casino::addMoney(double inMoney) {     // adds money to balance
    balance += inMoney;
}


double Casino::playBlackjack(CardDeck* deck, double bet) {

    bool playerBust = false;        // true if player goes over 21
    bool dealerBust = false;        // true if dealer goes over 21
    int winLossMultiplier;

    int playerChoice;
    int deckIndex = 0;              // what card in the deck is being used

    size_t j;
    string input;

    vector<string> dealerHand(2);
    vector<string> playerHand(2);
    vector<int> dealerPointsHand(2);
    vector<int> playerPointsHand(2);

    deck->shuffle();

    if ( deckIndex > 37 ) {
        // if deck has less than 15 cards, reset

        delete deck;
        deck = new CardDeck;
        deck->shuffle();
        deckIndex = 0;

    }
    
    // deal cards
    int currentCard;

    for (int i = 0; i < 2; i++) {
        currentCard = deck->deal(deckIndex++) % 13 + 1;
        dealerHand[i] = cardConvertString(currentCard);
        numToCard(currentCard);
        dealerPointsHand[i] = currentCard;
    }

    for (int i = 0; i < 2; i++) {
        currentCard = deck->deal(deckIndex++) % 13 + 1;
        playerHand[i] = cardConvertString(currentCard);
        numToCard(currentCard);
        playerPointsHand[i] = currentCard;
    }

    // print dealer and player hands
    cout << "\nDealer Hand is: ? (Face Down), " << dealerHand[1] << "\n";

    cout << "Player Hand is: ";
    cout << playerHand[0] << ", " << playerHand[1];


    if (vectorSum(dealerPointsHand) == 21 && vectorSum(playerPointsHand) == 21) {
        // tie
        cout << "\nDealer Cards Are: " << dealerHand[0] << dealerHand[1];
        cout << "\nDouble Blackjack: Push\n";
        winLossMultiplier = 0;
    }

    if (vectorSum(playerPointsHand) == 21) {
        // player wins
        cout << "\n\nPlayer Blackjack!\n";
        return 1.5 * bet;
    }

    if (vectorSum(dealerPointsHand) == 21) {
        // dealer wins
        cout << "\n\nDealer Cards Are: " << dealerHand[0] << ", " << dealerHand[1];
        cout << "\nDealer Blackjack!\n";
        return -1 * bet;
    }


    while (true) { // while loop for invalid input checks

        cout << "\n\nWould you like to (1) hit or (2) stand:  ";
        cin >> playerChoice;

        if (playerChoice == 1) {
            // hit

            // add card to playerHand
            currentCard = deck->deal(deckIndex++) % 13 + 1;
            playerHand.push_back(cardConvertString(currentCard));
            numToCard(currentCard);
            playerPointsHand.push_back(currentCard);

            // print player hand again
            cout << "Player Hand is: " << playerHand[0];
            for (j = 1; j < playerHand.size(); j++) {
                cout << ", " << playerHand[j];
            }
            cout << '\n';

            // cout << "Player Hand is: " << playerPointsHand[0];
            // for (j = 1; j < playerHand.size(); j++) {
            //     cout << ", " << playerPointsHand[j];
            // }
            // cout << '\n';

        } else if (playerChoice == 2) {
            // stand
            break;

        } else {
            cerr << "INVALID CHOICE. PLEASE TRY AGAIN." << '\n';
            playerChoice = 0;
            cin.clear();
        }

        // check for over 21 points
        if ( vectorSum(playerPointsHand) > 21) {
            
            if ( checkForAce(playerPointsHand) ) {
                for (size_t i = 0; i < playerPointsHand.size(); i++)
                    if ( playerPointsHand[i] == 11 )
                        playerPointsHand[i] = 1;

            } else {
                playerBust = true;
                break;
            }
        }

    }  

    if (playerBust) {
        // dealer win
        cout << "\nPlayer Went Over 21.\nPlayer Loses.\n";
        winLossMultiplier =  -1;

    } else {
        
        // dealer hits until 17 points
        while (vectorSum(dealerPointsHand) < 17) {

            currentCard = deck->deal(deckIndex++) % 13 + 1;
            dealerHand.push_back(cardConvertString(currentCard));
            numToCard(currentCard);
            dealerPointsHand.push_back(currentCard);

            if ( vectorSum(dealerPointsHand) > 21 ) {

                if (checkForAce(dealerPointsHand)) {

                    for (size_t i = 0; i < dealerPointsHand.size(); i++)
                        if (dealerPointsHand[i] == 11)
                            dealerPointsHand[i] = 1;

                } else {
                    dealerBust = true;
                    break;
                }

            }

        }

        if (dealerBust) {
            // player win
            cout << "\nDealer Went Over 21.\nPlayer Wins!\n";
            winLossMultiplier = 1;

        } else if (vectorSum(dealerPointsHand) > vectorSum(playerPointsHand)) {
            // dealer win

            // print dealer hand
            cout << "\nDealer Cards Are: " << dealerHand[0];

            for (j = 1; j < dealerHand.size(); j++) {
                cout << ", " << dealerHand[j];
            }

            cout << "\nPlayer Loses.\n";
            winLossMultiplier = -1;

        } else if (vectorSum(playerPointsHand) > vectorSum(dealerPointsHand)) {
            // player win

            // print dealer hand
            cout << "\nDealer Cards Are: " << dealerHand[0];

            for (j = 1; j < dealerHand.size(); j++) {
                cout << ", " << dealerHand[j];
            }

            cout << "\nPlayer Wins!\n";
            winLossMultiplier = 1;

        } else {
            // draw

            // print dealer hand
            cout << "\nDealer Cards Are: " << dealerHand[0];

            for (j = 1; j < dealerHand.size(); j++) {
                cout << ", " << dealerHand[j];
            }

            cout << "\nPush\n";
            winLossMultiplier = 0;

        }

    }

    return winLossMultiplier * bet;

}


double Casino::playCoinFlip(double bet) {

    
    return 0;

}


double Casino::playRoulette(double bet) {

    
    return 0;

}
