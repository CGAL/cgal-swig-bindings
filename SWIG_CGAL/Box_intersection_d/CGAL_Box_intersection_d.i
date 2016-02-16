// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_Box_intersection_d

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Box_intersection_d)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

//include files
%{
  #include <SWIG_CGAL/Common/Iterator.h>
%}

%pragma(java) jniclassimports=
%{
  import java.util.Iterator;
  import CGAL.Kernel.Bbox_2;
  import CGAL.Kernel.Bbox_3;
  import CGAL.Kernel.Segment_2;
  import CGAL.Kernel.Point_2;
%}

%pragma(java) moduleimports=
%{
  import java.util.Iterator;
%}


%include "std_pair.i"
SWIG_CGAL_declare_identifier_of_template_class(Pair_of_int,std::pair<int,int>)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Pair_of_int,)
SWIG_CGAL_declare_identifier_of_template_class(Ids_iterator,SWIG_CGAL_Iterator<std::vector< std::pair<int,int> >::iterator,std::pair<int,int> >)

%typemap(javaimports) Collect_ids_callback %{import java.util.Iterator;%}
%typemap(javaimports) Box_with_id_2 %{import CGAL.Kernel.Bbox_2;%}
%typemap(javaimports) Box_with_id_3 %{import CGAL.Kernel.Bbox_3;%}

%typemap(javaimports) Collect_polyline_intersection_points %{import java.util.Iterator;%}
%typemap(javaimports) Box_for_segment_polyline_2 %{import CGAL.Kernel.Segment_2;%}

#ifdef SWIGJAVA
%include "SWIG_CGAL/Java/typemaps.i"
SWIG_CGAL_array_of_int_to_vector_of_pair_of_int_typemap_in
#endif

%include "SWIG_CGAL/Box_intersection_d/Box_with_id.h"
%include "SWIG_CGAL/Box_intersection_d/Callbacks.h"
%include "SWIG_CGAL/Box_intersection_d/enum.h"



SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Box_with_id_2>::input,Box_with_id_2,Box_with_id_2,Box_with_id_2::cpp_base,SWIGTYPE_p_Box_with_id_2,"(LCGAL/Box_intersection_d/Box_with_id_2;)J",box_intersection_d)
SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Box_with_id_3>::input,Box_with_id_3,Box_with_id_3,Box_with_id_3::cpp_base,SWIGTYPE_p_Box_with_id_3,"(LCGAL/Box_intersection_d/Box_with_id_3;)J",box_intersection_d)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(box_intersection_all_pairs_d)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(box_self_intersection_d)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(box_self_intersection_all_pairs_d)
#endif

//includes
%{
  #include <SWIG_CGAL/Box_intersection_d/Box_with_id.h>
  #include <SWIG_CGAL/Box_intersection_d/Callbacks.h>
  #include <SWIG_CGAL/Box_intersection_d/enum.h>
  #include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
  #include <CGAL/box_intersection_d.h>
  #include <vector>
%}

SWIG_CGAL_declare_identifier_of_template_class(Collect_ids_callback_2,Collect_ids_callback<2>)
SWIG_CGAL_declare_identifier_of_template_class(Collect_ids_callback_3,Collect_ids_callback<3>)

%include "SWIG_CGAL/Box_intersection_d/macros.i"
declare_box_intersection_d_box_functions(Box_with_id_2,Collect_ids_callback<2>)
declare_box_intersection_d_box_functions(Box_with_id_3,Collect_ids_callback<3>)

#ifdef SWIG_CGAL_HAS_Box_intersection_d_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Box_intersection_d/extensions.i"
#endif

/*
SWIG_CGAL_set_wrapper_iterator_helper_input(Segment_2)

%inline %{
#include <boost/foreach.hpp>
#include <SWIG_CGAL/Kernel/Segment_2.h>

void dummy(Segment_2){} // look at %types

void box_intersection_d(  Wrapper_iterator_helper< Segment_2 >::input range1
                        , Wrapper_iterator_helper< Segment_2 >::input range2
                        , Collect_ids_callback& callback
                        , int cutoff=10
                        , Topology topology=CLOSED
                        , Setting setting=BIPARTITE
)
{
  std::vector< Box_with_id<2> > cpp_range1, cpp_range2;

  int i=0;
  BOOST_FOREACH(Segment_2::cpp_base& s, range1)
    cpp_range1.push_back( Box_with_id<2>(s.bbox(), i++) );
  BOOST_FOREACH(Segment_2::cpp_base& s, range2)
    cpp_range2.push_back( Box_with_id<2>(s.bbox(), i++) );

  CGAL::box_intersection_d( cpp_range1.begin(), cpp_range1.end(),
                            cpp_range2.begin(), cpp_range2.end(),
                            callback, (std::ptrdiff_t) cutoff,
                            CGAL::enum_cast< CGAL::Box_intersection_d::Topology >(topology),
                            CGAL::enum_cast< CGAL::Box_intersection_d::Setting >(setting)
  );
}
%}
*/
