#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

// Helper function to compute the distance between two vectors.
float distance( std::vector<float> const & a,
		std::vector<float> const & b ) {
  if ( a.size() != b.size() ) {
    std::cout << "error in distance: size does not match" << std::endl;
    return -1.0;
  }
  float sum = 0.0;
  for ( unsigned int i = 0; i < a.size(); ++i ) {
    sum += pow(a[i] - b[i], 2.0);    
  }
  sum = sqrt(sum);
  return sum;
}

int main(int argc, char ** argv){

  // Make sure the command line options are correctly set
  std::vector< std::vector<float> > points;
  if ( argc < 4 || (argc-1)%2 != 0 ) {
    std::cout << "Error. Please enter list of 2-d vectors on the command line." << std::endl;
    return 0;
  }

  // Input points from command line. 
  for ( unsigned int i = 1; i < argc; i+=2 ) {
    float xi = atof( argv[i] );
    float yi = atof( argv[i+1] );
    points.push_back( {xi, yi} );
    std::cout << "Input : (" << xi << "," << yi << ")" << std::endl;
  }
  // Find minimum. First set to a large value, loop over
  // inputs, and find the pair with smallest magnitude. 
  float min = std::numeric_limits<float>::max();
  std::vector< std::vector<float> >::const_iterator min1 = points.end();
  std::vector< std::vector<float> >::const_iterator min2 = points.end();
  for ( std::vector< std::vector<float> >::const_iterator i = points.begin(); i != points.end(); ++i ) {
    for ( std::vector< std::vector<float> >::const_iterator j = i + 1; j != points.end(); ++j ) {
      float d = distance( *i, *j );
      if ( d < 0.0 ) { // Error case
	std::cout << "Invalid inputs." << std::endl;
	return 0;
      }
      if ( d < min ) {
	min1 = i;
	min2 = j;
	min = d;
      }
    }
  }
  std::cout << "The minimum pair is (" << min1->at(0) << "," << min1->at(1) << ")  -- (" << min2->at(0) << "," << min2->at(1) << ") " << std::endl;
  std::cout << " mag = " << min << std::endl;

  return 0;
}
