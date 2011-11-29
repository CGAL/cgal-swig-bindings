// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POLYHEDRON_3_MODIFIER_BASE_H
#define SWIG_CGAL_POLYHEDRON_3_MODIFIER_BASE_H

#include <CGAL/Modifier_base.h>

template <class Polyhedron_base>
class Modifier_base{
  typedef typename Polyhedron_base::HalfedgeDS HDS;  
  CGAL::Modifier_base<HDS>* data;
  typedef Modifier_base<Polyhedron_base> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  #ifndef SWIG
  typedef CGAL::Modifier_base<HDS> cpp_base;
  cpp_base&  get_data(){return *data;}
  
  Modifier_base(void* ptr):data(static_cast<cpp_base*>(ptr)){}
  //the storage of modifier is handled by this class
  #endif    
  Modifier_base():data(NULL){} //should not be used (only to not exposed void* to SWIG)
};

template <class Polyhedron_base,class Cpp_modifier>
class Modifier_wrapper{
  Cpp_modifier modifier;
  typedef Modifier_wrapper<Polyhedron_base,Cpp_modifier> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  Modifier_base<Polyhedron_base> get_modifier(){
    return Modifier_base<Polyhedron_base>( static_cast<void*>(&modifier) );
  }
  #ifndef SWIG
  Cpp_modifier& get_modifier_cpp_base() {return modifier;}
  #endif
};


#endif //SWIG_CGAL_POLYHEDRON_3_MODIFIER_BASE_H
