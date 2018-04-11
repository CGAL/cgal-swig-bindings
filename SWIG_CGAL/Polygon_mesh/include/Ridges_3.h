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

#ifndef SWIG_CGAL_POLYGON_MESH_RIDGES_3_H
#define SWIG_CGAL_POLYGON_MESH_RIDGES_3_H

#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <CGAL/Ridges.h>
#include <SWIG_CGAL/Polygon_mesh/include/Jet_fitting_3.h>
#include <CGAL/Umbilics.h>
#include <CGAL/iterator.h>

struct Ridges_3{

#ifndef SWIG
template <class Key, class Value>
struct Local_pmap{
  typedef Key key_type;
  typedef Value value_type;
  typedef Value& reference;
  typedef boost::lvalue_property_map_tag category;

  std::vector<Value>& m_values;
  Local_pmap(std::vector<Value>& values)
    : m_values(values)
  {}

  friend
  reference get(const Local_pmap& m, key_type k)
  {
    return m.m_values[k];
  }

  friend
  void put(Local_pmap& m, key_type k, const value_type& v)
  {
    m.m_values[k]=v;
  }

  reference operator[](key_type k){ return m_values[k]; }
  const value_type& operator[](key_type k) const { return m_values[k]; }
};


template <class Key, class Value>
static
Local_pmap<Key, Value> make_pm(std::vector<Value>& v)
{
  return Local_pmap<Key, Value>(v);
}

static
void copy_ridges(std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges,
                 PolygonMeshRidgesJNI& ridges)
{
  // first init the java arrays
  std::size_t total_nb_points = 0;
  std::size_t nb_ridges = cpp_ridges.size();
  for (std::size_t i=0; i<nb_ridges; ++i)
    total_nb_points+=cpp_ridges[i]->line()->size();
  ridges.reserve(nb_ridges, total_nb_points);
  // now do the copy
  ridges.nb_ridges_and_ranges[1]=0;
  for (std::size_t i=0; i<nb_ridges; ++i)
  {
    ridges.nb_ridges_and_ranges[i+2]=ridges.nb_ridges_and_ranges[i+1]+cpp_ridges[i]->line()->size();
    ridges.types[i]=cpp_ridges[i]->line_type();
    ridges.strengths[i]=cpp_ridges[i]->strength();
    ridges.sharpnesses[i]=cpp_ridges[i]->sharpness();
    typedef CGAL::Ridge_line<PolygonMesh>::ridge_halfhedge Pair_type;
    std::size_t k=0;
    BOOST_FOREACH(const Pair_type& p, *cpp_ridges[i]->line())
    {
      std::size_t id = ridges.nb_ridges_and_ranges[i+1]+k;
      ridges.halfedges[ id ]=p.first;
      ridges.barycentric_coordinates[ id ]=p.second;
      ++k;
    }
    delete cpp_ridges[i];
  }
}

static
void copy_umbilics(std::vector< CGAL::Umbilic<PolygonMesh>* > cpp_umbilics,
                   PolygonMeshUmbilicsJNI& umbilics)
{
  // first init the java arrays
  std::size_t total_nb_contour_halfedges = 0;
  std::size_t nb_umbilics = cpp_umbilics.size();
  for (std::size_t i=0; i<nb_umbilics; ++i)
    total_nb_contour_halfedges+=cpp_umbilics[i]->contour_list().size();
  umbilics.reserve(nb_umbilics, total_nb_contour_halfedges);
  // now do the copy
  umbilics.nb_umbilics_and_ranges[1]=0;
  for (std::size_t i=0; i<nb_umbilics; ++i)
  {
    umbilics.nb_umbilics_and_ranges[i+2]=umbilics.nb_umbilics_and_ranges[i+1]+cpp_umbilics[i]->contour_list().size();
    umbilics.types[i]=cpp_umbilics[i]->umbilic_type();
    umbilics.umbilics[i]=cpp_umbilics[i]->vertex();
    std::size_t k=0;
    BOOST_FOREACH(PolygonMesh::Halfedge_descriptor h, cpp_umbilics[i]->contour_list())
    {
      std::size_t id = umbilics.nb_umbilics_and_ranges[i+1]+k;
      umbilics.contour_halfedges[ id ]=h;
      ++k;
    }
    delete cpp_umbilics[i];
  }
}
#endif

//enums
enum Ridge_type {NO_RIDGE=0,
		 MAX_ELLIPTIC_RIDGE, MAX_HYPERBOLIC_RIDGE, MAX_CREST_RIDGE,
		 MIN_ELLIPTIC_RIDGE, MIN_HYPERBOLIC_RIDGE, MIN_CREST_RIDGE};

enum Umbilic_type { NON_GENERIC_UMBILIC = 0, ELLIPTIC_UMBILIC, HYPERBOLIC_UMBILIC};

// CGAL::compute_crest_ridges()
static
void compute_crest_ridges(PolygonMesh& pm,
                          PolygonMeshRidgesJNI ridges,
                          int order = 3)
{
  typedef PolygonMesh::Vertex_descriptor VD;
  std::size_t nv=num_vertices(pm);
  std::vector<double> vertex_k1_pm(nv), vertex_k2_pm(nv),
                      vertex_b0_pm(nv), vertex_b3_pm(nv),
                      vertex_P1_pm(nv), vertex_P2_pm(nv);
  std::vector<EPIC_Kernel::Vector_3> vertex_d1_pm(nv), vertex_d2_pm(nv);

  Jet_fitting_3::compute_differential_quantities_impl(pm,
                                  make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                                  make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                                  make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                                  make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                                  3, order);

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_crest_ridges(pm,
                             make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                             make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                             make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                             make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                             std::back_inserter(cpp_ridges),
                             CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

static
void compute_crest_ridges(PolygonMesh& pm,
                          PolygonMeshDoublePropertyJNI& vertex_double_map,  //vertex_k1_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map2, //vertex_k2_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map3, //vertex_b0_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map4, //vertex_b3_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map5, //vertex_d1_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map6, //vertex_d2_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map7, //vertex_P1_pm
                          PolygonMeshDoublePropertyJNI& vertex_double_map8, //vertex_P2_pm
                          PolygonMeshRidgesJNI ridges,
                          int order = 3) //either 3 or 4
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

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_crest_ridges(pm, vertex_k1_pm, vertex_k2_pm,
                                 vertex_b0_pm, vertex_b3_pm,
                                 vertex_d1_pm, vertex_d2_pm,
                                 vertex_P1_pm, vertex_P2_pm,
                                 std::back_inserter(cpp_ridges),
                                 CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

// CGAL::compute_max_ridges()
static
void compute_max_ridges(PolygonMesh& pm,
                        PolygonMeshRidgesJNI ridges,
                        int order = 3)
{
  typedef PolygonMesh::Vertex_descriptor VD;
  std::size_t nv=num_vertices(pm);
  std::vector<double> vertex_k1_pm(nv), vertex_k2_pm(nv),
                      vertex_b0_pm(nv), vertex_b3_pm(nv),
                      vertex_P1_pm(nv), vertex_P2_pm(nv);
  std::vector<EPIC_Kernel::Vector_3> vertex_d1_pm(nv), vertex_d2_pm(nv);

  Jet_fitting_3::compute_differential_quantities_impl(pm,
                                  make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                                  make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                                  make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                                  make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                                  3, order);

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_max_ridges(pm,
                           make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                           make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                           make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                           make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                           std::back_inserter(cpp_ridges),
                           CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

static
void compute_max_ridges(PolygonMesh& pm,
                        PolygonMeshDoublePropertyJNI& vertex_double_map,  //vertex_k1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map2, //vertex_k2_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map3, //vertex_b0_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map4, //vertex_b3_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map5, //vertex_d1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map6, //vertex_d2_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map7, //vertex_P1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map8, //vertex_P2_pm
                        PolygonMeshRidgesJNI ridges,
                        int order = 3) //either 3 or 4
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

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_max_ridges(pm, vertex_k1_pm, vertex_k2_pm,
                               vertex_b0_pm, vertex_b3_pm,
                               vertex_d1_pm, vertex_d2_pm,
                               vertex_P1_pm, vertex_P2_pm,
                               std::back_inserter(cpp_ridges),
                               CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

// CGAL::compute_min_ridges()
static
void compute_min_ridges(PolygonMesh& pm,
                        PolygonMeshRidgesJNI ridges,
                        int order = 3)
{
  typedef PolygonMesh::Vertex_descriptor VD;
  std::size_t nv=num_vertices(pm);
  std::vector<double> vertex_k1_pm(nv), vertex_k2_pm(nv),
                      vertex_b0_pm(nv), vertex_b3_pm(nv),
                      vertex_P1_pm(nv), vertex_P2_pm(nv);
  std::vector<EPIC_Kernel::Vector_3> vertex_d1_pm(nv), vertex_d2_pm(nv);

  Jet_fitting_3::compute_differential_quantities_impl(pm,
                                  make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                                  make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                                  make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                                  make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                                  3, order);

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_min_ridges(pm,
                           make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                           make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                           make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                           make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                           std::back_inserter(cpp_ridges),
                           CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

static
void compute_min_ridges(PolygonMesh& pm,
                        PolygonMeshDoublePropertyJNI& vertex_double_map,  //vertex_k1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map2, //vertex_k2_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map3, //vertex_b0_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map4, //vertex_b3_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map5, //vertex_d1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map6, //vertex_d2_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map7, //vertex_P1_pm
                        PolygonMeshDoublePropertyJNI& vertex_double_map8, //vertex_P2_pm
                        PolygonMeshRidgesJNI ridges,
                        int order = 3) //either 3 or 4
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

  std::vector< CGAL::Ridge_line<PolygonMesh>* > cpp_ridges;
  CGAL::compute_min_ridges(pm, vertex_k1_pm, vertex_k2_pm,
                               vertex_b0_pm, vertex_b3_pm,
                               vertex_d1_pm, vertex_d2_pm,
                               vertex_P1_pm, vertex_P2_pm,
                               std::back_inserter(cpp_ridges),
                               CGAL::enum_cast<CGAL::Ridge_order>(order));
  copy_ridges(cpp_ridges, ridges);
}

// CGAL::compute_umbilics()
static
void compute_umbilics(PolygonMesh& pm,
                      PolygonMeshUmbilicsJNI umbilics,
                      double size=2)
{
  typedef PolygonMesh::Vertex_descriptor VD;
  std::size_t nv=num_vertices(pm);
  std::vector<double> vertex_k1_pm(nv), vertex_k2_pm(nv),
                      vertex_b0_pm(nv), vertex_b3_pm(nv),
                      vertex_P1_pm(nv), vertex_P2_pm(nv);
  std::vector<EPIC_Kernel::Vector_3> vertex_d1_pm(nv), vertex_d2_pm(nv);

  Jet_fitting_3::compute_differential_quantities_impl(pm,
                                  make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                                  make_pm<VD>(vertex_b0_pm), make_pm<VD>(vertex_b3_pm),
                                  make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                                  make_pm<VD>(vertex_P1_pm), make_pm<VD>(vertex_P2_pm),
                                  3, 3);

  std::vector< CGAL::Umbilic<PolygonMesh>* > cpp_umbilics;

  CGAL::compute_umbilics(pm,
                         make_pm<VD>(vertex_k1_pm), make_pm<VD>(vertex_k2_pm),
                         make_pm<VD>(vertex_d1_pm), make_pm<VD>(vertex_d2_pm),
                         std::back_inserter(cpp_umbilics),
                         size);
  copy_umbilics(cpp_umbilics, umbilics);
}

static
void compute_umbilics(PolygonMesh& pm,
                      PolygonMeshDoublePropertyJNI& vertex_double_map,  //vertex_k1_pm
                      PolygonMeshDoublePropertyJNI& vertex_double_map2, //vertex_k2_pm
                      PolygonMeshDoublePropertyJNI& vertex_double_map3, //vertex_d1_pm
                      PolygonMeshDoublePropertyJNI& vertex_double_map4, //vertex_d2_pm
                      PolygonMeshUmbilicsJNI umbilics,
                      double size=2)
{
  PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                       PolygonMesh::Vertex_descriptor,
                       double> vertex_k1_pm(vertex_double_map),
                               vertex_k2_pm(vertex_double_map2);

  PolygonMesh_property<PolygonMeshDoublePropertyJNI,
                       PolygonMesh::Vertex_descriptor,
                       EPIC_Kernel::Vector_3> vertex_d1_pm(vertex_double_map3),
                               vertex_d2_pm(vertex_double_map4);

  std::vector< CGAL::Umbilic<PolygonMesh>* > cpp_umbilics;

  CGAL::compute_umbilics(pm,
                         vertex_k1_pm, vertex_k2_pm,
                         vertex_d1_pm, vertex_d2_pm,
                         std::back_inserter(cpp_umbilics),
                         size);
  copy_umbilics(cpp_umbilics, umbilics);
}

};

#endif