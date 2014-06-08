/** \file      Options.hh 
    \brief     Header for Options
    \author    Doug Hague
    \date      26.07.2013
    \copyright See License.txt
*/
#ifndef BLOBB_OPTIONS_HH
#define BLOBB_OPTIONS_HH

#include "blobb/AbsObject.hh"  // abstract base class

namespace Blobb {

/** \class Options 
    \brief Container for program options.
*/
class Options : public AbsObject { 
public:
  Options();
  Options(Int_t argc, Char_t** argv);
  Options(const Options& other, const string& /*newName*/);
  Options& operator=(const Options& rhs);
  inline virtual ~Options() { }

  virtual Bool_t isEmpty() const;
  virtual void clear();
  virtual Bool_t isEqual(const AbsObject& other) const;

  virtual void set(Int_t argc, Char_t** argv);
  static void PrintOptions(std::ostream& os);

  //! print help?
  inline Bool_t help() const { return mHelp; }
  //! Set is print help
  inline void setHelp(Bool_t help = kTrue){ mHelp = help; }
  //! print version?
  inline Bool_t version() const { return mVersion; }
  //! Set is print version
  inline void setVersion(Bool_t version = kTrue){ mVersion = version; }
  //! print copyright?
  inline Bool_t copyright() const { return mCopyright; }
  //! Set is print copyright
  inline void setCopyright(Bool_t copyright = kTrue)
  { mCopyright = copyright; }
  //! batch mode?
  inline Bool_t batch() const { return mBatch; }
  //! Set is print help
  inline void setBatch(Bool_t batch = kTrue){ mBatch = batch; }

  //! Get program name
  inline const string& progName() const { return mProgName; }
  //! Set input filename
  inline void setProgName(const string& name){ mProgName = name; }

  //! Get input file name
  inline const string& inFileName() const { return mInFileName; }
  //! Set input filename
  inline void setInFileName(const string& name){ mInFileName = name; }
  //! Has input file name
  inline Bool_t hasInFileName() const { return mInFileName != ""; }

protected:
  Bool_t     mHelp;         //!< print help
  Bool_t     mVersion;      //!< print version
  Bool_t     mCopyright;    //!< print copyright
  Bool_t     mBatch;        //!< batch-mode
  string     mProgName;     //!< program (executable) name
  string     mInFileName;   //!< input file name

private:
  //! cerealize
  template <class Archive> void serialize(Archive& ar)
  {
    ar(BLOBB_NVP(mHelp),
       BLOBB_NVP(mVersion),
       BLOBB_NVP(mCopyright),
       BLOBB_NVP(mBatch),
       BLOBB_NVP(mProgName),
       BLOBB_NVP(mInFileName));
  }
  //! Macro: define concrete class
  BLOBB_CLASS_DEF(Options);   
};

} // end namespace Blobb

#endif // BLOBB_OPTIONS_HH
