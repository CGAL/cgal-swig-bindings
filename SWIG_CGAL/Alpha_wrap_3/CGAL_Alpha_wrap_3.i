// ------------------------------------------------------------------------------
// Copyright (c) 2022 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

%define AW3_DOCSTRING
"SWIG wrapper for the CGAL 3D Alpha Wrapping provided under the GPL-3.0+ license"
%enddef
%module (package="CGAL", docstring=AW3_DOCSTRING) CGAL_Alpha_wrap_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Alpha_wrap_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

//include files
%{
  #include <SWIG_CGAL/Common/Iterator.h>
  #include <SWIG_CGAL/Polyhedron_3/all_includes.h>
  #include <SWIG_CGAL/Alpha_wrap_3/all_includes.h>
%}

%pragma(java) jniclassimports=
%{
import java.util.Iterator;
import java.util.Collection;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Kernel.Point_3;
%}

%pragma(java) moduleimports=%{
import java.util.Iterator;
import java.util.Collection;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Kernel.Point_3;
%};

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//import Polyhedron_3 wrapper types
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper

%include "std_vector.i"
%typemap(javaimports) std::vector<Point_3>
%{ import CGAL.Kernel.Point_3; %}

%template(Point_3_Vector) std::vector<Point_3>;
%template(Int_Vector) std::vector<int>;
%template(Polygon_Vector) std::vector< std::vector<int> >;


// %types(Point_3*,Point_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated
// typemaps for input iterators
SWIG_CGAL_set_wrapper_iterator_helper_input(Point_3)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(alpha_wrap_3)
#endif

%include "SWIG_CGAL/typemaps.i"
SWIG_CGAL_vector_of_int_to_array_of_int_typemap_out
#ifdef SWIGPYTHON
SWIG_CGAL_python_vector_of_int_typecheck
#endif

%inline %{
  void alpha_wrap_3(const std::vector<Point_3>& points,
                    const std::vector< std::vector<int> >& faces,
                    double alpha,
                    double offset,
                    Polyhedron_3_SWIG_wrapper& alpha_wrap)
  {
    std::size_t nb_pts = points.size();
    std::vector< Point_3::cpp_base > cgal_points;
    cgal_points.reserve(nb_pts);
    BOOST_FOREACH(const Point_3& pt, points)
      cgal_points.push_back( pt.get_data() );
    CGAL::alpha_wrap_3(cgal_points, faces, alpha, offset, alpha_wrap.get_data());
  }

  void alpha_wrap_3(const Polyhedron_3_SWIG_wrapper& tmesh,
                    double alpha,
                    double offset,
                    Polyhedron_3_SWIG_wrapper& alpha_wrap)
  {
    CGAL::alpha_wrap_3(tmesh.get_data(), alpha, offset, alpha_wrap.get_data());
  }

  void alpha_wrap_3(const std::vector<Point_3>& points,
                    double alpha,
                    double offset,
                    Polyhedron_3_SWIG_wrapper& alpha_wrap)
  {
    std::size_t nb_pts = points.size();
    std::vector< Point_3::cpp_base > cgal_points;
    cgal_points.reserve(nb_pts);
    BOOST_FOREACH(const Point_3& pt, points)
      cgal_points.push_back( pt.get_data() );
    CGAL::alpha_wrap_3(cgal_points, alpha, offset, alpha_wrap.get_data());
  }
%}
