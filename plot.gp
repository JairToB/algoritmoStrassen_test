set terminal pngcairo size 800,600
set output "graficoComparacion.png"

set title "Multiplicacion Standard vs Strassen"
set xlabel "Tamano de la matriz (n)"
set ylabel "Tiempo (microsegundos)"

set key top left
set grid

plot "data.dat" using 1:2 with linespoints title "Standard", \
     "data.dat" using 1:3 with linespoints title "Strassen"
