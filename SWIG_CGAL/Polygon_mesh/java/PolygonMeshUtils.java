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

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.DoubleBuffer;
import java.nio.IntBuffer;

public class PolygonMeshUtils {

  private PolygonMeshUtils() {
    // no instantiation
  }

  public static IntBuffer allocateNewIntBuffer(int newSize) {
    return allocateNewIntBuffer(newSize, null);
  }

  public static IntBuffer allocateNewIntBuffer(IntBuffer original) {
    return allocateNewIntBuffer(original.capacity(), original);
  }

  public static IntBuffer allocateNewIntBuffer(int newSize, IntBuffer original) {
    ByteBuffer bb = ByteBuffer.allocateDirect(newSize * Integer.BYTES);
    bb.order(ByteOrder.nativeOrder());
    IntBuffer intBuffer = bb.asIntBuffer();
    if (original != null) {
      original.rewind();
      intBuffer.put(original);
    }
    return intBuffer;
  }

  public static DoubleBuffer allocateNewDoubleBuffer(int newSize) {
    return allocateNewDoubleBuffer(newSize, null);
  }

  public static DoubleBuffer allocateNewDoubleBuffer(DoubleBuffer original) {
    return allocateNewDoubleBuffer(original.capacity(), original);
  }

  public static DoubleBuffer allocateNewDoubleBuffer(int newSize, DoubleBuffer original) {
    ByteBuffer bb = ByteBuffer.allocateDirect(newSize * Double.BYTES);
    bb.order(ByteOrder.nativeOrder());
    DoubleBuffer doubleBuffer = bb.asDoubleBuffer();
    if (original != null) {
      original.rewind();
      doubleBuffer.put(original);
    }
    return doubleBuffer;
  }

  public static ByteBuffer allocateNewByteBuffer(int newSize) {
    return allocateNewByteBuffer(newSize, null);
  }

  public static ByteBuffer allocateNewByteBuffer(ByteBuffer original) {
    return allocateNewByteBuffer(original.capacity(), original);
  }

  public static ByteBuffer allocateNewByteBuffer(int newSize, ByteBuffer original) {
    ByteBuffer bb = ByteBuffer.allocateDirect(newSize * Byte.BYTES);
    bb.order(ByteOrder.nativeOrder());
    return bb;
  }

  public static int nextCapacity(int currentCapacity) {
    return (currentCapacity * 3) / 2 + 1;
  }

}
