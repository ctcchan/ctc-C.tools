#ifndef PROGRAMS_H_
#define PROGRAMS_H_

class Programs {
public:
    void randomRow(Printer &print, Modules &module);   // generate a row of random pitches
    void normalize(Printer &print, Modules &module);   // allow input of any integers to create a tone row
    void rowTable(Printer &print, Modules &module);    // allow the use of a table other than the chromatic table
    void matrix(Printer &print, Modules &module);  // create a matrix
    void matrixRotate(Printer &print, Modules &module);  // matrix in rotation
    void multiTable(Printer &print, Modules &module, int sign, int range);   // multiplications of various types, with inversion/in rotation
    void primeSet(Printer &print, Modules &module); // find the prime set of a given set
    void primeTable(Printer &print);  // print out the table of pitch class sets by Larry Solomon
    void permuteTable(Printer &print, Modules &module);	// find all permutations of a given set
    void subsetsTable(Printer &print, Modules &module);	// find all subsets of a given set
};

#endif
