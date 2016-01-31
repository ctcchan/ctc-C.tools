#include <iostream>

#include "GlobalVariables.h"
#include "Modules.h"

int main() {
    heading();

    const int NUMBER_OF_PROGRAMS = 13;   // number of sub-programs that can be called
    int menuChoice;
    bool valid;	// input valid check

    do {
        valid = true;   // initialize valid to be true;
        menu(); // print out menu
        cin >> menuChoice;
        cout << endl;
        programCalling(menuChoice); // call programs
        if (menuChoice <= NUMBER_OF_PROGRAMS && menuChoice > 0)
            // only print this line if user's menu choice has been within the correct range
            // and when the program has been executed corrected
            cout << endl << "What would you like to do next?" << endl;
    } while (valid == false || menuChoice != 0);
    // valid is a global variable it is changed inside programCalling()

    cout << "Exiting the program..." << endl; // end of program

    return 0;
}
