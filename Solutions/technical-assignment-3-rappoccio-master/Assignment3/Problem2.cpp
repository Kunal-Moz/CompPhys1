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

int main(void){
  unsigned long x = 0;
  std::cout << "Enter a number, negative to exit:" << std::endl;
  while ( std::cin >> x ) {
    if ( x < 20 ) {
      unsigned long fact = factorial(x);
      std::cout << "x = " << x << ", x!= " << fact << std::endl;
    } else {      
      std::cout << "Number is too large for representation" << std::endl;
    }
  }  
  return 0;
}
