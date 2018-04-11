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

#ifndef SWIG_CGAL_POLYGON_MESH_SUBDIVISION_METHOD_3_H
#define SWIG_CGAL_POLYGON_MESH_SUBDIVISION_METHOD_3_H

#include <CGAL/subdivision_method_3.h>

struct Subdivision_method_3
{
  static
  void CatmullClark_subdivision(PolygonMesh& pm, int number_of_iterations)
  {
    CGAL::Subdivision_method_3::CatmullClark_subdivision(pm, number_of_iterations);
  }

// disabled as an internal copy is done (which is not possible due to the java alterego)
//  static
//  void DooSabin_subdivision(PolygonMesh& pm, int number_of_iterations)
//  {
//    CGAL::Subdivision_method_3::DooSabin_subdivision(pm, number_of_iterations);
//  }

  static
  void Loop_subdivision(PolygonMesh& pm, int number_of_iterations)
  {
    CGAL::Subdivision_method_3::Loop_subdivision(pm, number_of_iterations);
  }

  static
  void Sqrt3_subdivision(PolygonMesh& pm, int number_of_iterations)
  {
    CGAL::Subdivision_method_3::Sqrt3_subdivision(pm, number_of_iterations);
  }
};

#endif