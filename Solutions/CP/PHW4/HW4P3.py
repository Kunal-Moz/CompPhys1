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



v = Matrix(8, 1)       # column vector with 6 rows
v[0][0] = v0
v[1][0] = v0
v[2][0] = v0
v[3][0] = v0
v[4][0] = v0
v[5][0] = v0
v[6][0] = v0
v[7][0] = v0

Req1 = []
rvec = []

for ival in xrange(200):
    r1 = float(ival+1)/10.
    i1 = Matrix_copy(v)
    R = Matrix(8,8)
    R[0][0] = r5+r12
    R[0][2] = r12
    R[0][3] = r12
    R[0][4] = r12
    R[0][5] = -r12
    R[0][6] = -r12
    R[0][7] = r12      

    R[1][2] = -r3
    R[1][3] = r1+r2
    R[1][4] = r2
    R[1][5] = -r2

    R[2][0] = -r5
    R[2][2] = r3+r4
    R[2][3] = r4
    R[2][4] = r4
    R[2][5] = -r4
    R[2][6] = -r4

    R[3][3] = r2
    R[3][4] = r2
    R[3][5] = -r2-r9
    R[3][6] = r11

    R[4][1] = -r10
    R[4][4] = r7+r10
    R[4][5] = r9
    R[4][7] = r10

    R[5][1] = -r6
    R[5][3] = r1
    R[5][4] = -r7

    R[6][0] = r12
    R[6][1] = -r10
    R[6][2] = r12
    R[6][3] = r12
    R[6][4] = r10+r12
    R[6][5] = -r12
    R[6][6] = -r12
    R[6][7] = r8+r10+r12

    R[7][0] = r5
    R[7][1] = -r6
    R[7][7] = -r8
   
    rvec.append(r1)
    solve_Gauss_Jordan(R, i1)
    r_eq1 = v0 / sum( [i1[i][0] for i in xrange(len(i1))] )
    Req1.append(r_eq1)
    

plt.plot(rvec,Req1,label="r1")
plt.ylabel('Equivalent Resistance of Cube (Ohms)')
plt.xlabel('Resistor (Ohms)')
plt.legend()
plt.show()


