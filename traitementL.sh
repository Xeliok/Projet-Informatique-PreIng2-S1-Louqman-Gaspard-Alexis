#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <fichier-csv>"
    exit 1
fi

fichier_csv="$1"

if [ ! -e "$fichier_csv" ]; then
    echo "le fichier n'existe pas"
    exit 1
fi

resultat_csv="resultat.csv"

awk -F';' '{distance[$1]+=$5} END {for (i in distance) printf "%s;%.2f\n", i, distance[i]}' "$fichier_csv" | sort -t ';' -k2,2nr | head -n 10 >"$resultat_csv"

gnuplot -persist <<EOF
    set title "10 plus grandes distances"
    set xlabel "ROUTE ID"
    set ylabel "DISTANCE en km"
    set yrange [0:*]
    set style data histograms
    set style fill solid
    set boxwidth 0.7 relative
    set output 'graphique/graphique_L.png'
    
    set terminal png size 800,800
    set datafile separator ";"
    plot "$resultat_csv" using 2:xtic(1) with boxes lc rgb "#20F19F" title "Trajet complet"
EOF

echo "resultat dans resultat csv"
