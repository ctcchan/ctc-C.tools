#ifndef PRINTER_H_
#define PRINTER_H_

#include <fstream>
#include "GlobalVariables.h"

class Printer{
    public:
        void fillDisplay(char s, int num);
        void newLines(char out, ofstream &outFile);
        void heading();
        void menu();
        void programHeading(string program, int filling, char out, ofstream &outFile, string addString = "");
        void programHeading(int s, int r, int d, int arrSize, int arrSize2, int r1[50], int r2[50], char out, ofstream &outFile, string addString = "");
        void programHeading(int arrSize, int r[50], char out, ofstream &outFile);
        void primeReference();
};

#endif
