#ifndef CGAL_SWIG_INPUT_ITERATOR_H
#define CGAL_SWIG_INPUT_ITERATOR_H

#include "triple.h"

template <class T>
struct Iterator_helper{
  template <class Ti>
  static T convert(const Ti& i){
    return T(i);
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


#ifdef SWIGPYTHON
#define DECLARE_ITERATOR_CLASS(NAME,RETURN)                    \
template<class T>                                              \
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
  CGAL_##NAME<T> __iter__(){return *this;}                     \
  RETURN next()                                                \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<RETURN>::convert ( (cur++) );     \
    throw 1;                                                   \
    return Iterator_helper<RETURN>::default_value();           \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};       
#else
#define DECLARE_ITERATOR_CLASS(NAME,RETURN)                    \
template<class T>                                              \
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
  RETURN next()                                                \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<RETURN>::convert ( (cur++) );     \
    return Iterator_helper<RETURN>::default_value();           \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};
#endif

#endif //CGAL_SWIG_INPUT_ITERATOR_H
