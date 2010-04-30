#ifndef CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H
#define CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H

#include "global_functions.h"

template<class Cpp_wrapper,class Cpp_base>
class Container_writer{
  const jobject* container; //we suppose that it is not garbaged collected:
                            //the original must stay valid while iterator used.
                            //Usually ok because used within the same function
  jmethodID init_id, add_id;
  jclass cont_class,obj_class;
public:

  Container_writer(){}
  Container_writer(const jobject& container_,const char* name):container(&container_)
  {
    obj_class = JNU_GetEnv()->FindClass(name);
    assert( obj_class !=NULL );
    init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(JZ)V");
    
    cont_class=JNU_GetEnv()->GetObjectClass(*container);
    assert(cont_class!=NULL);
    add_id=JNU_GetEnv()->GetMethodID(cont_class, "add", "(Ljava/lang/Object;)Z");
    assert(add_id!=NULL);
  }
 
  void operator()(const Cpp_base& new_base) {
    Cpp_wrapper*  object=new Cpp_wrapper(new_base);
    jlong hptr = (jlong) object;
    jobject ho = JNU_GetEnv()->NewObject(obj_class, init_id, hptr,true);
    assert(ho!=NULL);
    JNU_GetEnv()->CallBooleanMethod(*container, add_id, ho);
  }
};



#endif// CGAL_SWIG_JAVA_OUTPUT_ITERATOR_WRAPPER_H

