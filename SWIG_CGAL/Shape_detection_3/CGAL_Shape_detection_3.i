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

//  Allow 'void' data type
Decl_void_type()

%{
#include <SWIG_CGAL/Shape_detection_3/all_includes.h> 
%}
