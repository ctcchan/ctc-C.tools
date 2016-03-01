#include <iostream>
#include <iomanip>

#include "Printer.h"
#include "Modules.h"

string Printer::getAuthor() {
    return author;
}

string Printer::getTitle() {
    return title;
}

string Printer::getVersion() {
    return version;
}

string Printer::getYear() {
    return year;
}

string Printer::getEmail() {
    return email;
}

string Printer::getWeb() {
    return web;
}

void Printer::fillDisplay(char s, int num) {
    cout << '\n' << setfill(s) << setw(num) << '\n';
}

void Printer::newLines(char out, ofstream &outFile) {
    cout << endl << endl;
    if (out == 'y')
        outFile << endl << endl;
}

void Printer::heading() {
    fillDisplay('=', 61);
    cout << endl << "\t\t" << getTitle() << ", " << getVersion() << ", " << getYear() << endl << endl
        << "This program lets you construct pitch sets, rows or matrixes" << endl
        << "from input, then display them to the console or outputs them" << endl
        << "to a file in your current working directory. Please choose" << endl
        << "from the options below." << endl << endl
        << "** This program can be downloaded and used freely but is" << endl
        << "provided with no warranties." << endl << endl
        << right << setfill(' ') << setw(46) << "by " << getAuthor() << endl
        << setw(60) << getEmail() << endl
        << setw(60) << getWeb() << endl;
    fillDisplay('=', 61);
}

void Printer::menu() {
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

void Printer::programHeading(string program, int filling, char out, ofstream &outFile, string addString) {
    fillDisplay('*', filling);
    cout << endl << program + addString << endl;    // add " (left)" or " (right)"
    fillDisplay('*', filling);
    cout << endl;

    if (out == 'y')
        outFile << program + addString << endl << endl;
}

void Printer::programHeading(int s, int r, int d, char out, ofstream &outFile, string addString) {
    Modules mod;

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

        for (int i = 0; i < mod.getRowSize(1); i++)
            outFile << TABLE[mod.getRow(i, 1)] << " ";
        outFile << " x   ";
        for (int i = 0; i < mod.getRowSize(2); i++)
            outFile << TABLE[mod.getRow(i, 2)] << " ";
        outFile << endl << endl;
    }
}

void Printer::programHeading(char out, ofstream &outFile) {
    Modules mod;

    fillDisplay('*', 14);
    cout << endl << "The Prime Set" << endl;
    fillDisplay('*', 14);
    cout << endl;

    if (out == 'y') {
        outFile << "The Prime Set" << endl;
        for (int i = 0; i < mod.getRowSize(1); i++)
            outFile << TABLE[mod.getRow(i, 5)] << " ";
        outFile << endl << endl;
    }
}

void Printer::primeReference() {
    cout << "** Reference: Solomon, Larry. \"The Table of Pitch Class Sets.\" "
        << "In Larry Solomon, Musician & Scholar," << endl
        << "http://solomonsmusic.net/pcsets.htm (accessed November 7, 2015)." << endl;
}
