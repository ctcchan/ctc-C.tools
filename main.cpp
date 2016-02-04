#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// global variables
const int NUMBER_OF_PROGRAMS = 11;   // number of sub-programs that can be called
const int LIMIT = 50; // max size of rows
const int MAXINT = 2147483647; // max number an integer can hold
const string TABLE[12] = {"C  ", "C# ", "D  ", "Eb ", "E  ", "F  ", // chromatic table for printing
                          "F# ", "G  ", "Ab ", "A  ", "Bb ", "B  "};
char choice;    // choice, 'y' or 'n'
ofstream outputFile;    // output stream object
int x, y;   // sizes of rows
bool valid; // input valid check
string input, input2;   // get user inputs
int row[LIMIT], row2[LIMIT];    // the rows
int tranTable[LIMIT];    // transposition table for the series

// function prototypes
// modules
void fillDisplay(char sym, int num);
void heading();
void menu();
void programCalling(int m);
void programHeading(string program, int filling, string addString = "");
void programHeading(int s, int r, int d, string addString = "");
void programHeading();
void primeReference();
int mod(int num, int rangeSize = 12);   // same function as modLoop() below, use recursion instead of loop
//int modLoop(int num, int rangeSize = 12);
void insertionSort(int *ptArr, int arrSize);
void insertionSortMulti(int arrMulti[LIMIT * 4][LIMIT * 4], int arrSize);
int pitchToNum(string pitch);
string intToString(int num);
void inputInvalid(bool &check);
void inputRowLength(bool &check, int &length, int lim = LIMIT, string num = "");
void inputRow(bool &check, string in, int arr[LIMIT], int arrSize, string num = "");
void inputRow(bool &check, int arr[LIMIT], int arrSize);
int rotationDirection();
void outputting(char &f, ofstream &outFile);
// programs
void randomRow();
void normalize();
void rowTable();
void matrix();
void matrixRotate();
void multiTable(int sign, int range);
void primeSet();
void primeTable();

int main(){
    heading();

    int menuChoice;

    do{
        valid = true;   // initialize valid to be true;
        menu(); // print out menu
        cin >> menuChoice;
        cout << endl;
        programCalling(menuChoice); // call program
        if(menuChoice <= NUMBER_OF_PROGRAMS && menuChoice > 0)
        // only print this line if user's menu choice has been within the correct range
        // and when the program has been executed corrected
            cout << endl << "What would you like to do next?" << endl;
    }while(valid == false || menuChoice != 0);
    // valid is a global variable it is changed inside programCalling()

    cout << "Exiting the program..." << endl; // end of program
    cin.clear();
	return 0;
}

void fillDisplay(char sym, int num){    // fill the display with user-defined characters
    cout << "\n" << setfill(sym) << setw(num) << "\n";
}

void heading(){ // print out the program's heading
    fillDisplay('=', 63);
    cout << endl << "\t\t\tctc-C.tools ver. 1.0" << endl << endl
        << "This program lets users construct pitch sets, rows or matrixes" << endl
        << "from input, then display them or outputs them to a file in the" << endl
        << "same directory. Please choose from the options below." << endl << endl
        << "\t\t\t\t" << "by Chin Ting Chan, 2015" << endl;
    fillDisplay('=', 63);
}

void menu(){    // print out the menu of programs
    cout << endl << "0: Exit the program" << endl
        << "1: Generate a random tone row" << endl
        << "2: Construct a row with input of any integers" << endl
        << "3: Construct a twelve-tone row to be mapped to a custom table" << endl
        << "4: Construct a matrix" << endl
        << "5: Construct a matrix in rotation" << endl
        << "6: Construct a multiplication table" << endl
        << "7: Construct a multiplication table in rotation" << endl
        << "8: Construct a multiplication table with inversion" << endl
        << "9: Construct a multiplication table with inversion in rotation" << endl
        << "10: Compute the prime set from a given set"<< endl
        << "11: Print the table of pitch class sets" << endl << endl;
}

