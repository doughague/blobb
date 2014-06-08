/** \file      Random.cxx 
    \brief     Source for Random 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Random.hh"    // this class
#include "blobb/ClassImp.hh"  // blobb class implementation
#include "blobb/CLUI.hh"      // command-line user interface
#include "blobb/Math.hh"      // math helpers

//! Blobb class implementation macro
BLOBB_CLASS_IMP(Random)

namespace Blobb {
    
//_____________________________________________________________________________
//! The maximum integer returned by the std::rand function.
/** The RAND_MAX macro expands to an integral constant expression whose value is the 
    maximum value returned by the std::rand function.
    This value is library-dependent, but is guaranteed to be at least 32767 
    on any standard library implementation.
 */
static const UInt_t gRandMax = RAND_MAX;

//_____________________________________________________________________________
/** Default constructor. */
Random::Random(UInt_t seed, UInt_t numIter)
  : AbsObject(),
    mSeed(),
    mNumIter()
{
  setSeed(seed);
  setNumIter(numIter);
}

//_____________________________________________________________________________
/** Copy constructor. */
Random::Random(const Random& other, const string& /*newName*/)
  : AbsObject(other),
    mSeed(other.mSeed),
    mNumIter(other.mNumIter)
{}

//_____________________________________________________________________________
/** Assignment operator. */
Random& Random::operator=(const Random& rhs)
{
  AbsObject::operator=(rhs);
  mSeed    = rhs.mSeed;
  mNumIter = rhs.mNumIter;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t Random::isEmpty() const
{
  if(mSeed    != 0) return kFalse;
  if(mNumIter != 0) return kFalse;
  return kTrue;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void Random::clear()
{
  mSeed    = 0;
  mNumIter = 0;
}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t Random::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const Random& n = dynamic_cast<const Random&>(other); 
    // check members
    if(mSeed    != n.seed())  return kFalse;
    if(mNumIter != n.numIter()) return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}

//_____________________________________________________________________________
//! Seed the random number generator.
/** Default argument, seed = 0, seeds the random number generator to 
    value to local "now" time.
    If seed is set to 1, the generator is reinitialized to its initial value 
    and produces the same values as before any call to rand or srand.
*/
void Random::setSeed(UInt_t seed)
{
  UInt_t s = seed;
  if(seed == 0) s = time(NULL);
  mSeed = s;
  srand(mSeed);
}

//_____________________________________________________________________________
//! Set the number of iterations.
void Random::setNumIter(UInt_t numIter)
{
  setSeed(mSeed);
  for(UInt_t n=0; n<numIter; n++) rndm();
}

//_____________________________________________________________________________
/** A uniform random floating-point number in the range [0., max]. 
    If max == 0., a maximum of 1. is used.
*/
Double_t Random::rndm(Double_t max) const
{
  mNumIter++;
  if(max == 0.) return Double_t(rand()) / Double_t(gRandMax);
  else return max * Double_t(rand()) / Double_t(gRandMax);
}

//_____________________________________________________________________________
/** A uniform random integer number in the range [0, max-1]. 
    If max == 0., a maximum of gRandMax is used.
*/
UInt_t Random::integer(UInt_t max) const
{
  mNumIter++;
  if(max == 0) return rand();
  else return rand() % max;
}

//_____________________________________________________________________________
/** A uniform random double number in the range [min, max]. */
Double_t Random::uniform(Double_t min, Double_t max) const
{
  return min + rndm()*(max-min);
}

//_____________________________________________________________________________
/** An exponential random variate: \f$ e^{-t/\tau} \f$. */
Double_t Random::exponential(Double_t tau) const
{
  return (-tau * Math::Ln(rndm()));
}

//_____________________________________________________________________________
/** A gaussian random variate with mean and sigma: 
    \f[ \frac{e^{-(t-\mu)^2/\sigma^2}}{\sqrt{2\pi\sigma^{2}}} \f]. 

    This method was taken from <a href="http://root.cern.ch/root/html/src/TRandom.cxx.html">TRandom</a> 
    on 04.10.2013 by Doug Hague and included the following documentation:

    Samples a random number from the Gaussian Distribution 
    with the given mean and sigma.                                                 
    Uses the Acceptance-complement ratio from W. Hoermann and G. Derflinger 
    This is one of the fastest existing method for generating normal random variables. 
    It is a factor 2/3 faster than the polar (Box-Muller) method used in the previous 
    version of TRandom::Gaus. The speed is comparable to the Ziggurat method (from Marsaglia)
    implemented for example in GSL and available in the MathMore library. 
                                                                            
    REFERENCE:  - W. Hoermann and G. Derflinger (1990):                       
    The ACR Method for generating normal random variables,       
    OR Spektrum 12 (1990), 181-185.                             
                                                                            
    Implementation taken from 
    UNURAN (c) 2000  W. Hoermann & J. Leydold, Institut f. Statistik, WU Wien 
*/
Double_t Random::gaussian(Double_t mean, Double_t sigma) const
{
  static const Double_t kC1 = 1.448242853;
  static const Double_t kC2 = 3.307147487;
  static const Double_t kC3 = 1.46754004;
  static const Double_t kD1 = 1.036467755;
  static const Double_t kD2 = 5.295844968;
  static const Double_t kD3 = 3.631288474;
  static const Double_t kHm = 0.483941449;
  static const Double_t kZm = 0.107981933;
  static const Double_t kHp = 4.132731354;
  static const Double_t kZp = 18.52161694;
  static const Double_t kPhln = 0.4515827053;
  static const Double_t kHm1 = 0.516058551;
  static const Double_t kHp1 = 3.132731354;
  static const Double_t kHzm = 0.375959516;
  static const Double_t kHzmp = 0.591923442;
  static const Double_t kAs = 0.8853395638;
  static const Double_t kBs = 0.2452635696;
  static const Double_t kCs = 0.2770276848;
  static const Double_t kB  = 0.5029324303;
  static const Double_t kX0 = 0.4571828819;
  static const Double_t kYm = 0.187308492 ;
  static const Double_t kS  = 0.7270572718 ;
  static const Double_t kT  = 0.03895759111;

  Double_t result;
  Double_t rn,x,y,z;
  do {
    y = rndm();
    if (y>kHm1) {
      result = kHp*y-kHp1; break; }
  
    else if (y<kZm) {  
      rn = kZp*y-1;
      result = (rn>0) ? (1+rn) : (-1+rn);
      break;
    } 

    else if (y<kHm) {  
        rn = rndm();
        rn = rn-1+rn;
      z = (rn>0) ? 2-rn : -2-rn;
      if ((kC1-y)*(kC3+Math::Abs(z))<kC2) {
	result = z; break; }
      else {  
	x = rn*rn;
	if ((y+kD1)*(kD3+x)<kD2) {
	  result = rn; break; }
	else if (kHzmp-y<Math::Exp(-(z*z+kPhln)/2)) {
	  result = z; break; }
	else if (y+kHzm<Math::Exp(-(x+kPhln)/2)) {
	  result = rn; break; }
      }
    }

    while (1) {
      x = rndm();
      y = kYm * rndm();
      z = kX0 - kS*x - y;
      if (z>0) 
	rn = 2+y/x;
      else {
	x = 1-x;
	y = kYm-y;
	rn = -(2+y/x);
      }
      if ((y-kAs+x)*(kCs+x)+kBs<0) {
	result = rn; break; }
      else if (y<x+kT)
	if (rn*rn<4*(kB-Math::Ln(x))) {
	  result = rn; break; }
    }
  } while(0);
  return mean + sigma * result;
}

//_____________________________________________________________________________
/** An Poisson random variate: \f$ \mu^{t} e^{-\mu} / t! \f$. */
Double_t Random::poisson(Double_t mean) const
{
  int n;
  if (mean <= 0) return 0;
  if (mean < 25) {
    Double_t expmean = Math::Exp(-mean);
    Double_t pir = 1;
    n = -1;
    while(1) {
      n++;
      pir *= rndm();
      if (pir <= expmean) break;
    }
    return static_cast<Double_t>(n);
  }
  // for large value we use inversion method
  else if (mean < 1E9) {
    Double_t em, t, y;
    Double_t sq, alxm, g;

    sq = Math::Sqrt(2.0*mean);
    alxm = Math::Ln(mean);
    g = mean*alxm - Math::LnGamma(mean + 1.0);

    do {
      do {
	y = Math::Tan(Math::Pi()*rndm());
	em = sq*y + mean;
      } while( em < 0.0 );

      em = Math::Floor(em);
      t = 0.9*(1.0 + y*y)* Math::Exp(em*alxm - Math::LnGamma(em + 1.0) - g);
    } while( rndm() > t );

    return em;

  } else {
    // use Gaussian approximation for very large values
    return gaussian(0,1)*Math::Sqrt(mean) + mean +0.5;
  }
}

//_____________________________________________________________________________
/** An Power-Law random variate: 
    \f[ \frac{\gamma-1}{x_{min}} \left( \frac{x}{x_{min}} \right)^{-\gamma} \f]. 
*/
Double_t Random::powerlaw(Double_t xmin, Double_t gamma) const
{
  if(gamma != 1.0) return xmin * Math::Pow((1.-rndm()), -1./(gamma-1.));
  else return 0.;
}

//_____________________________________________________________________________
//! Read this object from user interface.
Bool_t Random::readFromUI(CLUI& clui, Bool_t /*verbose*/) 
{ 
  clui.request("Seed");
  setSeed(UInt_t(clui.readDouble()));
  clui.request("Number of Iterations");
  setNumIter(UInt_t(clui.readDouble()));
  return kTrue;
}

//_____________________________________________________________________________
//! Print this object to user interface.
void Random::printToUI(CLUI& clui, Bool_t /*verbose*/) const
{ 
  clui.os() << "Random: " << mSeed << ", " << mNumIter << endl;
}


} // end namespace Blobb
