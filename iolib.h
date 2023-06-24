// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include <stdio.h>
#include <string.h>
#include "mymatheval.h"
//#include <matheval.h>

void printDoubleMatrix(double** m, int s);

void printDoubleVector(double *v, int s);

void returnsError(char* err, char* usg);

void printStep(FILE* output, void *func, int count, int execNewMod, char **names, double *xVecNewMod, int iter);

void generalPrint(int n, int iter, double **hess, double **L, double **U, double *frstDerivEval, double *y, double *delta, double* xVector);
