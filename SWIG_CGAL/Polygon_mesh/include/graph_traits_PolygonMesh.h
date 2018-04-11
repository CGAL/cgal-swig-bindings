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

#ifndef BOOST_GRAPH_TRAITS_POLYGON_MESH_JNI
#define BOOST_GRAPH_TRAITS_POLYGON_MESH_JNI

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <CGAL/boost/graph/iterator.h>
#include <CGAL/boost/graph/Euler_operations.h>

#include <CGAL/assertions.h>

#include "PolygonMesh.h"

namespace boost {

   template<>
   struct graph_traits<PolygonMesh>{
      private:
         typedef PolygonMesh PM;
  
         struct PM_graph_traversal_category : public virtual boost::bidirectional_graph_tag,
                                       public virtual boost::vertex_list_graph_tag,
                                       public virtual boost::edge_list_graph_tag
  {};

      public:
         // Graph
         typedef PM::Vertex_descriptor vertex_descriptor;
         typedef PM::Edge_descriptor edge_descriptor;
         typedef boost::undirected_tag directed_category;
         typedef boost::disallow_parallel_edge_tag edge_parallel_category;
         typedef PM_graph_traversal_category traversal_category;

         // HalfedgeGraph
         typedef PM::Halfedge_descriptor halfedge_descriptor;

         // FaceGraph
         typedef PM::Face_descriptor face_descriptor;
  
         // VertexListGraph
         typedef PM::Vertex_iterator vertex_iterator;
         typedef int vertices_size_type;

         // EdgeListGraph
         typedef PM::Edge_iterator edge_iterator;
         typedef int edges_size_type;

         // HalfEdgeListGraph
         typedef PM::Halfedge_iterator halfedge_iterator;
         typedef int halfedges_size_type;

         // FaceListGraph
         typedef PM::Face_iterator face_iterator;
         typedef int faces_size_type;

         // IncidenceGraph
         typedef int degree_size_type;
         typedef CGAL::In_edge_iterator<PM> in_edge_iterator;

         typedef CGAL::Out_edge_iterator<PM> out_edge_iterator;

         // nulls
         static vertex_descriptor null_vertex() { return vertex_descriptor(); }
         static edge_descriptor null_edge() { return edge_descriptor(); }
         static halfedge_descriptor null_halfedge() { return halfedge_descriptor(); }
         static face_descriptor null_face() { return face_descriptor(); }
   };

  template<>
  struct graph_traits<const PolygonMesh>
    : public graph_traits<PolygonMesh>
  {};
}


// Graph

boost::graph_traits<PolygonMesh>::vertices_size_type
num_vertices(const PolygonMesh& pm) {
   return pm.boundOnVertexDescriptor();
}

boost::graph_traits<PolygonMesh>::edges_size_type
num_edges(const PolygonMesh& pm) {
   return pm.boundOnEdgeDescriptor();
}

boost::graph_traits<PolygonMesh>::degree_size_type
degree(boost::graph_traits<PolygonMesh>::vertex_descriptor v, 
       const PolygonMesh& pm) {
   return pm.vertexDegree(v);
}

// boost::graph_traits<PolygonMesh>::degree_size_type
// in_degree(boost::graph_traits<PolygonMesh>::vertex_descriptor v, 
//        const PolygonMesh& pm) {
//    return pm.vertexDegree(v);
// }

// boost::graph_traits<PolygonMesh>::degree_size_type
// out_degree(boost::graph_traits<PolygonMesh>::vertex_descriptor v, 
//        const PolygonMesh& pm) {
//    return pm.vertexDegree(v);
// }

boost::graph_traits<PolygonMesh >::vertex_descriptor
source(boost::graph_traits<PolygonMesh>::halfedge_descriptor h, 
       const PolygonMesh& pm) {
   return pm.source(h);
}

boost::graph_traits<PolygonMesh>::vertex_descriptor
source(boost::graph_traits<PolygonMesh>::edge_descriptor e, 
       const PolygonMesh& pm) {
   return pm.source(e.halfedge_descriptor());
}

