#include "CardDeck.h"

// using namespace std;

CardDeck::CardDeck(int n) {
    // default constructor has n = 52 cards

    int i;
    
    cards = new int[n];
    size = n;

    // fill array with numbers [1 - n] 
    for (i = 0; i < n; i++)
        cards[i] = i;

}

CardDeck::CardDeck(const CardDeck &copyDeck) {
    // copy constructor

    int i;

    size = copyDeck.size;
    cards = new int[size];      // create array of same size as copyDeck

    // copy array from copyDeck to this deck
    for (i = 0; i < size; i++) {
        cards[i] = copyDeck.cards[i];
    }

}

CardDeck::~CardDeck() {

    // conceptual help from GeeksForGeeks at
    // https://www.geeksforgeeks.org/destructors-c/

    delete[] cards;
}

void CardDeck::print() {                // for debugging purposes
    // print cards to the screen

    for (int i = 0; i < size; i++) {

        if ( i % 13 == 0 && i != 0)
            std::cout << '\n';

        std::cout << std::setw(2) << cards[i] << ' ';
    
    }

    std::cout << '\n';

}

int CardDeck::getSize() {
    return size;
}

void CardDeck::shuffle() {
    // help from Porter Dosch -- CS202 Student

    int i;
    std::vector<int> temp_vector;

    // copy cards array into temp vector
    for (i = 0; i < size; i++)
        temp_vector.push_back(cards[i]);

    std::random_shuffle(temp_vector.begin(), temp_vector.end());        // srand() set to 0 in main()

    // copy temp vector back into cards array
    for (i = 0; i < size; i++)
        cards[i] = temp_vector[i];

}

int CardDeck::deal(int index) {
    return cards[index];
}

const CardDeck & CardDeck::operator=( const CardDeck &toBeAssigned) {
    // overloads the '=' operator to permit assignment of CardDeck objects

    // from array.cpp in class notes by Professor Emrich

    // conceptual help from GeeksForGeeks at
    // https://www.geeksforgeeks.org/cpp-assignment-operator-overloading/

    int i;

    if ( &toBeAssigned != this ) {

        if ( size != toBeAssigned.size ) {

            delete[] cards;
            size = toBeAssigned.size;
            cards = new int[size];

        }

        for (i = 0; i < size; i++)
            cards[i] = toBeAssigned.cards[i];

    }

    return (*this);

}
