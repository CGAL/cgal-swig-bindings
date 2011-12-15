// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%{
  #include <SWIG_CGAL/Common/Reference_wrapper.h>
%}
%include "SWIG_CGAL/Common/Reference_wrapper.h"
//the _2 is needed to avoid clash with the dim 3
SWIG_CGAL_declare_identifier_of_template_class(Ref_Locate_type_2,Reference_wrapper<SWIG_Triangulation_2::Locate_type>)
