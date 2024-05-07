// References: https://cplusplus.com/reference/cstdlib/rand/  https://en.cppreference.com/w/cpp/container/list  https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
#include "casino.h"
#include <string>
#include <limits>
#include <stdlib.h>
#include <iomanip>
#include <set>

using namespace std;

bool checkBet(double, double);

void roll(list<string> &, string[]);

void printSlots(string[]);

double bigWin(string[], double);

void Casino::play() {
    while(1) {
        char input; // to store input.
        cout << "Enter a command. (h) for help." << endl;

        if(cin >> input) {
            if(input == 'q' || input == 'Q') {
                break; // if input is q, quit.
            }

            else if(input == 'h' || input == 'H') {
                // function to describe commands.
                cout << "Commands:\nA: Add money to balance.\nB: Play blackjack.\n";
                cout << "S: Play slots.\nC: Coin Flip - double or nothing\nR: Play Roulette.\n\n";
            }

            else if(input == 'a' || input == 'A') {
                // function to add money to balance. 
                double funds;
                // error checking. this same code is run for every single function that requires input.
                cout << "Input amount of money to add: ";
                while(1) {
                    if(cin >> funds) {
                        if(funds > 0) { // check if the value is non-negative.
                        break;
                        }
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid amount. Please enter a non-negative numerical value. Must be no greater than available balance.\n\n";
                    cout << "Input amount of money to add: ";
                }

                addMoney(funds);
            }

            else if(input == 'b' || input == 'B') {
                // Blackjack
                double bet;
                cout << "Input bet: ";
                while(1) {
                    if(cin >> bet) {
                        if(checkBet(bet, balance)) {
                            break;
                        }
                    }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount. Please enter a non-negative numerical value. Must be no greater than available balance.\n\n"                cout << "Input bet: ";
                }
                balance -= bet;
                CardDeck *deck = new CardDeck;
                balance += playBlackjack(deck, bet);
                delete deck;
            }

            else if(input == 'S' || input == 's') {
                // Slots
                double bet;
                cout << "Input bet: ";
                while(1) {
                    if(cin >> bet) {
                        if(checkBet(bet, balance)) {
                            break;
                        }
                    }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount. Please enter a non-negative numerical value. Must be no greater than available balance.\n\n"                cout << "Input bet: ";
                }
                balance -= bet;
                balance += playSlots(bet);
            }

            else if(input == 'C' || input == 'c') {
                // Coinflip
                double bet;
                cout << "Input bet: ";
                while(1) {
                    if(cin >> bet) {
                        if(checkBet(bet, balance)) {
                            break;
                        }
                    }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount. Please enter a non-negative numerical value. Must be no greater than available balance.\n\n"                cout << "Input bet: ";
                }
                balance -= bet;
                balance += playCoinFlip(bet);
            }

            else if(input == 'R' || input == 'r') {
                // Roulette
                double bet;
                cout << "Input bet: ";
                while(1) {
                    if(cin >> bet) {
                        if(checkBet(bet, balance)) {
                            break;
                        }
                    }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount. Please enter a non-negative numerical value. Must be no greater than available balance.\n\n"                cout << "Input bet: ";
                }
                balance -= bet;
                balance += playRoulette(bet);
            }
        cout << "Current balance: " << balance << "\n\n";
        }
    }
}

double Casino::void playSlots(double inputBet) {
    // Providing a seed value
	srand((unsigned) time(NULL));
    string slotMachine[9]; // to store final values
    // initialize slots 
    list<string> slots{"blank", "blank", "blank", "blank", "7", "7", "7", "777", "777", "777", "bar", "bar", "bar", "bar", "diamond", "diamond", "diamond", "10x", "50x", "100x"}; // to store the values for rolling
    double bet = inputBet;
    double win;
    int numSpins;

    // roll and output the reward.
    roll(slots, slotMachine);

    printSlots(slotMachine);
        
    win = bigWin(slotMachine, bet);

    // TODO : different outputs for different win values.
    if(win < 2*bet) {
        cout << "Payout: " << win << "\n\n";
    }

    else if(win < 8*bet) {
        cout << "Big win!\n" << win << "\n\n";
    }
        
    else if(win < 8*bet) {
        cout << "Big win!\n" << win << "\n\n";
    }

    else if(win < 20*bet) {
        cout << "Massive win!\n" << win << "\n\n";
    }

    else if(win < 50*bet) {
        cout << "Magnificent win!\n" << win << "\n\n";
    }

    else {
        cout << "Tremendous!\n" << win << "\n\n";
    }
    
    return win;
}

void printSlots(string slots[]) {
    // prints, for a 3x3 board, the output of a roll.
    cout << '/' << setw(35) << setfill('-') << right << '\\' << endl << setfill(' ');
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            cout << setw(12) << left << slots[3*i + j];
        }
        cout << "\n\n";
    }
}

