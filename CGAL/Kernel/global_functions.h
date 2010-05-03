#ifndef CGAL_SWIG_KERNEL_GLOBAL_FUNCTIONS_H
#define CGAL_SWIG_KERNEL_GLOBAL_FUNCTIONS_H

#include "typedefs.h"
#include <CGAL/squared_distance_3.h>
#include "Point_3.h"
#include "Plane_3.h"
#include "Line_3.h"
#include "Segment_3.h"


#define CGAL_SWIG_GF_MACRO_DEFINITION
#include "../Common/global_function_macros.h"
#undef CGAL_SWIG_GF_MACRO_DEFINITION


#include "global_function_signatures.h"

#undef FORWARD_CALL_GF_1
#undef FORWARD_CALL_GF_2

#endif //CGAL_SWIG_KERNEL_GLOBAL_FUNCTIONS_H
