// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

#ifndef SWIG_CGAL_POLYGON_MESH_JET_FITTING_3_H
#define SWIG_CGAL_POLYGON_MESH_JET_FITTING_3_H

#include <CGAL/Monge_via_jet_fitting.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <CGAL/boost/graph/iterator.h>
#include <limits>



struct Jet_fitting_3{

#ifndef SWIG
  template <class VertexPointMap>
  static
  void get_neighbors(PolygonMesh::Vertex_descriptor v, PolygonMesh& pm,
                     const VertexPointMap& vpm,
                     std::vector<EPIC_Kernel::Point_3>& points,
                     unsigned int min_nb_points=5, unsigned int k_ring=0)
  {
    boost::unordered_set<PolygonMesh::Vertex_descriptor> selected;
    selected.insert(v);
    unsigned int k=0;
    std::vector<PolygonMesh::Vertex_descriptor> vertex_stack;
    vertex_stack.push_back(v);
    do{
      bool new_vertices=false;
      std::vector<PolygonMesh::Vertex_descriptor> last_ring_vertices;
      last_ring_vertices.swap(vertex_stack);

      BOOST_FOREACH(PolygonMesh::Vertex_descriptor lv, last_ring_vertices)
      {
        BOOST_FOREACH(PolygonMesh::Halfedge_descriptor h, CGAL::halfedges_around_target(lv, pm))
        {
          PolygonMesh::Vertex_descriptor src = source(h, pm);
          if ( selected.insert(src).second)
          {
            vertex_stack.push_back( src );
            points.push_back( get(vpm, src) );
            new_vertices=true;
          }
        }
      }
      ++k;
      if (!new_vertices) break;
    }while(points.size()<min_nb_points || k==k_ring);
  }

  template <class VertexVectorMap, class VertexDoubleMap>
  static
  void compute_differential_quantities_impl(PolygonMesh& pm,
                                            VertexDoubleMap vertex_k1_map,
                                            VertexDoubleMap vertex_k2_map,
                                            VertexDoubleMap vertex_b0_map,
                                            VertexDoubleMap vertex_b3_map,
                                            VertexVectorMap vertex_d1_map,
                                            VertexVectorMap vertex_d2_map,
                                            VertexDoubleMap vertex_P1_map,
                                            VertexDoubleMap vertex_P2_map,
                                            int d_fitting=3,
                                            int d_monge=4)
  {
    typedef CGAL::Monge_via_jet_fitting<EPIC_Kernel> Monge_via_jet_fitting;
    typedef Monge_via_jet_fitting::Monge_form Monge_form;

    const  unsigned int min_nb_points = (d_fitting + 1) * (d_fitting + 2) / 2;

    //container for approximation points
    std::vector<EPIC_Kernel::Point_3> in_points;

    typedef boost::property_map<PolygonMesh,CGAL::vertex_point_t>::type VPM;
    VPM vpm = get(CGAL::vertex_point,pm);

    BOOST_FOREACH(PolygonMesh::Vertex_descriptor v, vertices(pm))
    {
      in_points.clear();
      Monge_form monge_form;
      Monge_via_jet_fitting monge_fit;

      //gather points around the vertex using rings
      get_neighbors(v, pm, vpm, in_points, min_nb_points);

      //exit if the nb of points is too small
      if ( in_points.size() < min_nb_points )
      {
        std::cerr << "Too few points to perform the fitting\n";
        throw "Too few points to perform the fitting";
      }

      //For Ridges we need at least 3rd order info
      assert( d_monge >= 3);
      // run the main fct : perform the fitting
      monge_form = monge_fit(in_points.begin(), in_points.end(),
                             d_fitting, d_monge);

      //switch min-max ppal curv/dir wrt the mesh orientation
      const EPIC_Kernel::Vector_3 n = CGAL::Polygon_mesh_processing::compute_vertex_normal(v, pm);
      monge_form.comply_wrt_given_normal(n);

      //Store monge data needed for ridge computations in property maps
      put(vertex_d1_map, v, monge_form.maximal_principal_direction());
      put(vertex_d2_map, v, monge_form.minimal_principal_direction());
      put(vertex_k1_map, v, monge_form.coefficients()[0]);
      put(vertex_k2_map, v, monge_form.coefficients()[1]);
      put(vertex_b0_map, v, monge_form.coefficients()[2]);
      put(vertex_b3_map, v, monge_form.coefficients()[5]);
      if ( d_monge >= 4) {
        //= 3*b1^2+(k1-k2)(c0-3k1^3)
        put(vertex_P1_map, v,
          3*monge_form.coefficients()[3]*monge_form.coefficients()[3]
          +(monge_form.coefficients()[0]-monge_form.coefficients()[1])
          *(monge_form.coefficients()[6]
            -3*monge_form.coefficients()[0]*monge_form.coefficients()[0]
            *monge_form.coefficients()[0]));
        //= 3*b2^2+(k2-k1)(c4-3k2^3)
        put(vertex_P2_map, v,
          3*monge_form.coefficients()[4]*monge_form.coefficients()[4]
          +(-monge_form.coefficients()[0]+monge_form.coefficients()[1])
          *(monge_form.coefficients()[10]
            -3*monge_form.coefficients()[1]*monge_form.coefficients()[1]
            *monge_form.coefficients()[1]));
      }
    }
  }

