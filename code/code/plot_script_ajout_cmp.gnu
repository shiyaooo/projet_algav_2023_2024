set title 'Temps d Ajout'
set style data histograms
unset xtics
set ylabel 'Temps(s)'
set logscale y
set yrange [1e-7:10]
set ytics ('10^{-7}' 1e-7,'10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1, '10^{0}' 1, '10^{1}' 10)
set boxwidth 1
set style histogram cluster gap 1
set style fill solid border -1
set key top right
plot 'time_data_ajout_cmp.txt' using 1:xtic(1) title 'tas_min_tab', '' using 2 title 'tas_min_ab', '' using 3 title 'file_binomiale'
