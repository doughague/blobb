/** \file      src/progs/blobb.cxx
    \brief     Source for binary executable for blobb.
    \author    Doug Hague
    \date      08.06.2014
    \copyright See License.txt
*/
#include "blobb/Exception.hh"   // exception handler
#include "blobb/LogService.hh"  // log service
#include "blobb/Options.hh"     // program options
#include "blobb/BloBB.hh"       // main program
using namespace Blobb;          // blobb top level namespace

//_____________________________________________________________________________
//! main method for blobb
Int_t main(Int_t argc, Char_t** argv)
{
  try {
    // --------------------------------------------
    // parse options; can throw Exception
    Options options(argc, argv);
    // Print help?
    if(options.help()){
      // Print help
      BloBB::PrintUsage(std::cout);
      return EXIT_SUCCESS;
    }

#ifdef HAVE_CONFIG_H
    // Print version?
    if(options.version()){
      std::cout << BLOBB_VERSION << endl;
      return EXIT_SUCCESS;
    }
    // print copyright?
    if(options.copyright()){
      std::cout << BLOBB_LIB_NAME << " - " << BLOBB_TITLE << endl;
      std::cout << BLOBB_COPYRIGHT << endl;
      return EXIT_SUCCESS;
    }
#else
    // Print version?
    if(options.version()){
      loutW(InputArguments) << "Version information not available." << endl;
      return EXIT_FAILURE;
    }
    // print copyright?
    if(options.copyright()){
      loutW(InputArguments) << "Copyright information not available." << endl;
      return EXIT_FAILURE;
    }
#endif // HAVE_CONFIG_H

    // --------------------------------------------
    // main program handler
    BloBB blobb;
    // check for input file-name
    if(options.hasInFileName())  blobb.load(options.inFileName());
    else                         blobb = BloBB::BuildDefault();

    // --------------------------------------------
    // run; can throw Exception
    return blobb.main();
  }
  catch(const Exception& e) {
    // catch any Exceptions
    loutF(Evaluation) << e.what() << endl;
    return EXIT_FAILURE;
  }
}
