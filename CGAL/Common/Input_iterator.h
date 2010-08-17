#ifndef CGAL_SWIG_INPUT_ITERATOR_H
#define CGAL_SWIG_INPUT_ITERATOR_H

#include "triple.h"

#ifndef SWIG  
template <class T>
struct Iterator_helper{
  
  template <class Iterator>
  static T convert(const Iterator& it,typename boost::enable_if< 
                                                      boost::is_same<
                                                        typename T::cpp_base,
                                                        typename std::iterator_traits<Iterator>::value_type
                                                      >
                                              >::type* =0)
  {
    return T(*it);
  }

  template <class Ti>
  static T convert(const Ti& i,typename boost::enable_if< 
                                    boost::is_same< 
                                      boost::false_type,
                                      typename boost::is_same<
                                        typename T::cpp_base,
                                        typename std::iterator_traits<Ti>::value_type
                                      >::type
                                    >
                                  >::type* =0)
  {
    return T(i);
  }
  

  static T
  default_value(){return T();}
};

template<class T1>
struct Iterator_helper<std::pair<T1,int> >{
  template <class T>
  static std::pair<T1,int> convert(const T& i){
    return std::pair<T1,int>(T1(i->first),i->second);
  }
  
  static std::pair<T1,int>
  default_value(){return std::pair<T1,int>(T1(NULL),-1);}
};

template<class T1>
struct Iterator_helper<CGAL_SWIG::Triple<T1,int,int> >{
  template <class T>
  static CGAL_SWIG::Triple<T1,int,int> convert(const T& i){
    return CGAL_SWIG::Triple<T1,int,int>(T1(i->first),i->second,i->third);
  }
  
  static CGAL_SWIG::Triple<T1,int,int>
  default_value(){return CGAL_SWIG::Triple<T1,int,int>(T1(NULL),-1,-1);}
};

template<>
struct Iterator_helper<double>{
  template <class T>
  static double convert(const T& i){  return *i; }
  static double default_value(){return 0.;}
};


#endif

#ifdef SWIGPYTHON

#include "../Python/exceptions.h"

#define DECLARE_ITERATOR_CLASS(NAME)                           \
template<class T,class R>                                      \
class CGAL_##NAME{                                             \
  typename T::NAME cur;                                        \
  typename T::NAME end;                                        \
public:                                                        \
                                                               \
  CGAL_##NAME(                                                 \
    typename T::NAME cur_,                                     \
    typename T::NAME end_                                      \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  CGAL_##NAME<T,R> __iter__(){return *this;}                   \
  R next()                                                     \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<R>::convert ( (cur++) );          \
    throw Stop_iteration();                                    \
    return Iterator_helper<R>::default_value();                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};       
#else
#define DECLARE_ITERATOR_CLASS(NAME)                           \
template<class T,class R>                                      \
class CGAL_##NAME{                                             \
  typename T::NAME cur;                                        \
  typename T::NAME end;                                        \
public:                                                        \
                                                               \
  CGAL_##NAME(                                                 \
    typename T::NAME cur_,                                     \
    typename T::NAME end_                                      \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  R next()                                                     \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<R>::convert ( (cur++) );          \
    return Iterator_helper<R>::default_value();                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};
#endif



#define DECLARE_CIRCULATOR_CLASS(NAME)                         \
template<class T,class R>                                      \
class CGAL_##NAME{                                             \
  typename T::NAME cur;                                        \
public:                                                        \
  typedef typename T::NAME cpp_base;                           \
  CGAL_##NAME( typename T::NAME cur_):cur(cur_){}              \
    CGAL_##NAME<T,R> __iter__(){return *this;}                 \
  R next() {                                                   \
    return Iterator_helper<R>::convert ( (cur++) );            \
  }                                                            \
  R prev() {                                                   \
    return Iterator_helper<R>::convert ( (cur--) );            \
  }                                                            \
  bool hasNext(){return true; }                                \
};

#endif //CGAL_SWIG_INPUT_ITERATOR_H
