// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module CGAL_Voronoi_diagram_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Voronoi_diagram_2)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%import "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"

%{
  #include <SWIG_CGAL/Voronoi_diagram_2/typedefs.h>  
  #include <SWIG_CGAL/Voronoi_diagram_2/all_includes.h>  
  //needed for importing Triangulation_2 module
  //WHY isn't it inside all_includes??????
  #include <SWIG_CGAL/Triangulation_2/Object.h>
  #include <SWIG_CGAL/Triangulation_2/all_includes.h>
  #include <SWIG_CGAL/Kernel/Iso_rectangle_2.h>
%}

%pragma(java) jniclassimports=%{
  import CGAL.Kernel.Point_2;
  import CGAL.Triangulation_2.Delaunay_triangulation_2;
  import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle;
  import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle;
  import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge;
  import CGAL.Triangulation_2.Regular_triangulation_2;
  import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle;
  import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle;
  import CGAL.Triangulation_2.Regular_triangulation_2_Edge;
  import CGAL.Kernel.Weighted_point_2;
  import java.util.Iterator;
  import java.util.Collection;
  import CGAL.Java.JavaData;
%}

%include "SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_2.h"
%include "SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_handles_2.h"
%include "SWIG_CGAL/Voronoi_diagram_2/Locate_result.h"


#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Kernel_iterator_helper<Point_2>::input,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
SWIG_CGAL_input_iterator_typemap_in(Kernel_iterator_helper<Weighted_point_2>::input,Weighted_point_2,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"(LCGAL/Kernel/Weighted_point_2;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Voronoi_diagram_2_wrapper::Voronoi_diagram_2_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE



//typemaps for output iterator
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Pt_2_output_iterator Kernel_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Pt_2_output_iterator,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"LCGAL/Kernel/Point_2;")
%define Wpt_2_output_iterator Kernel_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Wpt_2_output_iterator,Weighted_point_2,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"LCGAL/Kernel/Weighted_point_2;")
#else
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(Point_2_output_iterator,Point_2_output_iterator_nested_iterator,Point_2)
SWIG_CGAL_declare_generic_output_iterator(Weighted_point_2_output_iterator,Weighted_point_2_output_iterator_nested_iterator,Weighted_point_2)
#endif


//import Triangulation_2 package types
SWIG_CGAL_import_Delaunay_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Delaunay_triangulation_2_Face_handle_SWIG_wrapper
SWIG_CGAL_import_Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper

//import Regular_triangulation_2 package types
SWIG_CGAL_import_Regular_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Regular_triangulation_2_Face_handle_SWIG_wrapper
SWIG_CGAL_import_Regular_triangulation_2_Vertex_handle_SWIG_wrapper


%import "SWIG_CGAL/Voronoi_diagram_2/declare_voronoi_diagram_2.i"

//exposes voronoi diagram with Delaunay_triangulation_caching_degeneracy_removal_policy_2s
declare_voronoi_diagram_2(Voronoi_diagram_2,V2_DT_AT_CAP,Point_2,Delaunay_triangulation_2)
//exposes power diagram with Regular_triangulation_caching_degeneracy_removal_policy_2s
declare_voronoi_diagram_2(Power_diagram_2,V2_RT_AT_CAP,Weighted_point_2,Regular_triangulation_2)

//function added for convinience but that is not in CGAL
//  typemaps for output iterator
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Segment_2_output_iterator Kernel_iterator_helper<Segment_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Segment_2_output_iterator,Segment_2,Segment_2,Segment_2::cpp_base,SWIGTYPE_p_Segment_2,"LCGAL/Kernel/Segment_2;")
#else
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(Segment_2_output_iterator,Segment_2_output_iterator_nested_iterator,Segment_2)
#endif

%types(Segment_2*,Segment_2);//needed so that the identifier SWIGTYPE_p_Segment_2 is generated
void crop_voronoi_facet(Voronoi_diagram_2_SWIG_wrapper&,Voronoi_diagram_2_Face_handle_SWIG_wrapper&,Iso_rectangle_2&,Segment_2_output_iterator);
%{
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef Kernel_iterator_helper<Segment_2>::output      Segment_2_output_iterator; 
  #else
  typedef Generic_output_iterator<Segment_2>  Segment_2_output_iterator;
  #endif
  
  #include <SWIG_CGAL/Voronoi_diagram_2/utility.h>
  void crop_voronoi_facet(Voronoi_diagram_2_SWIG_wrapper& vd_wrapper,Voronoi_diagram_2_Face_handle_SWIG_wrapper& fh_wrapper,Iso_rectangle_2& rect_wrapper,Segment_2_output_iterator output)
  {
    internal::crop_face_boundary(vd_wrapper.get_data(),rect_wrapper.get_data(),fh_wrapper.get_data(),output);
  }
%}

