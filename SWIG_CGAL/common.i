// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

%define SWIG_CGAL_declare_identifier_of_template_class(Prefix,Type ... )
%inline %{ typedef Type  Prefix##_SWIG_wrapper; %}
%define SWIG_CGAL_import_##Prefix##_SWIG_wrapper
%inline %{typedef Type  Prefix##_SWIG_wrapper; %}
%enddef
%define  Prefix##_SWIG_wrapper_for_typemap Type %enddef
%template (Prefix) Type;
%enddef

%define SWIG_CGAL_add_java_loadLibrary_CGAL_Java()
  %pragma(java) jniclasscode=%{
    static{
      try {
          System.loadLibrary("CGAL_Java");
      } catch (UnsatisfiedLinkError e) {
        System.err.println("Native code library CGAL_Java failed to load. \n" + e);
        throw e;
      }
    }
  %}      
%enddef

%define SWIG_CGAL_add_java_loadLibrary(NAME)
  %pragma(java) jniclasscode=%{
    static {
      try {
          System.loadLibrary("NAME");
      } catch (UnsatisfiedLinkError e) {
        System.err.println("Native code library NAME failed to load. \n" + e);
        throw e;
      }
    }
  %}
  // always load CGAL_Java to get JNI_OnLoad called
  SWIG_CGAL_add_java_loadLibrary_CGAL_Java()  
%enddef

// general macro that defines useful instructions for all packages
#ifdef SWIG_CGAL_NO_FINALIZE
  %define SWIG_CGAL_package_common()
    %typemap(javafinalize) SWIGTYPE ""
  %enddef
#else
  %define SWIG_CGAL_package_common()
  %enddef
#endif

//macro function to define proper java iterators
#ifdef SWIGJAVA
#if SWIG_VERSION > 0x020005
  //2011-11-25: wsfulton  visibility is now back to protected by default!
  SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
  SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
#endif
//this one is specific to iterator of int, double, ...
%define SWIG_CGAL_set_as_java_iterator_non_class(Iterator_type,Object_type)
  %typemap(javaimports) Iterator_type
  %{
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;
  %}
  
  %typemap(javainterfaces) Iterator_type %{  Iterable<Object_type>, Iterator<Object_type> %}

  %typemap(javacode) Iterator_type
  %{
    public void remove() {
      throw new UnsupportedOperationException();
    }
    
    public Iterator<Object_type> iterator() {
      return this;
    }

    public Object_type next() {
      return slow_next();
    }
  %}
%enddef
  
%define SWIG_CGAL_set_as_java_iterator(Iterator_type,Object_type,Extra_import)
  %typemap(javaimports) Iterator_type
  %{
  Extra_import
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;
  %}
  
  %typemap(javainterfaces) Iterator_type %{  Iterable<Object_type>, Iterator<Object_type> %}

  %typemap(javacode) Iterator_type
  %{
    public void remove() {
      throw new UnsupportedOperationException();
    }
    
    public Iterator<Object_type> iterator() {
      return this;
    }
    
    //we store an object of type Object_type to avoid
    //creation and allocation of a java object at each iteration.
    private Object_type objectInstance = new Object_type();
    public Object_type next() {
      next(objectInstance);
      return objectInstance;
    }
  %}
%enddef
#else
%define SWIG_CGAL_set_as_java_iterator(Iterator_type,Object_type,Extra_import)
%enddef
%define SWIG_CGAL_set_as_java_iterator_non_class(Iterator_type,Object_type)
%enddef
#endif

//input iterator typemap
//   Object_typemap_       is the object on which the typemap should be defined (used in the cpp code)
//   Out_Object_           is the object wrapped by swig that is obtained when calling *
//   Out_JAVA              the name of the wrapped Out_Object_ in java
//   Out_Object_cpp_base_  is the CGAL cpp type associated to Out_Object_
//   SWIG_for_python_      python specific Out_Object_ class id
//   SWIG_for_java_        java specific class name (should be a string)
//   Function_name_        python specific: name of the function using the input_iterator
#ifdef SWIGPYTHON
%define SWIG_CGAL_input_iterator_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_,Function_name_)
  %typemap(in) Object_typemap_ {
    try{
      Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_end;
      Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_begin($input,SWIG_for_python_);
      $1=std::make_pair(it_begin,it_end);
    }
    catch(Bad_element_type){
      SWIG_fail;
    }
    catch(Not_an_iterator){
      SWIG_fail;
    }
  }

  %include exception.i
  %exception Function_name_
  {
    try{
        $action
      }
      catch(Bad_element_type){
        //TODO: throw a specify exception
        //TODO add a message to specify that the list does not contains only points
        SWIG_fail;
      }
  }
  //check that the input is an iterator
  %typemap(typecheck,precedence=0) Object_typemap_ {
    PyObject* iter=PyObject_GetIter($input);
    if (iter!=NULL){
      Py_DECREF(iter);
      $1=1;
    }
    else $1=0;
  }
  
%enddef  
#endif
#ifdef SWIGJAVA
%define SWIG_CGAL_input_iterator_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_,Function_name_)
  %typemap(jni) Object_typemap_ "jobject"  //replace in jni class
  %typemap(jtype) Object_typemap_ "Iterator<Out_JAVA>"   //replace in java wrapping class
  %typemap(jstype) Object_typemap_ "Iterator<Out_JAVA>"  //replace in java function args
  %typemap(javain) Object_typemap_ "$javainput" //replace in java function call to wrapped function

  %typemap(in) Object_typemap_ {
    Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_end;
    Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_begin($input,SWIG_for_java_);
    $1=std::make_pair(it_begin,it_end);
  }
