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
import CGAL.Polygon_mesh.Ridges_3.Ridge_type;

public class PolygonMeshRidges implements IPolygonMeshRidges {

  private IntBuffer types;
  private DoubleBuffer strengths;
  private DoubleBuffer sharpnesses;
  private IntBuffer halfedges;
  private DoubleBuffer barycentricCoordinates;
  private IntBuffer nbRidgesAndRanges;

  /**
   * Creates an empty multi polyline with an initial capacity of one ridge of ten points.
   */
  public PolygonMeshRidges() {
    reserve(1, 10);
  }

  /**
   * Initializes capacities
   */
  public void reserve(int nRidges, int totalNpoints)
  {
    this.types=PolygonMeshUtils.allocateNewIntBuffer(nRidges);
    this.strengths=PolygonMeshUtils.allocateNewDoubleBuffer(nRidges);
    this.sharpnesses=PolygonMeshUtils.allocateNewDoubleBuffer(nRidges);
    this.halfedges=PolygonMeshUtils.allocateNewIntBuffer(totalNpoints);
    this.barycentricCoordinates=PolygonMeshUtils.allocateNewDoubleBuffer(totalNpoints);
    this.nbRidgesAndRanges=PolygonMeshUtils.allocateNewIntBuffer(nRidges+2);
    nbRidgesAndRanges.put(0,nRidges);
  }

  /**
   * returns the strength of the i-th ridge
   */
  public double getStrength(int i) {
    return strengths.get(i);
  }

  /**
   * returns the sharpness of the i-th ridge
   */
  public double getSharpness(int i) {
    return strengths.get(i);
  }

  /**
   * returns the type of the i-th ridge
   */
  public Ridge_type getType(int i){
    return Ridge_type.swigToEnum(types.get(i));
  }

  /**
   * returns the j-th halfedge of the i-th ridge
   */
  public int getRidgeHalfedge(int i, int j) {
    return halfedges.get(nbRidgesAndRanges.get(i+1) + j);
  }

  /**
   * returns the j-th barycentric coordinate of the i-th ridge
   */
  public double getRidgeBarycentricCoordinate(int i, int j) {
    return barycentricCoordinates.get(nbRidgesAndRanges.get(i+1) + j);
  }

  /**
   * returns the X-coordinate of the j-th point of the i-th ridge
   */
  public double getRidgePointX(int i, int j, PolygonMeshBase pm){
    int h = getRidgeHalfedge(i, j);
    double w_src = getRidgeBarycentricCoordinate(i, j);
    return pm.vertexX( pm.source(h) ) * w_src +
           pm.vertexX( pm.target(h) ) * (1-w_src);
  }

  /**
   * returns the Y-coordinate of the j-th point of the i-th ridge
   */
  public double getRidgePointY(int i, int j, PolygonMeshBase pm){
    int h = getRidgeHalfedge(i, j);
    double w_src = getRidgeBarycentricCoordinate(i, j);
    return pm.vertexY( pm.source(h) ) * w_src +
           pm.vertexY( pm.target(h) ) * (1-w_src);
  }

  /**
   * returns the Z-coordinate of the j-th point of the i-th ridge
   */
  public double getRidgePointZ(int i, int j, PolygonMeshBase pm){
    int h = getRidgeHalfedge(i, j);
    double w_src = getRidgeBarycentricCoordinate(i, j);
    return pm.vertexZ( pm.source(h) ) * w_src +
           pm.vertexZ( pm.target(h) ) * (1-w_src);
  }

  /**
   * Returns the number of polylines in this object
   */
  @Override
  public int getNumberOfRidges() {
    return nbRidgesAndRanges.get(0);
  }

  /**
   * Returns the number of points in the i-th ridge
   */
  @Override
  public int getNumberOfPoints(int i) {
    return nbRidgesAndRanges.get(i+2) - nbRidgesAndRanges.get(i+1);
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
   * Method used by native code to access the strength array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getStrengthsArray() {
    return strengths;
  }

  /**
   * Method used by native code to access the sharpness array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getSharpnessArray() {
    return sharpnesses;
  }

  /**
   * Method used by native code to access the halfedge array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getHalfedgeArray() {
    return halfedges;
  }

  /**
   * Method used by native code to access the barycentric coordinate array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private DoubleBuffer getBarycentricCoordinateArray() {
    return barycentricCoordinates;
  }

  /**
   * Method used by native code to access the nb ridges and size array.<br>
   * <b>Warning:</b> Do not remove the method even if unused (it is called by native code)
   */
  @SuppressWarnings("unused")
  private IntBuffer getnbRidgesAndRangeArray() {
    return nbRidgesAndRanges;
  }
}
