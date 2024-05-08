// Colsen Murray, Porter Dosch
// Dr Emrich, CS202, 4/5/2024
// This is the header file for a casino class, which 
// holds gameplay for several popular casino games

#ifndef CASINO_H
#define CASINO_H

#include "CardDeck.h"
#include <cstddef>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string>

class Casino {

    public:
        // edge case: negative starting value
        Casino(double startBalance = 1000);         // constructor sets totalBands to 1000 by default       // Colsen

        // edge cases: negative money; realistic amt (upper limit); must be a valid cash amount (two decimal places)
        void addMoney(double inMoney);       // add funds without playing a game     // Colsen
        
        double getBalance() const;
        bool checkValidBalance() const;

        // edge cases: every bad user input; bad bet call
        void play();                            // driver function for gameplay         // Porter

        // edge cases: funds >= 0; invalid bet; general incorrect gameplay error-checking
        double playBlackjack(CardDeck*, double);      // returns the amt won/lost                     // Colsen
        double playSlots(double);          // returns the amt won/lost                     // Porter
        double playCoinFlip(double);       // returns the amt won/lost                     // Colsen
        void playRoulette();       // returns the amt won/lost                     // Colsen

    private:
        double balance;      // current player balance

};

#endif