boost::graph_traits<PolygonMesh>::vertex_descriptor
target(boost::graph_traits<PolygonMesh>::halfedge_descriptor h, 
       const PolygonMesh& pm) {
   return pm.target(h);
}

boost::graph_traits<PolygonMesh>::vertex_descriptor
target(boost::graph_traits<PolygonMesh>::edge_descriptor e, 
       const PolygonMesh& pm) {
    return pm.target(e.halfedge_descriptor());
}

boost::graph_traits<PolygonMesh>::halfedge_descriptor
halfedge(boost::graph_traits<PolygonMesh >::vertex_descriptor v,
         const PolygonMesh& pm) {
  return pm.vertexHalfedge(v);
}
    
CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::vertex_iterator>
vertices(const PolygonMesh& pm) {
  return pm.vertices(); 
}

 
CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::edge_iterator>
edges(const PolygonMesh& pm) {
  return pm.edges(); 
}


CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::in_edge_iterator>
in_edges(boost::graph_traits<PolygonMesh>::vertex_descriptor v,
         const PolygonMesh& pm) {
  typedef boost::graph_traits<PolygonMesh>::in_edge_iterator Iter;
  return CGAL::make_range(Iter(halfedge(v,pm),pm), Iter(halfedge(v,pm),pm,1));
}


CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::out_edge_iterator>
out_edges(boost::graph_traits<PolygonMesh>::vertex_descriptor v,
          const PolygonMesh& pm) {
  typedef boost::graph_traits<PolygonMesh>::out_edge_iterator Iter;
  return CGAL::make_range(Iter(halfedge(v,pm),pm), Iter(halfedge(v,pm),pm,1));
}


// std::pair<boost::graph_traits<PolygonMesh >::edge_descriptor,
//           bool>
// edge(boost::graph_traits<PolygonMesh >::vertex_descriptor u, 
//      boost::graph_traits<PolygonMesh >::vertex_descriptor v, 
//      const PolygonMesh& pm) {
//    // TODO must this be the DIRECTED edge or the 
//   boost::graph_traits<PolygonMesh >::halfedge_descriptor 
//     he1(pm.halfedge(u, v));
//    if(pm.isValidHalfedge(he1)){
//       return std::make_pair(pm.edge(he1), true);
//    }
//   return std::make_pair(boost::graph_traits<PolygonMesh>::null_edge(), false);
// }


//
// HalfedgeGraph
//
boost::graph_traits<PolygonMesh>::halfedge_descriptor
next(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
     const PolygonMesh& pm) {
  return pm.next(h);
}

boost::graph_traits<PolygonMesh>::halfedge_descriptor
prev(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
     const PolygonMesh& pm) {
  return pm.prev(h);
}

boost::graph_traits<PolygonMesh>::halfedge_descriptor
opposite(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
         const PolygonMesh& pm) {
  return pm.opposite(h);
}

boost::graph_traits<PolygonMesh>::edge_descriptor
edge(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
     const PolygonMesh&) {
  return PolygonMesh::Edge_descriptor(h);
}

boost::graph_traits<PolygonMesh>::halfedge_descriptor
halfedge(boost::graph_traits<PolygonMesh >::edge_descriptor e,
         const PolygonMesh&) {
  return e.halfedge_descriptor();
}


std::pair<
  boost::graph_traits<PolygonMesh>::halfedge_descriptor,
  bool
>
halfedge(boost::graph_traits<PolygonMesh>::vertex_descriptor u,
         boost::graph_traits<PolygonMesh>::vertex_descriptor v,
         const PolygonMesh& pm) {
  boost::graph_traits<PolygonMesh >::halfedge_descriptor h = pm.halfedge(u, v);
  return std::make_pair(h, pm.isValidHalfedge(h));
}

//
// HalfedgeListGraph
//
CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::halfedge_iterator>
halfedges(const PolygonMesh& pm) {
  return pm.halfedges();
}

boost::graph_traits<PolygonMesh>::halfedges_size_type
num_halfedges(const PolygonMesh& pm) {
   return pm.boundOnHalfedgeDescriptor();
}


