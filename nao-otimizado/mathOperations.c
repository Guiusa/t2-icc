// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "mathOperations.h"

//Gera a função que será passada para libmatheval como forma de string
//Func1 é o limite do primeiro somatório e func2 do segundo
void generateStringFunction (char *funcString, int func1, int func2) {
    char stringAux[STR_SIZE_LIMIT];
	strcpy(stringAux, "");
	
    for (int i = 1; i <= func1; i++) {
        snprintf(stringAux, 25, "(x%d-(", i);
        strcat(funcString, stringAux);
        for (int j = 1; j <= func2; j++) {
            if (j != func2) {
                snprintf(stringAux, 25, "(x%d)^%d+" , i+j, j);
                strcat(funcString, stringAux);
            } else {
                snprintf (stringAux, 25, "(x%d)^%d" , i+j, j);
                strcat(funcString, stringAux);
            }
        }
        if (i != func1) {
            snprintf(stringAux, 25, "))^2+");
            strcat(funcString, stringAux);
        } else {
            snprintf(stringAux, 25, "))^2");
            strcat(funcString, stringAux);            
        }
    }

    return;
}

//Usa a libmatheval para pegar cada derivada secundária e calcular seu valor
//Com o vetor das variáveis
void createHessCoefficientsMatrix (void ***secondDerivatives, double **hessMatrix, char **names, int count, double *Xvector) {
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            hessMatrix[i][j] = evaluator_evaluate(secondDerivatives[i][j], count, names, Xvector);
    
    return;
}

//Usa a libmatheval para pegar cada derivada primária e calcular seu valor
void evalueteFirstDerivatives (void **firstDerivatives, double* frstDerivEval, char **names,
int count, double *Xvector){
	for(int i = 0; i<count; i++)
		frstDerivEval[i] = evaluator_evaluate(firstDerivatives[i], count, names, Xvector);
	return;
}

//Calcula a norma do vetor
double norm (double *vet, int n) {
    double max = fabs(vet[0]);
    
    for (int i = 1; i < n; i++) {
        if (fabs(vet[i]) > max)
            max = fabs(vet[i]);
    }

    return max;
}

//Soma X anterior a delta
void calcNewX (double *Xvector, double *delta, int n) {
    for (int i = 0; i < n; i++)
        Xvector[i] += delta[i];
}

//Faz todas as operações do método QuasiNewton como especificado nos comentários
void iterQuasiNewton(double **hess, double* derivEval, double* lastDerivEval, double *delta, double* x, int n){
	//calcula qk:
	double *qk = malloc(sizeof(double) * n);
	for(int i = 0; i<n; i++)
		qk[i] = derivEval[i] - lastDerivEval[i];
	//pk * pkT
	double **pkMatrix = multiplyColumnLine(delta, delta, n);
	//pkT*pk e depois divide a matriz pelo escalar
	double pkEscalar = multiplyLineColumn(delta, qk, n);
	divideMatrixEscalar(pkMatrix, pkEscalar, n);
	
	//Hk * qk * (qk)T * Hk
	double *hessXqk = multiplyMatrixColumn(hess, qk, n);
	double **columnXqkT = multiplyColumnLine(hessXqk, qk, n); 
	double **partial = multiplyMatrix(columnXqkT, hess, n);
	//(qk)T * Hk * qk
	double *qkTHk = multiplyLineMatrix(qk, hess, n);
	double escalar = multiplyLineColumn(qkTHk, qk, n);
	// PAssa-se o escalar negativo porque na função essa matriz deve ser
	//subtraída, dessa forma todos os elementos tem sinal trocado e pode-se 
	//realizar uma soma com resultado igual
	divideMatrixEscalar(partial, -escalar, n);

	double **deltaHess = summMatrix(partial, pkMatrix, n);
	double **final = summMatrix(hess, deltaHess, n);
	copy_matrixes(final, hess, n);

	freeDoubleMatrix(n, final);
	freeDoubleMatrix(n, deltaHess);
	freeDoubleMatrix(n, partial);
	free(qkTHk);
	free(hessXqk);
	free(qk);
	freeDoubleMatrix(n, pkMatrix);
	freeDoubleMatrix(n, columnXqkT);
}
