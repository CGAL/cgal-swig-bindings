// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_TYPEDEFS_H
#define SWIG_CGAL_KERNEL_TYPEDEFS_H

#include <SWIG_CGAL/Kernel/decl.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Lazy_exact_nt.h>
#include <CGAL/Cartesian_converter.h>
#include <CGAL/internal/Exact_type_selector.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC_Kernel;

typedef CGAL::internal::Exact_type_selector<int>::Type Exact_nt;
typedef CGAL::Simple_cartesian< CGAL::Lazy_exact_nt<Exact_nt> > LZNT_Kernel;

typedef CGAL::Cartesian_converter<EPIC_Kernel,LZNT_Kernel> To_Lazy;
typedef CGAL::Cartesian_converter<LZNT_Kernel,EPIC_Kernel> To_EPIC;
#endif
