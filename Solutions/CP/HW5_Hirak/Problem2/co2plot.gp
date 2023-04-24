reset

set term png

set out "co2_quadratic.png"
#set out "co2_extrapolation_quadratic.png"

set xrange [1950:2020]
set yrange [300:500]

set xlabel 'years'
set ylabel 'CO2 concentration (ppm)'

set arrow from 3700,60000 to 3914,50000
set label 'Here we die' at 3600, 62000

set title 'CO2 concentration vs year quadratic fit'

a =   0.0119 
b = -45.90 
c = 44452.97 

f(x) = a*x**2 + b*x + c 
g(x) = 0.0119*x**2 - 45.9*x + 44452.97

fit f(x) 'co2.dat' using 3:5 via a, b, c

#plot 'co2.dat' using 3:5 w p via a,b,c

plot 'co2.dat' u 3:5 w p pointtype 0 lc rgb 'blue' title 'data', f(x) lc rgb 'red' lt 2 title 'our fit', g(x) lt 1 lc rgb 'green' title 'Future' 


set out



