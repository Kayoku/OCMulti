#!/bin/bash

gnuplot <<EOF
set terminal png enhanced
set output 'draw2D.png'

set autoscale
plot "$1" u 1:2, "$2" u 1:2
EOF


#plot "$1" u 1:2 with points pointtype 7 lt rgb "red" t "Solutions filtrées", "$2" u 1:2 lt rgb "blue" t "Solutions aléatoires"

