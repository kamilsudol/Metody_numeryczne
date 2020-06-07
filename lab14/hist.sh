set terminal pngcairo

set output "hist3.png"
plot "nj3.out" u 1:2 w boxes fs pattern 5 t "n_j", "gj3.out" u 1:2 w boxes t "g_j"