// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#include <stdexcept>
#include <cassert>
#include <SWIG_CGAL/Java/global_functions.h>
#include <iostream>

JavaVM* & get_cached_jvm(){
  static JavaVM* cached_jvm = NULL;
  return cached_jvm;
}

JNIEnv * JNU_GetEnv() {
  JNIEnv *env;
  assert(get_cached_jvm()!=NULL);
  jint rc = get_cached_jvm()->GetEnv((void **)&env, JNI_VERSION_1_2);
  if (rc == JNI_EDETACHED)
    throw std::runtime_error("current thread not attached");
  if (rc == JNI_EVERSION)
    throw std::runtime_error("jni version not supported");
  return env;
}

