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
%define Iterator_for_java(Iterator_type,Object_type,Extra_import)
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
  %}
%enddef

%define Add_info(Class_name,Info_type)
  %typemap(javacode) Class_name
  %{
    public void setInfo(Info_type i) {
      setInfo_i( (Object) i);
    }
    
    public Info_type getInfo(){
      return (Info_type) getInfo_i();
    }
  %}
%enddef

#else
%define Iterator_for_java(Iterator_type,Object_type,Extra_import)
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
%define Typemap_for_Input_iterator(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_,Function_name_)
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
%define Typemap_for_Input_iterator(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_,Function_name_)
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
//-----
#ifdef SWIGPYTHON
//Add extra exception handling for function using an input_iterator as input
//   Function_name_   :     python specific: name of the function
%define Typemap_for_Input_iterator_additional_function(Function_name_)
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
%define Typemap_for_Output_iterator(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_)
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
%define Typemap_for_Output_iterator(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_)
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
%rename(set_equal) operator=;
#endif


%include "std_string.i"

//RENAMING
#ifdef SWIGPYTHON
%rename(__str__) toString; //print overloading in python using java
%rename(__eq__)  equals;   //equalily overloading in python using java
#endif