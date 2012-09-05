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
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Weighted_point_2; import java.util.Iterator; import java.util.Collection; import CGAL.Java.JavaData;%}

%include "SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_2.h"
%include "SWIG_CGAL/Voronoi_diagram_2/Voronoi_diagram_handles_2.h"
%include "SWIG_CGAL/Voronoi_diagram_2/Locate_result.h"


#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
//typemap for point input iterator
SWIG_CGAL_input_iterator_typemap_in(Kernel_iterator_helper<Point_2>::input,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Kd_tree_wrapper::Kd_tree_wrapper)
#endif
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE



//typemaps for output iterator
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Pt_2_output_iterator Kernel_iterator_helper<Point_2>::output %enddef
SWIG_CGAL_output_iterator_typemap_in(Pt_2_output_iterator,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"LCGAL/Kernel/Point_2;")
#else
%include "SWIG_CGAL/Common/Output_iterator_wrapper.h"
SWIG_CGAL_declare_generic_output_iterator(Point_2_output_iterator,Point_2_output_iterator_nested_iterator,Point_2)
#endif


//import Triangulation_2 package types
SWIG_CGAL_import_Delaunay_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Delaunay_triangulation_2_Face_handle_SWIG_wrapper
SWIG_CGAL_import_Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper

SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Vertex_handle,   Voronoi_vertex_wrapper_2   <V2_DT_AT_CAP, Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper, Delaunay_triangulation_2_Face_handle_SWIG_wrapper>)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Face_handle,     Voronoi_face_wrapper_2     <V2_DT_AT_CAP, Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper, Delaunay_triangulation_2_Face_handle_SWIG_wrapper>)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Halfedge_handle, Voronoi_halfedge_wrapper_2 <V2_DT_AT_CAP, Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper, Delaunay_triangulation_2_Face_handle_SWIG_wrapper>)

//Iterators and circulators
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Voronoi_diagram_2_Face_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Face_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Face_iterator,Voronoi_diagram_2_Face_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Bounded_faces_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Bounded_faces_iterator,Voronoi_diagram_2_Face_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Unbounded_faces_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Unbounded_faces_iterator,Voronoi_diagram_2_Face_handle_SWIG_wrapper >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Voronoi_diagram_2_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Edge_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Edge_iterator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Halfedge_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Halfedge_iterator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Unbounded_halfedges_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Unbounded_halfedges_iterator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Bounded_halfedges_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Bounded_halfedges_iterator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator, Voronoi_diagram_2_Halfedge_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Ccb_halfedge_circulator,SWIG_CGAL_Circulator<V2_DT_AT_CAP::Ccb_halfedge_circulator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Halfedge_around_vertex_circulator,SWIG_CGAL_Circulator<V2_DT_AT_CAP::Halfedge_around_vertex_circulator,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Voronoi_diagram_2_Vertex_handle,)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Vertex_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Vertex_iterator,Voronoi_diagram_2_Vertex_handle_SWIG_wrapper >)

SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_2,import CGAL.Kernel.Point_2;)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2_Site_iterator,SWIG_CGAL_Iterator<V2_DT_AT_CAP::Site_iterator,Point_2 >)

SWIG_CGAL_declare_identifier_of_template_class(Locate_result, Locate_result_wrapper<Voronoi_diagram_2_Vertex_handle_SWIG_wrapper,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper,Voronoi_diagram_2_Face_handle_SWIG_wrapper>)
SWIG_CGAL_declare_identifier_of_template_class(Voronoi_diagram_2,Voronoi_diagram_2_wrapper<V2_DT_AT_CAP,Point_2,Delaunay_triangulation_2_SWIG_wrapper,Delaunay_triangulation_2_Vertex_handle_SWIG_wrapper, Delaunay_triangulation_2_Face_handle_SWIG_wrapper, Voronoi_diagram_2_Vertex_handle_SWIG_wrapper,Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper,Voronoi_diagram_2_Face_handle_SWIG_wrapper>)

