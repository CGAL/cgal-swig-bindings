// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
#define SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H

#include <jni.h>

JNIEXPORT JavaVM* & get_cached_jvm();
JNIEXPORT JNIEnv * JNU_GetEnv();


#endif //SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
