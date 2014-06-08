/** \file      Printable.cxx 
    \brief     Source for Printable 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Printable.hh"  // this class
#include "blobb/CLUI.hh"       // command-line user interface
#include <iomanip>             // cplusplus.com/reference/iomanip/

namespace Blobb {

Int_t Printable::mNameLength(0);

//_____________________________________________________________________________
//! Print description of object to ostream.
/** Printing contents set by contents integer, which is interpreted as an OR of 
    'enum eContentsOptions' values and in the style given by 'enum eStyleOption'. 
    Each message is prefixed by string 'indent' when printed
*/
void Printable::printStream(ostream& os, Int_t contents, 
			    eStyleOption style, const string& indent) const 
{

  // Handling of 'verbose'  is delegated to dedicated implementation function
  if(style==kVerbose || style==kStandard) {
    printMultiline(os,contents,style==kVerbose,indent);
    return;
  } 

  // Handle here Inline and SingleLine styles
  if(style != kInline) os << indent;

  // Print class name if requested
  if(contents & kAddress) {
    printAddress(os);
    if(contents!=kAddress) os << " ";
  }

  // Print class name if requested
  if(contents & kClassName) {
    printClassName(os);
    if(contents!=kClassName) os << "::";
  }

  // Print object name if requested
  if(contents & kName) {
    if(mNameLength>0) os << std::setw(mNameLength);
    printName(os);
  }

  // Print title if required
  if(contents & kTitle) {
    if(contents==kTitle) printTitle(os);
    else {
      os << " \"";
      printTitle(os);
      os << "\"";
    }
  }

  // Print input argument structure from proxies if requested
  if(contents & kArgs) printArgs(os);
  
  // Print value if requested
  if(contents & kValue) {
    if(contents & kName) os << " = ";
    printValue(os);
  }

  // Print extras if required
  if(contents & kExtras) {
    if(contents!=kExtras) os << " ";
    printExtras(os);
  }

  // end-line, if requested
  if(style!=kInline) os << endl;
}

//_____________________________________________________________________________
//! Print object to stream.
void Printable::print(ostream& os, const string& indent) const
{
  printStream(os, defaultPrintContents(""), Printable::kSingleLine, indent);   
}

//_____________________________________________________________________________
//! Print object to command-line interface.
void Printable::print(CLUI& clui, const string& indent) const
{
  print(clui.os(), indent);
}

//_____________________________________________________________________________
//! Print object to std::cout.
void Printable::print(const string& indent) const
{
  print(cout, indent);
}

//_____________________________________________________________________________
//! Print address of object
void Printable::printAddress(ostream& os) const 
{
  os << this;
}

//_____________________________________________________________________________
//! Print class name of object
void Printable::printClassName(ostream& /*os*/) const 
{}

//_____________________________________________________________________________
//! Print name of object
void Printable::printName(ostream& /*os*/) const 
{}

//_____________________________________________________________________________
//! Print title of object
void Printable::printTitle(ostream& /*os*/) const 
{}

//_____________________________________________________________________________
//! Interface to print value of object
void Printable::printValue(ostream& /*os*/) const
{}

//_____________________________________________________________________________
//! Interface to print extras of object
void Printable::printExtras(ostream& /*os*/) const
{}

//_____________________________________________________________________________
//! Interface for detailed printing of object
void Printable::printMultiline(ostream& /*os*/, Int_t /*contents*/, 
			       Bool_t /*verbose*/, const string& /*indent*/) const
{}

//_____________________________________________________________________________
//! Interface for printing of object arguments. 
/** Arguments are loosely defined as external server objects in this context */
void Printable::printArgs(ostream& /*os*/) const 
{}

//_____________________________________________________________________________
//! Default choice of contents to be printed (name and value)
Int_t Printable::defaultPrintContents(const string& /*opt*/) const
{ 
  return kName | kValue; 
}

//_____________________________________________________________________________
//! The default printing style.
/** Choose V for verbose, S for standard or I for inline. */
Printable::eStyleOption Printable::defaultPrintStyle(const string& opt) const
{ 
  if(opt == "") return kSingleLine;
  if(     opt.find("V") != string::npos) return kVerbose;
  else if(opt.find("S") != string::npos) return kStandard;
  else if(opt.find("I") != string::npos) return kInline;
  return kSingleLine;
}

//_____________________________________________________________________________
//! Return a reference to the current default stream
/** To use in Print(). 
    Use the optional parameter to specify a new default stream 
    (a reference to the old one is still returned). 
    This method allows subclasses to provide an inline implementation of
    Print() without pulling in iostream.h.
*/
ostream& Printable::defaultPrintStream(ostream *os) 
{
  static ostream *_defaultPrintStream = &cout;
  ostream& _oldDefault= *_defaultPrintStream;
  if(0 != os) _defaultPrintStream= os;
  return _oldDefault;
}

//_____________________________________________________________________________
/** Set length of field reserved from printing name 
    in multi-line collection printing to given amount.
*/
void Printable::nameFieldLength(Int_t newLen)
{
  mNameLength = newLen>0 ? newLen : 0;
}

//_____________________________________________________________________________
//! Streamer
ostream& operator<<(ostream& os, const Printable& rp)
{
  rp.printStream(os, rp.defaultPrintContents(""), Printable::kInline); 
  return os; 
}

} // end namespace Blobb
