/** \file      LogService.hh 
    \brief     Header for LogService class.
    \author    Doug Hague
    \date      23.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_LOGSERVICE_HH
#define BLOBB_LOGSERVICE_HH

#include <iostream>  // cplusplus.com/reference/iostream/
using std::ostream;  // STL out-stream
using std::endl;     // STL end-line

namespace Blobb {

//_____________________________________________________________________________
/** \enum eLogLevel Log message level. */
enum eLogLevel { 
  kDebug    = 5, //!< debugging
  kInfo     = 4, //!< information
  kProgress = 3, //!< progress
  kWarning  = 2, //!< warning
  kError    = 1, //!< error
  kFatal    = 0, //!< fatal
  kSilent   = -1 //!< silent
};

//_____________________________________________________________________________
/** \enum eLogTopic Log message topic. */
enum eLogTopic { 
  None           = 1,  //!< no topic
  InputArguments = 2,  //!< input arguments
  Evaluation     = 4,  //!< evaluation
  ObjectHandling = 8,  //!< object handling
  DataHandling   = 16, //!< data handling
  Plotting       = 32  //!< data handling
};

//_____________________________________________________________________________
// logging methods
void SetLogPrefix(const char* prefix);
void SetLogLevel(eLogLevel level);
eLogLevel GetLogLevel();
eLogLevel LogLevel(const char* name);
eLogLevel IntToLogLevel(int val);
ostream& Log(eLogLevel level, eLogTopic topic, bool skipPrefix = false);

} // end namespace Blobb


//_____________________________________________________________________________
// Shortcut streamer definitions, with topic 
//! Stream debug message macro. 
#define loutD(t) Blobb::Log(Blobb::kDebug,t) 
//! Stream info message macro. 
#define loutI(t) Blobb::Log(Blobb::kInfo,t) 
//! Stream progress message macro. 
#define loutP(t) Blobb::Log(Blobb::kProgress,t) 
//! Stream warning message macro. 
#define loutW(t) Blobb::Log(Blobb::kWarning,t) 
//! Stream error message macro. 
#define loutE(t) Blobb::Log(Blobb::kError,t) 
//! Stream fatal message macro. 
#define loutF(t) Blobb::Log(Blobb::kFatal,t) 

//! Stream debug message macro - no prefix. 
#define loutnpD(t) Blobb::Log(Blobb::kDebug,t,true) 
//! Stream progress message macro - no prefix. 
#define loutnpP(t) Blobb::Log(Blobb::kProgress,t,true) 

#endif // end BLOBB_LOGSERVICE_HH
