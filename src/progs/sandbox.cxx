/** \file      src/progs/sandbox.cxx
    \brief     Source for binary executable for playing in a sandbox.
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Exception.hh"   // exception handler
#include "blobb/LogService.hh"  // log service

#include "blobb/CLUI.hh"         // command-line user interface
#include "blobb/Random.hh"       // random
#include "blobb/TimeStamp.hh"    // time-stamp
#include "blobb/Named.hh"        // named
#include "blobb/Parameter.hh"    // parameter
#include "blobb/Warrior.hh"      // warrior

using namespace Blobb;           // blobb top level namespace

//_____________________________________________________________________________
//! main method for blobb
Int_t main()
{
  CLUI clui;

  // Random r;
  // r.readFromUI(clui);
  // r.printToUI(clui);
  // r.write(cout);

  // TimeStamp t;
  // t.write(cout);

  // Named n;
  // n.readFromUI(clui);
  // n.write(cout);

  // Parameter p("MyPar", "My Parameter");
  // p.print(clui);
  // // clui.os() << p;
  // // p.readFromUI(clui);
  // // p.printToUI(clui);
  // // p.write(cout);

  Warrior w("Test", "A test warrior");
  w.readFromUI(clui, kTrue);
  // // w.print(clui);
  // w.printToUI(clui, kTrue);
  // // w.write(cout);

  return 0;
}
