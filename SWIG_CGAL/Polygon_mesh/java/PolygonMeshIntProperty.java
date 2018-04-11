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

import CGAL.Polygon_mesh.PolygonMeshUtils;

public class PolygonMeshIntProperty implements IPolygonMeshIntProperty {

  private static int DEFAULT_INIT_VALUE = 0;

  private int initValue;
  private int nComponents;
  private int currentCapacity;
  private IntBuffer values;

  private PolygonMeshIntProperty() {}

  public PolygonMeshIntProperty(int nElements, int nComponents) {
    this(nElements, nComponents, DEFAULT_INIT_VALUE);
  }

  public PolygonMeshIntProperty(int nElements, int nComponents, int initValue) {
    this.nComponents = nComponents;
    this.initValue = initValue;
    this.currentCapacity = nElements;
    values = PolygonMeshUtils.allocateNewIntBuffer(this.currentCapacity * nComponents);
  }

  @Override
  public void resize(int newElementCapacity) {
    int oldCapacity = currentCapacity;
    currentCapacity = newElementCapacity;
    values = PolygonMeshUtils.allocateNewIntBuffer(currentCapacity * nComponents);
    for (int i = oldCapacity; i < currentCapacity; i++)
      values.put(i, initValue);
  }

  @Override
  public int getNumberOfcomponents() {
    return nComponents;
  }

  @Override
  public int initializationValue() {
    return initValue;
  }

  @Override
  public IntBuffer getIntBuffer() {
    return values;
  }

  @Override
  public int get(int e) {
    return values.get(nComponents * e);
  }
  
  @Override
  public void set(int e, int v) {
    values.put(nComponents * e, v); 
  }

  @Override
  public int get(int e, int component) {
    return values.get(nComponents * e + component);
  }
  
  @Override
  public void set(int e, int component, int v) {
    values.put(nComponents * e + component, v); 
  }

  @Override
  public PolygonMeshIntProperty copy() {
    PolygonMeshIntProperty copy = new PolygonMeshIntProperty();
    copy.initValue = this.initValue;
    copy.nComponents = this.nComponents;
    copy.currentCapacity = this.currentCapacity;
    copy.values = PolygonMeshUtils.allocateNewIntBuffer(values);
    return copy;
  } 
}
