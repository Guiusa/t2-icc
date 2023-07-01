// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "iolib.h"

//printar a matriz de doubles
void printDoubleMatrix(double** m, int s){
	for(int i = 0; i<s; i++){
		for(int j = 0; j<s; j++)
			printf("%1.5f ", m[i][j]);
		printf("\n");
	}
}

void printDoubleVector(double *v, int s){
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++)
			printf("%1.5f ", v[(i * s) + j]);
		printf("\n");
	}
}

//Printa um erro com background vermelho e o uso correto com o fundo verde, Se 
// o uso não for necessário passa-se a string "" e nada é printado
void returnsError(char* err, char* usg){
	printf("\033[1;41mERROR: %s\033[0m\n", err);
	if(strcmp(usg, ""))
		printf("\033[1;42mUSAGE: %s\033[0m\n", usg);
}

void printStep(FILE* output, void *func, int count, char **names, double *xVecNewMod, int iter){
	double rNewMod = evaluator_evaluate(func, count, names, xVecNewMod);
	
	if(output == NULL){
		printf("%d\t|\t", iter);
		printf("%1.25lf", rNewMod);
		printf("\n");
	}
	else {
		fprintf(output, "%d\t|\t", iter);
		fprintf(output, "%1.25lf", rNewMod);
		fprintf(output, "\n");
	}
}

void generalPrint(int n, int iter, double **hess, double **L, double **U, double *frstDerivEval, double *y, double *delta, double *xVector){
	printf("RESULTADOS PARA A ITERAÇÃO %d:\n", iter);
	printf("Derivadas primeiras calculadas:\n");
	printDoubleVector(frstDerivEval, n);
	printf("\nHessiana:\n");
	printDoubleMatrix(hess, n);
	printf("\nL:\n");
	printDoubleMatrix(L, n);
	printf("\nU:\n");
	printDoubleMatrix(U, n);
	printf("\ny da fatoração:\n");
	printDoubleVector(y, n);
	printf("\nDelta calculado:\n");
	printDoubleVector(delta, n);
	printf("\nxVector:\n");
	printDoubleVector(xVector, n);
	printf("\n");
	for(int i = 0; i<80; i++) printf("#");
	printf("\n");	
}
