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

#ifndef POLYGON_MESH_FACE_GRAPH_JNI_BASE
#define POLYGON_MESH_FACE_GRAPH_JNI_BASE

#include <CGAL/assertions.h>
#include <CGAL/Iterator_range.h>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/unordered_map.hpp>

class PolygonMesh {

protected:

  // HE connectivity
  int* nextHE;
  int* prevHE;
  int* heVertex;
  int* heFace;

  // no need for opposite -- by default, opposite pairs are stored at contiguous even/odd indices
  // for each vertex, store an incoming half edge 
  int* vertexHE;
  // faces
  int* faceHE;
  // vertex coordinates
  double *vX, *vY, *vZ;

  //counters
  int* elementSize;

  // buffers containing indices
  // indexing is done so that the map element <-> index is a permutation which only contains cycles of order 1 and 2
  // this way, the permutation is its own inverse (involution) and can be used to translate element to index and vice versa
  // if there are V vertices and the capacity is C, i.e., there are H "holes", the following rule is maintained:
  // - Every vertex in position 1...V and every hole in position V+1...H is in a cycle of order 1 (i.e., its index is equal to its id)
  // - Every vertex in position V+1...H is coupled with a hole in position 0...V, so that they are part of a cycle of order 2
  int* vIndex;
  int* eIndex;
  int* fIndex;

  // garbage collection system
  //
  // position of the first free elements
  int* firstFreeElement;
  // capacity for element
  int* elementCapacity;
  // number of removed elements
  int* removedElement;

  const static int VERTEX_IDX = 0;
  const static int EDGE_IDX = 1;
  const static int FACE_IDX = 2;

  // When an element is removed, its halfedge pointer (or next pointer in the case of an halfedge)
  // is pointed to -(position of next free slot)-4. This way:
  // - if the value is positive, the element is valid todo update me)
  // - if the value is NULL_INDEX, the element pointer has not been initialized (like after a call to addVertex())
  // - otherwise if the value is another negative number, the element has been removed. In this case:
  //   - if the value is INVALID_INDEX, this is the last free element available
  //   - if the value is -n, n>1, then the next free element is at n-4

  // Increases the storage capacity for faces and returns the new capacity
  virtual void increaseFaceCapacity() {};

  // Increases the storage capacity for vertices and returns the new capacity
  virtual void increaseVertexCapacity() {};

  // Increases the storage capacity for edges and halfedges and returns the new capacity
  virtual void increaseEdgeCapacity() {};
public:
  // Increase the vertex, edge, and face capacities to the specified values
  virtual void reserve(int,int,int) {};
private:
 
  // Restore the indexing of elements (without holes)
  // Here are the rules:
  // 1- Elements are indexed 0...n-1, holes are indexed n,...,C (capacity);
  // 2- An element or hole whose descriptor can be used as its index is in a 1-cycle;
  // 3- Elements and holes whose descriptors cannot be used as index are paired in 2-cycles.
  // Every time we add or remove, two elements (or holes) change their cycle type:
  // 1- The added or remved object, which changes from being a hole to an element (or vice versa);
  // 2- The object that was at a position "n" when adding or position "n-1" when removing.
  //    This object does not change its nature (hole or element) but the status of its index changes (from usable to not usable and vice versa).
  // Whatever the reason, these two objects need to change the type of cycle in which they are (from 1-cycle to 2-cycle and vice versa).
  // If any of these objects was in a 2-cycle, the other object must be unaffected, so we might need to restore a 2-cycle.
  void restoreIndexing(int o1, int o2, int* elementIndex) {
    // Special case 1: if the object that changes nature also changes the status of its index, nothing to do.
    if (o1 == o2) {
       return;
    }
    int permO1 = elementIndex[o1];
    // Special case 2: if the elements were connected together, just put them in 1-cycles
    if (permO1 == o2) {
       elementIndex[o1] = o1;
       elementIndex[o2] = o2;
       return;
    }
    int permO2 = elementIndex[o2];
    int freeO1;
    int freeO2;
    // if the first element was in a 1-cycle, then it was in the correct side of the array.
    // The modified element will thus be in the wrong side of the array, and will need to be in a 2-cycle
    if (o1 == permO1) {
       freeO1 = o1;
    // else, it needs to be self-connected, and the currently connected element becomes free 
    } else {
       elementIndex[o1] = o1;
       freeO1 = permO1;
    }
    // same thing for the element that goes above/below the limit
    if (o2 == permO2) {
       freeO2 = o2;
    } else {
       elementIndex[o2] = o2;
       freeO2 = permO2;
    }
    // connect the free elements
    elementIndex[freeO1] = freeO2;
    elementIndex[freeO2] = freeO1;
  }

public:

