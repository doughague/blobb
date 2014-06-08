/** \file      src/lib/TimeStamp.cxx 
    \brief     Source for TimeStamp class
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#include "blobb/TimeStamp.hh"  // this class
#include "blobb/ClassImp.hh"     // blobb class implementation
#include "blobb/Exception.hh"  // exception handler

//! Blobb class implementation macro
BLOBB_CLASS_IMP(TimeStamp)

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. 
    Default argument, uts = -1, sets value to local "now" time.
    \param uts Unix timestamp as an integer
 */
TimeStamp::TimeStamp(Int_t uts)
  : AbsObject(),
    mUts(uts)
{
  if(uts<0) setNow();
}

//_____________________________________________________________________________
/** Constructor from ISO-8601 time-stamp string. */
TimeStamp::TimeStamp(string isoString)
  : AbsObject(),
    mUts(0)
{
  set(isoString);
}

//_____________________________________________________________________________
/** Copy constructor. */
TimeStamp::TimeStamp(const TimeStamp& other, const string& /*newName*/)
  : AbsObject(other),
    mUts(other.mUts)
{}

//_____________________________________________________________________________
/** Cloner. */
AbsObject* TimeStamp::clone(const char* /*newName*/) const
{
  return new TimeStamp(*this);
}

//_____________________________________________________________________________
/** Assignment operator. */
TimeStamp& TimeStamp::operator=(const TimeStamp& rhs)
{
  AbsObject::operator=(rhs);
  mUts = rhs.mUts;
  return *this;
}

//_____________________________________________________________________________
/** Is this peak empty? */
Bool_t TimeStamp::isEmpty() const 
{ 
  return (mUts == 0); 
}

//_____________________________________________________________________________
/** Clear (zero) the support range(s). */
void TimeStamp::clear()
{ 
  mUts = 0;
}

//_____________________________________________________________________________
/** Does this equal other? */
Bool_t TimeStamp::isEqual(const AbsObject& other) const
{
  if(isSame(other)) return true;

  // check cast
  TimeStamp* ts = (TimeStamp*)(&other);
  if(!ts) return false;

  // check members
  if(mUts != ts->uts()) return false;

  //return
  return true;
}

//_____________________________________________________________________________
/** Compare this to other. 
    Returns: 
    - -1 if this is earlier than other, 
    - +1 if this is later
    -  0 else
*/
Int_t TimeStamp::compare(const AbsObject& other) const
{
  if(isSame(other)) return 0;

  // check cast
  TimeStamp* ts = (TimeStamp*)(&other);
  if(!ts) return 0;

  // compare time-stamp
  if(mUts < ts->uts()) return -1;
  else if(mUts > ts->uts()) return 1;
  else return 0;
}

//_____________________________________________________________________________
/** Set from ISO-8201 string. */
void TimeStamp::set(string isoString)
{
  mUts = ParseIsoString(isoString);
}

//_____________________________________________________________________________
/** Set to local time now. */
void TimeStamp::setNow()
{
  mUts = time(NULL);
}

//_____________________________________________________________________________
/** Get the local ISO-8601 time-string. */
string TimeStamp::asString(Bool_t includeOffset) const
{
  tm_t* timeInfo = localTimeInfo();
  char* buffer = new char[32];
  if(includeOffset) strftime(buffer,32,"%F %T%z",timeInfo);
  else strftime(buffer,32,"%F %T",timeInfo);
  string ret(buffer);
  delete [] buffer;
  return ret;
}

//_____________________________________________________________________________
/** Get the local ISO-8601 time-string. */
string TimeStamp::asStringGm() const
{
  tm_t* timeInfo = gmTimeInfo();
  char* buffer = new char[32];
  strftime(buffer,32,"%FT%T",timeInfo);
  string ret(buffer);
  delete [] buffer;
  return ret;
}

//_____________________________________________________________________________
/** Get the local description of the time-string. 
    i.e. 
*/
string TimeStamp::asDescription() const
{
  tm_t* timeInfo = localTimeInfo();
  char* buffer = new char[128];
  strftime(buffer,128,"%A %B %e, %Y at %T %Z",timeInfo);
  string ret(buffer);
  delete [] buffer;
  return ret;
}

//_____________________________________________________________________________
/** Timezone name or abbreviation.
    If timezone cannot be termined, no characters
 */
string TimeStamp::tzAbbrev() const
{
  tm_t* timeInfo = localTimeInfo();
  char* buffer = new char[32];
  strftime(buffer,32,"%Z",timeInfo);
  string ret(buffer);
  delete [] buffer;
  return ret;
}

//_____________________________________________________________________________
/** ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
    If timezone cannot be determined, no characters.
 */
string TimeStamp::tzOffset() const
{
  tm_t* timeInfo = localTimeInfo();
  char* buffer = new char[32];
  strftime(buffer,32,"%z",timeInfo);
  string ret(buffer);
  delete [] buffer;
  return ret;
}

