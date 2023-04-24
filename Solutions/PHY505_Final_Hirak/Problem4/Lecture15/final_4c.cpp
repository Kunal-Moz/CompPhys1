#include <iostream>
using namespace std;

#include "linalg.hpp"
using namespace cpt;

int main()
{


    double m1 = 1, m2 = 1, m3= 1;

    // Matrix with masses as the diagonal elements
    Matrix<double,2> M(9, 9);
    M(0,0) = m1;
    M(1,1) = m2;
    M(2,2) = m3;
    M(3,3) = m1;
    M(4,4) = m2;
    M(5,5) = m3;
    M(6,6) = m1;
    M(7,7) = m2;
    M(8,8) = m3;
    cout << "M =\n" << M;


    Matrix<double,2> v(9, 1);       // column vector with 3 rows
    v(0,0) = 1.0;
    v(1,0) = 1.0;
    v(2,0) = 1.0;
    
    cout << " v = \n" << v << endl;
    cout << "v.dim1 = " << v.dim1() << endl;



    Matrix<double,2> Minv(9,9);
    inverse(M, Minv);
    cout << "Minv=" << endl << Minv << endl;

    // "Spring" constants affecting each mass
    double k12 = 1, k23 = 1;
    double Lagrange[9][9] = {
        {   3, -1, -1,  0,  0,  0,  0,  0,  0},
        {  -1,  3, -1, -1,  0,  0,  0,  0,  0},
        {  -1, -1,  3, -1, -1,  0,  0,  0,  0},
        {   0, -1, -1,  3, -1, -1,  0,  0,  0},
        {   0,  0, -1, -1,  3, -1, -1,  0,  0},
        {   0,  0,  0, -1, -1,  3, -1, -1,  0},
        {   0,  0,  0,  0, -1, -1,  3, -1, -1},
        {   0,  0,  0,  0,  0, -1, -1,  3, -1},
        {   0,  0,  0,  0,  0,  0, -1, -1,  3}
    };
    Matrix<double,2> K(9, 9);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            K(i,j) = Lagrange[i][j];
    cout << "K =\n" << K;

    
    Matrix<double,2> Kinv(9,9);
    inverse(K, Kinv);
    cout << "Kinv=" << endl << Kinv << endl;


    Matrix<double,2> R_save(Kinv), i(v);
 
    solve_Gauss_Jordan(Kinv, i);
    cout << " Solution using Gauss-Jordan elimination\n i = \n"
         << i << endl;
    for (int j=0; j<1001; ++j){
        v = i;
        Matrix<double,2> R_save(Kinv), i(v);
        solve_Gauss_Jordan(Kinv, i);
        if (j == 999){cout << j <<"th Solution using Gauss-Jordan elimination\n i = \n"
         << i << endl;}
    }


    // Solve with generalized eigenvector solution
    //Matrix<double,1> eigenvalues = solve_eigen_generalized(K, M, true);

    //cout << "Eigenvalues =\n" << eigenvalues << endl
      //   << "Eigenvectors =\n" << K;


}
