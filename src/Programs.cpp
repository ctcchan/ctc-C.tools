#include <iostream>
#include <cstdlib>
#include <ctime>

#include "GlobalVariables.h"
#include "Printer.h"
#include "Modules.h"
#include "Programs.h"

void Programs::randomRow(Printer &print, Modules &module) {   // generate a row of random pitches
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    cout << endl;
    module.inputRowLength(3, 10000, "");
    srand(unsigned(time(NULL)));
    for (int i = 0; i < module.getRowSize(1); i++) // populate array with random numbers from 0-11
        module.setRow(i, rand() % 12, 3);

    print.programHeading("The Random Tone Row", 20, choice, outputFile);

    for (int i = 0; i < module.getRowSize(1); i++) {    // print out the random row
        cout << TABLE[module.getRow(i, 3)] << " ";
        if (choice == 'y')
            outputFile << TABLE[module.getRow(i, 3)] << " ";
    }

    print.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::normalize(Printer &print, Modules &module) {   // allow input of any integers to create a tone row
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    cout << endl;
    module.inputRowLength(1);
    module.inputRowNor();
    cout << endl;

    print.programHeading("The Row", 8, choice, outputFile);

    for (int i = 0; i < module.getRowSize(1); i++) { // print out the final row
        cout << TABLE[module.mod(module.getRow(i, 1))] << " ";
        // look up from the table and translate pitch numbers to pitch names
        if (choice == 'y')
            outputFile << TABLE[module.mod(module.getRow(i, 1))] << " ";
    }

    print.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::rowTable(Printer &print, Modules &module) {    // allow the use of a table other than the chromatic table
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    char answer;
    bool valid; //input valid check

    module.populateRow(true, 1, "Enter a twelve-tone row in pitches or numbers to create a reference table: ");

    do {
        valid = true;
        cout << endl << "Use the same row as the reference table? (y/n): ";
        // use the same row as a matrix mapped to a reference table
        cin >> answer;
        if (!cin)
            module.inputInvalid(valid);
        else {
            switch (answer) {
                case 'y':   // if 'y', the row equals the table
                    for (int i = 0; i < module.getRowSize(1); i++)
                        module.setRow(i, module.getRow(i, 1), 2);
                    break;
                case 'n':   // if 'n', enter a new row
                    module.populateRow(true, 2, "Enter your twelve-tone row in pitches or numbers to map to the reference table: ");
                    break;
                default:
                    module.inputInvalid(valid);
            }
        }
    } while (valid == false);

    print.programHeading("The Row", 8, choice, outputFile);

    for (int i = 0; i < module.getRowSize(1); i++) { // print out the row
        cout << TABLE[module.getRow(module.mod(module.getRow(i, 2)), 1)] << " ";
        // look up from the table (row[i]) and translate pitch numbers to pitch names
        if (choice == 'y')
            outputFile << TABLE[module.getRow(module.mod(module.getRow(i, 2)), 1)]  << " ";
    }

    print.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::matrix(Printer &print, Modules &module) {  // create a matrix
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    module.populateRow(false, 1, "Please enter your row: ");

    module.transposition(1);

    print.programHeading("The Matrix", 11, choice, outputFile);

    int tranTableMatrix[50];
    // initialize a different transposition to find the distance of each pitch from first pitch
    for (int i = 0; i < module.getRowSize(1); i++)
        tranTableMatrix[i] = module.mod(module.getRow(i, 1) - module.getRow(0, 1));

    // print out the matrix table
    const string TABLE_NUM[12] = { "0 ", "1 ", "2 ", "3 ", "4 ", "5 ",
        "6 ", "7 ", "8 ", "9 ", "10", "11" };
    cout << "     "; // print out I
    if (choice == 'y')
        outputFile << "     ";
    for (int i = 0; i < module.getRowSize(1); i++) {
        cout << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
        if (choice == 'y')
            outputFile << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
    }
    print.newLines(choice, outputFile);

    for (int i = 0; i < module.getRowSize(1); i++) {
        cout << "P" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << "  ";    // print out P
        if (choice == 'y')
            outputFile << "P" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << "  ";

        for (int j = 0; j < module.getRowSize(1); j++) { // print body of matrix
            module.setRow(j, module.mod(module.getRow(j, 1) - module.getRow(i, 4)), 1); // minus to get transpositions of inversions
            cout << TABLE[module.getRow(j, 1)] << " ";
            // look up from the table and translate pitch numbers to pitch names
            if (choice == 'y')
                outputFile << TABLE[module.getRow(j, 1)] << " ";
        }

        cout << " R" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << " ";    // print out R
        if (choice == 'y')
            outputFile << " R" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << " ";

        print.newLines(choice, outputFile);
    }

    cout << "     "; // print out RI
    if (choice == 'y')
        outputFile << "     ";
    for (int i = 0; i < module.getRowSize(1); i++) {
        cout << "RI" + TABLE_NUM[tranTableMatrix[i]];
        if (choice == 'y')
            outputFile << "RI" + TABLE_NUM[tranTableMatrix[i]];
    }

    print.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::matrixRotate(Printer &print, Modules &module) {  // matrix in rotation
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    module.populateRow(false, 1, "Please enter your row: ");

    module.transposition(1);

    int direction = module.rotationDirection();

    print.programHeading("The Matrix in Rotation", (direction == 1) ? 31 : 30, choice, outputFile, (direction == 1) ? " (right)" : " (left)");

    // print out the matrix table
    for (int i = 0; i < module.getRowSize(1); i++) {
        for (int j = 0; j < module.getRowSize(1); j++)
            module.setRow(j, module.mod(module.getRow(j, 1) - module.getRow(i, 4)), 1); // minus to get transpositions of inversions
        for (int j = 0; j < module.getRowSize(1); j++) {
            cout << TABLE[module.getRow(module.mod(j + i * direction, module.getRowSize(1)), 1)] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            if (choice == 'y')
                outputFile << TABLE[module.getRow(module.mod(j + i * direction, module.getRowSize(1)), 1)] << " ";
        }
        print.newLines(choice, outputFile);
    }

    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}

void Programs::multiTable(Printer &print, Modules &module, int sign, int range) {   // multiplications of various types, with inversion/in rotation by 1 index
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    cout << endl;
    module.inputRowLength(1, 50, "1st ");
    module.inputRow(1, "1st ");
    cout << endl;
    module.inputRowLength(2, 50, "2nd ");
    module.inputRow(2, "2nd ");

    module.transposition(2);

    int direction = 0;
    if (range == 0)  // only execute if range = 0 (rotation)
        direction = module.rotationDirection();

    print.programHeading(sign, range, direction, choice, outputFile, (direction == 1) ? " (right)" : " (left)");

    for (int i = 0; i < module.getRowSize(2); i++) { // print out the multiplication table
        for (int j = 0; j < module.getRowSize(1); j++)
            module.setRow(j, module.mod(module.getRow(j, 1) + module.getRow(i, 4) * sign), 1); // plus or minus to transpositions of row2[i]
        for (int j = 0; j < module.getRowSize(1); j++) {
            cout << TABLE[module.getRow(module.mod(j + (i - i * range) * direction, module.getRowSize(1) + range * 12), 1)] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            // when range is 1, it cancels the rotation by subtraction, and set the limit larger than 12
            // when it is 0, it sets the range to x, thus rotation (j + i, x)
            if (choice == 'y')
                outputFile << TABLE[module.getRow(module.mod(j + (i - i * range) * direction, module.getRowSize(1) + range * 12), 1)] << " ";
        }
        print.newLines(choice, outputFile);
    }
    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}

void Programs::primeSet(Printer &print, Modules &module) {
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    cout << endl;
    module.inputRowLength(1, 12, "");
    module.inputRow(5);
    cout << endl;

    module.sortRow(1); // insertion sort of row[i]

    // initialize a large 2-D array as a grid
    for (int i = 0; i < module.getRowSize(1); i++) { //populate the 2-D array with all transpositions of normal sets
        for (int j = 0; j < module.getRowSize(1); j++) {
            module.setMultiRow(i, j, module.mod(module.getRow(j, 5) - module.getRow(i, 5)));
            module.setMultiRow(i + module.getRowSize(1), j, module.mod(module.getRow(j, 5) - (12 - module.getRow(i, 5))));
            module.setMultiRow(i + module.getRowSize(1) * 2, j, module.mod(12 - module.getRow(j, 5) - module.getRow(i, 5)));
            module.setMultiRow(i + module.getRowSize(1) * 3, j, module.mod(module.getRow(i, 5) - module.getRow(j, 5)));
        }
    }

    int smallest;
    for (int i = 0; i < module.getRowSize(1) * 4; i++) { // reduce the normal sets to start at pitch 0
        smallest = 12;  // initialize smallest every times it loops back
        for (int j = 0; j < module.getRowSize(1); j++)
            // find smallest
            smallest = (module.getMultiRow(i, j) < smallest) ? module.getMultiRow(i, j) : smallest;
        for (int j = 0; j < module.getRowSize(1); j++)
            // subtract smallest from rows
            module.setMultiRow(i, j, module.getMultiRow(i, j) - smallest);
    }

    module.sortRow(2);    // insertion sort of all normal sets

    int position = 0;
    /*
    // this solution sometimes doesn't work; keep for reference only
    // 0 1 3 7 8 is wrong; the [x- 1] position is incorrect?
    // find position of the smallest outer, then 2nd, 3rd... pitches in the normal sets
        for(int i = 0; i < x * 4; i++) {
            position = (multiRow[i][x - 1] <= multiRow[position][x - 1]) ?
                // most important to first determine the outer pitch is the smallest
                // then the first pitch (+- 1); sometimes 0138 cannot be reduced to 0237
                (multiRow[i][1] - 1 <= multiRow[position][1]) ?
                // if position 2-4 are all less/equal, return i, else return the last smaller value
                ((multiRow[i][2] <= multiRow[position][2]) &&
                 (multiRow[i][3] <= multiRow[position][3]) &&
                 (multiRow[i][4] <= multiRow[position][4]) ? i : position)
                : position  // if position 1 is NOT less
                : position; // if position x - 1 (last) is NOT less
        }
    */
    int posArr[48];   // store the smallest numbers from each column
    smallest = 12;
    // find smallest pitch on last column of all rows
    for (int i = 0; i < module.getRowSize(1) * 4; i++)
        smallest = (module.getMultiRow(i, module.getRowSize(1) - 1) < smallest) ? module.getMultiRow(i, module.getRowSize(1) - 1) : smallest;
    // store the positions where the smallest outer pitch occurs
    // if the position's value is not the smallest, store -1
    for (int i = 0; i < module.getRowSize(1) * 4; i++)
        posArr[i] = (module.getMultiRow(i, module.getRowSize(1) - 1) == smallest) ? i : -1;

    int column = 1; // start the above process again on second pitch
    while (column < module.getRowSize(1) - 1) {
        smallest = 12;  // initialize smallest to 12 every time
        // find smallest pitch on each column
        for (int i = 0; i < module.getRowSize(1) * 4; i++) {
            if (posArr[i] >= 0)  // only check posArr[i] that are positive
                smallest = (module.getMultiRow(posArr[i], column) < smallest) ? module.getMultiRow(posArr[i], column) : smallest;
        }
        // store the positions where the smallest 2nd pitch occurs
        // when the loop comes back, it finds smallest 3rd pitch, etc, but only on positions
        // where the PREVIOUS pitch is smallest
        for (int i = 0; i < module.getRowSize(1) * 4; i++) {
            if (posArr[i] >= 0)  // only check posArr[i] that are positive
                posArr[i] = (module.getMultiRow(posArr[i], column) == smallest) ? i : -1;
        }
        column++;
    }

    for (int i = 0; i < module.getRowSize(1) * 4; i++) { // find the final position
        if (posArr[i] >= 0)  // the list should consist of all -1 except for one, which stores the final position
            position = posArr[i];
    }

    /*  The following program sometimes returns Forte Prime, sometimes returns Rahn Prime.
        The algorithm it uses is different from them because it looks at the largest
        pitch, then calculate to find the row that has the smallest sum.
        Below are sets that are different in Forte and Rahn Primes:

        Pitch Class Set     Forte Prime         Rahn Prime
        5-20                (0,1,3,7,8)         (0,1,5,6,8)
        6-Z29               (0,1,3,6,8,9)       (0,2,3,6,7,9)
        6-31                (0,1,3,5,8,9)       (0,1,4,5,7,9)
        7-20                (0,1,2,4,7,8,9)     (0,1,2,5,6,7,9)
        8-26                (0,1,2,4,5,7,9,10)  (0,1,3,4,5,7,8,10)
        */
    /*
    int sumArr[200] = {0};
    for(int i = 0; i < x * 4; i++) { // find the sum of each row
        for(int j = 0; j < x; j++)
            sumArr[i] += multiRow[i][j];
    }
    for(int i = 0; i < x * 4; i++) {
        // if the outer pitch in a row is the least, check the sum of all pitches
        // if the row is also the least; then it is the prime set
        position = (multiRow[i][x - 1] <= multiRow[position][x - 1]) ?
            (sumArr[i] <= sumArr[position] ? i : position) : position;
    }
    */
    print.programHeading(choice, outputFile);
    /*
        for(int i = 0; i < x * 4; i++) { // print out all the sets for checking
            for(int j = 0; j < x; j++) {
                cout << multiRow[i][j] << " ";
                if(choice == 'y')
                    outputFile << multiRow[i][j] << " ";
            }
            cout << endl;
            if(choice == 'y')
                outputFile << endl;
        }
    */

    for (int i = 0; i < module.getRowSize(1); i++) { // print out the prime set (multiRow[position][i] only consist of integers)
        if (i == 0) {
            cout << "(" << module.getMultiRow(position, i) << ", ";
            if (choice == 'y')
                outputFile << "(" << module.getMultiRow(position, i) << ", ";
        }
        else if (i < module.getRowSize(1) - 1) {
            cout << module.getMultiRow(position, i) << ", ";
            if (choice == 'y')
                outputFile << module.getMultiRow(position, i) << ", ";
        }
        else {
            cout << module.getMultiRow(position, i) << ")";
            if (choice == 'y')
                outputFile << module.getMultiRow(position, i) << ")";
        }
    }
    print.newLines(choice, outputFile);

    int invertedPrime[12]; // find the inversion of the prime set
    for (int i = 0; i < module.getRowSize(1); i++) // inverse the prime set
        invertedPrime[i] = module.getMultiRow(position, module.getRowSize(1) - 1) - module.getMultiRow(position, i);

    for (int i = 0; i < module.getRowSize(1); i++) { // insertion sort of invertedPrime[i]
        int j = i;
        while (j > 0 && invertedPrime[j] < invertedPrime[j - 1]) {
            module.swap(invertedPrime[j], invertedPrime[j - 1]);
            j--;
        }
    }

    // convert prime sets from integer arrays into single strings
    string primeString = "";
    string invertedPrimeString = "";
    for (int i = 0; i < module.getRowSize(1); i++) {
        primeString += module.intToString(module.getMultiRow(position, i));
        invertedPrimeString += module.intToString(invertedPrime[i]);
    }

    // use text files as inputs to print out more information about the prime set
    bool found = false;
    string setNum, forteSetNum, primeSetNum, intervalVector, description;
    ifstream inFile, inFile2;
    inFile.open("setTable.txt");    // use setTable.txt to output information of the set
    inFile2.open("setTableDescription.txt");  // description

    if (!inFile) {    // make sure the file is in the same directory
        cout << "The file \"setTable.txt\" is not found." << endl << endl;
        inFile.clear();
    } else {
        while (!inFile.eof()) {   // process the txt file consisting of all Forte sets
            inFile >> setNum >> forteSetNum >> primeSetNum >> intervalVector;
            inFile.ignore(MAXINT, '\t');   // take out two tabs before the description
            inFile.ignore(MAXINT, '\t');
            getline(inFile, description);   // store the rest of the line as a string to description
            if (primeSetNum == primeString) {
                found = true;
                break;  // break out of the loop if the set is found at current position
            }
        }

        // add symbols for printing
        primeSetNum = "(" + primeSetNum + ")";
        invertedPrimeString = "[" + invertedPrimeString + "]";
        intervalVector = "<" + intervalVector + ">";

        if (found == false) { // if not found, say it is not found
            cout << "Set does not match any Forte Prime Sets." << endl << endl;
            if (choice == 'y')
                outputFile << "Set does not match any Forte Prime Sets." << endl << endl;
        } else {
            cout << "Number: " << setNum << endl << "Forte Set-name: " << forteSetNum << endl
                << "Prime Form: " << primeSetNum << endl << "Inversion: " << invertedPrimeString
                << endl << "Interval Vector: " << intervalVector << endl << "Description: "
                << description << endl << endl;
            if (choice == 'y')
                outputFile << "Number: " << setNum << endl << "Forte Set-name: " << forteSetNum << endl
                    << "Prime Form: " << primeSetNum << endl << "Inversion: " << invertedPrimeString
                    << endl << "Interval Vector: " << intervalVector << endl << "Description: "
                    << description << endl << endl;
        }
        if (choice == 'y')
            outputFile << endl;

        print.primeReference();
        cout << endl;
    }

    outputFile.close(); // close files after reading all data

    // read setTableDescription.txt
    char answer;
    bool valid;	// input valid check

    do {
        valid = true;
        cout << "Would you like to read more? (y/n): ";
        cin >> answer;
        if (!cin)
            module.inputInvalid(valid);
        else {
            switch (answer) {
                case 'y':
                    cout << endl;
                    if (!inFile2) {   // make sure the file is in the same directory
                        cout << "The file \"setTableDescription.txt\" is not found." << endl;
                        inFile2.clear();
                    }
                    else {
                        while (!inFile2.eof()) {  // read the entire file and print it out
                            getline(inFile2, description);
                            cout << description << endl;
                        }
                        cout << endl;
                        print.primeReference();
                    }
                    break;
                case 'n':
                    break;
                default:
                    module.inputInvalid(valid);
            }
        }
        cout << endl;
    } while (valid == false);

    inFile.close(); // close files after reading all data
    inFile2.close();
}

void Programs::primeTable(Printer &print) {  // print out the table of pitch class sets by Larry Solomon
    ifstream inFile, inFile2;
    inFile.open("setTable.txt");
    inFile2.open("setTableDescription.txt");

    string entireTable;

    bool finish = false;  // control printing of reference
    if (!inFile) {   // make sure the file is in the same directory
        cout << "The file \"setTable.txt\" is not found." << endl << endl;
        inFile.clear();
    } else {
        while (!inFile.eof()) {  // read the entire file and print it out
            getline(inFile, entireTable);
            cout << entireTable << endl;
        }
        cout << endl;
        finish = true;
    }

    if (!inFile2) {   // make sure the file is in the same directory
        cout << "The file \"setTableDescription.txt\" is not found." << endl << endl;
        inFile2.clear();
    } else {
        while (!inFile2.eof()) {  // read the entire file and print it out
            getline(inFile2, entireTable);
            cout << entireTable << endl;
        }
        cout << endl;
        finish = true;
    }

    if (finish == true) {
        print.primeReference();
        cout << endl;
    }

    inFile.close();    // close file after reading all data
    inFile2.close();
}

void Programs::permuteTable(Printer &print, Modules &module) {	// find all permutations of a given set
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    module.populateRow(false, 1, "Please enter your row: ");

    string stringTable = "";
    for (int i = 0; i < module.getRowSize(1); i++)
        stringTable += module.intToString(module.getRow(i, 1));

    print.programHeading("The Permutation Table", 22, choice, outputFile);

    module.permute("", stringTable, module.getRowSize(1), choice, outputFile);

    cout << endl;
    if (choice == 'y')
        outputFile << endl << endl;

    outputFile.close();
}

void Programs::subsetsTable(Printer &print, Modules &module) {	// find all subsets of a given set
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    module.populateRow(false, 1, "Please enter your row: ");

    string stringTable = "";
    for (int i = 0; i < module.getRowSize(1); i++)
        stringTable += module.intToString(module.getRow(i, 1));

    print.programHeading("All Subsets", 12, choice, outputFile);

    module.subsets("", stringTable, choice, outputFile);

    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}
