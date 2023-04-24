#include <iostream>
#include <cmath>
#include <limits>

unsigned long factorial(unsigned long x) {
  unsigned long fact = 1;
  if (x == 0 ) {
    return 1;
  }
  else {
    do {
      fact *= x;
      x--;
    } while ( x > 0 );
    return fact; 
  }
}

double stirling(double x) {
  if ( std::abs(x) > 0.000000001 ) {
    return x*log(x) - x;
  } else {
    return 1.0;
  }
}


int main(void){
  unsigned long x = 0;
  std::cout << "Enter a number, negative to exit:" << std::endl;
  while ( std::cin >> x ) {
    if ( x < 20 ) {
      unsigned long fact = factorial(x);
      std::cout << "x = " << x << ", x!= " << fact << std::endl;
    } else {
      double lnfact = stirling(x);
      std::cout << "x = " << x << ", ln(x!)= " << lnfact << std::endl;
    }
  }  
  return 0;
}
