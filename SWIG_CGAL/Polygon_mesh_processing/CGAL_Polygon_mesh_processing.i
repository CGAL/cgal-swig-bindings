// ------------------------------------------------------------------------------
// Copyright (c) 2015 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

%define PMP_DOCSTRING
"SWIG wrapper for the CGAL Polygon Mesh Processing package provided under the GPL-3.0+ license"
%enddef
%module (package="CGAL", docstring=PMP_DOCSTRING) CGAL_Polygon_mesh_processing

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Polygon_mesh_processing)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

//include files
%{
  #include <SWIG_CGAL/Common/Iterator.h>
  #include <SWIG_CGAL/Polyhedron_3/all_includes.h>
  #include <SWIG_CGAL/Polygon_mesh_processing/all_includes.h>
%}

%pragma(java) jniclassimports=
%{
import java.util.Iterator;
import java.util.Collection;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Vertex_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Bbox_3;
%}

%pragma(java) moduleimports=%{
import java.util.Iterator;
import java.util.Collection;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Vertex_handle;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Bbox_3;
%};

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//import Polyhedron_3 wrapper types
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper
SWIG_CGAL_import_Polyhedron_3_Halfedge_handle_SWIG_wrapper
SWIG_CGAL_import_Polyhedron_3_Facet_handle_SWIG_wrapper
SWIG_CGAL_import_Polyhedron_3_Vertex_handle_SWIG_wrapper

%include "SWIG_CGAL/Polygon_mesh_processing/Polygon_mesh_slicer.h"
%typemap(javaimports) Polygon_mesh_slicer_wrapper %{import CGAL.Kernel.Plane_3; import CGAL.Polyhedron_3.Polyhedron_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Polygon_mesh_slicer,Polygon_mesh_slicer_wrapper<Polyhedron_3_SWIG_wrapper>)

%include "SWIG_CGAL/Polygon_mesh_processing/Side_of_triangle_mesh.h"
%typemap(javaimports) Side_of_triangle_mesh_wrapper %{import CGAL.Kernel.Point_3; import CGAL.Kernel.Bounded_side; import CGAL.Polyhedron_3.Polyhedron_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Side_of_triangle_mesh,Side_of_triangle_mesh_wrapper<Polyhedron_3_SWIG_wrapper>)

%include "SWIG_CGAL/Common/triple.h"
SWIG_CGAL_declare_identifier_of_template_class(Integer_triple,SWIG_CGAL::Triple<int,int,int>)

%include "std_pair.i"
%typemap(javaimports) std::pair<Polyhedron_3_Facet_handle_SWIG_wrapper,
                                Polyhedron_3_Facet_handle_SWIG_wrapper>
    %{ import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; %}
SWIG_CGAL_declare_identifier_of_template_class(Facet_pair,std::pair<Polyhedron_3_Facet_handle_SWIG_wrapper,Polyhedron_3_Facet_handle_SWIG_wrapper>)
%typemap(javaimports) std::pair<Polyhedron_3_Halfedge_handle_SWIG_wrapper,
                                Polyhedron_3_Halfedge_handle_SWIG_wrapper>
    %{ import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle; %}
SWIG_CGAL_declare_identifier_of_template_class(Halfedge_pair,std::pair<Polyhedron_3_Halfedge_handle_SWIG_wrapper,Polyhedron_3_Halfedge_handle_SWIG_wrapper>)

%include "std_vector.i"
%typemap(javaimports) std::vector<Point_3>
  %{ import CGAL.Kernel.Point_3; %}

%template(Point_3_Vector) std::vector<Point_3>;
%template(Int_Vector) std::vector<int>;
%template(Polygon_Vector) std::vector< std::vector<int> >;
%template(Polylines) std::vector< std::vector<Point_3> >;


//includes
%{
  #include <CGAL/polygon_mesh_processing.h>
  #include <CGAL/Polygon_mesh_processing/clip.h>
  #include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <SWIG_CGAL/Polygon_mesh_processing/utils.h>
  #include <iostream>
%}

