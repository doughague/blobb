/** \file      Printable.hh 
    \brief     Header for Printable
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_PRINTABLE_HH
#define BLOBB_PRINTABLE_HH

#include "blobb/Common.hh"  // common includes

namespace Blobb {

class CLUI;

/** \class Printable 
    \brief Utility class for printing objects.

    This class is shamelessly lifted from 
    root.cern.ch/root/html/RooPrintable.html.
*/
class Printable { 
public:
  //_____________________________________________________________________________
  //! \enum eContentsOption Option for contents to print.
  /** \note Can be ORed. */
  enum eContentsOption { 
    kAddress   =  1, 
    kClassName =  2, 
    kName      =  4, 
    kTitle     =  8,
    kValue     = 16, 
    kArgs      = 32, 
    kExtras    = 64 
  };

  //_____________________________________________________________________________
  //! \enum eStyleOption Option for style of printing.
  /** \note Exclusive. */
  enum eStyleOption { 
    kInline     = 1, 
    kSingleLine = 2, 
    kStandard   = 3, 
    kVerbose    = 4 
  };

public:
  //_____________________________________________________________________________
  //! Default constructor.
  Printable(){ }
  //! Destructor.
  inline virtual ~Printable() { }

  // Master print function
  virtual void printStream(ostream& os, Int_t contents, eStyleOption style, 
			   const string& indent="") const;
  virtual void print(ostream& os, const string& indent="") const;
  virtual void print(CLUI& clui, const string& indent="") const;
  virtual void print(const string& indent="") const;

  // Virtual hook function for class-specific content implementation
  virtual void printAddress(ostream& os) const;
  virtual void printClassName(ostream& os) const;
  virtual void printName(ostream& os) const;
  virtual void printTitle(ostream& os) const;
  virtual void printValue(ostream& os) const;
  virtual void printArgs(ostream& os) const;
  virtual void printExtras(ostream& os) const;
  virtual void printMultiline(ostream& os, Int_t contents, 
			      Bool_t verbose=kFalse, const string& indent="") const;

  // Formatting control
  static ostream& defaultPrintStream(ostream *os=0);
  virtual Int_t defaultPrintContents(const string& opt) const;
  virtual eStyleOption defaultPrintStyle(const string& opt) const;
  static void nameFieldLength(Int_t newLen);

protected:
  static Int_t mNameLength;
};

// streamer
ostream& operator<<(ostream& os, const Printable& rp);

} // end namespace Blobb

#endif // BLOBB_PRINTABLE_HH
