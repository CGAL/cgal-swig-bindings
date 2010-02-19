//macro function to define proper java iterators
#ifdef SWIGJAVA
%define Iterator_for_java(Iterator_type,Object_type)
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
%define Iterator_for_java(Iterator_type,Object_type)
%enddef
#endif

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