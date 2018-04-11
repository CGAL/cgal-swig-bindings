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

package CGAL.Polygon_mesh;

import java.util.PrimitiveIterator;

public interface IPolygonMeshBase {

  /**
   * Returns the number of vertices
   */
  public int numberOfVertices();

  /**
   * Returns the number of edges
   */
  public int numberOfEdges();

  /**
   * Returns the number of halfedges
   */
  public int numberOfHalfedges();

  /**
   * Returns the number of faces
   */
  public int numberOfFaces();

  /**
   * Returns an upper bound on vertex descriptors
   */
  public int boundOnVertexDescriptor();

  /**
   * Returns an upper bound on edge descriptors
   */
  public int boundOnEdgeDescriptor();

  /**
   * Returns an upper bound on halfedge descriptors
   */
  public int boundOnHalfedgeDescriptor();

  /**
   * Returns an upper bound on face descriptors
   */
  public int boundOnFaceDescriptor();

  /**
   * Checks whether the given vertex descriptor is valid
   */
  public boolean isValidVertex(int v);

  /**
   * Checks whether the given edge descriptor is valid
   */
  public boolean isValidEdge(int e);

  /**
   * Checks whether the given halfedge descriptor is valid
   */
  public boolean isValidHalfedge(int h);

  /**
   * Checks whether the given face descriptor is valid
   */
  public boolean isValidFace(int f);

  /**
   * Returns the next halfedge around its face.
   */
  public int next(int h);

  /**
   * Returns the previous halfedge around its face.
   */
  public int prev(int h);

  /**
   * Returns the halfedge with source and target swapped
   */
  public int opposite(int h);

  /**
   * Sets the successor of h1 around a face to h2, and the predecessor of h2 to h1
   */
  public void setNext(int h1, int h2);

  /**
   * Sets the target vertex of h and the source of opposite(h) to v
   */
  public void setTarget(int h, int v);

  /**
   * Sets the halfedge of v to h. The target vertex of h must be v
   */
  public void setVertexHalfedge(int v, int h);

  /**
   * Adds a new vertex to the graph wothout initializing the connectivity
   */
  public int addVertex();

  /**
   * Removes v from the graph
   */
  public void removeVertex(int v);

  /**
   * Adds two opposite halfedges to the graph without initializing the connectivity
   */
  public int addEdge();

  /**
   * Removes the two halfedges corresponding to e from the graph
   */
  public void removeEdge(int e);

  /**
   * Returns the face incident to halfedge h
   */
  public int face(int h);

  /**
   * Returns a halfedge incident to face f
   */
  public int faceHalfedge(int f);

  /**
   * Sets the corresponding face of h to f
   */
  public void setFace(int h, int f);

  /**
   * Sets the corresponding halfedge of f to h
   */
  public void setFaceHalfedge(int f, int h);

  /**
   * Adds a new face to the graph without initializing the connectivity
   */
  public int addFace();

  /**
   * Removes f from the graph
   */
  public void removeFace(int f);

  /**
   * The target vertex of h
   */
  public int target(int h);

  /**
   * The source vertex of h
   */
  public int source(int h);

  /**
   * A halfedge with target v
   */
  public int vertexHalfedge(int v);

  /**
   * The edge corresponding to h and opposite(h)
   */
  public int edge(int h);

  /**
   * One of the halfedges corresponding to e
   */
  public int edgeHalfedge(int e);

  /**
   * The halfedge with source u and target v. To check if the halfedge is actually present, use {@link #isValidHalfedge(int)}
   */
  public int halfedge(int source, int target);

  /**
   * Returns the degree of a face, that is, the number of incident half edges (or edges)
   */
  public int faceDegree(int f);

  /**
   * Returns the degree of a vertex, that is, the number of incident edges (or half edges that have this vertex as a source, or equivalently as a target)
   */
  public int vertexDegree(int v);

  /**
   * Returns the x coordinate of a vertex
   */
  public double vertexX(int v);

  /**
   * Returns the y coordinate of a vertex
   */
  public double vertexY(int v);

  /**
   * Returns the z coordinate of a vertex
   */
  public double vertexZ(int v);

  /**
   * Sets the x coordinate of a vertex
   */
  public void setVertexX(int v, double d);

  /**
   * Sets the y coordinate of a vertex
   */
  public void setVertexY(int v, double d);

  /**
   * Sets the z coordinate of a vertex
   */
  public void setVertexZ(int v, double d);

  /**
   * Returns an iterable on all vertices
   */
  public PrimitiveIterator.OfInt vertices();

  /**
   * Returns an iterable on all edges
   */
  public PrimitiveIterator.OfInt edges();

  /**
   * Returns an iterable on all halfedges
   */
  public PrimitiveIterator.OfInt halfedges();

  /**
   * Returns an iterable on all faces
   */
  public PrimitiveIterator.OfInt faces();

  /**
   * Returns the index associated to a given vertex, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the vertex is not valid.
   */
  int vertexIndex(int v);
  
  /**
   * Returns the vertex associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfVertices()}.
   */
  int vertexAt(int i);
  
  /**
   * Returns the index associated to a given edge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the edge is not valid.
   */
  int edgeIndex(int e);
  
  /**
   * Returns the edge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfEdges()}.
   */
  int edgeAt(int i);
  
  /**
   * Returns the index associated to a given halfedge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the halfedge is not valid.
   */
  int halfedgeIndex(int h);
  
  /**
   * Returns the halfedge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfHalfedges()}.
   */
  int halfedgeAt(int i);
  
  /**
   * Returns the index associated to a given face, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the face is not a valid face.
   */
  int faceIndex(int f);
  
  /**
   * Returns the face associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfFaces()}.
   */
  int faceAt(int i);

  /**
   * Returns a copy of the mesh
   */
  PolygonMeshBase copy();
}
