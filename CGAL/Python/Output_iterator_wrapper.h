#ifndef CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H
#define CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

template<class Cpp_wrapper,class Cpp_base>
class Container_writer{
  PyObject* list;
  swig_type_info* type;
  
public:

  Container_writer(){}
  Container_writer(PyObject * list_,swig_type_info* type_):list(list_),type(type_)
  {
    if (!PyList_Check(list)) { //not a list
      PyErr_SetString(PyExc_TypeError, "Not a list.");
      throw 1;
      return;
    }
  }
 
  void operator()(const Cpp_base& new_base) {
    Cpp_base* result = new Cpp_base(new_base);
    PyObject* py_object= SWIG_NewPointerObj(SWIG_as_voidptr(result), type, 1);
    assert(py_object!=NULL);
    PyList_Append(list,py_object);
  }
};



#endif// CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

