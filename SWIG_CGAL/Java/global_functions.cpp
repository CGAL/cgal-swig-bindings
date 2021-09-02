// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#include <stdexcept>
#include <cassert>
#include <SWIG_CGAL/Java/global_functions.h>
#include <iostream>

JavaVM* & get_cached_jvm(){
  static JavaVM* cached_jvm = nullptr;
  return cached_jvm;
}

JNIEnv * JNU_GetEnv() {
  JNIEnv *env;
  assert(get_cached_jvm()!=nullptr);
  jint rc = get_cached_jvm()->GetEnv((void **)&env, JNI_VERSION_1_2);
  if (rc == JNI_EDETACHED)
    rc = get_cached_jvm()->AttachCurrentThreadAsDaemon((void**)&env, nullptr);
  if (rc == JNI_EVERSION)
    throw std::runtime_error("jni version not supported");
  return env;
}

