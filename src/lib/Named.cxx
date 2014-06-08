/** \file      Named.cxx 
    \brief     Source for Named 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Named.hh"        // this class
#include "blobb/ClassImp.hh"     // blobb class implementation
#include "blobb/CLUI.hh"         // command-line user interface

//! Blobb class implementation macro
BLOBB_CLASS_IMP(Named)

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
Named::Named(const string& name, const string& title)
  : AbsObject(),
    mName(name),
    mTitle(title)
{}

//_____________________________________________________________________________
/** Copy constructor. */
Named::Named(const Named& other, const string& newName)
  : AbsObject(other),
    mName(other.mName),
    mTitle(other.mTitle)
{
  if(newName != "")
    mName = newName;
}

//_____________________________________________________________________________
/** Assignment operator. */
Named& Named::operator=(const Named& rhs)
{
  AbsObject::operator=(rhs);
  mName  = rhs.mName;
  mTitle = rhs.mTitle;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t Named::isEmpty() const
{
  if(mName  != "") return kFalse;
  if(mTitle != "") return kFalse;
  return kTrue;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void Named::clear()
{
  mName  = "";
  mTitle = "";
}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t Named::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const Named& n = dynamic_cast<const Named&>(other); 
    // check members
    if(mName  != n.name())  return kFalse;
    if(mTitle != n.title()) return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}

//_____________________________________________________________________________
//! Print name of object
void Named::printName(ostream& os) const 
{
  os << mName;
}

//_____________________________________________________________________________
//! Print title of object
void Named::printTitle(ostream& os) const 
{
  os << mTitle;
}

//_____________________________________________________________________________
//! Read this object from user interface.
Bool_t Named::readFromUI(CLUI& clui, Bool_t /*verbose*/) 
{ 
  clui.request("Name");
  mName = clui.readString();
  clui.request("Title");
  mTitle = clui.readString();
  return kTrue;
}

//_____________________________________________________________________________
//! Print this object to user interface.
void Named::printToUI(CLUI& clui, Bool_t /*verbose*/) const
{ 
  clui.os() << mName;
  if(hasTitle()) clui.os(kFalse) << "(" << mTitle << ")";
  clui.os(kFalse) << endl;
}


} // end namespace Blobb
