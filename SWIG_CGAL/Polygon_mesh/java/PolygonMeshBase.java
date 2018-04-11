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

import java.nio.DoubleBuffer;
import java.nio.IntBuffer;
import java.util.HashSet;
import java.util.Set;

import CGAL.Polygon_mesh.PolygonMeshRange.AllEdgesDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.AllFacesDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.AllHalfedgesDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.AllVerticesDescriptorRange;

/**
 * Base class containing base buffers, C++ access functions and basic operations for a {@link PolygonMesh}
 */
public class PolygonMeshBase extends PolygonMeshAccess implements IPolygonMeshBase {

  protected static final int INVALID_INDEX = -2;
  protected static final int NULL_INDEX = -1;

  // default initial capacity if none is specified
  protected static final int DEFAULT_CAPACITY = 10;

  private Set<IPolygonMeshProperty> vertexProperties;
  private Set<IPolygonMeshProperty> edgeProperties;
  private Set<IPolygonMeshProperty> halfedgeProperties;
  private Set<IPolygonMeshProperty> faceProperties;

  /**
   * Creates an empty {@link PolygonMeshBase}, with a given initial capacity for vertices, edges and faces.
   */
  public PolygonMeshBase(int estimatedNVertices, int estimatedNEdges, int estimatedNFaces) {
    vertexProperties = new HashSet<>();
    edgeProperties = new HashSet<>();
    halfedgeProperties = new HashSet<>();
    faceProperties = new HashSet<>();
    this.elementCapacity = PolygonMeshUtils.allocateNewIntBuffer(ElementIndex.values().length);
    this.removedElement = PolygonMeshUtils.allocateNewIntBuffer(ElementIndex.values().length);
    this.elementSize = PolygonMeshUtils.allocateNewIntBuffer(ElementIndex.values().length);
    this.firstFreeElement = PolygonMeshUtils.allocateNewIntBuffer(ElementIndex.values().length);
    this.firstFreeElement.put(0, INVALID_INDEX);
    this.firstFreeElement.put(1, INVALID_INDEX);
    this.firstFreeElement.put(2, INVALID_INDEX);
    int vCap = Math.max(estimatedNVertices, 1);
    int eCap = Math.max(estimatedNEdges, 1);
    int fCap = Math.max(estimatedNFaces, 1);
    increaseVertexCapacity(vCap);
    increaseEdgeCapacity(eCap);
    increaseFaceCapacity(fCap);
  }
  
  /**
   * Creates an empty {@link PolygonMeshBase}, with a default initial capacity of ten.
   */
  public PolygonMeshBase() {
    this(DEFAULT_CAPACITY);
  }

  /**
   * Copy constructor. Only copies references to buffers and properties, used by derived classes to be built on top of other {@link PolygonMeshBase}.
   */
  protected PolygonMeshBase(PolygonMeshBase other) {
    super(other);
    this.vertexProperties = other.vertexProperties;
    this.edgeProperties = other.edgeProperties;
    this.halfedgeProperties = other.halfedgeProperties;
    this.faceProperties = other.faceProperties;
  }

  /**
   * Increases the vertex, edge, and face capacities
   */
  public void reserve(int nv, int ne, int nf) {
    increaseVertexCapacity(nv);
    increaseEdgeCapacity(ne);
    increaseFaceCapacity(nf);
  }

  /**
   * Returns a copy of the mesh.
   */
  @Override
  public PolygonMeshBase copy() {
    PolygonMeshBase copy = new PolygonMeshBase();
    PolygonMeshAccess.copy(this, copy); 
    for(IPolygonMeshProperty vP : vertexProperties) {
       copy.vertexProperties.add(vP.copy());
    }
    for(IPolygonMeshProperty eP : edgeProperties) {
       copy.edgeProperties.add(eP.copy());
    }
    for(IPolygonMeshProperty hP : halfedgeProperties) {
       copy.halfedgeProperties.add(hP.copy());
    }
    for(IPolygonMeshProperty fP : faceProperties) {
       copy.faceProperties.add(fP.copy());
    }
    return copy;
  }

  /**
   * Creates an empty {@link PolygonMeshBase}, with a given initial capacity.
   */
  public PolygonMeshBase(int estimatedNElements) {
    this(estimatedNElements, estimatedNElements, estimatedNElements);
  }

  /**
   * Creates an empty {@link PolygonMeshBase}, with a given initial capacity for vertices and faces.
   */
  public PolygonMeshBase(int estimatedNVertices, int estimatedNFaces) {
    // assume genus 0  =>  E = V + F - 2
    this(estimatedNVertices, estimatedNVertices + estimatedNFaces - 2, estimatedNFaces);
  }

