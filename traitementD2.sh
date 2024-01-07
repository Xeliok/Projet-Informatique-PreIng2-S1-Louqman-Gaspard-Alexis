#! /bin/bash

LC_NUMERIC=C awk -F';' 'NR>1 {distance[$6]+=$5} END {for (driver in distance) printf "%.3f;%s\n", distance[driver], driver}' data.csv | LC_NUMERIC=C sort -t';' -rnk1,1 | head -n 10 > resultats.csv

awk -F';' -v OFS=';' '{temp=$1; $1=$2; $2=temp; print}' resultats.csv > resultats_inverses.csv

gnuplot -persist <<EOF
	set datafile separator ";"
	set terminal pngcairo enhanced font 'Arial,10'
	set output 'graphique_horizontal.png'
	
	set style data histograms
	set style histogram rowstacked
	set boxwidth 0.8 
	set style fill solid
	set ytics nomirror
	set xtics rotate by -45
	set ylabel 'Distances'
	set xlabel 'Drivers'
	plot 'resultats_inverses.csv' using 2:xtic(1) title 'Distances' lc rgb "blue"
EOF

