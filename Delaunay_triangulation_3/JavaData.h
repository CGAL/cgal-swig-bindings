#ifndef JAVA_DATA_H
#define JAVA_DATA_H

#include <jni.h>

class JavaData {
  int* cnt;
  JavaVM *vm;
  JNIEnv* env;
  jint vmVersion;
  jobject data;
 
  void copy(const JavaData&);
  void clean();
  
public:  
  JavaData (JNIEnv* e = NULL, jobject ref = NULL);
  JavaData(const JavaData & d);
  ~JavaData();
  JavaData& operator=(const JavaData& d);
  inline jobject get_data();
  inline void set_data(const jobject& n);
}; //end of class

#endif //JAVA_DATA_H
