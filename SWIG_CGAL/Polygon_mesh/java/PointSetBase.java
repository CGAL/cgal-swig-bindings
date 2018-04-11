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

/**
 * Base class containing base buffers, C++ access functions and basic operations for a {@link PointSet}
 * The class is an array of indices and each index corresponds to a point. Each property associated to
 * a point uses the index to access it. The only time an index is set is when the capacity is increased.
 * Initially pointIndex.get(i)==i.
 * A resize without changing the capacity is only a setting of the size variable. A removal is a swap
 * of the last index with the index marked as removed + a decrease of 1 of the size.
 *
 */
public class PointSetBase extends PointSetAccess implements IPointSetBase {

  // default initial capacity if none is specified
  protected static final int DEFAULT_CAPACITY = 10;

  private Set<IPolygonMeshProperty> properties;

  /**
   * Creates an empty {@link PointSetBase}, with a given initial capacity for points.
   */
  public PointSetBase(int estimatedNPoints) {
    properties = new HashSet<>();
    this.sizeAndCapacity = PolygonMeshUtils.allocateNewIntBuffer(2);
    increaseCapacity(estimatedNPoints);
  }

  /**
   * Creates an empty {@link PointSetBase}, with a default initial capacity of ten.
   */
  public PointSetBase() {
    this(DEFAULT_CAPACITY);
  }

  /**
   * Copy constructor. Only copies references to buffers and properties, used by derived classes to be built on top of other {@link PointSetBase}.
   */
  protected PointSetBase(PointSetBase other) {
    super(other);
    this.properties = other.properties;
  }

  /**
   * Increases the capacity
   */
  public void reserve(int nv) {
    increaseCapacity(nv);
  }

  /**
   * Returns a copy of the mesh.
   */
  @Override
  public PointSetBase copy() {
    PointSetBase copy = new PointSetBase();
    PointSetAccess.copy(this, copy);
    for(IPolygonMeshProperty vP : properties) {
       copy.properties.add(vP.copy());
    }
    return copy;
  }

  /**
   * Increases the storage capacity for vertices and returns the new capacity
   */
  protected void increaseCapacity() {
    increaseCapacity(PolygonMeshUtils.nextCapacity(Capacity()));
  }

  protected void increaseCapacity(int newCapacity) {
    int oldCapacity = Capacity();
    if (oldCapacity >= newCapacity) return;

    DoubleBuffer newPointX = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, pointX);
    DoubleBuffer newPointY = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, pointY);
    DoubleBuffer newPointZ = PolygonMeshUtils.allocateNewDoubleBuffer(newCapacity, pointZ);
    IntBuffer newPointIndex = PolygonMeshUtils.allocateNewIntBuffer(newCapacity, pointIndex);

    pointX=newPointX;
    pointY=newPointY;
    pointZ=newPointZ;
    pointIndex = newPointIndex;

    sizeAndCapacity.put(1, newCapacity);

    for(int i=oldCapacity; i<newCapacity; ++i)
    {
      pointIndex.put(i,i);
    }

    // resize properties
    for (IPolygonMeshProperty property : properties) {
      property.resize(newCapacity);
    }
  }

  /**
   * Returns the capacity of the container
   */
  @Override
  public int Capacity() {
    return sizeAndCapacity.get(1);
  }

  /**
   * Returns the number of points
   */
  @Override
  public int getNumberOfPoints() {
    return sizeAndCapacity.get(0);
  }

  /**
   * Adds a new point
   */
  @Override
  public int addPoint() {
    int newId = sizeAndCapacity.get(0);
    int newSize = newId+1;
    if (newSize > sizeAndCapacity.get(1))
      increaseCapacity();
    sizeAndCapacity.put(0, newSize);
    return newId;
  }

  /**
   * Adds a new point and set its coordinates
   */
  @Override
  public int addPoint(double x, double y, double z)
  {
    int i=addPoint();
    setPointX(i, x);
    setPointY(i, y);
    setPointZ(i, z);
    return i;
  }

  /**
   * Removes a point
   */
  @Override
  public void removePoint(int i) {
    int newSize=sizeAndCapacity.get(0)-1;
    if (i!=newSize)
    {
      // swap indices
      int lastIndex=pointIndex.get(newSize);
      pointIndex.put(newSize, pointIndex.get(i));
      pointIndex.put(i, lastIndex);
    }
    sizeAndCapacity.put(0, newSize);
  }

  /**
   * Returns the x coordinate of a point
   */
  @Override
  public double pointX(int i) {
    return pointX.get( pointIndex.get(i) );
  }

  /**
   * Returns the y coordinate of a point
   */
  @Override
  public double pointY(int i) {
    return pointY.get( pointIndex.get(i) );
  }

  /**
   * Returns the z coordinate of a point
   */
  @Override
  public double pointZ(int i) {
    return pointZ.get( pointIndex.get(i) );
  }

  /**
   * Sets the x coordinate of a point
   */
  @Override
  public void setPointX(int i, double d) {
    pointX.put( pointIndex.get(i), d );
  }

  /**
   * Sets the y coordinate of a point
   */
  @Override
  public void setPointY(int i, double d) {
    pointY.put( pointIndex.get(i), d );
  }

  /**
   * Sets the z coordinate of a point
   */
  @Override
  public void setPointZ(int i, double d) {
    pointZ.put( pointIndex.get(i), d );
  }

  /**
   * Returns the index associated to a given point
   */
  @Override
  public int getIndex(int i){
    return pointIndex.get(i);
  }

  public enum PropertyValueType {
    INT, DOUBLE, BYTE;
  }

  /**
   * Creates a property on the given element type, with the given value type and the given number of components
   */
  public IPolygonMeshProperty createProperty(PropertyValueType propertyType, int nComponents) {
    int capacity = sizeAndCapacity.get(1);
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
  public boolean removeProperty(IPolygonMeshProperty property) {
    return properties.remove(property);
  }

  // specific properties, used by CGAL algorithms
  public IPolygonMeshDoubleProperty createNormalProperty() {
    return (IPolygonMeshDoubleProperty) createProperty(PropertyValueType.DOUBLE, 3);
  }
}
