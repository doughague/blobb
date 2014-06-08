/** \file      CLUI.hh 
    \brief     Header for CLUI
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_CLUI_HH
#define BLOBB_CLUI_HH

#include "blobb/Common.hh"  // common includes

namespace Blobb {

/** \class CLUI 
    \brief Utility class for handling command-line user interface.
*/
class CLUI { 
public:
  CLUI();
  CLUI(const CLUI& other);
  CLUI& operator=(const CLUI& rhs);
  inline virtual ~CLUI() { }

  ostream& os(Bool_t prefix = kTrue);
  void setOutStream(ostream* os);
  istream& is();
  void setInStream(istream* is);

  void request(const string& req = "");
  string readString();
  Double_t readDouble();

protected:
  ostream* mOs;  //!< out-stream
  istream* mIs;  //!< in-stream

  //! Prefix for out messages.
  static const string Prefix;
};

} // end namespace Blobb

#endif // BLOBB_CLUI_HH
