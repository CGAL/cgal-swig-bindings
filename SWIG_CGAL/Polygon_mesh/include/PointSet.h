// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

#ifndef POLYGON_MESH_POINT_SET_H
#define POLYGON_MESH_POINT_SET_H

#include <CGAL/Iterator_range.h>
#include <boost/function_output_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

class PointSet {

protected:
  // Java environment
  JNIEnv *jni;

  // pointer to the Java alter-ego of this class
  jobject self;

  double *point_x, *point_y, *point_z;
  int *point_index, *size_and_capacity;

  virtual void ensure_capacity(int c) = 0;

public:

  PointSet(){}

  virtual void reserve(int n) = 0;

  int capacity() const
  {
    return size_and_capacity[1];
  }

  int size() const
  {
    return size_and_capacity[0];
  }

  int add_point()
  {
    int new_pos = size_and_capacity[0];
    int new_size = new_pos+1;
    ensure_capacity(new_size);
    size_and_capacity[0]=new_size;
    return new_pos;
  }

  void add_points(int n)
  {
    int new_size = size_and_capacity[0]+n;
    ensure_capacity(new_size);
    size_and_capacity[0]=new_size;
  }

  template <class Point_3>
  int add_point(const Point_3& p)
  {
    set_point(add_point(), p);
    return size_and_capacity[0]-1;
  }

  void removePoint(int i)
  {
    int new_size=size_and_capacity[0]-1;
    if (i!=new_size)
      std::swap(point_index[i], point_index[new_size]);
    size_and_capacity[0]=new_size;
  }

  template <class Point_3>
  Point_3 point_from_index(int i) const
  {
    return Point_3(
      point_x[ i ],
      point_y[ i ],
      point_z[ i ] );
  }

  template <class Point_3>
  Point_3 point(int i) const
  {
    return point_from_index<Point_3>(point_index[i]);
  }

  template <class Point_3>
  void set_point_from_index(int i, const Point_3& p)
  {
    point_x[i] = p[0];
    point_y[i] = p[1];
    point_z[i] = p[2];
  }

  template <class Point_3>
  void set_point(int i, const Point_3& p) {
    set_point_from_index(point_index[i], p);
  }

  void set_point(int i, double x, double y, double z) {
    point_x[ point_index[i] ] = x;
    point_y[ point_index[i] ] = y;
    point_z[ point_index[i] ] = z;
  }

  int index(int i) const {
    return point_index[i];
  }

  int distance(int* it) const
  {
    return static_cast<int>(it-point_index);
  }

  void clear()
  {
    size_and_capacity[0]=0;
  }

  void resize(int new_size)
  {
    if (size_and_capacity[0] >= new_size)
      size_and_capacity[0]=new_size;
    else
      add_points(new_size-size_and_capacity[0]);
  }

// Point iterators
  template <class Point_3>
  struct Index_to_point{
    const PointSet* point_set_ptr;
    typedef Point_3 result_type;
    typedef int argument_type;

    Index_to_point()
      : point_set_ptr(NULL)
    {}

    Index_to_point(const PointSet& point_set)
      : point_set_ptr(&point_set)
    {}

    Point_3 operator()(int i) const
    {
      return point_set_ptr->point<Point_3>(i);
    }
  };

  template <class Point_3>
  boost::transform_iterator<Index_to_point<Point_3>, boost::counting_iterator<int> >
  points_begin() const
  {
    return boost::make_transform_iterator(
      boost::counting_iterator<int>(0),
      Index_to_point<Point_3>(*this) );
  }

  template <class Point_3>
  boost::transform_iterator<Index_to_point<Point_3>, boost::counting_iterator<int> >
  points_end() const
  {
    return boost::make_transform_iterator(
      boost::counting_iterator<int>(size()),
      Index_to_point<Point_3>(*this) );
  }

  template <class Point_3>
  CGAL::Iterator_range<
    boost::transform_iterator<Index_to_point<Point_3>, boost::counting_iterator<int> >
  > points() const
  {
    return CGAL::make_range(points_begin<Point_3>(), points_end<Point_3>());
  }

// index iterator
  typedef int* iterator;
  typedef const int* const_iterator;
  const int* begin() const  { return point_index; }
  const int* end() const { return point_index+size(); }
  CGAL::Iterator_range<const int*> range() const{ return CGAL::make_range(begin(), end()); }

  int* begin() { return point_index; }
  int* end() { return point_index+size(); }
  CGAL::Iterator_range<int*> range() { return CGAL::make_range(begin(), end()); }


// insert iterator
  struct Point_appender{
    PointSet* point_set_ptr;

    Point_appender(PointSet& point_set)
      : point_set_ptr(&point_set)
    {}

    template <class Point_3>
    void operator()(const Point_3& p)
    {
      point_set_ptr->add_point(p);
    }
  };

  boost::function_output_iterator<Point_appender>
  inserter()
  {
    return boost::make_function_output_iterator( Point_appender(*this) );
  }

  template <class NormalMap>
  struct Point_and_normal_appender{
    PointSet* point_set_ptr;
    NormalMap nmap;

    Point_and_normal_appender(PointSet& point_set, const NormalMap& nmap)
      : point_set_ptr(&point_set), nmap(nmap)
    {}

    template <class Point_3, class Vector_3>
    void operator()(const std::pair<Point_3, Vector_3>& p)
    {
      int pos = point_set_ptr->add_point(p.first);
      put(nmap, point_set_ptr->index(pos), p.second);
    }
  };

  template <class NormalMap>
  boost::function_output_iterator<Point_and_normal_appender<NormalMap> >
  inserter(const NormalMap& nmap)
  {
    return boost::make_function_output_iterator( Point_and_normal_appender<NormalMap>(*this, nmap) );
  }


};

#endif