   const static int INVALID_INDEX = -2;
   const static int NULL_INDEX = -1;

   // helper classes to wrap int indices
   class Integer_wrapper{
      private: 
         int index;
      public: 
         // default init
         Integer_wrapper() : index(NULL_INDEX) {}
         // cast from int
         Integer_wrapper(int i) : index(i) {}
         // cast to int
         operator int() const {return index;}
         Integer_wrapper& operator++(){index++; return *this;}
         Integer_wrapper& operator--(){index--; return *this;}
         bool operator==(const Integer_wrapper& rhs) const { return index == rhs.index;}
         bool operator!=(const Integer_wrapper& rhs) const { return index != rhs.index;}
         bool operator<(const Integer_wrapper& rhs) const { return index < rhs.index;}
         bool operator>(const Integer_wrapper& rhs) const { return index > rhs.index;}
         bool operator<=(const Integer_wrapper& rhs) const { return index <= rhs.index;}
         bool operator>=(const Integer_wrapper& rhs) const { return index >= rhs.index;}
   };
   
   class Vertex_descriptor : public Integer_wrapper {
      public:
         Vertex_descriptor(int i) : Integer_wrapper(i) {}
         Vertex_descriptor() : Integer_wrapper() {}
   };

   class Halfedge_descriptor : public Integer_wrapper {
      public:
         Halfedge_descriptor(int i) : Integer_wrapper(i) {}
         Halfedge_descriptor() : Integer_wrapper() {}
   };

   class Face_descriptor : public Integer_wrapper {
      public:
         Face_descriptor(int i) : Integer_wrapper(i) {}
         Face_descriptor() : Integer_wrapper() {}
   };

   // helper classes to wrap int indices
   class Edge_descriptor{
      private: 
         int index;
      public: 
         // default init
         Edge_descriptor() : index(INVALID_INDEX) {}
         // construct with halfedge (oriented)
         Edge_descriptor(Halfedge_descriptor h) : index(h) {}
         // cast from int
         Edge_descriptor(int i) : index(2*i) {}
         // cast to int
         operator int() const {return index/2;}
         // cast to Halfedge_descriptor
         Halfedge_descriptor halfedge_descriptor(){return Halfedge_descriptor(index);}
         Edge_descriptor& operator++(){index = 2*(index/2 + 1); return *this;}
         Edge_descriptor& operator--(){index = 2*(index/2 - 1); return *this;}
         bool operator==(const Edge_descriptor& rhs) const { return index/2 == rhs.index/2;}
         bool operator!=(const Edge_descriptor& rhs) const { return index/2 != rhs.index/2;}
         bool operator<(const Edge_descriptor& rhs) const { return index/2 < rhs.index/2;}
         bool operator>(const Edge_descriptor& rhs) const { return index/2 > rhs.index/2;}
         bool operator<=(const Edge_descriptor& rhs) const { return index/2 <= rhs.index/2;}
         bool operator>=(const Edge_descriptor& rhs) const { return index/2 >= rhs.index/2;}
   };