%types(Point_3*,Point_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated
// typemaps for input iterators
SWIG_CGAL_set_wrapper_iterator_helper_input(Point_3)
SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::input,
                                    Polyhedron_3_Facet_handle_SWIG_wrapper,
                                    Polyhedron_3_Facet_handle,
                                    Polyhedron_3_Facet_handle_SWIG_wrapper::cpp_base,
                                    SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t,
                                    "(LCGAL/Polyhedron_3/Polyhedron_3_Facet_handle;)J",
                                    refine)
SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Halfedge_handle_SWIG_wrapper>::input,
                                    Polyhedron_3_Halfedge_handle_SWIG_wrapper,
                                    Polyhedron_3_Halfedge_handle,
                                    Polyhedron_3_Halfedge_handle_SWIG_wrapper::cpp_base,
                                    SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t,
                                    "(LCGAL/Polyhedron_3/Polyhedron_3_Halfedge_handle;)J",
                                    isotropic_remeshing)
SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::input,
                                    Polyhedron_3_Vertex_handle_SWIG_wrapper,
                                    Polyhedron_3_Vertex_handle,
                                    Polyhedron_3_Vertex_handle_SWIG_wrapper::cpp_base,
                                    SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Vertex_handleT_Polyhedron_3__t,
                                    "(LCGAL/Polyhedron_3/Polyhedron_3_Vertex_handle;)J",
                                    fair)
SWIG_CGAL_input_iterator_typemap_in(Wrapper_iterator_helper<Halfedge_pair_SWIG_wrapper>::input,
                                    Halfedge_pair_SWIG_wrapper,
                                    Halfedge_pair,
                                    internal::Converter<Halfedge_pair_SWIG_wrapper>::result_type,
                                    SWIGTYPE_p_std__pairT_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t_t,
                                    "(LCGAL/Polygon_mesh_processing/Halfedge_pair;)J",
                                    stitch_borders)

#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(split_long_edges)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(reverse_face_orientations)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(compute_vertex_normal)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(compute_face_normal)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(remove_connected_components)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(keep_connected_components)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(area)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(border_halfedges)
#endif
// typemaps for output iterators
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::output,
                                     Polyhedron_3_Facet_handle_SWIG_wrapper,
                                     Polyhedron_3_Facet_handle,
                                     Polyhedron_3_Facet_handle_SWIG_wrapper::cpp_base,
                                     SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t,
                                     "LCGAL/Polyhedron_3/Polyhedron_3_Facet_handle;")
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Halfedge_handle_SWIG_wrapper>::output,
                                     Polyhedron_3_Halfedge_handle_SWIG_wrapper,
                                     Polyhedron_3_Halfedge_handle,
                                     Polyhedron_3_Halfedge_handle_SWIG_wrapper::cpp_base,
                                     SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t,
                                     "LCGAL/Polyhedron_3/Polyhedron_3_Halfedge_handle;")
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::output,
                                     Polyhedron_3_Vertex_handle_SWIG_wrapper,
                                     Polyhedron_3_Vertex_handle,
                                     Polyhedron_3_Vertex_handle_SWIG_wrapper::cpp_base,
                                     SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Vertex_handleT_Polyhedron_3__t,
                                     "LCGAL/Polyhedron_3/Polyhedron_3_Vertex_handle;")
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<Facet_pair_SWIG_wrapper>::output,
                                     Facet_pair_SWIG_wrapper,
                                     Facet_pair,
                                     internal::Converter<Facet_pair_SWIG_wrapper>::result_type,
                                     SWIGTYPE_p_std__pairT_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t_t,
                                     "LCGAL/Polygon_mesh_processing/Facet_pair;")
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper<Integer_triple_SWIG_wrapper>::output,
                                     Integer_triple_SWIG_wrapper,
                                     Integer_triple,
                                     internal::Converter<Integer_triple_SWIG_wrapper>::result_type,
                                     SWIGTYPE_p_SWIG_CGAL__TripleT_int_int_int_t,
                                     "LCGAL/Polygon_mesh_processing/Integer_triple;")
