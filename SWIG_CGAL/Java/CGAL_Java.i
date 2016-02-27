// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Java

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary_CGAL_Java()
SWIG_CGAL_package_common()

//include files
%{
  #include <SWIG_CGAL/Java/JavaData.h>
%}

//definitions
%include "SWIG_CGAL/Java/JavaData.h"

%{
  #include <jni.h>
  //function called when library is loaded in Java
  JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *) {
    get_cached_jvm() = jvm;
    return JNI_VERSION_1_2;
  }
%}

#ifdef SWIG_CGAL_HAS_Java_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Java/extensions.i"
#endif
