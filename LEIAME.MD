# Guiusepe Oneda Dal Pai GRR20210572 / Fernando Gbur dos Santos GRR20211761

## Sobre o programa:
AVISO: O Script já foi executado e contém os resultados para os parâmetros especificados no trabalho.

Na pasta /tables os arquivos já estão separados por métrica do LIKWID como arquivos csv. Os dados podem ser 
visualizados graficamente com o gnuplot na pasta /plots

Ex:
```
gnuplot dp.gp
```

### Compilação:
É necessário compilar as duas versões (/otimizado e /nao-otimizado) do código com ```make``` para 
executar o script com:
```
./script.sh
```
### Execução sem o script:

```
./pontosCriticos [-o <OUTPUT_FILE>] [< entrada.txt]
```