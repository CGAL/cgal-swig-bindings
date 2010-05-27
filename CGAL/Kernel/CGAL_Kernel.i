%module CGAL_Kernel

%include "../common.i"

//%typemap(javapackage) Point_3 "CGAL.Kernel"

#ifdef SWIGJAVA
//method getCPtr and constructor from (long,bool) should be public
//to be used in other packages cf. file java.swg
SWIG_JAVABODY_METHODS(public,public,Point_2)
SWIG_JAVABODY_METHODS(public,public,Point_3)
SWIG_JAVABODY_METHODS(public,public,Plane_3)
SWIG_JAVABODY_METHODS(public,public,Segment_3)
SWIG_JAVABODY_METHODS(public,public,Line_3)
#endif

//include files
%{
  #include "Point_2.h"
  #include "Point_3.h"
  #include "Plane_3.h"
  #include "Segment_3.h"
  #include "Line_3.h"
  #include "global_functions.h"
%}

//definitions
%include "Point_2.h"
%include "Point_3.h"
%include "Plane_3.h"
%include "Segment_3.h"
%include "Line_3.h"
%include "../Common/global_function_macros.h"
%include "global_function_signatures.h"


