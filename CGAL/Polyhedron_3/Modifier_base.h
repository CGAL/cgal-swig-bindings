#ifndef CGAL_SWIG_POLYHEDRON_3_MODIFIER_BASE_H
#define CGAL_SWIG_POLYHEDRON_3_MODIFIER_BASE_H

#include <CGAL/Modifier_base.h>

template <class Polyhedron_base>
class Modifier_base{
  typedef typename Polyhedron_base::HalfedgeDS HDS;  
  CGAL::Modifier_base<HDS>* data;
public:
  typedef CGAL::Modifier_base<HDS> cpp_base;

  Modifier_base(void* ptr):data(static_cast<cpp_base*>(ptr)){}
  cpp_base&  get_data(){return *data;}
  //the storage of modifier is handled by this class
};

template <class Polyhedron_base,class Cpp_modifier>
class Modifier_wrapper{
  Cpp_modifier modifier;
public:
  Modifier_base<Polyhedron_base> get_modifier(){
    return Modifier_base<Polyhedron_base>( static_cast<void*>(&modifier) );
  }
};


#endif //CGAL_SWIG_POLYHEDRON_3_MODIFIER_BASE_H
