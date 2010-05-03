#ifndef SWIG_CGAL_KERNEL_SQUARED_DISTANCE_3_H
#define SWIG_CGAL_KERNEL_SQUARED_DISTANCE_3_H

#include "typedefs.h"
#include <CGAL/squared_distance_3.h>

#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class SquaredDistance_3{
public:
  static double squared_distance(const Point_3& point1, const Point_3& point2){ 
    return CGAL::squared_distance(point1.get_data(), point2.get_data());
  };
  static double squared_distance(const Point_3& point, const Plane_3& plane){ 
    return CGAL::squared_distance(point.get_data(), plane.get_data());
  };
  static double squared_distance(const Point_3& point, const Segment_3& segment){ 
    return CGAL::squared_distance(point.get_data(), segment.get_data());
  };
  static double squared_distance(const Point_3& point, const Line_3& line){ 
    return CGAL::squared_distance(point.get_data(), line.get_data());
  };
  static double squared_distance(const Plane_3& plane, const Point_3& point){ 
    return CGAL::squared_distance(plane.get_data(), point.get_data());
  };
//  static double squared_distance(const Plane_3& plane1, const Plane_3& plane2){ 
//    return CGAL::squared_distance(plane1.get_data(), plane2.get_data());
//  };
  static double squared_distance(const Plane_3& plane, const Segment_3& segment){ 
    return CGAL::squared_distance(plane.get_data(), segment.get_data());
  };
  static double squared_distance(const Plane_3& plane, const Line_3& line){ 
    return CGAL::squared_distance(plane.get_data(), line.get_data());
  };
  static double squared_distance(const Segment_3& segment, const Point_3& point){ 
    return CGAL::squared_distance(segment.get_data(), point.get_data());
  };
  static double squared_distance(const Segment_3& segment, const Plane_3& plane){ 
    return CGAL::squared_distance(segment.get_data(), plane.get_data());
  };
  static double squared_distance(const Segment_3& segment1, const Segment_3& segment2){ 
    return CGAL::squared_distance(segment1.get_data(), segment2.get_data());
  };
  static double squared_distance(const Segment_3& segment, const Line_3& line){ 
    return CGAL::squared_distance(segment.get_data(), line.get_data());
  };
  static double squared_distance(const Line_3& line, const Point_3& point){ 
    return CGAL::squared_distance(line.get_data(), point.get_data());
  };
  static double squared_distance(const Line_3& line, const Plane_3& plane){ 
    return CGAL::squared_distance(line.get_data(), plane.get_data());
  };
  static double squared_distance(const Line_3& line, const Segment_3& segment){ 
    return CGAL::squared_distance(line.get_data(), segment.get_data());
  };
  static double squared_distance(const Line_3& line1, const Line_3& line2){ 
    return CGAL::squared_distance(line1.get_data(), line2.get_data());
  };



  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const SquaredDistance_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_SQUARED_DISTANCE_3_H
