#ifndef CGAL_SWIG_INPUT_ITERATOR_H
#define CGAL_SWIG_INPUT_ITERATOR_H

#include "triple.h"
#include "../Kernel/Point_3.h"
#include "../Kernel/Point_2.h"
#include "../Kernel/Plane_3.h"

template <class T>
struct Iterator_helper{
  //~ template <class Ti,bool is_const>
  //~ static T convert(const CGAL::internal::CC_iterator<Ti,is_const>& i){
    //~ return T(i);
  //~ }

  //~ template <class Iterator>
  //~ static T convert(Iterator it){
    //~ return T(*it);
  //~ }

  template <class Ti>
  static T convert(const Ti& i){
    return T(i);
  }
  
  //TODO: find another fix
  template <class Ti>
  static T convert(const typename std::_List_iterator<Ti> it){
    return T(*it);
  }

  static T
  default_value(){return T(NULL);}
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

template <>
struct Iterator_helper<Point_3>{
  template <class Ti>
  static Point_3 convert(const Ti& i){
    return Point_3(*i);
  }
  
  static Point_3
  default_value(){return Point_3();}
};

template <>
struct Iterator_helper<Point_2>{
  template <class Ti>
  static Point_2 convert(const Ti& i){
    return Point_2(*i);
  }
  
  static Point_2
  default_value(){return Point_2();}
};

template <>
struct Iterator_helper<Plane_3>{
  template <class Ti>
  static Plane_3 convert(const Ti& i){
    return Plane_3(*i);
  }
  
  static Plane_3
  default_value(){return Plane_3();}
};

#ifdef SWIGPYTHON
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
  CGAL_##NAME<T,R> __iter__(){return *this;}                     \
  R next()                                                     \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<R>::convert ( (cur++) );          \
    throw 1;                                                   \
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
