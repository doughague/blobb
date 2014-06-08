/** \file      TimeStamp.hh 
    \brief     Header for TimeStamp class
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef BLOBB_TIMESTAMP_HH
#define BLOBB_TIMESTAMP_HH

#include "blobb/AbsObject.hh"  // abstract bas class
#include <ctime>               // for struct tm, gmtime

namespace Blobb {

/** \typedef tm_t 
    Equivalent to struct C/C++ standard library time struct  
    <a href="cplusplus.com/reference/ctime/tm/" >tm</a>.
*/
typedef struct tm tm_t;


/** \class TimeStamp
    \brief Seconds since Jan 1, 1970 00:00:00 UTC.

    This class holds a single integer to be interpreted as 
    "Unix Time Stamp": seconds since Jan 1, 1970 00:00:00 UTC,
    where UTC is "Universal Time, Coordinated".

    In essence, this is a integer with 
    methods which allow setting, getting and conversion consistent 
    with interpreting the integer as seconds UTC.
    Thus, there are methods which allow this class to interact with 
    other TimeStamp objects, a (signed) integer, and 
    <a href="en.wikipedia.org/wiki/ISO_8601" >ISO-8601</a>
    formatted "time-strings", i.e. "1970-01-01T00:00:00+00:00".

    \note This class does not hold sub-second times.
*/
class TimeStamp : public AbsObject {
public:
  TimeStamp(Int_t uts = -1);
  TimeStamp(string isoString);
  TimeStamp(const TimeStamp& other, const string& /*newName*/);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual TimeStamp& operator=(const TimeStamp& rhs);
  inline virtual ~TimeStamp() { }

  Bool_t isEmpty() const;
  void clear();
  Bool_t isEqual(const AbsObject& other) const;

  inline Bool_t isSortable() const { return true; }
  Int_t compare(const AbsObject& other) const;

  //! Set the UTS value
  inline void set(Int_t uts){ mUts = uts; }
  void set(string isoString);
  void setNow();
  //! Get the UTS value
  inline time_t uts() const { return mUts; }
  string asString(Bool_t includeOffset = true) const;
  string asStringGm() const;
  string asDescription() const;

  // timezone info
  string tzAbbrev() const;
  string tzOffset() const;
  Int_t tzSecondsOffset() const;

  // arithmetic
  Double_t difference(const TimeStamp& other) const;
  TimeStamp& operator+=(Int_t seconds);
  TimeStamp& operator-=(Int_t seconds);
  TimeStamp& operator+=(string tzOffset);
  TimeStamp& operator-=(string tzOffset);

  // static utilities
  static inline UInt_t SecPerMin(){  return 60; }
  static inline UInt_t SecPerHour(){ return 3600; }
  static inline UInt_t SecPerDay(){  return 86400; }
  static inline UInt_t SecPerWeek(){ return 604800; }
  static inline UInt_t SecPerYear(){ return 31536000; }
  static inline Double_t SecToMin(Double_t sec){  return sec/SecPerMin(); }
  static inline Double_t SecToHour(Double_t sec){ return sec/SecPerHour(); }
  static inline Double_t SecToDay(Double_t sec){  return sec/SecPerDay(); }
  static inline Double_t SecToWeek(Double_t sec){ return sec/SecPerWeek(); }
  static inline Double_t SecToYear(Double_t sec){ return sec/SecPerYear(); }
  static inline Double_t MinToSec(Double_t min){   return min *SecPerMin(); }
  static inline Double_t HourToSec(Double_t hour){ return hour*SecPerHour(); }
  static inline Double_t DayToSec(Double_t day){   return day *SecPerDay(); }
  static inline Double_t WeekToSec(Double_t week){ return week*SecPerWeek(); }
  static inline Double_t YearToSec(Double_t year){ return year*SecPerYear(); }
  static Bool_t IsLeapYear(Int_t year);
  static Int_t* DaysInMonths(Bool_t isLeapYear);
  static time_t LkTime(const tm_t& timeInfo);
  static time_t GmTime(const tm_t& timeInfo);
  static tm_t GetTM(Int_t year, Int_t month, Int_t day, Int_t hour, Int_t min, Int_t sec);
  static Bool_t ParseDateTime(string dateTime, tm_t& timeInfo);
  static Int_t ParseTzOffset(string tzoffset);
  static time_t ParseIsoString(string isoString);

protected:
  tm_t* localTimeInfo();
  tm_t* localTimeInfo() const;
  tm_t* gmTimeInfo();
  tm_t* gmTimeInfo() const;

private:
  time_t mUts;  //!< Unix Time Stamp: seconds since Jan 1, 1970 00:00:00 UTC

private:
  // save minimal
  template <class Archive> string save_minimal(const Archive&) const
  {
    return asString();
  }
  // load minimal
  template <class Archive> void load_minimal(const Archive&, const string& value)
  {
    mUts = ParseIsoString(value);
  }
  // //! cerealize
  // template <class Archive> void serialize(Archive& ar)
  // {
  //   ar(BLOBB_NVP(mUts));
  // }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(TimeStamp);   
};

//_____________________________________________________________________________
/** Difference in time between t1 and t2 = t1 - t2.
    If t2 describes a time point later than t1, the result is negative.
 */
inline Double_t operator-(const TimeStamp& t1, const TimeStamp& t2)
{ 
  return t1.difference(t2); 
}

} // end namespace Blobb

#endif // BLOBB_TIMESTAMP_HH
