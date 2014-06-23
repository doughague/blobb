/** \file      Warrior.cxx 
    \brief     Source for Warrior 
    \author    John D. Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#include "blobb/Warrior.hh"   // this class
#include "blobb/ClassImp.hh"  // blobb class implementation
#include "blobb/Random.hh"    // random number
#include "blobb/CLUI.hh"      // command-line user interface

//! Blobb class implementation macro
BLOBB_CLASS_IMP(Warrior)

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
Warrior::Warrior(const string& name, const string& title)
  : Named(name, title),
    mProwess("Prowess", ""),
    mAgility("Agility", ""),
    mIntelligence("Intelligence", ""),
    mPersonality("Personality", ""),
    mHealth("Health", ""),
    mFatigue("Fatigue", ""),
    mStun("Stun", ""),
    mDisarm("Disarm", ""),
    mFallen("Fallen", ""),
    mFatigueTime("FatigueTime", ""),
    mHealthTime("HealthTime", "")
{}

//_____________________________________________________________________________
/** Copy constructor. */
Warrior::Warrior(const Warrior& other, const string& newName)
  : Named(other),
    mProwess(other.mProwess),
    mAgility(other.mAgility),
    mIntelligence(other.mIntelligence),
    mPersonality(other.mPersonality),
    mHealth(other.mHealth),
    mFatigue(other.mFatigue),
    mStun(other.mStun),
    mDisarm(other.mDisarm),
    mFallen(other.mFallen),
    mFatigueTime(other.mFatigueTime),
    mHealthTime(other.mHealthTime)
{
  if(newName != "")
    setName(newName);
}

//_____________________________________________________________________________
/** Assignment operator. */
Warrior& Warrior::operator=(const Warrior& rhs)
{
  Named::operator=(rhs);
  mProwess      = rhs.mProwess;
  mAgility      = rhs.mAgility;
  mIntelligence = rhs.mIntelligence;
  mPersonality  = rhs.mPersonality;
  mHealth       = rhs.mHealth;
  mFatigue      = rhs.mFatigue;
  mStun         = rhs.mStun;
  mDisarm       = rhs.mDisarm;
  mFallen       = rhs.mFallen;
  mFatigueTime  = rhs.mFatigueTime;
  mHealthTime   = rhs.mHealthTime;
  return *this;
}

//_____________________________________________________________________________
/** Has counts != 0. in any bin? */
Bool_t Warrior::isEmpty() const
{
  if(!mProwess.isEmpty())      return kFalse;
  if(!mAgility.isEmpty())      return kFalse;
  if(!mIntelligence.isEmpty()) return kFalse;
  if(!mPersonality.isEmpty())  return kFalse;
  if(!mHealth.isEmpty())       return kFalse;
  if(!mFatigue.isEmpty())      return kFalse;
  if(!mStun.isEmpty())         return kFalse;
  if(!mDisarm.isEmpty())       return kFalse;
  if(!mFallen.isEmpty())       return kFalse;
  if(!mFatigueTime.isEmpty())  return kFalse;
  if(!mHealthTime.isEmpty())   return kFalse;
  return kTrue;
}

//_____________________________________________________________________________
/** Set all counts to zero. */
void Warrior::clear()
{
  mProwess.clear();
  mAgility.clear();
  mIntelligence.clear();
  mPersonality.clear();
  mHealth.clear();
  mFatigue.clear();
  mStun.clear();
  mDisarm.clear();
  mFallen.clear();
  mFatigueTime.clear();
  mHealthTime.clear();
}

//_____________________________________________________________________________
/** Equivalence. */
Bool_t Warrior::isEqual(const AbsObject& other) const
{
  // check pointer
  if(isSame(other)) return kTrue;
  // check members
  try{ 
    // dynamically cast
    const Warrior& w = dynamic_cast<const Warrior&>(other); 
    // check members
    if(!Named::isEqual(w))               return kFalse;
    if(mProwess      != w.mProwess)      return kFalse;
    if(mAgility      != w.mAgility)      return kFalse;
    if(mIntelligence != w.mIntelligence) return kFalse;
    if(mPersonality  != w.mPersonality)  return kFalse;
    if(mHealth       != w.mHealth)       return kFalse;
    if(mFatigue      != w.mFatigue)      return kFalse;
    if(mStun         != w.mStun)         return kFalse;
    if(mDisarm       != w.mDisarm)       return kFalse;
    if(mFallen       != w.mFallen)       return kFalse;
    if(mFatigueTime  != w.mFatigueTime)  return kFalse;
    if(mHealthTime   != w.mHealthTime)   return kFalse;
    return kTrue;
  }
  catch(const bad_cast& bc){ return kFalse; }
}

//_____________________________________________________________________________
//! Calculate the disability
/** Assess level of disability and apply to personality to determine 
    willingness to attack. 
*/
Double_t Warrior::calcDisability()
{
  return mStun.value() + mDisarm.value() + mFallen.value();
}

//_____________________________________________________________________________
//! Establish fight-or-flight
/** Decided whether the warrior will attack or defend.
    \return true means attack */
Bool_t Warrior::fightOrFlight(const Random& rnd)
{
  return ((mPersonality.getRandom(rnd) - 20.*calcDisability()) > 55.);
}

