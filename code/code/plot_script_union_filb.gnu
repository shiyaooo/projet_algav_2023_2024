set title 'Temps d Union_FilB en fonction de la taille'
set xlabel 'Taille de la liste'
set ylabel 'Temps d Union_FilB (s)'
set yrange [2.4e-6:7e-6]
set xrange [2000:180000]
plot 'time_data_union_filb.txt' with linespoints title 'Union_FilB'
