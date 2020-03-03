// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


%{
  #include <SWIG_CGAL/Common/Reference_wrapper.h>
%}
%include "SWIG_CGAL/Common/Reference_wrapper.h"
//the _2 is needed to avoid clash with the dim 3
SWIG_CGAL_declare_identifier_of_template_class(Ref_Locate_type_2,Reference_wrapper<SWIG_Triangulation_2::Locate_type>)
