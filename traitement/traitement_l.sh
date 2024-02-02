#!/bin/bash

awk -F';' '{distance[$1]+=$5} END {for (i in distance) printf "%s;%.2f\n", i, distance[i]}' $1 | sort -t ';' -k2,2nr | head -n 10 > temp/temp_l.csv

gnuplot -persist <<EOF
    set title "10 plus grandes distances"
    set xlabel "ROUTE ID"
    set ylabel "DISTANCE en km"
    set yrange [0:*]
    set style data histograms
    set style fill solid
    set boxwidth 0.7 relative
    set output 'images/graphique_L.png'
    
    set terminal png size 800,800
    set datafile separator ";"
    plot "temp/temp_l.csv" using 2:xtic(1) with boxes lc rgb "#20F19F" title "Trajet complet"
EOF
