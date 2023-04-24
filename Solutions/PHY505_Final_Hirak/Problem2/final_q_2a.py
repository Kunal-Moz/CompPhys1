from matplotlib.pyplot import figure, show
from numpy import arange, sin, pi, exp, cos

r = arange(-10.0, 1000.0, 0.01)

fig = figure(1)

V0 = 2
r0 = 2

ax1 = fig.add_subplot(111)
ax1.plot(r, V0*exp(r/r0)*cos(pi*r/r0))
ax1.grid(True)
#ax1.set_ylim((-2, 2))
ax1.set_ylabel('f(x)')
ax1.set_xlabel('x')
ax1.set_title('V0*exp(r/r0)*cos(pi*r/r0)')

for label in ax1.get_xticklabels():
    label.set_color('black')

show()