%enddef
#endif
  
#ifdef SWIGJAVA
%{
  #include <SWIG_CGAL/Java/exception.h>
%}
%include exception.i
%exception
{
  try{
      $action
  }
  catch(std::exception& e){
    std::string error_msg("Error in SWIG_CGAL code. Here is the text of the C++ exception:\n");
    error_msg += e.what();
    if ( !throwJavaException(error_msg.c_str()) )
      throw; //rethrow exception that could not be thrown in java
  }
  catch(...){
    if ( !throwJavaException("Unknown error in SWIG_CGAL code") )
      throw; //rethrow exception that could not be thrown in java
  }
}
#endif
  
  
//-----
#ifdef SWIGPYTHON
//Add extra exception handling for function using an input_iterator as input
//   Function_name_   :     python specific: name of the function
%define SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Function_name_)
%include exception.i
%exception Function_name_
{
  try{
      $action
    }
    catch(Bad_element_type){
      SWIG_fail;
    }
}
%enddef

%exception {
   try {
      $action
   } catch (std::exception &e) {
      std::string error_msg("Error in SWIG_CGAL code. Here is the text of the C++ exception:\n");
      error_msg += e.what();
      PyErr_SetString(PyExc_Exception, error_msg.c_str());
      SWIG_fail;
   }
}

#endif  

//output iterator typemap
//   Object_typemap_       is the object on which the typemap should be defined (used in the cpp code)
//   Out_Object_           is the object wrapped by swig that is obtained when calling *
//   Out_JAVA              is the name of the wrapped Out_Object_ in java
//   Out_Object_cpp_base_  is the CGAL cpp type associated to Out_Object_
//   SWIG_for_python_      python specific Out_Object_ class id
//   SWIG_for_java_        java specific class name (should be a string)
#ifdef SWIGPYTHON
%define SWIG_CGAL_output_iterator_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_)
  %typemap(in) Object_typemap_ {
    try{
      $1=boost::make_function_output_iterator( Container_writer<Out_Object_,Out_Object_cpp_base_>($input,SWIG_for_python_) );
    }
    catch(Not_a_list){
      SWIG_fail;
    }
  }
  //check that the input is a list
  %typemap(typecheck,precedence=0) Object_typemap_ {
    $1 = PyList_Check($input) ? 1 : 0;
  }
%enddef
#endif
#ifdef SWIGJAVA
%define SWIG_CGAL_output_iterator_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_)
  %typemap(jni) Object_typemap_ "jobject"  //replace in jni class
  %typemap(jtype) Object_typemap_ "Collection<Out_JAVA>"   //replace in java wrapping class
  %typemap(jstype) Object_typemap_ "Collection<Out_JAVA>"  //replace in java function args
  %typemap(javain) Object_typemap_ "$javainput" //replace in java function call to wrapped function

  %typemap(in) Object_typemap_ {
    $1=boost::make_function_output_iterator( Container_writer<Out_Object_,Out_Object_cpp_base_>($input,SWIG_for_java_) );
  }
