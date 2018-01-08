#!/bin/bash

gnuplot <<EOF
set terminal png enhanced
set output 'draw2D.png'
plot "$1" using 1:2 
EOF
