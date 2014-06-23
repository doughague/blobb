/** \file      BloBB.hh
    \brief     Header for BloBB
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_BLOBB_HH
#define BLOBB_BLOBB_HH

#include "blobb/Named.hh"        // named base class
#include "blobb/TimeStamp.hh"    // time-stamp
#include "blobb/Random.hh"       // random numbers
#include "blobb/Warrior.hh"      // warrior
#include "blobb/CLUI.hh"         // command-line user interface
#include <cereal/types/map.hpp>  // map cerealization
#include <map>                   // cplusplus.com/reference/map/
using std::map;

namespace Blobb {

//_____________________________________________________________________________
/** \typedef std::map<string,Warrior> Warriors_t 
    \brief A std::map of Warrior's. 
*/
typedef map<string,Warrior> Warriors_t;

//_____________________________________________________________________________
/** \class BloBB 
    \brief Master class for game control and state persistence.
*/
class BloBB : public Named { 
public:
  BloBB();
  BloBB(const BloBB& other, const string& newName);
  BloBB& operator=(const BloBB& rhs);
  inline virtual ~BloBB() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  //! Get start time
  inline TimeStamp& startTime(){ return mStartTime; }
  //! Get start time (const)
  inline const TimeStamp& startTime() const { return mStartTime; }
  //! Set start time
  inline void setStartTime(const TimeStamp& time){ mStartTime = time; }
  //! Get end time
  inline TimeStamp& endTime(){ return mEndTime; }
  //! Get end time (const)
  inline const TimeStamp& endTime() const { return mEndTime; }
  //! Set end time
  inline void setEndTime(const TimeStamp& time){ mEndTime = time; }
  //! Get random generator
  inline Random& random(){ return mRandom; }
  //! Get random generator (const)
  inline const Random& random() const { return mRandom; }
  //! Set random generator
  inline void setRandom(const Random& rnd){ mRandom = rnd; }
  //! Get warriors map
  inline Warriors_t& warriors(){ return mWarriors; }
  //! Get warriors map (const)
  inline const Warriors_t& warriors() const { return mWarriors; }
  //! Set warriors map
  inline void setWarriors(const Warriors_t& wars){ mWarriors = wars; }
  //! Get warrior
  inline Warrior& warrior(const string& name){ return mWarriors.at(name); }
  //! Get warrior (const)
  inline const Warrior& warrior(const string& name) const { return mWarriors.at(name); }
  //! Set warrior
  inline void addWarrior(const Warrior& war){ mWarriors[war.name()] = war; }
  void printWarriors(Bool_t verbose = kFalse) const;

  void printMenu() const;

  Int_t main();

  // utilities
  static void PrintUsage(ostream& os);
  static void PrintBanner(CLUI& clui);
  static BloBB BuildDefault();

protected:
  string readCommand();
  void saveState();
  void loadState();
  void registerWarrior();
  void fight();

private:
  // data members
  TimeStamp  mStartTime; //!< start-time
  TimeStamp  mEndTime;   //!< end-time
  Random     mRandom;    //!< random numbers
  Warriors_t mWarriors;  //<! warriors
  // helpers
  mutable CLUI mClui;    //!< command-line user interface

  //! cerealize
  template <class Archive> void serialize(Archive& ar)
  {
    ar(make_nvp("Named", cereal::base_class<Named>(this)),
       BLOBB_NVP(mStartTime),
       BLOBB_NVP(mEndTime),
       BLOBB_NVP(mRandom),
       BLOBB_NVP(mWarriors));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(BloBB);   
};

} // end namespace Blobb

#endif // BLOBB_BLOBB_HH
