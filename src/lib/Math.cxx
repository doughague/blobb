/** \file      Math.cxx 
    \brief     Source for math functions.
    \author    Doug Hague, NvE 14-nov-1998 UU-SAP Utrecht
    \date      24.07.2013
    \copyright See License.txt
    \note      Most of this code was copied dirrectly from the 
               appropriate ROOT::TMath sources.
*/
#include "blobb/Math.hh"        // these methods
#include "blobb/Exception.hh"   // exception handler
#include <cmath>                // C math library
#ifdef HAVE_LIMITS_H
   #include <limits>            // C++ limits of typed numbers
#endif

namespace Blobb {

namespace Math {

//_____________________________________________________________________________
// std::numeric_limits<Double_t>::infinity() = inf  
// std::numeric_limits<Double_t>::epsilon()  = 2.22045e-16
// std::numeric_limits<Float_t>::infinity()  = inf 
// std::numeric_limits<Float_t>::epsilon()   = 1.19209e-07
#ifdef HAVE_LIMITS_H
   //! infinity
   static const Double_t kInfinity = std::numeric_limits<Double_t>::infinity();
   //! epsilon
   static const Double_t kEpsilon  = std::numeric_limits<Double_t>::epsilon();
#else
   //! infinity
   static const Double_t kInfinity = 1e30;
   //! epsilon
   static const Double_t kEpsilon  = 1e-10;
#endif

//______________________________________________________________________________
/** Machine \f$ \infty \f$ = std::numeric_limits<Double_t>::infinity(). */
Double_t Infinity()
{
  return kInfinity;
}

//______________________________________________________________________________
/** Machine epsilon \f$ 1/\infty \f$. */
Double_t Epsilon()
{
  return kEpsilon;
}

//______________________________________________________________________________
/** Base of the natural logarithm: \f$e\f$. */
Double_t E()
{
  return 2.71828182845904509;
}

//______________________________________________________________________________
/** The natural logarithm of 10: \f$\ln{10}\f$. */
Double_t Ln10()
{
  return 2.30258509299404590;
}

//______________________________________________________________________________
/** The common logarithm of base of the natural logarithm: \f$\log{e}\f$. */
Double_t LogE()
{
  return 4.34294481903251817e-01;
}

//______________________________________________________________________________
/** The logarithm base two of the natural logarithm: \f$\log_{2}{e}\f$. */
Double_t Log2E()
{
  return 1.44269504088896340736;
}

//______________________________________________________________________________
/** Pi: \f$\pi\f$. */
Double_t Pi()
{
  return 3.14159265358979323846;
}

//______________________________________________________________________________
/** \f$ \sqrt{2\pi} \f$. */
Double_t Sqrt2Pi()
{
  return 2.50662827463100024;
}

//______________________________________________________________________________
/** \f$ \frac{1}{\sqrt{2\pi}} \f$. */
Double_t InvSqrt2Pi()
{
  return 0.398942280401432703;
}

//______________________________________________________________________________
/** Conversion factor for converting degrees to radians: \f$ \pi/180 \f$
    One degree is equivalent to PI/180 radians. 
*/
Double_t DegToRad()
{
  return 1.74532925199432955e-02;
}

//______________________________________________________________________________
/** Conversion factor for converting radians to degrees: \f$ 180/\pi \f$
    One radian is equivalent to 180/PI degrees. 
*/
Double_t RadToDeg()
{
  return 5.72957795130823229e+01;
}

//______________________________________________________________________________
/** \f$ \sqrt{2} \f$. */
Double_t Sqrt2()
{
  return 1.41421356237309515;
}

//______________________________________________________________________________
/** \f$ 1/\sqrt{2} \f$. */
Double_t InvSqrt2()
{
  return 0.707106781186547462;
}

//______________________________________________________________________________
/** Convert input degrees to radians: \f$  degrees \times \pi / 180 \f$. */
Double_t ToRadians(Double_t degrees)
{
  return degrees * DegToRad();
}

//______________________________________________________________________________
/** Convert input radians to degrees: \f$  radians \times 180 / \pi \f$. */
Double_t ToDegrees(Double_t radians)
{
  return radians * RadToDeg();
}

//______________________________________________________________________________
/** The cosine function: \f$ \cos{x} \f$. */
Double_t Cos(Double_t radians)
{
  return std::cos(radians);
}

//______________________________________________________________________________
/** The sine function: \f$ \sin{x} \f$. */
Double_t Sin(Double_t radians)
{
  return std::sin(radians);
}

//______________________________________________________________________________
/** The tangent function: \f$ \tan{x} \f$. */
Double_t Tan(Double_t radians)
{
  return std::tan(radians);
}

//______________________________________________________________________________
/** The principal value of the arc cosine of x, expressed in radians:
    \f$ \cos^{-1}{x} \f$. 
*/
Double_t ACos(Double_t x)
{
  return std::acos(x);
}

//______________________________________________________________________________
/** The principal value of the arc sine of x, expressed in radians:
    \f$ \sin^{-1}{x} \f$. 
*/
Double_t ASin(Double_t x)
{
  return std::asin(x);
}

//______________________________________________________________________________
/** The principal value of the arc tangent of x, expressed in radians:
    \f$ \tan^{-1}{x} \f$. 
*/
Double_t ATan(Double_t x)
{
  return std::atan(x);
}

//______________________________________________________________________________
/** Returns the principal value of the arc tangent of y/x, expressed in radians:
    \f$ \tan^{-1}{y/x} \f$. 
*/
Double_t ATan2(Double_t y, Double_t x)
{
  return std::atan2(y,x);
}

//______________________________________________________________________________
/** The exponential function: \f$ e^{x} \f$. */
Double_t Exp(Double_t x)
{
  return std::exp(x);
}

//______________________________________________________________________________
/** The natural logarithm function: \f$ \ln{x} \f$. */
Double_t Ln(Double_t x)
{
  if(x<=0.) throw Exception("Math::Ln: Negative input argument.");
  return std::log(x);
}

//______________________________________________________________________________
/** Ten raised to the power exponent: \f$ 10^{a} \f$. */
Double_t Exp10(Double_t exponent)
{
  return std::pow(10., exponent);
}

//______________________________________________________________________________
/** The common logarithm function: \f$ \log{x} \f$. */
Double_t Log(Double_t x)
{
  if(x<=0.) throw Exception("Math::Log: Negative input argument.");
  return std::log10(x);
}

//______________________________________________________________________________
/** The logarithm base 2 function: \f$ \log_{2}{x} \f$. */
Double_t Log2(Double_t x)
{
  return Ln(x) * Log2E();
}

//______________________________________________________________________________
/** The base raised to the power exponent: \f$ x^{a} \f$. */
Double_t Pow(Double_t base, Double_t exponent)
{
  return std::pow(base, exponent);
}

//______________________________________________________________________________
/** The square-root function: \f$ \sqrt{x} \f$. */
Double_t Sqrt(Double_t x)
{
  if(x<0.) throw Exception("Math::Sqrt: Negative input argument.");
  return std::sqrt(x);
}

//______________________________________________________________________________
/** Returns the floating-point remainder of numer/denom (rounded towards zero).
    \return numerator - tquot * denominator 
    Where tquot is the truncated (i.e., rounded towards zero) result of: numer/denom. 
*/
Double_t Remainder(Double_t numerator, Double_t denominator)
{
  return std::fmod(numerator, denominator);
}

//______________________________________________________________________________
/** Breaks x into an integral and a fractional part.
    The integer part is stored in the object pointed by intpart, and the fractional part is returned by the function.
    Both parts have the same sign as x. 
*/
Double_t FracPart(Double_t x, Double_t& intPart)
{
  return std::modf(x, &intPart);
}

//______________________________________________________________________________
/** The absolute value: \f$ |x| \f$. */
Double_t Abs(Double_t x)
{
  return std::abs(x);
}

//______________________________________________________________________________
/** Rounds x upward, returning the smallest integral value that is not less than x: 
    \f$ \lceil x \rceil \f$. */
Double_t Ceil(Double_t x)
{
  return std::ceil(x);
}

//______________________________________________________________________________
/** Rounds x downward, returning the largest integral value that is not greater than x: 
    \f$ \lfloor x \rfloor \f$. */
Double_t Floor(Double_t x)
{
  return std::floor(x);
}

//______________________________________________________________________________
/** Returns the smallest of a and b. If both are equivalent, a is returned. */
Double_t Min(Double_t a, Double_t b)
{
  return fmin(a, b);
}

//______________________________________________________________________________
/** Returns the largest of a and b. If both are equivalent, a is returned. */
Double_t Max(Double_t a, Double_t b)
{
  return fmax(a, b);
}

//______________________________________________________________________________
/** Round to nearest integer. Rounds half integers to the nearest even integer. */
Int_t Nint(Double_t x)
{
  int i;
  if (x >= 0) {
    i = int(x + 0.5);
    if (x + 0.5 == Double_t(i) && i & 1) i--;
  } else {
    i = int(x - 0.5);
    if (x - 0.5 == Double_t(i) && i & 1) i++;
  }
  return i;
}

//______________________________________________________________________________
//! The floor of the log-base-2 of the value. 
/**  If \f$ x > 1 \f$ then \f$ \lfloor \log_{2} x \rfloor + 1 \f$ 
     else 0.
*/
UInt_t FloorLog2(Double_t x)
{
  if(x > 1.) return 1 + UInt_t( Floor( Log2(x) ) );
  else return 0;
}

//______________________________________________________________________________
/** The error function.
    \f[ \frac{2}{\sqrt{\pi}} \int_{0}^{x} e^{-t^2} dt \f]
*/
Double_t Erf(Double_t x)
{
  return erf(x);
}

//______________________________________________________________________________
/** The complementary error function.
    \f[ \frac{2}{\sqrt{\pi}} \int_{x}^{\infty} e^{-t^2} dt \f]
*/
Double_t Erfc(Double_t x)
{
  return erfc(x);
}

//______________________________________________________________________________
/** The inverse of the error function.
    \note x must be in (-1,1)
*/
Double_t ErfInverse(Double_t x)
{
  Int_t kMaxit    = 50;
  Double_t kEps   = 1e-14;
  Double_t kConst = 0.8862269254527579;     // sqrt(pi)/2.0

  if(Math::Abs(x) <= kEps) return kConst*x;

  // Newton iterations
  Double_t erfi, derfi, y0,y1,dy0,dy1;
  if(Math::Abs(x) < 1.0) {
    erfi  = kConst*Math::Abs(x);
    y0    = Math::Erf(0.9*erfi);
    derfi = 0.1*erfi;
    for (Int_t iter=0; iter<kMaxit; iter++) {
      y1  = 1. - Math::Erfc(erfi);
      dy1 = Math::Abs(x) - y1;
      if (Math::Abs(dy1) < kEps)  {if (x < 0) return -erfi; else return erfi;}
      dy0    = y1 - y0;
      derfi *= dy1/dy0;
      y0     = y1;
      erfi  += derfi;
      if(Math::Abs(derfi/erfi) < kEps) {if (x < 0) return -erfi; else return erfi;}
    }
  }
  return 0; //did not converge
}

//______________________________________________________________________________
/** Computes quantiles for standard normal distribution N(0, 1) at probability p.

    ALGORITHM AS241  APPL. STATIST. (1988) VOL. 37, NO. 3, 477-484.
    \note x must be in (0,1)
*/
Double_t NormQuantile(Double_t p)
{
  if((p<=0) || (p>=1))
    throw Exception("Math::NormQuantile probability outside [0, 1]");

  Double_t  a0 = 3.3871328727963666080e0;
  Double_t  a1 = 1.3314166789178437745e+2;
  Double_t  a2 = 1.9715909503065514427e+3;
  Double_t  a3 = 1.3731693765509461125e+4;
  Double_t  a4 = 4.5921953931549871457e+4;
  Double_t  a5 = 6.7265770927008700853e+4;
  Double_t  a6 = 3.3430575583588128105e+4;
  Double_t  a7 = 2.5090809287301226727e+3;
  Double_t  b1 = 4.2313330701600911252e+1;
  Double_t  b2 = 6.8718700749205790830e+2;
  Double_t  b3 = 5.3941960214247511077e+3;
  Double_t  b4 = 2.1213794301586595867e+4;
  Double_t  b5 = 3.9307895800092710610e+4;
  Double_t  b6 = 2.8729085735721942674e+4;
  Double_t  b7 = 5.2264952788528545610e+3;
  Double_t  c0 = 1.42343711074968357734e0;
  Double_t  c1 = 4.63033784615654529590e0;
  Double_t  c2 = 5.76949722146069140550e0;
  Double_t  c3 = 3.64784832476320460504e0;
  Double_t  c4 = 1.27045825245236838258e0;
  Double_t  c5 = 2.41780725177450611770e-1;
  Double_t  c6 = 2.27238449892691845833e-2;
  Double_t  c7 = 7.74545014278341407640e-4;
  Double_t  d1 = 2.05319162663775882187e0;
  Double_t  d2 = 1.67638483018380384940e0;
  Double_t  d3 = 6.89767334985100004550e-1;
  Double_t  d4 = 1.48103976427480074590e-1;
  Double_t  d5 = 1.51986665636164571966e-2;
  Double_t  d6 = 5.47593808499534494600e-4;
  Double_t  d7 = 1.05075007164441684324e-9;
  Double_t  e0 = 6.65790464350110377720e0;
  Double_t  e1 = 5.46378491116411436990e0;
  Double_t  e2 = 1.78482653991729133580e0;
  Double_t  e3 = 2.96560571828504891230e-1;
  Double_t  e4 = 2.65321895265761230930e-2;
  Double_t  e5 = 1.24266094738807843860e-3;
  Double_t  e6 = 2.71155556874348757815e-5;
  Double_t  e7 = 2.01033439929228813265e-7;
  Double_t  f1 = 5.99832206555887937690e-1;
  Double_t  f2 = 1.36929880922735805310e-1;
  Double_t  f3 = 1.48753612908506148525e-2;
  Double_t  f4 = 7.86869131145613259100e-4;
  Double_t  f5 = 1.84631831751005468180e-5;
  Double_t  f6 = 1.42151175831644588870e-7;
  Double_t  f7 = 2.04426310338993978564e-15;

  Double_t split1 = 0.425;
  Double_t split2=5.;
  Double_t konst1=0.180625;
  Double_t konst2=1.6;

  Double_t q, r, quantile;
  q=p-0.5;
  if (Math::Abs(q)<split1) {
    r=konst1-q*q;
    quantile = q* (((((((a7 * r + a6) * r + a5) * r + a4) * r + a3)
		     * r + a2) * r + a1) * r + a0) /
      (((((((b7 * r + b6) * r + b5) * r + b4) * r + b3)
	 * r + b2) * r + b1) * r + 1.);
  } else {
    if(q<0) r=p;
    else    r=1-p;
    //error case
    if (r<=0)
      quantile=0;
    else {
      r=Math::Sqrt(-Math::Log(r));
      if (r<=split2) {
	r=r-konst2;
	quantile=(((((((c7 * r + c6) * r + c5) * r + c4) * r + c3)
		    * r + c2) * r + c1) * r + c0) /
	  (((((((d7 * r + d6) * r + d5) * r + d4) * r + d3)
	     * r + d2) * r + d1) * r + 1);
      } else{
	r=r-split2;
	quantile=(((((((e7 * r + e6) * r + e5) * r + e4) * r + e3)
		    * r + e2) * r + e1) * r + e0) /
	  (((((((f7 * r + f6) * r + f5) * r + f4) * r + f3)
	     * r + f2) * r + f1) * r + 1);
      }
      if (q<0) quantile=-quantile;
    }
  }
  return quantile;
}

//______________________________________________________________________________
/** The inverse of the complementary error function
    Implement using  the quantile of the normal distribution
    instead of ErfInverse for better numerical precision for large x.
    \note x must be in (0,2)
*/
Double_t ErfcInverse(Double_t x)
{
  return - 0.70710678118654752440 * NormQuantile( 0.5 * x);
}

//______________________________________________________________________________
/** The factorial function: \f$ x! \f$. */
Double_t Factorial(Int_t n)
{
  if(n == 0) return 1.;
  Double_t x(1.);
  Int_t b(0);
  do {
    b++;
    x *= b;
  } while (b != n);
  return x;
}

//______________________________________________________________________________
/** Calculates a value of a polynomial of the form:
    \f$ a_{0}x^{N} + a_{1}x^{N-1} + ... + a_{N} \f$
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t PolynomialEval(Double_t x, const Double_t* a, Int_t N)
{
   if (N==0) return a[0];
   else{
     Double_t pom = a[0];
     for(Int_t i=1; i <= N; i++)
       pom = pom *x + a[i];
     return pom;
   }
}

//______________________________________________________________________________
/** Calculates a value of a polynomial of the form:
    \f$ x^{N} + a_{0}x^{N-1} + ... + a_{N-1} \f$
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t PolynomialEval1(Double_t x, const Double_t* a, Int_t N)
{
   if (N==0) return a[0];
   else{
     Double_t pom = x + a[0];
     for(Int_t i=1; i < N; i++)
       pom = pom *x + a[i];
     return pom;
   }
}

//______________________________________________________________________________
/** The Gamma function. 
    \f[ \Gamma(x) = \int_{0}^{\infty} e^{-t} t^{x-1} dt \f]
*/
Double_t Gamma(Double_t x)
{
  return tgamma(x);
}

//______________________________________________________________________________
/** (Natural) Logarithm of gamma function.
  
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t LnGamma(Double_t x)
{
  return lgamma(x);
}

//! big number
static const Double_t kBig    = 4.503599627370496e15;
//! inverse of big number
static const Double_t kBiginv = 2.22044604925031308085e-16;
//! LS2PI?
static const Double_t kLS2PI  = 0.91893853320467274178;
//! machine EP?
static const Double_t kMACHEP = 1.11022302462515654042363166809e-16;
//! maximum logarithm
static const Double_t kMAXLOG = 709.782712893383973096206318587;
//! MAXLGM?
static const Double_t kMAXLGM = 2.556348e305;

//______________________________________________________________________________
/** The "normalized" lower incomplete gamma function.

    \f[ \gamma(a,x) = \frac{1}{\Gamma(a)} \int_{0}^{x} e^{-t} t^{a-1} dt \f]

    It is normalized such that \f$ \gamma(a,x) = 1 - \Gamma(a,x) \f$.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t LowerIncGamma( Double_t a, Double_t x )
{
  Double_t ans, ax, c, r;

  // LM: for negative values returns 1.0 instead of zero
  // This is correct if a is a negative integer since Gamma(-n) = +/- inf
  if (a <= 0)  return 1.0;  

  if (x <= 0)  return 0.0;

  if( (x > 1.0) && (x > a ) )
    return( 1.0 - UpperIncGamma(a,x) );

  /* Compute  x**a * exp(-x) / gamma(a)  */
  ax = a * Ln(x) - x - LnGamma(a);
  if( ax < -kMAXLOG )
    return( 0.0 );

