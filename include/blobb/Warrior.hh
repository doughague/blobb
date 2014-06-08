/** \file      Warrior.hh 
    \brief     Header for Warrior
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_WARRIOR_HH
#define BLOBB_WARRIOR_HH

#include "blobb/Named.hh"      // named base class
#include "blobb/Parameter.hh"  // parameter

namespace Blobb {

class Random;

/** \class Warrior 
    \brief Container for a warrior.
*/
class Warrior : public Named { 
public:
  Warrior(const string& name = "", const string& title = "");
  Warrior(const Warrior& other, const string& newName);
  Warrior& operator=(const Warrior& rhs);
  inline virtual ~Warrior() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  Double_t calcDisability();
  Bool_t fightOrFlight(const Random& random);
  Double_t swingQuality(const Random& random);
  string updateDisability(Int_t hstat, Int_t fstat, Bool_t forf,
			  const Random& random);
  string updateDisability(Bool_t forf, const Random& random);
  Bool_t collapsed() const;

  // printing
  void printValue(ostream& os) const;
  void printExtras(ostream& os) const;

  // user interface plug-in
  virtual Bool_t readFromUI(CLUI& clui, Bool_t verbose = kFalse);
  virtual void printToUI(CLUI& clui, Bool_t verbose = kFalse) const;

public:
  // Attributes
  Parameter mProwess;       //!< prowess
  Parameter mAgility;       //!< agility
  Parameter mIntelligence;  //!< intelligence
  Parameter mPersonality;   //!< personality
  Parameter mHealth;        //!< health
  // Disabilities
  Parameter mFatigue;       //!< fatigue
  Parameter mStun;          //!< stun
  Parameter mDisarm;        //!< disarm
  Parameter mFallen;        //!< fallen
  Parameter mFatigueTime;   //!< fatigueTime
  Parameter mHealthTime;    //!< healthTime

private:
  //! cerealize
  template <class Archive> void serialize(Archive& ar)
  {
    ar(make_nvp("Named", cereal::base_class<Named>(this)),
       BLOBB_NVP(mProwess),
       BLOBB_NVP(mAgility),
       BLOBB_NVP(mIntelligence),
       BLOBB_NVP(mPersonality),
       BLOBB_NVP(mHealth),
       BLOBB_NVP(mFatigue),
       BLOBB_NVP(mStun),
       BLOBB_NVP(mDisarm),
       BLOBB_NVP(mFallen),
       BLOBB_NVP(mFatigueTime),
       BLOBB_NVP(mHealthTime));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(Warrior);   
};

} // end namespace Blobb

#endif // BLOBB_WARRIOR_HH
