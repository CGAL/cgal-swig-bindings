#ifndef SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
#define SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H

#include <jni.h>

JNIEXPORT JavaVM* & get_cached_jvm();
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved);
JNIEXPORT JNIEnv * JNU_GetEnv();


#endif //SWIG_CGAL_JAVA_GLOBAL_FUNCTIONS_H
