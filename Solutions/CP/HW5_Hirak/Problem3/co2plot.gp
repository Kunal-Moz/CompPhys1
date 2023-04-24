reset

set term png

#set out "co2_exp.png"
set out "co2_extrapolation_exp.png"

set xrange [1950:3220]
set yrange [300:70000]

set xlabel 'years'
set ylabel 'CO2 concentration (ppm)'

set arrow from 2700,60000 to 3115,50000
set label 'Here we die' at 2500, 62000

set title 'CO2 concentration vs year exponential fit'

a =  0.079274886244 
b = 0.0042236328406 
#c = 44452.97 

f(x) = a*exp(b*x) 
g(x) = 0.079274886244*exp(0.0042236328406*x)

fit f(x) 'co2.dat' using 3:5 via a, b

#plot 'co2.dat' using 3:5 w p via a,b

plot 'co2.dat' u 3:5 w p pointtype 0 lc rgb 'blue' title 'data', f(x) lc rgb 'red' lt 2 title 'Exponential fit', g(x) lt 1 lc rgb 'green' title 'Future' 


set out