void programCalling(int m){ // execute sub-programs
    if(!cin)    // if cin is in fail state, no need to go through switch statement
        inputInvalid(valid);
    else
        switch(m){ // choose from the menu and execute selected program
            case 0: break;
            case 1: randomRow(); break;
            case 2: normalize(); break;
            case 3: rowTable(); break;
            case 4: matrix(); break;
            case 5: matrixRotate(); break;
            case 6: multiTable(1, 1); break; // range = 1 cancels the effect of the rotation
            case 7: multiTable(1, 0); break;   // when range is 0, it lets the j + i take effect (rotation)
            case 8: multiTable(-1, 1); break; // multiply by -1 to change sign of the table, thus making inversions
            case 9: multiTable(-1, 0); break;
            case 10: primeSet(); break;
            case 11: primeTable(); break;
            default: inputInvalid(valid); // check if invalid, go back to menu
        }
}

void programHeading(string program, int filling, string addString){ // print out the heading of the program
    fillDisplay('*', filling);
    cout << endl << program + addString << endl;    // add " (left)" or " (right)"
    fillDisplay('*', filling);
    cout << endl;

    if(choice == 'y')
        outputFile << program + addString << endl << endl;
}

void programHeading(int s, int r, int d, string addString){  // overloaded function to print out multiplication programs' heading
    if(d == 1) d = 8;   //  " (right)" has 8 characters
    else if(d == -1) d = 7; // " (left)" has 7 characters
    else d = 0;

    fillDisplay('*', (r == 0 && s == -1) ? 52 + d : (r == 1 && s == -1) ? 40 + d :
                     (r == 0 && s == 1) ? 37 + d : 25 + d); // nested ? : to determine '*' length
    cout << endl;
    if(r == 0 && s == -1)
        cout << "The Multiplication Table with Inversion in Rotation" + addString;  // add " (left) or " (right)"
    else if(r == 1 && s == -1)
        cout << "The Multiplication Table with Inversion";
    else if(r == 0 && s == 1)
        cout << "The Multiplication Table in Rotation" + addString;
    else
        cout << "The Multiplication Table";
    cout << endl;
    fillDisplay('*', (r == 0 && s == -1) ? 52 + d : (r == 1 && s == -1) ? 40 + d :
                     (r == 0 && s == 1) ? 37 + d : 25 + d);
    cout << endl;

    if(choice == 'y'){
         if(r == 0 && s == -1)
            outputFile << "The Multiplication Table with Inversion in Rotation" + addString;
        else if(r == 1 && s == -1)
            outputFile << "The Multiplication Table with Inversion";
        else if(r == 0 && s == 1)
            outputFile << "The Multiplication Table in Rotation" + addString;
        else
            outputFile << "The Multiplication Table";
        outputFile << endl;

        for(int i = 0; i < x; i++)
            outputFile << TABLE[row[i]] << " ";
        outputFile << " x   ";
        for(int i = 0; i < y; i++)
            outputFile << TABLE[row2[i]] << " ";
        outputFile << endl << endl;
    }
}

void programHeading(){  // overloaded function to print out prime set's heading
    fillDisplay('*', 14);
    cout << endl << "The Prime Set" << endl;
    fillDisplay('*', 14);
    cout << endl;

    if(choice == 'y')
        outputFile << "The Prime Set" << endl;

    for(int i = 0; i < x; i++)
        outputFile << TABLE[row[i]] << " ";
    outputFile << endl << endl;
}

void primeReference(){  // reference to Larry Solomon's web site
    cout << "** Reference: Solomon, Larry. \"The Table of Pitch Class Sets.\" "
         << "In Larry Solomon, Musician & Scholar," << endl
         << "http://solomonsmusic.net/pcsets.htm (accessed November 7, 2015)." << endl;
}