  ax = Exp(ax);

  /* power series */
  r = a;
  c = 1.0;
  ans = 1.0;

  do
    {
      r += 1.0;
      c *= x/r;
      ans += c;
    }
  while( c/ans > kMACHEP );

  return( ans * ax/a );
}

//______________________________________________________________________________
/** The "normalized" upper incomplete gamma function.

    \f[ \Gamma(a,x) = \frac{1}{\Gamma(a)} \int_{x}^{\infty} e^{-t} t^{a-1} dt \f]

    It is normalized such that \f$ \Gamma(a,x) = 1 - \gamma(a,x) \f$.

    In this implementation both arguments must be positive.
    The integral is evaluated by either a power series or
    continued fraction expansion, depending on the relative
    values of a and x.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t UpperIncGamma(Double_t a, Double_t x)
{
  Double_t ans, ax, c, yc, r, t, y, z;
  Double_t pk, pkm1, pkm2, qk, qkm1, qkm2;

  // LM: for negative values returns 0.0
  // This is correct if a is a negative integer since Gamma(-n) = +/- inf
  if (a <= 0)  return 0.0;  

  if (x <= 0) return 1.0;

  if( (x < 1.0) || (x < a) )
    return( 1.0 - LowerIncGamma(a,x) );

  ax = a * Ln(x) - x - LnGamma(a);
  if( ax < -kMAXLOG )
    return( 0.0 );

  ax = Exp(ax);

  /* continued fraction */
  y = 1.0 - a;
  z = x + y + 1.0;
  c = 0.0;
  pkm2 = 1.0;
  qkm2 = x;
  pkm1 = x + 1.0;
  qkm1 = z * x;
  ans = pkm1/qkm1;

