set datafile separator ";"
set terminal pngcairo enhanced size 800,900
set output 'graphique_traitement_t.png'

set style data histograms
set style histogram clustered 
set boxwidth 1.5
set style fill solid
set ytics nomirror

set title 'Option -t : NB routes=f(Towns)'
set ylabel 'NB Routes'
set xlabel 'Town Names'
set xtics rotate by -45
set size 1, 1

plot 'temp_t.csv' using 2:xtic(1) title 'Total routes' lc rgb "#53166D", \
'' using 3 title 'First town' lc rgb "#F9B6E5"

