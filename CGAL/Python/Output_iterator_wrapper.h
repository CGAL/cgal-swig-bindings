#ifndef CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H
#define CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

#include "global_functions.h"

template<class Cpp_wrapper,class Cpp_base>
class Container_writer{
  PyObject* list;
  swig_type_info* type;
  
public:

  Container_writer(){}
  Container_writer(PyObject * list_,swig_type_info* tinfo):list(list_),type(tinfo)
  {
    if (!PyList_Check(list)) { //not a list
      current_ptr=NULL;
      PyErr_SetString(PyExc_TypeError, "Not a list.");
      throw 1;
      return;
    }
  }
 
  void operator()(const Cpp_base& new_base) {

  }
};



#endif// CGAL_SWIG_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

