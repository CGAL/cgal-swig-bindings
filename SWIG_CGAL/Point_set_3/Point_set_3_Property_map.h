// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_POINT_SET_3_PROPERTY_MAP_H
#define SWIG_CGAL_POINT_SET_3_PROPERTY_MAP_H

#include <boost/static_assert.hpp>

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Common/Iterator.h>

#include <SWIG_CGAL/Point_set_3/typedefs.h>

#include <sstream>
#include <fstream>

namespace SWIG_Point_set_3
{

template <typename T>
struct CppType
{
  typedef T type;
  static T get_data(const T& t) { return t; }
};
template <>
struct CppType<Point_3>
{
  typedef typename Point_3::cpp_base type;
  static type get_data (const Point_3& p) { return p.get_data(); }
};
template <>
struct CppType<Vector_3>
{
  typedef typename Vector_3::cpp_base type;
  static type get_data (const Vector_3& n) { return n.get_data(); }
};

template <typename Point_set_base, typename Type>
class CGAL_Property_map
{
  typename Point_set_base::template Property_map<typename CppType<Type>::type> data;
  bool valid;

public:
#ifndef SWIG
  typedef typename Point_set_base::template Property_map<typename CppType<Type>::type> cpp_base;
  CGAL_Property_map (cpp_base map, bool valid) : data(map), valid(valid) { }
#if CGAL_VERSION_NR >= 1060000000
  CGAL_Property_map (const std::optional<cpp_base>& opt_map)
    : valid(opt_map)
  {
    if (valid)
      data=*opt_map;
  }
#endif
  CGAL_Property_map (std::pair<cpp_base, bool> map_and_valid)
    : data(map_and_valid.first), valid(map_and_valid.second) { }
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
#endif

  typedef CGAL_Property_map<Point_set_base, Type> Self;

  CGAL_Property_map() : data(), valid(false) { }

  Type get (int idx) const { return data[idx]; }
  void set (int idx, const Type& t) { data[idx] = CppType<Type>::get_data(t); }
  bool is_valid() const { return valid; }

//Deep copy
  Self deepcopy() const {return Self(data, valid);}
  void deepcopy(const Self& other){data=other.get_data(); valid=other.is_valid(); }
};

}


#endif // SWIG_CGAL_POINT_SET_3_PROPERTY_MAP_H

