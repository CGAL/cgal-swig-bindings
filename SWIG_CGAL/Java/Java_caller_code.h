#ifndef SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
#define SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H

#include <SWIG_CGAL/Java/global_functions.h>
#include <cassert>
#include <iostream>
#include <string>

template <class Input_wrapper,class Output_wrapper>
class Java_caller_code
{
  jobject obj;
  jclass obj_class;
  jmethodID method_id;
  //jmethodID static_method_id;
public:

  Java_caller_code(jobject jobj,const char* fname, const char* fsign)
  {
    obj=JNU_GetEnv()->NewGlobalRef(jobj);
    obj_class=JNU_GetEnv()->GetObjectClass(obj);
    assert(obj_class!=NULL);
    method_id=JNU_GetEnv()->GetMethodID(obj_class, fname, fsign);
    assert(method_id!=NULL);
  }
  
  ~Java_caller_code()
  {
    JNU_GetEnv()->DeleteGlobalRef(obj);
  }
  
  
  #ifndef SWIG
  void run0(jobject data)
  {JNU_GetEnv()->CallVoidMethod(obj,method_id,data);}
  
  jobject run(jobject data)
  {return JNU_GetEnv()->CallObjectMethod(obj,method_id,data);}
  
  typename Output_wrapper::cpp_base run(const typename Input_wrapper::cpp_base& input,std::string input_signature,std::string output_signature) const
  {
    //create the wrapper object
    Input_wrapper*  cpp_wrapper=new Input_wrapper(input);
    //create the java corresponding object
    jclass obj_class = JNU_GetEnv()->FindClass(input_signature.c_str());
    assert( obj_class !=NULL );
    jmethodID init_id = JNU_GetEnv()->GetMethodID(obj_class,"<init>", "(JZ)V");    
    jlong hptr = (jlong) cpp_wrapper;
    jobject ho = JNU_GetEnv()->NewObject(obj_class, init_id, hptr,true);
    assert(ho!=NULL);
    //call java method
    jobject res = JNU_GetEnv()->CallObjectMethod(obj,method_id,ho);
    //convert the result back to c++
    jclass res_class=JNU_GetEnv()->GetObjectClass(res);
    assert(res_class!=NULL);
    output_signature=std::string("(")+output_signature+std::string(")J");
    jmethodID getCPtr_id=JNU_GetEnv()->GetStaticMethodID(res_class, "getCPtr",output_signature.c_str());
    assert(getCPtr_id!=NULL);
    jlong jcpp=(jlong) JNU_GetEnv()->CallStaticObjectMethod(res_class,getCPtr_id,res);
    assert( (void*) jcpp != NULL );
    return reinterpret_cast<Output_wrapper*>(jcpp)->get_data();
  }
  #endif
};


#endif // SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