double checkPayline(vector<string>& payline, double bet) {
    // to help with bigWin win check function.
    set<string> reels;
    for(size_t i = 0; i < payline.size(); ++i) {
        // check for equality of objects inside payline using a set.
        reels.insert(payline[i]);
    }
    // most difficult check first: some combination of 777 and 7.
    if(reels.size() == payline.size()-1) {
        if(reels.count("777") && reels.count("7")) {
            // if there is a mixture of 7s, return the original bet.
            return bet;
        }
    }

    else if(reels.size() == 1) {
        if(reels.count("bar")) {
            // bar returns half the original bet.
            return 0.5*bet;
        }

        else if(reels.count("7")) {
            // 7 returns 5x the original bet
            return 5*bet;
        }

        else if(reels.count("777")) {
            // 777 returns 7x the original bet
            return 7*bet;
        }

        else if(reels.count("diamond")) {
            // diamond returns 9x the original bet
            return 9*bet;
        }
    }
    return 0; // if nothing else matches, lose the bet.
}

double bigWin(string slots[], double bet) {
    // check the paylines (both diagonals and straight across).
    double win = 0;
    // have to check straight across (for all rows).
    
    for(int i = 0; i < 3; ++i) {
        vector<string> payline; // to store values from slots.
        // have to check all three elements along rows.
        // check this case, and since a 10x, 50x, or 100x multiplier will return 0 from checkPayline, then check for those cases.
        for(int j = 0; j < 3; ++j) {
            payline.push_back(slots[3*i + j]);
        }
        win += checkPayline(payline, bet);
        payline.clear();
        
        if(slots[3*i + 1] == "10x") {
            // now only have to check 1st and 3rd element.
            payline.push_back(slots[3*i]); // first element of each row
            payline.push_back(slots[3*i + 2]); // last element of each row
            win += 10*checkPayline(payline, bet); // for each multiplier, check the win.
        }

        else if(slots[3*i + 1] == "50x") {
            // same as above, different multiplier.
            payline.push_back(slots[3*i]);
            payline.push_back(slots[3*i + 2]);
            win += 50*checkPayline(payline, bet);
        }

        else if(slots[3*i + 1] == "100x") {
            payline.push_back(slots[3*i]);
            payline.push_back(slots[3*i + 2]);
            win += 100*checkPayline(payline, bet);
        }
    }
    
    // then have to check diagonals
    vector<string> payline;
    int middle = 4; // store the middle index of the machine.
    // off diagonal, then main.

    for(int j = 0; j < 3; j++) {
        payline.push_back(slots[4*j]);
    }
    win += checkPayline(payline, bet);
    payline.clear();

    for(int j = 2; j < 8; j += 2) {
        payline.push_back(slots[j]);
    }
    win += checkPayline(payline, bet);
    payline.clear();
    
    // then check the multiplier
    if(slots[middle] == "10x") {
        payline.push_back(slots[0]); 
        payline.push_back(slots[8]); 
        win += 10*checkPayline(payline, bet); 

        payline.clear(); 
        payline.push_back(slots[2]);
        payline.push_back(slots[6]);
        win += 10*checkPayline(payline, bet);
    }

    else if(slots[middle] == "50x") {
        payline.push_back(slots[0]);
        payline.push_back(slots[8]);
        win += 50*checkPayline(payline, bet);

        payline.clear(); 
        payline.push_back(slots[2]);
        payline.push_back(slots[6]);
        win += 50*checkPayline(payline, bet);
    }

    else if(slots[middle] == "100x") {
        payline.push_back(slots[0]);
        payline.push_back(slots[8]);
        win += 100*checkPayline(payline, bet);

        payline.clear(); 
        payline.push_back(slots[2]);
        payline.push_back(slots[6]);
        win += 100*checkPayline(payline, bet);
    }

    return win; // return final value of win.
}

bool checkBet(double bet, double balance) {
    // check the input bet against the user balance.
    return balance > bet;
}

void roll(list<string> & slots, string slotMachine[]) {
    string ret;
    int size = slots.size(); 

    for(int j = 0; j < 9; ++j) {
        auto it = slots.begin(); // iterator representing beginning of list.
        if(j == 1 || j == 4 || j == 7) {
            int numSpins = rand() % size; // spin for a randomly generated amount of spins each iteration. (exclude multipliers except for middle row)
            advance(it, numSpins);
            slotMachine[j] = *it;
        }

        else {
            int numSpins = rand() % (size - 3);
            advance(it, numSpins);
            slotMachine[j] = *it;
        }
    }
}