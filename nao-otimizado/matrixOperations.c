// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "matrixOperations.h"

// Aloca uma matriz de n*n doubles
double** createDoubleMatrix (int n) {
    double **matrix = malloc (sizeof(double*) * n);

    for (int i = 0; i < n; i++)
        matrix[i] = malloc (sizeof(double) * n);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    
    return matrix;
}

// aloca uma matriz de n*n ponteiros pra void, usados pela libmatheval
void*** createVoidMatrix (int n) {
	void ***matrix = malloc (sizeof(void**) * n);
    for (int i = 0; i < n; i++)
        matrix[i] = malloc(sizeof(void*) * n);
    return matrix;
}

//libera espaço de uma matriz de doubles
void freeDoubleMatrix (int n, double **matrix) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    
    free(matrix);
}

//libera espaço da matriz de ponteiros pra void
void freeVoidMatrix (int n, void ***matrix) {
    for (int i = 0; i < n; i++){
		for(int j=0; j<n; j++)
			evaluator_destroy(matrix[i][j]);
		free(matrix[i]);
	}
    free(matrix);
}

//libera espaço dos objetos da libmatheval
void freeVoidVector(int n, void** v){
	for (int i=0; i<n; i++)
		evaluator_destroy(v[i]);
	free(v);
}

//copia o valor incial dado para todas as variáveis da função
void copyInitialVector (int n, double num, double *vector) {
    for (int i = 0; i < n; i++)
        vector[i] = num;

    return;
}

char ** createVariableNamesVector (int n) {
	char **aux = (char**) malloc (sizeof(char *) * n);

	for (int i = 0; i < n; i ++)
		aux[i] = (char*) malloc (sizeof(char) * 25);
	
	return aux;
}

void freeVariableNamesVector (int n, char **vector) {
	for (int i = 0; i < n; i++)
		free(vector[i]);
	
	free(vector);
}

//copia a matriz a dentro da matriz b
void copy_matrixes(double **a, double **b, int s){
	for(int i = 0; i<s; i++)
			for(int j = 0; j<s; j++)
					b[i][j] = a[i][j];
	return;
}

//copia o vetor b no vetor a
void copyDoubleVector (double *a, double *b, int s){
	for (int i = 0; i<s; i++)
		a[i] = b[i];
}

//soma as matrizes a e b e retorna alocada
double** summMatrix(double **a, double **b, int s){
	double **r = createDoubleMatrix(s);
	for(int i = 0; i<s; i++)
		for(int j = 0; j<s; j++)
			r[i][j] = a[i][j] + b[i][j];

	return r;			
}

//multiplica a matriz m pelo vetor coluna c e devolve o vetor coluna r alocado
double* multiplyMatrixColumn(double **m, double* c, int s){
	double *r = malloc(s * sizeof(double));
	double summ = 0.0f;
	for (int i = 0; i<s; i++){
		for(int j = 0; j<s; j++)
			summ += m[i][j] * c[j];
		r[i] = summ;
		summ = 0.0f;		
	}
	return r;
}

//multiplica a matriz coluna c pela matriz linha l e retorna na matriz n*n r
double** multiplyColumnLine(double *c, double* l, int s){
	double** r = createDoubleMatrix(s);
	for(int i = 0; i<s; i++)
		for(int j = 0; j<s; j++)
			r[i][j] = c[i]*l[j];
	return r;
}

//Multiplica a matriz linha l pela matriz m e retorna a matriz linha r alocada
double* multiplyLineMatrix(double *l, double** m, int s){
	double *r = malloc(sizeof(double) * s);
	double summ = 0.0f;
	for (int i = 0; i<s; i++){
		for(int j = 0; j<s; j++){
			summ += l[j] * m[i][j];
		}
		r[i] = summ;
		summ = 0.0f;
	}
	return r;
}

//Multiplica a matriz linha l pela matriz coluna c e retorna o escalar
double multiplyLineColumn(double *c, double *l, int s){
	double summ = 0;
	for (int i = 0; i<s; i++)
		summ += l[i] * c[i];
	return summ;
}

//divide toda a matriz m pelo valor em escalar
void divideMatrixEscalar(double **m, double escalar, int s){
	if(!escalar) return;

	for (int i = 0; i<s; i++)
		for(int j = 0; j<s; j++)
			m[i][j] /= escalar;
	return;
}

//multiplica a matriz a por b e retorna em r já alocado
double** multiplyMatrix(double **a, double **b, int s){
	double** r = createDoubleMatrix(s);
	double summ = 0.0f;
	for(int i = 0; i<s; i++){
		for(int j = 0; j<s; j++){
			for(int k = 0; k<s; k++)
				summ += a[i][k] * b[k][j];
			r[i][j] = summ;
			summ = 0.0f;
		}
	}
	return r;
}

//Faz o pivoteamento parcial na fatoração LU, não inclusa no arquivo .h
int switch_pivot(double *frstDerivEval, double **u, int s, int j){
	int big = j;
	for (int i = j; i<s; i++)
		if(fabs(u[i][j]) > fabs(u[j][j]))
			big = i;

	if (u[big][j] == 0)
		return 0;

	if(big == j) return 1;

	double *auxP = u[big];
	u[big] = u[j];
	u[j] = auxP;
	
	double aux = frstDerivEval[big];
	frstDerivEval[big] = frstDerivEval[j];
	frstDerivEval[j] = aux;

	return 1;
}

//coloca o valor 1 na diagonal principal da matriz l
void initial_l(double **l, int s){
	for(int i = 0; i<s; i++)
		l[i][i] = 1;
}

//realiza a fatoração lu da matriz hessiana
void gen_l_u(double* frstDerivEval, double **l, double **u, int s){
	initial_l(l, s);
	for(int j = 0; j<s; j++){
		//Se nenhum elemento for maior que 0, para a execução da fatoração			
		//if(! switch_pivot(frstDerivEval, u, s, j))
		//			return;
		

		//Para cada linha embaixo da diagonal, realiza os paços da fatoração LU
		for(int i = j+1; i<s; i++){
			double mp = u[i][j] / u[j][j];
			l[i][j] = mp;

			u[i][j] = 0;
			for(int jp=j+1; jp<s; jp++)
				u[i][jp] = u[i][jp] - (u[j][jp] * mp);
		}		
	}

	return;
}

//Realiza o primeiro passo da multiplicação com L e U
void get_yc(double* y, double *frstDeriv, double **l, int s){
	for(int i = 0; i<s; i++){
		y[i] = -frstDeriv[i];
		for(int j = 0; j<i; j++)
			y[i] -= l[i][j]*y[j];
	}
	return;
}

//Realiza o segundo passo da multiplicação com L e U
int mul_yu(double* y, double** u, double* delta, int s){
	for(int i = s-1; i>=0; i--){
		//caso haja um 0 na diagonal principal, sistema é impossível
		if(u[i][i] == 0)
			return 0;
		delta[i] = y[i];
		for(int j = i+1; j<s; j++)
			delta[i] -= u[i][j]*delta[j];
		delta[i] /= u[i][i];
	}	
	return 1;
}
