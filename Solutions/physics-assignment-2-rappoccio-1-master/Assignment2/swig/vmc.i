%module vmc
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "Vec3D.h"
#include "vmc.h"
%}

%include "std_vector.i"
%include "std_string.i"

namespace std {
   %template(vector_double) vector<double>;
   %template(vector_Vec3D) vector<Vec3D>;
   %template(vector_vector_Vec3D) vector<vector<Vec3D>>;
};

%include "vmc.h"

