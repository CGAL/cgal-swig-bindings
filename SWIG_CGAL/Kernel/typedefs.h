#ifndef SWIG_CGAL_KERNEL_TYPEDEFS_H
#define SWIG_CGAL_KERNEL_TYPEDEFS_H

#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPIC_Kernel;

#endif
