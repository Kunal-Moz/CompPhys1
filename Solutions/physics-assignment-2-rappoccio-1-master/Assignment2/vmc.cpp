// Variational Monte Carlo for the harmonic oscillator
#include "vmc.h"

VMC::VMC(int Nin, std::vector<double> const & varsin, int MCStepsin) :
  rd(), gen(rd()), dis(0,1.), gausdev(),
  N(Nin), eSum(0), eSqdSum(0), xMin(0), xMax(0), dx(0),
  nPsiSqd(0), vars(varsin), nAccept(0), MCSteps(MCStepsin)
{
  zeroAccumulators();
}


void VMC::zeroAccumulators() {
  eSum = eSqdSum = 0;
  for (int i = 0; i < nPsiSqd; i++)
    psiSqd[i] = 0;
}

void VMC::MetropolisStep() {

  // choose a walker at random
  int n = int(dis(gen) * N);

  // make a trial move
  State xTrial (x[n].size());
  for ( unsigned int istate = 0; istate < xTrial.size(); ++istate ){
    std::vector<double> dvals;
    for ( auto d : delta ){
      dvals.push_back( d > 0 ? d * gausdev(gen) : 0 );
    }
    xTrial[istate] = x[n][istate] + Vec3D( dvals[0], dvals[1], dvals[2] );
  }
  
  // Metropolis test
  if (p(xTrial, x[n]) > dis(gen) ) {
    x[n] = xTrial;
    ++nAccept;
  }

  // accumulate energy and wave function
  double e = eLocal(x[n]);
  eSum += e;
  eSqdSum += e * e;
  int i = int((x[n][0] - xMin).r() / dx);
  if (i >= 0 && i < nPsiSqd )
    psiSqd[i] += 1;
}

void VMC::oneMonteCarloStep() {

  // perform N Metropolis steps
  for (int i = 0; i < N; i++) {
    MetropolisStep();
  }
}

void VMC::adjustStep() {
  // perform 20% of MCSteps as thermalization steps
  // and adjust step size so acceptance ratio ~50%
  int thermSteps = int(0.2 * MCSteps);
  int adjustInterval = int(0.1 * thermSteps) + 1;

  //std::cout << " Performing " << thermSteps << " thermalization steps ..."
  //<< std::flush;
  for (int i = 0; i < thermSteps; i++) {
    oneMonteCarloStep();
    if ((i+1) % adjustInterval == 0) {
      for ( double & idelta : delta ){
        idelta *= nAccept / (0.5 * N * adjustInterval) ;
      }
      nAccept = 0;
    }
  }
  //std::cout << "\n Adjusted Gaussian step size = " << delta[0] << std::endl;    
}


// production steps
void VMC::doProductionSteps( ) {
  zeroAccumulators();
  nAccept = 0;
  //std::cout << " Performing " << MCSteps << " production steps ..." << std::flush;
  for (int i = 0; i < MCSteps; i++)
    oneMonteCarloStep();
}

void VMC::printout() {

  // compute and print energy
  double eAve = get_eAve(); 
  double eVar = get_eVar(); 
  double error = sqrt(eVar) / sqrt(double(N) * MCSteps);
  std::cout << "\n <Energy> = " << eAve << " +/- " << error
	    << "\n Variance = " << eVar << std::endl;

}



void QHO::init_dist(){
  x.resize(N);
  for (int i = 0; i < N; i++) {
    x[i].resize(1); 
    x[i][0].set_x( dis(gen)-0.5 );
  }
  delta.resize(1);
  delta[0] = 1;
  xMin = -10;
  xMax = +10;
  dx = 0.1;

  nPsiSqd = int((xMax - xMin) / dx);
  psiSqd.resize(nPsiSqd);
  nAccept = 0;

}

double QHO::eLocal(State const & xi) {
  double alpha = vars[0];
  // compute the local energy
  return alpha + xi[0].x() * xi[0].x() * (0.5 - 2 * alpha * alpha);
}

double QHO::p(State const & xTrial, State const & x) {
  // compute the ratio of rho(xTrial) / rho(x)
  return exp(- 2 * vars[0] * (xTrial[0].x()*xTrial[0].x() - x[0].x()*x[0].x()));
}

void QHO::normPsi() {
  double psiNorm = 0;
  for (int i = 0; i < nPsiSqd; i++)
    psiNorm += psiSqd[i] * dx;
  for (int i = 0; i < nPsiSqd; i++) {
     psiSqd[i] /= psiNorm;
  }
}




