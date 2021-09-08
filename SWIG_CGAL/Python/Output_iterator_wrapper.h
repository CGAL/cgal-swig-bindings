// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_PYTHON_OUTPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

#include <boost/iterator/function_output_iterator.hpp>
#include <SWIG_CGAL/Python/exceptions.h>

template<class Cpp_wrapper,class Cpp_base>
class Container_writer{
  PyObject* list;
  swig_type_info* type;
  
public:

  Container_writer(){}
  Container_writer(PyObject * list_,swig_type_info* type_):list(list_),type(type_)
  {
    // CGAL_precondition(PyList_Check(list)); //properly handle by a typecheck in SWIG macro
    //only for function with overload !!!
    if (!PyList_Check(list)){
      SWIG_SetErrorMsg(PyExc_TypeError, "Not a List.");
      throw Not_a_list();
    }    
  }
 
  void operator()(const Cpp_base& new_base) {
    Cpp_base* result = new Cpp_base(new_base);
    PyObject* py_object= SWIG_NewPointerObj(SWIG_as_voidptr(result), type, 1);
    assert(py_object!=nullptr);
    PyList_Append(list,py_object);
    Py_DECREF(py_object);
  }
};

template<>
class Container_writer<int,int>{
  PyObject* list;
  
public:

  Container_writer(){}
  Container_writer(PyObject * list_,swig_type_info*):list(list_)
  {
    // CGAL_precondition(PyList_Check(list)); //properly handle by a typecheck in SWIG macro
    //only for function with overload !!!
    if (!PyList_Check(list)){
      SWIG_SetErrorMsg(PyExc_TypeError, "Not a List.");
      throw Not_a_list();
    }    
  }
 
  void operator()(int new_base) {
    
    PyObject* py_object=PyInt_FromLong(new_base);
    assert(py_object!=nullptr);
    PyList_Append(list,py_object);
    Py_DECREF(py_object);
  }
};

#endif// SWIG_CGAL_PYTHON_OUTPUT_ITERATOR_WRAPPER_H

