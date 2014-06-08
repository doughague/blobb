/** \file      Parameter.hh 
    \brief     Header for Parameter
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_PARAMETER_HH
#define BLOBB_PARAMETER_HH

#include "blobb/Named.hh"  // named base class

namespace Blobb {

class Random;

/** \class Parameter 
    \brief Container for a parameter.
*/
class Parameter : public Named { 
public:
  Parameter(const string& name = "", const string& title = "",
	    Double_t value = 0., Double_t error = 1.,
	    Double_t min = 0., Double_t max = 100.);
  Parameter(const Parameter& other, const string& newName);
  Parameter& operator=(const Parameter& rhs);
  inline virtual ~Parameter() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  void set(Double_t value, Double_t error = 1.);
  //! Get value
  inline Double_t value() const { return mValue; }
  //! Set value
  inline void setValue(Double_t value){ mValue = value; }
  //! Increment value
  inline void incrValue(Double_t value){ mValue += value; }
  //! Get error
  inline Double_t error() const { return mError; }
  //! Set error
  inline void setError(Double_t error){ mError = error; }

  //! Get min
  inline Double_t min() const { return mMin; }
  //! Set min
  inline void setMin(Double_t min){ mMin = min; }
  //! Get max
  inline Double_t max() const { return mMax; }
  //! Set max
  inline void setMax(Double_t max){ mMax = max; }
  void range(Double_t& min, Double_t& max) const;
  void setRange(Double_t min = 0., Double_t max = 100.);
  //! Has a range
  inline Bool_t isFree() const { return mMin != mMax; }
  //! Does not have a range
  inline Bool_t isFixed() const { return !isFree(); }

  Double_t getRandom(const Random& random);

  // printing
  void printValue(ostream& os) const;
  void printExtras(ostream& os) const;

  // user interface plug-in
  virtual Bool_t readFromUI(CLUI& clui, Bool_t verbose = kFalse);
  virtual void printToUI(CLUI& clui, Bool_t verbose = kFalse) const;

protected:
  Double_t mValue;  //!< value
  Double_t mError;  //!< error
  Double_t mMin;    //!< minimum
  Double_t mMax;    //!< maximum

private:
  //! cerealize
  template <class Archive> void serialize(Archive& ar)
  {
    ar(make_nvp("Named", cereal::base_class<Named>(this)),
       BLOBB_NVP(mValue),
       BLOBB_NVP(mError),
       BLOBB_NVP(mMin),
       BLOBB_NVP(mMax));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(Parameter);   
};

} // end namespace Blobb

#endif // BLOBB_PARAMETER_HH
