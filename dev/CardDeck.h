#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <time.h>
#include <string>
using namespace std;

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
