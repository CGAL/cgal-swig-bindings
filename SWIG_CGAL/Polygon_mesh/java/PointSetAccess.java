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
 * Base class containing base buffers and C++ access functions for a {@link PointSet}
 */
public abstract class PointSetAccess {

  // point coordinates
  protected DoubleBuffer pointX, pointY, pointZ;
  // point indices
  protected IntBuffer pointIndex;
  // size and capacity
  protected IntBuffer sizeAndCapacity;

  /**
   * Empty constructor, used by derived classes
   */
  protected PointSetAccess() {}

  /**
   * Copy constructor. Only copies references to buffers, used by derived classes to be built on top of other {@link PointSetAccess}.
   */
  protected PointSetAccess(PointSetAccess other) {
    copyReferences(other, this);
  }

  /**
   * Copies the references to the buffers.
   */
  protected static PointSetAccess copyReferences(PointSetAccess source, PointSetAccess target) {
    target.pointX = source.pointX;
    target.pointY = source.pointY;
    target.pointZ = source.pointZ;
    target.pointIndex = source.pointIndex;
    target.sizeAndCapacity = source.sizeAndCapacity;
    return target;
  }

  /**
   * Returns a copy of the mesh.
   */
  public static PointSetAccess copy(PointSetAccess source, PointSetAccess target) {
    target.pointX = PolygonMeshUtils.allocateNewDoubleBuffer(source.pointX);
    target.pointY = PolygonMeshUtils.allocateNewDoubleBuffer(source.pointY);
    target.pointZ = PolygonMeshUtils.allocateNewDoubleBuffer(source.pointZ);
    target.pointIndex = PolygonMeshUtils.allocateNewIntBuffer(source.pointIndex);
    target.sizeAndCapacity = PolygonMeshUtils.allocateNewIntBuffer(source.sizeAndCapacity);
    return target;
  }

  /////////////////////////////////////
  // low level functions called by C //
  /////////////////////////////////////
  /**
   * Returns the pointX array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final DoubleBuffer getPointXArray() {
    return pointX;
  }

  /**
   * Returns the pointY array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final DoubleBuffer getPointYArray() {
    return pointY;
  }

  /**
   * Returns the pointZ array.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final DoubleBuffer getPointZArray() {
    return pointZ;
  }

  /**
   * Returns the array containing the point size and capacity.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getSizeAndCapacity() {
    return sizeAndCapacity;
  }

  /**
   * Returns the array containing the array of internal indexing of points.<br>
   * <b>Warning:</b> do not suppress this method (even if unused) since it is called by C++ code.
   */
  @SuppressWarnings("unused")
  private final IntBuffer getPointIndex() {
    return pointIndex;
  }
}
