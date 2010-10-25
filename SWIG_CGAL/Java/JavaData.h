#ifndef JAVA_DATA_H
#define JAVA_DATA_H

#include <jni.h>
#include <cassert>
#include <SWIG_CGAL/Java/global_functions.h>

class JavaData {
  int* cnt;
  jobject data;
 
  void copy(const JavaData&);
  void clean();
  void init(jobject);
  
public:  
  JavaData (jobject ref = NULL);
  JavaData(const JavaData & d);
  ~JavaData();
#ifndef SWIG
  JavaData& operator=(const JavaData& d);
  bool operator<(const JavaData& d) const;
  void init_empty_object()
  {
    jclass objclass=JNU_GetEnv()->FindClass("Ljava/lang/Object;");
    assert(objclass!=NULL);
    jmethodID init_id=JNU_GetEnv()->GetMethodID(objclass,"<init>","()V");
    assert(init_id!=NULL);
    init(JNU_GetEnv()->NewObject(objclass,init_id));
  }
#endif
  jobject get_data();
  void set_data(jobject n);
}; //end of class

#endif //JAVA_DATA_H
