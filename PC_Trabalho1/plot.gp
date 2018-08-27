#! /usr/local/bin/gnuplot --persist

set terminal svg enhanced font "Helvetica, 16" size 800,800

set xtics 1
set ytics 1
set grid y x
set key inside b r
set xlabel "Threads"
set ylabel "Speedup"

set title "Covariance (size: 2048)\n{/*0.7 Intel(R) Xeon(R) 2.00GHz}"
set output "results/cov.svg"

f(x)=x
plot f(x) dashtype 30 title 'Ideal', "results/cov.dat" using 1:2 title 'PThread' with linespoints, "results/cov.dat" using 1:3 title 'OpenMP' with linespoints
