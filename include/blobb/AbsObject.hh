/** \file      AbsObject.hh 
    \brief     Header for AbsObject class.
    \author    Doug Hague
    \date      24.02.2014
    \copyright See License.txt
*/
#ifndef BLOBB_ABSOBJECT_HH
#define BLOBB_ABSOBJECT_HH

#include "blobb/Common.hh"     // common includes
#include "blobb/Exception.hh"  // exception handler
#include "blobb/Printable.hh"  // printable object
#include "blobb/ClassDef.hh"   // blobb class definition

namespace Blobb {

class CLUI;

/** \class AbsObject
    \brief An abstract base class.
*/
class AbsObject : public Printable {
protected:
  AbsObject();
  AbsObject(const AbsObject&, const string& /*newName*/);
  AbsObject& operator=(const AbsObject&);

public:
  //! Cloner. (pure virtual)
  virtual AbsObject* clone(const string& /*newName*/) const = 0;
  //! Destructor.
  inline virtual ~AbsObject(){ }

  //! Are the derived members filled? (pure virtual)
  virtual Bool_t isEmpty() const = 0;
  //! Clear ("zero") the derived members.  (pure virtual)
  virtual void clear() = 0;

  //! Class-type (pure virtual)
  virtual string className() const = 0;
  Bool_t isSame(const AbsObject& other) const;
  Bool_t isA(const string& className) const;
  Bool_t isSameClass(const AbsObject& other) const;

  //! Does this equal other? (pure virtual)
  virtual Bool_t isEqual(const AbsObject& other) const = 0;
  Bool_t operator==(const AbsObject& rhs) const;
  Bool_t operator!=(const AbsObject& rhs) const;

  // sorting
  virtual Bool_t isSortable() const;
  virtual Int_t compare(const AbsObject&) const;
  Bool_t operator<(const AbsObject& other) const;
  Bool_t operator<=(const AbsObject& other) const;
  Bool_t operator>(const AbsObject& other) const;
  Bool_t operator>=(const AbsObject& other) const;

  // printing
  void printClassName(ostream& os) const;

  // user interface plug-in
  virtual Bool_t readFromUI(CLUI& clui, Bool_t verbose = kFalse);
  virtual void printToUI(CLUI& clui, Bool_t verbose = kFalse) const;

  //_____________________________________________________________________________
  //! Write this object to the stream. (pure virtual)
  /** \note Only _this_ object is writen to the stream and the stream
      is post-pended with the "epilogue" syntax since cereal::*OutputArchive
      goes out of scope. */
  virtual void write(ostream& os, eArchiveType arcType = gDefArcType,
		     const string& objName = "") const = 0;
  Bool_t save(const string& fileName, const string& objName = "") const;

  //_____________________________________________________________________________
  //! Read this object from the stream. (pure virtual)
  /** \note Only _the_ object named 'name' is read from the stream.
      \warning Will throw std::exception's on error! */
  virtual void read(istream& is, eArchiveType arcType = gDefArcType,
		    const string& objName = "") = 0;
  Bool_t load(const string& fileName, const string& objName = "");
};

} // end namespace Blobb


#endif // end BLOBB_ABSOBJECT_HH
