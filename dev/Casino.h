// Colsen Murray, Porter Dosch
// Dr Emrich, CS202, 4/5/2024
// This is the header file for a casino class, which 
// holds gameplay for several popular casino games

#ifndef CASINO_H
#define CASINO_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

class Casino {

    public:
        // edge case: negative starting value
        Casino(double life_savings = 1000);         // constructor sets totalBands to 1000 by default       // Colsen

        // edge cases: negative money; realistic amt (upper limit); must be a valid cash amount (two decimal places)
        void cashPaycheck(double rent_money);       // add funds without playing a game     // Colsen

        // edge cases: every bad user input; bad bet call
        void playGame();                            // driver function for gameplay         // Porter

        // edge cases: funds >= 0; invalid bet; general incorrect gameplay error-checking
        double playBlackjack(int bet);      // returns the amt won/lost                     // Colsen
        double playSlots(int bet);          // returns the amt won/lost                     // Porter
        double playCoinFlip(int bet);       // returns the amt won/lost                     // Colsen
        double playRoulette(int bet);       // returns the amt won/lost                     // Colsen

    private:
        double totalBands;      // current player balance

};


// reused code from lab 3 below
class CardDeck {

    public:

        CardDeck(int = 52);             // default constructor
        CardDeck(const CardDeck &);     // copy constructor
        ~CardDeck();                    // destructor

        void print();                   // for debugging
        int getSize();                  // returns the array size
        void shuffle();
        int deal(int);                  // returns the card at given index

        const CardDeck &operator=(const CardDeck &);       // overload assignment operator

    private:

        int *cards;                     // pointer to cards array
        int size;                       // size of cards array 

};

#endif
