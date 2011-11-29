// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_JAVA_OUTPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_JAVA_OUTPUT_ITERATOR_WRAPPER_H

#include <boost/function_output_iterator.hpp>
#include <SWIG_CGAL/Java/global_functions.h>
#include <SWIG_CGAL/Java/exception.h>

template<class Cpp_wrapper,class Cpp_base>
class Container_writer{
  jobject container;
  jmethodID init_id, add_id;
  jclass cont_class,obj_class;
  int* ref_counter;
  
  void cleanup(){
    if (--(*ref_counter) == 0)
    {
      delete ref_counter;
      if (container!=NULL ){
        JNU_GetEnv()->DeleteGlobalRef(container);
        JNU_GetEnv()->DeleteGlobalRef(cont_class);
        JNU_GetEnv()->DeleteGlobalRef(obj_class);
      }
    }
  }
  
  void copy(const Container_writer& source){
    container=source.container;
    init_id=source.init_id;
    add_id=source.add_id;
    cont_class=source.cont_class;
    obj_class=source.obj_class;
    ref_counter=source.ref_counter;
    ++(*ref_counter);    
  }
public:

  Container_writer():container(NULL),cont_class(NULL),obj_class(NULL),ref_counter(new int(1)){}
  Container_writer(jobject container_,const char* name):ref_counter(new int(1))
  {
    container = JNU_GetEnv()->NewGlobalRef( container_ );
    JNI_THROW_ON_ERROR(container,NewGlobalRef," ")
    jclass tmp_class=JNU_GetEnv()->FindClass(name);
    JNI_THROW_ON_ERROR(tmp_class,FindClass,name)
    obj_class =(jclass) JNU_GetEnv()->NewGlobalRef( tmp_class );
    JNI_THROW_ON_ERROR(obj_class,NewGlobalRef," ")
    init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(JZ)V");
    JNI_THROW_ON_ERROR(init_id,GetMethodID,"<init> (JZ)V");
    cont_class=(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(container) );
    JNI_THROW_ON_ERROR(cont_class,NewGlobalRef," ")
    add_id=JNU_GetEnv()->GetMethodID(cont_class, "add", "(Ljava/lang/Object;)Z");
    JNI_THROW_ON_ERROR(add_id,GetMethodID,"add (Ljava/lang/Object;)Z")
  }
  
  ~Container_writer(){
    cleanup();
  }
  
  Container_writer(const Container_writer& source)
  {
    copy(source);
  }
  
  Container_writer& operator=(const Container_writer& source)
  {
    if (this!=&source){
      cleanup();
      copy(source);
    }
    return *this;
  }
  
  void operator()(const Cpp_base& new_base) {
    Cpp_wrapper*  object=new Cpp_wrapper(new_base);
    jlong hptr = (jlong) object;
    jobject ho = JNU_GetEnv()->NewObject(obj_class, init_id, hptr,true);
    JNI_THROW_ON_ERROR(ho,NewObject," ")
    JNU_GetEnv()->CallBooleanMethod(container, add_id, ho);
  }
};

template<>
class Container_writer<int,int>{
  jobject container;
  jmethodID init_id, add_id;
  jclass cont_class,obj_class;
  int* ref_counter;
  
  void cleanup(){
    if (--(*ref_counter) == 0)
    {
      delete ref_counter;
      if (container!=NULL ){
        JNU_GetEnv()->DeleteGlobalRef(container);
        JNU_GetEnv()->DeleteGlobalRef(cont_class);
        JNU_GetEnv()->DeleteGlobalRef(obj_class);
      }
    }
  }
  
  void copy(const Container_writer& source){
    container=source.container;
    init_id=source.init_id;
    add_id=source.add_id;
    cont_class=source.cont_class;
    obj_class=source.obj_class;
    ref_counter=source.ref_counter;
    ++(*ref_counter);    
  }
public:

  Container_writer():container(NULL),cont_class(NULL),obj_class(NULL),ref_counter(new int(1)){}
  Container_writer(jobject container_,const char* name):ref_counter(new int(1))
  {
    container = JNU_GetEnv()->NewGlobalRef( container_ );
    JNI_THROW_ON_ERROR(container,NewGlobalRef," ")
    jclass tmp_class=JNU_GetEnv()->FindClass(name);
    JNI_THROW_ON_ERROR(tmp_class,FindClass,name);
    obj_class =(jclass) JNU_GetEnv()->NewGlobalRef( tmp_class );
    JNI_THROW_ON_ERROR(obj_class,NewGlobalRef," ")
    init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(I)V");
    JNI_THROW_ON_ERROR(init_id,GetMethodID,"<init> (I)V")
    cont_class=(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(container) );
    JNI_THROW_ON_ERROR(cont_class,NewGlobalRef," ")
    add_id=JNU_GetEnv()->GetMethodID(cont_class, "add", "(Ljava/lang/Object;)Z");
    JNI_THROW_ON_ERROR(add_id,GetMethodID,"add (Ljava/lang/Object;)Z")
  }
  
  ~Container_writer(){
    cleanup();
  }
  
  Container_writer(const Container_writer& source)
  {
    copy(source);
  }
  
  Container_writer& operator=(const Container_writer& source)
  {
    if (this!=&source){
      cleanup();
      copy(source);
    }
    return *this;
  }
  
  void operator()(int new_base) {
    jobject ho = JNU_GetEnv()->NewObject(obj_class, init_id,new_base,true);
    JNI_THROW_ON_ERROR(ho,NewObject," ")
    JNU_GetEnv()->CallBooleanMethod(container, add_id, ho);
  }
};



#endif// SWIG_CGAL_JAVA_OUTPUT_ITERATOR_WRAPPER_H

