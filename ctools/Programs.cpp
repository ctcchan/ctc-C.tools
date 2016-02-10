#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "GlobalVariables.h"
#include "Modules.h"
#include "Programs.h"

void Programs::randomRow() {   // generate a row of random pitches
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[10000];	// the row

    cout << endl;
    x = module.inputRowLength(10000);
    srand(unsigned(time(NULL)));
    for (int i = 0; i < x; i++)  // populate array with random numbers from 0-11
        row[i] = rand() % 12;

    module.programHeading("The Random Tone Row", 20, choice, outputFile);

    for (int i = 0; i < x; i++) {    // print out the random row
        cout << TABLE[row[i]] << " ";
        if (choice == 'y')
            outputFile << TABLE[row[i]] << " ";
    }

    module.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::normalize() {   // allow input of any integers to create a tone row
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[50];	// the row

    cout << endl;
    x = module.inputRowLength();
    module.inputRowNor(x, row);

    module.programHeading("The Row", 8, choice, outputFile);

    for (int i = 0; i < x; i++) { // print out the final row
        cout << TABLE[module.mod(row[i])] << " ";
        // look up from the table and translate pitch numbers to pitch names
        if (choice == 'y')
            outputFile << TABLE[module.mod(row[i])] << " ";
    }

    module.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::rowTable() {    // allow the use of a table other than the chromatic table
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x = 12;	// size of row
    int row[50], row2[50];	// the row

    char answer;
    bool valid; //input valid check

    module.populateRow(true, x, row, "Enter a twelve-tone row in pitches or numbers to create a reference table: ");

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
                    for (int i = 0; i < x; i++)
                        row2[i] = row[i];
                    break;
                case 'n':   // if 'n', enter a new row
                    module.populateRow(true, x, row2, "Enter your twelve-tone row in pitches or numbers to map to the reference table: ");
                    break;
                default:
                    module.inputInvalid(valid);
            }
        }
    } while (valid == false);

    module.programHeading("The Row", 8, choice, outputFile);

    for (int i = 0; i < x; i++) { // print out the row
        cout << TABLE[row[module.mod(row2[i])]] << " ";
        // look up from the table (row[i]) and translate pitch numbers to pitch names
        if (choice == 'y')
            outputFile << TABLE[row[module.mod(row2[i])]] << " ";
    }

    module.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::matrix() {  // create a matrix
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[50];	// the row
    int tranTable[50];	// the transposition table

    module.populateRow(false, x, row, "Please enter your row: ");

    module.transposition(tranTable, x, row);

    module.programHeading("The Matrix", 11, choice, outputFile);

    int tranTableMatrix[50];
    // initialize a different transposition to find the distance of each pitch from first pitch
    for (int i = 0; i < x; i++)
        tranTableMatrix[i] = module.mod(row[i] - row[0]);

    // print out the matrix table
    const string TABLE_NUM[12] = { "0 ", "1 ", "2 ", "3 ", "4 ", "5 ",
        "6 ", "7 ", "8 ", "9 ", "10", "11" };
    cout << "     "; // print out I
    if (choice == 'y')
        outputFile << "     ";
    for (int i = 0; i < x; i++) {
        cout << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
        if (choice == 'y')
            outputFile << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
    }
    module.newLines(choice, outputFile);

    for (int i = 0; i < x; i++) {
        cout << "P" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << "  ";    // print out P
        if (choice == 'y')
            outputFile << "P" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << "  ";

        for (int j = 0; j < x; j++) { // print body of matrix
            row[j] = module.mod(row[j] - tranTable[i]); // minus to get transpositions of inversions
            cout << TABLE[row[j]] << " ";
            // look up from the table and translate pitch numbers to pitch names
            if (choice == 'y')
                outputFile << TABLE[row[j]] << " ";
        }

        cout << " R" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << " ";    // print out R
        if (choice == 'y')
            outputFile << " R" + TABLE_NUM[module.mod(12 - tranTableMatrix[i])] << " ";

        module.newLines(choice, outputFile);
    }

    cout << "     "; // print out RI
    if (choice == 'y')
        outputFile << "     ";
    for (int i = 0; i < x; i++) {
        cout << "RI" + TABLE_NUM[tranTableMatrix[i]];
        if (choice == 'y')
            outputFile << "RI" + TABLE_NUM[tranTableMatrix[i]];
    }

    module.newLines(choice, outputFile);
    outputFile << endl;

    outputFile.close();
}