   template<typename I>
   class Indexed_element_iterator : public boost::iterator_facade< 
      Indexed_element_iterator<I>, I, std::bidirectional_iterator_tag, I > {
      typedef boost::iterator_facade< Indexed_element_iterator<I>, I, std::bidirectional_iterator_tag, I > Facade;

    public: 
        Indexed_element_iterator() : mesh(NULL), i() {}
        Indexed_element_iterator(const PolygonMesh* m, const int index)
          : mesh(m), i(index) {}
    private:
        friend class boost::iterator_core_access;
        void increment() {
            ++i;
            CGAL_assertion(mesh != NULL);
        }
  
        void decrement() {
            --i;
            CGAL_assertion(mesh != NULL);
        }

        bool equal(const Indexed_element_iterator& other) const {
            return this->i == other.i;
        }

        I dereference() const {
            return mesh->elementAt<I>(i);
        }

        const PolygonMesh* mesh;
        int i;

    };
   //
   typedef Indexed_element_iterator<Vertex_descriptor> Vertex_iterator;
   typedef Indexed_element_iterator<Edge_descriptor> Edge_iterator;
   typedef Indexed_element_iterator<Halfedge_descriptor> Halfedge_iterator;
   typedef Indexed_element_iterator<Face_descriptor> Face_iterator;
   //
   typedef CGAL::Iterator_range<Vertex_iterator> Vertex_range;
   typedef CGAL::Iterator_range<Edge_iterator> Edge_range;
   typedef CGAL::Iterator_range<Halfedge_iterator> Halfedge_range;
   typedef CGAL::Iterator_range<Face_iterator> Face_range;

  // Returns the number of vertices 
  int numberOfVertices() const {
   return elementSize[VERTEX_IDX];
  }

  // Returns the number of edges
  int numberOfEdges() const {
   return elementSize[EDGE_IDX];
  }

  // Returns the number of halfedges
  int numberOfHalfedges() const {
   return 2*numberOfEdges();
  }
  
  // Returns the number of faces
  int numberOfFaces() const {
   return elementSize[FACE_IDX];
  }

  // Returns the capacity of the vertex container
  int vertexCapacity() const {
    return elementCapacity[VERTEX_IDX];
  }

  // Returns the capacity of the edge container
  int edgeCapacity() const {
    return elementCapacity[EDGE_IDX];
  }
  
  // Returns the capacity of the halfedge container
  int halfedgeCapacity() const {
    return 2*edgeCapacity();
  }

  // Returns the capacity of the face container
  int faceCapacity() const {
    return elementCapacity[FACE_IDX];
  }

  // Sets the capacity of the vertex container
  void setVertexCapacity(int n) {
    elementCapacity[VERTEX_IDX] =  n;
  }

  // Sets the capacity of the edge container
  void setEdgeCapacity(int n) {
    elementCapacity[EDGE_IDX] =  n;
  }

  // Sets the capacity of the face container
  void setFaceCapacity(int n) {
    elementCapacity[FACE_IDX] =  n;
  }

  // Returns the first free (removed) vertex
  int firstFreeVertex() const {
    return firstFreeElement[VERTEX_IDX];
  }

  // Returns the first free (removed) edge
  int firstFreeEdge() const {
    return firstFreeElement[EDGE_IDX];
  }

  // Returns the first free (removed) face
  int firstFreeFace() const {
    return firstFreeElement[FACE_IDX];
  }

  // Sets the first free (removed) vertex
  void setFirstFreeVertex(int n) {
    firstFreeElement[VERTEX_IDX] =  n;
  }

  // Sets the first free (removed) edge
  void setFirstFreeEdge(int n) {
    firstFreeElement[EDGE_IDX] =  n;
  }

  // Sets the first free (removed) face
  void setFirstFreeFace(int n) {
    firstFreeElement[FACE_IDX] =  n;
  }

  // Sets the number of vertices
  void setNumberOfVertices(int n) {
    elementSize[VERTEX_IDX] =  n;
  }

  // Sets the number of edges
  void setNumberOfEdges(int n) {
    elementSize[EDGE_IDX] =  n;
  }

  // Sets the number of faces
  void setNumberOfFaces(int n) {
    elementSize[FACE_IDX] =  n;
  }


  // Returns the number of removed vertices
  int numberOfRemovedVertices() const {
    return removedElement[VERTEX_IDX];
  }

  // Returns the number of removed edges
  int numberOfRemovedEdges() const {
    return removedElement[EDGE_IDX];
  }

  // Returns the number of removed faces
  int numberOfRemovedFaces() const {
    return removedElement[FACE_IDX];
  }

