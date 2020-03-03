// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

%import "SWIG_CGAL/common.i"

//modifiers examples
%{
  #include "SWIG_CGAL/Polyhedron_3/modifier_example.h" 
%}
%include "SWIG_CGAL/Polyhedron_3/Modifier_base.h"

%template(Polyhedron_3_Modifier_base)                  Modifier_base< Polyhedron_3_ >;

//simple modifiers
%template(Polyhedron_3_Modifier_1)                     Modifier_wrapper< Polyhedron_3_,Build_triangle<Polyhedron_3_::HalfedgeDS> >;
%template(Polyhedron_3_Modifier_2)                     Modifier_wrapper< Polyhedron_3_,Build_square<Polyhedron_3_::HalfedgeDS> >;


