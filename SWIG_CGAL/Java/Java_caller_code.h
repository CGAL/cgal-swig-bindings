#ifndef SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
#define SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H

#include <SWIG_CGAL/Java/global_functions.h>
#include <SWIG_CGAL/Common/Macros.h>
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
    input_class=original.input_class;
    input_cst_id=original.input_cst_id;
    output_class=original.output_class;
    get_output_id=original.get_output_id;
    ref_counter=original.ref_counter;    
    ++(*ref_counter);
  }
public:

  Java_caller_code(jobject jobj,const char* fname, const char* input_type,const char* output_type)
  :ref_counter(new int(1))
  {
    //set info for java predicate
    std::string fsign=std::string("(L")+input_type+std::string(";)L")+std::string(output_type)+std::string(";");
    java_predicate=JNU_GetEnv()->NewGlobalRef(jobj);
    jclass local_jclass=JNU_GetEnv()->GetObjectClass(java_predicate);
    predicate_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    assert(predicate_class!=NULL);
    predicate_id=JNU_GetEnv()->GetMethodID(predicate_class, fname, fsign.c_str());
    assert(predicate_id!=NULL);
    //set info for input
    local_jclass = JNU_GetEnv()->FindClass(input_type);
    input_class = (jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    input_cst_id=JNU_GetEnv()->GetMethodID(input_class,"<init>", "(JZ)V");
    //set info for output
    local_jclass=JNU_GetEnv()->FindClass(output_type);
    output_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    std::string output_signature=std::string("(L")+output_type+std::string(";)J");
    get_output_id=JNU_GetEnv()->GetStaticMethodID(output_class, "getCPtr",output_signature.c_str());
  }
  
  ~Java_caller_code()
  {
    cleanup();
  }
  
  Java_caller_code& operator=(const Java_caller_code &original)
  {
    if (this!=&original){
      cleanup();
      copy(original);
    }
    return *this;
  }

  Java_caller_code(const Java_caller_code& original)
  {
    copy(original);
  }
  
  #ifndef SWIG
  typename internal::Converter<Output_wrapper>::result_type
  run(const typename internal::Converter<Input_wrapper>::result_type& input) const
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
    return internal::Converter<Output_wrapper>::convert( *reinterpret_cast<Output_wrapper*>(jcpp) );
  }
  #endif
};

template <class Input_wrapper_1,class Input_wrapper_2,class Output_wrapper>
class Java_caller_code_2
{
  //info for calling the java predicate
  jobject java_predicate;
  jclass predicate_class;
  jmethodID predicate_id_1;
  jmethodID predicate_id_2;
  //info for input_1
  jclass input_class_1;
  jmethodID input_cst_id_1;
  //info for input_2
  jclass input_class_2;
  jmethodID input_cst_id_2;
  //info for output
  jclass output_class;
  jmethodID get_output_id;
  int* ref_counter;
  
  void cleanup()
  {
    if (ref_counter!=NULL && --(*ref_counter)==0){
      delete ref_counter;
      JNU_GetEnv()->DeleteGlobalRef(java_predicate);
      JNU_GetEnv()->DeleteGlobalRef(input_class_1);
      JNU_GetEnv()->DeleteGlobalRef(input_class_2);
      JNU_GetEnv()->DeleteGlobalRef(output_class);
      JNU_GetEnv()->DeleteGlobalRef(predicate_class);
    }    
  }
  
  void copy(const Java_caller_code_2& original)
  {
    java_predicate=original.java_predicate;
    predicate_class=original.predicate_class;
    predicate_id_1=original.predicate_id_1;
    predicate_id_2=original.predicate_id_2;
    input_class_1=original.input_class_1;
    input_cst_id_1=original.input_cst_id_1;
    input_class_2=original.input_class_2;
    input_cst_id_2=original.input_cst_id_2;
    output_class=original.output_class;
    get_output_id=original.get_output_id;
    ref_counter=original.ref_counter;    
    ++(*ref_counter);
  }
public:
  Java_caller_code_2():ref_counter(NULL){}

