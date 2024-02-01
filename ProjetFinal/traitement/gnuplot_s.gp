set datafile separator ";"
set terminal pngcairo enhanced size 1400,700 
set output 'graphique_traitement_s.png'

set title 'option -s'
set ylabel 'Distance (Km)'
set xlabel 'Route ID'
set key top right 

set xtics rotate by -55
set ytics nomirror
set xtics nomirror

plot 's/temp_s.csv' using 1:3:xtic(2) with lines notitle lc rgb "#F9B6E5", \
'' using 1:5 with lines notitle lc rgb "#F9B6E5", \
'' using 1:4 with lines title "Distances Moyenne" lc rgb "#53166D", \
'' using 1:3:5 with filledcurves below fill transparent solid title "Dist min -> Dist max" lc rgb "#F9B6E5"
