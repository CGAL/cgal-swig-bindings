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

import java.nio.IntBuffer;
import java.util.Collection;
import java.util.PrimitiveIterator;
import java.util.function.IntUnaryOperator;


public class PolygonMeshRange {

  private PolygonMeshRange() {
    // no initialization
  }

  /**
   * Type of element range
   */
  public enum RangeType {
    /**
     * All elements of given type
     */
    ALL_ELEMENTS(0),
    /**
     * A subset of elements of the given type
     */
    SUB_RANGE(1);

    RangeType(int i) {
      this.cgalIndex = i;
    }

    private int cgalIndex;

    public int index() {
      return cgalIndex;
    }
  }

  public interface DescriptorRange {
    int getType();
  }

  public abstract static class SubRange implements DescriptorRange {

    private static final int DEFAULT_CAPACITY = 10;
    protected static final int SIZE_ID = 0;
    protected static final int CAPACITY_ID = 1;

    protected IntBuffer range;
    protected IntBuffer sizeAndCapacity;

    public SubRange() {
      //init range
      this.range = PolygonMeshUtils.allocateNewIntBuffer(DEFAULT_CAPACITY);
      //init sizeAndCapacity
      this.sizeAndCapacity = PolygonMeshUtils.allocateNewIntBuffer(2);
      this.sizeAndCapacity.put(SIZE_ID, 0);
      this.sizeAndCapacity.put(CAPACITY_ID, range.capacity());
    }

    /**
     * Adds the given index to the range
     */
    public void add(int i) {
      int size = sizeAndCapacity.get(SIZE_ID);
      ensureCapacity(size + 1);
      range.put(size++, i);
      sizeAndCapacity.put(SIZE_ID, size);
    }

    /**
     * Adds the given indices to the range
     */
    public void add(int[] indices) {
      int size = sizeAndCapacity.get(SIZE_ID);
      ensureCapacity(size + indices.length);
      for (int i : indices)
        range.put(size++, i);
      sizeAndCapacity.put(SIZE_ID, size);
    }

    /**
     * Adds the given indices to the range
     */
    public void add(Collection<Integer> indices) {
      int size = sizeAndCapacity.get(SIZE_ID);
      ensureCapacity(size + indices.size());
      for (int i : indices)
        range.put(size++, i);
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
     * Returns the size of the range
     */
    public int getSize() {
      return sizeAndCapacity.get(SIZE_ID);
    }

    private void realloc(int newCapacity) {
      if (newCapacity <= sizeAndCapacity.get(CAPACITY_ID)) return;
      range = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, range);
      sizeAndCapacity.put(CAPACITY_ID, newCapacity);
    }

    /**
     * Method used by native code to access the incrase the array capacity.<br>
     * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
     */
    @SuppressWarnings("unused")
    private IntBuffer increaseCapacity() {
      realloc(PolygonMeshUtils.nextCapacity(sizeAndCapacity.get(CAPACITY_ID)));
      return range;
    }

    /**
     * Method used by native code to access the array.<br>
     * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
     */
    @SuppressWarnings("unused")
    private IntBuffer getArray() {
      return range;
    }

    /**
     * Method used by native code to access the array size and capacity.<br>
     * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
     */
    @SuppressWarnings("unused")
    private IntBuffer getSizeAndCapacity() {
      return sizeAndCapacity;
    }

    @Override
    public int getType() {
      return RangeType.SUB_RANGE.index();
    }

  }

  public interface VertexDescriptorRange extends DescriptorRange {}
  public interface EdgeDescriptorRange extends DescriptorRange {}
  public interface HalfedgeDescriptorRange extends DescriptorRange {}
  public interface FaceDescriptorRange extends DescriptorRange {}

  public static class VertexDescriptorSubRange extends SubRange implements VertexDescriptorRange {}
  public static class EdgeDescriptorSubRange extends SubRange implements EdgeDescriptorRange {}
  public static class HalfedgeDescriptorSubRange extends SubRange implements HalfedgeDescriptorRange {}
  public static class FaceDescriptorSubRange extends SubRange implements FaceDescriptorRange {}

  public static class VertexDescriptorOutputRange extends VertexDescriptorSubRange {}
  public static class EdgeDescriptorOutputRange extends EdgeDescriptorSubRange {}
  public static class HalfedgeDescriptorOutputRange extends HalfedgeDescriptorSubRange {}
  public static class FaceDescriptorOutputRange extends FaceDescriptorSubRange {}

  /**
   * Interface
   */
  private static class IndexedElementIterator implements PrimitiveIterator.OfInt, DescriptorRange {
    private int i;
    private int max;
    private IntUnaryOperator indexer;

    public IndexedElementIterator(IntUnaryOperator indexer, int max) {
      this.max = max;
      this.indexer = indexer;
    }

    @Override
    public boolean hasNext() {
      return  i < max;
    }

    @Override
    public int nextInt() {
      return indexer.applyAsInt(i++);
    }

    @Override
    public int getType() {
      return RangeType.ALL_ELEMENTS.index();
    }

  }

  public static class AllVerticesDescriptorRange extends IndexedElementIterator implements VertexDescriptorRange {

    public AllVerticesDescriptorRange(PolygonMeshBase mesh) {
      super(i -> mesh.vertexAt(i), mesh.numberOfVertices());
    }

  }

  public static class AllEdgesDescriptorRange extends IndexedElementIterator implements EdgeDescriptorRange {

    public AllEdgesDescriptorRange(PolygonMeshBase mesh) {
      super(i -> mesh.edgeAt(i), mesh.numberOfEdges());
    }

  }

  public static class AllHalfedgesDescriptorRange extends IndexedElementIterator implements HalfedgeDescriptorRange {

    public AllHalfedgesDescriptorRange(PolygonMeshBase mesh) {
      super(i -> mesh.halfedgeAt(i),  mesh.numberOfHalfedges());
    }

  }

  public static class AllFacesDescriptorRange extends IndexedElementIterator implements FaceDescriptorRange {

    public AllFacesDescriptorRange(PolygonMeshBase mesh) {
      super(i -> mesh.faceAt(i), mesh.numberOfFaces());
    }

  }

}