SWIG_CGAL_output_iterator_typemap_in(Wrapper_iterator_helper< int >::output,int,Integer,int,swig_types[0],"Ljava/lang/Integer;")
%types(Vector_3*,Vector_3);//needed so that the identifier SWIGTYPE_p_Vector_3 is generated
SWIG_CGAL_set_wrapper_iterator_helper_output(Vector_3)

%include "SWIG_CGAL/typemaps.i"
SWIG_CGAL_array_of_int_to_vector_of_int_typemap_in
SWIG_CGAL_vector_of_int_to_array_of_int_typemap_out
#ifdef SWIGPYTHON
SWIG_CGAL_python_vector_of_int_typecheck
#endif
// get the definition of CGAL_VERSION_NR
%include "CGAL/version.h"

%inline %{
  #ifndef SWIG
  #include <boost/shared_ptr.hpp>
  namespace PMP=CGAL::Polygon_mesh_processing;
  namespace params=CGAL::Polygon_mesh_processing::parameters;

  struct Is_constrained_map{
    typedef boost::graph_traits<Polyhedron_3_SWIG_wrapper::cpp_base>::edge_descriptor key_type;
    std::set<key_type>* m_set;
    typedef boost::readable_property_map_tag category;
    typedef bool value_type;
    typedef bool reference;

    Is_constrained_map() : m_set(nullptr) {}
    Is_constrained_map(std::set<key_type>& set_) : m_set(&set_) {}

    friend bool get(const Is_constrained_map& map, const key_type& k)
    {
      CGAL_assertion(map.m_set != nullptr);
      return map.m_set->count(k);
    }

    friend void put(const Is_constrained_map& map, const key_type& k, value_type b)
    {
      CGAL_assertion(map.m_set != nullptr);
      if (b)
        map.m_set->insert(k);
      else
        map.m_set->erase(k);
    }
  };

  #endif // SWIG
  // input iterators
  typedef Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::input Vertex_range;
  typedef Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::input Facet_range;
  typedef Wrapper_iterator_helper<Polyhedron_3_Halfedge_handle_SWIG_wrapper>::input Halfedge_range;
  typedef Wrapper_iterator_helper<Halfedge_pair_SWIG_wrapper>::input Halfedge_pair_range;
  typedef Wrapper_iterator_helper<Point_3>::input Point_3_range;
  // output iterators
  typedef Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::output Vertex_output_iterator;
  typedef Wrapper_iterator_helper<Polyhedron_3_Halfedge_handle_SWIG_wrapper>::output Halfedge_output_iterator;
  typedef Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::output Facet_output_iterator;
  typedef Wrapper_iterator_helper<Integer_triple_SWIG_wrapper>::output Integer_triple_output_iterator;
  typedef Wrapper_iterator_helper<Facet_pair_SWIG_wrapper>::output Facet_pair_output_iterator;
  typedef Wrapper_iterator_helper<Vector_3>::output Vector_3_output_iterator;
  typedef Wrapper_iterator_helper<int>::output Integer_output_iterator;

// Meshing Functions
//   CGAL::Polygon_mesh_processing::fair()
  void fair(Polyhedron_3_SWIG_wrapper& P,
            Vertex_range vertex_range)
  {
    PMP::fair(P.get_data(), vertex_range);
  }

  void fair(Polyhedron_3_SWIG_wrapper& P,
            Vertex_range vertex_range,
            int fairing_continuity)
  {
    PMP::fair(P.get_data(), vertex_range,
              params::fairing_continuity(fairing_continuity));
  }
//   CGAL::Polygon_mesh_processing::refine()
  void refine( Polyhedron_3_SWIG_wrapper& P,
               Facet_range facet_range,
               Facet_output_iterator facet_output,
               Vertex_output_iterator vertex_output)
  {
    PMP::refine(P.get_data(), facet_range, facet_output, vertex_output);
  }
  void refine( Polyhedron_3_SWIG_wrapper& P,
               Facet_range facet_range,
               Facet_output_iterator facet_output,
               Vertex_output_iterator vertex_output,
               double density_control_factor)
  {
    PMP::refine(P.get_data(), facet_range, facet_output, vertex_output,
                params::fairing_continuity(density_control_factor));
  }

// CGAL::Polygon_mesh_processing::triangulate_face()
  void triangulate_face(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
		                    Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::triangulate_face(face.get_data(), P.get_data());
  }

//   CGAL::Polygon_mesh_processing::triangulate_faces()
  void triangulate_faces(Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::triangulate_faces(P.get_data());
  }

  void triangulate_faces (Facet_range facet_range,
                          Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::triangulate_faces(facet_range, P.get_data());
  }

//   CGAL::Polygon_mesh_processing::isotropic_remeshing() (4.8)
  void isotropic_remeshing(Facet_range facet_range,
                           double target_edge_length,
                           Polyhedron_3_SWIG_wrapper& P,
                           int number_of_iterations,
                           Halfedge_range constraints,
                           bool protect_constraints=false)
  {
    typedef Polyhedron_3_SWIG_wrapper::cpp_base Polyhedron;
    typedef boost::graph_traits<Polyhedron>::edge_descriptor edge_descriptor;
    std::set<edge_descriptor> constrained_edges;
    BOOST_FOREACH(Polyhedron::Halfedge_handle h, constraints)
      constrained_edges.insert(edge(h,P.get_data()));
    CGAL::set_halfedgeds_items_id(P.get_data());
    // isotropic_remeshing requires a ForwardIterator
    std::vector<Polyhedron_3_SWIG_wrapper::cpp_base::Face_handle> faces(facet_range.first, facet_range.second);
    PMP::isotropic_remeshing(faces, target_edge_length, P.get_data(),
                             params::number_of_iterations(number_of_iterations).
                             edge_is_constrained_map(
                              Is_constrained_map(constrained_edges)).
                              protect_constraints(protect_constraints)
                              );
  }
  void isotropic_remeshing(Facet_range facet_range,
                           double target_edge_length,
                           Polyhedron_3_SWIG_wrapper& P,
                           int number_of_iterations)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    // isotropic_remeshing requires a ForwardIterator
    std::vector<Polyhedron_3_SWIG_wrapper::cpp_base::Face_handle> faces(facet_range.first, facet_range.second);
    PMP::isotropic_remeshing(faces, target_edge_length, P.get_data(),
                             params::number_of_iterations(number_of_iterations));
  }
  void isotropic_remeshing(Facet_range facet_range,
                           double target_edge_length,
                           Polyhedron_3_SWIG_wrapper& P)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    // isotropic_remeshing requires a ForwardIterator
    std::vector<Polyhedron_3_SWIG_wrapper::cpp_base::Face_handle> faces(facet_range.first, facet_range.second);
    PMP::isotropic_remeshing(make_range(facet_range), target_edge_length, P.get_data());
  }