int mod(int num, int sizeRange){    // make sure pitch classes are in the range of sizeRange (default: 12)
    if(num >= sizeRange)
        return mod(num - sizeRange, sizeRange); // keep subtracting sizeRange from input until it is in range
    else if(num < 0)
        return mod(num + sizeRange, sizeRange); // keep adding sizeRange to input until it is in range
    else
        return num;
}
/*
int modLoop(int num, int sizeRange){    //  same as mod() above, but use loop instead of recursion
    while(num >= sizeRange)
        num -= sizeRange;
    while(num < 0)
        num += sizeRange;
    return num;
}
*/
void insertionSort(int *ptArr, int arrSize){ // insertion sort of an array
    int temp;
    for(int i = 0; i < arrSize; i++){
        int j = i;
        while(j > 0 && *(ptArr + j) < *(ptArr + j - 1)){
            temp = *(ptArr + j);
            *(ptArr + j) = *(ptArr + j - 1);
            *(ptArr + j - 1) = temp;
            j--;
        }
    }
}

void insertionSortMulti(int arrMulti[LIMIT * 4][LIMIT * 4], int arrSize){  // insertion sort of a 2-D array
    for(int k = 0; k < arrSize * 4; k++){ // insertion sort of all normal sets
        int temp;
        for(int i = 0; i < arrSize; i++){
            int j = i;
            while(j > 0 && arrMulti[k][j] < arrMulti[k][j - 1]){
                temp = arrMulti[k][j];
                arrMulti[k][j] = arrMulti[k][j - 1];
                arrMulti[k][j - 1] = temp;
                j--;
            }
        }
    }
}

int pitchToNum(string pitch){   // convert pitch numbers/numbers from string to integer (0-11)
    if(pitch == "0" || pitch == "C" || pitch == "c" || pitch == "B#" || pitch == "b#")
        return 0;
    else if(pitch == "1" || pitch == "C#" || pitch == "c#" || pitch == "Db" || pitch == "db")
        return 1;
    else if(pitch == "2" || pitch == "D" || pitch == "d")
        return 2;
    else if(pitch == "3" || pitch == "D#" || pitch == "d#" || pitch == "Eb" || pitch == "eb")
        return 3;
    else if(pitch == "4" || pitch == "E" || pitch == "e" || pitch == "Fb" || pitch == "fb")
        return 4;
    else if(pitch == "5" || pitch == "E#" || pitch == "e#" || pitch == "F" || pitch == "f")
        return 5;
    else if(pitch == "6" || pitch == "F#" || pitch == "f#" || pitch == "Gb" || pitch == "gb")
        return 6;
    else if(pitch == "7" || pitch == "G" || pitch == "g")
        return 7;
    else if(pitch == "8" || pitch == "G#" || pitch == "g#" || pitch == "Ab" || pitch == "ab")
        return 8;
    else if(pitch == "9" || pitch == "A" || pitch == "a")
        return 9;
    else if(pitch == "10" || pitch == "A#" || pitch == "a#" || pitch == "Bb" || pitch == "bb")
        return 10;
    else if(pitch == "11" || pitch == "B" || pitch == "b" || pitch == "Cb" || pitch == "cb")
        return 11;
    else
        return -1;
}

string intToString(int num){   // convert an integer (0 - 11) to a string: 10 is A, 11 is B
    switch(num){
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "A";
        default: return "B";
    }
}

void inputInvalid(bool &check){ // input invalid warning
    check = false;
    cin.clear();    // clear input stream
    cin.ignore(MAXINT, '\n'); // ignore the max integer from input until '\n'
    cout << "INPUT INVALID--please try again..." << endl;
}

void inputRowLength(bool &check, int &length, int lim, string num){  // user input: how many pitches?
    do{
        check = true;
        cout << endl << "How many pitches would you like in your "
            << num << "row (1-" << lim << ")? ";
        cin >> length;
        if(length < 1 || length > lim || !cin)
            inputInvalid(check);
    }while(check == false);
}

