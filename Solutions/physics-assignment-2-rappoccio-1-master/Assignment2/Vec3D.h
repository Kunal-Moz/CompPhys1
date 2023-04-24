#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>

// Minimal four-vector class
class Vec3D{
  // Partially stolen from ROOT::TVector3 (https://root.cern.ch/doc/master/classTVector3.html)
public:
  Vec3D(double ix=0, double iy=0, double iz=0) :
    x_(ix),y_(iy),z_(iz){};

  inline double x() const { return x_;}
  inline double y() const { return y_;}
  inline double z() const { return z_;}
  double perp() const ;
  double perp2() const ;
  double p() const ;
  double r() const { return p(); }
  double phi() const ;
  double theta() const ;
  double cosTheta() const ;

  std::string PrintXYZ() const ;
  std::string Print() const ;

  inline void set_x(double xi) { x_=xi;}
  inline void set_y(double yi) { y_=yi;}
  inline void set_z(double zi) { z_=zi;}
  
  Vec3D operator+( const Vec3D & right) const ;
  Vec3D operator-( const Vec3D & right) const ;
  double operator*(const Vec3D & right) const ;

  Vec3D hat() const;
    
  double dtheta( Vec3D const & v) const;
  
protected :
  double x_;
  double y_;
  double z_;
};


void testVec3Ds();

#endif
