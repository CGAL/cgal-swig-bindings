// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_2_CRITERIA_H
#define SWIG_CGAL_MESH_2_CRITERIA_H

#include <SWIG_CGAL/Common/Macros.h>

enum Face_badness { NOT_BAD, BAD, IMPERATIVELY_BAD };

namespace internal{
  SWIG_CGAL_SPECIALIZE_CONVERTER_ENUM_2(Face_badness,::CGAL::Mesh_2::)
}//namespace internal


template <class Cpp>
class Criteria_wrapper{
  Cpp data;
public:
  #ifndef SWIG
  typedef Cpp cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Criteria_wrapper(const cpp_base& base):data(base){}
  #endif
  Criteria_wrapper( double b , double S ):data(b,S){}
  Criteria_wrapper( double b ):data(b){}
  Criteria_wrapper(){}
//Deep copy
  typedef Criteria_wrapper<Cpp> Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/JavaData.h>

template <class Caller,class Face_handle_,class Quality_>
class Java_Is_bad_wrapper
{
  Caller caller;
  typedef Java_Is_bad_wrapper<Caller,Face_handle_,Quality_> Self;
  //disable deep copy (undelying objects cannot be copied)
  Self deepcopy();
  void deepcopy(const Self&);
public:
  typedef typename Face_handle_::cpp_base  Face_handle;
  typedef typename Quality_::cpp_base      Quality;

  Java_Is_bad_wrapper(Caller& call):caller(call){}
  //We need the default constructor because of a bug in Keonig lookup in SWIG cxx generated file
  Java_Is_bad_wrapper(){}
    
  CGAL::Mesh_2::Face_badness operator()(const Face_handle& f,Quality& q) const {
    return caller.run_2(f,q);
  }
  CGAL::Mesh_2::Face_badness operator()(Quality& q) const {return caller.run_1(q);}
};

template <class Is_bad_wrapper,class Caller>
class Java_criteria_wrapper{
  Is_bad_wrapper is_bad;
  typedef Java_criteria_wrapper<Is_bad_wrapper,Caller> Self;
  //disable deep copy (undelying objects cannot be copied)
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  typedef typename Is_bad_wrapper::Quality      Quality;
  typedef typename Is_bad_wrapper::Face_handle  Face_handle;
  typedef Is_bad_wrapper                        Is_bad;  

  #ifndef SWIG
  typedef Java_criteria_wrapper<Is_bad_wrapper,Caller> cpp_base;
  const cpp_base& get_data() const {return *this;}
        cpp_base& get_data()       {return *this;}
  const Is_bad& is_bad_object() const {return is_bad;}
  #endif
  
  //We need the default constructor because of a bug in Keonig lookup in SWIG cxx generated file
  Java_criteria_wrapper(){}
  Java_criteria_wrapper(Caller& call):is_bad(call){}
};

#endif

#endif //SWIG_CGAL_MESH_2_CRITERIA_H
