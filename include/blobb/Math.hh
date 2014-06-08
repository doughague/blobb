/** \file      Math.hh 
    \brief     Mathematical includes and usings header.
    \author    Doug Hague
    \date      26.02.2014
    \copyright See License.txt
*/
#ifndef BLOBB_MATH_HH
#define BLOBB_MATH_HH

#include "blobb/Common.hh"  // common includes

namespace Blobb {

//_____________________________________________________________________________
/** \namespace Math
    \brief Mathematical methods. 
*/
namespace Math {

// numerical limits 
Double_t Infinity();
Double_t Epsilon();

// numerical constants 
Double_t E();
Double_t Ln10();
Double_t LogE();
Double_t Log2E();
Double_t Pi();
Double_t Sqrt2Pi();
Double_t InvSqrt2Pi();
Double_t DegToRad();
Double_t RadToDeg();
Double_t Sqrt2();
Double_t InvSqrt2();

// trigonometric functions
Double_t ToRadians(Double_t degrees);
Double_t ToDegrees(Double_t radians);
Double_t Cos(Double_t radians);
Double_t Sin(Double_t radians);
Double_t Tan(Double_t radians);
Double_t ACos(Double_t x);
Double_t ASin(Double_t x);
Double_t ATan(Double_t x);
Double_t ATan2(Double_t y, Double_t x);

// exponential functions
Double_t Exp(Double_t x);
Double_t Ln(Double_t x);
Double_t Exp10(Double_t x);
Double_t Log(Double_t x);
Double_t Log2(Double_t x);

// power functions
Double_t Pow(Double_t base, Double_t exponent);
Double_t Sqrt(Double_t x);

// rounding functions
Double_t Remainder(Double_t numerator, Double_t denominator);
Double_t FracPart(Double_t x, Double_t& intPart);
Double_t Abs(Double_t x);
Double_t Ceil(Double_t x);
Double_t Floor(Double_t x);
Double_t Min(Double_t a, Double_t b);
Double_t Max(Double_t a, Double_t b);
Int_t    Nint(Double_t x);
UInt_t   FloorLog2(Double_t x);

// error functions
Double_t Erf(Double_t x);
Double_t Erfc(Double_t x);
Double_t ErfInverse(Double_t x);
Double_t ErfcInverse(Double_t x);

// gamma functions
Double_t Factorial(Int_t n);
Double_t Gamma(Double_t x);
Double_t LnGamma(Double_t x);
Double_t LowerIncGamma(Double_t a, Double_t x);
Double_t UpperIncGamma(Double_t a, Double_t x);

// chi-squared functions
Double_t Chi2Cdf(Double_t x, Double_t r, Double_t x0 = 0.);
Double_t Chi2Survival(Double_t x, Double_t r, Double_t x0 = 0.);
Double_t Chi2Prob(Double_t chi2, Int_t ndf);

// Kolmogorov-Smirnov probability
Double_t KolmogorovProb(Double_t z);

} // end namespace Math

} // end namespace Blobb


#endif // end BLOBB_MATH_HH
