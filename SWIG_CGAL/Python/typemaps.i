// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_PYTHON_TYPEMAPS_I
#define SWIG_CGAL_PYTHON_TYPEMAPS_I

%define SWIG_CGAL_array_of_array_of_double_to_vector_of_triangle_3_typemap_in
%typemap(in) boost::shared_ptr<std::vector< EPIC_Kernel::Triangle_3> > (double temp[$1_dim0][$1_dim1]) {
	boost::shared_ptr<std::vector< EPIC_Kernel::Triangle_3> > res(new std::vector< EPIC_Kernel::Triangle_3>());
	int l;
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return NULL;
	}
	if (PySequence_Length($input) != $1_dim0) {
		PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected $1_dim0 elements");
		return NULL;
	}
	if ($1_dim1 != 9) {
		PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected $1_dim1 elements");
		return NULL;
	}		
	for (l=0; l<$1_dim0; l++) {
		PyObject *points = PySequence_GetItem($input, l);		
		const EPIC_Kernel::Point_3& p = PySequence_GetSlice(points, 0, 3);
		const EPIC_Kernel::Point_3& q = PySequence_GetSlice(points, 3, 6);
		const EPIC_Kernel::Point_3& r = PySequence_GetSlice(points, 6, 9);
		res->push_back(EPIC_Kernel::Triangle_3(p, q, r));
		Py_DECREF(points);
	}
	$1=res;
}
%enddef


