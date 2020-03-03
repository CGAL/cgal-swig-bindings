// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_MESH_2_DECLARE_MACROS_I
#define SWIG_CGAL_MESH_2_DECLARE_MACROS_I


%define declare_conforming_global_functions(CDTWRAPPER)
  %inline %{
    void make_conforming_Delaunay_2(CDTWRAPPER& cdt)
    {
      CGAL::make_conforming_Delaunay_2(cdt.get_data());
    }
    void make_conforming_Gabriel_2(CDTWRAPPER& cdt){
      CGAL::make_conforming_Gabriel_2(cdt.get_data());
    }
  %}
%enddef

%define declare_refine_global_functions(MESHWRAPPER, CRITERIAWRAPPER)
  %inline %{
    void refine_Delaunay_mesh_2 (MESHWRAPPER& t, CRITERIAWRAPPER criteria)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),criteria.get_data());
    }
    void refine_Delaunay_mesh_2 (MESHWRAPPER& t,Point_range range,CRITERIAWRAPPER criteria,bool mark)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),criteria.get_data(),mark);
    }
    void refine_Delaunay_mesh_2 (MESHWRAPPER& t,Point_range range,CRITERIAWRAPPER criteria)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),criteria.get_data());
    }
  %}
%enddef

%define declare_lloyd_2_global_functions(MESHWRAPPER)
  %inline %{
    Mesh_optimization_return_code
    lloyd_optimize_mesh_2  ( MESHWRAPPER& t)
    {
      return CGAL::enum_cast< Mesh_optimization_return_code >(
        CGAL::lloyd_optimize_mesh_2(t.get_data())
      );
    }

    Mesh_optimization_return_code
    lloyd_optimize_mesh_2  (MESHWRAPPER& t,
                            const Mesh_2_parameters& params)
    {
      if (params.seeds_provided())
        return CGAL::enum_cast< Mesh_optimization_return_code >(
          CGAL::lloyd_optimize_mesh_2(t.get_data(),
                                      CGAL::parameters::time_limit = params.get_time_limit(),
                                      CGAL::parameters::max_iteration_number = params.get_max_iteration_number(),
                                      CGAL::parameters::convergence = params.get_convergence(),
                                      CGAL::parameters::freeze_bound = params.get_freeze_bound(),
                                      CGAL::parameters::seeds_begin = params.get_seeds().first,
                                      CGAL::parameters::seeds_end = params.get_seeds().second,
                                      CGAL::parameters::mark = params.get_mark())
        );

      return CGAL::enum_cast< Mesh_optimization_return_code >(
        CGAL::lloyd_optimize_mesh_2(t.get_data(),
                                    CGAL::parameters::time_limit = params.get_time_limit(),
                                    CGAL::parameters::max_iteration_number = params.get_max_iteration_number(),
                                    CGAL::parameters::convergence = params.get_convergence(),
                                    CGAL::parameters::freeze_bound = params.get_freeze_bound(),
                                    CGAL::parameters::mark = params.get_mark())
      );
    }

  %}
%enddef

#endif //SWIG_CGAL_MESH_2_DECLARE_MACROS_I
