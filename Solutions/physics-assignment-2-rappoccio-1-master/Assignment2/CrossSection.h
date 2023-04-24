// Adapted from the MSTW2008 code file example.cc
// Needs mstwpdf.cc mstwpdf.h mstw2008lo.00.dat
// c++  mstw.cpp  mstwpdf.cc
#ifndef CrossSection_h
#define CrossSection_h

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "mstwpdf.h"
#include "LorentzVector.h"
#include "Particle.h"


// Calculate Drell-Yan cross section given initial quark momenta p1 and p2
double dSigmaDOmega( const Particle & p1, const Particle & p2, int pdgID_out, double cosTheta );

class dSigmaDOmega_PP{
  public:
    dSigmaDOmega_PP( double e_com, c_mstwpdf & pdf, double q, int flavor, double cosTheta ):
        e_com_(e_com), pdf_(pdf), q_(q), flavor_(flavor), cosTheta_(cosTheta){}
    
    double operator()( std::vector<double> const & x );
  protected:
    double e_com_; 
    c_mstwpdf & pdf_;
    double q_;
    int flavor_;
    double cosTheta_;
};
#endif