//   CGAL::Polygon_mesh_processing::split_long_edges() (4.8)
  void split_long_edges(Halfedge_range halfedge_range,
                        const double& max_length,
                        Polyhedron_3_SWIG_wrapper& P)
  {
    typedef Polyhedron_3_SWIG_wrapper::cpp_base Polyhedron;
    typedef boost::graph_traits<Polyhedron>::edge_descriptor edge_descriptor;
    std::vector<edge_descriptor> edges;
    BOOST_FOREACH(Polyhedron::Halfedge_handle h, halfedge_range)
      edges.push_back(edge(h,P.get_data()));
    PMP::split_long_edges(edges, max_length, P.get_data());
  }
//

// Hole Filling Functions
//   CGAL::Polygon_mesh_processing::triangulate_hole()
  void triangulate_hole(Polyhedron_3_SWIG_wrapper& P,
                        Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                        Facet_output_iterator output)
  {
    CGAL::Polygon_mesh_processing::triangulate_hole(P.get_data(), h.get_data(),
                                                    output);
  }
//   CGAL::Polygon_mesh_processing::triangulate_and_refine_hole()
  void triangulate_and_refine_hole( Polyhedron_3_SWIG_wrapper& P,
                                    Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                    Facet_output_iterator facet_output,
                                    Vertex_output_iterator vertex_output)
  {
    PMP::triangulate_and_refine_hole(P.get_data(), h.get_data(), facet_output,
                                     vertex_output);
  }
  void triangulate_and_refine_hole( Polyhedron_3_SWIG_wrapper& P,
                                    Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                    Facet_output_iterator facet_output,
                                    Vertex_output_iterator vertex_output,
                                    double density_control_factor)
  {
    PMP::triangulate_and_refine_hole(P.get_data(), h.get_data(), facet_output,
                                     vertex_output,
                                     params::density_control_factor(density_control_factor));
  }
