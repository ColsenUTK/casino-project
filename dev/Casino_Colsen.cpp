#include "Casino.h"

string cardConvertString(int);      // converts the card number into the card name as a string

void printDivider();                // for formatting purposes

int vectorSum(vector<int> &);

bool checkForAce(vector<int> &);

void numToCard(int &card);

void print_wheel(vector<string> &arr);

void shift_wheel(vector<string> &arr);

string spin_wheel(vector<string> &arr);

bool in_vec(string val, vector<string> &arr);

double bet_results_roulette(string result_num, vector< vector<string>> bet_nums, vector<double> bets, vector<double> odds);

void bet_engine_roulette(vector<double> &odds, vector<double> &bets, vector< vector<string>> &bet_nums);

void print_bet_table_roulette();

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
    srand(time(0));
    int flip = rand() % 2;

    cout << "Call Heads [1] or Tails [2].\n";
    cout << ">  ";

    int input;
    cin >> input;

    cout << flip << '\n';
    printf("You %s!", (flip + 1) == input ? "Win" : "Lose");
    
    return (flip + 1) == input ? bet : -1 * bet;

}


void Casino::playRoulette() {

    vector<string> wheelNums = {"0", "28", "9", "26", "30", "11", "7", "20", "32", 
                            "17", "5", "22", "34", "15", "3", "24", "36", 
                            "13", "1", "00", "27", "10", "25", "29", "12", 
                            "8", "19", "31", "18", "6", "21", "33", "16", 
                            "4", "23", "35", "14", "2"};

    srand(time(0));

    string answer;
    vector< vector<string>> bet_nums;
    vector<double> odds, bets;
    double bet_result;

    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "  1. Change/Set Bet        [B/b]\n";
        cout << "  2. Spin Roulette Wheel   [S/s]\n";
        cout << "  3. Quit                  [Q/q]\n";
        cout << ">  ";

        cin >> answer;

        if (answer == "B" || answer == "b" || answer == "1") {
            
            bet_engine_roulette(odds, bets, bet_nums);

        } else if (answer == "S" || answer == "s" || answer == "2") {
            
            if (bets.size() < 1) {
                cerr << "No Bets Set. Please make a bet before spinning." << endl;
                continue;
            }
                
            string winning_num = spin_wheel(wheelNums);

            bet_result = bet_results_roulette(winning_num, bet_nums, bets, odds);

            printf("Winning Num:  %s\n", &winning_num[0]);
            printf("You %s $%.2f\n", bet_result >= 0 ? "Win" : "Lose", abs(bet_result));

            balance += bet_result;
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

void bet_engine_roulette(vector<double> &odds, vector<double> &bets, vector< vector<string>> &bet_nums) {
    
    print_bet_table_roulette();
    printf("Welcome to the Bet System!\n\n");

    while (true) {
        printf("What would you like to do?\n");
        printf("  1. Reset all bets [R/r]\n");
        printf("  2. Add a new bet  [A/a]\n");
        printf(">  ");

        string input;
        cin >> input;

        if (input == "R" || input == "r" || input == "1") {
            bets.resize(0);
            odds.resize(0);
            bet_nums.resize(0);
            break;
        } else if (input == "A" || input == "a" || input == "2") {
            
            while (true) {

                int bet;
                printf("How much would you like to bet?\n");
                printf(">  ");
                cin >> bet;
                cout << '\n';

                bets.push_back(bet);

                printf("What bet would you like to make? (Choose a Number)\n");
                printf("  1. 1-18 [1:1 odds]\n");
                printf("  2. 19-36 [1:1 odds]\n");
                printf("  3. 1st 12 [2:1 odds]\n");
                printf("  4. 2nd 12 [2:1 odds]\n");
                printf("  5. 3rd 12 [2:1 odds]\n");
                printf("  6. Evens [1:1 odds]\n");
                printf("  7. Odds [1:1 odds]\n");
                printf("  8. Black [1:1 odds]\n");
                printf("  9. Red [1:1 odds]\n");
                printf("  10. Single Number [35:1 odds]\n");
                printf(">  ");

                string input2;
                cin >> input2;

                vector<string> blacks = {"2", "4", "6", "8", "10", "11", "13", "15", "17", "20", "22", "24", "26", "28", "29", "31", "33", "35"};
                vector<string> reds = {"1", "3", "5", "7", "9", "12", "14", "16", "18", "19", "21", "23", "25", "27", "30", "32", "34", "36"};
                vector<string> tmpVec;

                if (input2 == "1") {
                    // 1-18
                    odds.push_back(1);

                    for (int i = 1; i < 19; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "2") {
                    // 19-36
                    odds.push_back(1);

                    for (int i = 19; i < 37; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "3") {
                    // 1st 12
                    odds.push_back(2);

                    for (int i = 1; i < 13; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "4") {
                    // 2nd 12
                    odds.push_back(2);

                    for (int i = 13; i < 25; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "5") {
                    // 3rd 12
                    odds.push_back(2);

                    for (int i = 25; i < 37; i++)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "6") {
                    // Evens
                    odds.push_back(1);

                    for (int i = 2; i < 37; i+=2)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "7") {
                    // Odds
                    odds.push_back(1);

                    for (int i = 1; i < 37; i+=2)
                        tmpVec.push_back(to_string(i));

                    bet_nums.push_back(tmpVec);

                } else if (input2 == "8") {
                    // Blacks
                    odds.push_back(1);

                    bet_nums.push_back(blacks);

                } else if (input2 == "9") {
                    // Reds
                    odds.push_back(1);

                    bet_nums.push_back(reds);

                } else if (input2 == "10") {
                    // single
                    odds.push_back(35);
                    printf("What Number?");
                    string num;
                    cin >> num;

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
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n----------------------------------------------\n");
    printf("|                                            |\n");
    printf("|                %*s%*s%*s%*s                |\n", 3, &arr[0][0], 3, &arr[1][0], 3, &arr[2][0], 3, &arr[3][0]);
    printf("|          %*s%*s            %*s%*s          |\n", 3, &arr[36][0], 3, &arr[37][0], 3, &arr[4][0], 3, &arr[5][0]);
    printf("|       %*s                        %*s       |\n", 3, &arr[35][0], 3, &arr[6][0]);
    printf("|    %*s                              %*s    |\n", 3, &arr[34][0], 3, &arr[7][0]);
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

void shift_wheel(vector<string> &arr) {
    string tmpVal = arr[37];
    string previous_val = arr[0];
    string current_val;
    for (int i = 1; i < 38; i++) {
        current_val = arr[i];
        arr[i] = previous_val;
        previous_val = current_val;
    }
    arr[0] = tmpVal;
}

string spin_wheel(vector<string> &arr) {
    int num_rotations = rand() % (228 - 38 + 1) + 38;

    print_wheel(arr);
    for (int i = 0; i < num_rotations; i++) {
        double multiplier = (double)i / num_rotations;
        usleep( 15000 + 500000 * ( pow(multiplier, 6) ) );

        shift_wheel(arr);
        print_wheel(arr);
    }
    usleep(1000000);
    return arr[11];
}

bool in_vec(string val, vector<string> &arr) {
    for (size_t i = 0; i < arr.size(); i++)
        if (val == arr[i])
            return true;
        
    return false;
}

double bet_results_roulette(string result_num, vector< vector<string>> bet_nums, vector<double> bets, vector<double> odds) {
    double money_won_lost = 0;

    for (size_t i = 0; i < bets.size(); i++) {

        if (in_vec(result_num, bet_nums[i]))
            money_won_lost += odds[i] * bets[i];
        else
            money_won_lost -= bets[i];

    }

    return money_won_lost;

}
