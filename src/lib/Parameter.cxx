/** \file      Parameter.cxx 
    \brief     Source for Parameter 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Parameter.hh"  // this class
#include "blobb/ClassImp.hh"   // blobb class implementation
#include "blobb/Random.hh"     // random number
#include "blobb/CLUI.hh"       // command-line user interface

//! Blobb class implementation macro
BLOBB_CLASS_IMP(Parameter)

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
Parameter::Parameter(const string& name, const string& title,
		     Double_t value, Double_t error,
		     Double_t min, Double_t max)
  : Named(name, title),
    mValue(value),
    mError(error),
    mMin(min),
    mMax(max)
{}

//_____________________________________________________________________________
/** Copy constructor. */
Parameter::Parameter(const Parameter& other, const string& newName)
  : Named(other),
    mValue(other.mValue),
    mError(other.mError),
    mMin(other.mMin),
    mMax(other.mMax)
{
  if(newName != "")
    setName(newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Parameter& Parameter::operator=(const Parameter& rhs)
{
  Named::operator=(rhs);
  mValue = rhs.mValue;
  mError = rhs.mError;
  mMin = rhs.mMin;
  mMax = rhs.mMax;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t Parameter::isEmpty() const
{
  if(mValue != 0.) return kFalse;
  if(mError != 0.) return kFalse;
  if(mMin   != 0.) return kFalse;
  if(mMax   != 0.) return kFalse;
  return kTrue;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void Parameter::clear()
{
  mValue = 0.;
  mError = 0.;
  mMin   = 0.;
  mMax   = 0.;
}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t Parameter::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const Parameter& p = dynamic_cast<const Parameter&>(other); 
    // check members
    if(!Named::isEqual(p))  return kFalse;
    if(mValue != p.value()) return kFalse;
    if(mError != p.error()) return kFalse;
    if(mMin   != p.min())   return kFalse;
    if(mMax   != p.max())   return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}

//_____________________________________________________________________________
//! Set all the values
void Parameter::set(Double_t value, Double_t error)
{
  mValue = value;
  mError = error;
}

//_____________________________________________________________________________
//! Get range
void Parameter::range(Double_t& min, Double_t& max) const
{
  min = mMin;
  max = mMax;
}

//_____________________________________________________________________________
//! Set the range values
void Parameter::setRange(Double_t min, Double_t max)
{
  mMin = min;
  mMax = max;
}

//_____________________________________________________________________________
//! Get a gaussian random number based on parameter.
Double_t Parameter::getRandom(const Random& random)
{
  return random.gaussian(mValue, mError);
}

//_____________________________________________________________________________
//! Interface to print value of object
void Parameter::printValue(ostream& os) const
{
  os << mValue << " +/- " << mError;
}

//_____________________________________________________________________________
//! Interface to print extras
void Parameter::printExtras(ostream& os) const
{
  os << "[" << mMin << ", " << mMax << "]";
}

//_____________________________________________________________________________
//! Read this object from user interface.
Bool_t Parameter::readFromUI(CLUI& clui, Bool_t verbose) 
{ 
  if(verbose){ 
    Named::readFromUI(clui);
    clui.request("Value");
    mValue = clui.readDouble();
    clui.request("Error");
    mError = clui.readDouble();
  }
  else{
    clui.request(name()+" Value");
    mValue = clui.readDouble();
    clui.request(name()+" Error");
    mError = clui.readDouble();
  }
  return kTrue;
}

//_____________________________________________________________________________
//! Print this object to user interface.
void Parameter::printToUI(CLUI& clui, Bool_t /*verbose*/) const
{ 
  // named
  // if(verbose) Named::printToUI(clui);
  clui.os() << name();
  if(hasTitle()) clui.os(kFalse) << " (" << title() << ")";

  // values
  clui.os(kFalse) << " = ";
  clui.os(kFalse) << mValue << " +/- " << mError;
  if(isFree()) clui.os(kFalse) << " [" << mMin << ", " << mMax << "]";
  clui.os(kFalse) << endl;
}

} // end namespace Blobb
