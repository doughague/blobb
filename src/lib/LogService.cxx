/** \file      src/lib/LogService.cxx 
    \brief     Source for logging helpers
    \author    Doug Hague
    \date      03.03.2014
    \copyright See License.txt
*/
#include "blobb/LogService.hh"  // these methods
#include "blobb/Common.hh"      // common includes
#include "blobb/Exception.hh"   // exception handler
#include <fstream>              // cplusplus.com/reference/ofstream/
#include <map>                  // cplusplus.com/reference/map/
using std::cout;
using std::clog;
using std::cerr;

namespace Blobb {

//_____________________________________________________________________________
#ifdef _WIN32
   //! "/dev/null" file stream for Windows
   static std::ofstream gDevNull("nul");
#else
   //! /dev/null file stream
   static std::ofstream gDevNull("/dev/null");
#endif

//_____________________________________________________________________________
//! Prefix for log messages.
static string gLogPrefix = "\x1b[1;41m[BloBB]\x1b[m \x1b[1;31m\xE2\x9E\xB3\x1b[m ";
// static string gLogPrefix = "BloBB";

//_____________________________________________________________________________
/** Set the prefix for log messages. */
void SetLogPrefix(const char* prefix)
{
  string spre(prefix);
  gLogPrefix = spre;
}

//_____________________________________________________________________________
//! Global logging level.
static eLogLevel gLogLevel = kInfo;

//_____________________________________________________________________________
/** Set the log level. */
void SetLogLevel(eLogLevel level)
{
  gLogLevel = level;
}

//_____________________________________________________________________________
/** Get the log level. */
eLogLevel GetLogLevel()
{
  return gLogLevel;
}

//_____________________________________________________________________________
//! Message level names.
static std::map<eLogLevel,string> gLevelNames = 
  {
    {kDebug,    "Debug"},
    {kInfo,     "Info"},
    {kProgress, "Progress"},
    {kWarning,  "Warning"},
    {kError,    "Error"},
    {kFatal,    "Fatal"},
    {kSilent,   "Silent"}
  };

//! Message topic names.
//_____________________________________________________________________________
static std::map<eLogTopic,string> gTopicNames = 
  {
    {None,           "None"},
    {InputArguments, "InputArguments"},
    {Evaluation,     "Evaluation"},
    {ObjectHandling, "ObjectHandling"},
    {DataHandling,   "DataHandling"},
    {Plotting,       "Plotting"}
  };


// //_____________________________________________________________________________
// /** Initialize the algorithm enumerated value-maps. */
// void InitLogDefs()
// {
//   if(gLevelNames.size() == 0){
//     gLevelNames[kDebug]    = "Debug";    
//     gLevelNames[kInfo]     = "Info";    
//     gLevelNames[kProgress] = "Progress";
//     gLevelNames[kWarning]  = "Warning";    
//     gLevelNames[kError]    = "Error";    
//     gLevelNames[kFatal]    = "Fatal";    
//     gLevelNames[kSilent]   = "Silent";    
//   }
//   if(gTopicNames.size() == 0){
//     gTopicNames[None]           = " ";
//     gTopicNames[InputArguments] = "InputArguments";
//     gTopicNames[Evaluation]     = "Evaluation";
//     gTopicNames[ObjectHandling] = "ObjectHandling";
//     gTopicNames[DataHandling]   = "DataHandling";
//   }
// }

//_____________________________________________________________________________
/** Get an log-level enumerated value from the name string. */
eLogLevel LogLevel(const char* name)
{
  string sname(name);
  // map iterator
  std::map<eLogLevel,string>::const_iterator it = gLevelNames.begin();
  // loop to find value and return key
  for(it = gLevelNames.begin(); it != gLevelNames.end(); ++it)
    if(it->second == sname)
      return it->first;
  // value not found
  throw Exception("LogLevel: Unknown log-level '" + sname + 
		  "', choose from: Debug, Info, Progress, Warning, Error, Fatal, Silent.");
}

//_____________________________________________________________________________
/** Get an log-level enumerated value from the name string. */
eLogLevel IntToLogLevel(Int_t val)
{
  // choose level
  switch(val){
  case 5: return kDebug;
  case 4: return kInfo;
  case 3: return kProgress;
  case 2: return kWarning;
  case 1: return kError;
  case 0: return kFatal;
  case -1: return kSilent;
  default: throw Exception("LogLevel: Unknown log-level, choose from: 5, 4, 3, 2, 1, 0, -1.");
  }
}

//_____________________________________________________________________________
/** Log a message to a stream. 
    \return C++ std::ostream associated with given message configuration
*/
ostream& Log(eLogLevel level, eLogTopic topic, Bool_t skipPrefix)
{
  // the stream
  std::ostream* os;
  // check global level
  if(level > gLogLevel && gDevNull.is_open()) 
    os = &gDevNull;
  else {
    // assign the stream
    switch(level){
    case kDebug:    os = &clog; break;
    case kInfo:     os = &clog; break;
    case kProgress: os = &clog; break;
    case kWarning:  os = &cerr; break;
    case kError:    os = &cerr; break;
    case kFatal:    os = &cerr; break;
    default:        os = &cout; break;
    }

    // Flush any previous messages
    (*os).flush();
    // print the prefix?
    if(!skipPrefix){
      (*os) << "[" << gLogPrefix << "]> ";
      // print the message
      (*os) << gLevelNames.at(level) << ":" << gTopicNames.at(topic);
      // None topic is special
      if(topic != None) (*os) << " -- ";
    }
  }

  // return the stream
  return (*os);
}

} // end namespace Blobb
