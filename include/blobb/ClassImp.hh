/** \file      ClassImp.hh 
    \brief     Macro for Blobb class implementation.
    \author    Doug Hague
    \date      10.05.2014
    \copyright See License.txt
*/
#ifndef BLOBB_CLASSIMP_HH
#define BLOBB_CLASSIMP_HH

#include <cereal/archives/binary.hpp>    // cereal binary archive
#include <cereal/archives/json.hpp>      // cereal JSON archive
#include <cereal/archives/xml.hpp>       // cereal XML archive
#include <cereal/types/polymorphic.hpp>  // cereal poly & registration

//_____________________________________________________________________________
/** \def BLOBB_CLASS_IMP(name) 
    Class implementation macro
*/
#define BLOBB_CLASS_IMP(name)                                                 \
  CEREAL_REGISTER_TYPE(Blobb::name)					      \
  Blobb::AbsObject* Blobb::name::clone(const string& newName) const           \
  {                                                                           \
    return new name(*this, newName);                                          \
  }                                                                           \
  string Blobb::name::className() const { return string(#name); }	      \
  void Blobb::name::write(ostream& os, eArchiveType arcType,                  \
			  const string& objName) const	                      \
  {                                                                           \
    string n = objName;                                                       \
    if(n == "") n = className();                                              \
    switch(arcType){                                                          \
    case kBinary :                                                            \
      {                                                                       \
  	cereal::BinaryOutputArchive boa(os);                                  \
  	boa(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    case kJson :                                                              \
      {                                                                       \
  	cereal::JSONOutputArchive joa(os);                                    \
  	joa(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    case kXml :                                                               \
      {                                                                       \
  	cereal::XMLOutputArchive xoa(os);                                     \
  	xoa(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    }                                                                         \
  }                                                                           \
  void Blobb::name::read(istream& is, eArchiveType arcType,                   \
			 const string& objName)                               \
  {                                                                           \
    string n = objName;                                                       \
    if(n == "") n = className();                                              \
    switch(arcType){                                                          \
    case kBinary :                                                            \
      {                                                                       \
  	cereal::BinaryInputArchive bia(is);                                   \
  	bia(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    case kJson :                                                              \
      {                                                                       \
  	cereal::JSONInputArchive jia(is);                                     \
  	jia(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    case kXml :                                                               \
      {                                                                       \
  	cereal::XMLInputArchive xia(is);                                      \
  	xia(make_nvp(n, *this));                                              \
  	return;                                                               \
      }                                                                       \
    }                                                                         \
  }                                                                           

#endif // end BLOBB_CLASSIMP_HH
