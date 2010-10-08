#ifndef CGAL_SWIG_MACROS_H
#define CGAL_SWIG_MACROS_H

#include <SWIG_CGAL/Common/triple.h>
#include <CGAL/utility.h>

#include <boost/mpl/if.hpp>


//Functor for FORWARD_CALL_N

namespace internal{

#define SPECIALIZE_CONVERTER(T)                    \
template <> struct Converter<T>{                   \
  static const bool is_reference=true;             \
  typedef T result_type;                           \
  static const T& convert(const T& t){return t;}   \
};


template <class T>
struct Converter{
  typedef typename T::cpp_base  result_type;
  static const bool is_reference=true;
  
  static const result_type&  convert(const T& t){return t.get_data();}
  static result_type& convert(T& t){return t.get_data_ref();}
};

template <class T>
typename Converter<T>::result_type
make_conversion(const T& t){return Converter<T>::convert(t);}


SPECIALIZE_CONVERTER(int)
SPECIALIZE_CONVERTER(unsigned)
SPECIALIZE_CONVERTER(bool)
SPECIALIZE_CONVERTER(double)
SPECIALIZE_CONVERTER(float)


#define SPECIALIZE_CONVERTER_ENUM(ENUM)     \
template <> struct Converter<ENUM>{         \
  static const bool is_reference=false;     \
  typedef ::CGAL:: ENUM result_type;        \
  static result_type convert(ENUM t)        \
  {return CGAL::enum_cast<CGAL:: ENUM>(t);} \
};


#ifndef SWIG
typedef  CGAL_SWIG::Triple<int,int,int> TRIPLE_INT;
SPECIALIZE_CONVERTER( TRIPLE_INT )
#endif


//TODO if need performance think about pointers
template <class P1,class P2>
struct Converter<std::pair<P1,P2> >{
  typedef std::pair<typename Converter<P1>::result_type,
                    typename Converter<P2>::result_type>           result_type;
  
  static const bool is_reference=false;
  
  static result_type convert(const std::pair<P1,P2>& t)
  {
    return std::make_pair(Converter<P1>::convert(t.first),
                          Converter<P2>::convert(t.second));
  }
};

template <class T1,class T2,class T3>
struct Converter< CGAL_SWIG::Triple<T1,T2,T3> >{
  typedef CGAL::Triple<  typename Converter<T1>::result_type,
                         typename Converter<T2>::result_type,    
                         typename Converter<T3>::result_type    >   result_type;
  
  static const bool is_reference=false;
  
  static result_type convert(const CGAL_SWIG::Triple<T1,T2,T3>& t){
    return CGAL::make_triple(Converter<T1>::convert(t.first),
                             Converter<T2>::convert(t.second),
                             Converter<T3>::convert(t.third));
  }
};


  //~ typename Triangulation::Cell_handle convert (const Cell_handle& c) {return c.get_data();}
  //~ typename Triangulation::Cell_handle& convert (Cell_handle& c) {return c.get_data_ref();}
  //~ typename Triangulation::Vertex_handle convert (const Vertex_handle& v) {return v.get_data();}
  //~ typename Triangulation::Vertex_handle& convert (Vertex_handle& v) {return v.get_data_ref();}
  //~ typename Triangulation::Facet convert(const DT3_Facet& f){return std::make_pair(convert(f.first),f.second);}
  //~ typename Triangulation::Edge convert (const DT3_Edge& e){return CGAL::make_tuple(convert(e.first),e.second,e.third);}
  //~ typename Triangulation::Point convert (const Point_3& p){return p.get_data();}
  //~ const int& convert (const int& i){return i;}
  //~ template <class T> const T& convert(const Reference_wrapper<T>& ref){return ref.object();}
  //~ template <class T> T& convert(Reference_wrapper<T>& ref){return ref.object_ref();}  
  


}//namespace internal

//Macro functions to ease the wrapping of member functions

#define FORWARD_CALL_0_PTR(RET,NAME) \
  RET NAME()\
  {return RET(this->data->NAME());}

#define FORWARD_CALL_0(RET,NAME) \
  RET NAME()\
  {return RET(this->data.NAME());}

#define FORWARD_CALL_1_PTR(RET,NAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c){\
    return RET(this->data->NAME(internal::Converter<IN_TYPE>::convert(c)));\
  }

#define FORWARD_CALL_1(RET,NAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE>::convert(c)));\
  }

#define FORWARD_CALL_2_PTR(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){\
    return RET(this->data->NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                                internal::Converter<IN_TYPE_2>::convert(c2)));\
  }

#define FORWARD_CALL_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2)));\
  }

#define FORWARD_CALL_3_PTR(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3){\
    return RET(this->data->NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                                internal::Converter<IN_TYPE_2>::convert(c2),\
                                internal::Converter<IN_TYPE_3>::convert(c3)));\
  }

#define FORWARD_CALL_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3)));\
  }

#define FORWARD_CALL_4_PTR(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2,const IN_TYPE_3& c3,const IN_TYPE_4& c4){\
    return RET(this->data->NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                                internal::Converter<IN_TYPE_2>::convert(c2),\
                                internal::Converter<IN_TYPE_3>::convert(c3),\
                                internal::Converter<IN_TYPE_4>::convert(c4)));\
  }

#define FORWARD_CALL_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4)));\
  }
  
#define FORWARD_CALL_5(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4),\
                               internal::Converter<IN_TYPE_5>::convert(c5)));\
  }

#define FORWARD_CALL_6(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5, const IN_TYPE_6& c6){\
    return RET(this->data.NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4),\
                               internal::Converter<IN_TYPE_5>::convert(c5),\
                               internal::Converter<IN_TYPE_6>::convert(c6)));\
  }

#endif //CGAL_SWIG_MACROS_H
