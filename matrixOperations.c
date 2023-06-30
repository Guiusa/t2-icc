// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "matrixOperations.h"


//aloca uma matrix k-diagonal
	m_diag* createDoubleMatrixD(int n, int k){
	m_diag* tmp = (m_diag*) malloc(sizeof(m_diag));
	tmp->diags = malloc(k * sizeof(t_vet));
	tmp->k = k;
	int gap;
	int i = 0;
	for(gap = -k/2; gap<=k/2; gap++, i++) {
		tmp->diags[i].vet = (double*) malloc((n-abs(gap)) * sizeof(double));
		tmp->diags[i].tam = 0;
	}
	return tmp;
}

//libera uma matriz k-diagonal
void freeDoubleMatrixD(m_diag *m){
	for(int i = 0; i<m->k; i++)
		free(m->diags[i].vet);
	free(m->diags);
	free(m);
}

//printa matriz diagonal
void printMatrixDiag(m_diag* m){
	for(int i = 0; i<m->k; i++){                                                  
   t_vet* tmp = &m->diags[i];                                                   
     for(int j = 0; j<tmp->tam; j++)                                             
       printf("%.4lf ", tmp->vet[j]);                                            
       printf("\n");                                                               
   }
}

void zeroMatrixDiag(m_diag* m){
	for(int i = 0; i<m->k; i++)
		m->diags[i].tam = 0;
}

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

//libera espaço de uma matriz de doubles
void freeDoubleMatrix (int n, double **matrix) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    
    free(matrix);
}

//libera espaço da matriz de ponteiros pra void
void freeVoidMatrix (int n, void ***matrix) {
    for (int i = 0; i < n; i++){
		//for(int j=0; j<n; j++)
			//evaluator_destroy(matrix[i][j]);
		free(matrix[i]);
	}
    free(matrix);
}

//libera espaço dos objetos da libmatheval
void freeVoidVector(int n, void** v){
	//for (int i=0; i<n; i++)
		//evaluator_destroy(v[i]);
	free(v);
}

//copia o valor incial dado para todas as variáveis da função
void copyInitialVector (int n, double num, double *vector) {
    for (int i = 0; i < n; i++)
        vector[i] = num;

    return;
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

//coloca o valor 1 na diagonal principal da matriz l
void initial_l(double **l, int s){
	for(int i = 0; i<s; i++)
		l[i][i] = 1;
}

//realiza a fatoração lu da matriz hessiana
void gen_l_u(double **l, double **u, int s){
	initial_l(l, s);
	for(int j = 0; j<s; j++){
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

void initial_u(double** u, m_diag* h, int s){
	zeroMatrixDiag(h);
	int k = h->k;
	int win_start = k/2;
	int win_end = win_start + k/2;
	int mat_start = 0;
	int mat_end = k/2;
	int t = win_end - win_start;
	int i;
	t_vet* tmp;
	for(i = 0; i < k/2; i++){
		for(int j = mat_start; j<=mat_end; j++){
			tmp = &h->diags[win_start+j];
			u[i][j] = tmp->vet[tmp->tam];
			tmp->tam ++;
		}
		mat_end++;
		win_start--;
	}
	for(; i<s-k/2; i++){
		for(int j = mat_start; j<=mat_end; j++){
			tmp = &h->diags[win_start+j];
			u[i][j] = tmp->vet[tmp->tam];
			tmp->tam++;
		}
	}
	for(; i<s; i++){
		win_end--;
		mat_start++;
		for(int j = mat_start; j<=mat_end; j++){
			tmp = &h->diags[win_start+j-mat_start];
			u[i][j] = tmp->vet[tmp->tam];
			tmp->tam++;
		}	
	}

}


void gen_l_u_diag(m_diag *m, double** l, double** u, int s){
	initial_l(l, s);
	initial_u(u, m, s);
	int k = m->k;
	int princ = k/2;
	int aux1 = princ;
	int j;	

	gen_l_u(l, u, s);
	
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
