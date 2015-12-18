// ------------------------------------------------------------------------------
// Copyright (c) 2015 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_Polygon_mesh_processing

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Polygon_mesh_processing)

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Common/Wrapper_iterator_helper.h"

//include files
%{
  #include <SWIG_CGAL/Common/Iterator.h>
  #include  <SWIG_CGAL/Polyhedron_3/all_includes.h>
  #include  <SWIG_CGAL/Polygon_mesh_processing/Polygon_mesh_slicer.h>
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

%include "SWIG_CGAL/Common/triple.h"
SWIG_CGAL_declare_identifier_of_template_class(Triple_of_int,SWIG_CGAL::Triple<int,int,int>)

%include "std_pair.i"
%typemap(javaimports) std::pair<Polyhedron_3_Facet_handle_SWIG_wrapper,
                                Polyhedron_3_Facet_handle_SWIG_wrapper>
    %{ import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; %}
SWIG_CGAL_declare_identifier_of_template_class(Facet_pair,std::pair<Polyhedron_3_Facet_handle_SWIG_wrapper,Polyhedron_3_Facet_handle_SWIG_wrapper>)
%typemap(javaimports) std::pair<Polyhedron_3_Halfedge_handle_SWIG_wrapper,
                                Polyhedron_3_Halfedge_handle_SWIG_wrapper>
    %{ import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle; %}
SWIG_CGAL_declare_identifier_of_template_class(Halfedge_pair,std::pair<Polyhedron_3_Halfedge_handle_SWIG_wrapper,Polyhedron_3_Halfedge_handle_SWIG_wrapper>)

//includes
%{
  #include <CGAL/polygon_mesh_processing.h>
  #include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <iostream>
%}

%types(Point_3*,Point_3);//needed so that the identifier SWIGTYPE_p_Point_3 is generated
SWIG_CGAL_set_wrapper_iterator_helper_input(Point_3)
SWIG_CGAL_set_wrapper_iterator_helper_input(Polyhedron_3_Facet_handle_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_input(Polyhedron_3_Vertex_handle_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_input(Halfedge_pair_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_output(Polyhedron_3_Facet_handle_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_output(Polyhedron_3_Vertex_handle_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_output(Triple_of_int_SWIG_wrapper)
SWIG_CGAL_set_wrapper_iterator_helper_output(Facet_pair_SWIG_wrapper)
%types(Vector_3*,Vector_3);//needed so that the identifier SWIGTYPE_p_Vector_3 is generated
SWIG_CGAL_set_wrapper_iterator_helper_output(Vector_3)


%inline %{
  #ifndef SWIG
  namespace PMP=CGAL::Polygon_mesh_processing;
  namespace params=CGAL::Polygon_mesh_processing::parameters;
  #endif
  // input iterators
  typedef Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::input Vertex_range;
  typedef Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::input Facet_range;
  typedef Wrapper_iterator_helper<Halfedge_pair_SWIG_wrapper>::input Halfedge_pair_range;
  typedef Wrapper_iterator_helper<Point_3>::input Point_3_range;
  // output iterators
  typedef Wrapper_iterator_helper<Polyhedron_3_Vertex_handle_SWIG_wrapper>::output Vertex_ouput_iterator;
  typedef Wrapper_iterator_helper<Polyhedron_3_Facet_handle_SWIG_wrapper>::output Facet_output_iterator;
  typedef Wrapper_iterator_helper<Triple_of_int_SWIG_wrapper>::output Triple_int_output_iterator;
  typedef Wrapper_iterator_helper<Facet_pair_SWIG_wrapper>::output Facet_pair_output_iterator;
  typedef Wrapper_iterator_helper<Vector_3>::output Vector_3_output_iterator;

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
               Vertex_ouput_iterator vertex_output)
  {
    PMP::refine(P.get_data(), facet_range, facet_output, vertex_output);
  }
  void refine( Polyhedron_3_SWIG_wrapper& P,
               Facet_range facet_range,
               Facet_output_iterator facet_output,
               Vertex_ouput_iterator vertex_output,
               double density_control_factor)
  {
    PMP::refine(P.get_data(), facet_range, facet_output, vertex_output,
                params::fairing_continuity(density_control_factor));
  }
//   CGAL::Polygon_mesh_processing::triangulate_faces()
  void triangulate_faces(Polyhedron_3_SWIG_wrapper& P)
  {
    PMP::triangulate_faces(P.get_data());
  }
//   CGAL::Polygon_mesh_processing::isotropic_remeshing() (4.8)
//   CGAL::Polygon_mesh_processing::split_long_edges() (4.8)
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
                                    Vertex_ouput_iterator vertex_output)
  {
    PMP::triangulate_and_refine_hole(P.get_data(), h.get_data(), facet_output,
                                     vertex_output);
  }
  void triangulate_and_refine_hole( Polyhedron_3_SWIG_wrapper& P,
                                    Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                    Facet_output_iterator facet_output,
                                    Vertex_ouput_iterator vertex_output,
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
                                         Vertex_ouput_iterator vertex_output)
  {
    PMP::triangulate_refine_and_fair_hole(P.get_data(), h.get_data(),
                                          facet_output, vertex_output);
  }
  void triangulate_refine_and_fair_hole( Polyhedron_3_SWIG_wrapper& P,
                                         Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                         Facet_output_iterator facet_output,
                                         Vertex_ouput_iterator vertex_output,
                                         double density_control_factor)
  {
    PMP::triangulate_refine_and_fair_hole(P.get_data(), h.get_data(), facet_output,
                                          vertex_output,
                                          params::density_control_factor(density_control_factor));
  }
  void triangulate_refine_and_fair_hole( Polyhedron_3_SWIG_wrapper& P,
                                         Polyhedron_3_Halfedge_handle_SWIG_wrapper& h,
                                         Facet_output_iterator facet_output,
                                         Vertex_ouput_iterator vertex_output,
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
                                   Triple_int_output_iterator out)
  {
    PMP::triangulate_hole_polyline( CGAL::make_range(points.first, points.second),
                                    CGAL::make_range(third_points.first, third_points.second),
                                    out);
  }

//
// Predicate Functions and Classes
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
    PMP::reverse_face_orientations(CGAL::make_range(face_range.first, face_range.second), P.get_data());
  }
//   CGAL::Polygon_mesh_processing::orient_polygon_soup() TODO
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
    PMP::stitch_borders(P.get_data(), hedges);
  }
//   CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh() TODO
//   CGAL::Polygon_mesh_processing::remove_isolated_vertices() (4.8)
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
//   CGAL::Polygon_mesh_processing::compute_face_normals() TODO
  /*Vector_3 compute_face_normals(Polyhedron_3_SWIG_wrapper& P,
                                Vector_3_output_iterator& out)
  {
    PMP::compute_face_normals(P.get_data(), out);
  }*/
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
//   CGAL::Polygon_mesh_processing::compute_vertex_normals() TODO
  /*Vector_3 compute_face_normals(Polyhedron_3_SWIG_wrapper& P,
                                Vector_3_output_iterator& out)
  {
    PMP::compute_vertex_normals(P.get_data(), out);
  }*/
//   CGAL::Polygon_mesh_processing::compute_normals()
//
// Connected Components
//   CGAL::Polygon_mesh_processing::connected_component() TODO
//   CGAL::Polygon_mesh_processing::connected_components() TODO
//   CGAL::Polygon_mesh_processing::keep_large_connected_components() TODO
//   CGAL::Polygon_mesh_processing::keep_largest_connected_components() TODO
//   CGAL::Polygon_mesh_processing::keep_connected_components() TODO
//   CGAL::Polygon_mesh_processing::remove_connected_components() TODO
//
// Geometric Measure functions
//   CGAL::Polygon_mesh_processing::face_area() (4.8)
//   CGAL::Polygon_mesh_processing::area() (4.8)
//   CGAL::Polygon_mesh_processing::volume() (4.8)
//   CGAL::Polygon_mesh_processing::edge_length() (4.8)
//   CGAL::Polygon_mesh_processing::face_border_length() (4.8)
//
// Miscellaneous
//   CGAL::Polygon_mesh_slicer
//   CGAL::Side_of_triangle_mesh
//   CGAL::Polygon_mesh_processing::bbox_3() (4.8)
//   CGAL::Polygon_mesh_processing::border_halfedges() (4.8)

%}