//
// MutableHalfedgeGraph
//
void
set_next(boost::graph_traits<PolygonMesh>::halfedge_descriptor h1, 
         boost::graph_traits<PolygonMesh>::halfedge_descriptor h2,
         PolygonMesh& pm) {
  pm.setNext(h1, h2);
}

void
set_target(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
           boost::graph_traits<PolygonMesh>::vertex_descriptor v,
           PolygonMesh& pm) {
  pm.setTarget(h, v);
}

void
set_halfedge(boost::graph_traits<PolygonMesh>::vertex_descriptor v,
             boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
             PolygonMesh& pm) {
  pm.setVertexHalfedge(v, h);
}


// template<typename P>
// void
// collect_garbage(PolygonMesh& pm)
// {
//  pm.collect_garbage();
// }

boost::graph_traits<PolygonMesh>::edge_descriptor
add_edge(PolygonMesh& pm) {
  return pm.addEdge();
}


//
// FaceGraph
//
boost::graph_traits<PolygonMesh>::halfedge_descriptor
halfedge(boost::graph_traits<PolygonMesh>::face_descriptor f,
     const PolygonMesh& pm) {
  return pm.faceHalfedge(f);
}
  
boost::graph_traits<PolygonMesh>::face_descriptor
face(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
     const PolygonMesh& pm) {
  return pm.face(h);
}



//
// MutableFaceGraph
//
void
set_face(boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
         boost::graph_traits<PolygonMesh>::face_descriptor f,
         PolygonMesh& pm) {
  pm.setFace(h, f);
}

  
void
set_halfedge(boost::graph_traits<PolygonMesh>::face_descriptor f,
             boost::graph_traits<PolygonMesh>::halfedge_descriptor h,
             PolygonMesh& pm) {
  pm.setFaceHalfedge(f, h);
}

 
//
// FaceListGraph
//
boost::graph_traits<PolygonMesh>::faces_size_type
num_faces(const PolygonMesh& pm)
{
  return pm.boundOnFaceDescriptor();
}
  
CGAL::Iterator_range<boost::graph_traits<PolygonMesh>::face_iterator>
faces(const PolygonMesh& pm)
{
  return pm.faces(); 
}
 

boost::graph_traits<PolygonMesh>::vertex_descriptor
add_vertex(PolygonMesh& pm) {
  return pm.addVertex();
}


void
remove_vertex(boost::graph_traits<PolygonMesh>::vertex_descriptor v, 
              PolygonMesh& pm) {
  pm.removeVertex(v);
}

void
remove_edge(boost::graph_traits<PolygonMesh>::edge_descriptor e, 
            PolygonMesh& pm) {
  pm.removeEdge(e);
}

// void
// remove_edge(boost::graph_traits<PolygonMesh>::edge_iterator eiter, 
//             PolygonMesh& pm) {
//   remove_edge(*eiter, pm);
// }
  
//void
//remove_edge(boost::graph_traits<PolygonMesh>::vertex_descriptor u, 
//            boost::graph_traits<PolygonMesh>::vertex_descriptor v, 
//            PolygonMesh& pm) {
//  std::pair<boost::graph_traits<PolygonMesh >::edge_descriptor, bool> e = edge(u, v, pm);
//  if(e.second)
//   remove_edge(e.first,pm);
//}


void
remove_face(boost::graph_traits<PolygonMesh>::face_descriptor f, 
            PolygonMesh& pm) {
  pm.removeFace(f);
}

boost::graph_traits<PolygonMesh>::face_descriptor
add_face(PolygonMesh& pm) {
  return pm.addFace();
}

void reserve (PolygonMesh& pm, int nv, int ne, int nf)
{
  pm.reserve(nv, ne, nf);
}

// template<typename InputIterator>
// typename boost::graph_traits<PolygonMesh>::face_descriptor
// add_face(InputIterator begin, InputIterator end, PolygonMesh& pm) {
//   std::vector<boost::graph_traits<PolygonMesh >::vertex_descriptor> 
//     v(begin, end);
//   return CGAL::Euler::add_face(v, pm);
// }

#endif
