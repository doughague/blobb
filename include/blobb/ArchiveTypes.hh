/** \file      ArchiveTypes.hh 
    \brief     Header for ArchiveType enumeration.
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#ifndef BLOBB_ARCHIVETYPE_HH
#define BLOBB_ARCHIVETYPE_HH

#include "blobb/Common.hh"  // common includes

namespace Blobb {

//_____________________________________________________________________________
/** \enum eArchiveType Archive types. */
enum eArchiveType { 
  kBinary =  0, /**< Binary */
  kJson   =  1, /**< JavaScript Object Notation */
  kXml    =  2  /**< eXtensible Markup Language */
};

//_____________________________________________________________________________
//! Default archive type.
static const eArchiveType gDefArcType = kJson;

//_____________________________________________________________________________
// methods
eArchiveType GetArchiveType(const string& name);
eArchiveType GetArchiveTypeFromExt(const string& ext);
eArchiveType GetArchiveTypeFromFileName(const string& fileName);
string GetArchiveName(eArchiveType algo);
string GetArchiveTitle(eArchiveType algo);
string GetArchiveExt(eArchiveType algo);
void PrintArchiveInfo(ostream& os, const string& prefix = "");

} // end namespace Blobb

#endif // end BLOBB_ARCHIVETYPE_HH
