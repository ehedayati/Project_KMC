set terminal png
set ou 'Height_steps.png'
set grid
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1
p 'visualization/gnuplot/Height_average' notitle w p ls 1
