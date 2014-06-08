/** \file      Named.hh 
    \brief     Header for Named
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_NAMED_HH
#define BLOBB_NAMED_HH

#include "blobb/AbsObject.hh"  // abstract base class

namespace Blobb {

/** \class Named 
    \brief Container for name & title.
*/
class Named : public AbsObject { 
public:
  Named(const string& name = "", const string& title = "");
  Named(const Named& other, const string& newName);
  Named& operator=(const Named& rhs);
  inline virtual ~Named() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  //! Get name
  inline const string& name() const { return mName; }
  //! Set name
  inline void setName(const string& name){ mName = name; }
  //! Has name?
  inline Bool_t hasName() const { return mName != ""; }
  //! Get title
  inline const string& title() const { return mTitle; }
  //! Set title
  inline void setTitle(const string& title){ mTitle = title; }
  //! Has title?
  inline Bool_t hasTitle() const { return mTitle != ""; }
  //! Set name & title
  inline void setNameTitle(const string& name, const string& title)
  { mName = name; mTitle = title; }

  // printing 
  void printName(ostream& os) const;
  void printTitle(ostream& os) const;

  // user interface plug-in
  virtual Bool_t readFromUI(CLUI& clui, Bool_t verbose = kFalse);
  virtual void printToUI(CLUI& clui, Bool_t verbose = kFalse) const;

private:
  string mName;   //!< name
  string mTitle;  //!< title

private:
  //! cerealize
  template <class Archive> void serialize(Archive& ar)
  {
    ar(BLOBB_NVP(mName),
       BLOBB_NVP(mTitle));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(Named);   
};

} // end namespace Blobb

#endif // BLOBB_NAMED_HH
