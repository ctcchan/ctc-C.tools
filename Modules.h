#ifndef MODULES_H_
#define MODULES_H_

void fillDisplay(char sym, int num);
void newLines(char out, ofstream &outFile);
void heading();
void menu();
void programHeading(string program, int filling, char out, ofstream &outFile, string addString = "");
void programHeading(int s, int r, int d, int arrSize, int arrSize2, int r1[50], int r2[50], char out, ofstream &outFile, string addString = "");
void programHeading(int arrSize, int r[50], char out, ofstream &outFile);
void primeReference();
void programCalling(int m);
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

#endif
