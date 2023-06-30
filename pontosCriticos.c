// Planejado e desenvolvido por
// Guiusepe Oneda Dal Pai - GRR20210572
// Fernando Gbur dos Santos - GRR20211761
#include "mathOperations.h"
#include "iolib.h"

int main (int argc, char **argv) {
	//Declaração das variáveis do programa
	FILE* output = NULL;
	int desviarSaida = 0;
	int retorno = 0;
  void *func;
  int n, k, func1, func2 , count, maxIter, hessSteps;
  char *funcString;
  void **firstDerivatives;
  void **secondDerivatives;
  char **variableNames;
  double xInitial, epsilon;
  double *xVecNewMod, *yNewMod, *deltaNewMod;
  double *derivEvalNewMod;
	double **hessNewMod, **l_NewMod, **u_NewMod;
	double** l_test;
	double **u_test;
	m_diag* hessD;
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
	funcString 				= malloc(100 * func1 * func2 * sizeof(char));
	strcpy(funcString, "");
	xVecNewMod 				= malloc (sizeof(double) * n);
	copyInitialVector(n, xInitial, xVecNewMod);
	yNewMod						= malloc (sizeof(double) * n);
	deltaNewMod				= malloc (sizeof(double) * n);
	variableNames       = createVariableNamesVector(n);
	firstDerivatives 	= malloc (sizeof(void*) * n);
	derivEvalNewMod		= malloc (sizeof(double) * n);
	//secondDerivatives = createVoidMatrix(n);
	secondDerivatives   = malloc (sizeof(void*) * n * n);
	l_NewMod 					= createDoubleMatrix(n);
	u_NewMod					= createDoubleMatrix(n);
	hessD							= createDoubleMatrixD(n, k);

	//Cria a string que descreve a função para a libmatheval
	generateStringFunction(funcString, func1, func2);
	//Atribui o buffer para func com a função da libmatheval
  func = evaluator_create(funcString);
  assert(func);
  //coloca as variáveis da função no vetor variableNames e quantidade delas em count
	evaluator_get_variables(variableNames, n);
  for (int i = 0; i < n; i++) {
    firstDerivatives[i] = evaluator_derivative(func, variableNames[i]);
  }

  //cria a matriz de derivadas secundárias
  for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
    		secondDerivatives[(i * n) + j] = evaluator_derivative(firstDerivatives[i], variableNames[j]);
	
	for (int i = 0; i < maxIter; i++) {
		evalueteFirstDerivatives(firstDerivatives, derivEvalNewMod, variableNames, n, xVecNewMod);
		// se a norma das derivadas primeiras for menor que o epsilon, quebra o laço
		//printf("%d\t%f\n", i, norm(derivEvalNewMod, n));
		if (norm(derivEvalNewMod, n) < epsilon)
			break; 
		// limita a atualização da matriz de coeficientes da hessiana de acordo com os hess steps
		//Calcula a hessiana e faz a fatoração L e U
		if (! (i%hessSteps)){
			createHessCoefficientsMatrixDiag(secondDerivatives, hessD, variableNames, n, xVecNewMod);
			gen_l_u_diag(hessD, l_NewMod, u_NewMod, n);
		
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
		
	//Libera todas as variáveis dinâmicas
	liberar:
  free(xVecNewMod);
	free(yNewMod);
	free(deltaNewMod);
	free(derivEvalNewMod);
	freeVoidVector(n, firstDerivatives);
	freeDoubleMatrix(n, l_NewMod);
	freeDoubleMatrix(n, u_NewMod);
	free(secondDerivatives);
  freeVariableNamesVector(n , variableNames);
  free(funcString);
	freeDoubleMatrixD(hessD);
	if(desviarSaida) fclose(output);
	return retorno;
}
