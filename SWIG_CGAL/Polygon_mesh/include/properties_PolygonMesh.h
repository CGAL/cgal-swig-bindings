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

#ifndef BOOST_PROPERTIES_POLYGON_MESH_JNI
#define BOOST_PROPERTIES_POLYGON_MESH_JNI

#include <CGAL/assertions.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/properties.h>

#include <boost/cstdint.hpp>
#include <boost/unordered_map.hpp>

#include "graph_traits_PolygonMesh.h"
#include "PolygonMesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel::Point_3 Point;
typedef CGAL::Exact_predicates_inexact_constructions_kernel::Vector_3 Vector;

// PolygonMesh property map that is wrapping points on the fly
class PM_point_map
{
   private:
      const PolygonMesh* faceGraph;

   public:
      
      typedef boost::read_write_property_map_tag category;
      typedef Point value_type;
      typedef Point reference;
      typedef boost::graph_traits<PolygonMesh>::vertex_descriptor key_type;
    
  PM_point_map() : faceGraph(NULL) {}

  PM_point_map(const PolygonMesh& fg): faceGraph(&fg) {}
    
  PM_point_map(const PM_point_map& pm) : faceGraph(pm.faceGraph) {}

  reference operator[](key_type v) const
  {
    CGAL_assertion(faceGraph!=NULL);
    return value_type(faceGraph->vertexX(v), faceGraph->vertexY(v), faceGraph->vertexZ(v));
  }

  friend reference get(const PM_point_map& pm, key_type v)
  {
    return pm[v];
  }

  friend void put(const PM_point_map& pm, key_type v, const value_type& p) {
    CGAL_precondition(pm.faceGraph!=NULL);
    PolygonMesh& fg = const_cast<PolygonMesh&>(*pm.faceGraph);
    fg.setVertexX(v, p[0]);
    fg.setVertexY(v, p[1]);
    fg.setVertexZ(v, p[2]);
  }

};

// generic property wrapper for properties based on PolygonMeshPropertyJNI
template <class PolygonMeshProperty, class Key, class Value>
struct PolygonMesh_property
{
  PolygonMeshProperty* base_ptr;
  typedef Key key_type;
  typedef Value value_type;
  typedef value_type reference;
  typedef boost::read_write_property_map_tag category;

  PolygonMesh_property()
    : base_ptr(NULL)
  {}

  PolygonMesh_property(PolygonMeshProperty& base)
    : base_ptr(&base)
  {}

  friend reference get(const PolygonMesh_property& map, key_type k)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    return static_cast<Value>(map.base_ptr->values[k]);
  }

  friend void put(const PolygonMesh_property& map, key_type k, const value_type& v)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    map.base_ptr->values[k] = v;
  }
};

template <class PolygonMeshProperty, class Key>
struct PolygonMesh_property<PolygonMeshProperty, Key, Vector>
{
  PolygonMeshProperty* base_ptr;
  typedef Key key_type;
  typedef Vector value_type;
  typedef value_type reference;
  typedef boost::read_write_property_map_tag category;

  PolygonMesh_property()
    : base_ptr(NULL)
  {}


  PolygonMesh_property(PolygonMeshProperty& base)
    : base_ptr(&base)
  {}

  friend reference get(const PolygonMesh_property& map, key_type k)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    return Vector(map.base_ptr->values[3*k], map.base_ptr->values[3*k+1], map.base_ptr->values[3*k+2]);
  }

  friend void put(const PolygonMesh_property& map, key_type k, const value_type& v)
  {
    CGAL_assertion(map.base_ptr!=NULL);
    map.base_ptr->values[3*k] = v.x();
    map.base_ptr->values[3*k+1] = v.y();
    map.base_ptr->values[3*k+2] = v.z();
  }
};

// class from which index properties are derived
template <typename VEF>
class PM_index_pmap : public boost::put_get_helper<boost::uint32_t, PM_index_pmap<VEF> >
{
public:
  typedef boost::readable_property_map_tag category;
  typedef boost::uint32_t                  value_type;
  typedef boost::uint32_t                  reference;
  typedef VEF                              key_type;

  value_type operator[](const key_type& vd) const
  {
    return vd;
  }
};

namespace boost {

//
// vertex point
//
   template<>
   struct property_map<PolygonMesh, boost::vertex_point_t > {
     typedef Point P;
     typedef PM_point_map type;
     typedef type const_type;
   };
   
   property_map<PolygonMesh, boost::vertex_point_t>::const_type
   get(boost::vertex_point_t, const PolygonMesh& fg) {
         return PM_point_map(fg);
   }

//
// vertex_index
//
   template<>
   struct property_map<PolygonMesh, boost::vertex_index_t >
   {
      typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::vertex_descriptor> type;
      typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::vertex_descriptor> const_type;
   };
   
   property_map<PolygonMesh, boost::vertex_index_t>::const_type
   get(const boost::vertex_index_t&, const PolygonMesh&)
   {
      return PM_index_pmap<boost::graph_traits<PolygonMesh>::vertex_descriptor>();
   }

//
// face_index
//
   template<>
   struct property_map<PolygonMesh, boost::face_index_t >
   {
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::face_descriptor> type;
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::face_descriptor> const_type;
   };
   
   property_map<PolygonMesh, boost::face_index_t>::const_type
   get(const boost::face_index_t&, const PolygonMesh&)
   {
     return PM_index_pmap<boost::graph_traits<PolygonMesh>::face_descriptor>();
   }

//
// edge_index
//
   template<>
   struct property_map<PolygonMesh, boost::edge_index_t >
   {
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::edge_descriptor> type;
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::edge_descriptor> const_type;
   };
   
   property_map<PolygonMesh, boost::edge_index_t>::const_type
   get(const boost::edge_index_t&, const PolygonMesh&)
   {
     return PM_index_pmap<boost::graph_traits<PolygonMesh>::edge_descriptor>();
   }

//
// halfedge_index
//
   template <>
   struct property_map<PolygonMesh, boost::halfedge_index_t >
   {
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::halfedge_descriptor> type;
     typedef PM_index_pmap<boost::graph_traits<PolygonMesh>::halfedge_descriptor> const_type;
   };
   
   property_map<PolygonMesh, boost::halfedge_index_t>::const_type
   get(const boost::halfedge_index_t&, const PolygonMesh&)
   {
     return PM_index_pmap<boost::graph_traits<PolygonMesh>::halfedge_descriptor>();
   }
} //end of namespace boost

#if CGAL_VERSION_NR > 1041200000
namespace CGAL{
#else
namespace boost{
#endif
  template<>
  struct graph_has_property<PolygonMesh, boost::vertex_index_t>
    : CGAL::Tag_true {};
  template<>
  struct graph_has_property<PolygonMesh, boost::edge_index_t>
    : CGAL::Tag_true {};
  template<>
  struct graph_has_property<PolygonMesh, boost::halfedge_index_t>
    : CGAL::Tag_true {};
  template<>
  struct graph_has_property<PolygonMesh, boost::face_index_t>
    : CGAL::Tag_true {};
  template<>
  struct graph_has_property<PolygonMesh, CGAL::vertex_point_t>
    : CGAL::Tag_true {};
  // template<>
  // struct graph_has_property<PolygonMesh, edge_weight_t>
  //  : CGAL::Tag_true {};
} // end of namespace CGAL/boost


#endif
