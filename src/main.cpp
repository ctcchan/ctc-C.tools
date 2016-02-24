#include <iostream>

#include "Printer.h"
#include "Modules.h"
#include "Programs.h"

void programCalling(Printer &p, Modules &mo, int m, bool &valid);

int main() {
    Printer print;
    Modules module;

    print.heading();

    const int NUMBER_OF_PROGRAMS = 13;   // number of sub-programs that can be called
    int menuChoice;
    bool valid;	// input valid check

    do {
        valid = true;   // initialize valid to be true;
        print.menu(); // print out menu
        cin >> menuChoice;
        cout << endl;
        programCalling(print, module, menuChoice, valid); // call programs
        if (menuChoice <= NUMBER_OF_PROGRAMS && menuChoice > 0)
            // only print this line if user's menu choice has been within the correct range
            // and when the program has been executed corrected
            cout << endl << "What would you like to do next?" << endl;
    } while (valid == false || menuChoice != 0);
    // valid is a global variable it is changed inside programCalling()

    cout << "Exiting the program..." << endl << endl; // end of program

    return 0;
}

void programCalling(Printer &p, Modules &mo, int m, bool &valid) { // execute sub-programs
    Programs program;

    if (!cin)    // if cin is in fail state, no need to go through switch statement
        mo.inputInvalid(valid);
    else {
        switch (m) { // choose from the menu and execute selected program
            case 0: break;
            case 1: program.randomRow(p, mo); break;
            case 2: program.normalize(p, mo); break;
            case 3: program.rowTable(p, mo); break;
            case 4: program.matrix(p, mo); break;
            case 5: program.matrixRotate(p, mo); break;
            case 6: program.multiTable(p, mo, 1, 1); break; // range = 1 cancels the effect of the rotation
            case 7: program.multiTable(p, mo, 1, 0); break;	// when range is 0, it lets the j + i take effect (rotation)
            case 8: program.multiTable(p, mo, -1, 1); break; // multiply by -1 to change sign of the table, thus making inversions
            case 9: program.multiTable(p, mo, -1, 0); break;
            case 10: program.primeSet(p, mo); break;
            case 11: program.primeTable(p); break;
            case 12: program.permuteTable(p, mo); break;
            case 13: program.subsetsTable(p, mo); break;
            default: mo.inputInvalid(valid); // check if invalid, go back to menu
        }
    }
}
