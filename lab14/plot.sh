set terminal pngcairo

set output 'gen2_x3.png'
set grid
plot "gen2.out" u 1:4 w p ls 1 
