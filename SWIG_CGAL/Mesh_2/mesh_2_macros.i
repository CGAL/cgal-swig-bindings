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

#endif //SWIG_CGAL_MESH_2_DECLARE_MACROS_I
