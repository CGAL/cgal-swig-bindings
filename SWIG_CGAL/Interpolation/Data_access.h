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
  Map map_;
  Cpp_base data;
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  const Map& get_map() const {return map_;} 
        Map& get_map()       {return map_;} 
  #endif
  
  Data_access_wrapper():map_(),data(map_){}
        
  void set(const Point& p, Value_type value)
  {
    map_.insert(std::make_pair(p.get_data(),internal::make_conversion(value)));
  }
  
  Value_type get(const Point& p) const
  {
    return Value_type( map_.find(p.get_data())->second );
  }
};

#endif //SWIG_CGAL_INTERPOLATION_DATA_ACCESS_H
