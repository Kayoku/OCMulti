#!/bin/bash

gnuplot <<EOF
set terminal png enhanced
set output 'courbe.png'
plot "$1" using 1:2 
EOF
