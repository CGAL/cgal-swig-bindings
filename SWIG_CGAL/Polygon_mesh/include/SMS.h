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

#ifndef SWIG_CGAL_PolygonMesh_SMS_H
#define SWIG_CGAL_PolygonMesh_SMS_H

#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <SWIG_CGAL/Polygon_mesh/include/utilities.h>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <boost/shared_ptr.hpp>

// Stop-condition policies
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_stop_predicate.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_length_stop_predicate.h>

// Cost policies
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/LindstromTurk_cost.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_length_cost.h>

// Placement policies
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/LindstromTurk_placement.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Midpoint_placement.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Constrained_placement.h>


#include <CGAL/boost/graph/properties.h>

#ifndef SWIG
namespace SMS = CGAL::Surface_mesh_simplification;
#endif

struct Triangulated_surface_mesh_simplification
{
  enum Placement { LINDSTROMTURK_PLACEMENT, MIDPOINT_PLACEMENT};
  enum Cost { LINDSTROMTURK_COST, EDGE_LENGTH_COST};
  enum Stop { COUNT_RATIO_STOP, COUNT_STOP, EDGE_LENGTH_STOP};

  static int
  edge_collapse(PolygonMesh& pm,
                Stop stop,
                double stop_param,
                Placement placement=LINDSTROMTURK_PLACEMENT,
                Cost cost=LINDSTROMTURK_COST)
  {
    switch (placement)
    {
      case LINDSTROMTURK_PLACEMENT:
        switch(cost)
        {
          case LINDSTROMTURK_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
            }
          case EDGE_LENGTH_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::LindstromTurk_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
            }
        }
      case MIDPOINT_PLACEMENT:
        switch(cost)
        {
          case LINDSTROMTURK_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>())
                );
            }
          case EDGE_LENGTH_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Midpoint_placement<PolygonMesh>()).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>())
                );
            }
        }
    }
    return -1;
  }

  static int
  edge_collapse(PolygonMesh& pm,
                Stop stop,
                double stop_param,
                PolygonMeshBoolPropertyJNI& edge_bool_map,
                Placement placement=LINDSTROMTURK_PLACEMENT,
                Cost cost=LINDSTROMTURK_COST)
  {
    typedef PolygonMesh_property<PolygonMeshBoolPropertyJNI, PolygonMesh::Edge_descriptor, bool> Ecm;
    Ecm ecm(edge_bool_map);

    switch (placement)
    {
      case LINDSTROMTURK_PLACEMENT:
        switch(cost)
        {
          case LINDSTROMTURK_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
            }
          case EDGE_LENGTH_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::LindstromTurk_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
            }
        }
      case MIDPOINT_PLACEMENT:
        switch(cost)
        {
          case LINDSTROMTURK_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::LindstromTurk_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
            }
          case EDGE_LENGTH_COST:
            switch(stop)
            {
              case COUNT_RATIO_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_ratio_stop_predicate<PolygonMesh>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case COUNT_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Count_stop_predicate<PolygonMesh>((int) stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
              case EDGE_LENGTH_STOP:
                return SMS::edge_collapse(pm,
                  SMS::Edge_length_stop_predicate<double>(stop_param),
                  CGAL::parameters::get_placement(SMS::Constrained_placement<SMS::Midpoint_placement<PolygonMesh>, Ecm>(ecm)).
                  get_cost(SMS::Edge_length_cost<PolygonMesh>()).
                  edge_is_constrained_map(ecm)
                );
            }
        }
    }
    return -1;
  }
};

#endif
