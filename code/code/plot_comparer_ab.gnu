set title 'Temps d executee en fonction de la taille'
set xlabel 'Taille de la liste'
set ylabel 'Temps d executee(s)'
plot 'time_data_ajout_iteratif_arbre.txt' with linespoints title 'Ajout_It_arbre','time_data_cons_arbre.txt' with linespoints title 'Construction_arbre'