//_____________________________________________________________________________
/** Seconds offset from UTC in timezone
    If timezone cannot be determined, zero.
 */
Int_t TimeStamp::tzSecondsOffset() const
{
  string tzo = tzOffset();
  if(tzo.length() == 0) return 0;
  else return ParseTzOffset(tzo);
}

//_____________________________________________________________________________
/** Difference in time between this and other.
    If other describes a time point later than this, the result is negative.
 */
Double_t TimeStamp::difference(const TimeStamp& other) const
{
  return difftime(mUts, other.uts());
}

//_____________________________________________________________________________
/** Add to this. */
TimeStamp& TimeStamp::operator+=(Int_t seconds)
{
  mUts += seconds;
  return *this;
}

//_____________________________________________________________________________
/** Subtract from this. */
TimeStamp& TimeStamp::operator-=(Int_t seconds)
{
  mUts -= seconds;
  return *this;
}

//_____________________________________________________________________________
/** Add to this. */
TimeStamp& TimeStamp::operator+=(string tzOffset)
{
  mUts += ParseTzOffset(tzOffset);
  return *this;
}

//_____________________________________________________________________________
/** Subtract from this. */
TimeStamp& TimeStamp::operator-=(string tzOffset)
{
  mUts -= ParseTzOffset(tzOffset);
  return *this;
}

//_____________________________________________________________________________
/** Get a pointer to a (local) time information struct. */
tm_t* TimeStamp::localTimeInfo()
{
  return localtime(&mUts);
}

//_____________________________________________________________________________
/** const Get a pointer to a (local) time information struct. */
tm_t* TimeStamp::localTimeInfo() const
{
  return localtime(&mUts);
}

//_____________________________________________________________________________
/** Get a pointer to a (gm) time information struct. */
tm_t* TimeStamp::gmTimeInfo()
{
  return gmtime(&mUts);
}

//_____________________________________________________________________________
/** const Get a pointer to a (gm) time information struct. */
tm_t* TimeStamp::gmTimeInfo() const
{
  return gmtime(&mUts);
}

//_____________________________________________________________________________
/** Is the given year a leap year?

    The calendar year is 365 days long, unless the year is exactly divisible
    by 4, in which case an extra day is added to February to make the year
    366 days long. If the year is the last year of a century, eg. 1700, 1800,
    1900, 2000, then it is only a leap year if it is exactly divisible by
    400. Therefore, 1900 wasn't a leap year but 2000 was. The reason for
    these rules is to bring the average length of the calendar year into
    line with the length of the Earth's orbit around the Sun, so that the
    seasons always occur during the same months each year. 
*/
Bool_t TimeStamp::IsLeapYear(Int_t year)
{
  return (year % 4 == 0) && !((year % 100 == 0) && (year % 400 > 0));
}

