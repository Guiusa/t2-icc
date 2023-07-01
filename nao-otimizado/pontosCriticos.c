// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "matrixOperations.h"
#include "mathOperations.h"
#include "iolib.h"
#include "time.h"

int main (int argc, char **argv) {
	//Declaração das variáveis do programa
	FILE* output = NULL;
	int desviarSaida = 0;
	int retorno = 0;
    int n, k, func1, func2 , count, maxIter, execNewMod, hessSteps;
    char *funcString;
    void *func;
    void **firstDerivatives;
    void ***secondDerivatives;
    char **variableNames;
    double xInitial, epsilon;
    double *xVecNewMod, *yNewMod, *deltaNewMod;
    double *derivEvalNewMod;
	double **hessNewMod, **l_NewMod, **u_NewMod;
	
	clock_t start_time, end_time;
	double total_time;

    int r = scanf ("%d %d %lf %lf %d %d" , &n, &k, &xInitial, &epsilon, &maxIter, &hessSteps);
	//Se n e k não forem válidos, retorna erro e para execução
	if(k%2==0 || k<3){
		returnsError("Valor de n e k inviabilizam a execução do programa", "");
		return 1; 
	}
	//Testa se deve desviar a saída para arquivo
	if(argc == 3 && !strcmp(argv[1], "-o")){
		desviarSaida = 1;
		output = fopen(argv[2], "w");
		if(output == NULL){
			returnsError("Não foi possível abrir o arquivo %s\n", argv[2]);
			return 2;
		}
	}

	//Limites superiores em cada somatório
    func1 = (n - (k/2));
	func2 = k/2;

	//Bloco para alocar e inicializar todas as variáveis dinâmicas
	funcString 			= malloc(100 * func1 * func2 * sizeof(char));
	strcpy(funcString, "");
	xVecNewMod 			= malloc (sizeof(double) * n);
	copyInitialVector(n, xInitial, xVecNewMod);
	yNewMod				= malloc (sizeof(double) * n);
	deltaNewMod			= malloc (sizeof(double) * n);
	firstDerivatives 	= malloc (sizeof(void*) * n);
	derivEvalNewMod		= malloc (sizeof(double) * n);
	secondDerivatives 	= createVoidMatrix(n);
	hessNewMod 			= createDoubleMatrix(n);
	l_NewMod 			= createDoubleMatrix(n);
	u_NewMod			= createDoubleMatrix(n);

	start_time = clock();
	
	//Cria a string que descreve a função para a libmatheval
	generateStringFunction(funcString, func1, func2);
	//Atribui o buffer para func com a função da libmatheval
    func = evaluator_create(funcString);
    assert(func);
    //coloca as variáveis da função no vetor variableNames e quantidade delas em count
    evaluator_get_variables(func, &variableNames, &count);

    //cria o vetor de derivadas primeiras e guarda o valor calculado em frstDerivEval
    for (int i = 0; i < count; i++)
        firstDerivatives[i] = evaluator_derivative(func, variableNames[i]);

    //cria a matriz de derivadas secundárias
    for (int i = 0; i < count; i++) 
		for (int j = 0; j < count; j++)
    		secondDerivatives[i][j] = evaluator_derivative(firstDerivatives[i], variableNames[j]);

	for (int i = 0; i < maxIter; i++) {
		evalueteFirstDerivatives(firstDerivatives, derivEvalNewMod, variableNames, count, xVecNewMod);
		// se a norma das derivadas primeiras for menor que o epsilon, quebra o laço
		//printf("%d\t%f\n", i, norm(derivEvalNewMod, n));
		if (norm(derivEvalNewMod, n) < epsilon)
			break;

		// limita a atualização da matriz de coeficientes da hessiana de acordo com os hess steps
		//Calcula a hessiana e faz a fatoração L e U
		if (! (i%hessSteps)){
			createHessCoefficientsMatrix(secondDerivatives, hessNewMod, variableNames, count, xVecNewMod);
			copy_matrixes(hessNewMod, u_NewMod, n);
			gen_l_u(derivEvalNewMod, l_NewMod, u_NewMod, n);
		}

		//Gera o y que é L*y = frstDeriv
		get_yc(yNewMod, derivEvalNewMod, l_NewMod, n);

		//Se tem 0 na diagonal principal, a matriz é impossível e o programa para
		if (! mul_yu(yNewMod, u_NewMod, deltaNewMod, n)){
			returnsError("Função gerada causa um sistema com solução impossível", "");
			retorno = 3;
			goto liberar;		
		}
	
		if (norm(deltaNewMod, n) < epsilon)
			break;

		//calcula o novo valor do vetor de X+1
		calcNewX(xVecNewMod, deltaNewMod, n);
		
		printStep(output, func, n, variableNames, xVecNewMod, i);
	
	}
	end_time = clock();

	total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC * 1000;

	printf("Tempo Decorrido em milisegundos:%lf\n" , total_time);

	//Libera todas as variáveis dinâmicas
	liberar:
	evaluator_destroy(func);
    free(xVecNewMod);
	free(yNewMod);
	free(deltaNewMod);
	free(derivEvalNewMod);
	freeVoidVector(n, firstDerivatives);
	freeVoidMatrix(n, secondDerivatives);
	freeDoubleMatrix(n, hessNewMod);
	freeDoubleMatrix(n, l_NewMod);
	freeDoubleMatrix(n, u_NewMod);
    free(funcString);
	if(desviarSaida) fclose(output);
	return retorno;
}
