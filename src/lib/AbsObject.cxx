/** \file      AbsObject.cxx 
    \brief     Source for AbsObject 
    \author    John D. Hague
    \date      08.05.2014
    \copyright See License.txt
*/
#include "blobb/AbsObject.hh"    // this class
#include "blobb/StringTools.hh"  // string tools
#include "blobb/LogService.hh"   // logging service
#include <fstream>               // cplusplus.com/reference/fstream/
using std::ofstream;             // STL output file stream
using std::ifstream;             // STL input file stream

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
AbsObject::AbsObject()
  : Printable()
{}

//_____________________________________________________________________________
/** Copy constructor. */
AbsObject::AbsObject(const AbsObject&, const string& /*newName*/)
  : Printable()
{}

//_____________________________________________________________________________
/** Assignment operator. */
AbsObject& AbsObject::operator=(const AbsObject&)
{
  return *this;
}

//_____________________________________________________________________________
//! Is this the same address as other?
Bool_t AbsObject::isSame(const AbsObject& other) const 
{ 
  return (this == &other); 
}

//_____________________________________________________________________________
//! Compare class-type
Bool_t AbsObject::isA(const string& classN) const 
{ 
  return (className() == classN); 
}

//_____________________________________________________________________________
//! Is this the same class-type as other?
Bool_t  AbsObject::isSameClass(const AbsObject& other) const 
{ 
  return (className() == other.className()); 
}

//_____________________________________________________________________________
//! Equivalence operator
Bool_t AbsObject::operator==(const AbsObject& rhs) const 
{ 
  return isEqual(rhs); 
}

//_____________________________________________________________________________
//! Anti-equivalence operator
Bool_t AbsObject::operator!=(const AbsObject& rhs) const 
{ 
  return !isEqual(rhs); 
}

//_____________________________________________________________________________
//! Is this object sortable?
Bool_t AbsObject::isSortable() const 
{ 
  return false; 
}

//_____________________________________________________________________________
//! Compare objects. 
/** Derived implementations should return:
    - -1 if other is "less than" this
    - +1 if other is "greater than" this
    -  0 else */
Int_t AbsObject::compare(const AbsObject&) const 
{ 
  return 0; 
}

//_____________________________________________________________________________
//! Less than operator.
Bool_t AbsObject::operator<(const AbsObject& other) const 
{ 
  return (compare(other) == -1); 
}

//_____________________________________________________________________________
//! Less than or equal operator.
Bool_t AbsObject::operator<=(const AbsObject& other) const 
{ 
  return (compare(other) <= 0); 
}

//_____________________________________________________________________________
//! Greater than operator.
Bool_t AbsObject::operator>(const AbsObject& other) const 
{ 
  return (compare(other) == 1); 
}

//_____________________________________________________________________________
//! Greater than or equal operator.
Bool_t AbsObject::operator>=(const AbsObject& other) const 
{ 
  return (compare(other) >= 0); 
}

//_____________________________________________________________________________
//! Print class name of object
void AbsObject::printClassName(ostream& os) const 
{ 
  os << className(); 
}

//_____________________________________________________________________________
//! Read this object from user interface.
Bool_t AbsObject::readFromUI(CLUI& /*clui*/, Bool_t /*verbose*/) 
{ 
  throw Exception("AbsObject::readFromUI: Not implemented for" + className());
}

//_____________________________________________________________________________
//! Print this object to user interface.
void AbsObject::printToUI(CLUI& /*clui*/, Bool_t /*verbose*/) const
{ 
  throw Exception("AbsObject::printToUI: Not implemented for" + className());
}

//_____________________________________________________________________________
//! Save this object to a file.
/** \param fileName The name of the output file.
    The type of file writen is dependent on the extension.
    Use:
     - .cnb for Cereal Native Binary
     - .json for JavaScript Object Notation (text)
     - .xml for eXtensible Markup Language, version="1.0" encoding="utf-8" (text).
     \param objName The name of the object in the file.

     \return "success" boolean: true if successfully saved.
*/
Bool_t AbsObject::save(const string& fileName, const string& objName) const
{
  // parse file name for extension type
  string fn = fileName;
  string ext = GetFileExt(fn);	
  eArchiveType arcType;
  if(ext == ".cnb") arcType = kBinary;
  else if(ext == ".json") arcType = kJson;
  else if(ext == ".xml") arcType = kXml;
  else{
    loutW(InputArguments) << "AbsObject::save: Unkonwn file extension '" << ext 
			  << "', using '.cnb' (cereal native binary)." << endl;
    fn = GetFileBase(fileName) + ".cnb";
    arcType = kBinary;
  } 

  // set up out file streamer
  ofstream* ofs = 0;
  if(arcType == kBinary)
    ofs = new ofstream(fn.c_str(), std::ios_base::trunc | std::ios::binary);
  else
    ofs = new ofstream(fn.c_str(), std::ios_base::trunc);

  // check & write the stream
  Bool_t success(kFalse);
  if(ofs->is_open()){
    loutI(DataHandling) << "Writing file " << fn << endl;
    write(*ofs, arcType, objName);
    success = kTrue;
  }
  else
    loutE(InputArguments) << "AbsObject::save: Failed to open file '" << fn 
			  << "', no data writen." << endl;    

  // clean & return
  if(ofs){ ofs->close(); delete ofs; ofs = 0; }
  return success;
}

//_____________________________________________________________________________
//! Load this object from a file.
/** \param fileName The name of the input file.
    The type of file read is dependent on the extension.
    Use:
     - .cnb for Cereal Native Binary
     - .json for JavaScript Object Notation (text)
     - .xml for eXtensible Markup Language, version="1.0" encoding="utf-8" (text).
     \param objName The name of the object in the file.

     \return "success" boolean: true if successfully loaded.
*/
Bool_t AbsObject::load(const string& fileName, const string& objName)
{
  // parse file name for extension type
  string ext = GetFileExt(fileName);	
  eArchiveType arcType;
  if(ext == ".cnb") arcType = kBinary;
  else if(ext == ".json") arcType = kJson;
  else if(ext == ".xml") arcType = kXml;
  else{
    loutE(InputArguments) << "AbsObject::load: Unkonwn file extension '" << ext 
			  << "', no data loaded." << endl;
    return kFalse;
  } 

  // set up out file streamer
  ifstream* ifs = 0;
  if(arcType == kBinary)
    ifs = new ifstream(fileName.c_str(), std::ios::binary);
  else
    ifs = new ifstream(fileName.c_str());

  // check & read the stream
  Bool_t success(kFalse);
  if(ifs->is_open()){
    try{ 
      loutI(DataHandling) << "Reading file " << fileName << endl;
      read(*ifs, arcType, objName); 
      success = kTrue;
    }
    catch(std::exception& e){
      loutE(InputArguments) << "AbsObject::load: Failed to read file '" << fileName 
			    << "'; " << e.what() << endl;    
    }
  }
  else
    loutE(InputArguments) << "AbsObject::load: Failed to open file '" << fileName 
			  << "', no data loaded." << endl;    

  // clean
  if(ifs){ ifs->close(); delete ifs; ifs = 0; }
  return success;
}

} // end namespace Blobb
