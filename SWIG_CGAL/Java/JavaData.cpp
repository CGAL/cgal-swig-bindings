// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#define SWIG_CGAL_JAVA_EXPORT 

#include <iostream>
#include <SWIG_CGAL/Java/JavaData.h>

void JavaData::init(jobject obj){
  if (obj!=NULL){
    cnt=new int(1);
    data = JNU_GetEnv()->NewGlobalRef(obj);
  }
  else
    data = NULL;
}

void JavaData::copy(const JavaData& d){
  cnt = d.cnt;
  data = d.data;
  if (d.data!=NULL)
    ++(*cnt);    
}

void JavaData::clean(){
  if (data != NULL){
    --(*cnt);
    if ((*cnt) == 0) {
      JNU_GetEnv()->DeleteGlobalRef(data);
      delete cnt;
      cnt=NULL;
    }
  }
  data=NULL;
}

JavaData::JavaData (jobject obj) { 
  init(obj);
}

JavaData::JavaData(const JavaData & d) {
  copy(d);
}

JavaData::~JavaData() {
  clean();
}

JavaData& JavaData::operator=(const JavaData& d){
  if (this!=&d){
    clean();
    copy(d);
  }
  return *this;
}

bool JavaData::operator<(const JavaData& d) const {
  return data < d.data;
}

jobject JavaData::get_data(){return data;}

void JavaData::set_data(jobject n){
  if (data!=NULL)
    clean();
  init(n);
}

