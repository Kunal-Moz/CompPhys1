reset

set terminal png 
set out 'linearfit.png'

set xlabel 'Year'
set ylabel 'Co2 concentration'

a = 2.0
b = 3.0

f(x) = a*x +b

fit f(x) 'co2data.dat' using 3:5  via a,b

plot 'co2data.dat' using 3:5 with lines lt 1 lc rgb 'blue' title 'Data', f(x) with lines lt 2 lc rgb 'red' title 'Linear Fit'

set out

#Final set of parameters            Asymptotic Standard Error
#=======================            ==========================
#a               = 1.54159          +/- 0.008688     (0.5636%)
#b               = -2711.84         +/- 17.27        (0.637%)


