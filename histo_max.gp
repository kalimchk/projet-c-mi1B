set terminal png size 1000,600
set output "histo_max.png"

set title "Capacité maximale des usines"
set xlabel "Usine"
set ylabel "Capacité (M.m3)"

set datafile separator ";"
set style data histograms
set style fill solid
set boxwidth 0.8
set xtics rotate by -45

plot "histo_max.dat" using 2:xtic(1) title "Capacité max"
