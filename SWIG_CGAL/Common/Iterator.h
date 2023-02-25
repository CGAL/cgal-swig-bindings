// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_ITERATOR_H
#define SWIG_CGAL_COMMON_ITERATOR_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/triple.h>
#include <type_traits>

#ifndef SWIG
template <class T>
struct Iterator_helper{

  template <class Iterator>
  static T convert(const Iterator& it,typename std::enable_if<
                                                      std::is_same<
                                                        typename internal::Converter<T>::result_type,
                                                        typename std::iterator_traits<Iterator>::value_type
                                                      >::value
                                              >::type* =0)
  {
    return T(*it);
  }

  template <class Ti>
  static T convert(const Ti& i,typename std::enable_if<
                                      !std::is_same<
                                        typename internal::Converter<T>::result_type,
                                        typename std::iterator_traits<Ti>::value_type
                                      >::value
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
  default_value(){return std::pair<T1,int>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<std::pair<T1,double> >{
  template <class T>
  static std::pair<T1,double> convert(const T& i){
    return std::pair<T1,double>(T1(i->first),i->second);
  }
  
  static std::pair<T1,double>
  default_value(){return std::pair<T1,double>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<SWIG_CGAL::Triple<T1,int,int> >{
  template <class T>
  static SWIG_CGAL::Triple<T1,int,int> convert(const T& i){
    return SWIG_CGAL::Triple<T1,int,int>(T1(i->first),i->second,i->third);
  }
  
  static SWIG_CGAL::Triple<T1,int,int>
  default_value(){return SWIG_CGAL::Triple<T1,int,int>(T1(),-1,-1);}
};

template<>
struct Iterator_helper<double>{
  template <class T>
  static double convert(const T& i){  return *i; }
  static double default_value(){return 0.;}
};

template<>
struct Iterator_helper<int>{
  template <class T>
  static int convert(const T& i){  return *i; }
  static int default_value(){return -1;}
};

#endif


#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/exceptions.h>
#endif

template<class Cpp_iterator,class Value_type>
class SWIG_CGAL_Iterator{
  Cpp_iterator cur;
  Cpp_iterator end;
public:
  typedef SWIG_CGAL_Iterator<Cpp_iterator, Value_type> Self;

  SWIG_CGAL_Iterator(){}

  #ifndef SWIG
  SWIG_CGAL_Iterator(
    Cpp_iterator cur_,
    Cpp_iterator end_
  ):cur(cur_),end(end_){}

  Cpp_iterator get_cur() const { return cur; }
  Cpp_iterator get_end() const { return end; }
  #endif
    
  #ifdef SWIGPYTHON
  SWIG_CGAL_Iterator<Cpp_iterator,Value_type> __iter__(){return *this;}

  Value_type next()
  {
    if (cur!=end)
      return Iterator_helper<Value_type>::convert ( (cur++) );
    throw Stop_iteration();
    return Iterator_helper<Value_type>::default_value();
  }

  Value_type __next__()
  {
    return next();
  }

  #else

  #ifdef SWIGJAVA
  Value_type slow_next()
  #else
  Value_type next()
  #endif  
  {
    if (cur!=end)
      return Iterator_helper<Value_type>::convert ( (cur++) );
    return Iterator_helper<Value_type>::default_value();
  }
  #endif //SWIGPYTHON
  
  void next(Value_type& r)
  {
    if (cur!=end)
      r=Iterator_helper<Value_type>::convert ( (cur++) );
    #ifdef SWIGPYTHON
    throw Stop_iteration();
    #endif
  }

  Self deepcopy() const {return Self(cur, end);}
  void deepcopy(const Self& other){cur=other.cur; end=other.end;}

  bool hasNext(){
    return cur!=end;
  }

  bool operator==(const Self& p) const { return cur==p.cur; }
  bool operator!=(const Self& p) const { return cur!=p.cur; }
};

template<class Cpp_circulator,class Value_type>
class SWIG_CGAL_Circulator{
  Cpp_circulator cur;
public:
  typedef SWIG_CGAL_Circulator<Cpp_circulator,Value_type> Self;
  SWIG_CGAL_Circulator(){}
  #ifndef SWIG
  SWIG_CGAL_Circulator( Cpp_circulator cur_):cur(cur_){}
  #endif
  
  #ifdef SWIGPYTHON
  SWIG_CGAL_Circulator<Cpp_circulator,Value_type> __iter__(){return *this;}
  #endif

  #ifdef SWIGJAVA
  Value_type slow_next()
  #else
  Value_type next()
  #endif
  {
    return Iterator_helper<Value_type>::convert ( (cur++) );
  }
  
  #ifdef SWIGJAVA
  void next(Value_type& r)
  {
    r = Iterator_helper<Value_type>::convert ( (cur++) );
  }
  #endif
  
  Self deepcopy() const {return Self(cur);}
  void deepcopy(const Self& other){cur=other.cur;}

  Value_type prev() {
    return Iterator_helper<Value_type>::convert ( (cur--) );
  }
  
  bool hasNext(){return cur!=Cpp_circulator();}

  bool operator==(const Self& p) const { return cur==p.cur; }
  bool operator!=(const Self& p) const { return cur!=p.cur; }
};



#endif //SWIG_CGAL_COMMON_ITERATOR_H
