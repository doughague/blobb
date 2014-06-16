/** \file      Config.hh 
    \brief     Configurations for libblobb.
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#ifndef BLOBB_CONFIG_HH
#define BLOBB_CONFIG_HH

//! project name
#define BLOBB_NAME    BLOBB
//! project moniker
#define BLOBB_MONIKER "blobb"
//! project title
#define BLOBB_TITLE   "Bleed or Be Bled"

//! project major version
#define BLOBB_VERSION_MAJOR 0
//! project minor version
#define BLOBB_VERSION_MINOR 2
//! project patch version
#define BLOBB_VERSION_PATCH 0
//! project version
#define BLOBB_VERSION "0.2.0"

//! install prefix
#define BLOBB_PREFIX  "/usr/local"
//! install include cflags
#define BLOBB_CFLAGS  "-I/usr/localinclude/blobb"
//! install library ldflags
#define BLOBB_LDFLAGS "-L/usr/locallib/ -lblobb"
//! install static library
#define BLOBB_STATIC  "/usr/locallib/libblobb.a"

//! source prefix
#define BLOBB_LOCAL_PREFIX  "/Users/JDT/Documents/fun/blobb"
//! library name
#define BLOBB_LIB_NAME      "blobb"
//! local head directory
#define BLOBB_LOCAL_CFLAGS  "-I/Users/JDT/Documents/fun/blobb/include/"
//! local library directory
#define BLOBB_LOCAL_LDFLAGS "-L/Users/JDT/Documents/fun/blobb/build/lib/ -lblobb"
//! local library directory
#define BLOBB_LOCAL_STATIC  "/Users/JDT/Documents/fun/blobb/build/lib/libblobb.a"

//! author
#define BLOBB_AUTHOR    "Doug Hague <doughague@gmail.com>, Jason Torpy <jason@dday76.net>"
//! year
#define BLOBB_YEAR      "2014"
//! copyright
#define BLOBB_COPYRIGHT "Copyright (C) 2014\n"                 \
                        "Doug Hague <doughague@gmail.com>, Jason Torpy <jason@dday76.net>\n"                             \
                        "This program comes with ABSOLUTELY NO WARRANTY.\n" \
                        "ALL RELEVANT COPYRIGHTS AND RESTRICTIONS APPLY.\n" \
                        "See /Users/JDT/Documents/fun/blobb/License.txt"

#endif // end BLOBB_CONFIG_HH
