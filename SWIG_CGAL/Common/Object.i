// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 

#ifndef SWIG_CGAL_Kernel_MODULE
%typemap(javaimports) Object%{
  import CGAL.Kernel.Point_2;
  import CGAL.Kernel.Point_3;
  import CGAL.Kernel.Triangle_2;
  import CGAL.Kernel.Triangle_3;
  import CGAL.Kernel.Segment_3;
  import CGAL.Kernel.Segment_2;
  import CGAL.Kernel.Line_3;
  import CGAL.Kernel.Line_2;
  import CGAL.Kernel.Plane_3;
  import CGAL.Kernel.Ray_2;
  import CGAL.Kernel.Ray_3;
%}
#endif

#define SWIG_CGAL_DECLARE_FCT_IS_AND_GET(TYPE) \
  bool is_##TYPE(); \
  TYPE get_##TYPE();

class Object 
{
public:
  Object(){};
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Point_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Point_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Triangle_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Triangle_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Segment_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Segment_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Line_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Line_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Plane_3)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Ray_2)
  SWIG_CGAL_DECLARE_FCT_IS_AND_GET(Ray_3)
  SWIG_CGAL_FORWARD_CALL_0(bool,empty)
};