//_____________________________________________________________________________
//! Update the disability
/** At the end of the fight = stun, disarm, fall
    \return message
*/
string Warrior::updateDisability(Int_t hstat, Int_t fstat, Bool_t forf,
				 const Random& rnd)
{
  // modify "disabilty"
  int disMod(0);    
  if(fstat<30) disMod += 10;
  if(hstat<50) disMod +=  5;
  if(hstat<20) disMod += 10;
  if(forf)     disMod -= 20;

  // update values
  Double_t checkStun   = rnd.gaussian(50+disMod,10);
  Double_t checkDisarm = rnd.gaussian(50+disMod,10);
  Double_t checkFall   = rnd.gaussian(50+disMod,10);

  string msg("");
  // stun
  if(checkStun>80 && mStun.value()==0) {
    mStun.setValue(mStun.value() + 1);
    msg += " is stunned";
  }
  else if(checkStun<30 && mStun.value()==1) {
    mStun.setValue(mStun.value() - 1);
    msg += " shakes off the cobwebs";
  }

  // disarm
  if(checkDisarm>80 && mDisarm.value()==0) {
    mDisarm.setValue(mDisarm.value()+1);
    msg += " is disarmed";
  }
  else if(checkDisarm<30 && mDisarm.value()==1) {
    mStun.setValue(mStun.value()-1);
    msg += " recovers a weapon";
  }

  // fallen
  if(checkFall>80 && mFallen.value()==0) {
    mFallen.setValue(mFallen.value()+1);
    msg += " has fallen";
  }
  else if(checkFall<30 && mFallen.value()==1) {
    mStun.setValue(mStun.value()-1);
    msg += " is standing again";
  }

  return msg;
}

//_____________________________________________________________________________
//! Update the disability
/** At the end of the fight = stun, disarm, fall
    \return message
*/
string Warrior::updateDisability(Bool_t forf, const Random& rnd)
{
  return updateDisability(mHealth.value(), mFatigue.value(), forf, rnd); 
}

//_____________________________________________________________________________
//! Determine quality of attack action.
/** Use attributes including fatigue and disabilities to determine quality of attack:
    triple prowess + agility and intel less fatigue.
 */
Double_t Warrior::swingQuality(const Random& rnd)
{
  return 3.*mProwess.getRandom(rnd)   + 
         mAgility.getRandom(rnd)      + 
         mIntelligence.getRandom(rnd) - 
         mFatigue.value();
}

//_____________________________________________________________________________
/** Is this warrior collapsed? */
Bool_t Warrior::collapsed() const
{
  return (mHealth.value()  <=0. || 
	  mFatigue.value() <=0.);
}

//_____________________________________________________________________________
//! Interface to print value of object
void Warrior::printValue(ostream& os) const
{
  os << "{" 
     << mProwess.value() << ","
     << mAgility.value() << "," 
     << mIntelligence.value() << "," 
     << mPersonality.value() << "," 
     << mHealth.value()
     << "}";
}

//_____________________________________________________________________________
//! Interface to print extras
void Warrior::printExtras(ostream& os) const
{
  os << "{" 
     << mFatigue.value() << ","
     << mStun.value() << "," 
     << mDisarm.value() << "," 
     << mFallen.value() << "," 
     << mFatigueTime.value() << "," 
     << mHealthTime.value()
     << "}";
}

//_____________________________________________________________________________
//! Read this object from user interface.
Bool_t Warrior::readFromUI(CLUI& clui, Bool_t verbose) 
{ 
  // local menu
  if(verbose){
    clui.os() << "Warrior attribute menu: " << endl;
    clui.os() << "  (0) None/exit" << endl;
    clui.os() << "  (1) Name & title (" << name() << ", " << title() << ")" << endl;
    clui.os() << "  (2) Prowess (" << mProwess.value() << "~" << mProwess.error() << ")" << endl;
    clui.os() << "  (3) Agility (" << mAgility.value() << "~" << mAgility.error() << ")" << endl;
    clui.os() << "  (4) Intelligence (" << mIntelligence.value() << "~" << mIntelligence.error() << ")" << endl;
    clui.os() << "  (5) Personality (" << mPersonality.value() << "~" << mPersonality.error() << ")" << endl;
    clui.os() << "  (6) Health (" << mHealth.value() << "~" << mHealth.error() << ")" << endl;
  }

  // request
  clui.request("attribute (0-6) to update for Warrior::"+name());
  Int_t attrib = UInt_t(clui.readDouble());
  switch(attrib){
  case 0:
    return kTrue;
  case 1: 
    Named::readFromUI(clui);
    break;
  case 2: 
    mProwess.readFromUI(clui, kFalse);
    break;
  case 3: 
    mAgility.readFromUI(clui, kFalse);
    break;
  case 4: 
    mIntelligence.readFromUI(clui, kFalse);
    break;
  case 5: 
    mPersonality.readFromUI(clui, kFalse);
    break;
  case 6: 
    mHealth.readFromUI(clui, kFalse);
    break;
  default:
    {
      clui.os() << "ERROR: Unknown attribute \"" << attrib << "\", choose again." << endl;
      readFromUI(clui, kTrue);
    }
  }

  // introspect, user must enter 0 to exit!!
    // bug: error values not assigning
    // bug: new names can't be referenced for subsequent warrior edits
  readFromUI(clui);
  return kTrue;
}

//_____________________________________________________________________________
//! Print this object to user interface.
void Warrior::printToUI(CLUI& clui, Bool_t verbose) const
{ 
  // Warrior head
  printStream(clui.os(), kClassName|kName|kTitle, kSingleLine);
  // atributes
  string indent("         ");
  mProwess.print     (clui, indent+"     ");
  mAgility.print     (clui, indent+"     ");
  mIntelligence.print(clui, indent);
  mPersonality.print (clui, indent+" ");
  mHealth.print      (clui, indent+"      ");
  // disabilities
  if(verbose){
    mFatigue.print    (clui, indent+"     ");
    mStun.print       (clui, indent+"        ");
    mDisarm.print     (clui, indent+"      ");
    mFallen.print     (clui, indent+"      ");
    mFatigueTime.print(clui, indent+" ");
    mHealthTime.print (clui, indent+"  ");
  }
}

} // end namespace Blobb
