// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Voronoi_diagram_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Voronoi_diagram_2)
SWIG_CGAL_package_common()

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
  #include <SWIG_CGAL/Kernel/Polygon_2.h>
%}

%pragma(java) jniclassimports=%{
  import CGAL.Kernel.Point_2;
  import CGAL.Kernel.Segment_2;
  import CGAL.Kernel.Iso_rectangle_2;
  import CGAL.Kernel.Polygon_2;
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


//typemap for point input iterator
SWIG_CGAL_set_wrapper_iterator_helper_input(Point_2)
SWIG_CGAL_set_wrapper_iterator_helper_input(Weighted_point_2)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(Voronoi_diagram_2_wrapper::Voronoi_diagram_2_wrapper)
#endif
SWIG_CGAL_set_wrapper_iterator_helper_output(Point_2)
SWIG_CGAL_set_wrapper_iterator_helper_output(Weighted_point_2)

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

/// Below are functions that are added for convinience but that is not in CGAL
///
%pragma(java) moduleimports=%{import CGAL.Kernel.Segment_2; import CGAL.Kernel.Iso_rectangle_2; import CGAL.Kernel.Polygon_2; import java.util.Collection;%}

//  typemaps for output iterator of Segment_2
SWIG_CGAL_set_wrapper_iterator_helper_output(Segment_2)


%types(Segment_2*,Segment_2);//needed so that the identifier SWIGTYPE_p_Segment_2 is generated
typedef Wrapper_iterator_helper<Segment_2>::output      Segment_2_output_iterator;
void crop_voronoi_facet(Voronoi_diagram_2_SWIG_wrapper&,Voronoi_diagram_2_Face_handle_SWIG_wrapper&,Iso_rectangle_2&,Segment_2_output_iterator);

%include "SWIG_CGAL/Common/Optional.h"
%typemap(javaimports)  Optional %{ import CGAL.Kernel.Segment_2; %}
%template (Optional_segment_2) Optional<Segment_2>;
void crop_voronoi_facet_polygon(Voronoi_diagram_2_SWIG_wrapper&,Voronoi_diagram_2_Face_handle_SWIG_wrapper&,Iso_rectangle_2&,Polygon_2&);
Optional<Segment_2> crop_voronoi_edge(Voronoi_diagram_2_SWIG_wrapper&, Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper&,Iso_rectangle_2&);
%{
  typedef Wrapper_iterator_helper<Segment_2>::output      Segment_2_output_iterator; 
  
  #include <SWIG_CGAL/Voronoi_diagram_2/utility.h>
  void crop_voronoi_facet(Voronoi_diagram_2_SWIG_wrapper& vd_wrapper,Voronoi_diagram_2_Face_handle_SWIG_wrapper& fh_wrapper,Iso_rectangle_2& rect_wrapper,Segment_2_output_iterator output)
  {
    internal::crop_face_boundary(vd_wrapper.get_data(),rect_wrapper.get_data(),fh_wrapper.get_data(),output);
  }
  void crop_voronoi_facet_polygon(Voronoi_diagram_2_SWIG_wrapper& vd_wrapper,Voronoi_diagram_2_Face_handle_SWIG_wrapper& fh_wrapper,Iso_rectangle_2& rect_wrapper,Polygon_2& result)
  {
    internal::crop_voronoi_facet_polygon(vd_wrapper.get_data(),rect_wrapper.get_data(),fh_wrapper.get_data(),result.get_data());
  }

  #include <SWIG_CGAL/Common/Optional.h>
  Optional<Segment_2> crop_voronoi_edge(Voronoi_diagram_2_SWIG_wrapper& vd_wrapper, Voronoi_diagram_2_Halfedge_handle_SWIG_wrapper& hh_wrapper, Iso_rectangle_2& rect_wrapper)
  {
    boost::optional< Segment_2::cpp_base > res =
      internal::crop_bissector(vd_wrapper.get_data(), hh_wrapper.get_data(), rect_wrapper.get_data());
    if ( !res ) return Optional<Segment_2>();
    return Optional<Segment_2>( Segment_2(*res) );
  }
%}

#ifdef SWIG_CGAL_HAS_Voronoi_diagram_2_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Voronoi_diagram_2/extensions.i"
#endif
