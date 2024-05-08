#include "Casino.h"

string cardConvertString(int);      // converts the card number into the card name as a string 

void printDivider();                // for formatting purposes

int vectorSum(vector<int> &);       // helper for blackjack

bool checkForAce(vector<int> &);    // helper for blackjack

void numToCard(int &card);      // helper for blackjack

void print_wheel(vector<string> &arr);      // helper to display wheel

void shift_wheel(vector<string> &arr);      // shifts wheel 1 space to the clockwise direction

string spin_wheel(vector<string> &arr);     // SPIN WHEEL GO WEEEEEEEEEE

bool in_vec(string val, vector<string> &arr);   // finds if a val is in a vector

double bet_results_roulette(string result_num, vector< vector<string>> bet_nums, vector<double> bets, vector<double> odds);     // gets the money won/lost from a spin

void bet_engine_roulette(vector<double> &odds, vector<double> &bets, vector< vector<string>> &bet_nums);                        // mini-client for setting and resetting bets

void print_bet_table_roulette();    // table of potential bets


void printDivider() {

    cout << "---------------------------------------------\n\n";

}


int vectorSum(vector<int> &hand) {
    // gets the point sum of a player's hand
    int sum = 0;

    for (size_t i = 0; i < hand.size(); i++)
        sum += hand[i];

    return sum;
}


bool checkForAce(vector<int> &hand) {
    // returns true if a given card is an ace
    bool isAce = false;
    for ( size_t i = 0; i < hand.size(); i++ )
        if (hand[i] == 11)
            isAce = true;

    return isAce;
}


void numToCard(int &card) {
    // returns a face card or ace as a point value
    if ( card == 11 || card == 12 || card == 13 )
        card = 10;
    else if ( card == 1 )
        card = 11;
}