  // Sets the number of removed vertices
  void setNumberOfRemovedVertices(int n) {
    removedElement[VERTEX_IDX] = n;
  }

  // Sets the number of removed edges
  void setNumberOfRemovedEdges(int n) {
    removedElement[EDGE_IDX] = n;
  }

  // Sets the number of removed faces
  void setNumberOfRemovedFaces(int n) {
    removedElement[FACE_IDX] = n;
  }
  // Checks whether a given vertex has been removed 
  bool isVertexRemoved(int v) const {
    return vertexHE[v] < NULL_INDEX;
  }

  // Returns an upper bound on vertex descriptors
  int boundOnVertexDescriptor() const {
    return numberOfVertices() + numberOfRemovedVertices();
  }

  // Returns an upper bound on edge descriptors
  int boundOnEdgeDescriptor() const {
    return numberOfEdges() + numberOfRemovedEdges();
  }

  // Returns an upper bound on halfedge descriptors
  int boundOnHalfedgeDescriptor() const {
    return 2 * boundOnEdgeDescriptor();
  }

  // Returns an upper bound on face descriptors
  int boundOnFaceDescriptor() const {
    return numberOfFaces() + numberOfRemovedFaces();
  }

  bool isRemoved(Vertex_descriptor v) const { 
   return isVertexRemoved(v);
  }

  // Checks whether a given edge has been removed 
  bool isEdgeRemoved(int e) const {
    // the negative value is stored in the even-indexed halfedge assiciated to the edge
    return nextHE[2*e] < NULL_INDEX;
  }             
  
  bool isRemoved(Edge_descriptor e) const {
   return isEdgeRemoved(e);
  }

  // Checks whether a given halfedge has been removed 
  bool isHalfedgeRemoved(int h) const {
    // the negative value is only stored in the even halfedge
    return nextHE[h - (h % 2)] < NULL_INDEX;
  }
  
  bool isRemoved(Halfedge_descriptor h) const { 
   return isHalfedgeRemoved(h);
  }

  // Checks whether a given face has been removed 
  bool isFaceRemoved(int f) const {
    return faceHE[f] < NULL_INDEX;
  }

  bool isRemoved(Face_descriptor f) const { 
    return isFaceRemoved(f);
  }

  // Checks whether the given vertex has a descriptor within bounds
  bool hasValidVertexDescriptor(int v) const {
    return v >=0 && v < boundOnVertexDescriptor();
  }

  bool hasValidDescriptor(Vertex_descriptor v) const { 
    return hasValidVertexDescriptor(v);
  }

  // Checks whether the given edge has a descriptor within bounds
  bool hasValidEdgeDescriptor(int e) const {
    return e >= 0 && e < boundOnEdgeDescriptor();
  }

  bool hasValidDescriptor(Edge_descriptor e) const { 
    return hasValidEdgeDescriptor(e);
  }

  // Checks whether the given vertex has an index within bounds
  bool hasValidHalfedgeDescriptor(int h) const {
    return h >= 0 && h < boundOnHalfedgeDescriptor();
  }

  bool hasValidDescriptor(Halfedge_descriptor h) const { 
    return hasValidHalfedgeDescriptor(h);
  }

  // Checks whether the given vertex has an index within bounds
  bool hasValidFaceDescriptor(int f) const {
   return f >= 0 && f < boundOnFaceDescriptor();
  }
  bool hasValidDescriptor(Face_descriptor f) const{ 
   return hasValidFaceDescriptor(f);
  }

  // Checks whether the given vertex descriptor is valid
  bool isValidVertex(int v) const {
   return hasValidVertexDescriptor(v) && !isVertexRemoved(v);
  }

  // Checks whether the given edge descriptor is valid
  bool isValidEdge(int e) const {
   return hasValidEdgeDescriptor(e) && !isEdgeRemoved(e);
  }

  // Checks whether the given halfedge descriptor is valid
  bool isValidHalfedge(int h) const {
   return hasValidHalfedgeDescriptor(h) && !isHalfedgeRemoved(h);
  }

