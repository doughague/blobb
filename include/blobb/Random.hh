/** \file      Random.hh 
    \brief     Header for Random
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_RANDOM_HH
#define BLOBB_RANDOM_HH

#include "blobb/AbsObject.hh"  // abstract base class

namespace Blobb {

/** \class Random 
    \brief A random number generator.

    This class currently uses std::rand() which might not 
    be suited for statistical studies.
*/
class Random : public AbsObject { 
public:
  Random(UInt_t seed = 0, UInt_t numIter = 0);
  Random(const Random& other, const string& newName);
  Random& operator=(const Random& rhs);
  inline virtual ~Random() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  //! Get seed
  inline UInt_t seed() const { return mSeed; }
  //! Set seed
  void setSeed(UInt_t seed);
  //! Get numIter
  inline UInt_t numIter() const { return mNumIter; }
  //! Set numIter
  void setNumIter(UInt_t numIter);

  // core method
  virtual Double_t rndm(Double_t max = 0.) const;
  virtual UInt_t integer(UInt_t max = 0) const;

  // distributions
  Double_t uniform(Double_t min = 0., Double_t max = 1.) const;
  Double_t exponential(Double_t tau = 1.) const;
  Double_t gaussian(Double_t mean = 0., Double_t sigma = 1.) const;
  Double_t poisson(Double_t mean = 1.) const;
  Double_t powerlaw(Double_t xmin = 1., Double_t gamma = 2.) const;

  // user interface plug-in
  virtual Bool_t readFromUI(CLUI& clui, Bool_t verbose = kFalse);
  virtual void printToUI(CLUI& clui, Bool_t verbose = kFalse) const;

private:
  UInt_t mSeed;             //!< seed
  mutable UInt_t mNumIter;  //!< number of iterations

private:
  //! cereal load
  template<class Archive> void load(Archive& archive)
  {
    UInt_t seed(0), numIter(0);
    archive(make_nvp("Seed", seed),
	    make_nvp("NumIter", numIter));
    setSeed(seed);
    setNumIter(numIter);
  }
  //! cereal save
  template<class Archive> void save(Archive& archive) const
  {
    archive(BLOBB_NVP(mSeed),
	    BLOBB_NVP(mNumIter));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(Random);   
};

} // end namespace Blobb

#endif // BLOBB_RANDOM_HH
