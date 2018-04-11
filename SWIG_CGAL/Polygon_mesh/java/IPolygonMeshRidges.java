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
import CGAL.Polygon_mesh.Ridges_3.Ridge_type;

public interface IPolygonMeshRidges {

  int getNumberOfRidges();
  int getNumberOfPoints(int i);
  double getStrength(int i);
  double getSharpness(int i);
  Ridge_type getType(int i);
  int getRidgeHalfedge(int ri, int hi);
  double getRidgeBarycentricCoordinate(int ri, int hi);
  double getRidgePointX(int i, int j, PolygonMeshBase pm);
  double getRidgePointY(int i, int j, PolygonMeshBase pm);
  double getRidgePointZ(int i, int j, PolygonMeshBase pm);
}
