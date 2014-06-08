/** \file      ClassDef.hh 
    \brief     Macro for Blobb class definition.
    \author    Doug Hague
    \date      10.05.2014
    \copyright See License.txt
*/
#ifndef BLOBB_CLASSDEF_HH
#define BLOBB_CLASSDEF_HH

#include "blobb/ArchiveTypes.hh"    // archive enumeration
#include <cereal/cereal.hpp>        // cereal
#include <cereal/access.hpp>        // cereal access
#include <cereal/types/string.hpp>  // string cerealization
using cereal::make_nvp;             // make name-value-pair

//_____________________________________________________________________________
//! \def BLOBB_CLASS_DEF(name) Class definition macro.
#define BLOBB_CLASS_DEF(name)                                                 \
public:								              \
 virtual AbsObject* clone(const string&) const;                               \
 virtual string className() const;		                              \
 virtual void write(ostream& os, eArchiveType arcType = gDefArcType,          \
		    const string& objName = "") const;		              \
 virtual void read(istream& is, eArchiveType arcType = gDefArcType,           \
		   const string& objName = "");				      \
private:                                                                      \
  friend class cereal::access

//_____________________________________________________________________________
//! Creates a name value pair for the variable T with almost(!) the same name as the variable
#define BLOBB_NVP(T) make_nvp(string(#T).substr(1, string(#T).length()), T)

#endif // end BLOBB_CLASSDEF_HH
