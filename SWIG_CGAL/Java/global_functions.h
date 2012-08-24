// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
#define SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H

#include <jni.h>

JNIEXPORT JavaVM* & get_cached_jvm();
JNIEXPORT JNIEnv * JNU_GetEnv();


#endif //SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
