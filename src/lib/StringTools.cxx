/** \file      StringTools.cxx 
    \brief     Source for string handling tools
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/StringTools.hh"  // these methods

namespace Blobb {

//_____________________________________________________________________________
/** Get the possition in a string where the path ends. */
size_t GetPathEndPos(const string& fileName)
{
#ifdef _WIN32 
    // This is defined for both win32 and win64, right?
    // Can someone please tell me why windows has to be contrarian?! :-P
    return fileName.find_last_of("\\") + 1;
#else
    return fileName.find_last_of("/") + 1;
#endif
}

//_____________________________________________________________________________
/** Get the possition in a string where the extension starts. */
size_t GetExtStartPos(const string& fileName)
{
  return fileName.find_last_of(".");
}

//_____________________________________________________________________________
/** Get the base-name from a file. 
    That is, strip the path and extension.
*/
string GetFileBase(const string& fileName)
{
  size_t pathEndPos = GetPathEndPos(fileName);
  size_t extStartPos = GetExtStartPos(fileName);
  return fileName.substr(pathEndPos, extStartPos-pathEndPos);
}

//_____________________________________________________________________________
/** Get the directory of a file. 
    \note This includes the trailing "/".
*/
string GetFileDir(const string& fileName)
{
  size_t pathEndPos = GetPathEndPos(fileName);
  return fileName.substr(0, pathEndPos);
}

//_____________________________________________________________________________
/** Get the extension of a file. 
    \note This includes the ".".
*/
string GetFileExt(const string& fileName)
{
  size_t extStartPos = GetExtStartPos(fileName);
  return fileName.substr(extStartPos, fileName.length());
}

} // end namespace Blobb
