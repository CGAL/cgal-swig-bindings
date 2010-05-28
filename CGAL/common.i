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
//   Out_Object_      is the object wrapper by swig that is obtained when calling *
//   Object_typemap_     is the object on which the typemap should be defined (used in the cpp code)
//   SWIG_for_python_ python specific Out_Object_ class id
//   SWIG_for_java_   java specific class name (should be a string)
//   Function_name    python specific: name of the function using the input_iterator
#ifdef SWIGPYTHON
%define Typemap_for_Input_iterator(Object_typemap_,Out_Object_,SWIG_for_python_,SWIG_for_java_,Function_name_)
  %typemap(in) Object_typemap_ {
    try{
      Input_iterator_wrapper<Out_Object_,Out_Object_::cpp_base> it_end;
      Input_iterator_wrapper<Out_Object_,Out_Object_::cpp_base> it_begin($input,SWIG_for_python_);
      $1=std::make_pair(it_begin,it_end);
    }
    catch(int){
      //TODO: throw a specify exception
      SWIG_fail;
    }
  }

  %include exception.i
  %exception Function_name_
  {
    try{
        $action
      }
      catch(int){
        //TODO: throw a specify exception
        //TODO add a message to specify that the list does not contains only points
        SWIG_fail;
      }
  }
%enddef  
#endif
#ifdef SWIGJAVA
%define Typemap_for_Input_iterator(Object_typemap_,Out_Object_,SWIG_for_python_,SWIG_for_java_,Function_name_)
  %typemap(jni) Object_typemap_ "jobject"  //replace in jni class
  %typemap(jtype) Object_typemap_ "Iterator<Out_Object_>"   //replace in java wrapping class
  %typemap(jstype) Object_typemap_ "Iterator<Out_Object_>"  //replace in java function args
  %typemap(javain) Object_typemap_ "$javainput" //replace in java function call to wrapped function

  %typemap(in) Object_typemap_ {
    Input_iterator_wrapper<Out_Object_,Out_Object_::cpp_base> it_end;
    Input_iterator_wrapper<Out_Object_,Out_Object_::cpp_base> it_begin($input,SWIG_for_java_);
    $1=std::make_pair(it_begin,it_end);
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
    catch(int){//TODO: throw a specify exception
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