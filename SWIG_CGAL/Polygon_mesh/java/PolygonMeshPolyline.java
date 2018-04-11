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

public class PolygonMeshPolyline implements IPolygonMeshPolyline {

  private DoubleBuffer coords;
  private final IntBuffer sizeAndCapacity;

  private static int DEFAULT_CAPACITY = 10;
  protected static final int SIZE_ID = 0;
  protected static final int CAPACITY_ID = 1;

  /**
   * Creates an empty polyline with an initial capacity of ten points.
   */
  public PolygonMeshPolyline() {
    this(DEFAULT_CAPACITY);
  }

  /**
   * Creates an empty polyline with a given initial capacity.
   */
  public PolygonMeshPolyline(int initialCapacity) {
    //init coords
    this.coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * initialCapacity);
    //init size_and_capacity
    this.sizeAndCapacity = PolygonMeshUtils.allocateNewIntBuffer(2);
    this.sizeAndCapacity.put(SIZE_ID, 0);
    this.sizeAndCapacity.put(CAPACITY_ID, initialCapacity);
  }

  /**
   * Adds the given point to the polyline
   */
  @Override
  public void pushBack(double x, double y, double z) {
    int size = sizeAndCapacity.get(SIZE_ID);
    ensureCapacity(size + 1);
    coords.put(3 * size, x);
    coords.put(3 * size + 1, y);
    coords.put(3 * size + 2, z);
    size++;
    sizeAndCapacity.put(SIZE_ID, size);
  }

  /**
   * Ensures that the capacity of this object is equal to the given value or higher
   */
  public void ensureCapacity(int minCapacity) {
    int currentCapacity = sizeAndCapacity.get(CAPACITY_ID);
    while (currentCapacity < minCapacity) {
      currentCapacity = PolygonMeshUtils.nextCapacity(currentCapacity);
    }
    realloc(currentCapacity);
  }

  /**
   * Returns the number of points in the polyline
   */
  @Override
  public int getNumberOfPoints() {
    return sizeAndCapacity.get(SIZE_ID);
  }

  private void realloc(int newCapacity) {
    if (newCapacity <= sizeAndCapacity.get(CAPACITY_ID)) return;
    coords = PolygonMeshUtils.allocateNewDoubleBuffer(3 * newCapacity, coords);
    sizeAndCapacity.put(CAPACITY_ID, newCapacity);
  }

  /**
   * Method used by native code to access the incrase the array capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  public DoubleBuffer increaseCapacity() {
    realloc(PolygonMeshUtils.nextCapacity(sizeAndCapacity.get(CAPACITY_ID)));
    return coords;
  }

  /**
   * Method used by native code to access the array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getArray() {
    return coords;
  }

  /**
   * Method used by native code to access the array size and capacity.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getSizeAndCapacity() {
    return sizeAndCapacity;
  }

}