  Java_caller_code_2(jobject jobj,const char* fname, const char* input_type_1, const char* input_type_2,const char* output_type)
  :ref_counter(new int(1))
  {
    //set info for calling predicates
    java_predicate=JNU_GetEnv()->NewGlobalRef(jobj);
    jclass local_jclass=JNU_GetEnv()->GetObjectClass(java_predicate);
    predicate_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    assert(predicate_class!=NULL);
    //set info for java predicate jobject
    std::string fsign_1=std::string("(L")+input_type_2+std::string(";)L")+std::string(output_type)+std::string(";");
    predicate_id_1=JNU_GetEnv()->GetMethodID(predicate_class, fname, fsign_1.c_str());
    assert(predicate_id_1!=NULL);    
    //set info for java predicate 2
    std::string fsign_2=std::string("(L")+input_type_1+std::string(";L")+input_type_2+std::string(";)L")+output_type+std::string(";");
    predicate_id_2=JNU_GetEnv()->GetMethodID(predicate_class, fname, fsign_2.c_str());
    assert(predicate_id_2!=NULL);
    //set info for input_1
    local_jclass = JNU_GetEnv()->FindClass(input_type_1);
    input_class_1 = (jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    input_cst_id_1=JNU_GetEnv()->GetMethodID(input_class_1,"<init>", "(JZ)V");
    //set info for input_2
    local_jclass = JNU_GetEnv()->FindClass(input_type_2);
    input_class_2 = (jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    input_cst_id_2=JNU_GetEnv()->GetMethodID(input_class_2,"<init>", "(JZ)V");
    //set info for output
    local_jclass=JNU_GetEnv()->FindClass(output_type);
    output_class=(jclass) JNU_GetEnv()->NewGlobalRef(local_jclass);
    std::string output_signature=std::string("()I"); 
    get_output_id=JNU_GetEnv()->GetMethodID(output_class, "swigValue",output_signature.c_str());
  }
  
  ~Java_caller_code_2()
  {
    cleanup();
  }
  
  Java_caller_code_2& operator=(const Java_caller_code_2 &original)
  {
    if (this!=&original){
      cleanup();
      copy(original);
    }
    return *this;
  }

  Java_caller_code_2(const Java_caller_code_2& original)
  {
    copy(original);
  }
  
  #ifndef SWIG
  typename internal::Converter<Output_wrapper>::result_type
  run_1(const typename internal::Converter<Input_wrapper_2>::result_type& input) const
  {
    //create the wrapper object 2
    Input_wrapper_2*  cpp_wrapper_2=new Input_wrapper_2(input);
    //create the java corresponding object
    assert( input_class_2 !=NULL );
    assert( input_cst_id_2 !=NULL );
    jobject input_in_java = JNU_GetEnv()->NewObject(input_class_2,input_cst_id_2, (jlong) cpp_wrapper_2,true);
    assert(input_in_java!=NULL);    
    //call java method
    jobject res = JNU_GetEnv()->CallObjectMethod(java_predicate,predicate_id_1,input_in_java);
    //convert the result back to c++
    assert(output_class!=NULL);
    assert(get_output_id!=NULL);
    int val=(int) JNU_GetEnv()->CallIntMethod(res,get_output_id);
    return CGAL::enum_cast<typename internal::Converter<Output_wrapper>::result_type>( val );
  }  
  
  typename internal::Converter<Output_wrapper>::result_type
  run_2(const typename internal::Converter<Input_wrapper_1>::result_type& input_1,
              typename internal::Converter<Input_wrapper_2>::result_type& input_2) const
  {
    //create the wrapper object 1
    Input_wrapper_1*  cpp_wrapper_1=new Input_wrapper_1(input_1);
    //create the java corresponding object
    assert( input_class_1 !=NULL );
    assert( input_cst_id_1 !=NULL );
    jobject input_in_java_1 = JNU_GetEnv()->NewObject(input_class_1,input_cst_id_1, (jlong) cpp_wrapper_1,true);
    assert(input_in_java_1!=NULL);
    
    //create the wrapper object 2
    Input_wrapper_2*  cpp_wrapper_2=new Input_wrapper_2(input_2);
    //create the java corresponding object
    assert( input_class_2 !=NULL );
    assert( input_cst_id_2 !=NULL );
    jobject input_in_java_2 = JNU_GetEnv()->NewObject(input_class_2,input_cst_id_2, (jlong) cpp_wrapper_2,true);
    assert(input_in_java_2!=NULL);
    
    //call java method
    jobject res = JNU_GetEnv()->CallObjectMethod(java_predicate,predicate_id_2,input_in_java_1,input_in_java_2);
    //convert the result back to c++
    assert(output_class!=NULL);
    assert(get_output_id!=NULL);
    int val=(int) JNU_GetEnv()->CallIntMethod(res,get_output_id);
    input_2=cpp_wrapper_2->get_data();
    return CGAL::enum_cast<typename internal::Converter<Output_wrapper>::result_type>( val );
  }
  #endif
};


#endif // SWIG_CGAL_JAVA_JAVA_CALLER_CODE_H
