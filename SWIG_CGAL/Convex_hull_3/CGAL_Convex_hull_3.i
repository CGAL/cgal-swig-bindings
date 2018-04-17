// ------------------------------------------------------------------------------
// Copyright (c) 2017 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_Convex_hull_3

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Convex_hull_3)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

%pragma(java) jniclassimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import java.util.Iterator;
%}
%pragma(java) moduleimports=%{
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Plane_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import java.util.Iterator;
%}

//include files
%{
#include <SWIG_CGAL/Polyhedron_3/all_includes.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Convex_hull_3/dual/halfspace_intersection_3.h>
#include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
%}

%types(Plane_3*,Plane_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated

SWIG_CGAL_set_wrapper_iterator_helper_input(Point_3)
SWIG_CGAL_set_wrapper_iterator_helper_input(Plane_3)

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//import Polyhedron_3 wrapper types
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper


%inline %{
typedef Wrapper_iterator_helper<Point_3>::input       Point_range;
typedef Wrapper_iterator_helper<Plane_3>::input       Plane_range;

void convex_hull_3(Point_range range, Polyhedron_3_SWIG_wrapper& P)
{
  CGAL::convex_hull_3(range.first, range.second, P.get_data());
}

void halfspace_intersection_3(Plane_range range, Polyhedron_3_SWIG_wrapper& P)
{
  std::vector<Plane_3::cpp_base> planes(range.first, range.second);
  CGAL::halfspace_intersection_3(planes.begin(), planes.end(), P.get_data());
}

void halfspace_intersection_3(Plane_range range, Polyhedron_3_SWIG_wrapper& P, Point_3& pt)
{
  std::vector<Plane_3::cpp_base> planes(range.first, range.second);
  CGAL::halfspace_intersection_3(planes.begin(), planes.end(), P.get_data(), pt.get_data());
}

bool is_strongly_convex_3(Polyhedron_3_SWIG_wrapper& P)
{
  return CGAL::is_strongly_convex_3(P.get_data());
}

%}

#ifdef SWIG_CGAL_HAS_Convex_hull_3_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Convex_hull_3/extensions.i"
#endif
