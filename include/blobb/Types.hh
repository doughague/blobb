/** \file      Types.hh 
    \brief     Fundamental types for this library.
    \author    Doug Hague
    \date      07.06.2014
    \copyright See License.txt
*/
#ifndef BLOBB_TYPES_HH
#define BLOBB_TYPES_HH

namespace Blobb { 

//_____________________________________________________________________________
// fundamental types
typedef bool               Bool_t;     //!< Boolean 1 bit (stored as 1 byte) (0=false, 1=true) (bool)
typedef char               Char_t;     //!< Signed Character 1 byte (char)
typedef unsigned char      UChar_t;    //!< Unsigned Character 1 byte (unsigned char)
typedef short              Short_t;    //!< Signed Short integer 2 bytes (short)
typedef unsigned short     UShort_t;   //!< Unsigned Short integer 2 bytes (unsigned short)
typedef int                Int_t;      //!< Signed integer 4 bytes (int)
typedef unsigned int       UInt_t;     //!< Unsigned integer 4 bytes (unsigned int)
typedef float              Float_t;    //!< Float 4 bytes (float)
typedef double             Double_t;   //!< Double 8 bytes (double)
#ifdef _WIN32
  typedef __int64            Long_t;   //!< Signed Long Integer 8 bytes (long int)
  typedef unsigned __int64   ULong_t;  //!< Unsigned Long Integer 8 bytes (long unsigned int)
#else
  typedef int64_t            Long_t;   //!< Signed Long Integer 8 bytes (long int)
  typedef uint64_t           ULong_t;  //!< Unsigned Long Integer 8 bytes (long unsigned int)
#endif

//_____________________________________________________________________________
// extra types
typedef const char         CChar_t;    //!< Constant Character 1 byte (const char)
typedef unsigned char      Byte_t;     //!< Byte (8 bits) (unsigned char)
typedef unsigned int       Pos_t;      //!< Position/size of string/vector/map 4 bytes (unsigned int)
typedef void*              VoidPtr_t;  //!< Void pointer

//_____________________________________________________________________________
// constants
#ifndef NULL                                               //!< NULL
#define NULL 0
#endif

static const UChar_t   kBitsPerByte = 8;                   //!< Number of bits in one byte
static const UChar_t   kSzB     = sizeof(Bool_t);          //!< size of Bool_t in memory
static const Bool_t    kFalse   = false;                   //!< false value = 0
static const Bool_t    kTrue    = true;                    //!< true value = 1

static const UChar_t   kSzC     = sizeof(Char_t);          //!< size of Char_t in memory
static const UChar_t   kMaxUC   = UChar_t(~0);             //!< maximum UChar_t value
static const Char_t    kMaxC    = kMaxUC >> 1;             //!< maximum Char_t value
static const Char_t    kMinC    = -kMaxC - 1;              //!< minimum Char_t value

static const UChar_t   kSzS     = sizeof(Short_t);         //!< size of Short_t in memory
static const UShort_t  kMaxUS   = UShort_t(~0);            //!< maximum UShort_t value
static const Short_t   kMaxS    = kMaxUS >> 1;             //!< maximum Short_t value
static const Short_t   kMinS    = -kMaxS - 1;              //!< minimum Short_t value

static const UChar_t   kSzI     = sizeof(Int_t);           //!< size of Int_t in memory
static const UInt_t    kMaxUI   = UInt_t(~0);              //!< maximum unit_t value
static const Int_t     kMaxI    = kMaxUI >> 1;             //!< maximum Int_t value
static const Int_t     kMinI    = -kMaxI - 1;              //!< minimum Int_t value

static const UChar_t   kSzF     = sizeof(Float_t);         //!< size of Float_t in memory
static const Float_t   kMaxF    = 3.4028234e38;            //!< maximum Float_t value
static const Float_t   kMinF    = -kMaxF;                  //!< minimum Float_t value

static const UChar_t   kSzD     = sizeof(Double_t);        //!< size of Double_t in memory
static const Double_t  kMaxD    = 1.7976931348623157e308;  //!< maximum Float_t value
static const Double_t  kMinD    = -kMaxD;                  //!< minimum Float_t value

static const UChar_t   kSzL     = sizeof(Long_t);          //!< size of Long_t in memory
static const ULong_t   kMaxUL   = ULong_t(~0);             //!< maximum ULong_t value
static const Long_t    kMaxL    = kMaxUL >> 1;             //!< maximum Long_t value
static const Long_t    kMinL    = -kMaxL - 1;              //!< minimum Long_t value

static const UChar_t   kSzVP    = sizeof(VoidPtr_t);       //!< size of pointer in memory
static const Bool_t    kIs64bit = (kSzVP==8);              //!< Is 64-bit?
static const ULong_t   kMaxVP   = ULong_t(~0);             //!< maximum pointer value

} // end namespace Blobb

#endif // end BLOBB_TYPES_HH
