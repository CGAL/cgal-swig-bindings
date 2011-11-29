// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef JAVA_DATA_H
#define JAVA_DATA_H

#include <jni.h>
#include <cassert>
#include <SWIG_CGAL/Java/global_functions.h>
#include <SWIG_CGAL/Java/decl.h>

class SWIG_CGAL_JAVA_DECL JavaData {
  int* cnt;
  jobject data;
 
  void copy(const JavaData&);
  void clean();
  void init(jobject);
  typedef JavaData Self;
  //disable deep copy because the jobject stored may not be clonable
  Self deepcopy();
  void deepcopy(const Self&);  
public:  
  JavaData (jobject ref = NULL);
  ~JavaData();
#ifndef SWIG
  JavaData(const JavaData & d);
  JavaData& operator=(const JavaData& d);
  bool operator<(const JavaData& d) const;
//  void init_empty_object()
//  {
//    jclass objclass=JNU_GetEnv()->FindClass("java/lang/Object");
//    assert(objclass!=NULL);
//    jmethodID init_id=JNU_GetEnv()->GetMethodID(objclass,"<init>","()V");
//    assert(init_id!=NULL);
//    init(JNU_GetEnv()->NewObject(objclass,init_id));
//  }
#endif
  jobject get_data();
  void set_data(jobject n);
}; //end of class

#endif //JAVA_DATA_H
