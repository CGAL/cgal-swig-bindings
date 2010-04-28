#include <iostream>
#include <stdexcept>
#include <cassert>
#include "JavaData.h"


static JavaVM* & get_cached_jvm(){
  static JavaVM* cached_jvm = NULL;
  return cached_jvm;
}

//function called when library is loaded in Java
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
  std::cout << "coucou"<< std::endl;
  get_cached_jvm() = jvm;
  return JNI_VERSION_1_2;
}

static JNIEnv * JNU_GetEnv() {
  JNIEnv *env;
  jint rc = get_cached_jvm()->GetEnv((void **)&env, JNI_VERSION_1_2);
  if (rc == JNI_EDETACHED)
    throw std::runtime_error("current thread not attached");
  if (rc == JNI_EVERSION)
    throw std::runtime_error("jni version not supported");
  return env;
}


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

