/** \file      Exception.hh 
    \brief     Header for exception handler
    \author    Doug Hague
    \date      24.02.2014
    \copyright See License.txt
*/
#ifndef BLOBB_EXCEPTION_HH
#define BLOBB_EXCEPTION_HH

#include "blobb/Common.hh"  // common includes
#include <exception>        // exception
#include <stdexcept>        // std::out_of_range
#include <typeinfo>         // std::bad_cast
using std::out_of_range;    // common enough to be "used"
using std::bad_cast;        // common enough to be "used"

namespace Blobb {

/** \class Exception
    \brief std::exception handling class.
*/
class Exception : public std::exception {

public:
  //_____________________________________________________________________________
  //! Constructor
  inline Exception(const string& message)
  : exception(), mMessage(message) 
  {}
  //_____________________________________________________________________________
  //! Copy constructor.
  inline Exception(const Exception& other)
  : exception(other), mMessage(other.mMessage)
  {}
  //_____________________________________________________________________________
  //! Assignemnt operator
  inline Exception& operator=(const Exception& rhs)
  {
    exception::operator=(rhs);
    mMessage = rhs.mMessage;
    return *this;
  }
  //_____________________________________________________________________________
  //! Destructor
  inline virtual ~Exception() throw() { }

  //_____________________________________________________________________________
  //! The message associated with the exception
  inline CChar_t* what() const throw() 
  { 
    return mMessage.c_str(); 
  }

private:
  //! exception message
  string mMessage;
};

} // end namespace Blobb

#endif // BLOBB_EXCEPTION_HH
