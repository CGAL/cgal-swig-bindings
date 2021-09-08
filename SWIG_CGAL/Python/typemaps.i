// ------------------------------------------------------------------------------
// Copyright (c) 2016 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_PYTHON_TYPEMAPS_I
#define SWIG_CGAL_PYTHON_TYPEMAPS_I

//IN typemap for a vector of int from an array of int
%define SWIG_CGAL_array_of_int_to_vector_of_int_typemap_in
%typemap(in) boost::shared_ptr<std::vector< int > > {
  boost::shared_ptr<std::vector< int > > res(new std::vector<int>());
  if (!PySequence_Check($input)) {
          PyErr_SetString(PyExc_ValueError,"Expecting a sequence");
          return nullptr;
  }
  int length=PySequence_Length($input);
  res->reserve(length);
  for (int i=0; i<length;++i){
    PyObject *o = PySequence_GetItem($input,i);
    if (!PyInt_Check(o))
    {
       Py_XDECREF(o);
       PyErr_SetString(PyExc_ValueError,"Expecting a sequence of int");
       return nullptr;
    }
    res->push_back( PyLong_AsLong(o));
    Py_DECREF(o);
  }
  $1=res;
}
%enddef

//IN typemap for a vector of Point_3 from an array of double
%define SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< EPIC_Kernel::Point_3 > > {
  boost::shared_ptr<std::vector< EPIC_Kernel::Point_3 > > res(new std::vector<EPIC_Kernel::Point_3>());
  if (!PySequence_Check($input)) {
          PyErr_SetString(PyExc_ValueError,"Expecting a sequence");
          return nullptr;
  }
  int length=PySequence_Length($input);
  res->reserve(length);
  for (int i=0; i<length; i += 3){
    res->push_back(EPIC_Kernel::Point_3
                   (PyFloat_AsDouble(PySequence_GetItem($input,i)),
                     PyFloat_AsDouble(PySequence_GetItem($input,i+1)),
                     PyFloat_AsDouble(PySequence_GetItem($input,i+2))
                     ));
  }
  $1=res;
}
%enddef

// IN typemap from an array of 9-uple of double to vector of triangles
%define SWIG_CGAL_array_of_array9_of_double_to_vector_of_triangle_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< Triangle_3::cpp_base> > {
	boost::shared_ptr<std::vector< Triangle_3::cpp_base> > res(new std::vector< Triangle_3::cpp_base>());
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return nullptr;
	}
	int length=PySequence_Length($input);
	for (int l=0; l<length; l++) {          
		PyObject* point = PySequence_GetItem($input, l);

		if (PySequence_Length(point) != 9) {
		  PyErr_SetString(PyExc_ValueError,"Expect 9 floats per triangle");
		  return nullptr;
		}

		const EPIC_Kernel::Point_3 p( 
		  PyFloat_AsDouble(PySequence_GetItem(point,0)),
		  PyFloat_AsDouble(PySequence_GetItem(point,1)),
		  PyFloat_AsDouble(PySequence_GetItem(point,2))
		);
		const EPIC_Kernel::Point_3 q( 
		  PyFloat_AsDouble(PySequence_GetItem(point,3)),
		  PyFloat_AsDouble(PySequence_GetItem(point,4)),
		  PyFloat_AsDouble(PySequence_GetItem(point,5))
		);
		const EPIC_Kernel::Point_3 r( 
		  PyFloat_AsDouble(PySequence_GetItem(point,6)),
		  PyFloat_AsDouble(PySequence_GetItem(point,7)),
		  PyFloat_AsDouble(PySequence_GetItem(point,8))
		);

		res->push_back(EPIC_Kernel::Triangle_3(p, q, r));
		Py_DECREF(point);
	}
	$1=res;
}
%enddef

// IN typemap from an array of 6-uple of double to vector of triangles
%define SWIG_CGAL_array_of_array6_of_double_to_vector_of_segment_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< Segment_3::cpp_base> > {
	boost::shared_ptr<std::vector< Segment_3::cpp_base> > res(new std::vector< Segment_3::cpp_base>());
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return nullptr;
	}
    int length=PySequence_Length($input);
	for (int l=0; l<length; l++) {          
		PyObject* point = PySequence_GetItem($input, l);

		if (PySequence_Length(point) != 6) {
		  PyErr_SetString(PyExc_ValueError,"Expect 6 floats per segment");
		  return nullptr;
		}

		const EPIC_Kernel::Point_3 p( 
		  PyFloat_AsDouble(PySequence_GetItem(point,0)),
		  PyFloat_AsDouble(PySequence_GetItem(point,1)),
		  PyFloat_AsDouble(PySequence_GetItem(point,2))
		);
		const EPIC_Kernel::Point_3 q( 
		  PyFloat_AsDouble(PySequence_GetItem(point,3)),
		  PyFloat_AsDouble(PySequence_GetItem(point,4)),
		  PyFloat_AsDouble(PySequence_GetItem(point,5))
		);

		res->push_back(EPIC_Kernel::Segment_3(p, q));
		Py_DECREF(point);
	}
	$1=res;
}
%enddef

//OUT typemap for vector of int to an array of int
%define SWIG_CGAL_vector_of_int_to_array_of_int_typemap_out
%typemap(out) boost::shared_ptr<std::vector< int > > {
  PyObject* list = PyList_New($1->size());
  for (std::size_t i=0;i<$1->size();++i){
    PyObject* py_object=PyInt_FromLong((*$1)[i]);
    assert(py_object!=nullptr);
    PyList_SetItem(list, i, py_object);
    Py_DECREF(py_object);
  }
  $result=list;
}
%enddef

//OUT typemap for vector of string to an array of string
%define SWIG_CGAL_vector_of_string_to_array_of_string_typemap_out
%typemap(out) boost::shared_ptr<std::vector< std::string > > {
  PyObject* list = PyList_New($1->size());
  for (std::size_t i=0;i<$1->size();++i){
    PyObject* py_object=PyUnicode_FromString((*$1)[i].c_str());
    assert(py_object!=nullptr);
    PyList_SetItem(list, i, py_object);
  }
  $result=list;
}
%enddef

%define SWIG_CGAL_python_vector_of_int_typecheck
%typemap(typecheck,precedence=0) boost::shared_ptr<std::vector< int > > {
  if (PySequence_Check($input) && PySequence_Length($input)!=0)
  {
    PyObject *o = PySequence_GetItem($input,0);
    if (PyInt_Check(o))
    {
       Py_DECREF(o);
      $1=1;
    }
    else{
      Py_XDECREF(o);
      $1=0;
    }
  }
  else $1=0;
}
%enddef

#endif // SWIG_CGAL_PYTHON_TYPEMAPS_I
