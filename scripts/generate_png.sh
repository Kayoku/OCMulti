#!/bin/bash

for dat in ../AB/*
do
    gnuplot <<EOF
    set terminal png enhanced
    set output '$dat.png'
    set autoscale
    plot "$1" u 1:2 lt rgb "red" t "Meilleur front connu", "$dat" u 1:2 lt rgb "blue" t "Front généré"
EOF
done


#plot "$1" u 1:2 with points pointtype 7 lt rgb "red" t "Solutions filtrées", "$2" u 1:2 lt rgb "blue" t "Solutions aléatoires"