//   CGAL::Polygon_mesh_processing::triangulate_refine_and_fair_hole()
  void triangulate_refine_and_fair_hole( Polyhedron_3_SWIG_wrapper& P,
                                         Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                         Facet_output_iterator facet_output,
                                         Vertex_output_iterator vertex_output)
  {
    PMP::triangulate_refine_and_fair_hole(P.get_data(), h.get_data(),
                                          facet_output, vertex_output);
  }
  void triangulate_refine_and_fair_hole( Polyhedron_3_SWIG_wrapper& P,
                                         Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                         Facet_output_iterator facet_output,
                                         Vertex_output_iterator vertex_output,
                                         double density_control_factor)
  {
    PMP::triangulate_refine_and_fair_hole(P.get_data(), h.get_data(), facet_output,
                                          vertex_output,
                                          params::density_control_factor(density_control_factor));
  }
  void triangulate_refine_and_fair_hole( Polyhedron_3_SWIG_wrapper& P,
                                         Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                         Facet_output_iterator facet_output,
                                         Vertex_output_iterator vertex_output,
                                         double density_control_factor,
                                         int fairing_continuity)
  {
    PMP::triangulate_refine_and_fair_hole(P.get_data(), h.get_data(),
                                          facet_output, vertex_output,
                                          params::density_control_factor(density_control_factor).
                                          fairing_continuity(fairing_continuity));
  }
//   CGAL::Polygon_mesh_processing::triangulate_hole_polyline()
  void triangulate_hole_polyline 	(Point_3_range points,
  		                             Point_3_range third_points,
                                   Integer_triple_output_iterator out)
  {
    std::vector<Point_3::cpp_base> pts(points.begin(), points.end());
    std::vector<Point_3::cpp_base> tpts(third_points.begin(), third_points.end());
    PMP::triangulate_hole_polyline( pts, tpts, out);
  }

  void triangulate_hole_polyline 	(Point_3_range points,
                                   Integer_triple_output_iterator out)
  {
    std::vector<Point_3::cpp_base> pts(points.begin(), points.end());
    PMP::triangulate_hole_polyline( pts, out);
  }

//
// Predicate Functions
//   CGAL::Polygon_mesh_processing::does_self_intersect()
  bool does_self_intersect(Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::does_self_intersect(P.get_data());
  }
//   CGAL::Polygon_mesh_processing::self_intersections()
  void self_intersections(Polyhedron_3_SWIG_wrapper& P,
                          Facet_pair_output_iterator out)
  {
    PMP::self_intersections(P.get_data(), out);
  }
//   CGAL::Polygon_mesh_processing::do_intersect()
  bool do_intersect(Polyhedron_3_SWIG_wrapper& P,
                    Polyhedron_3_SWIG_wrapper& Q)
  {
    return PMP::do_intersect(P.get_data(), Q.get_data());
  }

//
// Orientation Functions
//   CGAL::Polygon_mesh_processing::is_outward_oriented()
  bool is_outward_oriented(Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::is_outward_oriented(P.get_data());
  }
