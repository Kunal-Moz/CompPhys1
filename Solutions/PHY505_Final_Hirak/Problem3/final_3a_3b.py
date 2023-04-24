# pendul - Program to compute the motion of a simple pendulum
# using the Euler or Verlet method

from math import *
from numpy import array



def f(x) :
    Gb = -0.714
    Ga = -1.143
    E = 1.0
    f = Gb*x + 0.5* (Ga - Gb)* (abs(x+E) - abs(x-E))
    return f

def p(t,x,y,z) :
    alpha = 15.6
    p = alpha* (y- x - f(x))
    return p


def q(t,x,y,z) :
    q = (x- y +z)
    return q


def r(t,x,y,z) :
    beta = 28.0
    r = -beta*y
    return r


def main () : 

    tmin = 0.0
    tmax = 1.0
    nStep = 1000
    dt = 0.001
    tval = []
    xval = []
    yval = []
    zval = []
    t = tmin
    x = 1.0
    y = 0.0
    z = 0.0


    for i in range(20000):


        k0 = dt* p(t,x,y,z)
        #print k0
        l0 = dt* q(t,x,y,z)
        m0 = dt* r(t,x,y,z)

        k1 = dt* p(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0)
        l1 = dt* q(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0)
        m1 = dt* r(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0)

        k2 = dt* p(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1)
        l2 = dt* q(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1)
        m2 = dt* r(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1)

        k3 = dt* p(t+dt, x+k2, y+l2, z+m2)
        l3 = dt* q(t+dt, x+k2, y+l2, z+m2)
        m3 = dt* r(t+dt, x+k2, y+l2, z+m2)

        x = x + (k0 + 2*k1 + 2*k2 + k3)/6.0
        y = y + (l0 + 2*l1 + 2*l2 + l3)/6.0
        z = z + (m0 + 2*m1 + 2*m2 + m3)/6.0

        t = t + dt

        tval.append( t )
        xval.append( x )
        yval.append( y )
        zval.append( z )

        #print tval[i] , xval[i], yval[i], zval[i]

    import matplotlib
    matplotlib.rcParams['legend.fancybox'] = True
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    
    ax1 = plt.subplot(3, 1, 1)
    p1 = plt.plot( tval, xval )
    #ax1.legend( [p1], ['x'])
    plt.title("x, y, z vs t plot")
    plt.xlabel("t")
    plt.ylabel("x")

    ax2 = plt.subplot(3, 1, 2)
    p2 = plt.plot( tval, yval )
    #ax2.legend( [p2], ['y'])
    
    plt.xlabel("t")
    plt.ylabel("y")

    ax3 = plt.subplot(3, 1, 3)
    p3 = plt.plot( tval, zval)
    #ax3.legend( [p3], ['z'])
    
    plt.xlabel("t")
    plt.ylabel("z")

    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(xval, yval, zval)
    

    plt.show()

    


if __name__ == "__main__" :
    main()
