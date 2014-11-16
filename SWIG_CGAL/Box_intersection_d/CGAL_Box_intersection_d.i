// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_Box_intersection_d

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Box_intersection_d)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

//include files
%{
  #include <SWIG_CGAL/Common/Iterator.h>
%}

%include "SWIG_CGAL/Box_intersection_d/Box_with_id.h"
%include "SWIG_CGAL/Box_intersection_d/Callbacks.h"
%include "SWIG_CGAL/Box_intersection_d/enum.h"


SWIG_CGAL_set_wrapper_iterator_helper_input(Box_with_id_2)
SWIG_CGAL_set_wrapper_iterator_helper_input(Box_with_id_3)

//includes
%{
  #include <SWIG_CGAL/Box_intersection_d/Box_with_id.h>
  #include <SWIG_CGAL/Box_intersection_d/Callbacks.h>
  #include <SWIG_CGAL/Box_intersection_d/enum.h>
  #include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
  #include <CGAL/box_intersection_d.h>
  #include <vector>
%}

%include "SWIG_CGAL/Box_intersection_d/macros.i"
declare_box_intersection_d_box_functions(Box_with_id_2,Collect_ids_callback)
declare_box_intersection_d_box_functions(Box_with_id_3,Collect_ids_callback)
