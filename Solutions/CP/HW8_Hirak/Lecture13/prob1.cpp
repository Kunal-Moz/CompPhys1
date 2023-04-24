#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
 
#include "linalg.hpp"
using namespace cpt;
 
int main()
{
    cout << " Unbalanced Wheatstone bridge equations\n"
         << " --------------------------------------\n";
 
    double v0 = 2.5,
           r1 = 1, r2 = 1, r3 = 1,
           r4 = 1, r5 = 1, r6 = 1,
		   r7 = 1, r8 = 1, r9 = 1,
		   r10 = 1, r11 = 1, r12 = 1;

	double rxa = 1/( (1/r1)+ (1/r2)+ (1/r7) );
	double rab = 1/( (1/r3)+ (1/r6)+ (1/r8)+ (1/r9)+ (1/r11)+ (1/r12) );
	double rby = 1/( (1/r5)+ (1/r4)+ (1/r10) );

	double req = (rxa + rab + rby);

	double i0 = (v0/req);

double r1var[50];						// when we vary r1.
double r1eq_array[50];
for (int j = 0; j<50; ++j){
	r1var[j] = j+1;
	double rxa_n1 = 1/( (1/r1var[j])+ (1/r2)+ (1/r7) );
	double rab_n1 = 1/( (1/r3)+ (1/r6)+ (1/r8)+ (1/r9)+ (1/r11)+ (1/r12) );
	double rby_n1 = 1/( (1/r5)+ (1/r4)+ (1/r10) );

	double r1eq_n = (rxa_n1 + rab_n1 + rby_n1);
	r1eq_array[j] = r1eq_n ;
}

double r3var[50];						// when we vary r3.
double r3eq_array[50];
for (int j = 0; j<50; ++j){
	r3var[j] = j+1;
	double rxa_n3 = 1/( (1/r1)+ (1/r2)+ (1/r7) );
	double rab_n3 = 1/( (1/r3var[j])+ (1/r6)+ (1/r8)+ (1/r9)+ (1/r11)+ (1/r12) );
	double rby_n3 = 1/( (1/r5)+ (1/r4)+ (1/r10) );

	double r3eq_n = (rxa_n3 + rab_n3 + rby_n3);
	r3eq_array[j] = r3eq_n ;
}



	cout << "The ingoing current is = " << i0 << endl;

    Matrix<double,2> v(5, 1);       // column vector with 3 rows
    v[0][0] = i0*(r10);
    v[1][0] = i0*(r10+ r8);
	v[2][0] = i0*(-r7 -r8);
	v[3][0] = 0;
	v[4][0] = 0;


    cout << " v = \n" << v << endl;
    cout << "v.dim1 = " << v.dim1() << endl;
 
    Matrix<double,2> R(5, 5);       // 5x5 resistance matrix
    R[0][0] =  ( -r9 -r11);             // set components using slicing notation	1
    R[0][1] =  ( -r9)  ;
    R[0][2] =  ( r9+ r11)  ;
	R[0][3] =  ( r10) ;
	R[0][4] =  ( r11+ r5+ r10+ r9) ;

    R[1][0] =  ( r8)  ;        // set components using slicing notation	2
    R[1][1] =  ( r8)  ;
    R[1][2] =  ( -r8 -r6) ;
	R[1][3] =  ( r4+ r10+ r8+ r6) ;
	R[1][4] =  ( r10) ;

    R[2][0] =  ( -r7 -r8 -r9)  ;        // set components using slicing notation	3
    R[2][1] =  ( -r7 -r8 -r9 -r2)  ;
    R[2][2] =  ( r8+ r9)  ;
	R[2][3] =  ( -r8) ;
	R[2][4] =  ( r9) ;

    R[3][0] =  ( r12)  ;         // set components using slicing notation	4
    R[3][1] =  ( 0)  ;
    R[3][2] =  ( -r12 -r3)  ;
	R[3][3] =  ( -r4) ;
	R[3][4] =  ( r5) ;

    R[4][0] =  ( r12+ r11+ r1)  ;         // set components using slicing notation	5
    R[4][1] =  ( -r2)  ;
    R[4][2] =  ( -r12 -r11)  ;
	R[4][3] =  ( 0) ;
	R[4][4] =  ( -r11) ;

 




/*


    R[1][0] = r1 + ra;
    R[1][1] = -ra;
    R[1][2] = -r3;
 
    R(2,0) = rx + ra;               // or use subscripting notation
    R(2,1) = -r2 - rx - ra;
    R(2,2) = rx;
 */
    cout << " R = \n" << R << std::endl;
    cout << " R.dim1 = " << R.dim1() << endl;
    cout << " R.dim2 = " << R.dim2() << endl;
 
    // the solve_Gauss_Jordan replaces R by R^-1 and v by i
    // so save the original R and copy v into a vector i
    Matrix<double,2> R_save(R), i(v);
 
    solve_Gauss_Jordan(R, i);
    cout << " Solution using Gauss-Jordan elimination\n i = \n"
         << i << endl;
 
    // find the other currents
//    cout << " i_a = i_1 - i_2 = " << i[0] - i[1] << '\n'
//         << " i_v = i_1 + i_3 = " << i[0] + i[2] << '\n'
//         << " i_x = i_1 - i_2 + i_3 = " << i[0] - i[1] + i[2] << '\n'
//         << endl;
 
    // see whether LU decomposition gives the same answer
    i = v;
    solve_LU_decompose(R_save, i);
    cout << " Solution using LU Decompositon\n i = \n"
         << i << endl;



	cout << "The equivalent resistants are" << endl;
for (int k=0; k<50; ++k){
cout << r1var[k] << "	" << r1eq_array[k] << "    " <<	r3eq_array[k] << endl;
}

ofstream Compare_cube("Compare_cube.dat");
for (int p=0; p<50; ++p){

Compare_cube << r1var[p] << "    " << r1eq_array[p] << "    " << r3eq_array[p] << endl;
}

}