void inputRow(bool &check, string in, int arr[LIMIT], int arrSize, string num){ // user input: what pitches?
    for(int i = 0; i < arrSize; i++){
        cout << "Enter your " << num << "row in pitches or numbers (" << i + 1 << "): ";
        do{
            check = true;
            cin >> in;
            arr[i] = pitchToNum(in);
            if(arr[i] == -1)
                inputInvalid(check);
        }while(check == false);
    }
}

void inputRow(bool &check, int arr[LIMIT], int arrSize){  // overloaded function for row input in normalize()
    for(int i = 0; i < arrSize; i++){
        cout << "Enter your row in any integers between -" << MAXINT
             << " and " << MAXINT << " (" << i + 1 << "): ";
        do{
            check = true;
            cin >> arr[i];
            if(arr[i] < -MAXINT || arr[i] > MAXINT || !cin)
                inputInvalid(check);
        }while(check == false);
    }
}

int rotationDirection(){    // determine the direction of rotation (default to left)
    char direction;
    do{
        valid = true;
        cout << endl << "Would you like to rotate to the left instead of to the right? (y/n): ";
        cin >> direction;
        if(!cin)
            inputInvalid(valid);
        else{
            switch(direction){
                case 'y':
                    return -1;
                case 'n':
                    return 1;
                default:
                    inputInvalid(valid);
            }
        }
    }while(valid == false);
    return 1;
}

void outputting(char &f, ofstream &outFile){  // output to a text file
    string fName;

    do{
        valid = true;
        cout << "Would you like to write to a file? (y/n): ";
        cin >> f;
        switch(f){
            case 'y':
                cout << "Enter a file name (to append, enter the name of the existing file): ";
                cin >> fName;
                outFile.open(fName.c_str(), ios::app);
                break;
            case 'n':
                break;
            default:
                inputInvalid(valid);
        }
    }while(valid == false);
}

void randomRow(){   // create a random tone row
    outputting(choice, outputFile);

    inputRowLength(valid, x);
    srand(unsigned(time(NULL)));
	for(int i = 0; i < x; i++)  // populate array with random numbers from 0-11
        row[i] = rand() % 12;

    programHeading("The Random Tone Row", 20);

    for(int i = 0; i < x; i++){    // print out the random row
		cout << TABLE[row[i]] << " ";
		if(choice == 'y')
            outputFile << TABLE[row[i]] << " ";
    }
    cout << endl << endl;

    if(choice == 'y'){
        outputFile << endl << endl << endl;
        outputFile.close();
    }
}

void normalize(){   // allow input of any integers to create a tone row
    outputting(choice, outputFile);

    inputRowLength(valid, x);
    inputRow(valid, row, x);

    programHeading("The Row", 8);

    for(int i = 0; i < x; i++){ // print out the final row
        cout << TABLE[mod(row[i])] << " ";
        // look up from the table and translate pitch numbers to pitch names
        if(choice == 'y')
            outputFile << TABLE[mod(row[i])] << " ";
    }
    cout << endl << endl;

    if(choice == 'y'){
        outputFile << endl << endl << endl;
        outputFile.close();
    }
}

void rowTable(){    // allow the use of a table other than the chromatic table
    outputting(choice, outputFile);

    cout << endl << "Enter a twelve-tone row in pitches or numbers "
        << "to create a reference table" << endl;
    inputRow(valid, input, row, 12);

    char answer;

    do{
        valid = true;
        cout << endl << "Use the same row as the reference table? (y/n)" << endl;
        // use the same row as a matrix mapped to a reference table
        cin >> answer;
        switch(answer){
            case 'y':   // if 'y', the row equals the table
                for(int i = 0; i < 12; i++)
                    row2[i] = row[i];
                break;
            case 'n':   // if 'n', enter a new row
                cout << "Enter your twelve-tone row in pitches or numbers to map to the reference table: ";
                inputRow(valid, input2, row2, 12);
                break;
            default:
                inputInvalid(valid);
        }
    }while(valid == false);

    programHeading("The Row", 8);

    for(int i = 0; i < 12; i++){ // print out the matrix table
        cout << TABLE[row[mod(row2[i])]] << " ";
        // look up from the table (row[i]) and translate pitch numbers to pitch names
        if(choice == 'y')
            outputFile << TABLE[row[mod(row2[i])]] << " ";
    }
    cout << endl << endl;

    if(choice == 'y'){
        outputFile << endl << endl << endl;
        outputFile.close();
    }
}

