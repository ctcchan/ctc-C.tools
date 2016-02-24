#ifndef MODULES_H_
#define MODULES_H_

class Modules {
        int row[50];
        int row2[50];
        int rowLarge[10000];
        int tranTable[50];
        int rowPrime[12];
        int rowMulti[48][48];
        int rowSize;
        int rowSize2;
        void sorting(int choice) { // private sorting function; use sortRow(int) to activate this function
            if (choice == 1){
                for (int i = 0; i < rowSize; i++) { // insertion sort of rowPrime
                    int j = i;
                    while (j > 0 && rowPrime[j] < rowPrime[j - 1]) {
                        swap(rowPrime[j], rowPrime[j - 1]);
                        j--;
                    }
                }
            } else {
                for (int k = 0; k < rowSize * 4; k++) { // insertion sort of all normal sets
                    for (int i = 0; i < rowSize; i++) {
                        int j = i;
                        while (j > 0 && rowMulti[k][j] < rowMulti[k][j - 1]) {
                            swap(rowMulti[k][j], rowMulti[k][j - 1]);
                            j--;
                        }
                    }
                }
            }
        }
    public:
        Modules() : rowSize(0), rowSize2(0) {  } // default constructor
        int getRow(int rowColumn, int rowType); // get the pitch from current column in the row
        void setRow(int rowColumn, int rowPitch, int rowType); // set the pitch from current column in the row
        int getMultiRow(int rowColumn, int rowRow); // get the pitch from current column in the multirow
        void setMultiRow(int rowColumn, int rowRow, int rowPitch); // set the pitch from current column in the multirow
        int getRowSize(int rowType); // get the size of row
        void setRowSize(int x, int rowType); // set the size of the row
        void sortRow(int choice); // access insertion sort private function
        int mod(int num, int rangeSize = 12);	// make sure pitch classes are in the range of sizeRange (default: 12)
        //int modRecur(int num, int rangeSize = 12); // same as Modules::mod() above, use recursion instead of loop; stack-overflow
        void swap(int &a, int &b);	// swap a and b
        int pitchToNum(string pitch); // convert pitch numbers/numbers from string to integer (0-11)
        int charToNum(char pitch);    // convert a char to a pitch number: A is 10, B is 11
        string intToString(int num);   // convert an integer (0 - 11) to a string: 10 is A, 11 is B
        void permute(string soFar, string rest, int arrSize, char out, ofstream &outFile);	// print out a permutation table of a given set
        void subsets(string soFar, string rest, char out, ofstream &outFile);	// print out all subsets of a given set
        void inputInvalid(bool &check); // input invalid warning
        void generateTwelve(int rType);    // populate an array with a random twelve-tone row
        void inputRowLength(int rType, int lim = 50, string num = "");  // user input: how many pitches?
        void inputRow(int rType, string num = ""); // user input: what pitches?
        void inputRowNor(); // input for normalize()
        void transposition(int rType);	// make a transposition table
        void populateRow(bool fixed, int rType, string prompt);	// populate an array
        int rotationDirection();    // determine the direction of rotation (default to right)
        void outputting(char &f, ofstream &outFile);  // output to a text file
        ~Modules() {  } // destructor to free up memory
};

#endif
