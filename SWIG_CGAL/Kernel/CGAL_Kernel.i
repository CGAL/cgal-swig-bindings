// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Kernel

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Kernel");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Kernel failed to load. \n" + e);
      throw e;
    }
  }
%}


//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Common/Iterator.h"

//%typemap(javapackage) Point_3 "CGAL.Kernel"

#ifdef SWIGJAVA
//method getCPtr and constructor from (long,bool) should be public
//to be used in other packages cf. file java.swg
SWIG_JAVABODY_METHODS(public,public,Point_2)
SWIG_JAVABODY_METHODS(public,public,Weighted_point_2)
SWIG_JAVABODY_METHODS(public,public,Segment_2)
SWIG_JAVABODY_METHODS(public,public,Triangle_2)
SWIG_JAVABODY_METHODS(public,public,Ray_2)
SWIG_JAVABODY_METHODS(public,public,Direction_2)
SWIG_JAVABODY_METHODS(public,public,Line_2)
SWIG_JAVABODY_METHODS(public,public,Vector_2)
SWIG_JAVABODY_METHODS(public,public,Point_3)
SWIG_JAVABODY_METHODS(public,public,Weighted_point_3)
SWIG_JAVABODY_METHODS(public,public,Plane_3)
SWIG_JAVABODY_METHODS(public,public,Segment_3)
SWIG_JAVABODY_METHODS(public,public,Triangle_3)
SWIG_JAVABODY_METHODS(public,public,Tetrahedron_3)
SWIG_JAVABODY_METHODS(public,public,Line_3)
SWIG_JAVABODY_METHODS(public,public,Sphere_3)
SWIG_JAVABODY_METHODS(public,public,Ray_3)
SWIG_JAVABODY_METHODS(public,public,Direction_3)
SWIG_JAVABODY_METHODS(public,public,Vector_3)
SWIG_JAVABODY_METHODS(public,public,CGAL_Object)
SWIG_JAVABODY_METHODS(public,public,Polygon_2)
#endif

%pragma(java)          jniclassimports=%{import java.util.Iterator; import java.util.Collection;%}
%typemap(javaimports)  Polygon_2 %{import java.util.Iterator;%}
%pragma(java) moduleimports    =%{import java.util.Iterator;%}
//include files
%{
  #include <SWIG_CGAL/Kernel/Point_2.h>
  
  #include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
  typedef std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > Point_range_2;  
  
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
  #include <SWIG_CGAL/Kernel/CGAL_Object.h>
  #include <SWIG_CGAL/Kernel/global_functions.h>
  #include <SWIG_CGAL/Kernel/enum.h>
  #include <SWIG_CGAL/Kernel/Polygon_2.h>
  #include <SWIG_CGAL/Common/Iterator.h>
%}

//typemaps for Polygon_2
SWIG_CGAL_input_iterator_typemap_in(Point_range_2,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Polygon_2::Polygon_2)
#endif

//definitions
%include "SWIG_CGAL/Kernel/Point_2.h"
%include "SWIG_CGAL/Kernel/Weighted_point_2.h"
%include "SWIG_CGAL/Kernel/Segment_2_def.h"
%include "SWIG_CGAL/Kernel/Triangle_2.h"
%include "SWIG_CGAL/Kernel/Ray_2_def.h"
%include "SWIG_CGAL/Kernel/Direction_2_def.h"
%include "SWIG_CGAL/Kernel/Line_2_def.h"
%include "SWIG_CGAL/Kernel/Vector_2_def.h"
%include "SWIG_CGAL/Kernel/Point_3.h"
%include "SWIG_CGAL/Kernel/Weighted_point_3.h"
%include "SWIG_CGAL/Kernel/Plane_3_def.h"
%include "SWIG_CGAL/Kernel/Segment_3_def.h"
%include "SWIG_CGAL/Kernel/Line_3_def.h"
%include "SWIG_CGAL/Kernel/Sphere_3.h"
%include "SWIG_CGAL/Kernel/Triangle_3.h"
%include "SWIG_CGAL/Kernel/Ray_3_def.h"
%include "SWIG_CGAL/Kernel/Direction_3_def.h"
%include "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%include "SWIG_CGAL/Kernel/Vector_3_def.h"
%include "SWIG_CGAL/Kernel/CGAL_Object.h"
%include "SWIG_CGAL/Kernel/enum.h"
%include "SWIG_CGAL/Kernel/Polygon_2.h"
%include "SWIG_CGAL/Common/global_function_macros.h"
%include "SWIG_CGAL/Kernel/global_function_signatures.h"

//simple types
%include "SWIG_CGAL/Kernel/Reference_wrappers.i"

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

