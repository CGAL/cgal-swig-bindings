// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SURFACE_MESH_DETAILS_H
#define SWIG_CGAL_SURFACE_MESH_DETAILS_H

#include <SWIG_CGAL/Kernel/Sphere_3.h>

enum Surface_mesher_tag {MANIFOLD_TAG,MANIFOLD_WITH_BOUNDARY_TAG,NON_MANIFOLD_TAG};

template <class Criteria>
class Surface_mesh_criteria_3_wrapper
{
  Criteria data;
  typedef Surface_mesh_criteria_3_wrapper<Criteria> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Criteria cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
  Surface_mesh_criteria_3_wrapper( double angle_bound, double radius_bound, double distance_bound):data(angle_bound,radius_bound,distance_bound){}
  
};

template <class Cpp_base>
class Gray_level_image_3_wrapper
{
  Cpp_base data;
  typedef Gray_level_image_3_wrapper<Cpp_base> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
  Gray_level_image_3_wrapper(const std::string& s, double iso_value):data(s.c_str(),iso_value){}
};

template<class Cpp_base,class Function>
class Implicit_surface_3_wrapper{
  Cpp_base data;
  typedef Implicit_surface_3_wrapper<Cpp_base,Function> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  
  Implicit_surface_3_wrapper(const Function& f,const Sphere_3& sphere, double error):data(f.get_data(),sphere.get_data(),error){}
  Implicit_surface_3_wrapper(const Function& f,const Sphere_3& sphere):data(f.get_data(),sphere.get_data()){}
};

#endif //SWIG_CGAL_SURFACE_MESH_DETAILS_H
