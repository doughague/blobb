/** \file      Common.hh 
    \brief     Common includes and usings header.
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt

    This header file should include standard headers and using 
    which are commonly used in this library.

    The motivations for this file are:
    - Ensure that the things we need are available at compilation.
    - Attempt to strike a balance between "too much over-head", 
      that is including everything under the sun which will bog-down the library, 
      and "enough convenience", that is not having to include/using every 
      little thing in every source file.
    - We can also use this file for forward declarations, typedef-ing,
      platform specifics, handy macros, ...
*/
#ifndef BLOBB_COMMON_HH
#define BLOBB_COMMON_HH

//_____________________________________________________________________________
// Compiler directives (for portability).
#ifdef _WIN64
   // define something for Windows (64-bit)
#elif _WIN32
   // define something for Windows (32-bit)
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        // Unsupported platform
    #endif
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

//_____________________________________________________________________________
// C/C++ Standard Library
#include <cstdlib>     // cplusplus.com/reference/cstdlib/
#include <string>      // cplusplus.com/reference/string/
using std::string;
#include <vector>      // cplusplus.com/reference/vector/
using std::vector;
#include <ostream>     // cplusplus.com/reference/ostream/
using std::ostream;
#include <istream>     // cplusplus.com/reference/istream/
using std::istream;
#include <iostream>    // cplusplus.com/reference/iostream/
using std::cin;
using std::cout;
using std::endl;

//_____________________________________________________________________________
// Configuration for this library
#ifdef HAVE_CONFIG_H
   #include "blobb/Config.hh"
#endif

//_____________________________________________________________________________
// Fundamental type definitions for this library
#include "blobb/Types.hh"

//_____________________________________________________________________________
/** \namespace Blobb 
    \brief Top-level namespace for Bleed or Be Bled. 
    This namespace should encapsulate the methods and classes for blobb library.
*/
namespace Blobb { }

#endif // end BLOBB_COMMON_HH
