//this is the default with SWIG2
//The intermediary JNI class modifiers are now public by default meaning these
//intermediary low level functions are now accessible by default from outside any package
//used. The proxy class pointer constructor and getCPtr() methods are also now public.
//These are needed in order for the nspace option to work without any other mods.
#ifdef SWIGJAVA
SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)
#endif

//macro function to define proper java iterators
#ifdef SWIGJAVA
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
    private Object_type objectInstance = new Object_Default_Constructor;
    public Object_type next() {
      next(objectInstance);
      return objectInstance;
    }
  %}
%enddef
#else
%define SWIG_CGAL_set_as_java_iterator(Iterator_type,Object_type,Extra_import)
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
    catch(Bad_list_element){
      SWIG_fail;
    }
    catch(Not_a_list){
      SWIG_fail;
    }
  }

  %include exception.i
  %exception Function_name_
  {
    try{
        $action
      }
      catch(Bad_list_element){
        //TODO: throw a specify exception
        //TODO add a message to specify that the list does not contains only points
        SWIG_fail;
      }
  }
  //check that the input is a list
  %typemap(typecheck) Object_typemap_ {
    $1 = PyList_Check($input) ? 1 : 0;
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
    catch(Bad_list_element){
      SWIG_fail;
    }
}
%enddef
#endif  

//output iterator typemap
//   Object_typemap_       is the object on which the typemap should be defined (used in the cpp code)
//   Out_Object_           is the object wrapped by swig that is obtained when calling *
//   Out_JAVA              is the name of the wrapped Out_Object_ in java
//   Out_Object_cpp_base_  is the CGAL cpp type associated to Out_Object_
//   SWIG_for_python_      python specific Out_Object_ class id
//   SWIG_for_java_        java specific class name (should be a string)
//   Function_name_        python specific: name of the function using the input_iterator
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
  %typemap(typecheck) Object_typemap_ {
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

//exception for iterators (for next fonctions)
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

//RENAMING
#ifdef SWIGPYTHON
%rename(__str__) toString; //print overloading in python using java
%rename(__eq__)  equals;   //equalily overloading in python using java
#endif

//macro for defining void DECL macro for swig parsing
%define Decl_void_type()
#define SWIG_CGAL_JAVA_DECL
#define SWIG_CGAL_KERNEL_DECL
#define SWIG_CGAL_AABB_TREE_DECL
%enddef
