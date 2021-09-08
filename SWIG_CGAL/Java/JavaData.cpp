// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#define SWIG_CGAL_JAVA_EXPORT 

#include <iostream>
#include <SWIG_CGAL/Java/JavaData.h>

void JavaData::init(jobject obj){
  if (obj!=nullptr){
    cnt=new int(1);
    data = JNU_GetEnv()->NewGlobalRef(obj);
  }
  else
    data = nullptr;
}

void JavaData::copy(const JavaData& d){
  cnt = d.cnt;
  data = d.data;
  if (d.data!=nullptr)
    ++(*cnt);    
}

void JavaData::clean(){
  if (data != nullptr){
    --(*cnt);
    if ((*cnt) == 0) {
      JNU_GetEnv()->DeleteGlobalRef(data);
      delete cnt;
      cnt=nullptr;
    }
  }
  data=nullptr;
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
  if (data!=nullptr)
    clean();
  init(n);
}