string cardConvertString(int card) {
    // converts a numeric card to a string
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


Casino::Casino(double startMoney) {   // constructor (default 1000)
    balance = startMoney;
}


double Casino::getBalance() const {     // accessor for current balance
    return balance;
}


bool Casino::checkValidBalance() const {    // returns true if balance is > 0 and < 1 billion
    bool non_zero = balance > 0;
    bool upper_lim = balance < 1000000000;

    return non_zero && upper_lim;
}


void Casino::addMoney(double inMoney) {     // adds money to balance
    balance += inMoney;
}


double Casino::playBlackjack(CardDeck* deck, double bet) {

    bool playerBust = false;        // true if player goes over 21
    bool dealerBust = false;        // true if dealer goes over 21
    int winLossMultiplier;          // changes based on the type of win

    int playerChoice;
    int deckIndex = 0;              // what card in the deck is being used

    size_t j;
    string input;

    vector<string> dealerHand(2);       // holds the dealer hand in terms of cards
    vector<string> playerHand(2);       // holds the player hand in terms of cards
    vector<int> dealerPointsHand(2);    // holds the dealer hand in terms of points
    vector<int> playerPointsHand(2);    // holds the player hand in terms of points

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

    // add cards to point and card hands for dealer
    for (int i = 0; i < 2; i++) {
        currentCard = deck->deal(deckIndex++) % 13 + 1;
        dealerHand[i] = cardConvertString(currentCard);
        numToCard(currentCard);
        dealerPointsHand[i] = currentCard;
    }

    // add cards to point and card hands for player
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

        // print double blackjack case
        cout << "\nDealer Cards Are: " << dealerHand[0] << dealerHand[1];
        cout << "\nDouble Blackjack: Push\n";
        winLossMultiplier = 0;
    }

    if (vectorSum(playerPointsHand) == 21) {
        // player wins

        // print player blackjack case
        cout << "\n\nPlayer Blackjack!\n";
        return 1.5 * bet;
    }

    if (vectorSum(dealerPointsHand) == 21) {
        // dealer wins

        // print dealer blackjack case
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

        } else if (playerChoice == 2) {
            // stand
            break;

        } else {
            // error case
            cerr << "INVALID CHOICE. PLEASE TRY AGAIN." << '\n';
            playerChoice = 0;
            cin.clear();
        }

        // check for over 21 points
        if ( vectorSum(playerPointsHand) > 21) {
            // handle ace case for player busts
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

            // add cards to both lists
            currentCard = deck->deal(deckIndex++) % 13 + 1;
            dealerHand.push_back(cardConvertString(currentCard));
            numToCard(currentCard);
            dealerPointsHand.push_back(currentCard);

            // if dealers busts
            if ( vectorSum(dealerPointsHand) > 21 ) {

                // handle ace case
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
    // randomly generate coin flip
    srand(time(0));
    int flip = rand() % 2;

    cout << "Call Heads [1] or Tails [2].\n";
    cout << ">  ";
    int input;
    cin >> input;

    // output result
    printf("You %s!\n", (flip + 1) == input ? "Win" : "Lose");
    
    // return lost or won money 
    return (flip + 1) == input ? bet : -1 * bet;

}


void Casino::playRoulette() {
    // standard American Wheel Nums
    vector<string> wheelNums = {"0", "28", "9", "26", "30", "11", "7", "20", "32", 
                            "17", "5", "22", "34", "15", "3", "24", "36", 
                            "13", "1", "00", "27", "10", "25", "29", "12", 
                            "8", "19", "31", "18", "6", "21", "33", "16", 
                            "4", "23", "35", "14", "2"};

    // random time seeding
    srand(time(0));

    string answer;
    vector< vector<string>> bet_nums;   // lists of buckets of winning nums
    vector<double> odds, bets;          // lists of the bets made and their respective odds
    double bet_result;                  // win/loss sum after a spin

    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "  1. Change/Set Bet        [B/b]\n";
        cout << "  2. Spin Roulette Wheel   [S/s]\n";
        cout << "  3. Quit                  [Q/q]\n";
        cout << ">  ";

        cin >> answer;

        if (answer == "B" || answer == "b" || answer == "1") {
            // run bet engine
            bet_engine_roulette(odds, bets, bet_nums);

        } else if (answer == "S" || answer == "s" || answer == "2") {
            // must have made a bet
            if (bets.size() < 1) {
                cerr << "No Bets Set. Please make a bet before spinning." << endl;
                continue;
            }
            
            // SPIN THE WHEEL WOOOOOOOOOO
            string winning_num = spin_wheel(wheelNums);

            // negative for a loss, positive for a win
            bet_result = bet_results_roulette(winning_num, bet_nums, bets, odds);

            printf("Winning Num:  %s\n", &winning_num[0]);
            printf("You %s $%.2f\n", bet_result >= 0 ? "Win" : "Lose", abs(bet_result)); // shows the absolute value of the win/loss

            balance += bet_result; // update balance
            printf("New Balance:  $%.2f", balance);

        } else if (answer == "Q" || answer == "q" || answer == "3") {
            cout << "Goodbye!\n";
            break;
        } else {
            cerr << "Invalid Input. Please Try Again.\n";
            continue;
        }
    }

}


void print_bet_table_roulette() {

    printf("         |--------------|\n");
    printf("|--------|   0   |  00  |\n");
    printf("| 1-18   | 1  | 2  | 3  |\n");
    printf("| 19-36  | 4  | 5  | 6  |\n");
    printf("| 1st 12 | 7  | 8  | 9  |\n");
    printf("| 2nd 12 | 10 | 11 | 12 |\n");
    printf("| 3rd 12 | 13 | 14 | 15 |\n");
    printf("| Evens  | 16 | 17 | 18 |\n");
    printf("| Odds   | 19 | 20 | 21 |\n");
    printf("| Black  | 22 | 23 | 24 |\n");
    printf("| Red    | 25 | 26 | 27 |\n");
    printf("|--------| 28 | 29 | 30 |\n");
    printf("         | 31 | 32 | 33 |\n");
    printf("         | 34 | 35 | 36 |\n");
    printf("         |--------------|\n");

}

// mini-client for setting and resetting bets
void bet_engine_roulette(vector<double> &odds, vector<double> &bets, vector< vector<string>> &bet_nums) {
    
    print_bet_table_roulette();
    printf("Welcome to the Bet System!\n\n");

    while (true) { // loop for improper input checks
        printf("What would you like to do?\n");
        printf("  1. Reset all bets [R/r]\n");
        printf("  2. Add a new bet  [A/a]\n");
        printf(">  ");

        string input;
        cin >> input;

        if (input == "R" || input == "r" || input == "1") {
            // reset all bet vecs
            bets.resize(0);
            odds.resize(0);
            bet_nums.resize(0);
            break;

        } else if (input == "A" || input == "a" || input == "2") {
            
            while (true) {  // loop for improper input checks

                int bet;
                printf("How much would you like to bet?\n");
                printf(">  ");
                cin >> bet;
                cout << '\n';

                // add bet to the list of bets
                bets.push_back(bet);

                printf("What bet would you like to make? (Choose a Number)\n");
                printf("  1. 1-18 [1:1 odds]\n");
                printf("  2. 19-36 [1:1 odds]\n");
                printf("  3. 1st 12 [2:1 odds]\n");
                printf("  4. 2nd 12 [2:1 odds]\n");
                printf("  5. 3rd 12 [2:1 odds]\n");
                printf("  6. Evens [1:1 odds]\n");
                printf("  7. Odds [1:1 odds]\n");
                printf("  8. Black [1:1 odds]\n");              // It is not lost on me that the console is black and white. You'll just
                printf("  9. Red [1:1 odds]\n");                // have to believe that what I say is correct  (:   <- that face would never lie
                printf("  10. Single Number [35:1 odds]\n"); 
                printf(">  ");

                string input2;
                cin >> input2;

                // see above issue with a monochromatic console :/
                vector<string> blacks = {"2", "4", "6", "8", "10", "11", "13", "15", "17", "20", "22", "24", "26", "28", "29", "31", "33", "35"};
                vector<string> reds = {"1", "3", "5", "7", "9", "12", "14", "16", "18", "19", "21", "23", "25", "27", "30", "32", "34", "36"};
                vector<string> tmpVec;

                if (input2 == "1") {
                    // 1-18
                    odds.push_back(1); // 1:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 1; i < 19; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "2") {
                    // 19-36
                    odds.push_back(1); // 1:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 19; i < 37; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "3") {
                    // 1st 12
                    odds.push_back(2); // 2:1 odds
                    
                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 1; i < 13; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "4") {
                    // 2nd 12
                    odds.push_back(2); // 2:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 13; i < 25; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "5") {
                    // 3rd 12
                    odds.push_back(2); // 2:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 25; i < 37; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "6") {
                    // Evens
                    odds.push_back(1); // 1:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 2; i < 37; i+=2)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "7") {
                    // Odds
                    odds.push_back(1); // 1:1 odds

                    // add relevent nums to the tmpVec then add that to the list of buckets of nums
                    for (int i = 1; i < 37; i+=2)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "8") {
                    // Blacks
                    odds.push_back(1); // 1:1 odds

                    // add premade vec to vector of buckets of nums
                    bet_nums.push_back(blacks);

                } else if (input2 == "9") {
                    // Reds
                    odds.push_back(1); // 1:1 odds

                    // add premade vec to vector of buckets of nums
                    bet_nums.push_back(reds);

                } else if (input2 == "10") {
                    // single
                    odds.push_back(35); // 35:1 odds (BIG WIN)
                    printf("What Number?");
                    string num;
                    cin >> num;

                    // add that num as a potential winner
                    bet_nums.push_back({num});

                } else {
                    cerr << "Not a valid input. Please try again.\n";
                    continue;
                }

                break;

            }

            break;

        } else {
            cerr << "Not a valid input. Please try again.\n";
            continue;
        }
    }


}

void print_wheel(vector<string> &arr) {
    // I lost years of my life formatting this stupid function.
    // If I did this at a company, I would have charged hazard pay
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n----------------------------------------------\n");
    printf("|                                            |\n");
    printf("|                %*s%*s%*s%*s                |\n", 3, &arr[0][0], 3, &arr[1][0], 3, &arr[2][0], 3, &arr[3][0]);     // For whatever reason, printf
    printf("|          %*s%*s            %*s%*s          |\n", 3, &arr[36][0], 3, &arr[37][0], 3, &arr[4][0], 3, &arr[5][0]);   // only takes arrays of chars,
    printf("|       %*s                        %*s       |\n", 3, &arr[35][0], 3, &arr[6][0]);                                  // not stl strings. Made things
    printf("|    %*s                              %*s    |\n", 3, &arr[34][0], 3, &arr[7][0]);                                  // very fun
    printf("|    %*s                              %*s    |\n", 3, &arr[33][0], 3, &arr[8][0]);
    printf("| %*s                                    %*s |\n", 3, &arr[32][0], 3, &arr[9][0]);
    printf("| %*s                                    %*s |\n", 3, &arr[31][0], 3, &arr[10][0]);
    printf("| %*s                  O----             %*s <<======\n", 3, &arr[30][0], 3, &arr[11][0]);
    printf("| %*s                                    %*s |\n", 3, &arr[29][0], 3, &arr[12][0]);
    printf("| %*s                                    %*s |\n", 3, &arr[28][0], 3, &arr[13][0]);
    printf("|    %*s                              %*s    |\n", 3, &arr[27][0], 3, &arr[14][0]);
    printf("|    %*s                              %*s    |\n", 3, &arr[26][0], 3, &arr[15][0]);
    printf("|       %*s                        %*s       |\n", 3, &arr[25][0], 3, &arr[16][0]);
    printf("|          %*s%*s            %*s%*s          |\n", 3, &arr[24][0], 3, &arr[23][0], 3, &arr[18][0], 3, &arr[17][0]);
    printf("|                %*s%*s%*s%*s                |\n", 3, &arr[22][0], 3, &arr[21][0], 3, &arr[20][0], 3, &arr[19][0]);
    printf("|                                            |\n");
    printf("----------------------------------------------\n\n");
}

// shift vector that wheel is based on to the right one. 
void shift_wheel(vector<string> &arr) {
    string tmpVal = arr[37];
    string previous_val = arr[0];
    string current_val;

    // replace each index with the val to its left
    for (int i = 1; i < 38; i++) {
        current_val = arr[i];
        arr[i] = previous_val;
        previous_val = current_val;
    }
    arr[0] = tmpVal; // set first val to the saved final val
}

string spin_wheel(vector<string> &arr) {
    int num_rotations = rand() % (228 - 38 + 1) + 38;   // randomize the number of right shifts (minimum is 1 rotation. maximum is 6 rotations)

    print_wheel(arr);
    for (int i = 0; i < num_rotations; i++) {

        // I spent an unnecessary amount of time making the wheel slow down over time. I'm very proud of my solution. I named him James
        // James takes the current shift over total shifts to slow the wheel according to total shift amt
        usleep( 15000 + 500000 * ( pow((double)i / num_rotations, 6) ) );

        shift_wheel(arr);
        print_wheel(arr);
    }
    usleep(1000000);
    return arr[11]; // return the num at the pointer
}

bool in_vec(string val, vector<string> &arr) {
    for (size_t i = 0; i < arr.size(); i++)
        if (val == arr[i])
            return true;
        
    return false;
}

double bet_results_roulette(string result_num, vector< vector<string>> bet_nums, vector<double> bets, vector<double> odds) {
    double money_won_lost = 0;

    // iterate through all bets to find each result
    for (size_t i = 0; i < bets.size(); i++) {

        // if the winning num is in a bucket, it's a win for that bet
        if (in_vec(result_num, bet_nums[i]))
            money_won_lost += odds[i] * bets[i];
        else
            money_won_lost -= bets[i];      // can't lose more than you bet

    }

    return money_won_lost;

}