void matrix(){  // create a matrix
    outputting(choice, outputFile);

    inputRowLength(valid, x);
    inputRow(valid, input, row, x);

    tranTable[0] = 0;   // no transposition for first pitch
    for(int i = 1; i < x; i++)
    // initialize a transposition table to find distance between each pitch in the row
        tranTable[i] = row[i] - row[i - 1]; // start with subtracting 1st pitch from 2nd pitch

    programHeading("The Matrix", 11);

    int tranTableMatrix[LIMIT] = {0};
    // initialize a different transposition to find distance of each pitch from first pitch
    for(int i = 0; i < x; i++)
        tranTableMatrix[i] = mod(row[i] - row[0]);

    // print out the matrix table
	const string TABLE_NUM[12] = { "0 ", "1 ", "2 ", "3 ", "4 ", "5 ",
								   "6 ", "7 ", "8 ", "9 ", "10", "11" };
    cout << "     "; // print out I
    if(choice == 'y')
        outputFile << "     ";
    for(int i = 0; i < x; i++){
        cout << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
        if(choice == 'y')
            outputFile << "I" + TABLE_NUM[tranTableMatrix[i]] << " ";
    }
    cout << endl << endl;
    if(choice == 'y')
        outputFile << endl << endl;

    for(int i = 0; i < x; i++){
        cout << "P" + TABLE_NUM[mod(12 - tranTableMatrix[i])] << "  ";    // print out P
        if(choice == 'y')
            outputFile << "P" + TABLE_NUM[mod(12 - tranTableMatrix[i])] << "  ";

        for(int j = 0; j < x; j++){ // print body of matrix
            row[j] -= tranTable[i]; // minus to get transpositions of inversions
            cout << TABLE[mod(row[j])] << " ";
            // look up from the table and translate pitch numbers to pitch names
            if(choice == 'y')
                outputFile << TABLE[mod(row[j])] << " ";
        }

        cout << " R" + TABLE_NUM[mod(12 - tranTableMatrix[i])] << " ";    // print out R
        if(choice == 'y')
            outputFile << " R" + TABLE_NUM[mod(12 - tranTableMatrix[i])] << " ";

        cout << endl << endl;
        if(choice == 'y')
            outputFile << endl << endl;
    }

    cout << "     "; // print out RI
    if(choice == 'y')
        outputFile << "     ";
    for(int i = 0; i < x; i++){
        cout << "RI" + TABLE_NUM[tranTableMatrix[i]];
        if(choice == 'y')
            outputFile << "RI" + TABLE_NUM[tranTableMatrix[i]];
    }
    cout << endl << endl;
    if(choice == 'y'){
        outputFile << endl << endl << endl;
        outputFile.close();
    }
}

void matrixRotate(){  // matrix in rotation
    outputting(choice, outputFile);

    inputRowLength(valid, x);
    inputRow(valid, input, row, x);

    tranTable[0] = 0;   // no transposition for first pitch
    for(int i = 1; i < x; i++)
        tranTable[i] = row[i] - row[i - 1];
        // initialize a transposition table to find distance between each pitch in the row

    int direction = rotationDirection();

    programHeading("The Matrix in Rotation", (direction == 1) ? 31 : 30,
                (direction == 1) ? " (right)" : " (left)");

    // print out the matrix table
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++)
            row[j] -= tranTable[i]; // minus to get transpositions of inversions
        for(int j = 0; j < x; j++){
            cout << TABLE[mod(row[mod(j + i * direction, x)])] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            if(choice == 'y')
                outputFile << TABLE[mod(row[mod(j + i * direction, x)])] << " ";
        }

        cout << endl << endl;
        if(choice == 'y')
            outputFile << endl << endl;
    }

    if(choice == 'y'){
        outputFile << endl;
        outputFile.close();
    }
}

