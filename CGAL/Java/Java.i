%module CGAL_SWIG_Java


#ifdef SWIGJAVA
//method getCPtr and constructor from (long,bool) should be public
//to be used in other packages cf. file java.swg
SWIG_JAVABODY_METHODS(public,public,JavaData)
#endif

//include files
%{
  #include "JavaData.h"
%}

//definitions
%include "JavaData.h"

