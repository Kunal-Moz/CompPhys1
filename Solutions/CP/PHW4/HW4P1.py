from cpt import *
import matplotlib.pyplot as plt

print " Symmetric cube of resistors"
print " --------------------------------------\n"



v0 = 5.0
r1 = 1.0
r2 = 1.0
r3 = 1.0
r4 = 1.0
r5 = 1.0
r6 = 1.0
r7 = 1.0
r8 = 1.0
r9 = 1.0
r10 = 1.0
r11 = 1.0
r12 = 1.0



v = Matrix(6, 1)       # column vector with 6 rows
v[0][0] = v0
v[1][0] = v0
v[2][0] = v0
v[3][0] = v0
v[4][0] = v0
v[5][0] = v0

Req1 = []
Req6 = []
rvec = []

for ival in xrange(200):
    rval = float(ival+1)/10.
    i1 = Matrix_copy(v)
    i6 = Matrix_copy(v)
    R1 = Matrix(6, 6)
    R6 = Matrix(6, 6)
    R1[0][0] = rval+r4+r10
    R1[0][1] = rval
    R1[0][2] = r10

    R1[1][0] = rval
    R1[1][1] = rval+r5+r11
    R1[1][4] = r11

    R1[2][0] = r10
    R1[2][2] = r2+r6+r10
    R1[2][3] = r2

    R1[3][2] = r2
    R1[3][3] = r2+r7+r12
    R1[3][5] = r12

    R1[4][1] = r11
    R1[4][4] = r3+r8+r11
    R1[4][5] = r3

    R1[5][3] = r12
    R1[5][4] = r3
    R1[5][5] = r3+r9+r12


    R6[0][0] = r1+r4+r10
    R6[0][1] = r1
    R6[0][2] = r10

    R6[1][0] = r1
    R6[1][1] = r1+r5+r11
    R6[1][4] = r11

    R6[2][0] = r10
    R6[2][2] = r2+rval+r10
    R6[2][3] = r2

    R6[3][2] = r2
    R6[3][3] = r2+r7+r12
    R6[3][5] = r12

    R6[4][1] = r11
    R6[4][4] = r3+r8+r11
    R6[4][5] = r3

    R6[5][3] = r12
    R6[5][4] = r3
    R6[5][5] = r3+r9+r12

    rvec.append(rval)
    solve_Gauss_Jordan(R1, i1)
    r_eq1 = v0 / sum( [i1[i][0] for i in xrange(len(i1))] )
    Req1.append(r_eq1)
    solve_Gauss_Jordan(R6, i6)
    r_eq6 = v0 / sum( [i6[i][0] for i in xrange(len(i6))] )
    Req6.append(r_eq6)
    

plt.plot(rvec,Req1,label="r1")
plt.plot(rvec,Req6,label="r6")
plt.ylabel('Equivalent Resistance of Cube (Ohms)')
plt.xlabel('Resistor (Ohms)')
plt.legend()
plt.show()