void multiTable(int sign, int range){   // multiplications of various types, with inversion/in rotation by 1 index
    outputting(choice, outputFile);

    inputRowLength(valid, x, LIMIT, "1st ");
    inputRow(valid, input, row, x, "1st ");
    inputRowLength(valid, y, LIMIT, "2nd ");
    inputRow(valid, input2, row2, y, "2nd ");

    tranTable[0] = 0;   // no transposition for first pitch
    for(int i = 1; i < y; i++)  // i start on second pitch (i = 1)
        tranTable[i] = row2[i] - row2[i - 1];   // initialize the transposition table

    int direction = 0;
    if(range == 0)  // only execute if range = 0 (rotation)
        direction = rotationDirection();

    programHeading(sign, range, direction, (direction == 1) ? " (right)" : " (left)");

    for(int i = 0; i < y; i++){ // print out the multiplication table
        for(int j = 0; j < x; j++)
            row[j] += tranTable[i] * sign; // plus or minus to transpositions of row2[i]
        for(int j = 0; j < x; j++){
            cout << TABLE[mod(row[mod(j + (i - i * range) * direction, x + range * 12)])] << " ";
            // look up from the table and translate pitch numbers to pitch names
            // j + i prints the rows in rotation, moving (rotating to right) in the value of i
            // if direction is -1, it rotates to left in the value of i
            // x prevents the row from going over the length of the original row
            // when range is 1, it cancels the rotation by subtraction, and set the limit larger than 12
            // when it is 0, it sets the range to x, thus rotation (j + i, x)
            if(choice == 'y')
                outputFile << TABLE[mod(row[mod(j + (i - i * range) * direction, x + range * 12)])] << " ";
        }
        cout << endl << endl;
        if(choice == 'y')
            outputFile << endl << endl;
    }

    if(choice == 'y'){
        outputFile << endl;
        outputFile.close();
    }
}

