#!/bin/bash

gnuplot <<EOF
set terminal png enhanced
set output 'draw2D.png'

set autoscale
set style data linespoints

plot "$1" using 1:2, "$2" using 1:2, "$3" using 1:2, "$4" using 1:2, "$5" using 1:2
EOF
