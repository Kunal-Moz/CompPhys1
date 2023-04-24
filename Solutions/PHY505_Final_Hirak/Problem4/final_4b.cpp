#include <iostream>
using namespace std;

#include "linalg.hpp"
using namespace cpt;

int main()
{


    // "Spring" constants affecting each mass
    		// multiplied by 10^5 in units of some atomic scale
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




    // Solve with generalized eigenvector solution
    Matrix<double,1> eigenvalues = solve_eigen_symmetric(K);

    cout << "Eigenvalues =\n" << eigenvalues << endl
         << "Eigenvectors =\n" << K;


}
