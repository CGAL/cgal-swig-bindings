// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Java

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_AABB_tree failed to load. \n" + e);
      throw e;
    }
  }
%}


//include files
%{
  #include <SWIG_CGAL/Java/JavaData.h>
%}

//definitions
%include "SWIG_CGAL/Java/JavaData.h"

