#ifndef PROGRAMS_H_
#define PROGRAMS_H_

class Programs {
    public:
        void randomRow(Printer &print, Modules &module);
        void normalize(Printer &print, Modules &module);
        void rowTable(Printer &print, Modules &module);
        void matrix(Printer &print, Modules &module);
        void matrixRotate(Printer &print, Modules &module);
        void multiTable(Printer &print, Modules &module, int sign, int range);
        void primeSet(Printer &print, Modules &module);
        void primeTable(Printer &print);
        void permuteTable(Printer &print, Modules &module);
        void subsetsTable(Printer &print, Modules &module);
};

#endif
