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
        int getRow(int rowColumn, int rowType);
        void setRow(int rowColumn, int rowPitch, int rowType);
        int getMultiRow(int rowColumn, int rowRow);
        void setMultiRow(int rowColumn, int rowRow, int rowPitch);
        int getRowSize(int rowType);
        void setRowSize(int x, int rowType);
        void sortRow(int choice);
        int mod(int num, int rangeSize = 12);
        //int modRecur(int num, int rangeSize = 12);
        void swap(int &a, int &b);
        int pitchToNum(string pitch);
        int charToNum(char pitch);
        string intToString(int num);
        void permute(string soFar, string rest, int arrSize, char out, ofstream &outFile);
        void subsets(string soFar, string rest, char out, ofstream &outFile);
        void inputInvalid(bool &check);
        void generateTwelve(int rType);
        void inputRowLength(int rType, int lim = 50, string num = "");
        void inputRow(int rType, string num = "");
        void inputRowNor();
        void transposition(int rType);
        void populateRow(bool fixed, int rType, string prompt);
        int rotationDirection();
        void outputting(char &f, ofstream &outFile);
};

#endif
