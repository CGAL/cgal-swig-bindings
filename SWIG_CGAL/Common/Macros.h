// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MACROS_H
#define SWIG_CGAL_MACROS_H

#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/JavaData.h>
#endif

#include <SWIG_CGAL/Common/triple.h>
#include <CGAL/utility.h>
#include <CGAL/assertions.h>
#include <CGAL/is_iterator.h>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/functional/hash.hpp>

//Functor for SWIG_CGAL_FORWARD_CALL_N

namespace internal{

#define SWIG_CGAL_SPECIALIZE_CONVERTER(T)                    \
template <> struct Converter<T>{                   \
  static const bool is_reference=true;             \
  typedef T result_type;                           \
  static const T& convert(const T& t){return t;}   \
};


template <class T>
struct Converter{
  typedef typename T::cpp_base  result_type;
  static const bool is_reference=true;
  
  static const result_type& convert(const T& t){return t.get_data();}
  static       result_type& convert(      T& t){return t.get_data();}
};

template <class T>
typename Converter<T>::result_type
make_conversion(const T& t){return Converter<T>::convert(t);}


SWIG_CGAL_SPECIALIZE_CONVERTER(int)
SWIG_CGAL_SPECIALIZE_CONVERTER(unsigned)
SWIG_CGAL_SPECIALIZE_CONVERTER(bool)
SWIG_CGAL_SPECIALIZE_CONVERTER(double)
SWIG_CGAL_SPECIALIZE_CONVERTER(float)
#ifdef SWIGJAVA
SWIG_CGAL_SPECIALIZE_CONVERTER(JavaData)
#endif


#define SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM_2(ENUM,NSPACE)     \
template <> struct Converter<ENUM>{                  \
  static const bool is_reference=false;              \
  typedef NSPACE ENUM result_type;                   \
  static result_type convert(ENUM t)                 \
  {return CGAL::enum_cast< NSPACE ENUM>(t);}         \
};

#define SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM(ENUM)     \
  SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM_2(ENUM,::CGAL::)


#ifndef SWIG
typedef  SWIG_CGAL::Triple<int,int,int> TRIPLE_INT;
SWIG_CGAL_SPECIALIZE_CONVERTER( TRIPLE_INT )
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
struct Converter< SWIG_CGAL::Triple<T1,T2,T3> >{
  typedef CGAL::Triple<  typename Converter<T1>::result_type,
                         typename Converter<T2>::result_type,    
                         typename Converter<T3>::result_type    >   result_type;
  
  static const bool is_reference=false;
  
  static result_type convert(const SWIG_CGAL::Triple<T1,T2,T3>& t){
    return CGAL::make_triple(Converter<T1>::convert(t.first),
                             Converter<T2>::convert(t.second),
                             Converter<T3>::convert(t.third));
  }
};

}//namespace internal

#define DEFINE_EQUALITY_OPERATORS(TYPE) \
bool operator==(TYPE& p) const { return get_data() == p.get_data(); } \
bool operator!=(TYPE& p) const { return get_data( )!= p.get_data(); }

#define DEFINE_COMPARISON_OPERATORS(TYPE) \
bool operator< (TYPE& p) const { return get_data() <  p.get_data(); } \
bool operator> (TYPE& p) const { return get_data() >  p.get_data(); } \
bool operator<=(TYPE& p) const { return get_data() <= p.get_data(); } \
bool operator>=(TYPE& p) const { return get_data() >= p.get_data(); } \
DEFINE_EQUALITY_OPERATORS(TYPE)


//hash function renamed to __hash__ in python
#define DEFINE_HASH_FUNCTION_FOR_HANDLE \
int hashCode() const { return (int) boost::hash_value(&(*data) ); }

template <class T, bool is_iterator=CGAL::is_iterator<T>::value >
struct SWIG_CGAL_Extract_data;


template <class T>
struct SWIG_CGAL_Extract_data<T,false>
{
  typedef T reference;
  reference operator()(T t){
    CGAL_static_assertion(boost::is_reference<T>::value);
    return t;
  }
};

template <class T>
struct SWIG_CGAL_Extract_data<T,true>
{
  typedef typename boost::remove_cv< typename boost::remove_reference<T>::type >::type I;
  typedef typename std::iterator_traits<I>::reference reference;
  reference operator()(I t){return *t;}
};


template <class T>
typename SWIG_CGAL_Extract_data<const T&>::reference
SWIG_CGAL_extract_data(const T& t)
{return SWIG_CGAL_Extract_data<const T&>() (t);}

template <class T>
typename SWIG_CGAL_Extract_data<T&>::reference
SWIG_CGAL_extract_data(T& t)
{return SWIG_CGAL_Extract_data<T&>() (t);}


//Macro functions to ease the wrapping of member functions

