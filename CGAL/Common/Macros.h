#ifndef CGAL_SWIG_MACROS_H
#define CGAL_SWIG_MACROS_H


//Macro functions to ease the wrapping of member functions

#define FORWARD_CALL_0(RET,NAME) \
  RET NAME()\
  {return RET(this->data.NAME());}
  
#define FORWARD_CALL_1(RET,NAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c)\
    {return RET(this->data.NAME(this->convert(c)));}
  
#define FORWARD_CALL_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2)\
    {return RET(this->data.NAME(this->convert(c1),this->convert(c2)));}
  
#define FORWARD_CALL_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3)\
    {return RET(this->data.NAME(this->convert(c1),this->convert(c2),this->convert(c3)));}
  
#define FORWARD_CALL_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4)\
    {return RET(this->data.NAME(this->convert(c1),this->convert(c2),this->convert(c3),this->convert(c4)));}
  
#define FORWARD_CALL_5(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5)\
    {return RET(this->data.NAME(this->convert(c1),this->convert(c2),this->convert(c3),this->convert(c4),this->convert(c5)));}

#define FORWARD_CALL_6(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5, const IN_TYPE_6& c6)\
    {return RET(this->data.NAME(this->convert(c1),this->convert(c2),this->convert(c3),this->convert(c4),this->convert(c5),this->convert(c6)));}

#endif //CGAL_SWIG_MACROS_H