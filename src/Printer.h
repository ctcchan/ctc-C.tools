#ifndef PRINTER_H_
#define PRINTER_H_

#include <fstream>
#include "GlobalVariables.h"

class Printer {
    public:
        void fillDisplay(char s, int num);    // fill the display with user-defined characters
        void newLines(char out, ofstream &outFile); // print out new lines
        void heading(string author, string title, double version, string year); // print out the program's heading
        void menu();    // print out the menu of programs
        void programHeading(string program, int filling, char out, ofstream &outFile, string addString = ""); // print out the heading of the program
        void programHeading(int s, int r, int d, char out, ofstream &outFile, string addString = ""); // overloaded function to print out multiplication programs' heading
        void programHeading(char out, ofstream &outFile);  // overloaded function to print out prime set's heading
        void primeReference();  // reference to Larry Solomon's web site
};

#endif
