set terminal wxt size 1000,800
set xlabel 'X'
set ylabel 'Y'
set grid
set xrange[-10:10]
set yrange[-10:10]
set size ratio -1
f1(x) = (-1*x - 3)/2
f2(x) = (-3*x - 5)/4
plot f1(x) title 'Line 1' lw 2 lc rgb 'red', \
     f2(x) title 'Line 2' lw 2 lc rgb 'blue'
pause -1
