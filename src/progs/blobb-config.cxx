/** \file      blobb-config.cxx
    \brief     Source for binary executable for blobb-config.
    \author    Doug Hague
    \date      05.03.2014
    \copyright See License.txt
*/
#include "blobb/Common.hh"  // common includes
using namespace Blobb;

#include <iostream>  // http://www.cplusplus.com/reference/iostream
using std::cout;
using std::cerr;
using std::endl;

#ifdef HAVE_GETOPT_H
  #include <getopt.h>              // GNU option parsing
  /** \typedef GnuOpt_t
      \brief GNU getopt option.
      The struct option structure has these fields:
      - const char *name : This field is the name of the option. It is a string.
      - int has_arg : This field says whether the option takes an argument. 
      It is an integer, and there are three legitimate values: 
      no_argument, required_argument and optional_argument.
      - int *flag : If flag is a null pointer, then the val is a value 
      which identifies this option. Often these values are chosen to uniquely 
      identify particular long options. If flag is not a null pointer, 
      it should be the address of an int variable which is the flag for this option. 
      The value in val is the value to store in the flag to indicate that the option was seen. 
      - int val : These fields control how to report or act on the option when it occurs.
  */
  typedef struct option GnuOpt_t;
#endif // end HAVE_GETOPT_H


//_____________________________________________________________________________
//! Usage for blobb-config.
void PrintUsage(std::ostream& os)
{
  os << "blobb-config: Display information about the blobb library." << endl;
  os << "                 Note that this shows local build information only;" << endl;
  os << "                 On GNU/Linux use 'pkg-config blobb' (after 'make install)'" << endl;
  os << "                 for globally installed information." << endl;
  os << "Usage: blobb-config [option]" << endl;
  os << "Options:" << endl;
  os << "  -h|--help        Display this help message" << endl;
  os << "  -i|--info        Title & description" << endl;
  os << "  -c|--copyright   Lisence" << endl;
  os << "  -v|--version     Version" << endl;
  os << "  -@|--is-64bit    '1' if compiled as 64-bit library ('0' else)" << endl;
  os << "  -t|--type-info   Type information" << endl;
  os << "  -p|--prefix      Source prefix" << endl;
  os << "  -f|--cflags      Pre-processor and compiler flags" << endl;
  os << "  -l|--ldflags     Shared library linker flags" << endl;
  os << "  -s|--static      Static library" << endl;
}

