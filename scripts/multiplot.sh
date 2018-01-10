#!/bin/bash

gnuplot <<EOF
set terminal png enhanced size 1920, 480
set output '$2.png'
set autoscale
set multiplot layout 1, 3 

#
set title "AB"
unset key
plot "../instances/best.randomAB100.tsp" u 1:2 t "Meilleur front connu", "../AB/$1" u 1:2 t "Front généré"
#
set title "CD"
unset key
plot "../instances/best.randomCD100.tsp" u 1:2 t "Meilleur front connu", "../CD/$1" u 1:2 t "Front généré"
#
set title "EF"
unset key
plot "../instances/best.randomEF100.tsp" u 1:2 t "Meilleur front connu", "../EF/$1" u 1:2 t "Front généré"
#
EOF

#plot "$1" u 1:2 with points pointtype 7 lt rgb "red" t "Solutions filtrées", "$2" u 1:2 lt rgb "blue" t "Solutions aléatoires"

