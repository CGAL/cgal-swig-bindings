%module CGAL_Java

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_AABB_tree failed to load. \n" + e);
      System.exit(1);
    }
  }
%}


//method getCPtr and constructor from (long,bool) should be public
//to be used in other packages cf. file java.swg
SWIG_JAVABODY_METHODS(public,public,JavaData)


//include files
%{
  #include <SWIG_CGAL/Java/JavaData.h>
%}

//definitions
%include "SWIG_CGAL/Java/JavaData.h"