  // Checks whether the given face descriptor is valid
  bool isValidFace(int f) const {
   return hasValidFaceDescriptor(f) && !isFaceRemoved(f);
  }
  
  // Returns the next halfedge around its face
  int next(int h) const {
    return nextHE[h];
  }

  // Returns the previous halfedge around its face
  int prev(int h) const {
    return prevHE[h];
  }

  // Returns the halfedge with source and target swapped
  int opposite(int h) const {
    // halfedges are stored as couples of opposite HEs -> for eve HEs add 1, for odd HEs remove 1 
    // return h + 1 - 2 * (h % 2);
    // just flip the LSB
    return h + 1 - 2*(h % 2);
  }

  // Sets the successor of h1 around a face to h2, and the predecessor of h2 to h1
  void setNext(int h1, int h2){
    nextHE[h1] = h2;
    prevHE[h2] = h1;
  }

  // Sets the target vertex of h and the source of opposite(h) to v
  void setTarget(int h, int v){
    heVertex[h] = v;   
  }

  // Sets the halfedge of v to h. The target vertex of h must be v
  void setVertexHalfedge(int v, int h){
    vertexHE[v] = h;
  }

  // Adds a new vertex to the graph wothout initializing the connectivity
  int addVertex(){
    int nVertices = numberOfVertices();
    int newVertexDescriptor = firstFreeVertex();

    if (newVertexDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseVertexCapacity();
      newVertexDescriptor = firstFreeVertex();
    }
    // free space available: use it for the new element
    setFirstFreeVertex(-vertexHE[newVertexDescriptor] - 4);
    vertexHE[newVertexDescriptor] = NULL_INDEX;
    // set pointer to next free element (or -1 if this was the last one)
    setNumberOfVertices(++nVertices);
    int removedV = numberOfRemovedVertices();
    if (removedV > 0) setNumberOfRemovedVertices(--removedV);
    restoreIndexing(newVertexDescriptor, nVertices - 1, vIndex);
    return newVertexDescriptor;
  }
 
  // Removes v from the graph
  void removeVertex(int v) {
    int firstFreeV = firstFreeVertex();
    vertexHE[v] = -firstFreeV - 4;
    setFirstFreeVertex(v);
    int nVertices = numberOfVertices();
    setNumberOfVertices(--nVertices);
    int removedV = numberOfRemovedVertices();
    setNumberOfRemovedVertices(++removedV);
    restoreIndexing(v, nVertices, vIndex);
  }

  // Adds two opposite halfedges to the graph without initializing the connectivity
  int addEdge() {
    int nEdges = numberOfEdges();
    int newEdgeDescriptor = firstFreeEdge();
    if (newEdgeDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseEdgeCapacity();
      newEdgeDescriptor = firstFreeEdge();
   }
   // free space available: use it for the new element
   setFirstFreeEdge(-nextHE[2*newEdgeDescriptor] - 4);
   // initialize pointers to NULL_INDEX
   int he = 2 * newEdgeDescriptor;
   int ohe = he + 1;
   nextHE[he] = NULL_INDEX;
   nextHE[ohe] = NULL_INDEX;
   prevHE[he] = NULL_INDEX;
   prevHE[ohe] = NULL_INDEX;
   heVertex[he] = NULL_INDEX;
   heVertex[ohe] = NULL_INDEX;
   heFace[he] = NULL_INDEX;
   heFace[ohe] = NULL_INDEX;
   // set pointer to next free element (or -1 if this was the last one)
   setNumberOfEdges(++nEdges);
   int removedE = numberOfRemovedEdges();
   if (removedE > 0) setNumberOfRemovedEdges(--removedE);
   restoreIndexing(newEdgeDescriptor, nEdges - 1, eIndex);
   return newEdgeDescriptor;
  }

  // Removes the two halfedges corresponding to e from the graph
  void removeEdge(int e){
    int firstFreeE = firstFreeEdge();
    int he = 2*e;
    nextHE[he] = -firstFreeE - 4;
    setFirstFreeEdge(e);
    int nEdges = numberOfEdges();
    setNumberOfEdges(--nEdges);
    int removedE = numberOfRemovedEdges();
    setNumberOfRemovedEdges(++removedE);
    restoreIndexing(e, nEdges, eIndex);
  }
  