void primeSet(){
    outputting(choice, outputFile);

    inputRowLength(valid, x, 12);
    inputRow(valid, input, row, x);

    insertionSort(row, x);   // insertion sort of row[i]

    int multiRow[LIMIT * 4][LIMIT * 4] = {0}; // initialize a large 2-D array as a grid
    for(int i = 0; i < x; i++){ //populate the 2-D array with all transpositions of normal sets
        for(int j = 0; j < x; j++){
            multiRow[i][j] = mod(row[j] - row[i]);
            multiRow[i + x][j] = mod(row[j] - (12 - row[i]));
            multiRow[i + x * 2][j] = mod(12 - row[j] - row[i]);
            multiRow[i + x * 3][j] = mod(row[i] - row[j]);
        }
    }

    int smallest;
    for(int i = 0; i < x * 4; i++){ // reduce the normal sets to start at pitch 0
        smallest = 12;  // initialize smallest every times it loops back
        for(int j = 0; j < x; j++)
            // find smallest
            smallest = (multiRow[i][j] < smallest) ? multiRow[i][j] : smallest;
        for(int k = 0; k < x; k++)
            // subtract smallest from rows
            multiRow[i][k] -= smallest;
    }

    insertionSortMulti(multiRow, x);   // insertion sort of all normal sets

    int position = 0;
/*
    // this solution sometimes doesn't work; keep for reference only
    // 0 1 3 7 8 is wrong; the [x- 1] position is incorrect?
    // find position of the smallest outer, then 2nd, 3rd... pitches in the normal sets
    for(int i = 0; i < x * 4; i++){
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
    int posArr[LIMIT * 4] = {-1};   // store the smallest numbers from each column, default to -1
    smallest = 12;
    // find smallest pitch on last column of all rows
    for(int i = 0; i < x * 4; i++)
        smallest = (multiRow[i][x - 1] < smallest) ?
                    multiRow[i][x - 1] : smallest;
    // store the positions where the smallest outer pitch occurs
    // if the position's value is not the smallest, store -1
    for(int i = 0; i < x * 4; i++)
        posArr[i] = (multiRow[i][x - 1] == smallest) ? i : -1;

    int column = 1; // start the above process again on second pitch
    while(column < x - 1){
        smallest = 12;  // initialize smallest to 12 every time
        // find smallest pitch on each column
        for(int i = 0; i < x * 4; i++){
            if(posArr[i] >= 0)  // only check posArr[i] that are positive
                smallest = (multiRow[posArr[i]][column] < smallest) ?
                            multiRow[posArr[i]][column] : smallest;
        }
        // store the positions where the smallest 2nd pitch occurs
        // when the loop comes back, it finds smallest 3rd pitch, etc, but only on positions
        // where the PREVIOUS pitch is smallest
        for(int i = 0; i < x * 4; i++){
            if(posArr[i] >= 0)  // only check posArr[i] that are positive
                posArr[i] = (multiRow[posArr[i]][column] == smallest) ? i : -1;
        }
        column++;
    }

    for(int i = 0; i < x * 4; i++){ // find the final position
        if(posArr[i] >= 0)  // the list should consist of all -1 except for one, which stores the final position
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
    int sumArr[LIMIT * 4] = {0};
    for(int i = 0; i < x * 4; i++){ // find the sum of each row
        for(int j = 0; j < x; j++)
            sumArr[i] += multiRow[i][j];
    }
    for(int i = 0; i < x * 4; i++){
        // if the outer pitch in a row is the least, check the sum of all pitches
        // if the row is also the least; then it is the prime set
        position = (multiRow[i][x - 1] <= multiRow[position][x - 1]) ?
                   (sumArr[i] <= sumArr[position] ? i : position) : position;
    }
*/
    programHeading();
/*
    for(int i = 0; i < x * 4; i++){ // print out all the sets for checking
        for(int j = 0; j < x; j++){
            cout << multiRow[i][j] << " ";
            if(choice == 'y')
                outputFile << multiRow[i][j] << " ";
        }
        cout << endl;
        if(choice == 'y')
            outputFile << endl;
    }
*/
    cout << endl;
    if(choice == 'y')
        outputFile << endl;

    for(int i = 0; i < x; i++){ // print out the prime set (multiRow[position][i] only consist of integers)
        if(i == 0){
            cout << "(" << multiRow[position][i] << ", ";
            if(choice == 'y')
                outputFile << "(" << multiRow[position][i] << ", ";
        }else if(i < x - 1){
            cout << multiRow[position][i] << ", ";
            if(choice == 'y')
                outputFile << multiRow[position][i] << ", ";
        }else{
            cout << multiRow[position][i] << ")";
            if(choice == 'y')
                outputFile << multiRow[position][i] << ")";
        }
    }

    cout << endl << endl;
    if(choice == 'y')
        outputFile << endl << endl;

    int invertedPrime[12]= {0}; // find the inversion of the prime set
    for(int i = 0; i < x; i++) // inverse the prime set
        invertedPrime[i] = multiRow[position][x - 1] - multiRow[position][i];

    insertionSort(invertedPrime, x);   // insertion sort of invertedPrime[i]

    // convert prime sets from integer arrays into single strings
    string primeString = "";
    string invertedPrimeString = "";
    for(int i = 0; i < x; i++){
        primeString += intToString(multiRow[position][i]);
        invertedPrimeString += intToString(invertedPrime[i]);
    }

    // use text files as inputs to print out more information about the prime set
    bool found = false;
    string setNum, forteSetNum, primeSetNum, intervalVector, description;
    ifstream inFile, inFile2;
    inFile.open("setTable.txt");    // use setTable.txt to output information of the set
    inFile2.open("setTableDescription.txt");  // description

    if(!inFile){    // make sure the file is in the same directory
        cout << "The file \"setTable.txt\" is not found." << endl << endl;
        inFile.clear();
    }else{
        while(!inFile.eof()){   // process the txt file consisting of all Forte sets
            inFile >> setNum >> forteSetNum >> primeSetNum >> intervalVector;
            inFile.ignore(MAXINT, '\t');   // take out two tabs before the description
            inFile.ignore(MAXINT, '\t');
            getline(inFile, description);   // store the rest of the line as a string to description
            if(primeSetNum == primeString){
                found = true;
                break;  // break out of the loop if the set is found at current position
            }
        }

        // add symbols for printing
        primeSetNum = "(" + primeSetNum + ")";
        invertedPrimeString = "[" + invertedPrimeString + "]";
        intervalVector = "<" + intervalVector + ">";

        if(found == false){ // if not found, say it is not found
            cout << "Set does not match any Forte Prime Sets." << endl << endl;
            if(choice == 'y')
                outputFile << "Set does not match any Forte Prime Sets." << endl << endl;
        }else{
            cout << "Number: " << setNum << endl << "Forte Set-name: " << forteSetNum << endl
                 << "Prime Form: " << primeSetNum << endl << "Inversion: " << invertedPrimeString
                 << endl << "Interval Vector: " << intervalVector << endl << "Description: "
                 << description << endl << endl;
            if(choice == 'y')
                outputFile << "Number: " << setNum << endl << "Forte Set-name: " << forteSetNum << endl
                           << "Prime Form: " << primeSetNum << endl << "Inversion: " << invertedPrimeString
                           << endl << "Interval Vector: " << intervalVector << endl << "Description: "
                           << description << endl << endl;
        }

        if(choice == 'y'){
            outputFile << endl;
            outputFile.close();
        }

        inFile.close(); // close file after reading all data
        primeReference();
        cout << endl;
    }

    // read setTableDescription.txt
    char answer;
    do{
        valid = true;
        cout << "Would you like to read more? (y/n): ";
        cin >> answer;
        switch(answer){
            case 'y':
                cout << endl;
                if(!inFile2){   // make sure the file is in the same directory
                    cout << "The file \"setTableDescription.txt\" is not found." << endl;
                    inFile2.clear();
                }else{
                    while(!inFile2.eof()){  // read the entire file and print it out
                        getline(inFile2, description);
                        cout << description << endl;
                    }
                    inFile2.close();    // close file after reading all data
                    cout << endl;
                    primeReference();
                }
                break;
            case 'n':
                break;
            default:
                inputInvalid(valid);
        }
        cout << endl;
    }while(valid == false);
}

void primeTable(){  // print out the table of pitch class sets by Larry Solomon
    ifstream inFile, inFile2;
    inFile.open("setTable.txt");
    inFile2.open("setTableDescription.txt");

    string entireTable;

    valid = false;  // control printing of reference
    if(!inFile){   // make sure the file is in the same directory
        cout << "The file \"setTable.txt\" is not found." << endl << endl;
        inFile.clear();
    }else{
    	while(!inFile.eof()){  // read the entire file and print it out
            getline(inFile, entireTable);
            cout << entireTable << endl;
        }
        inFile.close();    // close file after reading all data
        cout << endl;
        valid = true;
    }

    if(!inFile2){   // make sure the file is in the same directory
        cout << "The file \"setTableDescription.txt\" is not found." << endl << endl;
        inFile2.clear();
    }else{
        while(!inFile2.eof()){  // read the entire file and print it out
            getline(inFile2, entireTable);
            cout << entireTable << endl;
        }
        inFile2.close();    // close file after reading all data
        cout << endl;
        valid = true;
    }

    if(valid == true){
        primeReference();
        cout << endl;
    }
}
