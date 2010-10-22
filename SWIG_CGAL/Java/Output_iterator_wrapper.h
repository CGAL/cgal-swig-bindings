#ifndef CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H
#define CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H

#include <boost/function_output_iterator.hpp>
#include <SWIG_CGAL/Java/global_functions.h>

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
    obj_class =(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->FindClass(name) );
    assert( obj_class !=NULL );
    init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(JZ)V");
    
    cont_class=(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(container) );
    assert(cont_class!=NULL);
    add_id=JNU_GetEnv()->GetMethodID(cont_class, "add", "(Ljava/lang/Object;)Z");
    assert(add_id!=NULL);
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
    assert(ho!=NULL);
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
    obj_class =(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->FindClass(name) );
    assert( obj_class !=NULL );
    init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(I)V");
    
    cont_class=(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(container) );
    assert(cont_class!=NULL);
    add_id=JNU_GetEnv()->GetMethodID(cont_class, "add", "(Ljava/lang/Object;)Z");
    assert(add_id!=NULL);
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
    assert(ho!=NULL);
    JNU_GetEnv()->CallBooleanMethod(container, add_id, ho);
  }
};



#endif// CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H

