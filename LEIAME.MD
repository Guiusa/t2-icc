# Guiusepe Oneda Dal Pai GRR20210572 / Fernando Gbur dos Santos GRR20211761

## Sobre o programa:
### Execução:

```
./pontosCriticos [-o <OUTPUT_FILE>]
```
Se não for dado um arquivo para output, o resultado é imrpesso na saída padrão
do sistema.

### Erros:
O programa conta com 3 códigos de erro:

- 1: Se o valor de k lido for par ou menor que 3, como a especificação exige que
não seja.

- 2: Se houver um arquivo de output especificado, mas não tenha sido possível
abrí-lo para execução

- 3: Se, durante a fatoração LU, haja um 0 na diagonal principal, há um sistema
impossível e o programa é interrompido

## Módulos:

### iolib
Esse módulo serve o propósito de executar as operações de input e output, as
funções nela serviram para debugar o código ao longo do desenvolvimento, exceto
pela função printStep, que realiza o output exigido pela especificação do
trabalho:

```
ITERAÇÃO | QUASI-NEWTON | NEWTON MOD
---------|--------------|-----------
	0	 |		f(xi)	|	f(xi)
``` 

Além dessa, também há a função returnsError, que imprime uma mensagem de erro 
com fundo vermelho em caso de erro do programa.

### mathOperations
Essa biblioteca serve para realizar operações matemáticas, principalmente em 
relação à biblioteca libmatheval, apesar que esse módulo não é o único a
utilizá-la.
Dentre as funções dela, encontra-se:
- Gerar a string da função de acordo com n e k
- Calcular a matriz hessiana a partir do vetor X e da matriz de derivadas
parciais secundárias
- Calcular o vetor de derivadas parciais primárias
- Calcular a norma de um vetor
- Calcular o vetor X da próxima iteração a partir do X atual e do delta
- Realizar todo o cálculo que resulta na Hessiana da próxima iteração no método
Quasi-Newton

### matrixOperations
Esse módulo realiza operações com matrizes, incluindo:
- Alocar e liberar espaço para cada matriz e vetor necessários na execução
do programa
- vários tipos de multiplicação, incluindo matrizes NxN, 1xN e Nx1
- Copiar dois vetores, bem como copiar matrizes
- Realizar a soma de matrizes
- Dividir todos os índices de uma matriz por um escalar
- Realizar a fatoração LU de uma matriz
