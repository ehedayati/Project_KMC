set terminal gif animate delay 30
set output 'foobar.gif'
set contour
set grid
set view 60,20
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1
stats 'Datafile' nooutput
set ztics 1
set zrange [-2:7]
do for [i=1:int(STATS_blocks)] {
   splot 'Datafile' index 0 matrix  notitle with p ls 1,'Datafile' index (i-1) matrix  notitle with p ls 1 
}#3~ splot for [j=1:i] 'Datafile' index (j-1) matrix  notitle with p ls 1