void Hydrogen::init_dist(){
  x.resize(N);
  for (int i = 0; i < N; i++){
    x[i].resize(1); 
    x[i][0] = Vec3D( dis(gen)-0.5, dis(gen)-0.5, dis(gen)-0.5 );
  }
  delta.resize(3); 
  delta[0] = 1;  
  delta[1] = 1;
  delta[2] = 1;
  xMin = 0;
  xMax = 5;
  dx = 0.1;

  nPsiSqd = int((xMax - xMin) / dx);
  psiSqd.resize(nPsiSqd);
  nAccept = 0;

}

double Hydrogen::eLocal(State const & xi) {
  double r = xi[0].p();
  if ( std::abs(r) < 0.0001)
      r = 0.0001; 
  double alpha = vars[0];    
  return -(1-alpha)/r - 0.5*alpha*alpha;    
}

double Hydrogen::p(State const & xTrial, State const & x) {
  double r1t = xTrial[0].p();
  double r1 = x[0].p();
  double alpha = vars[0];
  double retval = exp( -2*alpha*(r1t-r1 ) );
  return retval; 
}

void Hydrogen::normPsi() {
  double psiNorm = 0;
  for (int i = 0; i < nPsiSqd; i++){
    double r =i*dx;
    psiNorm += 4*pi*r*r*psiSqd[i] * dx;
  }
  for (int i = 0; i < nPsiSqd; i++) {
     psiSqd[i] /= psiNorm;
  }
}

void Helium::init_dist(){
  x.resize(N);
  for (int i = 0; i < N; i++){
    x[i].resize(2); 
    x[i][0] = Vec3D( dis(gen)-0.5, dis(gen)-0.5, dis(gen)-0.5 );
    x[i][1] = Vec3D( dis(gen)-0.5, dis(gen)-0.5, dis(gen)-0.5 );
  }
  delta.resize(3); 
  delta[0] = 1;
  delta[1] = 1;
  delta[2] = 1;   
  xMin = 0;
  xMax = 5;
  dx = 0.1;

  nPsiSqd = int((xMax - xMin) / dx);
  psiSqd.resize(nPsiSqd);
  nAccept = 0;

}

double Helium::eLocal(State const & xi) {
  auto & r1 = xi[0];
  auto & r2 = xi[1];
  auto r12 = r1 - r2;
  double alpha = vars[0];
    
  if ( r1.p() > 0.0001 && r2.p() > 0.0001 && r12.p() > 0.0001){
      auto den = 1+alpha*r12.p();
      return -4 + 
          alpha/den+
          alpha/pow(den, 2)+
          alpha/pow(den, 3)-
          1./(4*pow(den, 4))+
          (r12.hat()*(r1.hat() - r2.hat()) / pow(1+alpha*r12.p(), 2));
  }
    
  return 0;
}

double Helium::p(State const & xTrial, State const & x) {
  auto & r1t = xTrial[0];
  auto & r2t = xTrial[1];
  auto & r1 = x[0];
  auto & r2 = x[1];
  auto r12t = r1t-r2t;
  auto r12 = r1 - r2;
  double alpha = vars[0];
  double den = (1 + alpha * r12.p());
  double psit = exp( -2*r1t.p() ) * exp(-2*r2t.p()) * exp( 0.5*r12t.p() / (1 + alpha*r12t.p() ));
  double psi  = exp( -2*r1.p() )  * exp(-2*r2.p())  * exp( 0.5*r12.p()  / (1 + alpha*r12.p() ));
  //std::cout << "psit = " << psit << std::endl;
  //std::cout << "psi  = " << psi << std::endl;
  auto retval = (abs(psi)>0) ? pow(psit/psi,2) : 0;
  //std::cout << "r1t = " << r1t.Print() << std::endl;
  //std::cout << "r2t = " << r2t.Print() << std::endl;
  //std::cout << "r1  = " << r1.Print() << std::endl;
  //std::cout << "r2  = " << r2.Print() << std::endl;
  //std::cout << "retval = " << retval << std::endl;
  return retval; 
}

void Helium::normPsi() {
  double psiNorm = 0;
  for (int i = 0; i < nPsiSqd; i++){
    double r =i*dx;
    psiNorm += 4*pi*r*r*psiSqd[i] * dx;
  }
  for (int i = 0; i < nPsiSqd; i++) {
     psiSqd[i] /= psiNorm;
  }
}
