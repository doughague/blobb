/** \file      StringTools.hh 
    \brief     Header for string handling tools
    \author    Doug Hague
    \date      08.05.2014
    \copyright See License.txt
*/
#ifndef BLOBB_STRINGTOOLS_HH
#define BLOBB_STRINGTOOLS_HH

#include "blobb/Common.hh"  // common includes

namespace Blobb {

string GetFileBase(const string& fileName);
string GetFileDir(const string& fileName);
string GetFileExt(const string& fileName);

} // end namespace Blobb

#endif // BLOBB_STRINGTOOLS_HH
