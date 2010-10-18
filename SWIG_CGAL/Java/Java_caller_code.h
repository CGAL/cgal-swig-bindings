#ifndef SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
#define SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H

#include <SWIG_CGAL/Java/global_functions.h>
#include <cassert>
#include <iostream>
#include <string>

template <class Input_wrapper,class Output_wrapper>
class Java_caller_code
{
  //info for calling the java predicate
  jobject java_predicate;
  jclass predicate_class;
  jmethodID predicate_id;
  // types of input and output in java format
  std::string input_type_,output_type_;
  //info for input
  jclass input_class;
  jmethodID input_cst_id;
  //info for output
  jclass output_class;
  jmethodID get_output_id;
  int* ref_counter;
  
  void cleanup()
  {
    if (--(*ref_counter)==0){
      delete ref_counter;
      JNU_GetEnv()->DeleteGlobalRef(java_predicate);
      JNU_GetEnv()->DeleteGlobalRef(input_class);
      JNU_GetEnv()->DeleteGlobalRef(output_class);
      JNU_GetEnv()->DeleteGlobalRef(predicate_class);
    }    
  }
  
  void copy(const Java_caller_code& original)
  {
    java_predicate=original.java_predicate;
    predicate_class=original.predicate_class;
    predicate_id=original.predicate_id;
    input_type_=original.input_type_;
    output_type_=original.output_type_;
    input_class=original.input_class;
    input_cst_id=original.input_cst_id;
    output_class=original.output_class;
    get_output_id=original.get_output_id;
    ref_counter=original.ref_counter;    
    ++(*ref_counter);
  }
public:

  Java_caller_code(jobject jobj,const char* fname, const char* input_type,const char* output_type)
  :input_type_(input_type),output_type_(output_type),ref_counter(new int(1))
  {
    //set info for java predicate
    std::string fsign=std::string("(")+input_type_+std::string(")")+output_type_;
    java_predicate=JNU_GetEnv()->NewGlobalRef(jobj);
    jclass local_jclass=JNU_GetEnv()->GetObjectClass(java_predicate);
    predicate_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    assert(predicate_class!=NULL);
    predicate_id=JNU_GetEnv()->GetMethodID(predicate_class, fname, fsign.c_str());
    assert(predicate_id!=NULL);
    //set info for input
    local_jclass = JNU_GetEnv()->FindClass(input_type_.c_str());
    input_class = (jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    input_cst_id=JNU_GetEnv()->GetMethodID(input_class,"<init>", "(JZ)V");
    //set info for output
    local_jclass=JNU_GetEnv()->FindClass(output_type_.c_str());
    output_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    std::string output_signature=std::string("(")+output_type_+std::string(")J");
    get_output_id=JNU_GetEnv()->GetStaticMethodID(output_class, "getCPtr",output_signature.c_str());
  }
  
  ~Java_caller_code()
  {
    cleanup();
  }
  
  Java_caller_code& operator=(const Java_caller_code &original)
  {
    cleanup();
    copy(original);
    return *this;
  }

  Java_caller_code(const Java_caller_code& original)
  {
    copy(original);
  }
  
  #ifndef SWIG
  void run0(jobject data)
  {JNU_GetEnv()->CallVoidMethod(java_predicate,predicate_id,data);}
  
  jobject run(jobject data)
  {return JNU_GetEnv()->CallObjectMethod(java_predicate,predicate_id,data);}
  
  typename Output_wrapper::cpp_base run(const typename Input_wrapper::cpp_base& input) const
  {
    //create the wrapper object
    Input_wrapper*  cpp_wrapper=new Input_wrapper(input);
    //create the java corresponding object
    assert( input_class !=NULL );
    assert( input_cst_id !=NULL );
    jobject input_in_java = JNU_GetEnv()->NewObject(input_class,input_cst_id, (jlong) cpp_wrapper,true);
    assert(input_in_java!=NULL);
    
    //call java method
    jobject res = JNU_GetEnv()->CallObjectMethod(java_predicate,predicate_id,input_in_java);
    //convert the result back to c++
    assert(output_class!=NULL);
    assert(get_output_id!=NULL);
    jlong jcpp=(jlong) JNU_GetEnv()->CallStaticObjectMethod(output_class,get_output_id,res);
    assert( (void*) jcpp != NULL );
    return reinterpret_cast<Output_wrapper*>(jcpp)->get_data();
  }
  #endif
};


#endif // SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
