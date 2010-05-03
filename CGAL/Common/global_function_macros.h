//no inclusion protection, use with caution

#include "Macros.h"

#ifndef CGAL_SWIG_GF_MACRO_DEFINITION
//Macro used to ease the wrapping of global functions
#define FORWARD_CALL_GF_1(RET,NAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c){\
    return RET(CGAL:: NAME(internal::Converter<IN_TYPE>::convert(c)));\
  }

#define FORWARD_CALL_GF_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){\
    return RET(CGAL:: NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2)));\
  }
#else
#define FORWARD_CALL_GF_1(RET,NAME,IN_TYPE) RET NAME(const IN_TYPE& c);
#define FORWARD_CALL_GF_2(RET,NAME,IN_TYPE_1,IN_TYPE_2)  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2);
#endif
