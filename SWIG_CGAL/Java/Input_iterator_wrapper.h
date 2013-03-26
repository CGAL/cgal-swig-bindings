// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_JAVA_INPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_JAVA_INPUT_ITERATOR_WRAPPER_H

#include <boost/iterator/iterator_facade.hpp>
#include <SWIG_CGAL/Java/global_functions.h>
#include <SWIG_CGAL/Java/exception.h>

#ifndef SWIG
struct Ref_counted_jdata{
  jobject jiterator; 
  jclass it_class,pt_class;
  int* counter;
  
  Ref_counted_jdata():jiterator(NULL),counter(new int(1)){}
  
  Ref_counted_jdata(jobject jit):counter(new int(1))
  {
    jiterator=JNU_GetEnv()->NewGlobalRef(jit);
    JNI_THROW_ON_ERROR(jiterator,NewGlobalRef," ")
    it_class=(jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(jiterator) );
    JNI_THROW_ON_ERROR(it_class,NewGlobalRef," ")
  }
  
  void cleanup()
  {
    if (--(*counter) == 0)
    {
      delete counter;
      if (jiterator!=NULL){
        JNU_GetEnv()->DeleteGlobalRef(jiterator);
        JNU_GetEnv()->DeleteGlobalRef(it_class);
        JNU_GetEnv()->DeleteGlobalRef(pt_class);
      }
    }
  }
  
  void copy(const Ref_counted_jdata& source)
  {
    jiterator=source.jiterator;
    it_class=source.it_class;
    pt_class=source.pt_class;
    counter=source.counter;
    ++(*counter);
  }
  
  Ref_counted_jdata(const Ref_counted_jdata& source)
  {
    copy(source);
  }
  
  ~Ref_counted_jdata(){cleanup();}
  
  Ref_counted_jdata& operator=(const Ref_counted_jdata& source)
  {
    if (this!=&source){
      cleanup();
      copy(source);
    }
    return *this;
  }
  
};


template <class Cpp_wrapper,class Cpp_base>
struct Dereference_input_iterator{
  typedef typename boost::mpl::if_<
        boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
        Cpp_base&, Cpp_base
      >::type result_type;
  
  static result_type dereference(Cpp_wrapper* current_ptr) {
    return internal::Converter<Cpp_wrapper>::convert(*current_ptr); 
  }
};

template <class Cpp_wrapper>
struct Dereference_input_iterator<Cpp_wrapper,Cpp_wrapper>{
  typedef Cpp_wrapper& result_type;
  
  static result_type dereference(Cpp_wrapper* current_ptr) {
    return *current_ptr;
  }
};
#endif

template <class Cpp_wrapper,class Cpp_base>
class Input_iterator_wrapper:
public boost::iterator_facade<
    Input_iterator_wrapper<Cpp_wrapper,Cpp_base>,
    Cpp_base,
    boost::single_pass_traversal_tag,
    typename Dereference_input_iterator<Cpp_wrapper,Cpp_base>::result_type//this allows to use a reference for dereference when possible
    >
{
  typedef Dereference_input_iterator<Cpp_wrapper,Cpp_base> Deref;
  friend class boost::iterator_core_access;
  std::string signature;
  Cpp_wrapper* current_ptr;
  jmethodID getCPtr_id, next_id, hasnext_id;
  Ref_counted_jdata rc;
  
  void update_with_next_point(bool first=false){
    if (static_cast<bool> (JNU_GetEnv()->CallBooleanMethod(rc.jiterator,hasnext_id)) )
    {
      jobject jpoint=JNU_GetEnv()->CallObjectMethod(rc.jiterator,next_id);
      if (first){
        rc.pt_class = (jclass) JNU_GetEnv()->NewGlobalRef( JNU_GetEnv()->GetObjectClass(jpoint) );
        JNI_THROW_ON_ERROR(rc.pt_class,NewGlobalRef," ")
        getCPtr_id=JNU_GetEnv()->GetStaticMethodID(rc.pt_class, "getCPtr",signature.c_str());
        JNI_THROW_ON_ERROR(getCPtr_id,GetStaticMethodID,std::string("getCPtr ")+signature)
      }
      assert(getCPtr_id!=NULL);
      assert(rc.pt_class!=NULL);
      jlong jpt=(jlong) JNU_GetEnv()->CallStaticObjectMethod(rc.pt_class,getCPtr_id,jpoint);
      JNI_THROW_ON_ERROR((void*) jpt,CallStaticObjectMethod," ")
      current_ptr = (Cpp_wrapper*) jpt;
      
    }
    else{
      current_ptr=NULL;
    }
  }
  
public:
  

  Input_iterator_wrapper():current_ptr(NULL){}
  Input_iterator_wrapper(const jobject& jiterator_,const char* sign):signature(sign),rc(jiterator_)
  {
    assert(rc.it_class!=NULL);
    hasnext_id=JNU_GetEnv()->GetMethodID(rc.it_class, "hasNext", "()Z");
    JNI_THROW_ON_ERROR(hasnext_id,GetMethodID,"hasNext ()Z");
    next_id=JNU_GetEnv()->GetMethodID(rc.it_class, "next","()Ljava/lang/Object;");
    JNI_THROW_ON_ERROR(next_id,GetMethodID,"next ()Ljava/lang/Object;");
    getCPtr_id=NULL;
    rc.pt_class=NULL;
    update_with_next_point(true);
  }

  
  void increment(){assert(current_ptr!=NULL); update_with_next_point();}
  bool equal(const Input_iterator_wrapper & other) const{ return current_ptr==other.current_ptr; }
  
  typename Deref::result_type dereference() const { return Deref::dereference(current_ptr); }
};



#endif// SWIG_CGAL_JAVA_INPUT_ITERATOR_WRAPPER_H
