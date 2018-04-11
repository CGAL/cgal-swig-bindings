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

#ifndef SWIG_CGAL_POLYGON_MESH_CONVEX_HULL_3_H
#define SWIG_CGAL_POLYGON_MESH_CONVEX_HULL_3_H

#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <CGAL/convex_hull_3.h>

#ifndef SWIG
// workaround bug in CGAL
int add_vertex(const EPIC_Kernel::Point_3& p, PolygonMesh& pm)
{
  int v=add_vertex(pm);
  pm.setVertexX(v, p[0]);
  pm.setVertexY(v, p[1]);
  pm.setVertexZ(v, p[2]);
  return v;
}
#endif

#include <CGAL/Convex_hull_3/dual/halfspace_intersection_3.h>

struct Convex_hull_3{

static
bool is_strongly_convex_3(PolygonMesh& pm)
{
  return CGAL::is_strongly_convex_3(pm);
}

static
void convex_hull_3(boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > points,
                   PolygonMesh& pm)
{
  CGAL::convex_hull_3(points->begin(), points->end(), pm);
}

static
void convex_hull_3(PointSet& ps,
                   PolygonMesh& pm)
{
  CGAL::convex_hull_3(ps.points_begin<EPIC_Kernel::Point_3>(), ps.points_end<EPIC_Kernel::Point_3>(), pm);
}

static
void halfspace_intersection_3(boost::shared_ptr< std::vector<EPIC_Kernel::Plane_3> > planes,
                              PolygonMesh& pm)
{
  CGAL::halfspace_intersection_3(planes->begin(), planes->end(), pm);
}

static
void halfspace_intersection_3(boost::shared_ptr< std::vector<EPIC_Kernel::Plane_3> > planes,
                              PolygonMesh& pm,
                              double x, double y, double z)
{
  CGAL::halfspace_intersection_3(planes->begin(), planes->end(), pm, EPIC_Kernel::Point_3(x,y,z));
}

};

#endif