//   CGAL::Polygon_mesh_processing::reverse_face_orientations()
  void reverse_face_orientations(Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::reverse_face_orientations(P.get_data());
  }
  void reverse_face_orientations(Facet_range face_range,
                                 Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::reverse_face_orientations(CGAL::make_range(face_range), P.get_data());
  }
//   CGAL::Polygon_mesh_processing::orient_polygon_soup()
  bool orient_polygon_soup(std::vector<Point_3>& points,
                           std::vector< std::vector<int> >& polygons)
  {
    std::size_t nb_pts = points.size();
    std::vector< Point_3::cpp_base > cgal_points;
    cgal_points.reserve(nb_pts);
    BOOST_FOREACH(const Point_3& pt, points)
      cgal_points.push_back( pt.get_data() );
    bool res = PMP::orient_polygon_soup(cgal_points, polygons);
    if (cgal_points.size()>nb_pts)
      for (std::size_t i=nb_pts;i<cgal_points.size();++i)
        points.push_back( Point_3(cgal_points[i]) );
    return res;
  }
//
// Combinatorial Repairing Functions
//   CGAL::Polygon_mesh_processing::stitch_borders()
  void stitch_borders(Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::stitch_borders(P.get_data());
  }
  void stitch_borders(Polyhedron_3_SWIG_wrapper& P,
                      Halfedge_pair_range hedges)
  {
    PMP::stitch_borders(P.get_data(), CGAL::make_range(hedges));
  }
//   CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh()
  void polygon_soup_to_polygon_mesh(const std::vector<Point_3>& points,
                                    const std::vector< std::vector<int> >& polygons,
                                    Polyhedron_3_SWIG_wrapper& P)
  {
    std::size_t nb_pts = points.size();
    std::vector< Point_3::cpp_base > cgal_points;
    cgal_points.reserve(nb_pts);
    BOOST_FOREACH(const Point_3& pt, points)
      cgal_points.push_back( pt.get_data() );
    PMP::polygon_soup_to_polygon_mesh(cgal_points, polygons, P.get_data());
  }

  //   CGAL::Polygon_mesh_processing::remove_isolated_vertices() (4.8)
  void remove_isolated_vertices(Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::remove_isolated_vertices(P.get_data());
  }

//
// Normal Computation Functions
//   CGAL::Polygon_mesh_processing::compute_face_normal()
  Vector_3 compute_face_normal(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
                               Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::compute_face_normal(face.get_data(), P.get_data());
  }
  void compute_face_normal(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
                           Polyhedron_3_SWIG_wrapper& P,
                           Vector_3& output_normal)
  {
    output_normal=Vector_3(
        PMP::compute_face_normal(face.get_data(), P.get_data()) );
  }
//   CGAL::Polygon_mesh_processing::compute_face_normals()
  void compute_face_normals(Polyhedron_3_SWIG_wrapper& P,
                            Vector_3_output_iterator out)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    std::vector< EPIC_Kernel::Vector_3 > normals(P.get_data().size_of_vertices());
    typedef Polyhedron_3_SWIG_wrapper::cpp_base::Facet_handle Facet_handle;
    X_from_id_pmap<Facet_handle, EPIC_Kernel::Vector_3> ppmap(normals);
    PMP::compute_face_normals(P.get_data(), ppmap);
    BOOST_FOREACH(const EPIC_Kernel::Vector_3& v, normals)
      *out++=v;
  }
//   CGAL::Polygon_mesh_processing::compute_vertex_normal()
  Vector_3 compute_vertex_normal(Polyhedron_3_Vertex_handle_SWIG_wrapper& vertex,
                                 Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::compute_vertex_normal(vertex.get_data(), P.get_data());
  }
  void compute_vertex_normal(Polyhedron_3_Vertex_handle_SWIG_wrapper& vertex,
                             Polyhedron_3_SWIG_wrapper& P,
                             Vector_3& output_normal)
  {
    output_normal=Vector_3(
        PMP::compute_vertex_normal(vertex.get_data(), P.get_data()) );
  }
