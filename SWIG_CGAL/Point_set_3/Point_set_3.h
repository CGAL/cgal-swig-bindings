// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POINT_SET_3_POINT_SET_3_H
#define SWIG_CGAL_POINT_SET_3_POINT_SET_3_H

#include <boost/static_assert.hpp>

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Common/Iterator.h>

#include <SWIG_CGAL/Point_set_3/typedefs.h>

#include <sstream>
#include <fstream>


template <typename Point_set_base>
class Point_set_3_wrapper
{
protected:
  std::shared_ptr<Point_set_base> data_sptr;

public:

#ifndef SWIG
  typedef Point_set_base cpp_base;
  const cpp_base& get_data() const { return *data_sptr; }
        cpp_base& get_data()       { return *data_sptr; }
  std::shared_ptr<cpp_base> shared_ptr() { return data_sptr; }
#endif

  typedef Point_set_3_wrapper<Point_set_base> Self;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::const_iterator, unsigned int> iterator;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::Point_range::const_iterator, Point_3> Point_iterator;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::Vector_range::const_iterator, Vector_3> Vector_iterator;

  Point_set_3_wrapper(bool with_normal_map = false) : data_sptr (new cpp_base(with_normal_map)) { }

  SWIG_CGAL_FORWARD_CALL_0(bool, is_empty)
  SWIG_CGAL_FORWARD_CALL_0(bool, empty)

  SWIG_CGAL_FORWARD_CALL_0(unsigned, number_of_points)
  SWIG_CGAL_FORWARD_CALL_0(unsigned, size)
  
  
  bool join (Self other)
  {
    return data_sptr->join (other.get_data());
  }
  
  SWIG_CGAL_FORWARD_CALL_0(void, clear)
  SWIG_CGAL_FORWARD_CALL_0(void, clear_properties)
  
  SWIG_CGAL_FORWARD_CALL_1(void, reserve, unsigned)
  SWIG_CGAL_FORWARD_CALL_1(void, resize, unsigned)
  
  unsigned int insert ()
  {
    return (unsigned int)(*(data_sptr->insert()));
  }
  
  unsigned int insert (const Point_3& point)
  {
    return (unsigned int)(*(data_sptr->insert(point.get_data())));
  }

  unsigned int insert (const Point_3& point, const Vector_3& normal)
  {
    return (unsigned int)(*(data_sptr->insert(point.get_data(), normal.get_data())));
  }

  unsigned int insert (const Self& other, unsigned int idx)
  {
    return (unsigned int)(*(data_sptr->insert(other.get_data(), idx)));
  }

  iterator content() { return iterator (get_data().begin(), get_data().end()); }
  SWIG_CGAL_FORWARD_CALL_1(Point_3, point, unsigned)
  SWIG_CGAL_FORWARD_CALL_1(Vector_3, normal, unsigned)

  SWIG_CGAL_FORWARD_CALL_1(void, remove, unsigned)
  // void remove(iterator, iterator)
  SWIG_CGAL_FORWARD_CALL_1(bool, is_removed, unsigned)
  iterator garbage() { return iterator (get_data().garbage_begin(), get_data().garbage_end()); }
  SWIG_CGAL_FORWARD_CALL_0(unsigned, number_of_removed_points)
  SWIG_CGAL_FORWARD_CALL_0(unsigned, garbage_size)
  SWIG_CGAL_FORWARD_CALL_0(bool, has_garbage)
  SWIG_CGAL_FORWARD_CALL_0(void, collect_garbage)
  SWIG_CGAL_FORWARD_CALL_0(void, cancel_removals)

  // bool has_property_map(string)
  // pair<map,bool> add_property_map(string, T)
  // pair<map,bool> property_map(string)
  // bool remove_property_map(map)

  SWIG_CGAL_FORWARD_CALL_0(bool, has_normal_map)
  // pair<map,bool> add_normal_map(vec)
  // map normal_map()
  SWIG_CGAL_FORWARD_CALL_0(bool, remove_normal_map)
  // map point_map()
  
  void copy_properties (const Self& other)
  {
    data_sptr->copy_properties (other.get_data());
  }

  // vector<string> properties()
  // vector<string, type_info> properties_and_types()

  // NP parameters();
  
  SWIG_CGAL_FORWARD_CALL_0(std::string, info)

  // range range(map)
  
  Point_iterator points() const { return Point_iterator (get_data().points().begin(), get_data().points().end()); }
  Vector_iterator normals() const { return Vector_iterator (get_data().normals().begin(), get_data().normals().end()); }

};

#endif // SWIG_CGAL_POINT_SET_3_POINT_SET_3_H

