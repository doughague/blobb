/** \file      src/lib/ArchiveTypes.cxx 
    \brief     Source for archive enumeration helpers
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/ArchiveTypes.hh"  // these methods
#include "blobb/StringTools.hh"   // string manip tools
#include "blobb/Exception.hh"     // exception handler
#include "blobb/LogService.hh"    // logging helper
#include <map>                    // cplusplus.com/reference/map/

namespace Blobb {

//_____________________________________________________________________________
//! Archive names.
static std::map<eArchiveType,string> gArchiveNames = 
  {
    {kBinary, "Binary"},
    {kJson,   "JSON"},
    {kXml,    "XML"}
  };

//_____________________________________________________________________________
//! Archive titles.
static std::map<eArchiveType,string> gArchiveTitles = 
  {
    {kBinary, "Binary"},
    {kJson,   "JavaScript Object Notation"},
    {kXml,    "eXtensible Markup Language"}
  };

//_____________________________________________________________________________
//! Archive extensions.
static std::map<eArchiveType,string> gArchiveExts = 
  {
    {kBinary, ".cnb"},
    {kJson,   ".json"},
    {kXml,    ".xml"}
  };

//_____________________________________________________________________________
/** Get an archive enumerated value from the name string. */
eArchiveType GetArchiveType(const string& name)
{
  // loop to find value and return key
  std::map<eArchiveType,string>::const_iterator it = gArchiveNames.begin();
  for(it = gArchiveNames.begin(); it != gArchiveNames.end(); ++it)
    if(it->second == name)
      return it->first;
  // value not found
  loutW(InputArguments) << "GetArchiveType: Unkown archive name '" 
			<< name << "', returning 'Binary'." << endl;
  return kBinary;
}

//_____________________________________________________________________________
/** Get an archive enumerated value from the name string. */
eArchiveType GetArchiveTypeFromExt(const string& ext)
{
  // loop to find value and return key
  std::map<eArchiveType,string>::const_iterator it = gArchiveExts.begin();
  for(it = gArchiveExts.begin(); it != gArchiveExts.end(); ++it)
    if(it->second == ext)
      return it->first;
  // value not found
  loutW(InputArguments) << "GetArchiveTypeFromExt: Unkown archive extension '" 
			<< ext << "', returning 'Binary'." << endl;
  return kBinary;
}

//_____________________________________________________________________________
/** Get an archive enumerated value from the file name string. */
eArchiveType GetArchiveTypeFromFileName(const string& fileName)
{
  return GetArchiveTypeFromExt(GetFileExt(fileName));
}

//_____________________________________________________________________________
/** Get an archive name string from the enumerated value. */
string GetArchiveName(eArchiveType algo)
{
  try{ return gArchiveNames.at(algo).c_str(); }
  catch(const out_of_range& oor){ throw Exception("GetArchiveName: Undefined archive enumeration."); }
}

//_____________________________________________________________________________
/** Get an archive title string from the enumerated value. */
string GetArchiveTitle(eArchiveType algo)
{
  try{ return gArchiveTitles.at(algo).c_str(); }
  catch(const out_of_range& oor){ throw Exception("GetArchiveTitle: Undefined archive enumeration."); }
}

//_____________________________________________________________________________
/** Get an archive name string from the enumerated value. */
string GetArchiveExt(eArchiveType algo)
{
  try{ return gArchiveExts.at(algo).c_str(); }
  catch(const out_of_range& oor){ throw Exception("GetArchiveName: Undefined archive enumeration."); }
}

//_____________________________________________________________________________
//! Get an algorithm title string from the enumerated value.Print algorithm information to the stream 
void PrintArchiveInfo(ostream& os, const string& prefix)
{
  os << prefix << "NAME    DESCRIPTION" << endl;
  os << prefix << "Binary  " << gArchiveTitles[kBinary] << endl;
  os << prefix << "JSON    " << gArchiveTitles[kJson] << endl;
  os << prefix << "XML     " << gArchiveTitles[kXml] << endl;
}

} // end namespace Blobb
