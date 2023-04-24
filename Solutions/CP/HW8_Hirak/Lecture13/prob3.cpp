#include <cmath>
#include <iostream>
#include <string>
using namespace std;
 
#include "linalg.hpp"
using namespace cpt;
 
int main()
{
    cout << " Unbalanced Wheatstone bridge equations\n"
         << " --------------------------------------\n";
 
    double v0 = 4,
           r1 = 1, r2 = 1, r3 = 1,
           r4 = 1, r5 = 1, r6 = 1,
		   r7 = 1, r8 = 1, r9 = 1,
		   r10 = 1, r11 = 1, r12 = 1;


    Matrix<double,2> v(4, 1);       // column vector with 4 rows
    v[0][0] = v0*(1/r1);
    v[1][0] = v0*(1/r2);
	v[2][0] = v0*(1/r3);
	v[3][0] = v0*(1/r4);

 Matrix<double,2> vzero(1, 1);       // column vector with 4 rows
	vzero[0][0] = v0;


    Matrix<double,2> Rn(12, 1);       // column vector with 12 rows resistance
    Rn[0][0] = r1;
    Rn[1][0] = r2;
	Rn[2][0] = r3;
	Rn[3][0] = r4;
    Rn[4][0] = r5;
    Rn[5][0] = r6;
	Rn[6][0] = r7;
	Rn[7][0] = r8;
    Rn[8][0] = r9;
    Rn[9][0] = r10;
	Rn[10][0] = r11;
	Rn[11][0] = r12;
   

    cout << " v = \n" << v << endl;
    cout << "v.dim1 = " << v.dim1() << endl;
 
    Matrix<double,2> R(4, 4);       // 5x5 resistance matrix
    R[0][0] =  ( 1/r1 + 1/r2 + 1/r9 + 1/r4)  ;             // set components using slicing notation	1
    R[0][1] =  ( -1/r9)  ;
    R[0][2] =  ( 0) ;
	R[0][3] =  ( -1/r12) ;
	

    R[1][0] =  ( -1/r9)  ;        // set components using slicing notation	2
    R[1][1] =  ( 1/r2 + 1/r10 + 1/r9 + 1/r6)  ;
    R[1][2] =  ( -1/r10) ;
	R[1][3] =  ( 0) ;
	

    R[2][0] =  ( 0)  ;        // set components using slicing notation	3
    R[2][1] =  ( -1/r10)  ;
    R[2][2] =  ( 1/r3 + 1/r11 + 1/r10 + 1/r7) ;
	R[2][3] =  ( -1/r11) ;
	

    R[3][0] =  ( -1/r12)  ;         // set components using slicing notation	4
    R[3][1] =  ( 0)  ;
    R[3][2] =  ( -1/r11) ;
	R[3][3] =  ( 1/r4 + 1/r12 + 1/r11 + 1/r8) ;
	



    cout << " R = \n" << R << std::endl;
    cout << " R.dim1 = " << R.dim1() << endl;
    cout << " R.dim2 = " << R.dim2() << endl;
 
    // the solve_Gauss_Jordan replaces R by R^-1 and v by i
    // so save the original R and copy v into a vector i
    Matrix<double,2> R_save(R), i(v);
 
    solve_Gauss_Jordan(R, i);
    cout << " Solution using Gauss-Jordan elimination for node voltages\n V = \n"
         << i << endl;
 
//cout << " i1 =  " << (i[0][0])*5 << endl;

    // find the other currents
    cout << " i1 =  " << (-i[0][0] + vzero[0][0])/Rn[0][0] << '\n'
         << " i2 =  " << (-i[1][0] + vzero[0][0])/Rn[1][0] << '\n'
		<< " i3 =  " << (-i[2][0] + vzero[0][0])/Rn[2][0] << '\n'
		<< " i4 =  " << (-i[3][0] + vzero[0][0])/Rn[3][0] << '\n'
		<< " i5 =  " << (i[0][0])/Rn[4][0] << '\n'
		<< " i6 =  " << (i[1][0])/Rn[5][0] << '\n'
		<< " i7 =  " << (i[2][0])/Rn[6][0] << '\n'
		<< " i8 =  " << (i[3][0])/Rn[7][0] << '\n'
		<< " i9 =  " << (i[0][0] - i[1][0])/Rn[8][0] << '\n'
		<< " i10 =  " << (i[1][0] - i[2][0])/Rn[9][0] << '\n'
		<< " i11 =  " << (i[2][0] - i[3][0])/Rn[10][0] << '\n'
		<< " i12 =  " << (i[3][0] - i[1][0])/Rn[11][0] << '\n'
         << endl;
// We have defined the current passes through all the resistances. 
// Now we define the total current from the voltage. This is just the addition of i1, i2, i3, i4

double itot = ((-i[0][0] + vzero[0][0])/Rn[0][0]) + ( (-i[1][0] + vzero[0][0])/Rn[1][0] ) + ((-i[2][0] + vzero[0][0])/Rn[2][0]) + ((-i[3][0] + vzero[0][0])/Rn[3][0] );

// Equivalent resistance

double req = v0/itot ;

cout << "The equivalent resistance is = " << req << endl;

    // see whether LU decomposition gives the same answer
    i = v;
    solve_LU_decompose(R_save, i);
    cout << " Solution using LU Decompositon\n V = \n"
         << i << endl;
}