//_____________________________________________________________________________
/** Array of days in each month of the year. 

    \warning February (daysInMonth[1]) is set to zero and must be adjusted based on 
    isLeapYear, e.g.
    \code
    daysInMonth[1] = isLeapYear ? 29 : 28;
    \endcode
*/
Int_t* TimeStamp::DaysInMonths(Bool_t isLeapYear)
{
  static Int_t daysInMonth[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  daysInMonth[1] = isLeapYear ? 29 : 28;
  return daysInMonth;
}

//_____________________________________________________________________________
/** Returns the value of type time_t that represents the local time described 
    by the tm structure timeInfo.

    This function performs the reverse translation that localTimeInfo (localtime) does. 
*/
time_t TimeStamp::LkTime(const tm_t& timeInfo)
{
  // make non-const copy
  tm_t ticp = timeInfo;
  return mktime(&ticp);
}

//_____________________________________________________________________________
/** Returns the value of type time_t that represents the UTC time described 
    by the tm structure timeInfo.

    Similar to standard routine "mktime" but
    using the assumption that tm struct is filled with UTC, not local, time.
   
    \param timeInfo C/C++ standard library time struct.
           See <a href="cplusplus.com/reference/ctime/tm/" >tm</a>.

    \warning This version IS NOT configured to handle every possible
    weirdness of out-of-range values in the case of normalizing
    the tm struct.
   
    \warning This version DOES NOT correctly handle values that can't be
    fit into a time_t (i.e. beyond year 2038-01-18 19:14:07, or
    before the start of Epoch).
*/
time_t TimeStamp::GmTime(const tm_t& timeInfo)
{
  // get days in months
  Int_t* dim = DaysInMonths(IsLeapYear(timeInfo.tm_year));

  // copy input struct so that input doesn't change
  tm_t tm_cp = timeInfo;

  // reference values
  Int_t ref_tm_mon = tm_cp.tm_mon;
  Int_t ref_tm_mday = tm_cp.tm_mday;

  // count days in months past
  tm_cp.tm_yday = 0;
  for(Int_t imonth = 0; imonth < ref_tm_mon; imonth++) {
    tm_cp.tm_yday += dim[imonth];
  }
  // day [1-31] but yday [0-365]
  tm_cp.tm_yday += ref_tm_mday - 1;

  // adjust if day in this month is more than the month has
  while(ref_tm_mday > dim[ref_tm_mon]) {
    ref_tm_mday -= dim[ref_tm_mon];
    ref_tm_mon++;
  }

  // *should* calculate tm_wday (0-6) here ...

  // UTC is never DST
  tm_cp.tm_isdst = 0;

  // Calculate seconds since the Epoch based on formula in
  // POSIX IEEEE Std 1003.1b-1993 pg 22
  return (tm_cp.tm_sec +
	  tm_cp.tm_min*SecPerMin() +
	  tm_cp.tm_hour*SecPerHour() +
	  tm_cp.tm_yday*SecPerDay() +
	  (tm_cp.tm_year-70)*SecPerYear() +
	  ((tm_cp.tm_year-69)/4)*SecPerDay());  
}

//_____________________________________________________________________________
/** Returns the strunct tm that represents the time described 
    by the input parameters.
*/
tm_t TimeStamp::GetTM(Int_t year, Int_t month, Int_t day, Int_t hour, Int_t min, Int_t sec)
{
  tm_t timeInfo;
  timeInfo.tm_year = year - 1900;
  timeInfo.tm_mon  = month - 1;
  timeInfo.tm_mday = day;
  timeInfo.tm_hour = hour;
  timeInfo.tm_min  = min;
  timeInfo.tm_sec  = sec;
  return timeInfo;
}

//_____________________________________________________________________________
/** Parse the ISO-8601 date-time string, e.g. "yyyy-mm-ddThh:mm:ss", into time-info struct. 
    \return failed Bool_tean.
*/
Bool_t TimeStamp::ParseDateTime(string dateTime, tm_t& timeInfo)
{
  // check length
  if(dateTime.length() < 19){
    throw Exception("TimeStamp::ParseDateTime: Ill-formatted string, " \
		    "date-time string too short, use e.g. \"yyyy-mm-dd hh:mm:ss\"");
  }
  
  // check format
  if(dateTime[4] != '-' || dateTime[7] != '-' || 
     dateTime[13] != ':' || dateTime[16] != ':'){
    throw Exception("TimeStamp::ParseDateTime: Ill-formatted string, " \
		    "use i.e. \"yyyy-mm-dd hh:mm:ss\"");
  }

  // extract date-time components
  Int_t year  = atoi( dateTime.substr( 0, 4).c_str() );
  Int_t month = atoi( dateTime.substr( 5, 2).c_str() );
  Int_t day   = atoi( dateTime.substr( 8, 2).c_str() );
  Int_t hour  = atoi( dateTime.substr(11, 2).c_str() );
  Int_t min   = atoi( dateTime.substr(14, 2).c_str() );
  Int_t sec   = atoi( dateTime.substr(17, 2).c_str() );

  // return
  timeInfo = GetTM(year, month, day, hour, min, sec);
  return false;
}

//_____________________________________________________________________________
/** Parse the time-zone string, e.g. "+hh:mm" into total seconds offset. 
    \return total seconds of off-set to UTC.
*/
Int_t TimeStamp::ParseTzOffset(string tzoffset)
{
  // check length
  if(tzoffset.length() < 5){
    throw Exception("TimeStamp::ParseTzOffset: Ill-formatted string, " \
		    "time-zone offset too short, use e.g. \"+hhmm\"");
  }

  // check format
  if(tzoffset[0] != '+' && tzoffset[0] != '-'){
    throw Exception("TimeStamp::ParseTzOffset: Ill-formatted string, " \
		    "use i.e. \"+hhmm\"");
  }

  // extract time components
  Int_t hour = atoi( tzoffset.substr(1,2).c_str() );
  Int_t min  = atoi( tzoffset.substr(3,2).c_str() );

  // convert to seconds
  Int_t sec = Int_t(TimeStamp::HourToSec(hour) + TimeStamp::MinToSec(min));

  // check for negative
  if(tzoffset[0]=='-') sec *= -1;

  // return
  return sec;  
}

//_____________________________________________________________________________
/** Parse the ISO-8601 date-time string, e.g. "yyyy-mm-ddThh:mm:ss+hh:mm", into time_t. */
time_t TimeStamp::ParseIsoString(string isoString)
{
  // check length
  size_t sz = isoString.length();
  if(sz < 19){
    throw Exception("TimeStamp::ParseIsoString: Ill-formatted string, " \
		    "date-time string too short, use e.g. \"yyyy-mm-ddThh:mm:ss\"");
  }

  // parse date-time part of string
  tm_t timeInfo;
  Bool_t dtFailed = ParseDateTime(isoString, timeInfo);
  if(dtFailed) return 0;

  // check for & parse tz-offset
  Int_t secOffset(0);
  if(sz >= 24) secOffset = ParseTzOffset(isoString.substr(19,6));

  // create UTS
  time_t uts = GmTime(timeInfo);
  uts += secOffset;
  return uts;
}

} // end namespace Blobb
