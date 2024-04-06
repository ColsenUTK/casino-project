#include <iostream>
#include "Casino.h"
using namespace std;

int main() {

    string answer;

    while (true) {
        // Casino *myCasino = new Casino(/* add starting value here */);
        Casino *myCasino;

        cout << "\n----------------------------------------------------------\n";
        cout << "Would You Like to Go to The Casino? [Y/N]  ";
        cin >> answer;

        if (answer == "Y" || answer == "y") {
            // positive
            double bal = 0;

            cout << "What is your starting balance?  " << '\n';
            cin >> bal;

            // known error with non-numerical inputs. fix later

            cout << '\n';

            if ( bal > 0 ) {
                myCasino = new Casino(bal);

            } else {
                myCasino = new Casino();

            }

            myCasino->play();

            delete myCasino;

        } else if (answer == "N" || answer == "n") {
            // negative
            break;

        } else {
            // error
            cerr << "Invalid input. Please type Y or N.\n";

        }

    }

    return 0;

}