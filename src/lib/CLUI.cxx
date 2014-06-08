/** \file      CLUI.cxx 
    \brief     Source for CLUI 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/CLUI.hh"        // this class

namespace Blobb {

const string CLUI::Prefix = "\e[1;41m[BloBB]\e[m \e[1;31m\xE2\x9E\xB3\e[m ";
// const string CLUI::Prefix = "[BloBB]> ";

//_____________________________________________________________________________
/** Default constructor. */
CLUI::CLUI()
  : mOs(&cout),
    mIs(&cin)
{}

//_____________________________________________________________________________
/** Copy constructor. */
CLUI::CLUI(const CLUI& other)
  : mOs(other.mOs),
    mIs(other.mIs)
{}

//_____________________________________________________________________________
/** Assignment operator. */
CLUI& CLUI::operator=(const CLUI& rhs)
{
  mOs = rhs.mOs;
  mIs = rhs.mIs;
  return *this;
}

//_____________________________________________________________________________
//! Get out-stream
ostream& CLUI::os(Bool_t prefix)
{ 
  // Flush any previous messages
  (*mOs).flush();
  // print the prefix
  if(prefix) (*mOs) << Prefix;
  // return the stream
  return (*mOs);
}

//_____________________________________________________________________________
//! Set out-stream
void CLUI::setOutStream(ostream* os)
{ 
  mOs = os; 
}

//_____________________________________________________________________________
//! Get in-stream
istream& CLUI::is()
{ 
  return *mIs; 
}

//_____________________________________________________________________________
//! Set in-stream
void CLUI::setInStream(istream* is)
{ 
  mIs = is; 
}

//_____________________________________________________________________________
//! Request input
void CLUI::request(const string& req)
{
  os() << "Enter " << req << ": "; 
}

//_____________________________________________________________________________
//! Request input
string CLUI::readString()
{
  string str;
  std::getline(*mIs, str);
  return str;
}

//_____________________________________________________________________________
//! Request input
Double_t CLUI::readDouble()
{
  string s = readString();
  return Double_t(atof(s.c_str()));
}


} // end namespace Blobb