  template <class VertexVectorMap, class VertexDoubleMap>
  static void estimate_curvature_impl(PolygonMesh& pm,
                                      VertexVectorMap min_curv,
                                      VertexVectorMap max_curv,
                                      VertexDoubleMap min_curv_value,
                                      VertexDoubleMap max_curv_value)
  {
    typedef boost::graph_traits<PolygonMesh> GT;
    typedef GT::vertex_descriptor vertex_descriptor;
    typedef GT::halfedge_descriptor halfedge_descriptor;

    typedef CGAL::Monge_via_jet_fitting<EPIC_Kernel> Fitting;
    typedef Fitting::Monge_form Monge_form;
    typedef EPIC_Kernel::Point_3 Point;
    typedef EPIC_Kernel::Vector_3 Vector;

    boost::property_map<PolygonMesh, boost::vertex_point_t>::type vpm = get(boost::vertex_point, pm);

    BOOST_FOREACH(vertex_descriptor vd, vertices(pm))
    {
      std::vector<Point> points;

      // pick central point
      Point central_point = get(vpm, vd);
      points.push_back(central_point);

      BOOST_FOREACH(halfedge_descriptor h, CGAL::halfedges_around_target(vd, pm))
      {
        Point p = get(vpm, source(h, pm));
        points.push_back(p);
      }
      if(points.size() > 5)
      {
        // estimate curvature by fitting
        Fitting monge_fit;
        const int dim_monge = 2;
        const int dim_fitting = 2;
        Monge_form monge_form = monge_fit(points.begin(),points.end(),dim_fitting,dim_monge);

        // make monge form comply with vertex normal (to get correct
        // orientation)
        Vector n = CGAL::Polygon_mesh_processing::compute_vertex_normal(vd, pm);
        monge_form.comply_wrt_given_normal(n);

        Vector umin = monge_form.minimal_principal_direction();
        Vector umax = monge_form.maximal_principal_direction();

        put(min_curv, vd, umin);
        put(max_curv, vd, umax);
        put(min_curv_value, vd, monge_form.principal_curvatures(1));
        put(max_curv_value, vd, monge_form.principal_curvatures(0));
      }
      else
      {
        put(min_curv, vd, Vector(0,0,0));
        put(max_curv, vd, Vector(0,0,0));
        put(min_curv_value, vd, 0);
        put(max_curv_value, vd, 0);
      }
    }
  }
#endif

  static void estimate_curvature_values(PolygonMesh& pm,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map3,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map4)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         double> min_curv_value(vertex_double_map3), max_curv_value(vertex_double_map4);

    std::vector<EPIC_Kernel::Vector_3> min_curv(num_vertices(pm)), max_curv(num_vertices(pm));

    estimate_curvature_impl(pm,
                            CGAL::make_property_map(min_curv),
                            CGAL::make_property_map(max_curv),
                            min_curv_value, max_curv_value);

  }

  static void estimate_curvature(PolygonMesh& pm,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map2,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map3,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map4)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         EPIC_Kernel::Vector_3> min_curv(vertex_double_map), max_curv(vertex_double_map2);
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         double> min_curv_value(vertex_double_map3), max_curv_value(vertex_double_map4);

    estimate_curvature_impl(pm, min_curv, max_curv, min_curv_value, max_curv_value);
  }

  static void estimate_curvature_directions(PolygonMesh& pm,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map,
                                 PolygonMeshDoublePropertyJNI& vertex_double_map2)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         EPIC_Kernel::Vector_3> min_curv(vertex_double_map), max_curv(vertex_double_map2);
    std::vector<double> min_curv_value(num_vertices(pm), 0), max_curv_value(num_vertices(pm),0);

    estimate_curvature_impl(pm, min_curv, max_curv,
                            CGAL::make_property_map(min_curv_value),
                            CGAL::make_property_map(max_curv_value));
  }

  static
  void compute_differential_quantities(PolygonMesh& pm,
                                       PolygonMeshDoublePropertyJNI& vertex_double_map,  //vertex_k1_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map2, //vertex_k2_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map3, //vertex_b0_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map4, //vertex_b3_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map5, //vertex_d1_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map6, //vertex_d2_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map7, //vertex_P1_pm
                                       PolygonMeshDoublePropertyJNI& vertex_double_map8, //vertex_P2_pm
                                       int d_fitting=3,
                                       int d_monge=4)
  {
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         double>  vertex_k1_pm(vertex_double_map),
                                  vertex_k2_pm(vertex_double_map2),
                                  vertex_b0_pm(vertex_double_map3),
                                  vertex_b3_pm(vertex_double_map4),
                                  vertex_P1_pm(vertex_double_map7),
                                  vertex_P2_pm(vertex_double_map8);
    PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                         PolygonMesh::Vertex_descriptor,
                         EPIC_Kernel::Vector_3> vertex_d1_pm(vertex_double_map5),
                                                vertex_d2_pm(vertex_double_map6);
    compute_differential_quantities_impl(pm,
                                         vertex_k1_pm, vertex_k2_pm,
                                         vertex_b0_pm, vertex_b3_pm,
                                         vertex_d1_pm, vertex_d2_pm,
                                         vertex_P1_pm, vertex_P2_pm,
                                         d_fitting, d_monge);

  }
};

#endif // SWIG_CGAL_POLYGON_MESH_JET_FITTING_3_H
