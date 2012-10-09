// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Kernel

%include "SWIG_CGAL/common.i"
Decl_void_type()


SWIG_CGAL_add_java_loadLibrary(CGAL_Kernel)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Common/Iterator.h"

//%typemap(javapackage) Point_3 "CGAL.Kernel"

%pragma(java)          jniclassimports=%{import java.util.Iterator; import java.util.Collection;%}
%typemap(javaimports)  Polygon_2 %{import java.util.Iterator;%}
%pragma(java) moduleimports    =%{import java.util.Iterator;%}
//include files
%{
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Common/Input_iterator_wrapper.h>

  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > Point_range_2;  
  #else
  typedef Generic_input_iterator<Point_2> Point_range_2;
  #endif
  
  #include <SWIG_CGAL/Kernel/Weighted_point_2.h>
  #include <SWIG_CGAL/Kernel/Segment_2.h>
  #include <SWIG_CGAL/Kernel/Triangle_2.h>
  #include <SWIG_CGAL/Kernel/Ray_2.h>
  #include <SWIG_CGAL/Kernel/Direction_2.h>
  #include <SWIG_CGAL/Kernel/Line_2.h>
  #include <SWIG_CGAL/Kernel/Vector_2.h>
  #include <SWIG_CGAL/Kernel/Point_3.h>
  #include <SWIG_CGAL/Kernel/Weighted_point_3.h>
  #include <SWIG_CGAL/Kernel/Plane_3.h>
  #include <SWIG_CGAL/Kernel/Segment_3.h>
  #include <SWIG_CGAL/Kernel/Triangle_3.h>
  #include <SWIG_CGAL/Kernel/Tetrahedron_3.h>
  #include <SWIG_CGAL/Kernel/Line_3.h>
  #include <SWIG_CGAL/Kernel/Sphere_3.h>
  #include <SWIG_CGAL/Kernel/Ray_3.h>
  #include <SWIG_CGAL/Kernel/Direction_3.h>
  #include <SWIG_CGAL/Kernel/Vector_3.h>
  #include <SWIG_CGAL/Kernel/Object.h>
  #include <SWIG_CGAL/Common/global_function_macros.h>
  #include <SWIG_CGAL/Kernel/global_functions.h>
  #include <SWIG_CGAL/Kernel/enum.h>
  #include <SWIG_CGAL/Kernel/Polygon_2.h>
  #include <SWIG_CGAL/Kernel/Origin.h>
  #include <SWIG_CGAL/Kernel/Iso_rectangle_2.h>
  #include <SWIG_CGAL/Kernel/Iso_cuboid_3.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}

//typemaps for Polygon_2
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
SWIG_CGAL_input_iterator_typemap_in(Point_range_2,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Polygon_2::Polygon_2)
#endif
#else
%include "SWIG_CGAL/Common/Input_iterator_wrapper.h"
%define Point_range_2 Generic_input_iterator<Point_2> %enddef
%template(Point_2_input_iterator) Generic_input_iterator<Point_2>;
%template(Point_3_input_iterator) Generic_input_iterator<Point_3>;
%template(Weighted_point_2_input_iterator) Generic_input_iterator<Weighted_point_2>;
%template(Weighted_point_3_input_iterator) Generic_input_iterator<Weighted_point_3>;
%template(Triangle_3_input_iterator) Generic_input_iterator<Triangle_3>;
%template(Segment_3_input_iterator) Generic_input_iterator<Segment_3>;
#endif

//definitions
%include "SWIG_CGAL/Kernel/Point_2_decl.h"
%include "SWIG_CGAL/Kernel/Weighted_point_2.h"
%include "SWIG_CGAL/Kernel/Segment_2_decl.h"
%include "SWIG_CGAL/Kernel/Triangle_2.h"
%include "SWIG_CGAL/Kernel/Ray_2_decl.h"
%include "SWIG_CGAL/Kernel/Direction_2_decl.h"
%include "SWIG_CGAL/Kernel/Line_2_decl.h"
%include "SWIG_CGAL/Kernel/Vector_2_decl.h"
%include "SWIG_CGAL/Kernel/Point_3_decl.h"
%include "SWIG_CGAL/Kernel/Weighted_point_3.h"
%include "SWIG_CGAL/Kernel/Plane_3_decl.h"
%include "SWIG_CGAL/Kernel/Segment_3_decl.h"
%include "SWIG_CGAL/Kernel/Line_3_decl.h"
%include "SWIG_CGAL/Kernel/Sphere_3.h"
%include "SWIG_CGAL/Kernel/Triangle_3.h"
%include "SWIG_CGAL/Kernel/Ray_3_decl.h"
%include "SWIG_CGAL/Kernel/Direction_3_decl.h"
%include "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%include "SWIG_CGAL/Kernel/Vector_3_decl.h"
#ifdef SWIG_CGAL_Kernel_MODULE
%include "SWIG_CGAL/Common/Object.i"
#endif
%include "SWIG_CGAL/Kernel/enum.h"
%include "SWIG_CGAL/Kernel/Polygon_2.h"
%include "SWIG_CGAL/Common/global_function_macros.h"
%include "SWIG_CGAL/Kernel/global_function_signatures.h"
%include "SWIG_CGAL/Kernel/Origin.h"
%include "SWIG_CGAL/Kernel/Iso_rectangle_2.h"
%include "SWIG_CGAL/Kernel/Iso_cuboid_3.h"


const Origin           ORIGIN;
const Null_vector      NULL_VECTOR;
%{
const Origin      ORIGIN      = Origin();
const Null_vector NULL_VECTOR = Null_vector();
%}

//simple types
%include "SWIG_CGAL/Kernel/Reference_wrappers.i"

#ifdef SWIGPYTHON
//support operator*(double,Vector_d)
%pythoncode %{
Vector_2.__rmul__ = Vector_2.__mul__
Vector_3.__rmul__ = Vector_3.__mul__
%}
#endif

//we need to extend the Polygon_2 class in the .i because some function are target language dependant
%extend Polygon_2{
  void insert( int i, Point_range_2 range){
    $self->get_data().insert(boost::next($self->get_data().vertices_begin(),i),SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));
  }
  Polygon_2(Point_range_2 range){return new Polygon_2(Polygon_2::cpp_base(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)));}

  SWIG_CGAL_Iterator<Polygon_2::cpp_base::Vertex_iterator,Point_2>   vertices()   {return SWIG_CGAL_Iterator<Polygon_2::cpp_base::Vertex_iterator,Point_2>($self->get_data().vertices_begin(),$self->get_data().vertices_end());}
  SWIG_CGAL_Iterator<Polygon_2::cpp_base::Edge_const_iterator,Segment_2>  edges()      {return SWIG_CGAL_Iterator<Polygon_2::cpp_base::Edge_const_iterator,Segment_2>($self->get_data().edges_begin(),$self->get_data().edges_end());}
  SWIG_CGAL_Circulator<Polygon_2::cpp_base::Vertex_circulator,Point_2>        vertices_circulator()  {return SWIG_CGAL_Circulator<Polygon_2::cpp_base::Vertex_circulator,Point_2>($self->get_data().vertices_circulator());}
  SWIG_CGAL_Circulator<Polygon_2::cpp_base::Edge_const_circulator,Segment_2>  edges_circulator()     {return SWIG_CGAL_Circulator<Polygon_2::cpp_base::Edge_const_circulator,Segment_2>($self->get_data().edges_circulator());}  
}

//Iterators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_2,)
%template(Polygon_2_Vertex_iterator) SWIG_CGAL_Iterator< Polygon_2::cpp_base::Vertex_iterator,Point_2 >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Segment_2,)
%template(Polygon_2_Edge_const_iterator) SWIG_CGAL_Iterator< Polygon_2::cpp_base::Edge_const_iterator,Segment_2 >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Point_2,)
%template(Polygon_2_Vertex_circulator) SWIG_CGAL_Circulator< Polygon_2::cpp_base::Vertex_circulator,Point_2 >;

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator,Segment_2,)
%template(Polygon_2_Edge_const_circulator) SWIG_CGAL_Circulator< Polygon_2::cpp_base::Edge_const_circulator,Segment_2 >;


//global function that needs to know about Point_range_2
Bounded_side bounded_side_2(Point_range_2 range,const Point_2& p);
%{
  #include <CGAL/Polygon_2_algorithms.h>
  Bounded_side bounded_side_2(Point_range_2 range,const Point_2& p){
    return Bounded_side(CGAL::bounded_side_2(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),p.get_data(),EPIC_Kernel()));
  }
%}

