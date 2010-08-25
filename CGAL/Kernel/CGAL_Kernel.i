%module CGAL_Kernel

//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

%import  "../Common/Macros.h"
%include "../common.i"

//%typemap(javapackage) Point_3 "CGAL.Kernel"

#ifdef SWIGJAVA
//method getCPtr and constructor from (long,bool) should be public
//to be used in other packages cf. file java.swg
SWIG_JAVABODY_METHODS(public,public,Point_2)
SWIG_JAVABODY_METHODS(public,public,Weighted_point_2)
SWIG_JAVABODY_METHODS(public,public,Segment_2)
SWIG_JAVABODY_METHODS(public,public,Triangle_2)
SWIG_JAVABODY_METHODS(public,public,Point_3)
SWIG_JAVABODY_METHODS(public,public,Weighted_point_3)
SWIG_JAVABODY_METHODS(public,public,Plane_3)
SWIG_JAVABODY_METHODS(public,public,Segment_3)
SWIG_JAVABODY_METHODS(public,public,Triangle_3)
SWIG_JAVABODY_METHODS(public,public,Tetrahedron_3)
SWIG_JAVABODY_METHODS(public,public,Line_3)
SWIG_JAVABODY_METHODS(public,public,CGAL_Object)
#endif

//include files
%{
  #include "Point_2.h"
  #include "Weighted_point_2.h"
  #include "Segment_2.h"
  #include "Triangle_2.h"
  #include "Point_3.h"
  #include "Weighted_point_3.h"
  #include "Plane_3.h"
  #include "Segment_3.h"
  #include "Triangle_3.h"
  #include "Tetrahedron_3.h"
  #include "Line_3.h"
  #include "CGAL_Object.h"
  #include "global_functions.h"
  #include "enum.h"
%}

//definitions
%include "Point_2.h"
%include "Weighted_point_2.h"
%include "Segment_2.h"
%include "Triangle_2.h"
%include "Point_3.h"
%include "Weighted_point_3.h"
%include "Plane_3.h"
%include "Segment_3.h"
%include "Line_3.h"
%include "Triangle_3.h"
%include "Tetrahedron_3.h"
%include "CGAL_Object.h"
%include "enum.h"
%include "../Common/global_function_macros.h"
%include "global_function_signatures.h"


