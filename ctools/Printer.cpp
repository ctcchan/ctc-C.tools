#include <iostream>
#include <iomanip>

#include "Printer.h"

void Printer::fillDisplay(char s, int num) {    // fill the display with user-defined characters
    cout << '\n' << setfill(s) << setw(num) << '\n';
}

void Printer::newLines(char out, ofstream &outFile) {
    cout << endl << endl;
    if (out == 'y')
        outFile << endl << endl;
}

void Printer::heading() { // print out the program's heading
    fillDisplay('=', 61);
    cout << endl << "\t\t    ctc-C.tools ver. 1.5" << endl << endl
        << "This program lets you construct pitch sets, rows or matrixes" << endl
        << "from input, then display them or outputs them to a file in" << endl
        << "the same directory. Please choose from the options below." << endl << endl
        << "\t\t\t\t" << "by Chin Ting Chan, 2015" << endl;
    fillDisplay('=', 61);
}

void Printer::menu() {    // print out the menu of programs
    cout << endl << "0: Exit the program" << endl
        << "1: Generate a row of random pitches" << endl
        << "2: Construct a row with input of any integers" << endl
        << "3: Construct a twelve-tone row to be mapped to a custom table" << endl
        << "4: Construct a matrix" << endl
        << "5: Construct a matrix in rotation" << endl
        << "6: Construct a multiplication table" << endl
        << "7: Construct a multiplication table in rotation" << endl
        << "8: Construct a multiplication table with inversion" << endl
        << "9: Construct a multiplication table with inversion in rotation" << endl
        << "10: Compute the prime set from a given set" << endl
        << "11: Print the table of pitch class sets" << endl
        << "12: Find all permutations of a given set" << endl
        << "13: Find all subsets of a given set" << endl << endl;
}

void Printer::programHeading(string program, int filling, char out, ofstream &outFile, string addString) { // print out the heading of the program
    fillDisplay('*', filling);
    cout << endl << program + addString << endl;    // add " (left)" or " (right)"
    fillDisplay('*', filling);
    cout << endl;

    if (out == 'y')
        outFile << program + addString << endl << endl;
}

// overloaded function to print out multiplication programs' heading
void Printer::programHeading(int s, int r, int d, int arrSize, int arrSize2, int r1[50], int r2[50], char out, ofstream &outFile, string addString) {
    if (d == 1) d = 8;   //  " (right)" has 8 characters
    else if (d == -1) d = 7; // " (left)" has 7 characters
    else d = 0;

    fillDisplay('*', (r == 0 && s == -1) ? 52 + d : (r == 1 && s == -1) ? 40 + d :
            (r == 0 && s == 1) ? 37 + d : 25 + d); // nested ? : to determine '*' length
    cout << endl;
    if (r == 0 && s == -1)
        cout << "The Multiplication Table with Inversion in Rotation" + addString;  // add " (left) or " (right)"
    else if (r == 1 && s == -1)
        cout << "The Multiplication Table with Inversion";
    else if (r == 0 && s == 1)
        cout << "The Multiplication Table in Rotation" + addString;
    else
        cout << "The Multiplication Table";
    cout << endl;
    fillDisplay('*', (r == 0 && s == -1) ? 52 + d : (r == 1 && s == -1) ? 40 + d :
            (r == 0 && s == 1) ? 37 + d : 25 + d);
    cout << endl;

    if (out == 'y') {
        if (r == 0 && s == -1)
            outFile << "The Multiplication Table with Inversion in Rotation" + addString;
        else if (r == 1 && s == -1)
            outFile << "The Multiplication Table with Inversion";
        else if (r == 0 && s == 1)
            outFile << "The Multiplication Table in Rotation" + addString;
        else
            outFile << "The Multiplication Table";
        outFile << endl;

        for (int i = 0; i < arrSize; i++)
            outFile << TABLE[r1[i]] << " ";
        outFile << " x   ";
        for (int i = 0; i < arrSize2; i++)
            outFile << TABLE[r2[i]] << " ";
        outFile << endl << endl;
    }
}

void Printer::programHeading(int arrSize, int r[50], char out, ofstream &outFile) {  // overloaded function to print out prime set's heading
    fillDisplay('*', 14);
    cout << endl << "The Prime Set" << endl;
    fillDisplay('*', 14);
    cout << endl;

    if (out == 'y')
        outFile << "The Prime Set" << endl;

    for (int i = 0; i < arrSize; i++)
        outFile << TABLE[r[i]] << " ";
    outFile << endl << endl;
}

void Printer::primeReference() {  // reference to Larry Solomon's web site
    cout << "** Reference: Solomon, Larry. \"The Table of Pitch Class Sets.\" "
        << "In Larry Solomon, Musician & Scholar," << endl
        << "http://solomonsmusic.net/pcsets.htm (accessed November 7, 2015)." << endl;
}