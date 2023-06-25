// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrixOperations.h"
#include "iolib.h"
#include "mymatheval.h"
#define STR_SIZE_LIMIT 25

void generateStringFunction (char *funcString, int func1, int func2);

void createHessCoefficientsMatrix (void ***secondDerivatives, double **hessMatrix, char **names, int count, double *Xvector);
void createHessCoefficientsMatrixD (void ***secondDerivatives, m_diag *hessMatrix, char **names, int count, double *Xvector);


void evalueteFirstDerivatives (void **firstDerivatives, double* frstDerivEval, char **names, int count, double *Xvector);

double norm (double *vet, int n);

void calcNewX (double *Xvector, double *delta, int n);

void iterQuasiNewton(double **hess, double* derivEval, double* lastDerivEval, double *delta, double* x, int n);
