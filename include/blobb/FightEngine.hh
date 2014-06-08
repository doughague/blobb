/** \file      CLUI.hh 
    \brief     Header for CLUI
    \author    Doug Hague
    \date      08.06.2014
    \copyright See License.txt
*/
#ifndef BLOBB_FIGHTENGINE_HH
#define BLOBB_FIGHTENGINE_HH

#include "blobb/CLUI.hh"     // command-line user interface
#include "blobb/Random.hh"   // random numbers
#include "blobb/Warrior.hh"  // warrior

namespace Blobb {

/** \class FightEngine 
    \brief Utility class for handling command-line user interface.
*/
class FightEngine { 
public:
  FightEngine(CLUI* clui, Random* random,
	      Warrior* w1, Warrior* w2);
  inline virtual ~FightEngine() { }

  Int_t fight();

protected:
  CLUI*    mClui;   //!< clui
  Random*  mRandom; //!< random number generator
  Warrior* mW1;     //!< first warrior
  Warrior* mW2;     //!< second warrior

protected:
  // utilities
  Bool_t fightEnded() const;
  // commands
  string readCommand();
  void printMenu() const;
  void swing() const;
  void death() const;
};

} // end namespace Blobb

#endif // BLOBB_FIGHTENGINE_HH
