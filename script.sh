#!/bin/bash

n="1 2 3 4 5 6 7 8 9 10"
vet=('32' '64' '128' '200' '256' '512' '600' '1000' '2000' '4000')
tam=0

for i in $n; do
    tamAtual=${vet[$tam]}
    
    tempoOtm="$(likwid-perfctr -C 3 -g FLOPS_DP ./otimizado/pontosCriticos < otimizado/testes/teste$i > logs-otimizado/tempo_$i)"
    L3Otm="$(likwid-perfctr -C 3 -g L3 ./otimizado/pontosCriticos < otimizado/testes/teste$i > logs-otimizado/L3_$i)"
    L2CACHEOtm="$(likwid-perfctr -C 3 -g L2CACHE ./otimizado/pontosCriticos < otimizado/testes/teste$i > logs-otimizado/L2CACHE_$i)"

    tempoN="$(likwid-perfctr -C 3 -g FLOPS_DP ./nao-otimizado/pontosCriticos < nao-otimizado/testes/teste$i > logs-nao-otimizado/tempo_$i)"
    L3N="$(likwid-perfctr -C 3 -g L3 ./nao-otimizado/pontosCriticos < nao-otimizado/testes/teste$i > logs-nao-otimizado/L3_$i)"
    L2CACHEN="$(likwid-perfctr -C 3 -g L2CACHE ./nao-otimizado/pontosCriticos < nao-otimizado/testes/teste$i > logs-nao-otimizado/L2CACHE_$i)"

    tempo="$(cat logs-otimizado/tempo_$i | grep "milisegundos" | cut -d ':' -f 2 | tr -d ' ')"
    echo -n "$tamAtual " >> tables/tempo.dat
    echo -n "$tempo " >> tables/tempo.dat

    tempoNao="$(cat logs-nao-otimizado/tempo_$i | grep "milisegundos" | cut -d ':' -f 2 | tr -d ' ')"
    echo "$tempoNao " >> tables/tempo.dat

    l="$(cat logs-otimizado/L3_$i| grep "L3 bandwidth" | tr -d '|' | cut -d']' -f2 | tr -d ' ' | sed -n '1p')"
    echo -n "$tamAtual " >> tables/L3.dat
    echo -n "$l " >> tables/L3.dat

    lN="$(cat logs-nao-otimizado/L3_$i| grep "L3 bandwidth" | tr -d '|' | cut -d']' -f2 | tr -d ' ' | sed -n '1p')"
    echo "$lN " >> tables/L3.dat

    l2="$(cat "logs-otimizado/L2CACHE_$i" | grep "L2 miss ratio" | tr -d '|' | cut -d 'o' -f 2 | tr -d ' ' | sed -n '1p')"
    echo -n "$tamAtual " >> tables/L2.dat
    echo -n "$l2 " >> tables/L2.dat

    l2N="$(cat "logs-nao-otimizado/L2CACHE_$i" | grep "L2 miss ratio" | tr -d '|' | cut -d 'o' -f 2 | tr -d ' ' | sed -n '1p')"
    echo "$l2N " >> tables/L2.dat

    dp="$(cat "logs-otimizado/tempo_$i" | grep "DP MFLOP/s" | tr -d '|' | cut -d 's' -f 2 | tr -d ' ' | sed -n '1p')"
    echo -n "$tamAtual " >> tables/dp.dat
    echo -n "$dp " >> tables/dp.dat

    dpN="$(cat "logs-nao-otimizado/tempo_$i" | grep "DP MFLOP/s" | tr -d '|' | cut -d 's' -f 2 | tr -d ' ' | sed -n '1p')"
    echo "$dpN " >> tables/dp.dat

    tam=$((tam + 1))
done