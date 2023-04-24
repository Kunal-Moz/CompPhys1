#include <iostream>
using namespace std;

#include "linalg.hpp"
using namespace cpt;

int main()
{


    double m1 = 15.994, m2 = 12, m3= m2, m4 = m2, m5 = m1;		// C has mass of 12 amu and O has 15.994amu.  

    // Matrix with masses as the diagonal elements
    Matrix<double,2> M(5, 5);
    M(0,0) = m1;
    M(1,1) = m2;
    M(2,2) = m3;
    M(3,3) = m4;
    M(4,4) = m5;

    cout << "M =\n" << M;


    Matrix<double,2> Minv(5,5);
    inverse(M, Minv);
    cout << "Minv=" << endl << Minv << endl;

    // "Spring" constants affecting each mass
    double k = 15, kp = 12.69;		// multiplied by 10^5 in units of some atomic scale
    double Lagrange[5][5] = {
        {   k,	    	-k,		0,		0,		0},
        {  -k,	    (k+kp),	      -kp,		0,		0},
        {   0,         -kp,    	   (2*kp),	      -kp,		0},
	{   0,    	 0,	      -kp,	   (k+kp),	      -kp},
	{   0,  	 0,		0,	      -kp,		k}
    };
    Matrix<double,2> K(5, 5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            K(i,j) = Lagrange[i][j];
    cout << "K =\n" << K;




    // Solve with generalized eigenvector solution
    Matrix<double,1> eigenvalues = solve_eigen_generalized(K, M, true);

    cout << "Eigenvalues =\n" << eigenvalues << endl
         << "Eigenvectors =\n" << K;


}
