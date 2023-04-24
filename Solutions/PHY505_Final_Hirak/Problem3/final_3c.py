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

def p(t,x,y,z, alpha) :
    #alpha = 15.6
    p = alpha* (y- x - f(x))
    return p


def q(t,x,y,z) :
    q = (x- y +z)
    return q


def r(t,x,y,z, beta) :
    #beta = 16.0
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
    alphaval = []
    t = tmin
    x = 1.0
    y = 0.0
    z = 0.0
    beta = 28.0
    alpha = 0.0
    for i in range(500):
        alpha = alpha + 0.1
        x = 1.0
        y = 0.0
        z = 0.0
        print alpha
        for j in range(10000):
            
            k0 = dt* p(t,x,y,z,alpha)
            #print k0
            l0 = dt* q(t,x,y,z)
            m0 = dt* r(t,x,y,z,beta)

            k1 = dt* p(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0, alpha)
            l1 = dt* q(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0)
            m1 = dt* r(t+0.5*dt, x+0.5*k0, y+0.5*l0, z+0.5*m0, beta)

            k2 = dt* p(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1, alpha)
            l2 = dt* q(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1)
            m2 = dt* r(t+0.5*dt, x+0.5*k1, y+0.5*l1, z+0.5*m1, beta)

            k3 = dt* p(t+dt, x+k2, y+l2, z+m2, alpha)
            l3 = dt* q(t+dt, x+k2, y+l2, z+m2)
            m3 = dt* r(t+dt, x+k2, y+l2, z+m2, beta)

            x = x + (k0 + 2*k1 + 2*k2 + k3)/6.0
            y = y + (l0 + 2*l1 + 2*l2 + l3)/6.0
            z = z + (m0 + 2*m1 + 2*m2 + m3)/6.0

            t = t + dt
 
            tval.append( t )
            xval.append( x )
            yval.append( y )
            zval.append( z )
            alphaval.append( alpha )
        
        #print tval[i] , xval[i], yval[i], zval[i]
    plotOut = file("bif_plot.txt", 'w')
    for i in xrange( len(alphaval) ) :
        s = str( alphaval[i] ) + " " + str ( xval[i] ) +  " "  + str( yval[i]/xval[i]) + '\n'
        plotOut.write( s ) 

    plotOut.close(  )

    import matplotlib
    matplotlib.rcParams['legend.fancybox'] = True
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    '''
    ax1 = plt.subplot(3, 1, 1)
    p1 = plt.plot( tval, xval )
    
    plt.title("x, y, z vs t plot")
    plt.xlabel("t")
    plt.ylabel("x")

    ax2 = plt.subplot(3, 1, 2)
    p2 = plt.plot( tval, yval )
    
    
    plt.xlabel("t")
    plt.ylabel("y")

    ax3 = plt.subplot(3, 1, 3)
    p3 = plt.plot( tval, zval )
    
    
    plt.xlabel("t")
    plt.ylabel("z")
    '''
    '''
    ax4 = plt.subplot(1, 1, 1)
    p4 = plt.scatter( betaval, xval, marker= '.' )
    ax4.legend( [p4], ['x'])
    plt.title("x, y, z vs t plot")
    plt.xlabel("beta")
    plt.ylabel("x")
    
    '''
    '''
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(xval, yval, zval)
    '''

    #plt.show()

    


if __name__ == "__main__" :
    main()