  // Returns the face incident to halfedge h
  int face(int h) const {
    return heFace[h];
  }

  // Returns a halfedge incident to face f
  int faceHalfedge(int f) const {
    return faceHE[f];
  }

  // Sets the corresponding face of h to f
  void setFace(int h, int f){
    heFace[h] = f;
  }

  // Sets the corresponding halfedge of f to h
  void setFaceHalfedge(int f, int h){
   faceHE[f] = h;
  }

  // Adds a new face to the graph without initializing the connectivity
  int addFace(){
    int nFaces = numberOfFaces();
    int newFaceDescriptor = firstFreeFace();
    if (newFaceDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseFaceCapacity();
      newFaceDescriptor = firstFreeFace();
    }
    // free space available: use it for the new element
    setFirstFreeFace(-faceHE[newFaceDescriptor] - 4);
    faceHE[newFaceDescriptor] = NULL_INDEX;
    // set pointer to next free element (or -1 if this was the last one)
    setNumberOfFaces(++nFaces);
    int removedF = numberOfRemovedFaces();
    if (removedF > 0) setNumberOfRemovedFaces(--removedF);
    restoreIndexing(newFaceDescriptor, nFaces - 1, fIndex);
    return newFaceDescriptor;
  }

  // Removes f from the graph
  void removeFace(int f){
    int firstFreeF = firstFreeFace();
    faceHE[f] = -firstFreeF - 4;
    setFirstFreeFace(f);
    int nFaces = numberOfFaces();
    setNumberOfFaces(--nFaces);
    int removedF = numberOfRemovedFaces();
    setNumberOfRemovedFaces(++removedF);
    restoreIndexing(f, nFaces, fIndex);
  }

  // The target vertex of h
  int target(int h) const {
    return heVertex[h];
  }

  // The source vertex of h
  int source(int h) const {
    return heVertex[opposite(h)];
  }

  // A halfedge with target v
  int vertexHalfedge(int v) const {
    return vertexHE[v];
  }

  // The edge corresponding to h and opposite(h)
  int edge(int h) const {
    // opposite pairs are contiguous in the half edge list, so the edge index is just h/2
    return h / 2;
  }

  // One of the halfedges corresponding to e
  int edgeHalfedge(int e) const {
    // opposite pairs are contiguous in the half edge list, so the half indices are 2*e and 2*e+1. Just pick one
    return e * 2;
  }

  // Returns the half edge between two given vertices with the given orientation, or INVALID_INDEX if it doesn't exist
  int halfedge(int source, int target) const {
    int he = vertexHalfedge(target);
    int h = he;
    if(isValidHalfedge(h)){
      do {
        if (this->source(h) == source) return h;
        h = opposite(next(h));
      }
      while (h != he);
    }
    return INVALID_INDEX;
  }

  // Returns the degree of a face, that is, the number of incident half edges (or edges)
  int faceDegree(int f) const {
    int he = faceHalfedge(f);
    int h = he;
    int c = 0;
    do {
      c++;
      h = next(h);
    }
    while (h != he);
    return c;
  }

  // Returns the degree of a vertex, that is, the number of incident edges (or half edges that have this vertex as a source, or equivalently as a target)
  int vertexDegree(int v) const {
    int he = vertexHalfedge(v);
    int h = he;
    int c = 0;
    do {
      c++;
      h = opposite(next(h));
    }
    while (h != he);
    return c;
  }

  // Returns the x coordinate of a vertex
  double vertexX(int v) const {
    return vX[v];
  }

  // Returns the y coordinate of a vertex
  double vertexY(int v) const {
    return vY[v];
  }

  // Returns the z coordinate of a vertex
  double vertexZ(int v) const {
    return vZ[v];
  }
  
  // Sets the x coordinate of a vertex
  void setVertexX(int v, double d) {
    vX[v] = d;
  }

  // Sets the y coordinate of a vertex
  void setVertexY(int v, double d) {
    vY[v] = d;
  }

  // Sets the z coordinate of a vertex
  void setVertexZ(int v, double d) {
    vZ[v] = d;
  }

