%module CGAL_Kernel

//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

%import  "SWIG_CGAL/Common/Macros.h"
%include "SWIG_CGAL/common.i"

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
SWIG_JAVABODY_METHODS(public,public,Sphere_3)
SWIG_JAVABODY_METHODS(public,public,CGAL_Object)
#endif

//include files
%{
  #include <SWIG_CGAL/Kernel/Point_2.h>
  #include <SWIG_CGAL/Kernel/Weighted_point_2.h>
  #include <SWIG_CGAL/Kernel/Segment_2.h>
  #include <SWIG_CGAL/Kernel/Triangle_2.h>
  #include <SWIG_CGAL/Kernel/Point_3.h>
  #include <SWIG_CGAL/Kernel/Weighted_point_3.h>
  #include <SWIG_CGAL/Kernel/Plane_3.h>
  #include <SWIG_CGAL/Kernel/Segment_3.h>
  #include <SWIG_CGAL/Kernel/Triangle_3.h>
  #include <SWIG_CGAL/Kernel/Tetrahedron_3.h>
  #include <SWIG_CGAL/Kernel/Line_3.h>
  #include <SWIG_CGAL/Kernel/Sphere_3.h>
  #include <SWIG_CGAL/Kernel/CGAL_Object.h>
  #include <SWIG_CGAL/Kernel/global_functions.h>
  #include <SWIG_CGAL/Kernel/enum.h>
%}

//definitions
%include "SWIG_CGAL/Kernel/Point_2.h"
%include "SWIG_CGAL/Kernel/Weighted_point_2.h"
%include "SWIG_CGAL/Kernel/Segment_2.h"
%include "SWIG_CGAL/Kernel/Triangle_2.h"
%include "SWIG_CGAL/Kernel/Point_3.h"
%include "SWIG_CGAL/Kernel/Weighted_point_3.h"
%include "SWIG_CGAL/Kernel/Plane_3.h"
%include "SWIG_CGAL/Kernel/Segment_3.h"
%include "SWIG_CGAL/Kernel/Line_3.h"
%include "SWIG_CGAL/Kernel/Sphere_3.h"
%include "SWIG_CGAL/Kernel/Triangle_3.h"
%include "SWIG_CGAL/Kernel/Tetrahedron_3.h"
%include "SWIG_CGAL/Kernel/CGAL_Object.h"
%include "SWIG_CGAL/Kernel/enum.h"
%include "SWIG_CGAL/Common/global_function_macros.h"
%include "SWIG_CGAL/Kernel/global_function_signatures.h"