void Programs::matrixRotate() {  // matrix in rotation
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[50];	// the row
    int tranTable[50];	// the transposition table

    module.populateRow(false, x, row, "Please enter your row: ");

    module.transposition(tranTable, x, row);

    int direction = module.rotationDirection();

    module.programHeading("The Matrix in Rotation", (direction == 1) ? 31 : 30, choice, outputFile,
            (direction == 1) ? " (right)" : " (left)");

    // print out the matrix table
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++)
            row[j] = module.mod(row[j] - tranTable[i]); // minus to get transpositions of inversions
        for (int j = 0; j < x; j++) {
            cout << TABLE[row[module.mod(j + i * direction, x)]] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            if (choice == 'y')
                outputFile << TABLE[row[module.mod(j + i * direction, x)]] << " ";
        }
        module.newLines(choice, outputFile);
    }

    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}

void Programs::multiTable(int sign, int range) {   // multiplications of various types, with inversion/in rotation by 1 index
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x, y;	// sizes of rows
    int row[50], row2[50];	// the rows
    int tranTable[50];	// the transposition table

    cout << endl;
    x = module.inputRowLength(50, "1st ");
    module.inputRow(x, row, "1st ");
    cout << endl;
    y = module.inputRowLength(50, "2nd ");
    module.inputRow(y, row2, "2nd ");

    module.transposition(tranTable, x, row2);

    int direction = 0;
    if (range == 0)  // only execute if range = 0 (rotation)
        direction = module.rotationDirection();

    module.programHeading(sign, range, direction, x, y, row, row2, choice, outputFile, (direction == 1) ? " (right)" : " (left)");

    for (int i = 0; i < y; i++) { // print out the multiplication table
        for (int j = 0; j < x; j++)
            row[j] = module.mod(row[j] + tranTable[i] * sign); // plus or minus to transpositions of row2[i]
        for (int j = 0; j < x; j++) {
            cout << TABLE[row[module.mod(j + (i - i * range) * direction, x + range * 12)]] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            // when range is 1, it cancels the rotation by subtraction, and set the limit larger than 12
            // when it is 0, it sets the range to x, thus rotation (j + i, x)
            if (choice == 'y')
                outputFile << TABLE[row[module.mod(j + (i - i * range) * direction, x + range * 12)]] << " ";
        }
        module.newLines(choice, outputFile);
    }
    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}

