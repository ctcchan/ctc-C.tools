#ifndef MODULES_H_
#define MODULES_H_

class Modules {
    public:
        void programCalling(Printer print, Modules &module, int m);
        int mod(int num, int rangeSize = 12);
        //int modRecur(int num, int rangeSize = 12);
        void swap(int &a, int &b);
        void insertionSort(int arrSize, int *ptArr);
        void insertionSortMulti(int arrSize, int arrMulti[48][48]);
        int pitchToNum(string pitch);
        int charToNum(char pitch);
        string intToString(int num);
        void permute(string soFar, string rest, int arrSize, char out, ofstream &outFile);
        void subsets(string soFar, string rest, char out, ofstream &outFile);
        void inputInvalid(bool &check);
        void generateTwelve(int arr[50]);
        int inputRowLength(int lim = 50, string num = "");
        void inputRow(int arrSize, int arr[50], string num = "");
        void inputRowNor(int arrSize, int arr[50]);
        void transposition(int tran[50], int arrSize, int r[50]);
        void populateRow(bool fixed, int &arrSize, int arr[50], string prompt);
        int rotationDirection();
        void outputting(char &f, ofstream &outFile);
};

#endif