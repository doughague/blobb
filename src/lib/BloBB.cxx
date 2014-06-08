/** \file      src/lib/BloBB.cxx 
    \brief     Source for BloBB 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/BloBB.hh"        // this class
#include "blobb/ClassImp.hh"     // blobb class implementation
#include "blobb/LogService.hh"   // logging
#include "blobb/CLUI.hh"         // command-line user interface
#include "blobb/Options.hh"      // options
#include "blobb/FightEngine.hh"  // fighting engine
#include <sstream>               // cplusplus.com/reference/sstream/

//! Blobb class implementation macro
BLOBB_CLASS_IMP(BloBB)

namespace Blobb {

//_____________________________________________________________________________
/** \typedef Warriors_t::iterator warIter 
    \brief An iterator over a std::map of Warrior's. 
*/
typedef Warriors_t::iterator warIter;
/** \typedef Warriors_t::iterator warCIter 
    \brief A const iterator over a std::map of Warrior's. 
*/
typedef Warriors_t::const_iterator warCIter;

//_____________________________________________________________________________
/** Default constructor. */
BloBB::BloBB()
  : Named("BloBB", "Bleed or Be Bled"),
    mStartTime(-1),
    mEndTime(-1),
    mRandom(),
    mWarriors(),
    mClui()
{}

