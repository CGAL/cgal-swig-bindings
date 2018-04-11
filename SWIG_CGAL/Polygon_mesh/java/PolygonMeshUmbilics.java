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
import CGAL.Polygon_mesh.Ridges_3.Umbilic_type;

public class PolygonMeshUmbilics implements IPolygonMeshUmbilics {

  private IntBuffer types;
  private IntBuffer contourHalfedges;
  private IntBuffer umbilics;
  private IntBuffer nbUmbilicsAndRanges;

  /**
   * Creates an empty multi polyline with an initial capacity of one ridge of ten points.
   */
  public PolygonMeshUmbilics() {
    reserve(1, 10);
  }

  /**
   * Initializes capacities
   */
  public void reserve(int nUmbilics, int totalNContourHalfedges)
  {
    this.types=PolygonMeshUtils.allocateNewIntBuffer(nUmbilics);
    this.contourHalfedges=PolygonMeshUtils.allocateNewIntBuffer(totalNContourHalfedges);
    this.nbUmbilicsAndRanges=PolygonMeshUtils.allocateNewIntBuffer(nUmbilics+2);
    this.umbilics=PolygonMeshUtils.allocateNewIntBuffer(nUmbilics);
    nbUmbilicsAndRanges.put(0,nUmbilics);
  }

  /**
   * returns the i-th umbilic
   */
  public int getUmbilic(int i){
    return umbilics.get(i);
  }

  /**
   * returns the type of the i-th umbilic
   */
  public Umbilic_type getType(int i){
    return Umbilic_type.swigToEnum(types.get(i));
  }

  /**
   * returns the j-th contour halfedge of the i-th umbilic
   */
  public int getHalfedgeContour(int i, int j) {
    return contourHalfedges.get(nbUmbilicsAndRanges.get(i+1) + j);
  }

  /**
   * Returns the number of umbilics in this object
   */
  @Override
  public int getNumberOfUmbilics() {
    return nbUmbilicsAndRanges.get(0);
  }

  /**
   * Returns the number of contour halfedges in the i-th umbilic
   */
  @Override
  public int getNumberOfCoutourHalfedges(int i) {
    return nbUmbilicsAndRanges.get(i+2) - nbUmbilicsAndRanges.get(i+1);
  }

  /**
   * Method used by native code to access the type array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getTypesArray() {
    return types;
  }

  /**
   * Method used by native code to access the contour halfedge array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getContourHalfedgeArray() {
    return contourHalfedges;
  }

  /**
   * Method used by native code to access the nb umbilics and size array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getNbUmbilicsAndRangeArray() {
    return nbUmbilicsAndRanges;
  }

  /**
   * Method used by native code to access the umbilic array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getUmbilicArray() {
    return umbilics;
  }
}
