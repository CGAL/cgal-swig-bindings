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
      System.exit(1);
    }
  }
%}


//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif


%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Common/Input_iterator.h"

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
%}

//typemaps for Polygon_2
Typemap_for_Input_iterator(Point_range_2,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
#ifdef SWIGPYTHON
Typemap_for_Input_iterator_additional_function(Polygon_2::Polygon_2)
#endif

//definitions
%include "SWIG_CGAL/Kernel/Point_2.h"
%include "SWIG_CGAL/Kernel/Weighted_point_2.h"
%include "SWIG_CGAL/Kernel/Segment_2.h"
%include "SWIG_CGAL/Kernel/Triangle_2.h"
%include "SWIG_CGAL/Kernel/Ray_2.h"
%include "SWIG_CGAL/Kernel/Direction_2.h"
%include "SWIG_CGAL/Kernel/Line_2.h"
%include "SWIG_CGAL/Kernel/Vector_2.h"
%include "SWIG_CGAL/Kernel/Point_3.h"
%include "SWIG_CGAL/Kernel/Weighted_point_3.h"
%include "SWIG_CGAL/Kernel/Plane_3.h"
%include "SWIG_CGAL/Kernel/Segment_3.h"
%include "SWIG_CGAL/Kernel/Line_3.h"
%include "SWIG_CGAL/Kernel/Sphere_3.h"
%include "SWIG_CGAL/Kernel/Triangle_3.h"
%include "SWIG_CGAL/Kernel/Ray_3.h"
%include "SWIG_CGAL/Kernel/Direction_3.h"
%include "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%include "SWIG_CGAL/Kernel/Vector_3.h"
%include "SWIG_CGAL/Kernel/CGAL_Object.h"
%include "SWIG_CGAL/Kernel/enum.h"
%include "SWIG_CGAL/Kernel/Polygon_2.h"
%include "SWIG_CGAL/Common/global_function_macros.h"
%include "SWIG_CGAL/Kernel/global_function_signatures.h"



%extend Polygon_2{
  void insert( int i, Point_range_2 range){
    $self->get_data_ref().insert(boost::next($self->get_data().vertices_begin(),i),range.first,range.second);
  }
  Polygon_2(Point_range_2 range){return new Polygon_2(Polygon_2::cpp_base(range.first,range.second));}
}

//Iterators
Iterator_for_java(CGAL_Vertex_iterator,Point_2,)
%template(Polygon_2_Vertex_iterator) CGAL_Vertex_iterator< Polygon_2::cpp_base,Point_2 >;

Iterator_for_java(CGAL_Edge_const_iterator,Segment_2,)
%template(Polygon_2_Edge_const_iterator) CGAL_Edge_const_iterator< Polygon_2::cpp_base,Segment_2 >;

Iterator_for_java(CGAL_Vertex_circulator,Point_2,)
%template(Polygon_2_Vertex_circulator) CGAL_Vertex_circulator< Polygon_2::cpp_base,Point_2 >;

Iterator_for_java(CGAL_Edge_const_circulator,Segment_2,)
%template(Polygon_2_Edge_const_circulator) CGAL_Edge_const_circulator< Polygon_2::cpp_base,Segment_2 >;


//global function that needs to know about Point_range_2
Bounded_side bounded_side_2(Point_range_2 range,const Point_2& p);
%{
  #include <CGAL/Polygon_2_algorithms.h>
  Bounded_side bounded_side_2(Point_range_2 range,const Point_2& p){
    return Bounded_side(CGAL::bounded_side_2(range.first,range.second,p.get_data(),EPIC_Kernel()));
  }
%}

