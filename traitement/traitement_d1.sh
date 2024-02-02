#!/bin/bash
LC_NUMERIC=C awk -F';' '!seen[$1]++ {noms[$6]++} END {for (i in noms) printf("%d;%s\n", noms[i], i)}' $1 | LC_NUMERIC=C sort -rV | head -n 10 > temp/temp_d1.csv
awk -F';' -v OFS=';' '{temp=$1; $1=$2; $2=temp; print}' temp/temp_d1.csv > temp/inverse_temp_d1.csv #reverse the 2 columns

gnuplot <<EOF
	set datafile separator ";"
	set terminal pngcairo enhanced
	set size ratio 1
	set style data histograms
	set style histogram rowstacked
	set style fill solid
	set boxwidth 0.8 
	set output 'images/graphique_temp_d1.png'
	
	
	set xtic rotate by 90
	set terminal png size 800,800
	unset ytics
	unset x2tics
	set xtics nomirror offset 0,-11
	set y2tics rotate by 45
	
	
	set y2label 'Distance' offset 2,0
	set xlabel 'Drivers' offset 0,-11
	set xlabel rotate by 180
	set title ' ' offset 0,20
	set ylabel 'Option -d1' offset -2,0
	plot 'temp/inverse_temp_d1.csv' using 2:xtic(1) axes x1y2 notitle lc rgb "#20F19F" 
	
	set terminal wxt 
EOF
	convert -rotate 90 "images/graphique_temp_d1.png" "images/graphique_traitement_d1.png"
	rm images/graphique_temp_d1.png