%define SWIG_CGAL_array_of_array_of_double_to_iterator_of_vector_of_triangle_3_typemap_in(Object_typemap_,Out_Object_,Out_JAVA,Out_Object_cpp_base_,SWIG_for_python_,SWIG_for_java_,Function_name_)
  %typemap(in) Object_typemap_ (double temp[$1_dim0][$1_dim1]) {
    boost::shared_ptr<std::vector< EPIC_Kernel::Triangle_3> > res(new std::vector< EPIC_Kernel::Triangle_3>());
    int l;
    if (!PySequence_Check($input)) {
      PyErr_SetString(PyExc_ValueError,"Expected a sequence");
      return NULL;
    }
    if (PySequence_Length($input) != $1_dim0) {
      PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected $1_dim0 elements");
      return NULL;
    }
    if ($1_dim1 != 9) {
      PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected $1_dim1 elements");
      return NULL;
    }		
    for (l=0; l<$1_dim0; l++) {
      PyObject *points = PySequence_GetItem($input, l);		
      const EPIC_Kernel::Point_3& p = PySequence_GetSlice(points, 0, 3);
      const EPIC_Kernel::Point_3& q = PySequence_GetSlice(points, 3, 6);
      const EPIC_Kernel::Point_3& r = PySequence_GetSlice(points, 6, 9);
      res->push_back(EPIC_Kernel::Triangle_3(p, q, r));
      Py_DECREF(points);
    }
    try{
      Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_end;
      Input_iterator_wrapper<Out_Object_,Out_Object_cpp_base_> it_begin(res,SWIG_for_python_);
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
    PyObject* iter=PyObject_GetIter($1);
    if (iter!=NULL){
      Py_DECREF(iter);
      $1=1;
    }
    else $1=0;
  }
%enddef

/*
//IN typemap for reading vector of triangles from an array of array of double
%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in_advanced(KERNEL)
%typemap(in) boost::shared_ptr<std::vector< std::vector<KERNEL::Triangle_3> > > {
  boost::shared_ptr<std::vector< std::vector<KERNEL::Triangle_3> > > res(new std::vector< std::vector<KERNEL::Triangle_3> >());
  
//  const jsize size_of_lines = jenv->GetArrayLength($input);
  res->resize(size_of_lines);
  
//  jboolean is_copy;
  
  for (jsize l=0; l<size_of_lines; ++l){
//    jdoubleArray line = (jdoubleArray) jenv->GetObjectArrayElement($input,l);
    
//    const jsize size = jenv->GetArrayLength(line) / 3;
    (*res)[l].reserve((const std::size_t) size);
//    jdouble* triangle = jenv->GetDoubleArrayElements(line, &is_copy);

    for (int i=0; i<size; i++){
      (*res)[l].push_back(KERNEL::Triangle_3(triangle[i*3],triangle[i*3+1],triangle[i*3+2]));
    }
//    jenv->ReleaseDoubleArrayElements(line, triangles, JNI_ABORT);
  }
  $1=res;



    flist = PySequence_Fast(list, "This is not a sequence");

    if ((! flist) || (imax <= 2))
		PyErr_SetString(PyExc_TypeError, "Invalid number of points");
        return NULL;

    vl = PyMem_New(gpc_vertex_list, 1);
    vl->num_vertices = imax;
    vl->vertex = v = PyMem_New(gpc_vertex, imax);

    for (i=0; i<imax; i++) {
        point = PySequence_Fast(PySequence_Fast_GET_ITEM(flist, i), "this is not a point");
        if ((!point) || (PySequence_Length(point) != 2))
            return Polygon_Raise(ERR_INV);
        v->x = PyFloat_AsDouble(X = PyNumber_Float(PySequence_Fast_GET_ITEM(point, 0)));
        v->y = PyFloat_AsDouble(Y = PyNumber_Float(PySequence_Fast_GET_ITEM(point, 1)));
        v++;
        Py_DECREF(X);
        Py_DECREF(Y);
        Py_DECREF(point);
    }
    Py_DECREF(flist);


}
%enddef
%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in
SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in_advanced(EPIC_Kernel)
%enddef


	for (l=0; l<$1_dim0; l++) {
		PyObject *points = PySequence_GetItem($input, l);
		for (i=0; i<9; i++) {
			if (PyNumber_Check(points[i])) {
				temp[i] = (float) PyFloat_AsDouble(triangle);
				(*res)[l].push_back(KERNEL::Triangle_3(points[i*3],points[i*3+1],points[i*3+2]));
			} else {
				PyErr_SetString(PyExc_ValueError,"Sequence elements must be numbers");
				return NULL;
			}
		}
	}
	$1 = temp;
}

%typemap(in) float value[ANY] {
	int i;
	if (!PySequence_Check($input)) {
		PyErr_SetString(PyExc_ValueError,"Expected a sequence");
		return NULL;
	}
	if (PySequence_Length($input) != $1_dim0) {
		PyErr_SetString(PyExc_ValueError,"Size mismatch. Expected $1_dim0 elements");
		return NULL;
	}
	$1 = (float *) malloc($1_dim0*sizeof(float));
	for (i = 0; i < $1_dim0; i++) {
		PyObject *o = PySequence_GetItem($input,i);
		if (PyNumber_Check(o)) {
			$1[i] = (float) PyFloat_AsDouble(o);
		} else {
			PyErr_SetString(PyExc_ValueError,"Sequence elements must be numbers");
			free($1);
			return NULL;
		}
	}
}
%typemap(freearg) float value[ANY] {
	if ($1) free($1);
}

//IN typemap for reading vector of triangles from an array of array of double
%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in_advanced(KERNEL)
%typemap(in) boost::shared_ptr<std::vector< std::vector<KERNEL::Triangle_3> > > {
  boost::shared_ptr<std::vector< std::vector<KERNEL::Triangle_3> > > res(new std::vector< std::vector<KERNEL::Triangle_3> >());
  
//  const jsize size_of_lines = jenv->GetArrayLength($input);
  res->resize(size_of_lines);
  
//  jboolean is_copy;
  
  for (jsize l=0; l<size_of_lines; ++l){
//    jdoubleArray line = (jdoubleArray) jenv->GetObjectArrayElement($input,l);
    
//    const jsize size = jenv->GetArrayLength(line) / 3;
    (*res)[l].reserve((const std::size_t) size);
//    jdouble* triangle = jenv->GetDoubleArrayElements(line, &is_copy);

    for (int i = 0 ; i < size ; i++){
      (*res)[l].push_back(KERNEL::Triangle_3(triangle[i*3],triangle[i*3+1],triangle[i*3+2]));
    }
//    jenv->ReleaseDoubleArrayElements(line, triangles, JNI_ABORT);
  }
  $1=res;


	gpc_vertex_list *vl;
    PyObject *list=NULL, *flist, *point=NULL, *X, *Y;
    PyObject *list=NULL, *flist, *point=NULL, *X, *Y;
    PyObject *list=NULL, *flist, *point=NULL, *X, *Y;
    PyObject *list=NULL, *flist, *point=NULL, *X, *Y;
    gpc_vertex *v;
    int i, imax;
    if (! PyArg_ParseTuple($input, "O|O", &plist, &flist))
		PyErr_SetString(PyExc_TypeError, "Wrong number or type of arguments");
        return NULL;

    if (! PySequence_Check(list))
		PyErr_SetString(PyExc_TypeError, "Wrong number or type of arguments");
        return NULL;

    flist = PySequence_Fast(list, "This is not a sequence");
	imax = PySequence_Length(flist)

    if ((! flist) || (imax <= 2))
		PyErr_SetString(PyExc_TypeError, "Invalid number of points");
        return NULL;

    vl = PyMem_New(gpc_vertex_list, 1);
    vl->num_vertices = imax;
    vl->vertex = v = PyMem_New(gpc_vertex, imax);

    for (i=0; i<imax; i++) {
        point = PySequence_Fast(PySequence_Fast_GET_ITEM(flist, i), "this is not a point");
        if ((!point) || (PySequence_Length(point) != 2))
            return Polygon_Raise(ERR_INV);
        v->x = PyFloat_AsDouble(X = PyNumber_Float(PySequence_Fast_GET_ITEM(point, 0)));
        v->y = PyFloat_AsDouble(Y = PyNumber_Float(PySequence_Fast_GET_ITEM(point, 1)));
        v++;
        Py_DECREF(X);
        Py_DECREF(Y);
        Py_DECREF(point);
    }
    Py_DECREF(flist);


}
%enddef

%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in
SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_triangle_3_typemap_in_advanced(EPIC_Kernel)
%enddef
*/
#endif //SWIG_CGAL_PYTHON_TYPEMAPS_I
