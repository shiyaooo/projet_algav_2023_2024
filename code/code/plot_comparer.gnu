set title 'Temps d executee en fonction de la taille'
set xlabel 'Taille de la liste'
set ylabel 'Temps d executee(s)'
plot 'time_data_ajout_tab.txt' with linespoints title 'Ajout_It_tab','time_data_cons_tab.txt' with linespoints title 'Construction_tab'
