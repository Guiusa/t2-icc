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

set ylabel  "L3-BANDWIDTH"
set title   "L3-BANDWIDTH/N"
set terminal qt 1 title "L3-BANDWIDTH/N"
plot '../tables/L3.dat' using 1:2 title "com-otimizacao" with linespoints, \
     '' using 1:3 title "sem-otimizacao" with linespoints