void Programs::primeSet() {
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[12];	// the row

    cout << endl;
    x = module.inputRowLength(12);
    module.inputRow(x, row);

    module.insertionSort(x, row);   // insertion sort of row[i]

    int multiRow[48][48]; // initialize a large 2-D array as a grid
    for (int i = 0; i < x; i++) { //populate the 2-D array with all transpositions of normal sets
        for (int j = 0; j < x; j++) {
            multiRow[i][j] = module.mod(row[j] - row[i]);
            multiRow[i + x][j] = module.mod(row[j] - (12 - row[i]));
            multiRow[i + x * 2][j] = module.mod(12 - row[j] - row[i]);
            multiRow[i + x * 3][j] = module.mod(row[i] - row[j]);
        }
    }

    int smallest;
    for (int i = 0; i < x * 4; i++) { // reduce the normal sets to start at pitch 0
        smallest = 12;  // initialize smallest every times it loops back
        for (int j = 0; j < x; j++)
            // find smallest
            smallest = (multiRow[i][j] < smallest) ? multiRow[i][j] : smallest;
        for (int j = 0; j < x; j++)
            // subtract smallest from rows
            multiRow[i][j] -= smallest;
    }

    module.insertionSortMulti(x, multiRow);   // insertion sort of all normal sets

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
    for (int i = 0; i < x * 4; i++)
        smallest = (multiRow[i][x - 1] < smallest) ? multiRow[i][x - 1] : smallest;
    // store the positions where the smallest outer pitch occurs
    // if the position's value is not the smallest, store -1
    for (int i = 0; i < x * 4; i++)
        posArr[i] = (multiRow[i][x - 1] == smallest) ? i : -1;

    int column = 1; // start the above process again on second pitch
    while (column < x - 1) {
        smallest = 12;  // initialize smallest to 12 every time
        // find smallest pitch on each column
        for (int i = 0; i < x * 4; i++) {
            if (posArr[i] >= 0)  // only check posArr[i] that are positive
                smallest = (multiRow[posArr[i]][column] < smallest) ? multiRow[posArr[i]][column] : smallest;
        }
        // store the positions where the smallest 2nd pitch occurs
        // when the loop comes back, it finds smallest 3rd pitch, etc, but only on positions
        // where the PREVIOUS pitch is smallest
        for (int i = 0; i < x * 4; i++) {
            if (posArr[i] >= 0)  // only check posArr[i] that are positive
                posArr[i] = (multiRow[posArr[i]][column] == smallest) ? i : -1;
        }
        column++;
    }

    for (int i = 0; i < x * 4; i++) { // find the final position
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
    module.programHeading(x, row, choice, outputFile);
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

    for (int i = 0; i < x; i++) { // print out the prime set (multiRow[position][i] only consist of integers)
        if (i == 0) {
            cout << "(" << multiRow[position][i] << ", ";
            if (choice == 'y')
                outputFile << "(" << multiRow[position][i] << ", ";
        }
        else if (i < x - 1) {
            cout << multiRow[position][i] << ", ";
            if (choice == 'y')
                outputFile << multiRow[position][i] << ", ";
        }
        else {
            cout << multiRow[position][i] << ")";
            if (choice == 'y')
                outputFile << multiRow[position][i] << ")";
        }
    }
    module.newLines(choice, outputFile);

    int invertedPrime[12]; // find the inversion of the prime set
    for (int i = 0; i < x; i++) // inverse the prime set
        invertedPrime[i] = multiRow[position][x - 1] - multiRow[position][i];

    module.insertionSort(x, invertedPrime);   // insertion sort of invertedPrime[i]

    // convert prime sets from integer arrays into single strings
    string primeString = "";
    string invertedPrimeString = "";
    for (int i = 0; i < x; i++) {
        primeString += module.intToString(multiRow[position][i]);
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

        module.primeReference();
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
                        module.primeReference();
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

void Programs::primeTable() {  // print out the table of pitch class sets by Larry Solomon
    Modules module;
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
        module.primeReference();
        cout << endl;
    }

    inFile.close();    // close file after reading all data
    inFile2.close();
}

void Programs::permuteTable() {	// find all permutations of a given set
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[50];	// the row

    module.populateRow(false, x, row, "Please enter your row: ");

    string stringTable = "";
    for (int i = 0; i < x; i++)
        stringTable += module.intToString(row[i]);

    module.programHeading("The Permutation Table", 22, choice, outputFile);

    module.permute("", stringTable, x, choice, outputFile);

    cout << endl;
    if (choice == 'y')
        outputFile << endl << endl;

    outputFile.close();
}

void Programs::subsetsTable() {	// find all subsets of a given set
    Modules module;
    char choice;    // choice, 'y' or 'n'
    ofstream outputFile;    // output stream object
    module.outputting(choice, outputFile);

    int x;	// size of row
    int row[50];	// the row

    module.populateRow(false, x, row, "Please enter your row: ");

    string stringTable = "";
    for (int i = 0; i < x; i++)
        stringTable += module.intToString(row[i]);

    module.programHeading("All Subsets", 12, choice, outputFile);

    module.subsets("", stringTable, choice, outputFile);

    if (choice == 'y')
        outputFile << endl;

    outputFile.close();
}