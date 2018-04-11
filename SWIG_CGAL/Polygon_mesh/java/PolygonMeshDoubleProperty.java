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

import CGAL.Polygon_mesh.PolygonMeshUtils;

public class PolygonMeshDoubleProperty implements IPolygonMeshDoubleProperty {

  private static double DEFAULT_INIT_VALUE = 0d;

  private double initValue;
  private int nComponents;
  private int currentCapacity;
  private DoubleBuffer values;

  private PolygonMeshDoubleProperty() {}

  public PolygonMeshDoubleProperty(int nElements, int nComponents) {
    this(nElements, nComponents, DEFAULT_INIT_VALUE);
  }

  public PolygonMeshDoubleProperty(int nElements, int nComponents, double initValue) {
    this.nComponents = nComponents;
    this.initValue = initValue;
    this.currentCapacity = nElements;
    values = PolygonMeshUtils.allocateNewDoubleBuffer(this.currentCapacity * nComponents);
  }

  @Override
  public void resize(int newElementCapacity) {
    int oldCapacity = currentCapacity;
    currentCapacity = newElementCapacity;
    values = PolygonMeshUtils.allocateNewDoubleBuffer(currentCapacity * nComponents);
    for (int i = oldCapacity; i < currentCapacity; i++)
      values.put(i, initValue);
  }

  @Override
  public int getNumberOfcomponents() {
    return nComponents;
  }

  @Override
  public double initializationValue() {
    return initValue;
  }

  @Override
  public DoubleBuffer getDoubleBuffer() {
    return values;
  }

  @Override
  public double get(int e) {
    return values.get(nComponents * e);
  }
  
  @Override
  public void set(int e, double v) {
    values.put(nComponents * e, v); 
  }

  @Override
  public double get(int e, int component) {
    return values.get(nComponents * e + component);
  }
  
  @Override
  public void set(int e, int component, double v) {
    values.put(nComponents * e + component, v); 
  }

  @Override
  public PolygonMeshDoubleProperty copy() {
    PolygonMeshDoubleProperty copy = new PolygonMeshDoubleProperty();
    copy.initValue = this.initValue;
    copy.nComponents = this.nComponents;
    copy.currentCapacity = this.currentCapacity;
    copy.values = PolygonMeshUtils.allocateNewDoubleBuffer(values);
    return copy;
  } 
}