//   CGAL::Polygon_mesh_processing::compute_vertex_normals()
  void compute_vertex_normals(Polyhedron_3_SWIG_wrapper& P,
                              Vector_3_output_iterator out)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    std::vector< EPIC_Kernel::Vector_3 > normals(P.get_data().size_of_vertices());
    typedef Polyhedron_3_SWIG_wrapper::cpp_base::Vertex_handle Vertex_handle;
    X_from_id_pmap<Vertex_handle, EPIC_Kernel::Vector_3> ppmap(normals);
    PMP::compute_vertex_normals(P.get_data(), ppmap);
    BOOST_FOREACH(const EPIC_Kernel::Vector_3& v, normals)
      *out++=v;
  }
//   CGAL::Polygon_mesh_processing::compute_normals()
//
// Connected Components
//   CGAL::Polygon_mesh_processing::connected_component()
  void connected_component(Polyhedron_3_Facet_handle_SWIG_wrapper& seed_face,
                           Polyhedron_3_SWIG_wrapper& P,
                           Facet_output_iterator out)
  {
    PMP::connected_component(seed_face.get_data(), P.get_data(), out);
  }
//   CGAL::Polygon_mesh_processing::connected_components()
  boost::shared_ptr<std::vector<int> >
  connected_components(Polyhedron_3_SWIG_wrapper& P)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    boost::shared_ptr<std::vector<int> > cc_ids( new std::vector<int>(P.size_of_facets()) );
    typedef Polyhedron_3_SWIG_wrapper::cpp_base::Facet_handle Facet_handle;
    Int_from_id_pmap<Facet_handle> pmap(*cc_ids);
    PMP::connected_components(P.get_data(), pmap);
    return cc_ids;
  }

  //   CGAL::Polygon_mesh_processing::keep_large_connected_components() (4.8)
  int keep_large_connected_components(Polyhedron_3_SWIG_wrapper& P,
                                      int threshold_components_to_keep)
  {
    return PMP::keep_large_connected_components(P.get_data(),
                                                threshold_components_to_keep);
  }

//   CGAL::Polygon_mesh_processing::keep_largest_connected_components()
  int keep_largest_connected_components(Polyhedron_3_SWIG_wrapper& P,
                                        int nb_components_to_keep)
  {
    return PMP::keep_largest_connected_components(P.get_data(),
                                                  nb_components_to_keep);
  }
//   CGAL::Polygon_mesh_processing::keep_connected_components()
  void keep_connected_components(Polyhedron_3_SWIG_wrapper& P,
                                 Facet_range components_to_keep)
  {
    PMP::keep_connected_components(P.get_data(),
                                   CGAL::make_range(components_to_keep));
  }
  void keep_connected_components(Polyhedron_3_SWIG_wrapper& P,
                                 boost::shared_ptr<std::vector<int> > components_to_keep,
                                 boost::shared_ptr<std::vector<int> > fcm)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    typedef Polyhedron_3_SWIG_wrapper::cpp_base::Facet_handle Facet_handle;
    Int_from_id_pmap<Facet_handle> pmap(*fcm);
    PMP::keep_connected_components(P.get_data(),
                                   *components_to_keep,
                                   pmap);
  }

//   CGAL::Polygon_mesh_processing::remove_connected_components()

  void remove_connected_components( Polyhedron_3_SWIG_wrapper& P,
                                    Facet_range components_to_remove)
  {
    PMP::remove_connected_components(P.get_data(),
                                     CGAL::make_range(components_to_remove));
  }

  void remove_connected_components(Polyhedron_3_SWIG_wrapper& P,
                                 boost::shared_ptr<std::vector<int> > components_to_remove,
                                 boost::shared_ptr<std::vector<int> > fcm)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    typedef Polyhedron_3_SWIG_wrapper::cpp_base::Facet_handle Facet_handle;
    Int_from_id_pmap<Facet_handle> pmap(*fcm);
    PMP::remove_connected_components(P.get_data(),
                                     *components_to_remove,
                                     pmap);
  }
