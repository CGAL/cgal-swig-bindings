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

public interface IPointSetBase {

  /**
   * Returns a copy of the container.
   */
  public PointSetBase copy();

  /**
   * Returns the capacity of the container
   */
  public int Capacity();
  /**
   * Returns the number of points
   */
  public int getNumberOfPoints();

  /**
   * Adds a new point
   */
  public int addPoint();

  /**
   * Adds a new point and set its coordinates
   */
  public int addPoint(double x, double y, double z);

  /**
   * Removes a point
   */
  public void removePoint(int i);

  /**
   * Returns the x coordinate of a point
   */
  public double pointX(int i);

  /**
   * Returns the y coordinate of a point
   */
  public double pointY(int i);

  /**
   * Returns the z coordinate of a point
   */
  public double pointZ(int i);

  /**
   * Sets the x coordinate of a point
   */
  public void setPointX(int i, double d);

  /**
   * Sets the y coordinate of a point
   */
  public void setPointY(int i, double d);

  /**
   * Sets the z coordinate of a point
   */
  public void setPointZ(int i, double d);

  /**
   * Returns the index associated to a given point
   */
  public int getIndex(int i);

}
