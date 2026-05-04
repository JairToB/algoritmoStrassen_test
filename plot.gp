set terminal pngcairo size 800,600
set output "graficoStandardMatrix.png"

set title "Standard Matrix"
set xlabel "n"
set ylabel "Tiempo (microsegundos)"
set key top left
set grid

plot "data.dat" using 1:2 with linespoints title "Standard Matrix"