  /**
   * Increases the storage capacity for vertices and returns the new capacity
   */
  protected void increaseVertexCapacity() {
    increaseVertexCapacity(PolygonMeshUtils.nextCapacity(vertexCapacity()));
  }

  protected void increaseVertexCapacity(int newCapacity) {
    int oldCapacity = vertexCapacity();
    if (oldCapacity >= newCapacity) return;
    IntBuffer newVertexHE = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, vertexHE);
    DoubleBuffer newVertexX = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, vertexX);
    DoubleBuffer newVertexY = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, vertexY);
    DoubleBuffer newVertexZ = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, vertexZ);
    vertexHE = newVertexHE;
    vertexX = newVertexX;
    vertexY = newVertexY;
    vertexZ = newVertexZ;
    // initialize the nextFreeElement
    for (int i = oldCapacity; i < newCapacity - 1; i++) {
      int nextFree = i + 1;
      vertexHE.put(i, -nextFree - 4);
    }
    vertexHE.put(newCapacity - 1, INVALID_INDEX);
    // update capacity
    setVertexCapacity(newCapacity);
    // find the last free vertex and link to the newly created free slots
    int lastFreeVertex = firstFreeVertex();
    // if there aren't any free slots left, set the first created one as the next available
    if (lastFreeVertex == INVALID_INDEX) {
      setFirstFreeVertex(oldCapacity);
    }
    // else, look for the last slot and link it to the first created one
    else {
      while (lastFreeVertex != INVALID_INDEX) {
        int nextFree = -vertexHE.get(lastFreeVertex) - 4;
        if (nextFree == INVALID_INDEX) {
          vertexHE.put(lastFreeVertex, -oldCapacity - 4); 
        }
        lastFreeVertex = nextFree;
      }
    }
    // resize properties
    for (IPolygonMeshProperty vertexProperty : vertexProperties) {
      vertexProperty.resize(newCapacity);
    }
    // update index array
    IntBuffer newVertexIndex = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, vertexIndex);
    vertexIndex = newVertexIndex;
    // initialize the vertex index
    for (int i = oldCapacity; i < newCapacity; i++) {
      vertexIndex.put(i, i);
     }
  }

  /**
   * Increases the storage capacity for edges and halfedges and returns the new capacity
   */
  protected void increaseEdgeCapacity() {
    increaseEdgeCapacity(PolygonMeshUtils.nextCapacity(edgeCapacity()));
  }

  protected void increaseEdgeCapacity(int newCapacity) {
    int oldCapacity = edgeCapacity();
    if (oldCapacity >= newCapacity) return;
    IntBuffer newNextHE = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, nextHE);
    IntBuffer newPrevHE = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, prevHE);
    IntBuffer newHeVertex = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, heVertex);
    IntBuffer newHeFace = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, heFace);
    nextHE = newNextHE;
    prevHE = newPrevHE;
    heVertex = newHeVertex;
    heFace = newHeFace;
    // initialize the nextFreeElement
    for (int i = oldCapacity; i < newCapacity - 1; i++) {
      int nextFree = i + 1;
      nextHE.put(edgeHalfedge(i), -nextFree - 4);
    }
    nextHE.put(edgeHalfedge(newCapacity - 1), INVALID_INDEX);
    // update capacity
    setEdgeCapacity(newCapacity);
    // find the last free edge and link to the newly created free slots
    int lastFreeEdge = firstFreeEdge();
    // if there aren't any free slots left, set the first created one as the next available
    if (lastFreeEdge == INVALID_INDEX) {
      setFirstFreeEdge(oldCapacity);
    }
    // else, look for the last slot and link it to the first created one
    else {
      while (lastFreeEdge != INVALID_INDEX) {
        int nextFree = -nextHE.get(edgeHalfedge(lastFreeEdge)) - 4;
        if (nextFree == INVALID_INDEX) {
          nextHE.put(edgeHalfedge(lastFreeEdge), -oldCapacity - 4); 
        }
        lastFreeEdge = nextFree;
      }
    }
    // resize properties
    for (IPolygonMeshProperty edgeProperty : edgeProperties) {
      edgeProperty.resize(newCapacity);
    }
    for (IPolygonMeshProperty halfedgeProperty : halfedgeProperties) {
      halfedgeProperty.resize(2 * newCapacity);
    }
    // update index array
    IntBuffer newEdgeIndex = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, edgeIndex);
    edgeIndex = newEdgeIndex;
    // initialize the nextFreeElement
    for (int i = oldCapacity; i < newCapacity; i++) {
      edgeIndex.put(i, i);
     }
  }

  /**
   * Increases the storage capacity for faces and returns the new capacity
   */
  protected void increaseFaceCapacity() {
    increaseFaceCapacity(PolygonMeshUtils.nextCapacity(faceCapacity()));
  }

  protected void increaseFaceCapacity(int newCapacity) {
    int oldCapacity = faceCapacity();
    if (oldCapacity >= newCapacity) return;
    IntBuffer newFaceHE = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, faceHE);
    faceHE = newFaceHE;
    // initialize the nextFreeElement
    for (int i = oldCapacity; i < newCapacity - 1; i++) {
      int nextFree = i + 1;
      faceHE.put(i, -nextFree - 4);
    }
    faceHE.put(newCapacity - 1, INVALID_INDEX);
    // update capacity
    setFaceCapacity(newCapacity);
    // find the last free face and link to the newly created free slots
    int lastFreeFace = firstFreeFace();
    // if there aren't any free slots left, set the first created one as the next available
    if (lastFreeFace == INVALID_INDEX) {
      setFirstFreeFace(oldCapacity);
    }
    // else, look for the last slot and link it to the first created one
    else {
      while (lastFreeFace != INVALID_INDEX) {
        int nextFree = -faceHE.get(lastFreeFace) - 4;
        if (nextFree == INVALID_INDEX) {
          faceHE.put(lastFreeFace, -oldCapacity - 4); 
        }
        lastFreeFace = nextFree;
      }
    }
    // resize properties
    for (IPolygonMeshProperty faceProperty : faceProperties) {
      faceProperty.resize(newCapacity);
    }
    // update index array
    IntBuffer newFaceIndex = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, faceIndex);
    faceIndex = newFaceIndex;
    // initialize the nextFreeElement
    for (int i = oldCapacity; i < newCapacity; i++) {
      faceIndex.put(i, i);
     }
  }

 
  /**
   * Restore the indexing of elements (without holes)
   * Here are the rules:
   * 1- Elements are indexed 0...n-1, holes are indexed n,...,C (capacity);
   * 2- An element or hole whose descriptor can be used as its index is in a 1-cycle;
   * 3- Elements and holes whose descriptors cannot be used as index are paired in 2-cycles.
   * Every time we add or remove, two elements (or holes) change their cycle type:
   * 1- The added or remved object, which changes from being a hole to an element (or vice versa);
   * 2- The object that was at a position "n" when adding or position "n-1" when removing.
   *    This object does not change its nature (hole or element) but the status of its index changes (from usable to not usable and vice versa).
   * Whatever the reason, these two objects need to change the type of cycle in which they are (from 1-cycle to 2-cycle and vice versa).
   * If any of these objects was in a 2-cycle, the other object must be unaffected, so we might need to restore a 2-cycle.
   */
  private void restoreIndexing(int o1, int o2, IntBuffer elementIndex) {
    // Special case 1: if the object that changes nature also changes the status of its index, nothing to do.
    if (o1 == o2) {
       return;
    }
    int permO1 = elementIndex.get(o1);
    // Special case 2: if the elements were connected together, just put them in 1-cycles
    if (permO1 == o2) {
       elementIndex.put(o1, o1);
       elementIndex.put(o2, o2);
       return;
    }
    int permO2 = elementIndex.get(o2);
    int freeO1;
    int freeO2;
    // if the first element was in a 1-cycle, then it was in the correct side of the array.
    // The modified element will thus be in the wrong side of the array, and will need to be in a 2-cycle
    if (o1 == permO1) {
       freeO1 = o1;
    // else, it needs to be self-connected, and the currently connected element becomes free 
    } else {
       elementIndex.put(o1, o1);
       freeO1 = permO1;
    }
    // same thing for the element that goes above/below the limit
    if (o2 == permO2) {
       freeO2 = o2;
    } else {
       elementIndex.put(o2, o2);
       freeO2 = permO2;
    }
    // connect the free elements
    elementIndex.put(freeO1, freeO2);
    elementIndex.put(freeO2, freeO1);
  }

  /**
   * Returns the capacity of the vertex container
   */
  protected int vertexCapacity() {
    return elementCapacity.get(ElementIndex.VERTEX.index());
  }

  /**
   * Returns the capacity of the edge container
   */
  protected int edgeCapacity() {
    return elementCapacity.get(ElementIndex.EDGE.index());
  }

  /**
   * Returns the capacity of the halfedge container
   */
  protected int halfedgeCapacity() {
    return 2 * edgeCapacity();
  }

  /**
   * Returns the capacity of the face container
   */
  protected int faceCapacity() {
    return elementCapacity.get(ElementIndex.FACE.index());
  }

  /**
   * Returns the capacity of the container of the given element type
   */
  protected int elementCapacity(ElementIndex type) {
    return elementCapacity.get(type.index());
  }

  /**
   * Sets the capacity of the vertex container
   */
  private void setVertexCapacity(int n) {
    elementCapacity.put(ElementIndex.VERTEX.index(), n);
  }

  /**
   * Sets the capacity of the edge container
   */
  private void setEdgeCapacity(int n) {
    elementCapacity.put(ElementIndex.EDGE.index(), n);
  }

  /**
   * Sets the capacity of the face container
   */
  private void setFaceCapacity(int n) {
    elementCapacity.put(ElementIndex.FACE.index(), n);
  }

  /**
   * Returns the first free (removed) vertex
   */
  protected int firstFreeVertex() {
    return firstFreeElement.get(ElementIndex.VERTEX.index());
  }

  /**
   * Returns the first free (removed) edge
   */
  protected int firstFreeEdge() {
    return firstFreeElement.get(ElementIndex.EDGE.index());
  }

  /**
   * Returns the first free (removed) face
   */
  protected int firstFreeFace() {
    return firstFreeElement.get(ElementIndex.FACE.index());
  }

  /**
   * Returns the first free element of the given type
   */
  protected int firstFreeElement(ElementIndex type) {
    return firstFreeElement.get(type.index());
  }

  /**
   * Sets the first free (removed) vertex
   */
  private void setFirstFreeVertex(int n) {
    firstFreeElement.put(ElementIndex.VERTEX.index(), n);
  }

  /**
   * Sets the first free (removed) edge
   */
  private void setFirstFreeEdge(int n) {
    firstFreeElement.put(ElementIndex.EDGE.index(), n);
  }

  /**
   * Sets the first free (removed) face
   */
  private void setFirstFreeFace(int n) {
    firstFreeElement.put(ElementIndex.FACE.index(), n);
  }

  /**
   * Sets the number of vertices
   */
  private void setNumberOfVertices(int n) {
    elementSize.put(ElementIndex.VERTEX.index(), n);
  }

  /**
   * Sets the number of edges
   */
  private void setNumberOfEdges(int n) {
    elementSize.put(ElementIndex.EDGE.index(), n);
  }

  /**
   * Sets the number of faces
   */
  private void setNumberOfFaces(int n) {
    elementSize.put(ElementIndex.FACE.index(), n);
  }

  /**
   * Returns the number of removed vertices
   */
  protected int numberOfRemovedVertices() {
    return removedElement.get(ElementIndex.VERTEX.index());
  }

  /**
   * Returns the number of removed edges
   */
  protected int numberOfRemovedEdges() {
    return removedElement.get(ElementIndex.EDGE.index());
  }

  /**
   * Returns the number of removed faces
   */
  protected int numberOfRemovedFaces() {
    return removedElement.get(ElementIndex.FACE.index());
  }

  /**
   * Sets the number of removed vertices
   */
  private void setNumberOfRemovedVertices(int n) {
    removedElement.put(ElementIndex.VERTEX.index(), n);
  }

  /**
   * Sets the number of removed edges
   */
  private void setNumberOfRemovedEdges(int n) {
    removedElement.put(ElementIndex.EDGE.index(), n);
  }

  /**
   * Sets the number of removed faces
   */
  private void setNumberOfRemovedFaces(int n) {
    removedElement.put(ElementIndex.FACE.index(), n);
  }

  @Override
  public int numberOfVertices() {
    return elementSize.get(ElementIndex.VERTEX.index());
  }

  @Override
  public int numberOfEdges() {
    return elementSize.get(ElementIndex.EDGE.index());
  }

  @Override
  public int numberOfHalfedges() {
    return 2 * numberOfEdges();
  }

  @Override
  public int numberOfFaces() {
    return elementSize.get(ElementIndex.FACE.index());
  }

  @Override
  public int boundOnVertexDescriptor() {
    return numberOfVertices() + numberOfRemovedVertices();
  }

  @Override
  public int boundOnEdgeDescriptor() {
    return numberOfEdges() + numberOfRemovedEdges();
  }

  @Override
  public int boundOnHalfedgeDescriptor() {
    return 2 * boundOnEdgeDescriptor();
  }

  @Override
  public int boundOnFaceDescriptor() {
    return numberOfFaces() + numberOfRemovedFaces();
  }

  /**
   * Checks whether a given vertex has been removed
   */
  protected boolean isVertexRemoved(int v) {
    return vertexHE.get(v) < NULL_INDEX;
  }

  /**
   * Checks whether a given edge has been removed
   */
  protected boolean isEdgeRemoved(int e) {
    // the negative value is stored in the even-indexed halfedge assiciated
    // to the edge
    return nextHE.get(2 * e) < NULL_INDEX;
  }

  /**
   * Checks whether a given halfedge has been removed
   */
  protected boolean isHalfedgeRemoved(int h) {
    // the negative value is only stored in the even halfedge
    return nextHE.get(h - (h % 2)) < NULL_INDEX;
  }

  /**
   * Checks whether a given face has been removed
   */
  protected boolean isFaceRemoved(int f) {
    return faceHE.get(f) < NULL_INDEX;
  }

  /**
   * Checks whether the given vertex has an index within bounds
   */
  public boolean hasValidVertexDescriptor(int v) {
    return v >= 0 && v < boundOnVertexDescriptor();
  }

  /**
   * Checks whether the given edge has an index within bounds
   */
  public boolean hasValidEdgeDescriptor(int e) {
    return e >= 0 && e < boundOnEdgeDescriptor();
  }

  /**
   * Checks whether the given halfedge has an index within bounds
   */
  public boolean hasValidHalfedgeDescriptor(int h) {
    return h >= 0 && h < boundOnHalfedgeDescriptor();
  }

  /**
   * Checks whether the given face has an index within bounds
   */
  public boolean hasValidFaceDescriptor(int f) {
    return f >= 0 && f < boundOnFaceDescriptor();
  }

  /**
   * Checks whether the given vertex descriptor is valid
   */
  @Override
  public boolean isValidVertex(int v) {
    return hasValidVertexDescriptor(v) && !isVertexRemoved(v);
  }

  /**
   * Checks whether the given edge descriptor is valid
   */
  @Override
  public boolean isValidEdge(int e) {
    return hasValidEdgeDescriptor(e) && !isEdgeRemoved(e);
  }

  /**
   * Checks whether the given halfedge descriptor is valid
   */
  @Override
  public boolean isValidHalfedge(int h) {
    return hasValidHalfedgeDescriptor(h) && !isHalfedgeRemoved(h);
  }

  /**
   * Checks whether the given face descriptor is valid
   */
  @Override
  public boolean isValidFace(int f) {
    return hasValidFaceDescriptor(f) && !isFaceRemoved(f);
  }

  /**
   * Returns the next halfedge around its face
   */
  @Override
  public int next(int h) {
    return nextHE.get(h);
  }

  /**
   * Returns the previous halfedge around its face
   */
  @Override
  public int prev(int h) {
    return prevHE.get(h);
  }

  /**
   * Returns the halfedge with source and target swapped
   */
  @Override
  public int opposite(int h) {
    // halfedges are stored as couples of opposite HEs -> for even HEs add
    // 1, for odd HEs remove 1
    // --> just flip the least significant bit
    // return h ^ 1;
    return h + 1 - 2 * (h % 2);
  }

  /**
   * Sets the successor of h1 around a face to h2, and the predecessor of h2 to h1
   */
  @Override
  public void setNext(int h1, int h2) {
    nextHE.put(h1, h2);
    prevHE.put(h2, h1);
  }

  /**
   * Sets the target vertex of h and the source of opposite(h) to v
   */
  @Override
  public void setTarget(int h, int v) {
    heVertex.put(h, v);
  }

  /**
   * Sets the halfedge of v to h. The target vertex of h must be v
   */
  @Override
  public void setVertexHalfedge(int v, int h) {
    vertexHE.put(v, h);
  }

  /**
   * Adds a new vertex to the graph wothout initializing the connectivity
   */
  @Override
  public int addVertex() {
    int nVertices = numberOfVertices();
    int newVertexDescriptor = firstFreeVertex();
    if (newVertexDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseVertexCapacity();
      newVertexDescriptor = firstFreeVertex();
    }
    // free space available: use it for the new element
    setFirstFreeVertex(-vertexHE.get(newVertexDescriptor) - 4);
    vertexHE.put(newVertexDescriptor, NULL_INDEX);
    // set pointer to next free element (or -1 if this was the last one)
    setNumberOfVertices(++nVertices);
    int removedV = numberOfRemovedVertices();
    if (removedV > 0) setNumberOfRemovedVertices(--removedV);
    restoreIndexing(newVertexDescriptor, nVertices - 1, vertexIndex);
    return newVertexDescriptor;
  }

  /**
   * Removes v from the graph
   */
  @Override
  public void removeVertex(int v) {
    int firstFreeVertex = firstFreeVertex();
    vertexHE.put(v, -firstFreeVertex - 4);
    setFirstFreeVertex(v);
    int nVertices = numberOfVertices();
    setNumberOfVertices(--nVertices);
    int removedV = numberOfRemovedVertices();
    setNumberOfRemovedVertices(++removedV);
    restoreIndexing(v, nVertices, vertexIndex);
  }

  /**
   * Adds two opposite halfedges to the graph without initializing the connectivity
   */
  @Override
  public int addEdge() {
    int nEdges = numberOfEdges();
    int newEdgeDescriptor = firstFreeEdge();
    if (newEdgeDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseEdgeCapacity();
      newEdgeDescriptor = firstFreeEdge();
    }
    // free space available: use it for the new element
    int he = edgeHalfedge(newEdgeDescriptor);
    setFirstFreeEdge(-nextHE.get(he) - 4);
    // initialize pointers to NULL_INDEX
    int ohe = opposite(he);
    nextHE.put(he, NULL_INDEX);
    nextHE.put(ohe, NULL_INDEX);
    prevHE.put(he, NULL_INDEX);
    prevHE.put(ohe, NULL_INDEX);
    heVertex.put(he, NULL_INDEX);
    heVertex.put(ohe, NULL_INDEX);
    heFace.put(he, NULL_INDEX);
    heFace.put(ohe, NULL_INDEX);
    // set pointer to next free element (or -1 if this was the last one)
    setNumberOfEdges(++nEdges);
    int removedE = numberOfRemovedEdges();
    if (removedE > 0) setNumberOfRemovedEdges(--removedE);
    restoreIndexing(newEdgeDescriptor, nEdges - 1, edgeIndex);
    return newEdgeDescriptor;
  }

  /**
   * Removes the two halfedges corresponding to e from the graph
   */
  @Override
  public void removeEdge(int e) {
    int firstFreeEdge = firstFreeEdge();
    int he = edgeHalfedge(e);
    nextHE.put(he, -firstFreeEdge - 4);
    setFirstFreeEdge(e);
    int nEdges = numberOfEdges();
    setNumberOfEdges(--nEdges);
    int removedE = numberOfRemovedEdges();
    setNumberOfRemovedEdges(++removedE);
    restoreIndexing(e, nEdges, edgeIndex);
  }

  /**
   * Returns the face incident to halfedge h
   */
  @Override
  public int face(int h) {
    return heFace.get(h);
  }

  /**
   * Returns a halfedge incident to face f
   */
  @Override
  public int faceHalfedge(int f) {
    return faceHE.get(f);
  }

  /**
   * Sets the corresponding face of h to f
   */
  @Override
  public void setFace(int h, int f) {
    heFace.put(h, f);
  }

  /**
   * Sets the corresponding halfedge of f to h
   */
  @Override
  public void setFaceHalfedge(int f, int h) {
    faceHE.put(f, h);
  }

  /**
   * Adds a new face to the graph without initializing the connectivity
   */
  @Override
  public int addFace() {
    int nFaces = numberOfFaces();
    int newFaceDescriptor = firstFreeFace();
    if (newFaceDescriptor == INVALID_INDEX) {
      // need to increase capacity
      increaseFaceCapacity();
      newFaceDescriptor = firstFreeFace();
    }
    // free space available: use it for the new element
    setFirstFreeFace(-faceHE.get(newFaceDescriptor) - 4);
    faceHE.put(newFaceDescriptor, NULL_INDEX);
    // set pointer to next free element (or -1 if this was the last one)
    setNumberOfFaces(++nFaces);
    int removedF = numberOfRemovedFaces();
    if (removedF > 0) setNumberOfRemovedFaces(--removedF);
    restoreIndexing(newFaceDescriptor, nFaces - 1, faceIndex);
    return newFaceDescriptor;
  }

  /**
   * Removes f from the graph
   */
  @Override
  public void removeFace(int f) {
    int firstFreeFace = firstFreeFace();
    faceHE.put(f, -firstFreeFace - 4);
    setFirstFreeFace(f);
    int nFaces = numberOfFaces();
    setNumberOfFaces(--nFaces);
    int removedF = numberOfRemovedFaces();
    setNumberOfRemovedFaces(++removedF);
    restoreIndexing(f, nFaces, faceIndex);
  }

  /**
   * The target vertex of h
   */
  @Override
  public int target(int h) {
    return heVertex.get(h);
  }

  /**
   * The source vertex of h
   */
  @Override
  public int source(int h) {
    return heVertex.get(opposite(h));
  }

  /**
   * A halfedge with target v
   */
  @Override
  public int vertexHalfedge(int v) {
    return vertexHE.get(v);
  }

  /**
   * The edge corresponding to h and opposite(h)
   */
  @Override
  public int edge(int h) {
    // opposite pairs are contiguous in the half edge list, so the edge
    // index is just h/2
    return h / 2;
  }

  /**
   * One of the halfedges corresponding to e
   */
  @Override
  public int edgeHalfedge(int e) {
    // opposite pairs are contiguous in the half edge list, so the half
    // indices are 2*e and 2*e+1. Just pick one
    return e * 2;
  }

  /**
   * The halfedge with source u and target v. To check if the halfedge is actually present, use {@link #isValidHalfedge(int)}
   */
  @Override
  public int halfedge(int source, int target) {
    int he = vertexHalfedge(target);
    int h = he;
    if (isValidHalfedge(h)) {
      do {
        if (source(h) == source) return h;
        h = opposite(next(h));
      }
      while (h != he);
    }
    return NULL_INDEX;
  }

  /**
   * Returns the degree of a face, that is, the number of incident half edges (or edges)
   */
  @Override
  public int faceDegree(int f) {
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

  /**
   * Returns the degree of a vertex, that is, the number of incident edges (or half edges that have this vertex as a source, or equivalently as a target)
   */
  @Override
  public int vertexDegree(int v) {
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

  /**
   * Returns the x coordinate of a vertex
   */
  @Override
  public double vertexX(int v) {
    return vertexX.get(v);
  }

  /**
   * Returns the y coordinate of a vertex
   */
  @Override
  public double vertexY(int v) {
    return vertexY.get(v);
  }

  /**
   * Returns the z coordinate of a vertex
   */
  @Override
  public double vertexZ(int v) {
    return vertexZ.get(v);
  }

  /**
   * Sets the x coordinate of a vertex
   */
  @Override
  public void setVertexX(int v, double d) {
    vertexX.put(v, d);
  }

  /**
   * Sets the y coordinate of a vertex
   */
  @Override
  public void setVertexY(int v, double d) {
    vertexY.put(v, d);
  }

  /**
   * Sets the z coordinate of a vertex
   */
  @Override
  public void setVertexZ(int v, double d) {
    vertexZ.put(v, d);
  }

  public int invalidIndex() {
    return INVALID_INDEX;
  }

  public int nullIndex() {
    return NULL_INDEX;
  }

  /**
   * Returns the index associated to a given vertex, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the vertex is not valid.
   */
  @Override
  public int vertexIndex(int v){
    if(!isValidVertex(v)) return invalidIndex();
    return vertexIndex.get(v);
  }
  
  /**
   * Returns the vertex associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfVertices()}.
   */
  @Override
  public int vertexAt(int i){
    if(i < 0 || i >= numberOfVertices()) return invalidIndex();
    return vertexIndex.get(i);
  }
  
  /**
   * Returns the index associated to a given edge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the edge is not valid.
   */
  @Override
  public int edgeIndex(int e){
    if(!isValidEdge(e)) return invalidIndex();
    return edgeIndex.get(e);
  }
  
  /**
   * Returns the edge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfEdges()}.
   */
  @Override
  public int edgeAt(int i){
    if(i < 0 || i >= numberOfEdges()) return invalidIndex();
    return edgeIndex.get(i);
  }
  
  /**
   * Returns the index associated to a given halfedge, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the halfedge is not valid.
   */
  @Override
  public int halfedgeIndex(int h){
    if(!isValidHalfedge(h)) return invalidIndex();
    int e = h / 2;
    int r = h % 2;
    return 2 * edgeIndex.get(e) + r;
  }
  
  /**
   * Returns the halfedge associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfHalfedges()}.
   */
  @Override
  public int halfedgeAt(int i){
    if(i < 0 || i >= numberOfHalfedges()) return invalidIndex();
    int ei = i / 2;
    int ri = i % 2;
    return 2 * edgeIndex.get(ei) + ri;
  }
  
  /**
   * Returns the index associated to a given face, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the face is not a valid face.
   */
  @Override
  public int faceIndex(int f){
    if(!isValidFace(f)) return invalidIndex();
    return faceIndex.get(f);
  }
  
  /**
   * Returns the face associated to a given index, or an invalid value (see {@link PolygonMeshBase#nullIndex()}) if the index is outside of the range 0, {@link PolygonMeshBase#numberOfFaces()}.
   */
  @Override
  public int faceAt(int i){
    if(i < 0 || i >= numberOfFaces()) return invalidIndex();
    return faceIndex.get(i);
  }


  @Override
  public AllVerticesDescriptorRange vertices() {
    return new AllVerticesDescriptorRange(this);
  }

  @Override
  public AllEdgesDescriptorRange edges() {
    return new AllEdgesDescriptorRange(this);
  }

  @Override
  public AllHalfedgesDescriptorRange halfedges() {
    return new AllHalfedgesDescriptorRange(this);
  }

  @Override
  public AllFacesDescriptorRange faces() {
    return new AllFacesDescriptorRange(this);
  }

  public enum PropertyElementType {
    VERTEX, HALFEDGE, EDGE, FACE;
  }

  public enum PropertyValueType {
    INT, DOUBLE, BYTE;
  }

  /**
   * Creates a property on the given element type, with the given value type and the given number of components
   */
  public IPolygonMeshProperty createProperty(PropertyElementType elementType, PropertyValueType propertyType, int nComponents) {
    Set<IPolygonMeshProperty> properties;
    int capacity;
    switch (elementType) {
      case EDGE:
        properties = edgeProperties;
        capacity = edgeCapacity();
        break;
      case FACE:
        properties = faceProperties;
        capacity = faceCapacity();
        break;
      case HALFEDGE:
        properties = halfedgeProperties;
        capacity = halfedgeCapacity();
        break;
      case VERTEX:
        properties = vertexProperties;
        capacity = vertexCapacity();
        break;
      default:
        throw new EnumConstantNotPresentException(PropertyElementType.class, elementType.name());
    }

    IPolygonMeshProperty property;
    switch (propertyType) {
      case BYTE:
        property = new PolygonMeshByteProperty(capacity, nComponents);
        break;
      case DOUBLE:
        property = new PolygonMeshDoubleProperty(capacity, nComponents);
        break;
      case INT:
        property = new PolygonMeshIntProperty(capacity, nComponents);
        break;
      default:
        throw new EnumConstantNotPresentException(PropertyValueType.class, propertyType.name());
    }
    properties.add(property);
    return property;
  }

  /**
   * Removes the property from the Polygon Mesh. Returns true if the property was found and removed, and false if the property was not found.
   */
  public boolean removeProperty(PropertyElementType elementType, IPolygonMeshProperty property) {
    Set<IPolygonMeshProperty> properties;
    switch (elementType) {
      case EDGE:
        properties = edgeProperties;
        break;
      case FACE:
        properties = faceProperties;
        break;
      case HALFEDGE:
        properties = halfedgeProperties;
        break;
      case VERTEX:
        properties = vertexProperties;
        break;
      default:
        throw new EnumConstantNotPresentException(PropertyElementType.class, elementType.name());
    }
    return properties.remove(property);
  }

  // specific properties, used by CGAL algorithms

  public IPolygonMeshDoubleProperty createVertexNormalProperty() {
    return (IPolygonMeshDoubleProperty) createProperty(PropertyElementType.VERTEX, PropertyValueType.DOUBLE, 3);
  }

  public IPolygonMeshDoubleProperty createFaceNormalProperty() {
    return (IPolygonMeshDoubleProperty) createProperty(PropertyElementType.FACE, PropertyValueType.DOUBLE, 3);
  }

  public IPolygonMeshIntProperty createFaceConnectedComponentProperty() {
    return (IPolygonMeshIntProperty) createProperty(PropertyElementType.FACE, PropertyValueType.INT, 1);
  }

  public IPolygonMeshByteProperty createEdgeIsConstrainedProperty() {
    return (IPolygonMeshByteProperty) createProperty(PropertyElementType.EDGE, PropertyValueType.BYTE, 1);
  }

  public IPolygonMeshByteProperty getVertexIsConstrainedProperty() {
    return (IPolygonMeshByteProperty) createProperty(PropertyElementType.VERTEX, PropertyValueType.BYTE, 1);
  }

}