  do
    { 
      c += 1.0;
      y += 1.0;
      z += 2.0;
      yc = y * c;
      pk = pkm1 * z  -  pkm2 * yc;
      qk = qkm1 * z  -  qkm2 * yc;
      if(qk)
	{
	  r = pk/qk;
	  t = Abs( (ans - r)/r );
	  ans = r;
	}
      else
	t = 1.0;
      pkm2 = pkm1;
      pkm1 = pk;
      qkm2 = qkm1;
      qkm1 = qk;
      if( Abs(pk) > kBig )
	{
	  pkm2 *= kBiginv;
	  pkm1 *= kBiginv;
	  qkm2 *= kBiginv;
	  qkm1 *= kBiginv;
	}
    }
  while( t > kMACHEP );

  return( ans * ax );  
}

//______________________________________________________________________________
/** The Chi-squared cummulative distribution funcion. */
Double_t Chi2Cdf(Double_t x, Double_t r, Double_t x0)
{
  return 1. - Chi2Survival(x, r, x0);
}

//______________________________________________________________________________
/** The Chi-squared survival funcion: \f$1-F(x)\f$ where \f$F(x)\f$ 
    is the CDF of the Chi-squared distribution.
    
    \author Nve 14-nov-1998 UU-SAP Utrecht
*/
Double_t Chi2Survival(Double_t x, Double_t r, Double_t x0)
{
  return LowerIncGamma(0.5*r, 0.5*(x-x0));
}

