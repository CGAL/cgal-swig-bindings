/*
    typedefs.h
    Teton Simulation
    Authored on   October 19, 2019
    Last Modified October 19, 2019
*/

#ifndef SWIG_CGAL_SHAPE_DETECTION_3_TYPEDEFS_H
#define SWIG_CGAL_SHAPE_DETECTION_3_TYPEDEFS_H


#include <CGAL/Shape_detection_3.h>
#include <CGAL/Shape_detection_3/Efficient_RANSAC.h>

#include <SWIG_CGAL/Kernel/typedefs.h>

// Type declarations
typedef CGAL::Exact_predicates_inexact_constructions_kernel  Kernel;
typedef std::pair<Kernel::Point_3, Kernel::Vector_3>  Point_with_normal;
typedef std::vector<Point_with_normal>                       Pwn_vector;
typedef CGAL::First_of_pair_property_map<Point_with_normal>  Point_map;
typedef CGAL::Second_of_pair_property_map<Point_with_normal> Normal_map;
// In Shape_detection_traits the basic types, i.e., Point and Vector types
// as well as iterator type and property maps, are defined.
typedef CGAL::Shape_detection_3::Shape_detection_traits
  <Kernel, Pwn_vector, Point_map, Normal_map>                Traits;
typedef CGAL::Shape_detection_3::Efficient_RANSAC<Traits>    Efficient_ransac;
typedef CGAL::Shape_detection_3::Plane<Traits>               Plane;

#endif
