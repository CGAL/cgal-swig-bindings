/*
  CGAL_Shape_detection_3.i
  Teton Simulation
  Authored on   October 10, 2019
  Last Modified October 10, 2019
*/

/*
  Python Interface for CGAL's Shape Detection Algorithm

  This interface contains functions for detecting 3-dimensional 
  shapes within an unsorted point cloud (e.g. vertex vector).

  Includes support for:
      * Efficient RANSAC 
*/


//  Define CGAL Module
%module CGAL_Shape_detection_3

//  Standard API imports
%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h" //C++ macros that helps wrapping CGAL classes
%import  "SWIG_CGAL/Common/Iterator.h"
Decl_void_type()

%include "SWIG_CGAL/User_packages/Shape_detection_3/all_includes.h"
%{ 
#include <SWIG_CGAL/User_packages/Shape_detection_3/all_includes.h> 
%}

%include "SWIG_CGAL/User_packages/Shape_detection_3/Shape_detection_3.h"


//SWIG_CGAL_declare_identifier_of_template_class(Shape_iterator, CGAL_Shape_handle<Efficient_ransac, Plane>)

//  Main Class
SWIG_CGAL_declare_identifier_of_template_class(Shape_detection_3, Shape_detection_3_wrapper<Efficient_ransac, Plane, Kernel::Point_3, Kernel::Vector_3>)


