// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DATA_ACCESS_H
#define SWIG_CGAL_INTERPOLATION_DATA_ACCESS_H

#include <SWIG_CGAL/Common/Macros.h>
#include <CGAL/interpolation_functions.h>

namespace internal
{
  template <class T>
  struct get_map_type;
  
  template <class T>
  struct get_map_type<CGAL::Data_access<T> >
  {
    typedef T map_type;
  };
}

template <class Cpp_base,class Point,class Value_type>
class Data_access_wrapper
{
  typedef typename internal::get_map_type<Cpp_base>::map_type Map;
  Map m_map;
  Cpp_base data;
  typedef Data_access_wrapper<Cpp_base,Point,Value_type> Self;
//disable deep copy (Data_accessor has a const& member that prevents default construction induced by SWIG)
  Self deepcopy();
  void deepcopy(const Self&); 
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  const Map& get_map() const {return m_map;} 
        Map& get_map()       {return m_map;}
  #endif
  
  Data_access_wrapper():m_map(),data(m_map){}
        
  void set(const Point& p, Value_type value)
  {
    m_map.insert(std::make_pair(p.get_data(),internal::make_conversion(value)));
  }
  
  Value_type get(const Point& p) const
  {
    return Value_type( m_map.find(p.get_data())->second );
  }
};

#endif //SWIG_CGAL_INTERPOLATION_DATA_ACCESS_H
