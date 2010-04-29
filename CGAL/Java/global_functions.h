#ifndef CGAL_SWIG_JAVA_GLOBAL_FUNCTIONS_H
#define CGAL_SWIG_JAVA_GLOBAL_FUNCTIONS_H

#include <jni.h>

JavaVM* & get_cached_jvm();
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved);
JNIEnv * JNU_GetEnv();


#endif //CGAL_SWIG_JAVA_GLOBAL_FUNCTIONS_H
