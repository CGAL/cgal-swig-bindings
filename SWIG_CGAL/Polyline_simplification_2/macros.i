// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

%define declare_simply_functions(COST, STOP)
  %inline %{
    Polygon_2 simplify (const Polygon_2& polygon, COST cost, STOP stop)
    {
      Polygon_2::cpp_base res = CGAL::Polyline_simplification_2::simplify(polygon.get_data(), cost.get_data(), stop.get_data());
      return Polygon_2(res);
    }

    void simplify(Wrapper_iterator_helper<Point_2>::input input, COST cost, STOP stop, Wrapper_iterator_helper<Point_2>::output output, bool close=false)
    {
      CGAL::Polyline_simplification_2::simplify(input.first, input.second, cost.get_data(), stop.get_data(), output, close);
    }

    int simplify (PS2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper &ct, COST cost, STOP stop, bool keep_points=false)
    {
      return CGAL::Polyline_simplification_2::simplify(ct.get_data(), cost.get_data(), stop.get_data(), keep_points);
    }

    int simplify (PS2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper &ct, Constraint_id_wrapper<PS_CDTP2>& cid, COST cost, STOP stop, bool keep_points=false)
    {
      return CGAL::Polyline_simplification_2::simplify(ct.get_data(), cid.get_data(), cost.get_data(), stop.get_data(), keep_points);
    }
  %}
%enddef