  /**
   * Returns the index associated to a given vertex, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the vertex is not valid.
   */
  int vertexIndex(int v) const {
    if(!isValidVertex(v)) return INVALID_INDEX;
    return vIndex[v];
  }
  
  // Returns the vertex associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfVertices()}.
  int vertexAt(int i) const {
    if(i < 0 || i >= numberOfVertices()) return INVALID_INDEX;
    return vIndex[i];
  }
  
  // Returns the index associated to a given edge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the edge is not valid.
  int edgeIndex(int e) const {
    if(!isValidEdge(e)) return INVALID_INDEX;
    return eIndex[e];
  }
  
  // Returns the edge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfEdges()}.
  int edgeAt(int i) const {
    if(i < 0 || i >= numberOfEdges()) return INVALID_INDEX;
    return eIndex[i];
  }
  
  // Returns the index associated to a given halfedge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the halfedge is not valid.
  int halfedgeIndex(int h) const {
    if(!isValidHalfedge(h)) return INVALID_INDEX;
    int e = h / 2;
    int r = h % 2;
    return 2 * eIndex[e] + r;
  }
  
  // Returns the halfedge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfHalfedges()}.
  int halfedgeAt(int i) const {
    if(i < 0 || i >= numberOfHalfedges()) return INVALID_INDEX;
    int ei = i / 2;
    int ri = i % 2;
    return 2 * eIndex[ei] + ri;
  }
  
  // Returns the index associated to a given face, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the face is not a valid face.
  int faceIndex(int f) const {
    if(!isValidFace(f)) return INVALID_INDEX;
    return fIndex[f];
  }
  
  // Returns the face associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfFaces()}.
  int faceAt(int i) const {
    if(i < 0 || i >= numberOfFaces()) return INVALID_INDEX;
    return fIndex[i];
  }

  template<typename I>
  I elementAt(int i) const;

  int index(Vertex_descriptor v) const {
    return vertexIndex(v);
  }

  int index(Edge_descriptor e) const {
    return edgeIndex(e);
  }

  int index(Halfedge_descriptor h) const {
    return halfedgeIndex(h);
  }

  int index(Face_descriptor f) const {
    return faceIndex(f);
  }

  // An iterator range over all vertices
  Vertex_range vertices() const {
   return CGAL::make_range(Vertex_iterator(this, 0), Vertex_iterator(this, numberOfVertices()));
  }

  // An iterator range over all edges
  Edge_range edges() const {
   return CGAL::make_range(Edge_iterator(this, 0), Edge_iterator(this, numberOfEdges()));
  }

  // An iterator range over all halfedges
  Halfedge_range halfedges() const {
   return CGAL::make_range(Halfedge_iterator(this, 0), Halfedge_iterator(this, numberOfHalfedges()));
  }

  // An iterator range over all faces
  Face_range faces() const {
   return CGAL::make_range(Face_iterator(this, 0), Face_iterator(this, numberOfFaces()));
  }

};

std::size_t hash_value(const PolygonMesh::Integer_wrapper&  i)
{
  CGAL_assume((int) i>=0);
  std::size_t ret = i;
  return ret;
}

std::size_t hash_value(const PolygonMesh::Edge_descriptor&  i)
{
  CGAL_assume((int) i>=0);
  std::size_t ret = i;
  return ret;
}
  template<>
  PolygonMesh::Vertex_descriptor PolygonMesh::elementAt<PolygonMesh::Vertex_descriptor>(int i) const {
    return vertexAt(i);
  }

  template<>
  PolygonMesh::Edge_descriptor PolygonMesh::elementAt<PolygonMesh::Edge_descriptor>(int i) const {
    return edgeAt(i);
  }

  template<>
  PolygonMesh::Halfedge_descriptor PolygonMesh::elementAt<PolygonMesh::Halfedge_descriptor>(int i) const {
    return halfedgeAt(i);
  }

  template<>
  PolygonMesh::Face_descriptor PolygonMesh::elementAt<PolygonMesh::Face_descriptor>(int i) const {
    return faceAt(i);
  }

#endif
