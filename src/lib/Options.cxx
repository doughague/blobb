/** \file      Options.cxx 
    \brief     Source for Options 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Options.hh"      // this class
#include "blobb/ClassImp.hh"     // blobb class implementation
#include "blobb/StringTools.hh"  // string helper tools
#include "blobb/LogService.hh"   // logging

#ifdef HAVE_CONFIG_H
  #include "blobb/Config.hh"     // configuration information 
#endif

#ifdef HAVE_GETOPT_H
  #include <getopt.h>                 // GNU option parsing
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

#include <cctype>                   // http://www.cplusplus.com/reference/cctype/


//! Blobb class implementation macro
BLOBB_CLASS_IMP(Options)

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
Options::Options()
  : AbsObject(),
    mHelp(kFalse),
    mVersion(kFalse),
    mCopyright(kFalse),
    mBatch(kFalse),
    mProgName(""),
    mInFileName("")
{}

//_____________________________________________________________________________
/** Constructor from commandline arguments. 
    \warning Can throw Exception.
*/
Options::Options(Int_t argc, Char_t** argv)
  : AbsObject(),
    mHelp(kFalse),
    mVersion(kFalse),
    mCopyright(kFalse),
    mBatch(kFalse),
    mProgName(""),
    mInFileName("")
{
  set(argc, argv);
}

//_____________________________________________________________________________
/** Copy constructor. */
Options::Options(const Options& other, const string& /*newName*/)
  : AbsObject(other),
    mHelp(other.mHelp),
    mVersion(other.mVersion),
    mCopyright(other.mCopyright),
    mBatch(other.mBatch),
    mProgName(other.mProgName),
    mInFileName(other.mInFileName)
{}

//_____________________________________________________________________________
/** Assignment operator. */
Options& Options::operator=(const Options& rhs)
{
  AbsObject::operator=(rhs);
  mHelp        = rhs.mHelp;
  mVersion     = rhs.mVersion;
  mCopyright   = rhs.mCopyright;
  mBatch       = rhs.mBatch;
  mProgName    = rhs.mProgName;
  mInFileName  = rhs.mInFileName;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t Options::isEmpty() const
{
  if(mHelp)              return kFalse;
  if(mVersion)           return kFalse;
  if(mCopyright)         return kFalse;
  if(mBatch)             return kFalse;
  if(mProgName != "")    return kFalse;
  if(mInFileName != "")  return kFalse;
  return kTrue;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void Options::clear()
{
  mHelp        = kFalse;
  mVersion     = kFalse;
  mCopyright   = kFalse;
  mBatch       = kFalse;
  mProgName    = "";
  mInFileName  = "";
}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t Options::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const Options& r = dynamic_cast<const Options&>(other); 
    // check members
    if(mHelp        != r.help())             return kFalse;
    if(mVersion     != r.version())          return kFalse;
    if(mBatch       != r.copyright())        return kFalse;
    if(mBatch       != r.batch())            return kFalse;
    if(mProgName    != r.progName())         return kFalse;
    if(mInFileName  != r.inFileName())       return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}

//_____________________________________________________________________________
/** Parse commandline options and set values. */
void Options::set(Int_t argc, Char_t** argv)
{
#ifndef HAVE_GETOPT_H
  // --------------------------------------------
  // check for GNU getopt.h
  throw Exception("Options::set: <getopt.h> not found.");
#else

  // --------------------------------------------
  // check input(s)
  if(argc < 1)
    throw Exception("Options::set: Insuficient arguments");

  // --------------------------------------------
  // save program name
  mProgName = GetFileBase(string(argv[0]));
  // SetLogPrefix(mProgName.c_str());

  // --------------------------------------------
  // struct array for feeding to getopt
  static GnuOpt_t gGnuLongOpts[] = 
    {
      {"help",                no_argument,       0, 'h'},
      {"version",             no_argument,       0, 'v'},
      {"license",             no_argument,       0, 'L'},
      {"batch",               no_argument,       0, 'b'},
      {"print-level",         required_argument, 0, 'p'},
      {0, 0, 0, 0}
    };

  // --------------------------------------------
  // read options
  Int_t optIdx(0), optChar(-1);    // getopt_long stores the option index here.
  while(1){
    // GNU getopt_long parser
    // '' = no argument, ':' = required argument, '::' = optional argument
    optChar = getopt_long(argc, argv, "vLh?bp:", gGnuLongOpts, &optIdx);
    
    // Detect the end of the options.
    if(optChar == -1) break;

    // Detect the options
    switch(optChar){

    case 'v':
      mVersion = kTrue; 
      break;

    case 'L':
      mCopyright = kTrue; 
      break;

    case 'h': 
    case '?': 
      mHelp = kTrue; 
      break;

    case 'b': 
      {
	mBatch = kTrue; 
	break;
      }

    case 'p': 
      {
	string pl(optarg);
	if(isdigit(pl[0])){
	  // digit (integer) input
	  UInt_t pld(atoi(pl.c_str()));
	  try{ SetLogLevel(IntToLogLevel(pld)); }
	  catch(const Exception& e){
	    loutW(InputArguments) << "Options::set: " << e.what() << " Using print-level = Warning (=2)." << endl;
	    SetLogLevel(kWarning);
	  }
	}
	else{
	  // string input
	  try{ SetLogLevel(LogLevel(pl.c_str())); }
	  catch(const Exception& e){
	    loutW(InputArguments) << "Options::set: " << e.what() << " Using print-level = Warning." << endl;
	    SetLogLevel(kWarning);
	  }	  
	}
	break;
      }

    default:
      throw Exception("Options::set: PC LOAD LETTER.");
    } // end option switch
  } // end while (read opts)

  // --------------------------------------------
  // first non-option argument is input filename 
  if(optind < argc)
    mInFileName = string(argv[optind++]);

  // // --------------------------------------------
  // // build some options from input file name
  // if(mInFileName != ""){
  //   // set output extension, if not already given
  //   if(mOutExt == "") mOutExt = ".json";
  //   // set output directory, if not already given
  //   if(mOutDir == "") mOutDir = GetFileDir(mInFileName);
  //   // set output file name, if not already given
  //   if(mOutFileBase == ""){
  //     string inFileBase = GetFileBase(mInFileName);
  //     mOutFileBase = inFileBase;
  //   }
  // }

#endif // end HAVE_GETOPT_H
}

//_____________________________________________________________________________
/** Print options information to the stream. */
void Options::PrintOptions(std::ostream& os)
{
  os << "Options:" << endl;
  os << "  [Flag]                    [Default]   [Description]" << endl;
  os << "  -h|-?|--help              false       Print this this help message and exit." << endl;
  os << "  -v|--version              false       Print the version and exit." << endl;
  os << "  -L|--license              false       Print the license/copyright and exit." << endl;
  // os << "  -p|--print-level          Info        The logging verbosity of the program:" << endl;
  // os << "                                        Debug (loudest), Info, Progress, Warning, Error, Fatal, Silent" << endl;
  // os << "  -b|--batch                false       Run in batch (silent) mode." << endl;
}


} // end namespace Blobb
