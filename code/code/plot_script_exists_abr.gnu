set title 'Temps d Exists_arbre en fonction de la taille'
set xlabel 'Taille de la liste'
set yrange [1e-6:5e-6]
set ylabel 'Temps d Exists_arbre (s)'
plot 'time_data_exist_abr.txt' with linespoints title 'Exists_arbre'