//_____________________________________________________________________________
//! main method for blobb-config.
int main(int argc, char** argv)
{
#ifndef HAVE_CONFIG_H
  // --------------------------------------------
  // check for blobb/Config.hh
  cerr << "ERROR: blobb-config: blobb/Config.hh not found." << endl;
  return EXIT_FAILURE;
#else

#ifndef HAVE_GETOPT_H
  // --------------------------------------------
  // check for GNU getopt.h
  cerr << "ERROR: blobb-config: <getopt.h> not found." << endl;
  return EXIT_FAILURE;
#else

  // --------------------------------------------
  // check input(s)
  if(argc <= 1){
    PrintUsage(cerr);
    return 0;
  }

  // --------------------------------------------
  // struct array for feeding to getopt
  static GnuOpt_t gGnuLongOpts[] = 
    {
      {"help",       no_argument, 0, 'h'},
      {"info",       no_argument, 0, 'i'},
      {"copyright",  no_argument, 0, 'c'},
      {"version",    no_argument, 0, 'v'},
      {"type-info",  no_argument, 0, 't'},
      {"is-64bit",   no_argument, 0, '@'},
      {"prefix",     no_argument, 0, 'p'},
      {"cflags",     no_argument, 0, 'f'},
      {"ldflags",    no_argument, 0, 'l'},
      {"static",     no_argument, 0, 's'},
      {0, 0, 0, 0}
    };

  // getopt_long stores the option index here.
  int optIdx(0), optChar(-1);

  // --------------------------------------------
  // begin reading options
  while(1){
    // GNU getopt_long parser
    optChar = getopt_long(argc, argv, "hicv@tpfls", gGnuLongOpts, &optIdx);
    
    // Detect the end of the options.
    if(optChar == -1) break;

    // Detect the options
    switch(optChar){
    case 'h':
      PrintUsage(cout);
      return 0;

    case 'i':
      cout << BLOBB_LIB_NAME << " - " << BLOBB_TITLE << endl;
      return 0;

    case 'v':
      cout << BLOBB_VERSION << endl;
      return 0;

    case '@':
      cout << (kIs64bit ? 1 : 0) << endl;
      return 0;

    case 't':
      printf("%18s  %10s  %5s  %20s  %20s  %s\n",
	     "TYPE", "ALIAS", "BYTES", "MINIMUM VALUE", "MAXIMUM VALUE", "TITLE");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "bool", "Bool_t", kSzB, kFalse, kTrue, "boolean");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "char", "Char_t", kSzC, kMinC, kMaxC, "signed character");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "unsigned char", "UChar_t", kSzC, 0, kMaxUC, "unsigned character");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "short", "Short_t", kSzS, kMinS, kMaxS, "signed short");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "unsigned short", "UShort_t", kSzS, 0, kMaxUS, "unsigned short");
      printf("%18s  %10s  %5u  %20d  %20d  %s\n",
	     "int", "Int_t", kSzI, kMinI, kMaxI, "signed integer");
      printf("%18s  %10s  %5u  %20d  %20u  %s\n",
	     "unsigned int", "UInt_t", kSzI, 0, kMaxUI, "unsigned integer");
      printf("%18s  %10s  %5u         %1.6e          %1.6e  %s\n",
      	     "float", "Float_t", kSzF, kMinF, kMaxF, "floating-point number");
      printf("%18s  %10s  %5u  %1.12e   %1.12e  %s\n",
      	     "double", "Double_t", kSzD, kMinD, kMaxD, "double-precision number");
#ifdef __APPLE__
      printf("%18s  %10s  %5u  %20lld  %20lld  %s\n",
      	     "long int", "Long_t", kSzL, kMinL, kMaxL, "signed long integer");
      printf("%18s  %10s  %5u  %20d  %20llu  %s\n",
      	     "unsigned long long", "ULong_t", kSzL, 0, kMaxUL, "unsigned long integer");
      printf("%18s  %10s  %5u  %20d  %#20llx  %s\n",
      	     "void*", "VoidPtr_t", kSzVP, 0, kMaxVP, "void pointer");
#else
      printf("%18s  %10s  %5u  %20ld  %20ld  %s\n",
      	     "long int", "Long_t", kSzL, kMinL, kMaxL, "signed long integer");
      printf("%18s  %10s  %5u  %20d  %20lu  %s\n",
      	     "unsigned long int", "ULong_t", kSzL, 0, kMaxUL, "unsigned long integer");
      printf("%18s  %10s  %5u  %20d  %#20lx  %s\n",
      	     "void*", "VoidPtr_t", kSzVP, 0, kMaxVP, "void pointer");
#endif
      return 0;

    case 'c':
	cout << BLOBB_LIB_NAME << " - " << BLOBB_TITLE << endl;
	cout << BLOBB_COPYRIGHT << endl;
	return 0;

    case 'p':
      cout << BLOBB_LOCAL_PREFIX << endl;
      return 0;

    case 'f':
      cout << BLOBB_LOCAL_CFLAGS << endl;
      return 0;

    case 'l':
      cout << BLOBB_LOCAL_LDFLAGS << endl;
      return 0;

    case 's':
      cout << BLOBB_LOCAL_STATIC << endl;
      return 0;

    default:
      PrintUsage(cerr);
      return -1;
    } // end option switch
  } // end while (read opts)

  // --------------------------------------------
  // return
  return 0;

#endif // end HAVE_GETOPT_H
#endif // end HAVE_CONFIG_H
}
