from cpt import *
from math import *
import numpy as np

V0 = 2
r0 = 2

def f (p) :
    r = p[0]
    #x = p[0]
    #y = p[1]
    #z = p[2]
    if (r>=0 and r<=4):
        return (V0*exp(r/r0)*cos(pi*r/r0))
    else :
        return 0
    #return x*x + 2 * y*y + 0.3 * cos(3 * pi * x) + 0.4 * cos(4 * pi * y) + sin(pi*z)

def negf (p) :
    r = p[0]
    #x = p[0]
    #y = p[1]
    #z = p[2]
    if (r>=0 and r<=4):
        return (-V0*exp(r/r0)*cos(pi*r/r0))
    else :
        return 0
 
    #return x*x + 2 * y*y + 0.3 * cos(3 * pi * x) + 0.4 * cos(4 * pi * y) + sin(pi*z)


def df(p) :
    l1 = p[0]
    r = V0*(  (1/r0)*exp(l1/r0)*cos(pi*l1/r0) - (pi/r0)*exp(l1/r0)*sin(pi*l1/r0)  )
    return np.array( [r] )
    #l1 = p[0]
    #l2 = p[1]
    #l3 = p[2]
    #x = 2 * l1 - 0.9 * pi * sin(3 * pi * l1)
    #y = 4 * l2 - 1.6 * pi * sin(4 * pi * l2)
    #z = pi * cos(pi * l3)
    #return np.array( [x,y,z] )



p = input(" Enter starting point: ")
print p

k = float(p)
print k
gtol = input( " Enter desired accuracy: ")
print 'minimize'
xmin = scipy.optimize.minimize( fun=f, x0=k, tol=gtol )
fxmin = f(xmin.x)
print xmin.x, fxmin

print 'maximize'
xmax = scipy.optimize.minimize( fun=negf, x0=k, tol=gtol )
fxmax = negf(xmax.x)
print xmax.x, -fxmax

