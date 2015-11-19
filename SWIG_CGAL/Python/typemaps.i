// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_PYTHON_TYPEMAPS_I
#define SWIG_CGAL_PYTHON_TYPEMAPS_I

%define SWIG_CGAL_array_of_array9_of_double_to_vector_of_triangle_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< Triangle_3::cpp_base> > {
	boost::shared_ptr<std::vector< Triangle_3::cpp_base> > res(new std::vector< Triangle_3::cpp_base>());
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return NULL;
	}
	int length=PySequence_Length($input);
	for (int l=0; l<length; l++) {          
		PyObject* point = PySequence_GetItem($input, l);

		if (PySequence_Length(point) != 9) {
		  PyErr_SetString(PyExc_ValueError,"Expect 9 floats per triangle");
		  return NULL;
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

%define SWIG_CGAL_array_of_array6_of_double_to_vector_of_segment_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< Segment_3::cpp_base> > {
	boost::shared_ptr<std::vector< Segment_3::cpp_base> > res(new std::vector< Segment_3::cpp_base>());
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return NULL;
	}
    int length=PySequence_Length($input);
	for (int l=0; l<length; l++) {          
		PyObject* point = PySequence_GetItem($input, l);

		if (PySequence_Length(point) != 6) {
		  PyErr_SetString(PyExc_ValueError,"Expect 6 floats per segment");
		  return NULL;
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

#endif //SWIG_CGAL_PYTHON_TYPEMAPS_I
