// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

%define declare_simply_functions_cdt_and_polygon(COST, STOP)
  %inline %{
    int simplify (PS2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper &ct, COST cost, STOP stop, bool keep_points=false)
    {
      return CGAL::Polyline_simplification_2::simplify(ct.get_data(), cost.get_data(), stop.get_data(), keep_points);
    }
    int simplify (PS2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper &ct, Constraint_id_wrapper<PS_CDTP2>& cid, COST cost, STOP stop, bool keep_points=false)
    {
      return CGAL::Polyline_simplification_2::simplify(ct.get_data(), cid.get_data(), cost.get_data(), stop.get_data(), keep_points);
    }
    Polygon_2 simplify (const Polygon_2& polygon, COST cost, STOP stop)
    {
      Polygon_2::cpp_base res = CGAL::Polyline_simplification_2::simplify(polygon.get_data(), cost.get_data(), stop.get_data());
      return Polygon_2(res);
    }
  %}
%enddef

%define declare_simply_functions_point_range(COST, STOP)
  %inline %{
    void simplify(Wrapper_iterator_helper<Point_2>::input input, COST cost, STOP stop, Wrapper_iterator_helper<Point_2>::output output, bool close=false)
    {
      CGAL::Polyline_simplification_2::simplify(input.first, input.second, cost.get_data(), stop.get_data(), output, close);
    }
  %}
%enddef
