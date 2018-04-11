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

public class PolygonMeshSkeleton implements IPolygonMeshSkeleton {

  private DoubleBuffer coords;
  private IntBuffer edges;
  private final IntBuffer sizesAndCapacities;

  protected static final int COORDS_SIZE_ID = 0;
  protected static final int EDGES_SIZE_ID = 1;
  protected static final int COORDS_CAPACITY_ID = 2;
  protected static final int EDGES_CAPACITY_ID = 3;

  /**
   * Creates an empty skeleton with an initial capacity of ten points and ten edges.
   */
  public PolygonMeshSkeleton() {
    this(10,10);
  }

  /**
   * Creates an empty skeleton with given initial points and edge capacities.
   */
  public PolygonMeshSkeleton(int initialCoordCapacity, int initialEdgeCapacity) {
    //init coords
    this.coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * initialCoordCapacity);
    this.edges = PolygonMeshUtils.allocateNewIntBuffer(2 * initialEdgeCapacity);
    //init size_and_capacity
    this.sizesAndCapacities = PolygonMeshUtils.allocateNewIntBuffer(4);
    this.sizesAndCapacities.put(COORDS_SIZE_ID, 0);
    this.sizesAndCapacities.put(EDGES_SIZE_ID, 0);
    this.sizesAndCapacities.put(COORDS_CAPACITY_ID, initialCoordCapacity);
    this.sizesAndCapacities.put(EDGES_CAPACITY_ID, initialEdgeCapacity);
  }

  /**
   * Add the given point to the skeleton
   */
  @Override
  public void pushBackPoint(double x, double y, double z) {
    int size = sizesAndCapacities.get(COORDS_SIZE_ID);
    ensureCoordsCapacity(size + 1);
    coords.put(3 * size, x);
    coords.put(3 * size + 1, y);
    coords.put(3 * size + 2, z);
    sizesAndCapacities.put(COORDS_SIZE_ID, size+1);
  }

  /**
   * Add the given edge to the skeleton
   */
  @Override
  public void pushBackEdge(int i, int j) {
    int size = sizesAndCapacities.get(COORDS_SIZE_ID);
    ensureEdgesCapacity(size + 1);
    edges.put(2 * size, i);
    edges.put(2 * size + 1, j);
    sizesAndCapacities.put(EDGES_SIZE_ID, size+1);
  }

  /**
   * Ensures that the point capacity of this object is equal to the given value or higher
   */
  public void ensureCoordsCapacity(int minCapacity) {
    int currentCapacity = sizesAndCapacities.get(COORDS_CAPACITY_ID);
    while (currentCapacity < minCapacity) {
      currentCapacity = PolygonMeshUtils.nextCapacity(currentCapacity);
    }
    reallocCoords(currentCapacity);
  }

  /**
   * Ensures that the edge capacity of this object is equal to the given value or higher
   */
  public void ensureEdgesCapacity(int minCapacity) {
    int currentCapacity = sizesAndCapacities.get(EDGES_CAPACITY_ID);
    while (currentCapacity < minCapacity) {
      currentCapacity = PolygonMeshUtils.nextCapacity(currentCapacity);
    }
    reallocEdges(currentCapacity);
  }

  /**
   * Returns the number of points in the skeleton
   */
  @Override
  public int getNumberOfPoints() {
    return sizesAndCapacities.get(COORDS_SIZE_ID);
  }

  /**
   * Returns the number of edges in the skeleton
   */
  @Override
  public int getNumberOfEdges() {
    return sizesAndCapacities.get(EDGES_SIZE_ID);
  }

  private void reallocCoords(int newCapacity) {
    if (newCapacity <= sizesAndCapacities.get(COORDS_CAPACITY_ID)) return;
    coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * newCapacity, coords);
    sizesAndCapacities.put(COORDS_CAPACITY_ID, newCapacity);
  }

  private void reallocEdges(int newCapacity) {
    if (newCapacity <= sizesAndCapacities.get(EDGES_CAPACITY_ID)) return;
    edges = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, edges);
    sizesAndCapacities.put(EDGES_CAPACITY_ID, newCapacity);
  }

  /**
   * Method used by native code to access the increase the coords array capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  public DoubleBuffer setCoordsCapacity(int capacity) {
    ensureCoordsCapacity(capacity);
    return coords;
  }

  /**
   * Method used by native code to access the increase the edges array capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  public IntBuffer setEdgesCapacity(int capacity) {
    ensureEdgesCapacity(capacity);
    return edges;
  }

  /**
   * Method used by native code to access the coord array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getCoordsArray() {
    return coords;
  }

  /**
   * Method used by native code to access the edge array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getEdgesArray() {
    return edges;
  }

  /**
   * Method used by native code to access the array size and capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getsizesAndCapacities() {
    return sizesAndCapacities;
  }

}