#define SWIG_CGAL_FORWARD_CALL_SCOPE_0(RET,NAME,INAME) \
  RET NAME()\
  {return RET(SWIG_CGAL_extract_data(this->get_data()).INAME());}

#define SWIG_CGAL_FORWARD_CALL_0(RET,NAME) \
  SWIG_CGAL_FORWARD_CALL_SCOPE_0(RET,NAME,NAME)

#define SWIG_CGAL_DECLARE_CALL_AND_REF_0(RET,NAME) \
  inline RET NAME();\
  inline void NAME(RET& ref);\

#define SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(RET,NAME,INAME) \
  SWIG_CGAL_FORWARD_CALL_SCOPE_0(RET,NAME,INAME) \
  void NAME(RET& ref)\
  {ref = RET(SWIG_CGAL_extract_data(this->get_data()).INAME());}

#define SWIG_CGAL_FORWARD_CALL_AND_REF_0(RET,NAME) \
  SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_0(RET,NAME,NAME)
//---------------------------------------------------------------------------
#define SWIG_CGAL_DECLARE_CALL_1(RET,NAME,IN_TYPE) \
  inline RET NAME(const IN_TYPE& c);

#define SWIG_CGAL_FORWARD_CALL_SCOPE_1(RET,NAME,INAME,IN_TYPE) \
  RET NAME(const IN_TYPE& c){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).INAME(internal::Converter<IN_TYPE>::convert(c)));\
  }
  
#define SWIG_CGAL_FORWARD_CALL_1(RET,NAME,IN_TYPE) \
  SWIG_CGAL_FORWARD_CALL_SCOPE_1(RET,NAME,NAME,IN_TYPE)


#define SWIG_CGAL_DECLARE_CALL_AND_REF_1(RET,NAME,IN_TYPE) \
  inline RET NAME(const IN_TYPE& c);\
  inline void NAME(const IN_TYPE& c,RET& ret);

#define SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(RET,NAME,INAME,IN_TYPE) \
  SWIG_CGAL_FORWARD_CALL_SCOPE_1(RET,NAME,INAME,IN_TYPE) \
  void NAME(const IN_TYPE& c,RET& ret){\
    ret = RET(SWIG_CGAL_extract_data(this->get_data()).INAME(internal::Converter<IN_TYPE>::convert(c)));\
  }
  
#define SWIG_CGAL_FORWARD_CALL_AND_REF_1(RET,NAME,IN_TYPE) \
  SWIG_CGAL_FORWARD_CALL_AND_REF_SCOPE_1(RET,NAME,NAME,IN_TYPE)
//---------------------------------------------------------------------------
#define SWIG_CGAL_FORWARD_CALL_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2)));\
  }
  
#define SWIG_CGAL_FORWARD_CALL_AND_REF_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  SWIG_CGAL_FORWARD_CALL_2(RET,NAME,IN_TYPE_1,IN_TYPE_2) \
  void NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, RET& ret){\
     ret = RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2)));\
  }
//---------------------------------------------------------------------------
#define SWIG_CGAL_FORWARD_CALL_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3)));\
  }
  
#define SWIG_CGAL_FORWARD_CALL_AND_REF_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  SWIG_CGAL_FORWARD_CALL_3(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3) \
  void NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3,RET& ret){\
     ret = RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3)));\
  }
//---------------------------------------------------------------------------
#define SWIG_CGAL_FORWARD_CALL_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4)));\
  }
  
#define SWIG_CGAL_FORWARD_CALL_AND_REF_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
    SWIG_CGAL_FORWARD_CALL_4(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4) \
  void NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4,RET& ret){\
     ret = RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4)));\
  }
//---------------------------------------------------------------------------  
#define SWIG_CGAL_FORWARD_CALL_5(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4),\
                               internal::Converter<IN_TYPE_5>::convert(c5)));\
  }
//---------------------------------------------------------------------------
#define SWIG_CGAL_FORWARD_CALL_6(RET,NAME,IN_TYPE_1,IN_TYPE_2,IN_TYPE_3,IN_TYPE_4,IN_TYPE_5,IN_TYPE_6) \
  RET NAME(const IN_TYPE_1& c1,const IN_TYPE_2& c2, const IN_TYPE_3& c3, const IN_TYPE_4& c4, const IN_TYPE_5& c5, const IN_TYPE_6& c6){\
    return RET(SWIG_CGAL_extract_data(this->get_data()).NAME(internal::Converter<IN_TYPE_1>::convert(c1),\
                               internal::Converter<IN_TYPE_2>::convert(c2),\
                               internal::Converter<IN_TYPE_3>::convert(c3),\
                               internal::Converter<IN_TYPE_4>::convert(c4),\
                               internal::Converter<IN_TYPE_5>::convert(c5),\
                               internal::Converter<IN_TYPE_6>::convert(c6)));\
  }

#endif //SWIG_CGAL_MACROS_H