%enddef
#endif
//-----

//exception for iterators (for next functions)
#ifdef SWIGPYTHON
%include exception.i
%exception next
{
  try{
      $action
    }
    catch(Stop_iteration){//TODO: throw a specify exception
      SWIG_SetErrorObj(PyExc_StopIteration, SWIG_Py_Void());
      SWIG_fail;
    }
}

%exception __next__
{
  try{
      $action
    }
    catch(Stop_iteration){//TODO: throw a specify exception
      SWIG_SetErrorObj(PyExc_StopIteration, SWIG_Py_Void());
      SWIG_fail;
    }
}
#endif

//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

#ifdef SWIGJAVA
%rename(clone) deepcopy;
#endif


%include "std_string.i"

#ifdef SWIGPYTHON
%rename(__str__) toString; //print overloading in python using java
#endif

//operator renaming for languages that does not support them
#ifdef SWIGJAVA
%rename(plus) operator+;
%rename(minus) operator-;
%rename(times) operator*;
%rename(div) operator/;
%rename(iplus) operator+=;
%rename(iminus) operator-=;
%rename(itimes) operator*=;
%rename(idiv) operator/=;
%rename(equals) operator==;
%rename(not_equals) operator!=;
%rename(lt) operator<;
%rename(le) operator<=;
%rename(gt) operator>;
%rename(ge) operator>=;
#endif

#ifdef SWIGPYTHON
%rename (__hash__) hashCode;
#endif


//macro for defining void DECL macro for swig parsing
%define Decl_void_type()
#define SWIG_CGAL_JAVA_DECL
#define SWIG_CGAL_KERNEL_DECL
#define SWIG_CGAL_AABB_TREE_DECL
%enddef



//For non supported target languages

//Macro to declare pseudo output iterator.
//--GenericOutputIterator is the name exposed in the target language of the container that mimic the cpp output iterator
//--GenericIterator is the name exposed in the target language of the nested iterator of the previous class
//--Object is the object type the output iterator is supposed to collect (from the target language point of view)
%define SWIG_CGAL_declare_generic_output_iterator(GenericOutputIterator,GenericIterator,Object)
  %template (GenericIterator) SWIG_CGAL_Iterator<std::vector< Generic_output_iterator< Object >::Cpp_object>::iterator,Object >;
  %template (GenericOutputIterator) Generic_output_iterator< Object >;
%enddef

//do not generate a constant in the target language
%ignore SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE;

#if !defined(SWIGPYTHON) && !defined(SWIGJAVA)
  #define SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE 1
#else
  #define SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE 0
#endif



%{
#if !defined(SWIGPYTHON) && !defined(SWIGJAVA)
  #define SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE 1
#else
  #define SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE 0
#endif  
%}

#if SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define SWIG_CGAL_output_iterator_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_)
%enddef
#endif


//typemaps to ease SWIG to handle correctly input and output iterator declared using Wrapper_iterator_helper class
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%include "SWIG_CGAL/Common/Macros.h"
//typemap for input iterator
%define SWIG_CGAL_set_wrapper_iterator_helper_input(WRAPPER)
  SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<WRAPPER>::input,WRAPPER,WRAPPER,internal::Converter<WRAPPER>::result_type,SWIGTYPE_p_##WRAPPER,"(LCGAL/Kernel/"#WRAPPER";)J",insert)
%enddef
//typemap for output iterator
%define SWIG_CGAL_set_wrapper_iterator_helper_output(WRAPPER)
  SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<WRAPPER>::output,WRAPPER,WRAPPER,internal::Converter<WRAPPER>::result_type,SWIGTYPE_p_##WRAPPER,"LCGAL/Kernel/"#WRAPPER";")
%enddef
#else
//nothing need to be done for input iterator
%define SWIG_CGAL_set_wrapper_iterator_helper_input(WRAPPER)
%enddef
//output iterator
%define SWIG_CGAL_set_wrapper_iterator_helper_output(WRAPPER)
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(WRAPPER##_output_iterator,WRAPPER##_output_iterator_nested_iterator,WRAPPER)
%enddef
#endif

