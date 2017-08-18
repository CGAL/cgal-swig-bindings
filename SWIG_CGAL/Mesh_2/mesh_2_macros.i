// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
    cgal_lloyd_optimize_mesh_2  ( MESHWRAPPER& t,
                                  double time_limit,
                                  int max_iteration_number,
                                  double convergence,
                                  double freeze_bound,
                                  Point_range seeds,
                                  bool mark   = false)
    {
      return CGAL::enum_cast< Mesh_optimization_return_code >(
        CGAL::lloyd_optimize_mesh_2(t.get_data(),
                                    CGAL::parameters::time_limit = time_limit,
                                    CGAL::parameters::max_iteration_number = max_iteration_number,
                                    CGAL::parameters::convergence = convergence,
                                    CGAL::parameters::freeze_bound = freeze_bound,
                                    CGAL::parameters::seeds_begin = seeds.first,
                                    CGAL::parameters::seeds_end = seeds.second,
                                    CGAL::parameters::mark = mark)
      );
    }

    Mesh_optimization_return_code
    cgal_lloyd_optimize_mesh_2  (MESHWRAPPER& t,
                                 double time_limit   = 0,
                                 int max_iteration_number   = 0,
                                 double convergence   = 0.001,
                                 double freeze_bound   = 0.001)
    {
      return CGAL::enum_cast< Mesh_optimization_return_code >(
        CGAL::lloyd_optimize_mesh_2(t.get_data(),
                                    CGAL::parameters::time_limit = time_limit,
                                    CGAL::parameters::max_iteration_number = max_iteration_number,
                                    CGAL::parameters::convergence = convergence,
                                    CGAL::parameters::freeze_bound = freeze_bound)
      );
    }

  %}
%enddef

#endif //SWIG_CGAL_MESH_2_DECLARE_MACROS_I
