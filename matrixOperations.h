// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "mymatheval.h"


//estrutura que armazena o vetor de doubles de cada diagonal. A variável de
//tamanho serve para armazenar quantos elementos foram inseridos no vetor
typedef struct {
	double *vet;
	int tam;
} t_vet;

//a matriz é k diagonal, de forma que a diagonal principal tem k elementos, e 
//cada diagonal subsequente tem k-g elementos, onde g é o tamanho do gap.
// exemplo: com k igual a 3, diags tem 1 vetor com 3 elementos e 2 com 2 elems
typedef struct{
	t_vet *diags;
	int k;
} m_diag;

m_diag* createDoubleMatrixD(int n, int k);

void freeDoubleMatrixD(m_diag* m);

double** createDoubleMatrix (int n);

void*** createVoidMatrix (int n);

char ** createVariableNamesVector(int n);

void freeVariableNamesVector (int n, char **vector);

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

void gen_l_u(double **l, double **u, int s);

void get_yc(double* y, double *frstDeriv, double **l, int s);

int mul_yu(double* y, double** u, double* delta, int s);