//______________________________________________________________________________
/** Computation of the probability for a certain Chi-squared (chi2)
    and number of degrees of freedom (ndf).
   
    P(chi2,ndf) represents the probability that the observed Chi-squared
    for a correct model should be less than the value chi2.
   
    The returned probability corresponds to Chi2Prob() = 1-P(chi2,ndf),
    which denotes the probability that an observed Chi-squared exceeds
    the value chi2 by chance, even for a correct model.

    \note Calculations are based on the incomplete gamma function P(a,x),
    where a=ndf/2 and x=chi2/2.
   
    \author NvE 14-nov-1998 UU-SAP Utrecht
*/
Double_t Chi2Prob(Double_t chi2, Int_t ndf)
{
  // Set CL to zero in case ndf <= 0
  if(ndf <= 0) return 0.;
  if(chi2 <= 0.){
    if(chi2 < 0.) return 0.;
    else          return 1.;
  }
  return Chi2Survival(chi2, ndf); 
}

//______________________________________________________________________________
/** Calculates the Kolmogorov probability.

    Gives the probability that Kolmogorov's test statistic will exceed
    the value z assuming the null hypothesis. This gives a very powerful
    test for comparing two one-dimensional distributions.
    see, for example, Eadie et al, "statistocal Methods in Experimental
    Physics', pp 269-270).
   
    This function returns the confidence level for the null hypothesis, where:
    z = dn*sqrt(n), and
    dn  is the maximum deviation between a hypothetical distribution
    function and an experimental distribution with n events.
   
    \note To compare two experimental distributions with m and n events,
    use z = sqrt(m*n/(m+n))*dn
   
    Accuracy: The function is far too accurate for any imaginable application.
    Probabilities less than 10^-15 are returned as zero.
    However, remember that the formula is only valid for "large" n.
    Theta function inversion formula is used for z <= 1
   
    This function was translated by Rene Brun from PROBKL in CERNLIB.
*/
Double_t KolmogorovProb(Double_t z)
{
   Double_t fj[4] = {-2,-8,-18,-32}, r[4];
   const Double_t w = 2.50662827;
   // c1 - -pi**2/8, c2 = 9*c1, c3 = 25*c1
   const Double_t c1 = -1.2337005501361697;
   const Double_t c2 = -11.103304951225528;
   const Double_t c3 = -30.842513753404244;

   Double_t u = Abs(z);
   Double_t p;
   if (u < 0.2) {
      p = 1;
   } else if (u < 0.755) {
      Double_t v = 1./(u*u);
      p = 1 - w*(Exp(c1*v) + Exp(c2*v) + Exp(c3*v))/u;
   } else if (u < 6.8116) {
      r[1] = 0;
      r[2] = 0;
      r[3] = 0;
      Double_t v = u*u;
      Int_t maxj = Max(1,Nint(3./u));
      for (Int_t j=0; j<maxj;j++) {
         r[j] = Exp(fj[j]*v);
      }
      p = 2*(r[0] - r[1] +r[2] - r[3]);
   } else {
      p = 0;
   }
   return p;
}

} // end namespace Math

} // end namespace Blobb

