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

/**
 * Base class containing base buffers and C++ access functions for a {@link PolygonMesh}
 */
public abstract class PolygonMeshAccess {

  protected enum ElementIndex {
    VERTEX(0), EDGE(1), FACE(2);

    private int i;

    ElementIndex(int index) {
      this.i = index;
    }

    public int index() {
      return i;
    }

  }

  // HE connectivity
  protected IntBuffer nextHE;
  protected IntBuffer prevHE;
  protected IntBuffer heVertex;
  protected IntBuffer heFace;

  // no need for opposite -- by default, opposite pairs are stored at
  // contiguous even/odd indices
  // for each vertex, store an incoming half edge
  protected IntBuffer vertexHE;
  // faces
  protected IntBuffer faceHE;
  // vertex coordinates
  protected DoubleBuffer vertexX, vertexY, vertexZ;
  // counters
  protected IntBuffer elementSize;

  // garbage collection system
  //
  // position of the first free elements
  protected IntBuffer firstFreeElement;
  // total capacity for elements
  protected IntBuffer elementCapacity;
  // number of removed elements, i.e., number of "holes" in the element array
  protected IntBuffer removedElement;

  // buffers containing indices
  // indexing is done so that the map element <-> index is a permutation which only contains cycles of order 1 and 2
  // this way, the permutation is its own inverse (involution) and can be used to translate element to index and vice versa
  // if there are V vertices and the capacity is C, i.e., there are H "holes", the following rule is maintained:
  // - Every vertex in position 1...V and every hole in position V+1...H is in a cycle of order 1 (i.e., its index is equal to its id)
  // - Every vertex in position V+1...H is coupled with a hole in position 0...V, so that they are part of a cycle of order 2
  protected IntBuffer vertexIndex;
  protected IntBuffer edgeIndex;
  protected IntBuffer faceIndex;

  /**
   * Empty constructor, used by derived classes
   */
  protected PolygonMeshAccess() {}

  /**
   * Copy constructor. Only copies references to buffers, used by derived classes to be built on top of other {@link PolygonMeshAccess}.
   */
  protected PolygonMeshAccess(PolygonMeshAccess other) {
    copyReferences(other, this);
  }

  /**
   * Copies the references to the buffers.
   */
  protected static PolygonMeshAccess copyReferences(PolygonMeshAccess source, PolygonMeshAccess target) {
    target.elementCapacity = source.elementCapacity;
    target.elementSize = source.elementSize;
    target.firstFreeElement = source.firstFreeElement;
    target.removedElement = source.removedElement;
    target.nextHE = source.nextHE;
    target.prevHE = source.prevHE;
    target.heFace = source.heFace;
    target.heVertex = source.heVertex;
    target.vertexHE = source.vertexHE;
    target.vertexX = source.vertexX;
    target.vertexY = source.vertexY;
    target.vertexZ = source.vertexZ;
    target.faceHE = source.faceHE;
    target.vertexIndex = source.vertexIndex;
    target.edgeIndex = source.edgeIndex;
    target.faceIndex = source.faceIndex;
    return target;
  }
  
  /**
   * Returns a copy of the mesh.
   */
  public static PolygonMeshAccess copy(PolygonMeshAccess source, PolygonMeshAccess target) {
    target.elementCapacity = PolygonMeshUtils.allocateNewIntBuffer(source.elementCapacity);
    target.elementSize = PolygonMeshUtils.allocateNewIntBuffer(source.elementSize);
    target.firstFreeElement = PolygonMeshUtils.allocateNewIntBuffer(source.firstFreeElement);
    target.removedElement = PolygonMeshUtils.allocateNewIntBuffer(source.removedElement);
    target.nextHE = PolygonMeshUtils.allocateNewIntBuffer(source.nextHE);
    target.prevHE = PolygonMeshUtils.allocateNewIntBuffer(source.prevHE);
    target.heFace = PolygonMeshUtils.allocateNewIntBuffer(source.heFace);
    target.heVertex = PolygonMeshUtils.allocateNewIntBuffer(source.heVertex);
    target.faceHE = PolygonMeshUtils.allocateNewIntBuffer(source.faceHE);
    target.vertexHE = PolygonMeshUtils.allocateNewIntBuffer(source.vertexHE);
    target.vertexX = PolygonMeshUtils.allocateNewDoubleBuffer(source.vertexX);
    target.vertexY = PolygonMeshUtils.allocateNewDoubleBuffer(source.vertexY);
    target.vertexZ = PolygonMeshUtils.allocateNewDoubleBuffer(source.vertexZ);
    target.vertexIndex = PolygonMeshUtils.allocateNewIntBuffer(source.vertexIndex);
    target.edgeIndex = PolygonMeshUtils.allocateNewIntBuffer(source.edgeIndex);
    target.faceIndex = PolygonMeshUtils.allocateNewIntBuffer(source.faceIndex);
    return target;
  }

  /////////////////////////////////////
  // low level functions called by C //
  /////////////////////////////////////

  /**
   * Returns the nextHE array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getNextHEArray() {
    return nextHE;
  }

  /**
   * Returns the prevHE array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getPrevHEArray() {
    return prevHE;
  }

  /**
   * Returns the heFace array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getHEFaceArray() {
    return heFace;
  }

  /**
   * Returns the heVertex array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getHEVertexArray() {
    return heVertex;
  }

  /**
   * Returns the vertexHE array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getVertexHEArray() {
    return vertexHE;
  }

  /**
   * Returns the faceHE array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getFaceHEArray() {
    return faceHE;
  }

  /**
   * Returns the vertexX array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final DoubleBuffer getVertexXArray() {
    return vertexX;
  }

  /**
   * Returns the vertexY array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getVertexYArray() {
    return vertexY;
  }

  /**
   * Returns the vertexZ array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final DoubleBuffer getVertexZArray() {
    return vertexZ;
  }

  /**
   * Returns the array containing the capacity for the three element types.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getElementCapacity() {
    return elementCapacity;
  }

  /**
   * Returns the array containing the first free element for the three element types.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getFirstFreeElement() {
    return firstFreeElement;
  }

  /**
   * Returns the array containing the element size for the three element types.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getElementSize() {
    return elementSize;
  }

  /**
   * Returns the array containing the number of removed elements for the three element types.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getRemovedElement() {
    return removedElement;
  }

  /**
   * Returns the vertexIndex array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getVertexIndexArray() {
    return vertexIndex;
  }
  
  /**
   * Returns the edgeIndex array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getEdgeIndexArray() {
    return edgeIndex;
  }

  /**
   * Returns the faceIndex array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getFaceIndexArray() {
    return faceIndex;
  }
}