//_____________________________________________________________________________
/** Copy constructor. */
BloBB::BloBB(const BloBB& other, const string& newName)
  : Named(other),
    mStartTime(other.mStartTime),
    mEndTime(other.mEndTime),
    mRandom(other.mRandom),
    mWarriors(other.mWarriors),
    mClui(other.mClui)
{
  if(newName != "")
    setName(newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
BloBB& BloBB::operator=(const BloBB& rhs)
{
  Named::operator=(rhs);
  mStartTime = rhs.mStartTime;
  mEndTime   = rhs.mEndTime;
  mRandom    = rhs.mRandom;
  mWarriors  = rhs.mWarriors;
  mClui      = rhs.mClui;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t BloBB::isEmpty() const
{
  return kFalse;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void BloBB::clear()
{}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t BloBB::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const BloBB& b = dynamic_cast<const BloBB&>(other); 
    // check members
    if(!Named::isEqual(b))           return kFalse;
    if(mStartTime != b.startTime())  return kFalse;
    if(mEndTime   != b.endTime())    return kFalse;
    if(mRandom    != b.random())     return kFalse;
    if(mWarriors  != b.warriors())   return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}
  
//_____________________________________________________________________________
/** Read (next) command. */
string BloBB::readCommand()
{
  mClui.request("command");
  return mClui.readString();  
}

//_____________________________________________________________________________
/** Main program. */
Int_t BloBB::main()
{
  // --------------------------------------------
  // banner
  BloBB::PrintBanner(mClui);
  // print available warriors
  printWarriors();
  // menu
  printMenu();

  // --------------------------------------------
  // command loop
  string cmd = readCommand();
  while(kTrue){
    // check commands
    if     (cmd=="Q" || cmd=="quit")     break;
    else if(cmd=="L" || cmd=="load")     loadState();
    else if(cmd=="S" || cmd=="save")     saveState();
    else if(cmd=="M" || cmd=="menu")     printMenu();
    else if(cmd=="W" || cmd=="warriors") printWarriors();
    else if(cmd=="R" || cmd=="register") registerWarrior();
    else if(cmd=="F" || cmd=="fight")    fight();
    else{
      mClui.os() << "Unknown command: \"" << cmd << "\"" << endl;
      printMenu();
    }
    // read next command
    cmd = readCommand();
  }

  return 0;
}

//_____________________________________________________________________________
/** Print command menu. */
void BloBB::printMenu() const
{
  mClui.os() << endl;
  mClui.os() << "***********************************" << endl;
  mClui.os() << "Main Menu:" << endl;
  mClui.os() << "\tQ|quit      Quit the game" << endl;  
  mClui.os() << "\tM|menu      Print this menu" << endl;  
  mClui.os() << "\tL|load      Load a saved state" << endl;  
  mClui.os() << "\tS|save      Save the current state" << endl;  
  mClui.os() << "\tW|warriors  List currently available warriors" << endl;  
  mClui.os() << "\tR|register  Register new or update old warrior" << endl;  
  mClui.os() << "\tF|fight     Start a fight" << endl;  
  mClui.os() << "***********************************" << endl;
}

//_____________________________________________________________________________
/** Print all available warriors. */
void BloBB::printWarriors(Bool_t verbose) const
{
  mClui.os() << endl;
  mClui.os() << "***********************************" << endl;
  mClui.os() << "Warriors:" << endl;
  for(warCIter it = mWarriors.begin(); it != mWarriors.end(); ++it){
    if(!verbose)
      it->second.printStream(mClui.os(), kName|kTitle|kValue|kExtras, 
			     kSingleLine, "\t");
  }
  mClui.os() << "***********************************" << endl;
}

//_____________________________________________________________________________
/** Fight! */
void BloBB::fight()
{
  // print available warriors
  printWarriors();

  // get first warrior
  mClui.request("first fighter name");
  string w1Name = mClui.readString();
  Warrior* w1 = 0;
  if(mWarriors.count(w1Name) == 1) w1 = &mWarriors[w1Name];
  else{
    loutE(InputArguments) << "Cannot find warrior named \"" << w1Name << " \"!" << endl;
    return;
  }

  // get second warrior
  mClui.request("second fighter name");
  string w2Name = mClui.readString();
  Warrior* w2 = 0;
  if(mWarriors.count(w2Name) == 1) w2 = &mWarriors[w2Name];
  else{
    loutE(InputArguments) << "Cannot find warrior named \"" << w2Name << " \"!" << endl;
    return;
  }

  // set up engine
  FightEngine fe(&mClui, &mRandom, w1, w2);
  // run fight
  fe.fight();

  // print main menu when done
  printMenu();
}

//_____________________________________________________________________________
/** Register new or update old warrior. */
void BloBB::registerWarrior()
{
  Warrior w;
  printWarriors();
  mClui.request("warrior to update (empty creates new)");
  string wName = mClui.readString();
  // register new
  if(wName == ""){
    // new warrior
    w.readFromUI(mClui, kTrue);    
    // no name
    if(!w.hasName()){
      loutE(InputArguments) << "Cannot register unamed warrior!" << endl;
      return;
    }
    // check for over-write
    if(mWarriors.count(w.name()) == 0) addWarrior(w);
    else {
      loutW(InputArguments) << "Warrior named \"" << w.name() << "\" already exists!" << endl;
      mClui.request("overwrite this warrior with new values? (y/N)");
      string yorn = mClui.readString();
      if(yorn=="y" || yorn=="Y") addWarrior(w);
      else return;
    }
      
  }
  // update existing
  else{
    // check for existence
    if(mWarriors.count(wName) == 1) mWarriors[wName].readFromUI(mClui, kTrue);
    else {
      loutE(InputArguments) << "Warrior named \"" << wName << "\" not found!" << endl;
      return;
    }
  }
}

//_____________________________________________________________________________
/** Save the current state to file. */
void BloBB::saveState()
{
  std::stringstream ss;
  ss << "blobb-" << mStartTime.uts() << GetArchiveExt(gDefArcType);
  string defFileName = ss.str();
  // read file name
  mClui.request("file name to save (" + defFileName + ")");
  string fileName = mClui.readString();
  if(fileName == "") fileName = defFileName;
  mEndTime = TimeStamp(-1);
  save(fileName);
}

//_____________________________________________________________________________
/** Load a state from file. */
void BloBB::loadState()
{
  // read file name
  mClui.request("file name to load");
  string fileName = mClui.readString();
  if(fileName == ""){
    mClui.os() << "No file given to load" << endl;
    printMenu();
  }
  else{
    load(fileName);
  }
}

//_____________________________________________________________________________
/** Print usage to stream */
void BloBB::PrintUsage(ostream& os)
{
  os << "Description: Bleed or Be Bled; combat simulator." << endl;
  os << "Usage: gammet [data-file] [options]" << endl;
  os << "Arguments:" << endl;
  os << "  [data-file]   The name of the file containing previous state." << endl;
  Options::PrintOptions(os);
}

//_____________________________________________________________________________
/** Print the banner to the CLUI. */
void BloBB::PrintBanner(CLUI& clui)
{
  clui.os() << "*****************************************************************" << endl;
  clui.os() << "*                 /---\\ |        /---\\ /---\\     Bleed          *" << endl;
  clui.os() << "*                 |___/ | /---\\  |___/ |___/     or             *" << endl;
  clui.os() << "*                 |   \\ | |   |  |   \\ |   \\     Be             *" << endl;
  clui.os() << "*                 |___/ | \\___/  |___/ |___/     Bled           *" << endl;
  clui.os() << "*****************************************************************" << endl;
  clui.os() << "* blobb Copyright (C) 2014  Jason Torpy and Doug Hague          *" << endl;
  clui.os() << "*       This program comes with ABSOLUTELY NO WARRANTY.         *" << endl;
  clui.os() << "*       This is free software, and you are welcome              *" << endl;
  clui.os() << "*       to redistribute it under the conditions of GNU-GPL v3;  *" << endl;
  clui.os() << "*       see License.txt                                         *" << endl;
  TimeStamp now;
  clui.os() << "* It is now " << now.asDescription()  << " (" << now.uts() << " UTS)" << endl;
  clui.os() << "*****************************************************************" << endl;
}

//_____________________________________________________________________________
/** Build a default "workspace". */
BloBB BloBB::BuildDefault()
{
  BloBB blobb;
  Warrior w;

  // alice
  w.setNameTitle("Alice", "A Strong Warrior");
  w.mProwess.set     (60., 20.);
  w.mAgility.set     (60., 15.);
  w.mIntelligence.set(60., 5.);
  w.mPersonality.set (60., 10.);
  w.mHealth.set      (60., 5.);
  w.mFatigue.set     (60.);
  blobb.addWarrior(w);

  // bob
  w.setNameTitle("Bob", "A Weak Warrior");
  w.mProwess.set     (57.5, 20.);
  w.mAgility.set     (50.0, 15.);
  w.mIntelligence.set(50.0, 5.);
  w.mPersonality.set (50.0, 10.);
  w.mHealth.set      (50.0, 5.);
  w.mFatigue.set     (60.);
  blobb.addWarrior(w);

  // init some helpers
  blobb.setStartTime(TimeStamp(-1));
  blobb.setRandom(Random(blobb.startTime().uts()));

  return blobb;
}


} // end namespace Blobb
