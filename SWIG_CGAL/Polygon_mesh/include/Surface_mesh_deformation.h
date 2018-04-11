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

#ifndef SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_DEFORMATION_H
#define SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_DEFORMATION_H

#include <CGAL/Surface_mesh_deformation.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <boost/shared_ptr.hpp>

struct Surface_mesh_deformation
{
  static
  bool
  deform(PolygonMesh&pm,
         RangeIndexJNI roi_vertex_range,
         RangeIndexJNI ctl_vertex_range,
         boost::shared_ptr< std::vector<EPIC_Kernel::Point_3> > ctl_new_positions,
         int nb_iterations = 10,
         double delta_energy = 0)
  {
    typedef CGAL::Surface_mesh_deformation<PolygonMesh> Surface_mesh_deformation;
    typedef boost::graph_traits<PolygonMesh>::vertex_descriptor vertex_descriptor;

    Surface_mesh_deformation deform_mesh(pm);

    //insert ROI vertices
    if (roi_vertex_range.indices == NULL)
      deform_mesh.insert_roi_vertices(vertices(pm).first,
                                      vertices(pm).second);
    else
      deform_mesh.insert_roi_vertices(make_range(roi_vertex_range).first,
                                      make_range(roi_vertex_range).second);

    //insert control vertices
    if (ctl_vertex_range.indices==NULL)
      return false;

    for (int i=0; i< ctl_vertex_range.size; ++i)
      deform_mesh.insert_control_vertex( vertex_descriptor(ctl_vertex_range.indices[i]) );

    bool is_matrix_factorization_OK = deform_mesh.preprocess();

    if(!is_matrix_factorization_OK)
      return false;

    //set target positions
    for (int i=0; i< ctl_vertex_range.size; ++i)
    {
      vertex_descriptor vd = vertex_descriptor(ctl_vertex_range.indices[i]);
      deform_mesh.set_target_position(vd, (*ctl_new_positions)[i]);
    }

    //run the deformation
    deform_mesh.deform(nb_iterations, delta_energy);
    return true;
  }
};

#endif //SWIG_CGAL_POLYGON_MESH_SURFACE_MESH_DEFORMATION_H
