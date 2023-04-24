#include "root_finding.hpp"

using namespace std;

double f(double r) {
    int V0 = 2;
    int r0 = 2;
    return V0*exp(r/r0)*cos(M_PI*r/r0);
}
 
int main() {
    cout << " Algorithms for root of y = V0*exp(r/r0)*cos(M_PI*r/r0)\n"
         << " ------------------------------------------------\n";
 
    cout << " 1. Simple search\n"
         << " Enter initial guess x_0, step dx, and desired accuracy: ";
    double x0, dx, acc;
    cin >> x0 >> dx >> acc;
    cout << " answer = " << root_simple(f, x0, dx, acc,10000,false);
 
    cout << "\n\n"
         << " 2. Bisection search\n"
         << " Enter bracketing guesses x_1, x_2, (one root must lie between x1 and x2) and desired accuracy: ";
    double x1;
    cin >> x0 >> x1 >> acc;
	
    cout << " Answer = " << root_bisection(f, x0, x1, acc,1000,false) << endl;
	
	
}
