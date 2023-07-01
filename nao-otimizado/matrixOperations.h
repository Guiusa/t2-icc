// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <matheval.h>
#include <math.h>

double** createDoubleMatrix (int n);

void*** createVoidMatrix (int n);

void freeDoubleMatrix (int n, double **matrix);

void freeVoidMatrix (int n, void ***matrix);

void freeVoidVector(int n, void** v);

void copyInitialVector (int n, double num,double *vector);

void copyDoubleVector (double *a, double *b, int s);

void copy_matrixes(double **a, double **b, int s);

double** multiplyMatrix(double **a, double **b, int s);

double* multiplyMatrixColumn(double **m, double* c, int s);

double* multiplyLineMatrix(double *l, double** m, int s);

double** multiplyColumnLine(double *c, double* l, int s);

double multiplyLineColumn(double *c, double *l, int s);

double** summMatrix(double **a, double **b, int s);

void divideMatrixEscalar(double **m, double escalar, int s);

void gen_l_u(double* frstDerivEval, double **l, double **u, int s);

void get_yc(double* y, double *frstDeriv, double **l, int s);

int mul_yu(double* y, double** u, double* delta, int s);
