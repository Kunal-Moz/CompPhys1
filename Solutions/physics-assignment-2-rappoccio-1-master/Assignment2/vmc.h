// Variational Monte Carlo for the harmonic oscillator
#ifndef vmc_h
#define vmc_h

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "Vec3D.h"

class VMC {
public :

  // Allow multiple particles to account for QHO, Hydrogen, and Helium simultaneously
  typedef std::vector<Vec3D> State; 

  VMC(int Nin, std::vector<double> const & varsin, int MCStepsin);

  virtual ~VMC() {}; 

  // Initialization depends on base class
  virtual void init_dist() = 0; 
  
  void zeroAccumulators();

  // Probability of the trial given the previous x
  virtual double p(State const & xTrial, State const & x) = 0;

  // local energy
  virtual double eLocal(State const & xi) = 0;

  // Perform one Metropolis step
  void MetropolisStep(); 

  // runs N Metropolis steps sequentially
  void oneMonteCarloStep(); 

  // Runs 20% of MCSteps to adjust
  // the step size so acceptance ~ 50%
  void adjustStep(); 

  // production steps
  void doProductionSteps( );

  void printout();

  virtual void normPsi() = 0;

  std::vector<double> const & get_psiSqd() const { return psiSqd; }

  double get_eAve() const { return eSum / double(N) / MCSteps;}
  double get_eVar() const { double eAve = get_eAve(); return eSqdSum / double(N) / MCSteps - eAve * eAve;}


  double get_xMin() const { return xMin;}
  double get_xMax() const { return xMax;}
  double get_dx() const { return dx; }
  
protected :

  // C++11 random number generator from Mersenne twister. 
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  std::normal_distribution<> gausdev;

  int N;                         // number of walkers
  std::vector<State> x;          // walker positions
  std::vector<double> delta;     // step size
  double eSum;                   // accumulator to find energy
  double eSqdSum;                // accumulator to find fluctuations in E
  double xMin;                   // minimum x for histogramming psi^2(x)
  double xMax;                   // maximum x for histogramming psi^2(x)
  double dx;                     // psi^2(r) histogram step size
  std::vector<double> psiSqd;    // psi^2(r) histogram
  int nPsiSqd;                   // size of array
  std::vector<double> vars;      // trial function depends on vars
  int nAccept;                   // accumulator for number of accepted steps
  int MCSteps;                   // number of MC steps
    
  static constexpr double pi = 3.14159;
};

class QHO : public VMC{
public:
  QHO(int Nin, std::vector<double> const & varsin, int MCStepsin) : VMC(Nin, varsin, MCStepsin){
    init_dist();
  }
  ~QHO() {}
  void init_dist() override;
  double eLocal(State const & xi) override;
  double p(State const & xTrial, State const & x) override; 
  virtual void normPsi() override; 
};


class Hydrogen : public VMC{
public:
  Hydrogen(int Nin, std::vector<double> const & varsin, int MCStepsin) : VMC(Nin, varsin, MCStepsin){
    init_dist();
  }
  ~Hydrogen() {}
  void init_dist() override;
  double eLocal(State const & xi) override;
  double p(State const & xTrial, State const & x) override; 
  virtual void normPsi() override; 
};

class Helium : public VMC{
public:
  Helium(int Nin, std::vector<double> const & varsin, int MCStepsin) : VMC(Nin, varsin, MCStepsin){
    init_dist();
  }
  ~Helium() {}
  void init_dist() override;
  double eLocal(State const & xi) override;
  double p(State const & xTrial, State const & x) override; 
  virtual void normPsi() override; 
};




#endif 
