#ifndef JAVA_DATA_H
#define JAVA_DATA_H

#include "javadata.h"

void JavaData::copy(const JavaData& d){
  env = d.env;
  vm = d.vm;
  cnt = d.cnt;
  data = d.data;
  vmVersion = d.vmVersion;
  ++(*cnt);    
}

void JavaData::clean(){
  --(*cnt);
  if ((*cnt) == 0) {
    if (vm != NULL && env != NULL && data != NULL) {
      void* newEnv = NULL;
      vm->GetEnv(&newEnv,vmVersion);
      ((JNIEnv*)newEnv)->DeleteGlobalRef(data);
    }
    delete cnt;
  }    
}

JavaData::JavaData (JNIEnv* e = NULL, jobject ref = NULL):cnt(new int(1)),vm(NULL),env(e) { 
  if (env != NULL && ref != NULL) {
    jint ret = env->GetJavaVM(&vm);
    vmVersion = env->GetVersion();
    data = env->NewGlobalRef(ref);
  }else{
    data = NULL;
  }
}

JavaData::JavaData(const JavaData & d) {
  copy(d);
}

JavaData::~JavaData() {
  clean();
}

JavaData& JavaData::operator=(const JavaData& d){
  clean();
  copy(d);
  return *this;
}

jobject JavaData::get_data(){return data;}

void JavaData::set_data(const jobject& n){
  data=n;
}

