#include <iostream>
#include <cassert>
#include "JavaData.h"
#include "global_functions.h"

void JavaData::init(jobject obj){
  if (obj!=NULL){
    cnt=new int(1);
    assert(get_cached_jvm() != NULL);
    JNIEnv* env=JNU_GetEnv();
    //jint ret = env->GetJavaVM(&get_cached_jvm());
    env->GetJavaVM(&get_cached_jvm());
    data = env->NewGlobalRef(obj);
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
      assert(get_cached_jvm() != NULL);
      void* newEnv = NULL;
      get_cached_jvm()->GetEnv(&newEnv,JNI_VERSION_1_2);
      ((JNIEnv*)newEnv)->DeleteGlobalRef(data);
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

jobject JavaData::get_data(){return data;}

void JavaData::set_data(jobject n){
  if (data!=NULL)
    clean();
  init(n);
}

