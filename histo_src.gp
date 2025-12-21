set terminal png size 1000,600
set output "histo_src.png"

set title "Volumes des sources"
set xlabel "Source"
set ylabel "Volume (M.m3.year-1)"

set datafile separator ";"
set style data histograms
set style fill solid
set boxwidth 0.8
set xtics rotate by -45

plot "histo_src.dat" using 2:xtic(1) title "Sources"
