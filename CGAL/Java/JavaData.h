#ifndef JAVA_DATA_H
#define JAVA_DATA_H

#include <jni.h>

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
  JavaData& operator=(const JavaData& d);
  jobject get_data();
  void set_data(jobject n);
}; //end of class

#endif //JAVA_DATA_H
