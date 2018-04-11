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

public class PolygonMeshMultiPolyline implements IPolygonMeshMultiPolyline {

  private DoubleBuffer coords;
  private IntBuffer polylineEndpoints;
  private final IntBuffer sizesAndCapacities;

  private static int DEFAULT_CAPACITY = 10;
  private static int DEFAULT_N_POLYLINES = 1;
  protected static final int VERTEX_SIZE_ID = 0;
  protected static final int POLYLINE_SIZE_ID = 1;
  protected static final int VERTEX_CAPACITY_ID = 2;
  protected static final int POLYLINE_CAPACITY_ID = 3;

  /**
   * Creates an empty multi polyline with an initial capacity of ten points.
   */
  public PolygonMeshMultiPolyline() {
    this(DEFAULT_CAPACITY, DEFAULT_N_POLYLINES);
  }

  /**
   * Creates an empty multipolyline with a given initial capacity for polylines and vertices.
   */
  public PolygonMeshMultiPolyline(int estimatedVerticesPerPolyline, int estimatedNumberOfPolylines) {
    //init coords
    this.coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * estimatedVerticesPerPolyline * estimatedNumberOfPolylines);
    this.polylineEndpoints = PolygonMeshUtils.allocateNewIntBuffer(2 * estimatedNumberOfPolylines);
    //init size_and_capacity
    this.sizesAndCapacities = PolygonMeshUtils.allocateNewIntBuffer(4);
    this.sizesAndCapacities.put(VERTEX_SIZE_ID, 0);
    this.sizesAndCapacities.put(POLYLINE_SIZE_ID, 0);
    this.sizesAndCapacities.put(VERTEX_CAPACITY_ID, estimatedNumberOfPolylines * estimatedVerticesPerPolyline);
    this.sizesAndCapacities.put(POLYLINE_CAPACITY_ID, estimatedNumberOfPolylines);
  }

  /**
   * Adds the given point to the last started polyline
   */
  @Override
  public void pushBack(double x, double y, double z) {
    int size = sizesAndCapacities.get(VERTEX_SIZE_ID);
    ensureVertexCapacity(size + 1);
    coords.put(3 * size, x);
    coords.put(3 * size + 1, y);
    coords.put(3 * size + 2, z);
    size++;
    sizesAndCapacities.put(VERTEX_SIZE_ID, size);
  }
  
  /**
   * Starts a new polyline. The old polyline is considered finalized and can no longer be modified.
   */
  @Override
  public void beginPolyline() {
    int size = sizesAndCapacities.get(POLYLINE_SIZE_ID);
    int nVertices = sizesAndCapacities.get(VERTEX_SIZE_ID);
    ensurePolylineCapacity(size + 1);
    polylineEndpoints.put(2 * size, nVertices); 
  }

  @Override
  public void endPolyline() {
    int size = sizesAndCapacities.get(POLYLINE_SIZE_ID);
    int nVertices = sizesAndCapacities.get(VERTEX_SIZE_ID);
    ensurePolylineCapacity(size + 1);
    polylineEndpoints.put(2 * size + 1, nVertices); 
    size++;
    sizesAndCapacities.put(POLYLINE_SIZE_ID, size);
  }

  /**
   * Ensures that the vertex capacity of this object is equal to the given value or higher
   */
  public void ensureVertexCapacity(int minCapacity) {
    int currentCapacity = sizesAndCapacities.get(VERTEX_CAPACITY_ID);
    while (currentCapacity < minCapacity) {
      currentCapacity = PolygonMeshUtils.nextCapacity(currentCapacity);
    }
    reallocVertices(currentCapacity);
  }
  
  /**
   * Ensures that the polyline capacity of this object is equal to the given value or higher
   */
  public void ensurePolylineCapacity(int minCapacity) {
    int currentCapacity = sizesAndCapacities.get(POLYLINE_CAPACITY_ID);
    while (currentCapacity < minCapacity) {
      currentCapacity = PolygonMeshUtils.nextCapacity(currentCapacity);
    }
    reallocPolylines(currentCapacity);
  }

  /**
   * Returns the number of polylines in this object
   */
  @Override
  public int getNumberOfPolylines() {
    return sizesAndCapacities.get(POLYLINE_SIZE_ID);
  }

  /**
   * Returns the number of points in the i-th polyline
   */
  @Override
  public int getNumberOfPoints(int i) {
    return polylineEndpoints.get(2 * i + 1) - polylineEndpoints.get(2 * i);
  }

  private void reallocVertices(int newCapacity) {
    if (newCapacity <= sizesAndCapacities.get(VERTEX_CAPACITY_ID)) return;
    coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * newCapacity, coords);
    sizesAndCapacities.put(VERTEX_CAPACITY_ID, newCapacity);
  }

  private void reallocPolylines(int newCapacity) {
    if (newCapacity <= sizesAndCapacities.get(POLYLINE_CAPACITY_ID)) return;
    polylineEndpoints = PolygonMeshUtils.allocateNewIntBuffer(2 * newCapacity, polylineEndpoints);
    sizesAndCapacities.put(POLYLINE_CAPACITY_ID, newCapacity);
  }

  /**
   * Method used by native code to access the incrase the vertex array capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  public DoubleBuffer increaseVertexCapacity() {
    reallocVertices(PolygonMeshUtils.nextCapacity(sizesAndCapacities.get(VERTEX_CAPACITY_ID)));
    return coords;
  }
  
  /**
   * Method used by native code to access the incrase the polyline endpoints array capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  public IntBuffer increasePolylineCapacity() {
    reallocPolylines(PolygonMeshUtils.nextCapacity(sizesAndCapacities.get(POLYLINE_CAPACITY_ID)));
    return polylineEndpoints;
  }

  /**
   * Method used by native code to access the vertex array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getVertexArray() {
    return coords;
  }

  /**
   * Method used by native code to access the polyline endpoints array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getPolylineArray() {
    return polylineEndpoints;
  }

  /**
   * Method used by native code to access the array size and capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getSizesAndCapacities() {
    return sizesAndCapacities;
  }

}
