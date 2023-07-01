#!/usr/bin/gnuplot -c
## set encoding iso_8859_15
set encoding utf
set terminal qt persist
set grid
set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
set xrange ["0":]
set xlabel  "N (bytes)"
set logscale x 2

set ylabel  "L2-CACHE-MISS"
set title   "L2-CACHE-MISS/N"
set terminal qt 1 title "L2-CACHE-MISS/N"
plot '../tables/L2.dat' using 1:2 title "com-otimizacao" with linespoints, \
     '' using 1:3 title "sem-otimizacao" with linespoints