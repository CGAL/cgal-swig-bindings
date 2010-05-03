//no inclusion protection, use with caution

#include "Macros.h"

#ifndef CGAL_SWIG_GF_MACRO_DEFINITION
//Macro used to ease the wrapping of global functions
#define FORWARD_CALL_GF_1(RET,NAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE>::convert(c)));\
  }

#define FORWARD_CALL_GF_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2) \
              )           );\
  }
  
#define FORWARD_CALL_GF_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2),\
                            internal::Converter<IN_TYPE_3>::convert(c3) \
              )           );\
  }

#define FORWARD_CALL_GF_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3,const IN_TYPE_4& c4){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2),\
                            internal::Converter<IN_TYPE_3>::convert(c3),\
                            internal::Converter<IN_TYPE_4>::convert(c4) \
              )           );\
  }
  
#define FORWARD_CALL_GF_5(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3,const IN_TYPE_4& c4,const IN_TYPE_5& c5){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2),\
                            internal::Converter<IN_TYPE_3>::convert(c3),\
                            internal::Converter<IN_TYPE_4>::convert(c4),\
                            internal::Converter<IN_TYPE_5>::convert(c5) \
              )           );\
  }
  
#define FORWARD_CALL_GF_6(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3,const IN_TYPE_4& c4,const IN_TYPE_5& c5,const IN_TYPE_6& c6){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2),\
                            internal::Converter<IN_TYPE_3>::convert(c3),\
                            internal::Converter<IN_TYPE_4>::convert(c4),\
                            internal::Converter<IN_TYPE_5>::convert(c5),\
                            internal::Converter<IN_TYPE_6>::convert(c6) \
              )           );\
  }
  
#define FORWARD_CALL_GF_7(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6,IN_TYPE_7) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3,const IN_TYPE_4& c4,const IN_TYPE_5& c5,const IN_TYPE_6& c6,const IN_TYPE_7& c7){\
    return RET(CGAL:: NAME( internal::Converter<IN_TYPE_1>::convert(c1),\
                            internal::Converter<IN_TYPE_2>::convert(c2),\
                            internal::Converter<IN_TYPE_3>::convert(c3),\
                            internal::Converter<IN_TYPE_4>::convert(c4),\
                            internal::Converter<IN_TYPE_5>::convert(c5),\
                            internal::Converter<IN_TYPE_6>::convert(c6),\
                            internal::Converter<IN_TYPE_7>::convert(c7) \
              )           );\
  }

#else
#define FORWARD_CALL_GF_1(RET,NAME,IN_TYPE) RET NAME(const IN_TYPE&);
#define FORWARD_CALL_GF_2(RET,NAME,IN_TYPE_1,IN_TYPE_2)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&);
#define FORWARD_CALL_GF_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&,const IN_TYPE_3&);
#define FORWARD_CALL_GF_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&,const IN_TYPE_3&,const IN_TYPE_4&);
#define FORWARD_CALL_GF_5(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&,const IN_TYPE_3&,const IN_TYPE_4&,const IN_TYPE_5&);
#define FORWARD_CALL_GF_6(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&,const IN_TYPE_3&,const IN_TYPE_4&,const IN_TYPE_5&,const IN_TYPE_6&);
#define FORWARD_CALL_GF_7(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6,IN_TYPE_7)  RET NAME(const IN_TYPE_1&,const IN_TYPE_2&,const IN_TYPE_3&,const IN_TYPE_4&,const IN_TYPE_5&,const IN_TYPE_6&,const IN_TYPE_7&);
#endif
