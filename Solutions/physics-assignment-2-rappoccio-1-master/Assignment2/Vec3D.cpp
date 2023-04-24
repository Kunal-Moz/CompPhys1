#include "Vec3D.h"


double Vec3D::perp() const { return sqrt(perp2()); }
double Vec3D::perp2() const { return x_*x_+y_*y_; }
double Vec3D::p() const { return sqrt(perp2() + z_*z_); }
double Vec3D::phi() const { return x_==0.0 && y_ == 0.0 ? 0.0 : atan2(y_,x_); }
double Vec3D::theta() const { return  x_ == 0.0 && y_ == 0.0 && z_ == 0.0 ? 0.0 : atan2(perp(),z_); }
double Vec3D::cosTheta() const {
  double mag = sqrt(x_*x_ + y_*y_ + z_*z_);
  return mag == 0. ? 1.0 : z_ / mag;
}

std::string Vec3D::PrintXYZ() const {
  std::stringstream ss;
  ss << "(x,y,z) = (" << x_ << ", " << y_ << ", " << z_ << ")";
  return std::move(ss.str());
};

std::string Vec3D::Print() const {
  std::stringstream ss;
  ss << PrintXYZ(); 
  return std::move(ss.str());
};
  
  
Vec3D Vec3D::operator+( const Vec3D & right) const { return std::move( Vec3D(x_+right.x_,y_+right.y_,z_+right.z_) ); }
Vec3D Vec3D::operator-( const Vec3D & right) const { return std::move( Vec3D(x_-right.x_,y_-right.y_,z_-right.z_) ); }
double Vec3D::operator*(const Vec3D & right) const { return x_*right.x_ + y_*right.y_ + z_*right.z_; }

Vec3D Vec3D::hat() const{
    return Vec3D( x_/p(), y_/p(), z_/p() );
}

double Vec3D::dtheta( Vec3D const & v) const{
    return hat() * v.hat(); 
}


void testVec3Ds()
{
  
  std::cout << "Testing three vectors:" << std::endl;
  Vec3D v1(1.0,0.0,0.0);
  Vec3D v2(0.0,1.0,0.0);
  Vec3D v3(0.0,0.0,1.0);

  std::cout << v1.Print() << std::endl;
  std::cout << v2.Print() << std::endl;
  std::cout << v3.Print() << std::endl;
  
  Vec3D s1 = v1 + v2;
  Vec3D s2 = v1 + v3;
  std::cout << s1.Print() << std::endl;
  std::cout << s2.Print() << std::endl;
}