//

// Geometric Measure functions
//   CGAL::Polygon_mesh_processing::face_area()
  double face_area(Polyhedron_3_Facet_handle_SWIG_wrapper& face,
                   Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::face_area(face.get_data(), P.get_data());
  }
//   CGAL::Polygon_mesh_processing::area() (4.8)
  double area(Facet_range facet_range,
              Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::area(facet_range, P.get_data());
  }
  double area(Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::area(P.get_data());
  }
//   CGAL::Polygon_mesh_processing::volume() (4.8)
  double volume(Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::volume(P.get_data());
  }
//   CGAL::Polygon_mesh_processing::edge_length() (4.8)
  double edge_length(Polyhedron_3_Halfedge_handle_SWIG_wrapper& hedge,
                     Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::edge_length(hedge.get_data(), P.get_data());
  }
//   CGAL::Polygon_mesh_processing::face_border_length() (4.8)
  double face_border_length(Polyhedron_3_Halfedge_handle_SWIG_wrapper& hedge,
                            Polyhedron_3_SWIG_wrapper& P)
  {
    return PMP::face_border_length(hedge.get_data(), P.get_data());
  }
//
// Miscellaneous
  Bbox_3 bbox(Polyhedron_3_SWIG_wrapper& P)
  {
    return Bbox_3( PMP::bbox(P.get_data()));
  }

//
// Corefinement based
  void corefine(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B)
  {
    PMP::corefine(A.get_data(), B.get_data());
  }

  bool corefine_and_compute_union(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B, Polyhedron_3_SWIG_wrapper& out)
  {
    return PMP::corefine_and_compute_union(A.get_data(), B.get_data(), out.get_data());
  }

  bool corefine_and_compute_intersection(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B, Polyhedron_3_SWIG_wrapper& out)
  {
    return PMP::corefine_and_compute_intersection(A.get_data(), B.get_data(), out.get_data());
  }

  bool corefine_and_compute_difference(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B, Polyhedron_3_SWIG_wrapper& out)
  {
    return PMP::corefine_and_compute_difference(A.get_data(), B.get_data(), out.get_data());
  }

  bool clip(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B)
  {
    return PMP::clip(A.get_data(), B.get_data());
  }

  bool clip(Polyhedron_3_SWIG_wrapper& A, Plane_3& plane)
  {
    return PMP::clip(A.get_data(), plane.get_data());
  }

#if CGAL_VERSION_MAJOR ==5 && CGAL_VERSION_MINOR >= 1
  void split(Polyhedron_3_SWIG_wrapper& A, Polyhedron_3_SWIG_wrapper& B)
  {
    PMP::split(A.get_data(), B.get_data());
  }

  void split(Polyhedron_3_SWIG_wrapper& A, Plane_3& plane)
  {
    PMP::split(A.get_data(), plane.get_data());
  }
#endif

//   CGAL::Polygon_mesh_processing::border_halfedges() (4.8)
  void border_halfedges(Facet_range facet_range,
                        Polyhedron_3_SWIG_wrapper& P,
                        Halfedge_output_iterator out)
  {
    CGAL::set_halfedgeds_items_id(P.get_data());
    PMP::border_halfedges(make_range(facet_range), P.get_data(), out);
  }
  
%}

#ifdef SWIGJAVA
SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in
SWIG_CGAL_array_of_int_to_vector_of_vector_of_int_typemap_in

%inline
%{
#include <boost/shared_ptr.hpp>
void polygon_soup_to_polygon_mesh(boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
                                  boost::shared_ptr< std::vector< std::vector<int> > > polygons,
                                  Polyhedron_3_SWIG_wrapper& P)
{
  CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(*points, *polygons, P.get_data());
}
%}
#endif

#ifdef SWIG_CGAL_HAS_Polygon_mesh_processing_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Polygon_mesh_processing/extensions.i"
#endif
