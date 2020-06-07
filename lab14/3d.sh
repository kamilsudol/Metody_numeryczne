set terminal pngcairo 
set output "sfera.png"
unset key
set border 895
splot "sfera.out" u 1:2:3 pt 7 ps 0.5 lc rgb "black" 

set output "kula.png"
splot "kula.out" u 1:2:3:(sqrt($1**2 + $2**2 + $3**2)) pt 7 ps 0.5 lc rgb "black"