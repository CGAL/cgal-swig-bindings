/*
  Shape_detection_3.h
  Teton Simulation
  Authored on   October 10, 2019
  Last Modified October 10, 2019
*/

/*
  Contains C/C++ backend for SWIG_CGAL Interface Module
*/

#ifndef SWIGCGAL_SHAPE_DETECTION_3_H
#define SWIGCGAL_SHAPE_DETECTION_3_H


//  Shape Detection Library
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/Point_with_normal_3.h>
#include <CGAL/property_map.h>

#include <CGAL/Shape_detection_3.h>
#include <vector>

using namespace std;
using namespace CGAL;


/*
  Shape Detection Type Definitions
*/
typedef CGAL::Exact_predicates_inexact_constructions_kernel  Kernel;
typedef std::pair<Kernel::Point_3, Kernel::Vector_3>         Point_with_normal;
typedef std::vector<Point_with_normal>                       Pwn_vector;
typedef CGAL::First_of_pair_property_map<Point_with_normal>  Point_map;
typedef CGAL::Second_of_pair_property_map<Point_with_normal> Normal_map;
// In Shape_detection_traits the basic types, i.e., Point and Vector types
// as well as iterator type and property maps, are defined.
typedef CGAL::Shape_detection_3::Shape_detection_traits
  <Kernel, Pwn_vector, Point_map, Normal_map>                Traits;
typedef CGAL::Shape_detection_3::Efficient_RANSAC<Traits>    Efficient_ransac;
typedef CGAL::Shape_detection_3::Region_growing<Traits>      Region_growing;
typedef CGAL::Shape_detection_3::Plane<Traits>               Plane;


template <class ShapeType>
class Shape_detection_3_wrapper{

/*
  Private Variables
*/
Efficient_ransac shape_detection;


/*
  Public Functions
*/
public:

//Creation
  Shape_detection_3_wrapper(Pwn_vector points) 
  { 
    shape_detection.set_input(points);
    shape_detection.template add_shape_factory<ShapeType>();
    shape_detection.detect(); 
  }

//Accessors
  countShapes() {return shape_detection.shapes().end() - shape_detection.shapes().begin(); }

//Iterators

};

#endif
